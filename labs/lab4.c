#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int my_atoi(const char *str)
{
    int i = 0;
    int sign = 1;
    if (str[i] == '-'){
        sign = -1;
        i++;
    }
    int res = 0;
    while (str[i] >= '0' && str[i] <= '9'){ // conditions would be any real number (not '\0')
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res * sign;
}

int my_atof(const char *str)
{
    int i = 0;
    int sign = 1;
    if (str[i] == '-'){
        sign = -1;
        i++;
    }
    int res = 0;
    while (str[i] != '.' && str[i] != '\0'){
        res = res * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '\0'){
        return res * sign;
    }
    i++; // otherwise advance past '.'
    double dec = 0;
    double factor = 0.1;
    while(str[i] != '\0'){
        dec = dec + (str[i] - '0') * factor;
        factor = factor / 10;
        i++;
    }
    return sign * (res + dec);
}

int skip_after_equal_sign(const char *str){
    int i = 0;
    while (str[i] != '='){
        i++;
    }
    return i + 2;
}

int sum_from_file(const char* filename){
    FILE *fp = fopen(filename, "r");
    char line[200];
    int res = 0;
    while (fgets(line, sizeof(line), fp)){
        res += my_atof(line + skip_after_equal_sign(line));
    }
    fclose(fp);
    return res;
}

