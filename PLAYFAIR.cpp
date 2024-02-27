#include <stdio.h>
#include <string.h>

#define ROWS 5
#define COLS 5

// Function to decrypt Playfair encoded message
void decryptPlayfair(char *ciphertext) {
    // Define the Playfair key matrix (5x5 grid)
    char keyMatrix[ROWS][COLS] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'E', 'B', 'Z'},
        {'W', 'H', 'T', 'F', 'S'},
        {'G', 'O', 'Y', 'I', 'L'},
        {'C', 'A', 'P', 'D', 'N'}
    };

    int length = strlen(ciphertext);

    printf("Decrypted plaintext:\n");

    // Decrypt the ciphertext
    for (int i = 0; i < length; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];

        int aRow, aCol, bRow, bCol;
        int found = 0;

        // Find the positions of characters in the key matrix
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                if (keyMatrix[row][col] == a) {
                    aRow = row;
                    aCol = col;
                    found++;
                }
                if (keyMatrix[row][col] == b) {
                    bRow = row;
                    bCol = col;
                    found++;
                }
                if (found == 2) {
                    break;
                }
            }
            if (found == 2) {
                break;
            }
        }

        // Decrypt characters
        char decryptedA, decryptedB;
        if (aRow == bRow) {
            decryptedA = keyMatrix[aRow][(aCol + 4) % 5];
            decryptedB = keyMatrix[bRow][(bCol + 4) % 5];
        } else if (aCol == bCol) {
            decryptedA = keyMatrix[(aRow + 4) % 5][aCol];
            decryptedB = keyMatrix[(bRow + 4) % 5][bCol];
        } else {
            decryptedA = keyMatrix[aRow][bCol];
            decryptedB = keyMatrix[bRow][aCol];
        }

        printf("%c%c", decryptedA, decryptedB);
    }
}

int main() {
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    decryptPlayfair(ciphertext);
    printf("\n");
    return 0;
}
