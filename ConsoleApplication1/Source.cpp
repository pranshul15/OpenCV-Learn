#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void showimage() {
	// Read the image file
	Mat image = imread("D://Notes//EG//Assignment 5//5-images//0003.jpg");
	// Check for failure
	if (image.empty())
	{
		cout << "Image Not Found!!!" << endl;
		cin.get(); //wait for any key press
		return;
	}
	// Show our image inside a window.
	imshow("Image Window Name here", image);

	// Wait for any keystroke in the window
	waitKey(0);
}

void loadAndDisplay() {
	// Read the image file
	Mat image = imread("D://Photoes//IMG_20200104_081454.jpg");

	// Check for failure
	if (image.empty()) {
		cout << "Could not open or find the image" << endl;
		cin.get(); // wait for the press
		return;
	}

	// Name of the window
	String windowName = "Kota PG Room";

	// Create a window
	namedWindow(windowName);

	// Show our image inside the created window
	imshow(windowName, image);

	// wait for the keystroke in the window
	waitKey(0);

	// destroy the created window
	destroyWindow(windowName);
	return;
}

void createAndDisplay() {
	// create a new image which consists of 3 channels
	// image depth is 8 bits
	// 800x600 of resolution (800 wide and 600 height)
	// each pixel initialized to value of (100,250,30) for blue green and red planes respectively
	
	Mat image(600, 800, CV_8UC3, Scalar(100, 250, 30));

	String windowName = "Window with blank image";
	namedWindow(windowName);
	imshow(windowName, image);
	waitKey(0);
	destroyWindow(windowName);
	return;
}

void videoFromFile() {
	// open video from file for reading
	VideoCapture cap("D://Photoes//VID_20210207_190704.mp4");

	// if not success, exit program
	if (cap.isOpened() == false) {
		cout << "cannot open video file" << endl;
		cin.get();
		return;
	}

	// if we want to start video in the middle
	cap.set(CAP_PROP_POS_MSEC, 300);

	// get frame rates of the video
	double fps = cap.get(CAP_PROP_FPS);
	cout << "Frames per second : " << fps << endl;

	String videoName = "My First Video";

	namedWindow(videoName, WINDOW_NORMAL);

	while (true) {
		Mat frame;
		bool bsuccess = cap.read(frame);

		// Breaking while loop at the end of video
		if (bsuccess == false) {
			cout << "Found the end of the video" << endl;
			break;
		}

		// show the frame created in the video
		imshow(videoName, frame);

		// wait 10 ms until any key is pressed
		// If the key is 'Esc' break the while loop
		// If any other key, continue the loop
		// If no key within 10 ms, continue loop
		if (waitKey(10) == 27) {
			cout << "Esc key is pressed, stopping the loop" << endl;
			break;
		}
	}
}

void cameraCapturePlay() {
	// open the default video camera
	VideoCapture cap(0);

	// if not success, exit the program
	if (cap.isOpened() == false) {
		cout << "cannot open the camera" << endl;
		cin.get();
		return;
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

	cout << "resolution of the video : " << dWidth << " x " << dHeight << endl;

	String window_name = "My camera feed";
	namedWindow(window_name);

	while (true)
	{
		Mat frame;
		bool bsuccess = cap.read(frame);

		if (bsuccess == false) {
			cout << "video camera is disconnected" << endl;
			cin.get();
			return;
		}

		imshow(window_name, frame);

		if (waitKey(10) == 27) {
			cout << "Esc key is pressed, stopping the program" << endl; 
			break;
		}
	}
}

void saveImage() {
	Mat image = imread("D://Photoes//IMG_20200126_095749.jpg");

	if (image.empty()) {
		cout << "cannot open the image file" << endl;
		cin.get();
		return;
	}

	bool isSuccess = imwrite("D://myimagesave.jpg", image);

	if (isSuccess == false) {
		cout << "Failed to write image" << endl;
		cin.get();
		return;
	}

	cout << "Image is successully saved to file" << endl;

	String windowName = "The saved image";
	namedWindow(windowName);
	imshow(windowName, image);

	waitKey(0);

	destroyWindow(windowName);
	return;
}

void saveVideo() {
	VideoCapture cap(0);

	if (cap.isOpened() == false) {
		cout << "cannot open the video camera" << endl;
		cin.get();
		return;
	}

	int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
	int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));

	Size frame_size(frame_width, frame_height);
	int frames_per_second = 10;

	VideoWriter oVideoWriter("D://MyVid.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), frames_per_second,frame_size,true);

	if (oVideoWriter.isOpened() == false) {
		cout << "cannot save the video file" << endl;
		cin.get();
		return;
	}

	string windowName = "my camera feed";
	namedWindow(windowName);

	while (true) {

		Mat frame;
		bool isSuccess = cap.read(frame);

		if (isSuccess == false) {
			cout << "Video camera is disconnected" << endl;
			cin.get();
			return;
		}

		oVideoWriter.write(frame);
		imshow(windowName, frame);

		if (waitKey(10) == 27) {
			cout << "Esc key is pressed by the user. Stopping the video" << endl;
			break;
		}

	}

	oVideoWriter.release();
}

void changeBrightnessImage(){
	Mat image = imread("D://Photoes//DemoPic.jpg");

	if (image.empty()) {
		cout << "could not open file or image" << endl;
		cin.get();
		return;
	}

	// increase brightness by 50
	Mat imageBrightnessHigh50;
	image.convertTo(imageBrightnessHigh50, -1, 1, 50);

	// increase brightness by 100
	Mat imageBrightnessHigh100;
	image.convertTo(imageBrightnessHigh100, -1, 1, 100);

	// decrease brightness by 50
	Mat imageBrightnessLow50;
	image.convertTo(imageBrightnessLow50, -1, 1, -50);

	// decrease brightness by 100
	Mat imageBrightnessLow100;
	image.convertTo(imageBrightnessLow100, -1, 1, -100);

	// defining window names for above images
	cv::String windowNameOriginalImage = "Original Image";
	cv::String windowNameBrightnessHigh50 = "Brightness Increased by 50";
	cv::String windowNameBrightnessHigh100 = "Brightness Increased by 100";
	cv::String windowNameBrightnessLow50 = "Brightness Decreased by 50";
	cv::String windowNameBrightnessLow100 = "Brightness Decreased by 100";

	cv::imshow(windowNameOriginalImage, image);
	cv::imshow(windowNameBrightnessHigh50, imageBrightnessHigh50);
	cv::imshow(windowNameBrightnessHigh100, imageBrightnessHigh100);
	cv::imshow(windowNameBrightnessLow50, imageBrightnessLow50);
	cv::imshow(windowNameBrightnessLow100, imageBrightnessLow100);

	cv::waitKey(0);
	cv::destroyAllWindows();
}

int main(int argc, char** argv)
{
	changeBrightnessImage();
	return 0;
}
