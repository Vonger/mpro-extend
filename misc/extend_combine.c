#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int get_file_length(const char *name)
{
    FILE *fp;
    int size;

    fp = fopen(name, "rb");
    if (fp == NULL)
        return -1;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fclose(fp);

    return size;
}

uint8_t *alloc_from_file(const char *name, int *size)
{
    FILE *fp = fopen(name, "rb");
    if (fp == NULL)
        return NULL;

    fseek(fp, 0, SEEK_END);

    *size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    uint8_t *buf = malloc(*size);
    if (buf)
        fread(buf, 1, *size, fp);
    fclose(fp);

    return buf;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("extend_combine [firmware.bin] [extend.bin]\n");
        return -1;
    }

    int size = 0, size_uncompress, size_compress;
    char *buf = alloc_from_file(argv[1], &size);

    // find end of firmware.
    while (buf[--size] == (char)0xff);
    size++;
    printf("firmware valid size = %d\n", size);

    size_uncompress = get_file_length(argv[2]);
    printf("extend compress size = %d\n", size_uncompress);

    // compress extend.bin with lzma.
    char cmd[128] = "";
    snprintf(cmd, 128, "lzma %s", argv[2]);
    system(cmd);

    char name[128] = "";
    snprintf(name, 128, "%s.lzma", argv[2]);
    char *buf_compress = alloc_from_file(name, &size_compress);

    FILE *out = fopen("MPRO.output.bin", "wb");
    fwrite(buf, 1, size, out);
    fwrite(&size_uncompress, 1, 4, out);
    fwrite(&size_compress, 1, 4, out);
    fwrite(buf_compress, 1, size_compress, out);
    fclose(out);

    return 0;
}
