cmake_minimum_required (VERSION 3.0)

project ("OpenCV V4L2")

set (V4L2_SOURCE "src/opencv_v4l2.cpp")
set (MAIN_SOURCE "src/opencv_main.cpp")
set (INFO_SOURCE "src/opencv_buildinfo.cpp")

set (OPENCV_V4L2_BIN "opencv-v4l2")
set (OPENCV_V4L2_DISPLAY_BIN "opencv-v4l2-display")
set (OPENCV_V4L2_GL_DISPLAY_BIN "opencv-v4l2-gl-display")
set (OPENCV_V4L2_GPU_DISPLAY_BIN "opencv-v4l2-gpu-display")
set (OPENCV_MAIN_BIN "opencv-main")
set (OPENCV_MAIN_DISPLAY_BIN "opencv-main-display")
set (OPENCV_MAIN_GL_DISPLAY_BIN "opencv-main-gl-display")
set (OPENCV_MAIN_GPU_DISPLAY_BIN "opencv-main-gpu-display")
set (OPENCV_BUILDINFO_BIN "opencv-buildinfo")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Include the directories containing libraries
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory (lib)

set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${V4L2_HELPER_LIB_INSTALL_PATH}")

# Specify the compiler flags
set (GCC_COMPILE_FLAGS -Wall -Wpedantic -Wextra -O3 -Wshadow -std=c++11 -g)
add_compile_options (${GCC_COMPILE_FLAGS})

add_executable (${OPENCV_V4L2_BIN} ${V4L2_SOURCE})
target_include_directories (${OPENCV_V4L2_BIN} PUBLIC ${V4L2_HELPER_LIB_INCLUDE_DIR})
target_link_libraries (${OPENCV_V4L2_BIN} v4l2_helper)
target_link_libraries (${OPENCV_V4L2_BIN} ${OpenCV_LIBS})

add_executable (${OPENCV_V4L2_DISPLAY_BIN} ${V4L2_SOURCE})
target_include_directories (${OPENCV_V4L2_DISPLAY_BIN} PUBLIC ${V4L2_HELPER_LIB_INCLUDE_DIR})
target_compile_definitions (${OPENCV_V4L2_DISPLAY_BIN} PUBLIC ENABLE_DISPLAY)
target_link_libraries (${OPENCV_V4L2_DISPLAY_BIN} v4l2_helper)
target_link_libraries (${OPENCV_V4L2_DISPLAY_BIN} ${OpenCV_LIBS})

add_executable (${OPENCV_V4L2_GL_DISPLAY_BIN} ${V4L2_SOURCE})
target_include_directories (${OPENCV_V4L2_GL_DISPLAY_BIN} PUBLIC ${V4L2_HELPER_LIB_INCLUDE_DIR})
target_compile_definitions (${OPENCV_V4L2_GL_DISPLAY_BIN} PUBLIC ENABLE_DISPLAY PUBLIC ENABLE_GL_DISPLAY)
target_link_libraries (${OPENCV_V4L2_GL_DISPLAY_BIN} v4l2_helper)
target_link_libraries (${OPENCV_V4L2_GL_DISPLAY_BIN} ${OpenCV_LIBS})

add_executable (${OPENCV_V4L2_GPU_DISPLAY_BIN} ${V4L2_SOURCE})
target_include_directories (${OPENCV_V4L2_GPU_DISPLAY_BIN} PUBLIC ${V4L2_HELPER_LIB_INCLUDE_DIR})
target_compile_definitions (${OPENCV_V4L2_GPU_DISPLAY_BIN} PUBLIC ENABLE_DISPLAY PUBLIC ENABLE_GL_DISPLAY PUBLIC ENABLE_GPU_UPLOAD)
target_link_libraries (${OPENCV_V4L2_GPU_DISPLAY_BIN} v4l2_helper)
target_link_libraries (${OPENCV_V4L2_GPU_DISPLAY_BIN} ${OpenCV_LIBS})

add_executable (${OPENCV_MAIN_BIN} ${MAIN_SOURCE})
target_link_libraries (${OPENCV_MAIN_BIN} ${OpenCV_LIBS})

add_executable (${OPENCV_MAIN_DISPLAY_BIN} ${MAIN_SOURCE})
target_compile_definitions (${OPENCV_MAIN_DISPLAY_BIN} PUBLIC ENABLE_DISPLAY)
target_link_libraries (${OPENCV_MAIN_DISPLAY_BIN} ${OpenCV_LIBS})

add_executable (${OPENCV_MAIN_GL_DISPLAY_BIN} ${MAIN_SOURCE})
target_compile_definitions (${OPENCV_MAIN_GL_DISPLAY_BIN} PUBLIC ENABLE_DISPLAY PUBLIC ENABLE_GL_DISPLAY)
target_link_libraries (${OPENCV_MAIN_GL_DISPLAY_BIN} ${OpenCV_LIBS})

add_executable (${OPENCV_MAIN_GPU_DISPLAY_BIN} ${MAIN_SOURCE})
target_compile_definitions (${OPENCV_MAIN_GPU_DISPLAY_BIN} PUBLIC ENABLE_DISPLAY PUBLIC ENABLE_GL_DISPLAY PUBLIC ENABLE_GPU_UPLOAD)
target_link_libraries (${OPENCV_MAIN_GPU_DISPLAY_BIN} ${OpenCV_LIBS})

add_executable (${OPENCV_BUILDINFO_BIN} ${INFO_SOURCE})
target_link_libraries (${OPENCV_BUILDINFO_BIN} ${OpenCV_LIBS})

install (
	TARGETS
	${OPENCV_V4L2_BIN}
	${OPENCV_V4L2_DISPLAY_BIN}
	${OPENCV_V4L2_GL_DISPLAY_BIN}
	${OPENCV_V4L2_GPU_DISPLAY_BIN}
	${OPENCV_MAIN_BIN}
	${OPENCV_MAIN_DISPLAY_BIN}
	${OPENCV_MAIN_GL_DISPLAY_BIN}
	${OPENCV_MAIN_GPU_DISPLAY_BIN}
	RUNTIME DESTINATION bin
)

# uninstall target
# Ref: https://gitlab.kitware.com/cmake/community/wikis/FAQ#can-i-do-make-uninstall-with-cmake
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
