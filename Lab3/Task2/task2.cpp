#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        Mat image = *(Mat*)userdata;
        Vec3b color = image.at<Vec3b>(y, x);
        cout << "BGR color triplet: (" << (int)color[0] << ", " << (int)color[1] << ", " << (int)color[2] << ")" << endl;
    }
}



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

        imshow("image", img);
        setMouseCallback("image", onMouse, &img);
        waitKey(0);

    }
    catch (const exception& e) {
        cout << "file name is wrong" << endl;
        return 1;
    }


    return 0;
}
