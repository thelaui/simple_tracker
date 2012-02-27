#include "SimpleTracker.hpp"

#include <iostream>

int main() {
    st::SimpleTracker tracker(0.395, 13.f, 3.6f, 160.f);

    float x, y, z, rot_x, rot_y, rot_z;

    while (true) {
        if (tracker.get_transform(x, y, z, rot_x, rot_y, rot_z)) {
            std::cout << "\rx: " << x << " y: " << y << " z: " << z
                      << " rot_x: " << rot_x << " rot_y: " << rot_y << " rot_z: " << rot_z
                      << std::flush;
        } else {
            std::cerr << "\rUnable to get transform!" << std::endl;
        }

    }

    return 0;
}
