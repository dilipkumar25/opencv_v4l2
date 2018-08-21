
[//]: #
[//]: # "opencv_v4l2 - Main README.md file"
[//]: #
[//]: # "Copyright (c) 2017-2018, e-con Systems India Pvt. Ltd.  All rights reserved."
[//]: #

## OpenCV V4L2

A set of applications (and helper library) used to assess the performance of a camera
when OpenCV is used to display/process the camera stream.

## OpenCV build script

This repository also consists of a script and it's related files that automatically
fetches, builds and installs OpenCV with various features and optimization
flags enabled. The script also installs the required dependencies. Further,
it automatically tries to patch a header as it's required for a successful build.


#### Notes
1. This script needs to be run in the same folder where it's dependencies are
   available. Otherwise, the script might not work correctly.
2. This script doesn't automatically try to install CUDA. It must be installed
   manually. For Jetson boards, instructions can be found in the
   [linked NVIDIA site](https://docs.nvidia.com/jetpack-l4t/#jetpack/3.3/install.htm%3FTocPath%3D_____3)


## Build and Install
To install optimized OpenCV:

```
cd opencv
bash opencv_install_script.bash
```

This would have installed OpenCV successfully. To build the sample applications and helper library:

```
cd ..
mkdir build && cd build
cmake ..
make
sudo make install
```

## Generated Applications
The above commands would generate multiple binaries with different characteristics as specified below:

1. `opencv-main`: This application uses the VideoCapture API of OpenCV to fetch
   frames but doesn't render the frames on display. It just prints the framerate achieved.

    The application can be killed by pressing Ctrl+C.

2. `opencv-main-display`: This application is similar to `opencv-main` with the only addition that
   it uses `imshow` to display the camera stream in a window.

    This application can be killed by pressing the ESC key with the display window in focus.

3. `opencv-main-gl-display`: This application is similar to `opencv-main-display` with the only addition that
   it uses an OpenGL rendered window to display the camera stream.

    This application can be killed by pressing the ESC key with the display window in focus.

4. `opencv-main-gpu-display`: This application is similar to `opencv-main-gl-display` with the only
   addition that, the image data is copied to a GpuMat first before getting displayed.

    This application can be killed by pressing the ESC key with the display window in focus.

5. `opencv-v4l2`: This application uses V4L2 to grab frame data from the camera and encapsulate it in
   an OpenCV Mat. This data is then explicitly colorspace converted using `cvtColor`. The application only
   prints the framerate achieved.

    This application can be killed by pressing Ctrl+C.

6. `opencv-v4l2-display`: This application is similar to `opencv-v4l2` with the only addition that
   it uses `imshow` to display the camera stream in a window.

    This application can be killed by pressing the ESC key with the display window in focus.

7. `opencv-v4l2-gl-display`: This application is similar to `opencv-v4l2-display` with the only addition that
   it uses an OpenGL rendered window to display the camera stream.

    This application can be killed by pressing the ESC key with the display window in focus.

8. `opencv-v4l2-gpu-display`: This application is similar to `opencv-v4l2-gl-display` with the only
   addition that, the image data is copied to a GpuMat first before getting displayed.

    This application can be killed by pressing the ESC key with the display window in focus.

9. `opencv-buildinfo`: Sample application that prints the build information of the OpenCV library
   being used. This application can be used to verify that the options selected during compilation were
   really enabled.
