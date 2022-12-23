#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {
    size_t i = 0;
    uint32_t hash = 0;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

int main(int argc, char *argv[])
{
    uint32_t val = jenkins_one_at_a_time_hash((uint8_t *)argv[1], strlen(argv[1]));
    printf("0x%x\n", val);

    return 0;
}