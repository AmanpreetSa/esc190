#include "seamcarving.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double min(double a, double b)
{
    if (a <= b) {
        return a;
    }
    else {
        return b;
    }
}

void calc_energy(struct rgb_img *im, struct rgb_img **grad)
{
    create_img(grad, im->height, im->width);
    
    // note: treat image as an matrix (y,x)
    // rows (y values) increase as you go down
    // columns (x values) increase as you go right

    // logic for wrapping:
    // for missing left neighbour: wrap to rightmost pixel
    // for mising right neighbour: wrap to start pixel (leftmost pixel)
    // for missing top neighbour: wrap to bottom pixel
    // for missing bottom neighbour: wrap to top pixel

    for (int i = 0; i < im->height; i++) {
        for (int j = 0; j < im->width; j++) {
            
            int left_x;
            if (j > 0) {
                left_x = j - 1;  // left to current pixel
            } else {
                left_x = im->width - 1;  // wrap to rightmost pixel
            }

            int right_x;
            if (j < im->width - 1) {
                right_x = j + 1;  // right to current pixel
            } else {
                right_x = 0;  // wrap to leftmost pixel
            }

            int up_y;
            if (i > 0) {
                up_y = i - 1;  // above current pixel
            } else {
                up_y = im->height - 1;  // wrap to bottom pixel
            }

            int down_y;
            if (i < im->height - 1) {
                down_y = i + 1;  // below current pixel
            } else {
                down_y = 0;  // Edge case: wrap to top pixel
            }

            // rgb values x-direction
            uint8_t r_left = get_pixel(im, i, left_x, 0);
            uint8_t g_left = get_pixel(im, i, left_x, 1);
            uint8_t b_left = get_pixel(im, i, left_x, 2);
            
            uint8_t r_right = get_pixel(im, i, right_x, 0);
            uint8_t g_right = get_pixel(im, i, right_x, 1);
            uint8_t b_right = get_pixel(im, i, right_x, 2);
            
            // rgb values y-direction
            uint8_t r_up = get_pixel(im, up_y, j, 0);
            uint8_t g_up = get_pixel(im, up_y, j, 1);
            uint8_t b_up = get_pixel(im, up_y, j, 2);
            
            uint8_t r_down = get_pixel(im, down_y, j, 0);
            uint8_t g_down = get_pixel(im, down_y, j, 1);
            uint8_t b_down = get_pixel(im, down_y, j, 2);
            
            // x-grad (difference between left and right)
            int rx_grad = r_right - r_left;
            int gx_grad = g_right - g_left;
            int bx_grad = b_right - b_left;
            
            // y-grad (difference between up and down)
            int ry_grad = r_down - r_up;
            int gy_grad = g_down - g_up;
            int by_grad = b_down - b_up;
            
            // compute dual-gradient energy via formula
            double energy = sqrt(
                rx_grad * rx_grad + 
                gx_grad * gx_grad + 
                bx_grad * bx_grad +
                ry_grad * ry_grad + 
                gy_grad * gy_grad + 
                by_grad * by_grad
            );
            
            uint8_t energy_val = (uint8_t)(energy / 10.0);
            set_pixel(*grad, i, j, energy_val, energy_val, energy_val);
        }
    }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr)
{
    // logic (from top to bottom, thus only look at row adajacent to current row):
    // up = (i-1,j)
    // up_left = (i-1,j-1)
    // up_right = (i-1,j+1)    
    
    *best_arr = (double *)malloc(grad->height * grad->width * sizeof(double));
    
    // fill first row w/ grad energy values
    for (int j = 0; j < grad->width; j++) {
        (*best_arr)[j] = get_pixel(grad, 0, j, 0);
    }
    
    // DP table (i = 1 since row 1 energy is known)
    for (int i = 1; i < grad->height; i++) {
        for (int j = 0; j < grad->width; j++) {

            double cur_energy = get_pixel(grad, i, j, 0);
            double min_energy = 0.0;

            // first column
            if (j == 0) {
                double up = (*best_arr)[(i-1) * grad->width + (j)];
                double up_right = (*best_arr)[(i-1) * grad->width + (j+1)];
                min_energy = min(up, up_right);
            }
            
            // last column
            else if (j == grad->width - 1) {
                double up = (*best_arr)[(i-1) * grad->width + (j)];
                double up_left = (*best_arr)[(i-1) * grad->width + (j-1)];
                min_energy = min(up, up_left); 
            }

            // middle columns
            else {
                double up = (*best_arr)[(i-1) * grad->width + (j)];
                double up_left = (*best_arr)[(i-1) * grad->width + (j-1)];
                double up_right = (*best_arr)[(i-1) * grad->width + (j+1)];
                min_energy = min(up, min(up_left, up_right)); // since min has only two parameters defined below
            }

            (*best_arr)[i * grad->width + j] = cur_energy + min_energy;
        }
    }
}   

void recover_path(double *best, int height, int width, int **path)
{
    *path = (int *)malloc(height * sizeof(int));

    int min_index = 0;
    double min_val = best[(height - 1) * width]; // value to compare against, constantly update if condition met (bottom row, left column)

    // check every column in bottom row to find min_val (energy)
    // DP problem: find last position/column in entire path and we work bottom to top
    for (int j = 1; j < width; j++) {
        if (best[(height - 1) * width + j] < min_val) {
            min_val = best[(height - 1) * width + j];
            min_index = j;
        }
    }

    (*path)[height - 1] = min_index; // assign last position in path array (end of seam)

    // bottom to top (know position height - 1 already)
    for (int i = height - 2; i >= 0; i--) {
        int j = (*path)[i + 1];
        
        double energy_up = best[i * width + (j)];
        double energy_up_left = INFINITY;
        double energy_up_right = INFINITY; 
        
        if (j > 0) {
            energy_up_left = best[i * width + (j-1)];
        }
        
        if (j < width - 1) {
            energy_up_right = best[i * width + (j+1)];
        }
        
        // up left
        if (energy_up_left <= energy_up && energy_up_left <= energy_up_right) {
            (*path)[i] = j - 1;
        } 
        // only up
        else if (energy_up <= energy_up_left && energy_up <= energy_up_right) {
            (*path)[i] = j;
        } 
        
        // up right
        else {
            (*path)[i] = j + 1;
        }
    }
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path)
{
    // remove one column in image (keep calling function to remove more seams)
    create_img(dest, src->height, src->width-1);
    
    for (int i = 0; i < src->height; i++) {
        int dest_j = 0;
        for (int j = 0; j < src->width; j++) {
            if (j == path[i]) { // skip column in seam (don't want to copy)
                continue;
            }
            set_pixel(*dest, i, dest_j, get_pixel(src, i, j, 0), get_pixel(src, i, j, 1), get_pixel(src, i, j, 2));
            dest_j++;
        }
    }
}

int main()
{
    struct rgb_img *im;
    struct rgb_img *grad;
    struct rgb_img *carved;
    double *best_arr;
    int *path;

    read_in_img(&im, "6x5.bin");
    calc_energy(im, &grad);  
    print_grad(grad);
    dynamic_seam(grad, &best_arr);
    
    for (int i = 0; i < grad->height; i++) {
        for (int j = 0; j < grad->width; j++) {
            printf("%.6f\t", best_arr[i * grad->width + j]);
        }
    }

    recover_path(best_arr, grad->height, grad->width, &path);
    for (int i = 0; i < grad->height; i++) {
        printf("%d\t", path[i]);
    }

    remove_seam(im, &carved, path);
    write_img(carved, "carved.bin");

    destroy_image(carved);
    free(best_arr);
    free(path);
    destroy_image(im);
    destroy_image(grad);

    return 0;
}