#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
// Member functions of class viewport. The same as in window applies here.
/**
//-----------------------------------------------------------------
//                     V I E W P O R T
//-----------------------------------------------------------------

class Viewport {
matrix1_4 dl;  // Down Left
matrix1_4 ur;  // Up   Right

boolean setdl(matrix1_4 t1,matrix1_4 t2);
boolean setur(matrix1_4 t1,matrix1_4 t2);

public:
      Viewport();
      Viewport(float xmin,float xmax,float ymin,float ymax);
      Viewport(matrix1_4 x1,matrix1_4 x2);
void  V(float xmin,float xmax,float ymin,float ymax);
void  V(matrix1_4 x1,matrix1_4 x2);
void  set();
void  set(float xmin,float xmax,float ymin,float ymax);
void  set(matrix1_4 x1,matrix1_4 x2);
void  show();
float getXmin();
float getXmax();
float getYmin();
float getYmax();

};
**/
//------------------------------------------------------------------------
//------------
/**inline**/ void Viewport::V(matrix1_4 x1,matrix1_4 x2)
		       { Viewport temp = *this;
			 if (setdl(x1,x2) && setur(x1,x2))
			 W2Vchanged = TRUE;
			  else {
			  perror("Wrong parms in Viewport");
			  *this = temp;
			  }
			  //show();
		       }
/**inline**/ void Viewport::show() // It should show the viewport
			  {
			   matrix1_4 t1 = NDC2DC(ur),
				      t2 = NDC2DC(dl);
			   register int UpY,DownY,LeftX,RightX;
			   // We don't need aspect Ratio here
			   LeftX  = t2.get0(); DownY = t2.get1();
			   RightX = t1.get0(); UpY   = t1.get1();
			   UpY++;DownY--;
			   LeftX++;RightX--;
			   setcolor(LIGHTRED);
/***
			   putpixel(1,1,4);
			   putpixel(0,1,4);
			   putpixel(LeftX ,DownY,4);
			   putpixel(RightX,DownY,4);
			   putpixel(LeftX ,  UpY,4);
			   putpixel(RightX,  UpY,4);
***/
			   MyLine( LeftX,DownY,RightX,DownY);
			   MyLine(RightX,DownY,RightX,  UpY);
			   MyLine(RightX,  UpY, LeftX,  UpY);
			   MyLine( LeftX,  UpY, LeftX,DownY);
			  }
/**inline**/ void Viewport::V(float xmin,float xmax,float ymin,float ymax)
		     {
		     matrix1_4 t1(xmin,ymin,0,1),
			       t2(xmax,ymax,0,1);
		      V(t1,t2);
		     }

/**inline**/ void Viewport::Viewport()
              {
              dl.setm(0,0,0,1);
	      ur.setm(1,1,0,1);
              }
//------------
/**inline**/ void Viewport::Viewport(float xmin,float xmax,float ymin,float ymax)
	       {
	       V(xmin,xmax,ymin,ymax);
	       }
//--------------
/**inline**/ void Viewport::Viewport(matrix1_4 x1,matrix1_4 x2)
	       {
		 V(x1,x2);
	       }
//---------------- Set Down Left
/**inline**/ boolean Viewport::setdl(matrix1_4 t1,matrix1_4 t2)
		  {
		  if ( (t1.getx()<0) || (t1.gety()<0) ||
		       (t2.getx()<t1.getx()) || (t2.gety()<t1.gety()) )
			return(FALSE);
		  dl = t1;
		  return(TRUE);
		  }
//---------------- Set Up Right
/**inline**/ boolean Viewport::setur(matrix1_4 t1,matrix1_4 t2)
		  {
		    if ( (t2.getx()<0) || (t2.gety()<0) ||
		       (t2.getx()<t1.getx()) || (t2.gety()<t1.gety()) )
			return(FALSE);
		  ur = t2;
		  return(TRUE);
		  }
//-------------
/**inline**/ void Viewport::set(float xmin,float xmax,float ymin,float ymax)
               {
                 V(xmin,xmax,ymin,ymax);
               }
//-------------
/**inline**/ void Viewport::set(matrix1_4 t1,matrix1_4 t2)
               {
               V(t1,t2);
               }
//-------------
/**inline**/ float Viewport::getXmin()
               {
               return dl.getx();
               }
//-------------
/**inline**/ float Viewport::getXmax()
                {
                return ur.getx();
                }
//-------------
/**inline**/ float Viewport::getYmin()
               {
               return dl.gety();
               }
//--------------
/**inline**/ float Viewport::getYmax()
                {
                return ur.gety();
                }
