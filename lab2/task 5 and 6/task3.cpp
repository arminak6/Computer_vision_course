#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            throw invalid_argument("Please provide an image filename as a command-line argument.");
        }

        Mat img = imread(argv[1], IMREAD_GRAYSCALE);

        if (img.empty()) {
            throw runtime_error("Error: Could not read image file " + string(argv[1]));
        }

        int histSize = 256; // Number of bins
        float range[] = { 0, 256 }; // Range of pixel values
        const float* histRange = { range };

        Mat hist;

        // Compute histogram
        calcHist(&img, 1, nullptr, Mat(), hist, 1, &histSize, &histRange);

        // Normalize histogram
        normalize(hist, hist, 0, img.rows, NORM_MINMAX, -1, Mat());

        // Create histogram image
        int histWidth = 512;
        int histHeight = 400;
        int binWidth = cvRound((double)histWidth / histSize);
        Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(255, 255, 255));

        // Plot histogram
        for (int i = 1; i < histSize; ++i) {
            line(histImage, Point(binWidth * (i - 1), histHeight - cvRound(hist.at<float>(i - 1))),
                Point(binWidth * (i), histHeight - cvRound(hist.at<float>(i))),
                Scalar(0, 0, 0), 2, LINE_AA);
        }

        // Perform histogram equalization
        Mat equalizedImg;
        equalizeHist(img, equalizedImg);

        // Compute histogram of equalized image
        Mat equalizedHist;
        calcHist(&equalizedImg, 1, nullptr, Mat(), equalizedHist, 1, &histSize, &histRange);
        normalize(equalizedHist, equalizedHist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

        // Create histogram image for equalized image
        Mat equalizedHistImage(histHeight, histWidth, CV_8UC3, Scalar(255, 255, 255));

        // Plot histogram of equalized image
        for (int i = 1; i < histSize; ++i) {
            line(equalizedHistImage, Point(binWidth * (i - 1), histHeight - cvRound(equalizedHist.at<float>(i - 1))),
                Point(binWidth * (i), histHeight - cvRound(equalizedHist.at<float>(i))),
                Scalar(0, 0, 0), 2, LINE_AA);
        }

        // Display original image and histogram
        namedWindow("Original Image", WINDOW_NORMAL);
        imshow("Original Image", img);

        namedWindow("Original Histogram", WINDOW_NORMAL);
        imshow("Original Histogram", histImage);

        // Display equalized image and histogram
        namedWindow("Equalized Image", WINDOW_NORMAL);
        imshow("Equalized Image", equalizedImg);

        namedWindow("Equalized Histogram", WINDOW_NORMAL);
        imshow("Equalized Histogram", equalizedHistImage);

        // Write histograms to files
        imwrite("Original_Histogram.jpg", histImage);
        imwrite("Equalized_Histogram.jpg", equalizedHistImage);

        waitKey(0);
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
