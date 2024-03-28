#include <opencv2/highgui.hpp>
#include <iostream>

#define NEIGHBORHOOD_Y 9
#define NEIGHBORHOOD_X 9


using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        Mat img = *(Mat*)userdata;
        Mat image_out = img.clone();

        if(y+NEIGHBORHOOD_Y > image_out.rows || x + NEIGHBORHOOD_X > image_out.cols)
            return;        

        cv::Rect rect(x,y,NEIGHBORHOOD_X,NEIGHBORHOOD_Y);
        cv::Scalar mean = cv::mean(image_out(rect));
        cout << "mean: [" << mean[0] << ", " << mean[1] << ", " << mean[2] << "]" << endl;

        
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
