#include "Webcam.hpp"

#include <iostream>

namespace st {

Webcam::Webcam():
    capture_(cvCaptureFromCAM(-1)) {

    if (!capture_) {
        std::cerr << "Unable to open webcam!" << std::endl;
        return;
    }
}

IplImage* Webcam::get_image() const{
    IplImage* image(cvQueryFrame(capture_));

    if(!image)
        std::cerr << "Unable to get Image from webcam!" << std::endl;

    return image;
}

}
