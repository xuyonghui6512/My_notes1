/*2018.3.27
  made by Xuxuxu
  This class contains contents about how to 
  find the code form a picuture we have provided
  and pick up its ifo.
*/ 
#ifndef FIND_AND_PICK_H
#define FIND_AND_PICK_H

#include "common_include.h"
#include "my_bar_code.h"
//new include needed to use Zbar
#include <zbar.h>
using namespace zbar;       

namespace mybar_code
{
    class CodeDetect{
    public:
      CodeDetect(){}
      ~CodeDetect(){}
      static void Zbar_It(Mat& _img,Bar_code& _bar_code);
    };
}
#endif //FIND_AND_PICK_H