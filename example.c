#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

/*
 * 1. Receive a message
 * 2. Split it into IV and ciphertext
 * 3. Decrypt the message
 * 4. Print the IV and the plaintext
 */
int main(void) {
    uint8_t message[48];
    uint8_t iv[16];
    uint8_t ciphertext[32];
    uint8_t plaintext[32];
    size_t msg_len;

    // iv || ciphertext
    msg_len = recv_message(message, sizeof(message));
    if (msg_len != sizeof(message)) {
        fprintf(stderr, "Error: expected 48‑byte message, got %zu\n", msg_len);
        return EXIT_FAILURE;
    }

    memcpy(iv, message, sizeof(iv));
    memcpy(ciphertext, message + sizeof(iv), sizeof(ciphertext));

    decrypt_message(iv, ciphertext, plaintext, sizeof(plaintext));

    print_iv(iv, sizeof(iv));
    print_plaintext(plaintext, sizeof(plaintext));

    return EXIT_SUCCESS;
}


