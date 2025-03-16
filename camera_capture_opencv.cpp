// Created by Pouya Samandi on 2025-03-12.
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    // Open the default camera (0 is usually the built-in MacBook camera)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open camera!" << endl;
        return -1;
    }

    cout << "Camera opened successfully. Press 'q' to quit." << endl;

    cv::Mat frame;
    while (true) {
        // Capture a frame
        cap >> frame;
        if (frame.empty()) {
            cerr << "Error: Could not grab frame!" << endl;
            break;
        }

        // Display the frame (optional, for testing)
        cv::imshow("Live Camera", frame);

        // Check for 'q' key to exit
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the camera
    cap.release();
    cv::destroyAllWindows();
    return 0;
}