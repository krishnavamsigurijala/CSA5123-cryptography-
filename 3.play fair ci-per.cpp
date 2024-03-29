#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 5

void prepareMessage(char *message) {
    int len = strlen(message);
    int i, j;

    for (i = 0; i < len; i++) {
        message[i] = toupper(message[i]);
        if (message[i] == 'J')
            message[i] = 'I';
    }
}

void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int i, j, k, flag = 0;
    int *dicty = (int *)calloc(26, sizeof(int));

    for (i = 0; i < strlen(key); i++) {
        if (key[i] != ' ' && dicty[key[i] - 65] != 1) {
            keyTable[flag / SIZE][flag % SIZE] = key[i];
            dicty[key[i] - 65] = 1;
            flag++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (dicty[i] == 0) {
            keyTable[flag / SIZE][flag % SIZE] = (char)(i + 65);
            dicty[i] = 1;
            flag++;
        }
    }

    free(dicty);
}

void search(char keyTable[SIZE][SIZE], char a, char b, int arr[]) {
    int i, j;

    if (a == 'J')
        a = 'I';
    else if (b == 'J')
        b = 'I';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            } else if (keyTable[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

void encrypt(char message[], char keyTable[SIZE][SIZE]) {
    int i, a[4];

    for (i = 0; i < strlen(message); i += 2) {
        search(keyTable, message[i], message[i + 1], a);

        if (a[0] == a[2]) {
            message[i] = keyTable[a[0]][(a[1] + 1) % SIZE];
            message[i + 1] = keyTable[a[0]][(a[3] + 1) % SIZE];
        } else if (a[1] == a[3]) {
            message[i] = keyTable[(a[0] + 1) % SIZE][a[1]];
            message[i + 1] = keyTable[(a[2] + 1) % SIZE][a[1]];
        } else {
            message[i] = keyTable[a[0]][a[3]];
            message[i + 1] = keyTable[a[2]][a[1]];
        }
    }
}

int main() {
    char key[100], keyTable[SIZE][SIZE], message[100];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    prepareMessage(key);
    prepareMessage(message);

    generateKeyTable(key, keyTable);

    encrypt(message, keyTable);

    printf("Encrypted message: %s\n", message);

    return 0;
}
