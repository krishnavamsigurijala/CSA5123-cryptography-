#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to encrypt the message using the Hill cipher
void encrypt(char message[], int key[][2]) {
    int len = strlen(message);
    int i, j, k;
    int plaintext[len];
    int ciphertext[len];

    // Convert message characters to corresponding numerical values
    for (i = 0; i < len; i++) {
        if (message[i] == ' ') // Ignore spaces
            continue;
        plaintext[i] = message[i] - 'a'; // Assuming lowercase alphabets
    }

    // Encrypt the message using the key matrix
    for (i = 0; i < len; i += 2) {
        ciphertext[i] = (key[0][0] * plaintext[i] + key[0][1] * plaintext[i + 1]) % 26;
        ciphertext[i + 1] = (key[1][0] * plaintext[i] + key[1][1] * plaintext[i + 1]) % 26;
    }

    // Print the encrypted message
    printf("Encrypted message: ");
    for (i = 0; i < len; i++) {
        if (message[i] == ' ') {
            printf(" ");
            continue;
        }
        printf("%c", ciphertext[i] + 'a');
    }
    printf("\n");
}

int main() {
    // Define the key matrix
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    // Message to be encrypted
    char message[] = "meet me at the usual place at ten rather than eight oclock";

    // Encrypt the message using the Hill cipher
    encrypt(message, key);

    return 0;
}

