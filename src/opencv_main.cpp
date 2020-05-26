/*
 * opencv_v4l2 - opencv_main.cpp file
 *
 * Copyright (c) 2017-2018, e-con Systems India Pvt. Ltd.  All rights reserved.
 *
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>

using namespace std;
using namespace cv;

unsigned int GetTickCount()
{
        struct timeval tv;
        if(gettimeofday(&tv, NULL) != 0)
                return 0;
 
        return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int main(int argc, char **argv)
{
	unsigned int width, height;
	unsigned int start, end , fps = 0;
	VideoCapture cap(0 + CAP_V4L2); // open the default camera with V4L2 backend

	/*
	 * Re-using the frame matrix(ces) instead of creating new ones (i.e., declaring 'Mat frame'
	 * (and cuda::GpuMat gpu_frame) outside the 'while (1)' loop instead of declaring it
	 * within the loop) improves the performance for higher resolutions.
	 */
	Mat frame;
	#if defined(ENABLE_DISPLAY) && defined(ENABLE_GL_DISPLAY) && defined(ENABLE_GPU_UPLOAD)
	cuda::GpuMat gpu_frame;
	#endif

	if (argc == 3)
	{
		/*
		 * Courtesy: https://stackoverflow.com/a/2797823
		 */
		string width_str = argv[1];
		string height_str = argv[2];
		try {
			size_t pos;
			width = stoi(width_str, &pos);
			if (pos < width_str.size()) {
				cerr << "Trailing characters after width: " << width_str << '\n';
			}

			height = stoi(height_str, &pos);
			if (pos < height_str.size()) {
				cerr << "Trailing characters after height: " << height_str << '\n';
			}
		} catch (invalid_argument const &ex) {
			cerr << "Invalid width or height\n";
			return EXIT_FAILURE;
		} catch (out_of_range const &ex) {
			cerr << "Width or Height out of range\n";
			return EXIT_FAILURE;
		}
	}
	else
	{
		cout << "Note: This program accepts (only) two arguments. First arg: width, Second arg: height\n";
		cout << "No arguments given. Assuming default values. Width: 640; Height: 480\n";
		width = 640;
		height = 480;
	}

	if(!cap.isOpened())  // check if we succeeded
		return EXIT_FAILURE;
	cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
	cout << "Current resolution: Width: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << " Height: " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << '\n';

#ifdef ENABLE_DISPLAY
	/*
	 * Using a window with OpenGL support to display the frames improves the performance
	 * a lot. It is essential for achieving better performance.
	 */
	#ifdef ENABLE_GL_DISPLAY
	namedWindow("preview", cv::WINDOW_OPENGL);
	#else
	namedWindow("preview");
	#endif
	cout << "Note: Click 'Esc' key to exit the window.\n";
#endif

	start = GetTickCount();
	while (1) {
		cap >> frame; // get a new frame from camera
		if (frame.empty())
		{
			cerr << "Empty frame received from camera!\n";
			return EXIT_FAILURE;
		}

#ifdef ENABLE_DISPLAY
	/*
	 * It is possible to use a GpuMat for display (imshow) only
	 * when window is created with OpenGL support. So,
	 * ENABLE_GL_DISPLAY is also required for gpu_frame.
	 *
	 * Ref: https://docs.opencv.org/3.4.2/d7/dfc/group__highgui.html#ga453d42fe4cb60e5723281a89973ee563
	 */
	#if defined(ENABLE_GL_DISPLAY) && defined(ENABLE_GPU_UPLOAD)
		/*
		 * Uploading the frame matrix to a cv::cuda::GpuMat and using it to display (via cv::imshow) also
		 * contributes to better and consistent performance.
		 */
		gpu_frame.upload(frame);
		imshow("preview", gpu_frame);
	#else
		imshow("preview", frame);
	#endif

		if(waitKey(1) == 27) break;
#endif
		fps++;
		end = GetTickCount();
		if ((end - start) >= 1000) {
			cout << "fps = " << fps << endl ;
			fps = 0;
			start = end;
		}
	}

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
