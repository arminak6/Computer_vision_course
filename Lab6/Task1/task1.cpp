#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/flann.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;


void sift_and_brForce(Mat img1 , Mat img2){
    cvtColor(img1 , img1 , COLOR_BGR2GRAY);
    cvtColor(img2 , img2 , COLOR_BGR2GRAY);
    Ptr<SIFT> sift = SIFT::create();

    // find the keypoints and descriptors with SIFT
    vector<KeyPoint> kp1, kp2;
    Mat des1, des2;
    sift->detectAndCompute(img1, Mat(), kp1, des1);
    sift->detectAndCompute(img2, Mat(), kp2, des2);

    // BFMatcher with default params
    BFMatcher bf(NORM_L2, false);
    vector<vector<DMatch>> matches;
    bf.knnMatch(des1, des2, matches, 2);

    // Apply ratio test
    vector<vector<DMatch>> good_matches;
    for (size_t i = 0; i < matches.size(); i++)
    {
        if (matches[i][0].distance < 0.75 * matches[i][1].distance)
        {
            good_matches.push_back(matches[i]);
        }
    }


    double match_ratio = (double)good_matches.size() / (double)matches.size();

    if(match_ratio > 0.10){
        cout<< "The two images have similar content." << endl;
    }else if(match_ratio > 0.02){
        cout << "the two images have similar content processed by some strong transformation" << endl;
    }else{
        cout << "Images have different content" << endl;
    }
    // cv.drawMatchesKnn expects list of lists as matches.
    Mat img3;
    drawMatches(img1, kp1, img2, kp2, good_matches, img3, Scalar::all(-1), Scalar::all(-1), vector<vector<char>>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Show image
    imshow("Matches", img3);
}

void tt_br(Mat img1 , Mat img2){
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    cvtColor(img2, img2, COLOR_BGR2GRAY);

    Ptr<ORB> orb = ORB::create();

    // find the keypoints and descriptors with ORB
    vector<KeyPoint> kp1, kp2;
    Mat des1, des2;
    orb->detectAndCompute(img1, Mat(), kp1, des1);
    orb->detectAndCompute(img2, Mat(), kp2, des2);

    // create BFMatcher object
    BFMatcher matcher(NORM_HAMMING, true);

    // Match descriptors.
    vector<DMatch> matches;
    matcher.match(des1, des2, matches);

    // Sort them in the order of their distance.
    sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) { return a.distance < b.distance; });

    // Calculate average distance of top 10 matches
    double avgDist = 0.0;
    int numMatches = 10;
    for (int i = 0; i < numMatches; i++) {
        avgDist += matches[i].distance;
    }
    avgDist /= numMatches;


    // Determine if images have similar or different content
    if (avgDist < 40.0) {
        cout << "Images have similar content" << endl;
    }else if (avgDist < 50.0){
        cout << "the two images have similar content processed by some strong transformation" << endl;
    }else {
        cout << "Images have different content" << endl;
    }

    // Draw first 10 matches.
    Mat img3;
    drawMatches(img1, kp1, img2, kp2, matches, img3, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Show image
    imshow("Matches", img3);
    waitKey(0);
}

void sift(Mat img1 , Mat img2){
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    cvtColor(img2, img2, COLOR_BGR2GRAY);

    Ptr<Feature2D> sift = SIFT::create();

    // Detect keypoints and compute descriptors for both images
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    sift->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
    sift->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

    // Match descriptors using FLANN matcher
    Ptr<DescriptorMatcher> matcher = FlannBasedMatcher::create();
    vector<DMatch> matches;
    matcher->match(descriptors1, descriptors2, matches);

    // Calculate the maximum and minimum distances between keypoints
    double max_dist = 0;
    double min_dist = 100;
    for (int i = 0; i < descriptors1.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    // Filter matches based on distance threshold
    std::vector<DMatch> good_matches;
    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches[i].distance <= 2 * min_dist) {
            good_matches.push_back(matches[i]);
        }
    }

    // Compute similarity score
    double sim_score = (double)good_matches.size() / (double)descriptors1.rows;

    // Compare similarity score with threshold
    double threshold = 0.3; // Set threshold value here
    if (sim_score >= threshold) {
        cout << "Images are similar" << endl;
    } else {
        cout << "Images are not similar" << endl;
    }



}

int main(int argc, char **argv)
{
    try {
    if (argc < 3) {
        throw invalid_argument("Please provide an image filename as a command-line argument.");
    }

    Mat img1 = cv::imread(argv[1]);
    Mat img2 = cv::imread(argv[2]);

    if (img1.empty() || img2.empty()) {
        throw runtime_error("Error: Could not read image file " + string(argv[1]));
    }

    cout<< "the result of sift :" << endl;
    sift(img1 , img2);

    cout<<"result of using sift and brForce " << endl;
    sift_and_brForce(img1 , img2);

    cout<<"result of using orb and brForce " << endl;
    tt_br(img1 , img2); 


    waitKey(0);

    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return 1;
    }
    
    return 0;
}
