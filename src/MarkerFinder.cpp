#include "MarkerFinder.hpp"

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <algorithm>

namespace st {

MarkerFinder::MarkerFinder():
    last_result_(),
    hue_(0.f) {
//        cvNamedWindow("result1", CV_WINDOW_AUTOSIZE);
        cvNamedWindow("result2", CV_WINDOW_AUTOSIZE);
    }

MarkerFinder::MarkerFinder(float hue):
    last_result_(),
    hue_(hue) {
//        cvNamedWindow("result1", CV_WINDOW_AUTOSIZE);
        cvNamedWindow("result2", CV_WINDOW_AUTOSIZE);
    }

void MarkerFinder::set_color(float hue) {
    hue_ = hue;
}

bool MarkerFinder::process_image(IplImage* image, Result& result) {

    //threshold image
//    IplImage* hsv(NULL);
//    hsv = cvCreateImage(cvSize(image->width, image->height), image->depth, 3);
//
//    if (!hsv) {
//        std::cerr << "Unable to create image!" << std::endl;
//        return false;
//    }

    IplImage* threshold(NULL);
    threshold = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);

    if (!threshold) {
        std::cerr << "Unable to create image!" << std::endl;
        return false;
    }

    cvInRangeS(image, cvScalar(180, 240, 240), cvScalar(256, 256, 256), threshold);

    auto storage(cvCreateMemStorage());

    CvSeq* contour = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storage);

    cvFindContours(threshold, storage, &contour);

    double area_one(0.0), area_two(0.0);

    while (contour) {
        double area(std::fabs(cvContourArea(contour)));

        auto bounding_rect(cvBoundingRect(contour));

        if (area > area_one && area > area_two) {
            if (area_one > area_two) {
                area_two = area;
                result.second.x = bounding_rect.x + bounding_rect.width * 0.5;
                result.second.y = bounding_rect.y + bounding_rect.height * 0.5;
            } else {
                area_one = area;
                result.first.x = bounding_rect.x + bounding_rect.width * 0.5;
                result.first.y = bounding_rect.y + bounding_rect.height * 0.5;
            }
        } else if (area > area_two) {
            area_two = area;
            result.second.x = bounding_rect.x + bounding_rect.width * 0.5;
            result.second.y = bounding_rect.y + bounding_rect.height * 0.5;
        } else if (area > area_one) {
            area_one = area;
            result.first.x = bounding_rect.x + bounding_rect.width * 0.5;
            result.first.y = bounding_rect.y + bounding_rect.height * 0.5;
        }

//        cvDrawContours(image, contour, cvScalar(255, 0, 0), cvScalar(0, 0, 0), 0);

        contour = contour->h_next;
    }

    if (area_one == 0.f && area_two == 0.f)
        return false;


    IplImage* area_image(NULL);
    area_image = cvCreateImage(cvSize(image->width, image->height), image->depth, 3);

    if (!area_image) {
        std::cerr << "Unable to create image!" << std::endl;
        return false;
    }

    cvCircle(area_image, cvPoint(result.first.x, result.first.y), 60, cvScalar(0, 0, 255), 10);
    cvCircle(area_image, cvPoint(result.second.x, result.second.y), 60, cvScalar(0, 255, 0), 10);

    cvAdd(image, area_image, image);

//    cvShowImage("result1", threshold);
    cvShowImage("result2", image);
    cvWaitKey(27);

//    cvReleaseImage(&hsv);
    cvReleaseImage(&threshold);
//    cvReleaseImage(&area_image);


    return true;
}

}

