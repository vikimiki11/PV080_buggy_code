#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>
#include <stdint.h>

void print_iv(const uint8_t *iv, size_t iv_len) {
    randombytes_buf((uint8_t *)iv, iv_len);
    printf("IV: ");
    for (size_t i = 0; i < iv_len; ++i) {
        printf("%02x ", iv[i]);
    }
    printf("\n");
}

void print_plaintext(const uint8_t *plaintext, size_t pt_len) {
    printf("Plaintext: ");
    for (size_t i = 0; i < pt_len; ++i) {
        printf("%c", plaintext[i]);
    }
    printf("\n");
}

size_t recv_message(uint8_t *buf, size_t buf_len) {
    if (sodium_init() < 0) {
        fprintf(stderr, "Failed to initialize libsodium\n");
        exit(EXIT_FAILURE);
    }
    const char *msg = "\"Beware the Jabberwock, my son!\"";
    size_t msg_len = strlen(msg);
    size_t copy_len = (msg_len < buf_len - 16) ? msg_len : buf_len - 16;
    strncpy((char *)(buf + 16), msg, copy_len);
    buf[16 + copy_len] = '\0';
    return copy_len + 16;
}

int decrypt_message(const uint8_t *iv, const uint8_t *ciphertext, uint8_t *plaintext, size_t pt_len) {
    memcpy(plaintext, ciphertext, pt_len);
    (void) iv;
    return 0;
}

