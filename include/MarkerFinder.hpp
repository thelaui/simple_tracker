#ifndef ST_MARKER_FINDER
#define ST_MARKER_FINDER

#include <utility>
#include <cv.h>

namespace st {

class MarkerFinder {
    public:

        struct ResultMarker {
            float x,y, height;
        };

        typedef std::pair<ResultMarker, ResultMarker> Result;

        MarkerFinder();
        MarkerFinder(float hue);

        void set_color(float hue);
        bool process_image(IplImage* image, Result& result);

    private:
        std::pair<ResultMarker, ResultMarker> last_result_;

        float hue_;
};

}

#endif //ST_MARKER_FINDER

