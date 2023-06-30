#include <gsp.h>
#pragma hdrstop
#include <conio.h>
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
/* Member functions of the color class.Note the color::show() .
   All the functions can be inlined .
*/
//------------------------------------------------------------------------
/**
//-----------------------------------------------------------------
//                     C O L O R
//-----------------------------------------------------------------
class color {
int Color;
public:
     color();
     color(int n);
void set(int n);
int  get();
void reset();
void show();
};
**/
//-----------------------------------------------------------------

/**inline**/ void color::color() {Color = DEFAULT_COLOR;}
/**inline**/ void color::color(int n) {Color = n;}
/**inline**/ void color::set(int n){Color = n;}
/**inline**/ int  color::get() {return Color;}
/**inline**/ void color::reset(){Color = DEFAULT_COLOR;}
/**inline**/ void color::show(){
			CurrentColour = Color;
		   }

