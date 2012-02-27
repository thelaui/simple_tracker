#ifndef ST_SIMPLE_TRACKER
#define ST_SIMPLE_TRACKER

namespace st {

class Webcam;
class MarkerFinder;

class SimpleTracker {
    public:
        SimpleTracker();
        SimpleTracker(float fov, float marker_separation, float marker_height,
                      float hue);

        ~SimpleTracker();

        void set_fov(float fov);
        void set_marker_extents(float separation, float height);
        void set_marker_color(float hue);

        bool get_transform(float& pos_x, float& pos_y, float& pos_z,
                           float& rot_x, float& rot_y, float& rot_z) const;

    private:
        Webcam* webcam_;
        MarkerFinder* marker_finder_;

        float fov_, marker_separation_, marker_height_;

};

}

#endif // ST_SIMPLE_TRACKER
