// want: person with the highest average
// want: code that's short and easy to write

// if I know the highest average, need to just go through each student and find the student with that average

// want: a function that computes the averae for a particular student

// want: a way to go through all the students

// go through every file, for each student encountered
// every time, compute the average, and keep track of the max

// go through every file again, find the student whose average is the max_average

double find_average(char *files[], int num_files, char *student){
    double sum = 0;
    int num_courses = 0;

    int i;
    char line[100];
    char cur_student[100];
    for (i = 0; i < num_files; i++){
        FILE *fp = fopen(files[i], "r");
        while (fgets(line, 100, fp) != NULL){
            strncpy(cur_student, line, 10); // cur_student 
                                            // is the current student
            if(strcmp(cur_student, student) == 0){
                int grade;
                atoi(line + 11, &grade);
                sum += grade;
                num_courses++;
            }
        }
    }
    return sum / num_courses;
}

char *find_max_average_student(char *files[], int num_files)
{

    int i;
    char line[100];
    char cur_student[100];
    double cur_max_average = 0;
    char *max_student = malloc(sizeof(char)*11);
    for (i = 0; i < num_files; i++){
        FILE *fp = fopen(files[i], "r");
        while (fgets(line, 100, fp) != NULL){
            strncpy(cur_student, line, 10); // cur_student 
                                            // is the current student
        }
            double cur_average = find_average(files, num_files, cur_student);
            if (cur_average > cur_max_average){
                cur_max_average = cur_average;
                strcpy(max_student, cur_student);
            }
        }
    return max_student;
}

int main(){
    char *files[] = {"civ.txt", "esc180.txt"};
    char *best_student = find_max_average_student(files, 2);
    printf("The student with the highest average is %s\n", best_student);
    free(best_student);
    return 0;
}

