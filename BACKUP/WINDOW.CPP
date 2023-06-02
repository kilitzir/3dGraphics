#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
/* Member functions of window routines.
   If the parms of window is changed, the variable W2Vchanged becomes
   TRUE , in order for W2Vx, W2Vy, W2Va, W2Vb to recalculate . For more
   look page ... . <SetX> and <SetY> are used as <set> in matrix .
   All member functions can be inlined .
*/
/**
//-----------------------------------------------------------------
//                       W I N D O W
//-----------------------------------------------------------------

class Window {
float   Xmin,Xmax,
        Ymin,Ymax;
boolean SetX,SetY;
public:
         Window();
         Window(float xmin,float xmax,float ymin,float ymax);
void     setY(float xmin,float xmax);
void     setX(float ymin,float ymax);
void     set(float xmin,float xmax,float ymin,float ymax);
float    getXmin();
float    getXmax();
float    getYmin();
float    getYmax();
boolean  checkb();
};
**/

//------------------------------------------------------------------------
//----------
/**inline**/ void Window::Window() {}
//----------
/**inline**/ void Window::Window(float xmin,float xmax,float ymin,float ymax)
             {
             setX(xmin,xmax);
             setY(ymin,ymax);
             W2Vchanged = TRUE;
             }
//----------
/**inline**/ void Window::setX(float xmin,float xmax)
             {
             Xmin = xmin;
             Xmax = xmax;
             SetX = TRUE;
             W2Vchanged = TRUE;
             }
//----------
/**inline**/ void Window::setY(float ymin,float ymax)
             {
             Ymin = ymin;
             Ymax = ymax;
             SetY = TRUE;
             W2Vchanged = TRUE;
             }
//----------
/**inline**/ void Window::set(float xmin,float xmax,float ymin,float ymax)
             {
             setX(xmin,xmax);
             setY(ymin,ymax);
             }
//----------
/**inline**/ boolean Window::checkb()   {
                            if (SetX && SetY)
                            return (SetX && SetY);
                            else perror("UNDEFINED WINDOW");
                            return(0);
                            }
//----------
/**inline**/ float  Window::getXmin()
               {
               checkb();
               return Xmin;
               }
//----------
/**inline**/ float  Window::getXmax()
               {
               checkb();
               return Xmax;
               }
//----------
/**inline**/ float  Window::getYmin()
               {
               checkb();
               return Ymin;
               }
//----------
/**inline**/ float  Window::getYmax()
               {
               checkb();
               return Ymax;
               }
//----------