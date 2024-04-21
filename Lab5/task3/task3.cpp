#include "my_functions.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    try {
        if (argc < 2) {
            throw invalid_argument("Please provide an image filename as a command-line argument.");
        }

        Mat image = imread(argv[1]);

        if (image.empty()) {
            throw runtime_error("Error: Could not read image file " + string(argv[1]));
        }
        
        orange_mask(image);
        waitKey(0);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}
