#include <stdio.h>
#include <stdint.h>

#define AES_BLOCK_SIZE 16

// Perform CBC-MAC
void cbc_mac(const uint8_t *key, const uint8_t *message, size_t message_len, uint8_t *mac) {
    uint8_t last_block[AES_BLOCK_SIZE]; // Last block processed

    // Initialize last block to zero
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        last_block[i] = 0;
    }

    // Process each block of the message using XOR
    for (size_t i = 0; i < message_len; i += AES_BLOCK_SIZE) {
        for (int j = 0; j < AES_BLOCK_SIZE; ++j) {
            last_block[j] ^= message[i + j];
        }
    }

    // Copy the last block as the MAC
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        mac[i] = last_block[i];
    }
}

int main() {
    // Example one-block message and key
    uint8_t key[AES_BLOCK_SIZE] = {'K', 'E', 'Y', '1', '2', '3', '4', '5', '6', '7', '8', '9', '1', '0', '1', '1'};
    uint8_t message[AES_BLOCK_SIZE] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o'};
    size_t message_len = AES_BLOCK_SIZE; // Length of the message

    uint8_t mac[AES_BLOCK_SIZE]; // MAC buffer

    // Compute the MAC
    cbc_mac(key, message, message_len, mac);

    // Print the MAC
    printf("CBC-MAC: ");
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}

