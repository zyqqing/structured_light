#include "three_step_phase_shift.h"
#include <cstdio>

void printMinMax(IplImage *img) {
    
    int w = img->width;
    int h = img->height;
    int step = w; 

    float  *ptr = (float *)img->imageData;
    int i;
    float min,max;
    min = 1e6;
    max = 1e-6;

    for (i = 0; i < h ; i++) {
    for (int j = 0; j < w; j++) {
        float val = (float)ptr[i*step+j*4];
        if(val<min) min = val;
        if(val>max) max = val;
    }

    }

    cout << "min: " << min << "\nmax: "<<max << endl;
    
}

void makeimg() {
    IplImage *img = cvCreateImage(cvSize(480,640),IPL_DEPTH_32F,1);
    
    int w = img->width;
    int h = img->height;
    int step = img->widthStep;
    uchar *ptr = (uchar *)img->imageData;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j< w; j++) {
            ptr[i*step+j*4] = 0.4;
        }
    }
    cvScale(img, img, 2, 0.5); 
    cvShowImage("white",img);
    cvWaitKey(0);
}



int main(int argc, const char *argv[])
{
    if(argc<4) {
        printf("too fewer arguments!");
        return -1;
    }
    
//    makeimg();
    IplImage *phase1 = cvLoadImage(argv[1]);
    IplImage *phase2 = cvLoadImage(argv[2]);
    IplImage *phase3 = cvLoadImage(argv[3]);

    ThreeStepPhaseShift decoder(phase1,phase2,phase3);

    cout << "main():" << __LINE__ << endl;

    decoder.phaseWrap();
    IplImage* wrappedPhase = decoder.getWrappedPhase();
    printMinMax(wrappedPhase);
    cvScale(wrappedPhase, wrappedPhase, 1, 0.5); 
    cvShowImage("wrapped phase",wrappedPhase);
    cvShowImage("phase1 gray",decoder.imgPhase1Gray);
    
    /*cout << "main():" << __LINE__ << endl;

    IplImage* imgColor = decoder.getColorImage();
    
    cout << "main():" << __LINE__ << endl;

    // scale image to 0..255
    printMinMax(wrappedPhase);
    cvNamedWindow("wrapped phase");
    cvShowImage("color image",imgColor);
    cvShowImage("phase1", phase1);
    cvShowImage("phase1 gray",decoder.imgPhase1Gray);
*/
    cvShowImage("phase1", phase1);
    cvWaitKey(0);

    return 0;
}
