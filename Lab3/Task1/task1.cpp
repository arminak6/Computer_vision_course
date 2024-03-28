#include <opencv2/highgui.hpp>
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

        cv::namedWindow("image.jpg", WINDOW_NORMAL);
        cv::imshow("image.jpg", img);
        cv::waitKey(0);

    }
    catch (const exception& e) {
        cout << "file name is wrong" << endl;
        return 1;
    }


    return 0;
}