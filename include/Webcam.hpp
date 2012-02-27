#ifndef ST_WEBCAM
#define ST_WEBCAM

#include <cv.h>
#include <highgui.h>

namespace st {

class Webcam {
    public:
        Webcam();

        IplImage* get_image() const;

    private:
        CvCapture* capture_;
};

}

#endif //ST_WEBCAM
