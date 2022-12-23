#include <stdio.h>
#include <string.h>


char arr[26][4] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", 
                    "....", "..", ".---", "-.-", ".-..", "--", "-.", 
                    "---", ".--.", "--.-", ".-.", "...", "-", "..-", 
                    "...-", ".--", "-..-", "-.--", "--.."};

int main(void) {

    while(1) {
        char mode;
        char input[40] = {0};
        char *token;
        scanf("%c %s", &mode, input);
        if (mode == 'Q') break;
        for (int i = 0; i<strlen(input); i++) {
            if (input[i] >= 97 && input[i] <= 122) {
                input[i] = input[i] - 32;
            }
        }
        if (mode == 'E') {
            strcpy(token, input);
            int i;
            for (i=0; i<strlen(token); i++) {
                printf("%s", arr[token[i]-65]);
                if (i != strlen(token)-1)
                    printf("#");
            }
            printf("\n");
        } else if (mode == 'D') {
            token = strtok(input, "#");
            while (token != NULL) {
                int i;
                for (i=0; i<26; i++) {
                    if (strcmp(arr[i], token) == 0) {
                        printf("%c", i+65);
                        break;
                    }
                }
                printf("\n");
            }
        }
    }
    
    return 0;
}
