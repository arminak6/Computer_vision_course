#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat k_means(Mat image){

    // //convert image to grayscale
    // Mat grayImage;
    // cvtColor(image, grayImage, COLOR_BGR2GRAY);

    //apply median filter 
    medianBlur(image, image, 5);
    Mat data = image.reshape(1, image.cols * image.rows);
    data.convertTo(data, CV_32F);

    
    int K = 2;
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
        }
        output.at<cv::Vec3b>(i) = color;
    }

    imshow("k-means result", output);
    
    // string outputFilename = "k-means.jpg";
    // imwrite(outputFilename, output);
    waitKey();
    return output;
}


Mat erodee(Mat src){
    Mat gray;
    cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // Perform image preprocessing (median blur, thresholding, erosion, etc.)
    Mat blurred_image;
    medianBlur(gray, blurred_image, 3);

    threshold(gray, gray, 15, 255, THRESH_BINARY);

    Mat kernel = getStructuringElement(MORPH_RECT, cv::Size(3, 3));
    Mat erode_image;
    erode(gray, erode_image, kernel);

    Mat final_image;
    medianBlur(erode_image, final_image, 5);

    imshow("Median Blurred Image", final_image);
    waitKey(0);

    return final_image;
}


int main(int argc, char** argv) {

    Mat src = cv::imread(argv[1]);

    // Check if the image was successfully loaded
    if (src.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    Mat erode , kmeans, kham;
    erode = erodee(src);

    kmeans = k_means(erode);


    return 0;
}

