/*
 * opencv_v4l2 - opencv_buildinfo.cpp file
 *
 * Copyright (c) 2017-2018, e-con Systems India Pvt. Ltd.  All rights reserved.
 *
 */

#include <opencv2/core/utility.hpp>
#include <iostream>
int main()
{
	std::cout << cv::getBuildInformation() << std::endl;
	return 0;
}

