#include <iostream>
#include <vector>
#include <cmath>
#include "GaussianFilter.h"

// 定义高斯核大小
const int kernelSize = 5;

// 定义标准差
const double sigma = 1.0;

// 定义图像大小
const int width = 256;
const int height = 256;

// 创建高斯核
std::vector<std::vector<double>> createGaussianKernel() {
    std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize, 0.0));
    double sum = 0.0;
    int radius = kernelSize / 2;

    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            double value = exp(-(x * x + y * y) / (2 * sigma * sigma));
            kernel[x + radius][y + radius] = value;
            sum += value;
        }
    }

    // 归一化
    for (int i = 0; i < kernelSize; i++) {
        for (int j = 0; j < kernelSize; j++) {
            kernel[i][j] /= sum;
        }
    }

    return kernel;
}

// 应用高斯滤波
void applyGaussianBlur(const std::vector<std::vector<double>>& kernel, std::vector<std::vector<int>>& inputImage,
                       std::vector<std::vector<int>>& outputImage) {
    int radius = kernelSize / 2;

    for (int x = radius; x < height - radius; x++) {
        for (int y = radius; y < width - radius; y++) {
            double sum = 0.0;

            for (int i = -radius; i <= radius; i++) {
                for (int j = -radius; j <= radius; j++) {
                    sum += kernel[i + radius][j + radius] * inputImage[x + i][y + j];
                }
            }

            outputImage[x][y] = static_cast<int>(sum);
        }
    }
}