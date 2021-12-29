#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

void removeTabs(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == '\t') {
            str[i] = ' ';
        }
    }
}

int main() {
    int n;
    printf("Enter n\n");
	printf("n = %d", n);
    do {
		scanf("%d", n);
		if(n == 0) {
			printf("Enter correct n");
			scanf("%d", n);
		}
	} while (n == 0);
	printf("n = %d", n);
    char *string = readline("Enter string\n");
    do {
        if (string != NULL && *string != '\0') {
            char *finalString = NULL;
            int len = strlen(string);
            removeTabs(string);
            int currentWordLen = 0;
            for (int i = 0; i < len; i++) {
                if (string[i] == ' ') {
                    currentWordLen = 0;
                }
                if (currentWordLen == n) {
                    char *appendingString = (char *) malloc(3);
                    appendingString[0] = ' ';
                    appendingString[1] = string[i];
                    appendingString[2] = '\0';
                    if (finalString == NULL) {
                        finalString = appendingString;
                    } else {
                        finalString = strcat(finalString, appendingString);
                    }
                    currentWordLen = 0;
                } else {
                    char *appendingString = (char *) malloc(2);
                    appendingString[0] = string[i];
                    appendingString[1] = '\0';
                    if (finalString == NULL) {
                        finalString = appendingString;
                    } else {
                        finalString = strcat(finalString, appendingString);
                    }
                }
                if (string[i] != ' ') {
                    currentWordLen++;
                }
            }
            printf("%s\n", finalString);
        } else {
            printf("The string is empty");
        }
        string = readline("Enter string\n");
    } while (string != NULL);
    return 0;
}
