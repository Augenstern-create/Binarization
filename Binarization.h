#ifndef BINARIZATION_H
#define BINARIZATION_H

#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

void RGBToGRAY(const unsigned char* src, unsigned char* dst, int width, int height);
void ImageToGRAY(const unsigned char* src, unsigned char* dst, int width, int height, int channels);

void BinaryThresholded(const unsigned char* src, unsigned char* dst, int width, int height, double thresh);

void AntiBinaryThresholding(const unsigned char* src, unsigned char* dst, int width, int height, double thresh);

void TruncationThresholding(const unsigned char* src, unsigned char* dst, int width, int height, double thresh);

void AntiThresholdingTo0(const unsigned char* src, unsigned char* dst, int width, int height, double thresh);

void ThresholdingTo0(const unsigned char* src, unsigned char* dst, int width, int height, double thresh);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif  // BINARIZATION_H