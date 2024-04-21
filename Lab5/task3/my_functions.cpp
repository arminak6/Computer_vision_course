#include "my_functions.h"

void orange_mask(cv::Mat image){
    //convert image to HSV
    Mat hsv_image;
    cvtColor(image, hsv_image, cv::COLOR_BGR2HSV);
    
    //create orange mask
    Scalar lower_orange(10, 90, 120);
    Scalar upper_orange(50, 255, 255);

    Mat orange_mask;
    inRange(hsv_image, lower_orange, upper_orange, orange_mask);


    //smoth image
    Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    erode(orange_mask, orange_mask, kernel);
    dilate(orange_mask, orange_mask, kernel);

    Mat orange_image, everything_else_image;
    bitwise_and(image, image, orange_image, orange_mask);
    bitwise_not(orange_mask, everything_else_image);
    bitwise_and(image, image, everything_else_image, everything_else_image);

    //final result
    imshow("Orange Image", orange_image);
    
    string outputFilename = "Orange_Image.jpg";
    imwrite(outputFilename, orange_image);
}
