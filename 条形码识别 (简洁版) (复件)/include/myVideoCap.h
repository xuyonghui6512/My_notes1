#ifndef MYVIDEOCAP_H_
#define MYVIDEOCAP_H_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <sys/file.h>
  #include <string.h>
  #include <pthread.h>
  #include <linux/videodev2.h>
  #include <sys/ioctl.h>
  #include <sys/mman.h>
  #include <errno.h>
  #include <fcntl.h>
  #include <time.h>
  #include <sys/time.h>
  #include <signal.h>
//  #include <X11/Xlib.h>


  extern "C"
{

  #include "v4l2uvc.h"
}

using namespace cv;


namespace hitcrt
{



  class myVideoCap
  {
  public:
      myVideoCap(char *filename,int width=640,int height=480,int fps=30);
      ~myVideoCap();
      bool VideoGrab(Mat &dst);


  private:
      FILE *file = NULL;
      int format =V4L2_PIX_FMT_MJPEG;
      int ret;
      int grabmethod = 1;
      int width_ =640;
      int height_ =480;
      int fps_=30;
      struct vdIn *vd;
      Mat EncodedGraph;
  };




}



#endif // HITCRT_ROBOMASTERS_RUNE_H_
