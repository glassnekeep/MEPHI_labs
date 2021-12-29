#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <readline/readline.h>

typedef struct {
    char *name;
    char *station;
    int age;
} voter;
void addNewElement(int index, int len, voter *array, voter newElement) {
    //printf("\n----------------------\n");
    //printf("elen name = %s, elem station = %s, elem age = %d\n", newElement.name, newElement.station, newElement.age);
    //printf("\n----------------------\n");
    if (len == 0) {
        free(array);
        array = (voter *) malloc(sizeof(voter));
        array[0] = newElement;
    } else {
        array = (voter *) realloc(array, sizeof(voter) * (len + 1));
        for (int i = len; i > index; i--) {
            array[i] = array[i - 1];
            for (int j = 0; j < len + 1; j++) {
                //printf("name = %s, station = %s, age = %d. j = %d, n = %d\n", array[j].name, array[j].station, array[j].age, j, len);
            }
        }
        array[index] = newElement;
    }
}

void addNewElement1(int index, int len, voter *array, voter newElement) {
    array = (voter *) realloc(array, sizeof(voter) * (len + 1));
    for (int i = len; i > index; i--) {
        memcpy((char *) array + i * sizeof(voter), (char *) array + (i - 1) * sizeof(voter), sizeof(voter));
    }
    memcpy((char *) array + sizeof(voter) * index, &newElement, sizeof(newElement));
}

voter* addNewElement2(int index, int len, voter *array, voter newElement) {
    voter *newarr = (voter *) calloc((len + 1), sizeof(newElement));
    for (int i = 0; i < len + 1; i++) {
        if (i < index) {
            newarr[i] = array[i];
        }
        if (i >= index) {
            newarr[i + 1] = array[i];
        }
        if (i == index) {
            newarr[i] = newElement;
        }
    }
    return newarr;
}

void addNewElementToOrderedArray(int len, voter *array, voter newElement, int orderedFieldNumber) {
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (orderedFieldNumber == 1) {
            if (strcmp(newElement.name, array[i].name) < 0) {
                index = i;
                break;
            }
        } else if (orderedFieldNumber == 2) {
            if (strcmp(newElement.station, array[i].station) < 0) {
                index = i;
                break;
            }
        } else if (orderedFieldNumber == 3){
            if (newElement.age < array[i].age) {
                index = i;
                break;
            }
        }
    }
    addNewElement(index, len, array, newElement);
}

void deleteElementsFromIndex(int len, voter *array, int index, int numberOfElements) {
    for (int i = index; i < len - numberOfElements; i++) {
        array[i] = array[i + numberOfElements];
    }
    array = realloc(array, sizeof(voter) * len - numberOfElements);
}

int compareByName(void *value1, void *value2) {
    voter *voter1 = (voter *) value1;
    voter *voter2 = (voter *) value2;
    int result = strcmp(voter1 -> name, voter2 -> name);
    return result;
}

int compareByStation(void *value1, void *value2) {
    int result = 0;
    voter *voter1 = (voter *) value1;
    voter *voter2 = (voter *) value2;
    char *station1 = malloc(7 * sizeof(char));
    char *station2 = malloc(7 * sizeof(char));
    station1 = voter1 -> station;
    station2 = voter2 -> station;
    char *string1 = malloc(sizeof(char) * 3);
    char *string2 = malloc(sizeof(char) * 3);
    memcpy(string1, station1, sizeof(char) * 3);
    memcpy(string2, station2, sizeof(char) * 3);
    result = strcmp(string1, string2);
    if (result != 0) {
        return result;
    } else {
        char *string11 = malloc(sizeof(char) * 3);
        char *string22 = malloc(sizeof(char) * 3);
        memcpy(string11, station1 + 4 * sizeof(char), sizeof(char) * 3);
        memcpy(string22, station2 + 4 * sizeof(char), sizeof(char) * 3);
        int int1 = atoi(string11);
        int int2 = atoi(string22);
        result = int1 > int2;
        return result;
    }
}

int compareByAge(void *value1, void *value2) {
    voter *val1 = (voter *) value1;
    voter *val2 = (voter *) value2;
    int a1 = val1 -> age;
    int a2 = val2 -> age;
    return (a1 - a2);
}

void swap(char *elem1, char *elem2, int elemSize) {
    char *k = (char *) malloc(elemSize);
    memcpy(k, elem1, elemSize);
    memcpy(elem1, elem2, elemSize);
    memcpy(elem2, k, elemSize);
}

void combsort(void *array, int len, int elementSize, int (* comparator) (void *val1, void *val2)) {
    double factor = 1.247;
    int gap = (int) (len / factor);
    while (gap > 1) {
        for (int i = 0, j = gap; j < len; i++, j++) {
            if (comparator((char *) array + elementSize * i, (char *) array + elementSize * j) >= 0) {
                swap((char *) array + elementSize * i, (char *) array + elementSize * j, elementSize);
                char *elem1 = (char *) array + elementSize * i;
                printf("%s", elem1);
                char *elem2 = (char *) array + elementSize * j;
            }
        }
        gap = (int) (gap / factor);
    }
}

void combsort1(void *array, int len, int elementSize, int (* comparator) (void *val1, void *val2)) {
    double factor = 1.2473309;
    int gap = len;
    int swaps = 1;

    while ( gap > 1 || swaps ) {
        gap = (int)(gap / factor);
        if ( gap < 1 )
            gap = 1;
        swaps = 0;
        for (int i = 0; i < len - gap; ++i ) {
            int j = i + gap;
            if (comparator((char *) array + elementSize * i, (char *) array + elementSize * j) >= 0) {
                swap((char *) array + elementSize * i, (char *) array + elementSize * j, elementSize);
                char *elem1 = (char *) array + elementSize * i;
                swaps = 1;
            }
        }
    }
}

void pairInsertionSort(void *array, int len, int elementSize, int (* comparator) (void *val1, void *val2)) {
    for (int i = 0; i < len; i++) {
        for (int j = 1; j > 0 && comparator((char *) array + (j - 1) * elementSize, (char *) array + j * elementSize) > 0; j--) {
            swap ((char *) array + (j - 1) * elementSize, (char *) array + j * elementSize, elementSize);
        }
    }
}

void insertionSort(void *array, int len, int elementSize, int (* comparator) (void *val1, void *val2)) {
    char *temp = (char *) malloc(elementSize);
    for (int i = 0; i < len; i++) {
        memcpy(temp, (char *) array + elementSize * i, elementSize);
        for (int j = i - 1; j >= 0; j--) {
            if (comparator((char *) array + j * elementSize, temp) < 0) {
                break;
            }
            memcpy((char *) array + (j + 1) * elementSize, (char *) array + j * elementSize, elementSize);
            memcpy((char *) array + j * elementSize, temp, elementSize);
        }
    }
}

void selectionSort (void *array, int len, int elementSize, int (* comparator) (void *val1, void *val2)) {
    int max_index, min_index, i, j, k;
    char *max = (char *) malloc(elementSize);
    char *min = (char *) malloc(elementSize);
    k = len - 1;
    for (i = 0; i <= k; i++) {
        max = min = (char *) array + elementSize * i;
        max_index = min_index = i;
        for (j = i + 1; j <= k; j++) {
            char *compare = (char *) array + elementSize * j;
            if (comparator(compare, max) > 0) {
                memcpy(max, compare, elementSize);
                max_index = j;
            }
            if (comparator(compare, min) < 0) {
                memcpy(min, compare, elementSize);
                min_index = j;
            }
        }
        char *arri = (char *) array + elementSize * i;
        char *arrk = (char *) array + elementSize * k;
        char *arrmax = (char *) array + elementSize * max_index;
        char *arrmin = (char *) array + elementSize * min_index;
        if (max_index == i && min_index != k) {
            swap(arrk, arrmax, elementSize);
            swap(arri, arrmin, elementSize);
        }
        if (min_index == k && max_index != i) {
            swap (arri, arrmin, elementSize);
            swap (arrk, arrmax, elementSize);
        }
        if (min_index == k && max_index == i) {
            swap (arrk, arri, elementSize);
        }
        if (min_index != k && max_index != i) {
            swap (arrk, arrmax, elementSize);
            swap (arri, arrmin, elementSize);
        }
        k--;
    }
}

void selectionSort1 (void *array, int len, int elementSize, int (* comparator) (void*, void *)) {
    int max_index, min_index, num = len - 1;
    char *max = NULL;
    char *min = NULL;
    for (int i = 0; i <= num; i++) {
        max = realloc(max, elementSize);
        min = realloc(min, elementSize);
        memcpy(max, array + i * elementSize, elementSize);
        memcpy(min, array + i * elementSize, elementSize);
        max_index = i;
        min_index = i;
        for (int j = i + 1; j <= num; j++) {
            if (comparator((char *)array + j * elementSize, max) > 0) {
                memcpy(max, (char *)array + j * elementSize, elementSize);
                max_index = j;
            }
            if (comparator((char *)array + j * elementSize, min) < 0) {
                memcpy(min, (char *)array + j * elementSize, elementSize);
                min_index = j;
            }
        }
        if (max_index == i && min_index != num) {
            swap((char *)array + num * elementSize, (char *)array + max_index * elementSize, elementSize);
            swap((char *)array + i * elementSize, (char *)array + min_index * elementSize, elementSize);
        }
        if (min_index == num && max_index != i) {
            swap((char *)array + i * elementSize, (char *)array + min_index * elementSize, elementSize);
            swap((char *)array + num * elementSize, (char *)array + max_index * elementSize, elementSize);
        }
        if (min_index == num && max_index == i) {
            swap((char *)array + num * elementSize, (char *)array + i * elementSize, elementSize);
        }
        if (min_index != num && max_index != i) {
            swap ((char *)array + num * elementSize, (char *)array + max_index * elementSize, elementSize);
            swap ((char *)array + i * elementSize, (char *)array + min_index * elementSize, elementSize);
        }
        num--;
    }
    free(max);
    free(min);
}

void clearScreen() {
    system("clear");
    fflush(stdout);
}

void menu() {
    int choice;
    voter *array = NULL;
    int n = 0;
    int orderedNumber = 0;
    do {
        //TODO возможно стоит сделать так, чтобы пока не введен определенный символ, будет в while цикле гоняться это все
        printf("1. Enter matrix\n2. Export matrix\n3. Edit matrix\n4. Exit\n");
        while (scanf("%d", &choice) != 1 || ((int) choice > 4) || (int) choice < 1) {
            printf("Error. Enter correct number\n");
            getchar();
        }
        switch (choice) {
            int choice1;
            case 1:
                //clearScreen();
                printf("1. Read from keyboard\n2. Read from text file\n3. Random generation\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 3) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                switch (choice1) {
                    case 1:
                        printf("Enter number of elements in the array\n");
                        while (scanf("%d", &n) != 1 || (n <= 0)) {
                            printf("Error. Enter correct number\n");
                            getchar();
                        }
                        if (array != NULL) {
                            free(array);
                        }
                        array = (voter *) malloc(sizeof(voter) * n);
                        for (int i = 0; i < n; i++) {
                            char *name;
                            char *station;
                            int age;
                            name = readline("Enter name\n");
                            do {
                                station = readline("Enter station, the format is XXX-YYY, X - letter, Y - digit\n");
                            } while (strlen(station) != 7 || !(station[0] >= 'A' && station[0] <= 'z') ||
                            !(station[1] >= 'A' && station[1] <= 'z') ||
                            !(station[2] >= 'A' && station[2] <= 'z') ||
                            !(station[3] == '-') || !(station[4] >= '0' && station[4] <= '9') ||
                            !(station[5] >= '0' && station[5] <= '9') ||
                            !(station[6] >= '0' && station[6] <= '9'));
                            printf("Enter age\n");
                            while (scanf("%d", &age) != 1 || (age <= 0)) {
                                printf("Error. Enter correct age\n");
                                getchar();
                            }
                            voter element = {
                                    name, station, age
                            };
                            array[i] = element;
                            //addNewElement(0, n, array, element);
                        }
                        //сформировали массив структур voter
                        break;
                        case 2:
                            printf("");
                            int correct = 1;
                            do {
                                correct = 1;
                                char *filename = readline("Enter file name\n");
                                printf("filename = %s\n", filename);
                                FILE *file;
                                file = fopen(filename, "r");
                                if (fscanf(file, "%d", &n) != 1) {
                                    correct = 0;
                                    printf(0);
                                } else {
                                    if (array != NULL) {
                                        free(array);
                                    }
                                    //printf("%d\n", n);
                                    array = (voter *) malloc(sizeof(voter) * n);
                                    for (int i = 0; i < n; i++) {
                                        char *name = malloc(sizeof(char) * 40);
                                        char *station = malloc(sizeof(char) * 8);
                                        int age;
                                        if (fscanf(file, "%s\n", name) != 1) {
                                            correct = 0;
                                            printf("Error name, name = %s\n", name);
                                            break;
                                        }
                                        if (fscanf(file, "%s\n", station) != 1) {
                                            correct = 0;
                                            printf("error station");
                                            break;
                                        } else {
                                            if (strlen(station) == 7 &&
                                            station[0] >= 'A' && station[0] <= 'z' &&
                                            station[1] >= 'A' && station[1] <= 'z' &&
                                            station[2] >= 'A' && station[2] <= 'z' &&
                                            station[3] == '-' && station[4] >= '0' && station[4] <= '9' &&
                                            station[5] >= '0' && station[5] <= '9' && station[6] >= '0' &&
                                            station[6] <= '9') {
                                            } else {
                                                correct = 0;
                                                printf("incorrect\n");
                                                break;
                                            }
                                        }
                                        if (fscanf(file, "%d", &age) != 1) {
                                            correct = 0;
                                            break;
                                        }
                                        voter element = {
                                                .name = name,
                                                .station = station,
                                                .age = age
                                        };
                                        array[i] = element;
                                        //addNewElement(0, n, array, element);
                                    }
                                }
                            } while (correct != 1);
                            break;
                            case 3:
                                srand(time(NULL));
                                n = rand() % 5;
                                if (array != NULL) {
                                    free(array);
                                }
                                array = (voter *) malloc(sizeof(voter) * n);
                                for (int i = 0; i < n; i++) {
                                    char *name;
                                    char *station;
                                    int nameSize = rand() % 20;
                                    name = (char *) malloc(sizeof(char) * (nameSize + 1));
                                    station = (char *) malloc(sizeof(char) * 8);
                                    for (int j = 0; j < nameSize; j++) {
                                        name[j] = (char) ('a' + rand() % 26);
                                    }
                                    name[nameSize] = '\0';
                                    station[0] = 'A' + rand() % 26;
                                    station[1] = 'A' + rand() % 26;
                                    station[2] = 'A' + rand() % 26;
                                    station[3] = '-';
                                    station[4] = '0' + rand() % 10;
                                    station[5] = '0' + rand() % 10;
                                    station[6] = '0' + rand() % 10;
                                    station[7] = '\0';
                                    int age = rand() % 100;
                                    voter element = {
                                            .name = name,
                                            .station = station,
                                            .age = age
                                    };
                                    array[i] = element;
                                    //printf("Case 3name = %s, station = %s, age = %d, i = %d\n", array[i].name, array[i].station, array[i].age, i);
                                }
                                break;
                }
                orderedNumber = 0;
                break;
                case 2:
                    printf("1. Write the array into the console\n2. Write array to file\n");
                    while (scanf("%d", &choice1) != 1 || ((int) choice1 > 2) || (int) choice1 < 1) {
                        printf("Error. Enter correct number\n");
                        getchar();
                    }
                    switch (choice1) {
                        case 1:
                            printf("n = %d\n", n);
                            for (int i = 0; i < n; i++) {
                                //printf("array size = %d, sizeof struct = %d\n", (int) sizeof(array), (int) sizeof(voter *));
                                printf("name = %s, station = %s, age = %d. i = %d, n = %d\n", array[i].name, array[i].station, array[i].age, i, n);
                            }
                            break;
                            case 2:
                                printf("");
                                char *filename = readline("Enter file name\n");
                                printf("filename = %s\n", filename);
                                FILE *file;
                                file = fopen(filename, "w");
                                for (int i = 0; i < n; i++) {
                                    fprintf(file, "name = %s, station = %s, age = %d\n", array[i].name, array[i].station, array[i].age);
                                }
                                break;
                    }
                    break;
                    case 3:
                        printf("1. Insert element by index\n2. Insert element by index to ordered array\n3. Delete elements from index\n4. Sort array\n");
                        while (scanf("%d", &choice1) != 1 || ((int) choice1 > 4) || (int) choice1 < 1) {
                            printf("Error. Enter correct number\n");
                            getchar();
                        }
                        switch (choice1) {
                            case 1:
                                printf("");
                                int index;
                                printf("Enter index\n");
                                while (scanf("%d", &index) != 1 || ((int) index > n - 1) || (int) index < 0) {
                                    printf("Error. Enter correct index\n");
                                    getchar();
                                }
                                /*int age;
                                char *name = readline("Enter name\n");
                                char *station;
                                do {
                                    station = readline("Enter station, the format is XXX-YYY, X - letter, Y - digit\n");
                                } while (strlen(station) != 7 || !(station[0] >= 'A' && station[0] <= 'z') ||
                                !(station[1] >= 'A' && station[1] <= 'z') ||
                                !(station[2] >= 'A' && station[2] <= 'z') ||
                                !(station[3] == '-') || !(station[4] >= '0' && station[4] <= '9') ||
                                !(station[5] >= '0' && station[5] <= '9') ||
                                !(station[6] >= '0' && station[6] <= '9'));
                                printf("Enter age\n");
                                while (scanf("%d", &age) != 1 || (age <= 0)) {
                                    printf("Error. Enter correct age\n");
                                    getchar();
                                }
                                //printf("sizeof name = %d sizeof station = %d, sizeof age = %d\n", (int) sizeof(name), (int) sizeof(station), (int) sizeof(age));
                                voter element = {
                                        .name = name,
                                        .station = station,
                                        .age = age
                                };*/
                                voter element;
                                element.name = readline("Enter name\n");
                                element.station = readline("Enter station\n");
                                element.age = atoi(readline("Enter age\n"));
                                //printf("sizeof array[0] = %d, sizeof elem = %d", (int) sizeof(array[0]), (int) sizeof(element));
                                for (int i = 0; i < n; i++) {
                                    //printf("array size = %d, sizeof struct = %d\n", (int) sizeof(array), (int) sizeof(voter *));
                                    //printf("name = %s, station = %s, age = %d. i = %d, n = %d\n", array[i].name, array[i].station, array[i].age, i, n);
                                }
                                array = realloc(array, (n + 1) * sizeof(element));
                                addNewElement(index, n, array, element);
                                n++;
                                for (int i = 0; i < n; i++) {
                                    //printf("array size = %d, sizeof struct = %d\n", (int) sizeof(array), (int) sizeof(voter *));
                                    //printf("name = %s, station = %s, age = %d. i = %d, n = %d\n", array[i].name, array[i].station, array[i].age, i, n);
                                }
                                break;
                                case 2:
                                    if (orderedNumber != 0) {
                                        /*char *name1;
                                        char *station1;
                                        int age1;
                                        name1 = readline("Enter name\n");
                                        do {
                                            station1 = readline("Enter station, the format is XXX-YYY, X - letter, Y - digit\n");
                                        } while (strlen(station1) != 7 || !(station1[0] >= 'A' && station1[0] <= 'z') ||
                                        !(station1[1] >= 'A' && station1[1] <= 'z') ||
                                        !(station1[2] >= 'A' && station1[2] <= 'z') ||
                                        !(station1[3] == '-') || !(station1[4] >= '0' && station1[4] <= '9') ||
                                        !(station1[5] >= '0' && station1[5] <= '9') ||
                                        !(station1[6] >= '0' && station1[6] <= '9'));
                                        printf("Enter age\n");
                                        while (scanf("%d", &age1) != 1 || (age1 <= 0)) {
                                            printf("Error. Enter correct age\n");
                                            getchar();
                                        }
                                        voter element1;
                                        element1.name = name1;
                                        element1.station = station1;
                                        element1.age = age1;*/
                                        voter element1;
                                        element1.name = readline("Enter name\n");
                                        element1.station = readline("Enter station\n");
                                        element1.age = atoi(readline("Enter age\n"));
                                        //printf("sizeof array[0] = %d, sizeof elem = %d", (int) sizeof(array[0]), (int) sizeof(element));
                                        for (int i = 0; i < n; i++) {
                                            //printf("array size = %d, sizeof struct = %d\n", (int) sizeof(array), (int) sizeof(voter *));
                                            //printf("name = %s, station = %s, age = %d. i = %d, n = %d\n", array[i].name, array[i].station, array[i].age, i, n);
                                        }
                                        array = realloc(array, (n + 1) * sizeof(element1));
                                        addNewElementToOrderedArray(n, array, element1, orderedNumber);
                                        n++;
                                    } else {
                                        printf("The array is not ordered\n");
                                    }
                                    break;
                                    case 3:
                                        printf("");
                                        int index1;
                                        int number;
                                        printf("Enter index\n");
                                        while (scanf("%d", &index1) != 1 || ((int) index1 > n - 1) || (int) index1 < 0) {
                                            printf("Error. Enter correct index\n");
                                            getchar();
                                        }
                                        printf("Enter number of elements\n");
                                        while (scanf("%d", &number) != 1 || ((int) number + index1 > n - 1) || (int) number < 0) {
                                            printf("Error. Enter correct number of elements\n");
                                            getchar();
                                        }
                                        deleteElementsFromIndex(n, array, index1, number);
                                        n -= number;
                                        break;
                                        case 4:
                                            printf("1. Compare by name\n2. Compare by station\n3. Compare by age\n");
                                            int choice2;
                                            int comparatorNum;
                                            while (scanf("%d", &comparatorNum) != 1 || ((int) comparatorNum > 3) || (int) comparatorNum < 1) {
                                                printf("Error. Enter correct comparator\n");
                                                getchar();
                                            }
                                            printf("1. Comb sort\n2. Insertion sort\n3. Double-selection sort\n");
                                            while (scanf("%d", &choice2) != 1 || ((int) choice2 > 3) || (int) choice2 < 1) {
                                                printf("Error. Enter correct number\n");
                                                getchar();
                                            }
                                            switch (choice2) {
                                                case 1:
                                                    if (comparatorNum == 1) {
                                                        combsort1(array, n, sizeof(voter), compareByName);
                                                    } else if (comparatorNum == 2) {
                                                        combsort1(array, n, sizeof(voter), compareByStation);
                                                    } else if (comparatorNum == 3){
                                                        combsort1(array, n, sizeof(voter), compareByAge);
                                                    } else {
                                                        printf("Error\n");
                                                    }
                                                    orderedNumber = 1;
                                                    break;
                                                    case 2:
                                                        if (comparatorNum == 1) {
                                                            insertionSort(array, n, sizeof(voter), compareByName);
                                                        } else if (comparatorNum == 2) {
                                                            insertionSort(array, n, sizeof(voter), compareByStation);
                                                        } else if (comparatorNum == 3){
                                                            insertionSort(array, n, sizeof(voter), compareByAge);
                                                        } else {
                                                            printf("Error\n");
                                                        }
                                                        orderedNumber = 2;
                                                        break;
                                                        case 3:
                                                            if (comparatorNum == 1) {
                                                                selectionSort1(array, n, sizeof(voter), compareByName);
                                                            } else if (comparatorNum == 2) {
                                                                selectionSort1(array, n, sizeof(voter), compareByStation);
                                                            } else if (comparatorNum == 3) {
                                                                selectionSort1(array, n, sizeof(voter), compareByAge);
                                                            } else {
                                                                printf("Error\n");
                                                            }
                                                            orderedNumber = 3;
                                                            break;
                                            }
                                            break;
                        }
                        break;
                        default:
                            exit(0);
                            break;
        }
    } while (choice != 4);
    free(array);
}
int main() {
    /*voter *array = malloc(sizeof(voter));
    printf("%d\n", sizeof(voter));
    int len = 0;
    voter voter1 = {
            "Kirill", "xxx-yyy", 15
    };
    voter voter2 = {
            "Andrey", "axx-yyy", 16
    };
    voter voter3 = {
            "George", "bxx-yyy", 20
    };
    voter voter4 = {
            "Artemiy", "gxx-yyy", 30
    };
    voter voter5 = {
            "Vasiliy", "nxx-yyy", 20
    };
    voter voter6 = {
            "Gleb", "6xx-yyy", 13
    };
    addNewElement(0, len, array, voter1);
    len++;
    addNewElement(0, len, array, voter2);
    len++;
    addNewElement(0, len, array, voter3);
    len++;
    addNewElement(0, len, array, voter4);
    len++;
    for (int i = 0; i < len; i++) {
        printf("name = %s, station = %s, age = %d\n", array[i].name, array[i].station, array[i].age);
    }
    insertionSort(array, len, sizeof(voter), compareByName);
    printf("\nSorted array \n--------------------------------------\n");
    for (int i = 0; i < len; i++) {
        printf("name = %s, station = %s, age = %d\n", array[i].name, array[i].station, array[i].age);
    }*/
    menu();
    return 0;
}
