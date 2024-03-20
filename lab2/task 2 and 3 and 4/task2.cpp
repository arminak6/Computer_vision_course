#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ImageFilters.h"
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    try {
        if (argc < 2) {
            throw invalid_argument("Please provide an image filename as a command-line argument.");
        }

        Mat img = imread(argv[1]);
        int kernel_size = std::stoi(argv[2]);


        if (img.empty()) {
            throw runtime_error("Error: Could not read image file " + string(argv[1]));
        }

        if(kernel_size % 2 == 0){
            throw runtime_error("Error: Please enter odd number ");
        }


        float scale_factor = 0.5; // Adjust the scale factor as needed
        resize(img, img, Size(), scale_factor, scale_factor);

        //original image
        cv::namedWindow("image.jpg", WINDOW_NORMAL);
        cv::imshow("image.jpg", img);
        cv::waitKey(0);

        //gray scale image
        Mat gray_image;
        cv::cvtColor(img, gray_image, COLOR_BGR2GRAY);
        namedWindow("Grayscale Image", WINDOW_NORMAL);
        imshow("Grayscale Image", gray_image);
        cv::waitKey(0);   


        // max filter   
        Mat max_ax = maxFilter(gray_image,kernel_size);
        namedWindow("image_max.jpg", WINDOW_NORMAL);
        imshow("image_max.jpg", max_ax);
        string outputFilename = "image_max.jpg";
        // imwrite(outputFilename, gray_image);
        waitKey(0);
        
        //min filter
        Mat min_ax = minFilter(gray_image,kernel_size);
        namedWindow("image_min", WINDOW_NORMAL);
        imshow("image_min", min_ax);
        outputFilename = "image_min.jpg";
        // imwrite(outputFilename, gray_image);
        waitKey(0);

        // //median filter
        Mat median_image;
        median_image = medianFilter(gray_image, kernel_size);
        namedWindow("image_median", WINDOW_NORMAL);
        imshow("image_median", median_image);
        outputFilename = "medianBlur.jpg";
        imwrite(outputFilename, gray_image);
        waitKey(0);


        Mat smoothed_image;
        GaussianBlur(gray_image, smoothed_image, Size(kernel_size, kernel_size), 0, 0);
        namedWindow("image_smooth_Gaussian", WINDOW_NORMAL);
        imshow("image_smooth_Gaussian", smoothed_image);
        outputFilename = "image_smooth_Gaussian.jpg";
        // imwrite(outputFilename, gray_image);
        waitKey(0);

    }
    catch (const exception& e) {
        cout << "file name is wrong" << endl;
        return 1;
    }


    return 0;
}