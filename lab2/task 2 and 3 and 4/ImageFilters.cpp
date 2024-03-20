#include "ImageFilters.h"

using namespace cv;

cv::Mat maxFilter(cv::Mat src, int kernelSize) {

    cv::Mat dst = src.clone(); // Create a copy of the source image

    int padding = kernelSize / 2;
    for (int y = padding; y < src.rows - padding; ++y) {
        for (int x = padding; x < src.cols - padding; ++x) {
            uchar maxVal = 0;
            for (int j = -padding; j <= padding; ++j) {
                for (int i = -padding; i <= padding; ++i) {
                    maxVal = std::max(maxVal, src.at<uchar>(y + j, x + i));
                }
            }
            dst.at<uchar>(y, x) = maxVal;
        }
    }

    return dst;
}

cv::Mat minFilter(cv::Mat src, int kernelSize) {


    cv::Mat dst = src.clone(); // Create a copy of the source image

    int padding = kernelSize / 2;
    for (int y = padding; y < src.rows - padding; ++y) {
        for (int x = padding; x < src.cols - padding; ++x) {
            uchar minVal = 255;
            for (int j = -padding; j <= padding; ++j) {
                for (int i = -padding; i <= padding; ++i) {
                    minVal = std::min(minVal, src.at<uchar>(y + j, x + i));
                }
            }
            dst.at<uchar>(y, x) = minVal;
        }
    }


    return dst;
}

// cv::Mat minFilter(const cv::Mat src, int kernelSize) {
//     CV_Assert(src.type() == CV_8UC1); // Ensure input image is single-channel (grayscale)

//     cv::Mat dst = src.clone(); // Create a copy of the source image

//     int padding = kernelSize / 2;
//     int rows = src.rows;
//     int cols = src.cols;

//     for (int y = padding; y < rows - padding; ++y) {
//         for (int x = padding; x < cols - padding; ++x) {
//             uchar minVal = 255;

//             // Iterate over the local window
//             for (int j = -padding; j <= padding; ++j) {
//                 for (int i = -padding; i <= padding; ++i) {
//                     uchar pixelVal = src.at<uchar>(y + j, x + i);
//                     minVal = std::min(minVal, pixelVal);
//                 }
//             }

//             dst.at<uchar>(y, x) = minVal;
//         }
//     }

//     return dst;
// }




cv::Mat medianFilter(cv::Mat image, int kernelSize) {
    cv::Mat result = image.clone();
    int rows = image.rows;
    int cols = image.cols;

    // Iterate through each pixel in the image
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Create a vector to store pixel values within the kernel
            std::vector<uchar> values;

            // Iterate through the kernel centered at the current pixel
            for (int m = -kernelSize / 2; m <= kernelSize / 2; ++m) {
                for (int n = -kernelSize / 2; n <= kernelSize / 2; ++n) {
                    int rowIdx = i + m;
                    int colIdx = j + n;

                    // Check boundaries to avoid out-of-bound access
                    if (rowIdx >= 0 && rowIdx < rows && colIdx >= 0 && colIdx < cols) {
                        values.push_back(image.at<uchar>(rowIdx, colIdx));
                    }
                }
            }

            // Sort the values to find the median
            std::sort(values.begin(), values.end());

            // Assign the median value to the result image
            result.at<uchar>(i, j) = values[values.size() / 2];
        }
    }

    return result;
}

