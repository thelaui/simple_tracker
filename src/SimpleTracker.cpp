#include "SimpleTracker.hpp"

#include "Webcam.hpp"
#include "MarkerFinder.hpp"

#include <cmath>
#include <cv.h>

namespace st {

SimpleTracker::SimpleTracker():
    webcam_(new Webcam()),
    marker_finder_(new MarkerFinder()),
    fov_(0.f),
    marker_separation_(0.f),
    marker_height_(0.f) {}

SimpleTracker::SimpleTracker(float fov, float marker_separation, float marker_height, float hue):
    webcam_(new Webcam()),
    marker_finder_(new MarkerFinder(hue)),
    fov_(fov),
    marker_separation_(marker_separation),
    marker_height_(marker_height) {}

SimpleTracker::~SimpleTracker() {
    if (webcam_)
        delete webcam_;
    if (marker_finder_)
        delete marker_finder_;
}

void SimpleTracker::set_fov(float fov) {
    fov_ = fov;
}

void SimpleTracker::set_marker_extents(float separation, float height) {
    marker_separation_ = separation;
    marker_height_ = height;
}

void SimpleTracker::set_marker_color(float hue) {
    marker_finder_->set_color(hue);
}

bool SimpleTracker::get_transform(float& pos_x, float& pos_y, float& pos_z,
                                  float& rot_x, float& rot_y, float& rot_z) const {

    IplImage* image(webcam_->get_image());

    MarkerFinder::Result marker_data;
    if(!marker_finder_->process_image(image, marker_data))
        return false;

    float pixel_separation(std::sqrt(std::pow(marker_data.first.x - marker_data.second.x, 2) +
                                     std::pow(marker_data.first.y - marker_data.second.y, 2)));

    float scale(marker_separation_/pixel_separation);
    float width(image->width*scale);

    pos_z = width * 0.5f / std::tan(fov_*0.5f);
    pos_x = -scale * (0.5f * (marker_data.first.x + marker_data.second.x) - image->width * 0.5f);
    pos_y = -scale * (0.5f * (marker_data.first.y + marker_data.second.y) - image->height * 0.5f);

    rot_x = 0.f;
    rot_y = 0.f;

    float angle(0.f);
    if (marker_data.first.y > marker_data.second.y)
        angle = std::acos((marker_data.first.x - marker_data.second.x)/pixel_separation);
    else
        angle = std::acos((marker_data.second.x - marker_data.first.x)/pixel_separation);

    rot_z = angle > M_PI*0.5 ? angle-M_PI : angle;

    return true;

}

}
