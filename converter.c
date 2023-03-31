#include <stdio.h>
#include <string.h>

// find label at start of a line and if the line where the label is found is smaller than line,
// return 0, return 1 if label is found after line
// return -1 if no label is found
int forward_or_backward_jump(int line, char * label) {
    printf("To find on line %d \n", line);
    FILE *fp;
    char buffer[1024];
    int line_number = 0;

    fp = fopen("test.ll", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    while (fgets(buffer, 1024, fp)) {
        line_number++;
        if (strncmp(label, buffer, strlen(label)) == 0) {
            if (line < line_number) {
                printf("Label found on line: %d \n", line_number);
                return 1;
            }
            else {
                printf("Label found on line: %d \n", line_number);
                return 0;
            }

        }

    }
    return -1;

}

char *split(char *str, const char *delim)
{
    char *p = strstr(str, delim);

    if (p == NULL) return NULL;     // delimiter not found

    *p = '\0';                      // terminate string after head
    return p + strlen(delim);       // return tail substring
}

int main() {
    FILE *fp;
    char buffer[1024];
    int line_number = 0;

    fp = fopen("test.ll", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    while (fgets(buffer, 1024, fp)) {
        line_number++;
        if (strstr(buffer, "br") != NULL) {
            printf("Line %d %s", line_number, buffer);

            char *tail;

            tail = split(buffer, "label ");

            if (tail) {
                tail[strlen(tail)-1] = 0;
                tail++;
                char * second_tail;
                second_tail = split(tail, ", label");
                if (second_tail) {
                    second_tail+=2;
                    int fbtail = forward_or_backward_jump(line_number, tail);
                    int fbsecondtail = forward_or_backward_jump(line_number, second_tail);
                    printf("tail: '%s'\n", tail);
                    printf("%d \n", fbtail);
                    
                    
                    printf("second_tail: '%s'\n", second_tail);
                    printf("%d \n", fbsecondtail);
                }
                else {
                    printf("tail: '%s'\n", tail);
                    int fbtail = forward_or_backward_jump(line_number, tail);
                    printf("%d \n", fbtail);
                }

            }

        }
    }

    fclose(fp);
    return 0;
}
