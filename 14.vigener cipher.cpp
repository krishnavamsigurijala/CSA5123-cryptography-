#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to encrypt a single character using Vigenère cipher
char encryptChar(char ch, int key) {
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';
        return ((ch - base + key) % ALPHABET_SIZE) + base;
    }
    return ch;
}

int main() {
    char plaintext[1000];
    int keyLength;
    
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    printf("Enter key length: ");
    scanf("%d", &keyLength);
    
    int *key = (int*)malloc(keyLength * sizeof(int));
    if (key == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    printf("Enter key (space-separated integers between 0 and 26): ");
    for (int i = 0; i < keyLength; ++i) {
        scanf("%d", &key[i]);
    }
    
    // Encrypting the plaintext using the provided key
    printf("Encrypted text: ");
    int keyIndex = 0;
    for (int i = 0; plaintext[i] != '\0'; ++i) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            printf("%c", encryptChar(ch, key[keyIndex]));
            keyIndex = (keyIndex + 1) % keyLength; // Move to the next key
        } else {
            printf("%c", ch);
        }
    }
    
    free(key);
    return 0;
}

