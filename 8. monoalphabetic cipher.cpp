#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ROWS 5
#define COLS 5

// Function to preprocess the plaintext message
void preprocessMessage(char *message) {
    int len = strlen(message);
    int j_index;

    // Remove spaces from the message
    for (int i = 0; i < len; i++) {
        if (message[i] == ' ') {
            for (int j = i; j < len; j++) {
                message[j] = message[j + 1];
            }
            len--;
        }
    }

    // Replace 'J' with 'I'
    for (int i = 0; i < len; i++) {
        if (message[i] == 'J')
            message[i] = 'I';
    }
}

// Function to find the row and column of a character in the Playfair matrix
void findPosition(char keyMatrix[ROWS][COLS], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt plaintext using Playfair cipher
void encryptPlayfair(char *plaintext, char keyMatrix[ROWS][COLS]) {
    // Preprocess the plaintext message
    preprocessMessage(plaintext);

    // Encrypt the message
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = (i + 1 < len) ? plaintext[i + 1] : 'X'; // If odd number of characters, pad with 'X'

        int aRow, aCol, bRow, bCol;
        findPosition(keyMatrix, a, &aRow, &aCol);
        findPosition(keyMatrix, b, &bRow, &bCol);

        if (aRow == bRow) {
            // Same row
            printf("%c%c", keyMatrix[aRow][(aCol + 1) % COLS], keyMatrix[bRow][(bCol + 1) % COLS]);
        } else if (aCol == bCol) {
            // Same column
            printf("%c%c", keyMatrix[(aRow + 1) % ROWS][aCol], keyMatrix[(bRow + 1) % ROWS][bCol]);
        } else {
            // Rectangle case
            printf("%c%c", keyMatrix[aRow][bCol], keyMatrix[bRow][aCol]);
        }
    }
}

int main() {
    // Define the Playfair key matrix
    char keyMatrix[ROWS][COLS] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    // Define the plaintext message
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";

    // Encrypt the plaintext using the Playfair matrix
    printf("Encrypted message:\n");
    encryptPlayfair(plaintext, keyMatrix);
    printf("\n");

    return 0;
}
