#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

#include <opencv2/core.hpp>

using namespace cv;

// Function declarations
cv::Mat maxFilter(cv::Mat src, int kernelSize);
cv::Mat minFilter(cv::Mat src, int kernelSize);
cv::Mat medianFilter(cv::Mat image, int kernelSize);

#endif // IMAGEFILTERS_H

