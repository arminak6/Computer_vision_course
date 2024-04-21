#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void segment_sky(Mat inputImage)
{   
    //convert image to gray scale
    Mat grayImage;  
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);
    
    //apply threshold on grayscale image
    Mat binaryMask;
    threshold(grayImage, binaryMask, 90, 255, THRESH_BINARY);
   
    
    // find regions
    vector<vector<Point>> contours;
    findContours(binaryMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //find two biggesgt area
    Mat largestContourMask = Mat::zeros(binaryMask.size(), CV_8UC1);
    double maxArea_1 = 0.0;
    double maxArea_2 = 0.0;
    int maxAreaIdx_1 = -1;
    int maxAreaIdx_2 = -1;
    for (size_t i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);
        if (area > maxArea_1)
        {
            maxArea_1 = area;
            maxAreaIdx_1 = i;
        }else if (area > maxArea_2){
            maxArea_2 = area;
            maxAreaIdx_2 = i;
        }
        
    }

    Mat mask_sky = Mat::zeros(inputImage.size(), CV_8UC1);
    drawContours(mask_sky, contours, maxAreaIdx_1, Scalar(255), FILLED);
    Mat mask_asphalt = Mat::zeros(inputImage.size(), CV_8UC1);
    drawContours(mask_asphalt, contours, maxAreaIdx_2, Scalar(255), FILLED);
    

    Mat segmentedImage;
    inputImage.copyTo(segmentedImage);
    segmentedImage.setTo(Scalar(0, 0, 255), mask_sky);

    Mat sky;
    inputImage.copyTo(sky, mask_sky);
    inputImage.copyTo(sky, mask_asphalt);

    imshow("Contours segmentation " , sky);
    string outputFilename = "segment_sky.jpg";
    imwrite(outputFilename, sky);
}


void k_means(Mat image){

    //convert image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    //apply median filter 
    medianBlur(grayImage, grayImage, 5);
    Mat data = image.reshape(1, image.cols * image.rows);
    data.convertTo(data, CV_32F);

    
    int K = 3;
    TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0);
    int attempts = 3;
    int flags = cv::KMEANS_RANDOM_CENTERS;

    Mat labels, centers;
    kmeans(data, K, labels, criteria, attempts, flags, centers);


    Mat output(image.size(), CV_8UC3);
    Vec3b blue(255, 0, 0);
    Vec3b red(0, 0, 255);
    Vec3b green(0, 255, 0);


    for (int i = 0; i < labels.rows; i++) {
        int label = labels.at<int>(i);
        Vec3b color;
        if (label == 0) {
            color = blue;
        } else if (label == 1) {
            color = red;
        } else {
            color = green;
        }
        output.at<cv::Vec3b>(i) = color;
    }

    imshow("k-means result", output);
    
    string outputFilename = "k-means.jpg";
    imwrite(outputFilename, output);
    waitKey();
}




int main(int argc, char** argv)
{
    if (argc < 2) {
        throw invalid_argument("Please provide an image filename as a command-line argument.");
    }

    Mat image = imread(argv[1]);
    
    if (image.empty())
    {
        cerr << "Image provided does not exist";
    }


    //using countor(first method) 
    segment_sky(image);

    //using k-means(second method)
    k_means(image);
    

    return 0;
}