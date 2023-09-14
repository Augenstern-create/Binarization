#include <iostream>
#include <cmath>
#include <vector>
#include <omp.h>
#include "Binarization.h"

// rgb转灰度图
void RGBToGRAY(const unsigned char* src, unsigned char* dst, int width, int height) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < width * height; i++) {
        dst[i] = 0.299 * src[i * 3 + 0] + 0.587 * src[i * 3 + 1] + 0.114 * src[i * 3 + 2];
    }
}

// 转灰度图
void ImageToGRAY(const unsigned char* src, unsigned char* dst, int width, int height, int channels) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < width * height; i++) {
        dst[i] = 0.299 * src[i * channels + 0] + 0.587 * src[i * channels + 1] + 0.114 * src[i * channels + 2];
    }
}

// 二进制阈值化
void BinaryThresholded(const unsigned char* src, unsigned char* dst, int width, int height, double thresh) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < width * height; i++) {
        if (src[i] < thresh) {
            dst[i] = 0;
        } else {
            dst[i] = 255;
        }
    }
}

// 反二进制阈值化
void AntiBinaryThresholding(const unsigned char* src, unsigned char* dst, int width, int height, double thresh) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < width * height; i++) {
        if (src[i] < thresh) {
            dst[i] = 255;
        } else {
            dst[i] = 0;
        }
    }
}

// 截断阈值化
void TruncationThresholding(const unsigned char* src, unsigned char* dst, int width, int height, double thresh) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < width * height; i++) {
        if (src[i] < thresh) {
            dst[i] = src[i];
        } else {
            dst[i] = thresh;
        }
    }
}

// 反阈值化为0
void AntiThresholdingTo0(const unsigned char* src, unsigned char* dst, int width, int height, double thresh) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < width * height; i++) {
        if (src[i] < thresh) {
            dst[i] = src[i];
        } else {
            dst[i] = 0;
        }
    }
}

// 阈值化为0
void ThresholdingTo0(const unsigned char* src, unsigned char* dst, int width, int height, double thresh) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < width * height; i++) {
        if (src[i] < thresh) {
            dst[i] = 0;
        } else {
            dst[i] = src[i];
        }
    }
}

// 平均值阈值
double AverageValueThreshold(const unsigned char* src, int width, int height) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    int sum = 0;
    for (size_t i = 0; i < width * height; i++) {
        sum += src[i];
    }
    return (double)sum / (double)(width * height);  // 修正括号位置
}

// 中值阈值
double MedianThreshold(const unsigned char* src, int width, int height) {
    int sum[256] = {0};
    int threshold = 0;
    int medianCount = (width * height) / 2;  // 中值位置
#ifdef _OPENMP
#pragma omp parallel for
#endif

    for (size_t i = 0; i < width * height; i++) {
        sum[src[i]]++;
    }

    // 找到中值位置对应的灰度级
    for (int i = 0; i < 256; i++) {
        medianCount -= sum[i];
        if (medianCount <= 0) {
            threshold = i;
            break;
        }
    }

    return (double)threshold;
}

// 高斯滤波
void GaussianFilter(const unsigned char* src, unsigned char* dst, int width, int height) {}

// 自适应阈值
void AdaptiveThreshold(const unsigned char* src, unsigned char* dst, int width, int height) {
#ifdef _OPENMP
#pragma omp parallel for
#endif
}