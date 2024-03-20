#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
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

        if (img.empty()) {
            throw runtime_error("Error: Could not read image file " + string(argv[1]));
        }

        // Resize the image to a smaller size
        Mat resized_img;
        float scale_factor = 0.5; // Adjust the scale factor as needed
        resize(img, resized_img, Size(), scale_factor, scale_factor);

        // Display the resized image
        cv::namedWindow("Resized Image", WINDOW_NORMAL);
        cv::imshow("Resized Image", resized_img);
        cv::waitKey(0);

        // Convert the resized image to grayscale
        Mat gray_image;
        cvtColor(resized_img, gray_image, COLOR_BGR2GRAY);

        // Display the grayscale image
        namedWindow("Grayscale Image", WINDOW_NORMAL);
        imshow("Grayscale Image", gray_image);
        cv::waitKey(0);    

        string outputFilename = "Garden_grayscale.jpg";
        imwrite(outputFilename, gray_image);

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
