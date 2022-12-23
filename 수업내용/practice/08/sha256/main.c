#include <stdio.h>
#include <openssl/sha.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("Failed to open %s\n", argv[1]);
        return -1;
    }

    SHA256_CTX ctx;

    SHA256_Init(&ctx);

    int bytes;
    unsigned char data[1024];

    while ((bytes = fread(data, 1, 1024, fp)) != 0)
        SHA256_Update(&ctx, data, bytes);

    unsigned char c[SHA256_DIGEST_LENGTH];

    SHA256_Final(c,&ctx);

    int i;
    for(i=0; i<SHA256_DIGEST_LENGTH; i++)
        printf("%02x", c[i]);

    printf(" %s\n", argv[1]);

    fclose (fp);

    return 0;
}
