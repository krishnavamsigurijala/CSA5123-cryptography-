#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate letter frequencies in a string
void calculateLetterFrequencies(const char *text, int *frequencies) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char c = tolower(text[i]);
            frequencies[c - 'a']++;
        }
    }
}

// Function to find the most common letter in the given frequencies array
int findMostCommonLetter(const int *frequencies) {
    int maxFreq = 0;
    int mostCommonLetter = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequencies[i] > maxFreq) {
            maxFreq = frequencies[i];
            mostCommonLetter = i;
        }
    }
    return mostCommonLetter;
}

// Function to decrypt a ciphertext using a given shift (for monoalphabetic substitution cipher)
void decryptMonoalphabetic(const char *ciphertext, int shift) {
    printf("Shift %d: ", shift);
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char c = tolower(ciphertext[i]);
            char decrypted = 'a' + ((c - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE);
            if (isupper(ciphertext[i])) {
                decrypted = toupper(decrypted);
            }
            printf("%c", decrypted);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

// Main function
int main() {
    char ciphertext[1000];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    int frequencies[ALPHABET_SIZE] = {0};
    calculateLetterFrequencies(ciphertext, frequencies);

    int mostCommonLetter = findMostCommonLetter(frequencies);
    int shift = (mostCommonLetter + ALPHABET_SIZE - ('e' - 'a')) % ALPHABET_SIZE;

    printf("Top possible plaintexts in rough order of likelihood:\n");
    for (int i = 0; i < 10; i++) {
        decryptMonoalphabetic(ciphertext, shift);
        shift = (shift + 1) % ALPHABET_SIZE;
    }

    return 0;
}

