#include <stdio.h>
#include <stdlib.h>

int mystrlen(char *string) {
    int i = 0;
    while(string[i] !='\0') {
        i++;
    }
    return i;
}

void tabsToSpaces(char *string) {
    for (int i = 0; i < mystrlen(string); i++) {
        if (string[i] == '\t') {
            string[i] = ' ';
        }
    }
}

void mymemcpy(char *Dst, char *Src, int size) {
    for (int i = 0; i < size; i++) {
        *(Dst++) = *(Src++);
    }
}

char *mystrcat(char *str1, char *str2) {
    char *sumString = NULL;
    if (str1 == NULL) {
        sumString = (char *) malloc(mystrlen(str2)+1);
        mymemcpy(sumString, str2, mystrlen(str2) + 1);
    } else {
        int len1 = mystrlen(str1);
        int len2 = mystrlen(str2);
        sumString = (char *) malloc(len1 + len2 + 1);
        mymemcpy(sumString, str1, len1);
        mymemcpy(sumString + len1, str2, len2 + 1);
    }
    return sumString;
}

char *myreadline(char *text) {
    printf("%s", text);
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = mystrlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            mymemcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

int main() {
    int n;
    printf("Enter n\n");
    scanf("%d", &n);
    char *string = myreadline("Enter string\n");
    do {
        if (string != NULL && *string != '\0') {
            char *finalString = NULL;
            int len = mystrlen(string);
            int currentWordLen = 0;
            tabsToSpaces(string);
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
                        finalString = mystrcat(finalString, appendingString);
                    }
                    currentWordLen = 0;
					free(appendingString);
                } else {
                    char *appendingString = (char *) malloc(2);
                    appendingString[0] = string[i];
                    appendingString[1] = '\0';
                    if (finalString == NULL) {
                        finalString = appendingString;
                    } else {
                        finalString = mystrcat(finalString, appendingString);
                    }
					free(appendingString);
                }
                if (string[i] != ' ') {
                    currentWordLen++;
                }
            }
            printf("%s\n", finalString);
			finalString = NULL;
			free(finalString);
        } else {
            printf("The string is empty");
        }
		free(string);
        string = myreadline("Enter string\n");
    } while (string != NULL);
    return 0;
}
