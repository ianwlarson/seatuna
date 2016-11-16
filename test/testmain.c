#include <stdio.h>
#include <stdlib.h>

#include "portable_sha256.h"
#include "portable_chacha20.h"

#include "seatuna.h"


bool sha_tests();
bool chacha20_tests();
bool seatuna_tests();


int main(int argc, char **argv)
{
    sha_tests();
    chacha20_tests();
    seatuna_tests();

    return 0;
}

bool sha_tests()
{
    uint8_t test01[3] = {0x61, 0x62, 0x63};
    sha256_ctx *ctxt = malloc(sizeof(*ctxt));
    sha256_init(ctxt);
    sha256_update(test01, sizeof(test01), ctxt);
    uint8_t dig01[32];
    sha256_final(dig01, ctxt);
    free(ctxt);

    for (size_t i = 0; i < 32; ++i) {
        printf("%02x", dig01[i]);
    }
    printf("\n\n");

    return true;
}

bool chacha20_tests()
{
    uint8_t key[32] = {0};
    key[31] = 0x01;
    uint8_t nonce[12] = {0};
    nonce[11] = 0x02;

    uint32_t counter = 1;

    uint8_t cipher[375];

    char *plaintext_hex =
        "416e79207375626d697373696f6e2074"
        "6f20746865204945544620696e74656e"
        "6465642062792074686520436f6e7472"
        "696275746f7220666f72207075626c69"
        "636174696f6e20617320616c6c206f72"
        "2070617274206f6620616e2049455446"
        "20496e7465726e65742d447261667420"
        "6f722052464320616e6420616e792073"
        "746174656d656e74206d616465207769"
        "7468696e2074686520636f6e74657874"
        "206f6620616e20494554462061637469"
        "7669747920697320636f6e7369646572"
        "656420616e20224945544620436f6e74"
        "7269627574696f6e222e205375636820"
        "73746174656d656e747320696e636c75"
        "6465206f72616c2073746174656d656e"
        "747320696e2049455446207365737369"
        "6f6e732c2061732077656c6c20617320"
        "7772697474656e20616e6420656c6563"
        "74726f6e696320636f6d6d756e696361"
        "74696f6e73206d61646520617420616e"
        "792074696d65206f7220706c6163652c"
        "20776869636820617265206164647265"
        "7373656420746f";

    uint8_t plaintext[375];

    hex_to_buf(plaintext_hex, plaintext);

    cc20_bytes(key, &counter, nonce, cipher, 375);

    for (size_t i = 0; i < 375; i++) {
        cipher[i] ^= plaintext[i];
    }

    for (size_t i = 0; i < 375; ++i) {
        printf("%02x", cipher[i]);
    }
    printf("\n\n");

    return true;
}

bool seatuna_tests()
{
    return false;
    uint8_t *buf = malloc(1000);

    SeaTuna_t *s = malloc(sizeof(*s));
    seatuna_init(s);
    uint8_t rand_seed[32] = {0xab, 0xab, 0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,0xab,};
    seatuna_seed(rand_seed, 32, s);

    printf("Generating 500MB of certifiably random bytes!!\n");
    FILE *fp = fopen("D:\\Programming\\rand.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        goto end;
    }
    for (uint32_t i = 0; i < 500000; ++i) {
        seatuna_get_bytes(buf, 1000, s);
        fwrite(buf, 1, 1000, fp);
    }

    fclose(fp);

end:
    free(buf);
    free(s);
}