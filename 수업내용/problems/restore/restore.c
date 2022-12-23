#include <stdio.h>
#include <string.h>

#define MAX_STRING 300 // 15 * 20

int num_of_substrings;
char substring[15][20];
int overlapped[15][15];

#define MIN(a,b) (((a)<(b))?(a):(b))

int overlap(char str1[], char str2[])
{
    if (strstr(str1, str2) != NULL) {
        return -1;
    }

    int str1_length = strlen(str1);
    int str2_length = strlen(str2);

    int max_length = MIN(str1_length, str2_length);

    int idx, max = 0;
    for (idx=1; idx <= max_length; idx++) {
        char *tmp = &str1[str1_length-idx];

        if (strncmp(tmp, str2, idx) == 0) {
            max = idx;
        }
    }

    return max;
}

char* find_shortest_string(char base_string[], int current_index, int selected[])
{
    int idx, max_value = -1, next_index = -1, count = 0;

    for (idx=0; idx<num_of_substrings; idx++) {
        if (selected[idx]) {
            count++;
            continue;
        }

        if (overlapped[current_index][idx] == -1) {
            selected[idx] = 1;
        }

        if (max_value <= overlapped[current_index][idx]) {
            max_value = overlapped[current_index][idx];
            next_index = idx;
        }
    }

    if (count == num_of_substrings) {
        return base_string;
    }

    strcat(base_string, substring[next_index] + overlapped[current_index][next_index]);
    selected[next_index] = 1;

    return find_shortest_string(base_string, next_index, selected);
}

int main()
{
    int num_of_cases = 0;

    scanf("%d", &num_of_cases);

    if (num_of_cases < 1 || num_of_cases > 50) {
        return -1;
    }

    int i, j, k;
    for (i=0; i<num_of_cases; i++) {
        scanf("%d", &num_of_substrings);

        // == //

        memset(substring, 0, sizeof(char)*15*20);

        for (j=0; j<num_of_substrings; j++) {
            scanf("%s", substring[j]);
        }

        // == //

        memset(overlapped, 0, sizeof(int)*15*15);

        for (j=0; j<num_of_substrings; j++) {
            for (k=0; k<num_of_substrings; k++) {
                if (j == k) {
                    continue;
                }
                overlapped[j][k] = overlap(substring[j], substring[k]);
            }
        }

        // == //

        int shortest_length = 300;
        char final_result[MAX_STRING] = {0};

        for (j=0; j<num_of_substrings; j++) {
            char temp[MAX_STRING] = {0};
            int selected[15] = {0};

            strcpy(temp, substring[j]);
            selected[j] = 1;

            find_shortest_string(temp, j, selected);

            if (shortest_length > strlen(temp)) {
                shortest_length = strlen(temp);
                strcpy(final_result, temp);
            }
        }

        // == //

        printf("%s\n", final_result);
    }

    return 0;
}
