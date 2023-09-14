#include "browse.h"
#define USE_SHELL_OPEN
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define TJE_IMPLEMENTATION
#include "tiny_jpeg.h"

#include "Binarization.h"

char saveFile[1024];

// 读取图片
unsigned char *loadImage(const char *filename, int *Width, int *Height, int *Channels) {
    return (stbi_load(filename, Width, Height, Channels, 0));
}

// 保存图片
void saveImage(const char *filename, int Width, int Height, int Channels, unsigned char *Output) {
    memcpy(saveFile + strlen(saveFile), filename, strlen(filename));
    *(saveFile + strlen(saveFile) + 1) = 0;

    if (!tje_encode_to_file(saveFile, Width, Height, Channels, true, Output)) {
        fprintf(stderr, "save JPEG fail.\n");
        return;
    }
#ifdef USE_SHELL_OPEN
    browse(saveFile);
#endif
}

void splitpath(const char *path, char *drv, char *dir, char *name, char *ext) {
    const char *end;
    const char *p;
    const char *s;
    if (path[0] && path[1] == ':') {
        if (drv) {
            *drv++ = *path++;
            *drv++ = *path++;
            *drv = '\0';
        }
    } else if (drv)
        *drv = '\0';
    for (end = path; *end && *end != ':';) end++;
    for (p = end; p > path && *--p != '\\' && *p != '/';)
        if (*p == '.') {
            end = p;
            break;
        }
    if (ext)
        for (s = end; (*ext = *s++);) ext++;
    for (p = end; p > path;)
        if (*--p == '\\' || *p == '/') {
            p++;
            break;
        }
    if (name) {
        for (s = p; s < end;) *name++ = *s++;
        *name = '\0';
    }
    if (dir) {
        for (s = path; s < p;) *dir++ = *s++;
        *dir = '\0';
    }
}

void getCurrentFilePath(const char *filePath, char *saveFile) {
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    splitpath(filePath, drive, dir, fname, ext);
    size_t n = strlen(filePath);
    memcpy(saveFile, filePath, n);
    char *cur_saveFile = saveFile + (n - strlen(ext));
    cur_saveFile[0] = '_';
    cur_saveFile[1] = 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return (0);
    }
    char *szfile1 = argv[1];
    int width, height, channels;
    width = height = channels = 0;

    unsigned char *src = nullptr;
    src = loadImage(szfile1, &width, &height, &channels);
    if (width == 0 || height == 0 || channels == 0 || src == nullptr) {
        printf("Image Read Failure\n");
        return -1;
    }
    unsigned char *graysrc = (unsigned char *)malloc(width * height * sizeof(unsigned char));
    unsigned char *graydst = (unsigned char *)malloc(width * height * sizeof(unsigned char));
    double thresh = 127.0;
    ImageToGRAY(src, graysrc, width, height, channels);
    ThresholdingTo0(graysrc, graydst, width, height, thresh);

    saveImage("done.jpg", width, height, 1, graydst);

    delete[] src;
    delete[] graysrc;
    delete[] graydst;
    printf("fulfillment");
}
