#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define NEIGHBORHOOD_Y 9
#define NEIGHBORHOOD_X 9

#define MAX_B_CHANNEL 70
#define MAX_G_CHANNEL 100
#define MAX_R_CHANNEL 70

const int THRESHOLD = 50;


void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        Mat image = *(Mat*)userdata;
        Mat image_out = image.clone();
        
        if(y+NEIGHBORHOOD_Y > image_out.rows || x + NEIGHBORHOOD_X > image_out.cols)
            return;

        cv::Rect rect(x,y,NEIGHBORHOOD_X,NEIGHBORHOOD_Y);
        cv::Scalar mean = cv::mean(image_out(rect));
        
        
        Mat mask = Mat::zeros(image_out.size(), CV_8UC1);
        
        
        for (int i = 0; i < image_out.rows; i++)
        {
            for (int j = 0; j < image_out.cols; j++)
            {
                
                Vec3b pixel_color = image_out.at<Vec3b>(i, j);
                
                if(((abs(pixel_color[0] - mean[0])) < THRESHOLD) && (abs((pixel_color[1] - mean[1])) < THRESHOLD)  && (abs(pixel_color[2] - mean[2]) < THRESHOLD) ) 
                {
                    mask.at<uchar>(i, j) = 255;
                }else{
                    mask.at<uchar>(i, j) = 0;
                }
            }
        }
        string outputFilename = "new_robocup.jpg";
        imwrite(outputFilename, mask);
        imshow("mask", mask);
        waitKey(0);
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


        cvtColor(img, img, COLOR_BGR2HSV);
        

        imshow("image", img);
        string outputFilename = "HSV_robocup.jpg";
        imwrite(outputFilename, img);


        setMouseCallback("image", onMouse, &img);
        waitKey(0);

    }
    catch (const exception& e) {
        cout << "file name is wrong" << endl;
        return 1;
    }


    return 0;
}