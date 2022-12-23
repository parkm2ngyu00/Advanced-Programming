#include "hash.h"

int hash_func(char *path, unsigned char *hash)
{
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Failed to open %s\n", path);
        return -1;
    }

    MD5_CTX ctx;

    MD5_Init(&ctx);

    int bytes;
    unsigned char data[1024];

    while ((bytes = fread(data, 1, 1024, fp)) != 0)
        MD5_Update(&ctx, data, bytes);

    MD5_Final(hash, &ctx);

    // int i;
    // for(i=0; i<MD5_DIGEST_LENGTH; i++)
    //     printf("%02x", hash[i]);

    // printf("\n");

    fclose (fp);

    return 0;
}
