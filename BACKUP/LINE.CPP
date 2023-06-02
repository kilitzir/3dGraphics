#include <gsp.h>
#pragma hdrstop
#include <alloc.h>
#include <dos.h>
void MyLine(int x1,int y1,int x2,int y2);
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
/* The member functions for classes line, polyline.The function poluline::
   show has not implemented because the routine for clipping is too
   difficult to implement.
   Some functions can be inlined. At first I did that, but when I start
   debugging the program, it was frustrating to need to recompile all files
   for just one change.The functions that definetely can be inlined are
   those who have the /**inline**/ prefix in front.
*/
//------------------------------------------------------------------------
/**
//-----------------------------------------------------------------
//                     L I N E
//-----------------------------------------------------------------
class Line {
protected:
          point first,last;
public :
        Line();
void    set_Line(float x,float y,float z);
void    set_Line(float x1,float x2,float y1,float y2,
                 float z1,float z2);
        void reset();
void    show();
Line operator=(Line &b);
};
//-----------------------------------------------------------------
//                     P O L Y L I N E
//-----------------------------------------------------------------
class polyline {
point *p;
int   no_points;
point *plane[3];  // defines which entries define a plane;
matrix1_4 N; // matrix for the above Plane;
public :
        polyline();
        polyline(float x,float y,float z);
        polyline(float *x,float *y,float *z=NULL,int no=0);
void    add(float x,float y,float z);
void    reset();
void    show();
polyline operator=(polyline &g);
};
//-----------------------------------------------------------------
**/

void polyline::add(float x,float y,float z)
         {
         if (no_points == 0)
               p = (point*) malloc(sizeof(Line));
         else  p = (point*) realloc(p,sizeof(Line)*(no_points+1));
	 p[no_points].setm(x,y,z,1);
	 /* This is needed to bulid a polygon in one epipedo
	 if (plane[0] == NULL)       plane[0] = &p[no_points];
	 else if (plane[1] == NULL)     plane[1] = &p[no_points];
	      else if (plane[2] == NULL) {
		  N = (*plane[0]-*plane[1]) % (*plane[1] - p[no_points]);
		 if (N == O1_4)
		     {}
		 else
		     plane[2] = &p[no_points];
	      }
	 **/
	 no_points++;

	 }

//------------------
 void polyline::polyline(float *x,float *y,float*z,int no)
         {
         int i;
         for (i=0;i<no;i++)
           if (z == NULL) add(x[i],y[i],0);
           else           add(x[i],y[i],z[i]);
         }

//-----------------------------------------------------------------
//                     L I N E
//-----------------------------------------------------------------
/**inline**/ void  Line::Line()
           { }
//---------------
/**inline**/ void Line::set_Line(float x,float y,float z)
          {
            if (!first.checkb())
               first.setm(x,y,z,1);
            else
                if (!last.checkb())
                  last.setm(x,y,z,1);
                else perror("Line HAS BEEN DEFINED");
          }
/**inline**/ void Line::set_Line(float x1,float x2,float y1,float y2,
                float z1,float z2)
          {
          set_Line(x1,y1,z1);
	  set_Line(x2,y2,z2);
          }
/**inline**/ void Line::reset()
           {first.unsetb(); last.unsetb();}
/**inline**/ void Line::show()
	   {
	    matrix1_4 temp1 = homo2can(first* *CurrentViewMatrix),
		      temp2 = homo2can(last * *CurrentViewMatrix);
            if (ClipLine(temp1,temp2) ) {
                temp1 = WC2PC(temp1);
		MyLine(temp1.get0(),temp1.get1(),temp1.get2(),temp1.get3());
            }
           }
/**inline**/ Line Line::operator=(Line &b)
	    {
            b.first.checkb();
            b.last.checkb();
            first = b.first;
            last = b.last;
            return *this;
            }

//-----------------------------------------------------------------
//                     P O L Y L I N E
//-----------------------------------------------------------------
/**inline**/ void polyline::polyline()
	  { p = NULL;no_points = 0;}
//----------------
/**inline**/ void polyline::reset()
              {
               if (no_points)
               free(p);
               no_points = 0;
              }
//----------------
/**inline**/ polyline polyline::operator=(polyline &g)
             {
             if (no_points)
                 free(p);
             p = (point*) malloc(sizeof(point)*(g.no_points));
             no_points = g.no_points;
             memcpy(p,g.p,sizeof(point)*no_points);
	     return *this;
	     }
/**inline**/ void polyline::show()  {
		point *tempp = p, *plus1=p+1;
	    for (int i=0;i<no_points;
			 i++,tempp++,plus1 = (i == no_points-1?p:plus1+1)) {
		matrix1_4 temp1 = homo2can(*tempp * *CurrentViewMatrix),
			  temp2 = homo2can(*plus1 * *CurrentViewMatrix);
		if (ClipLine(temp1,temp2) ) {
			temp1 = WC2PC(temp1);
			MyLine(temp1.get0(),temp1.get1(),temp1.get2(),temp1.get3());
		}
		else cerr << "Problem Found !!!!" << endl;
	    }// for
	   }

//-----------------------------------------------------------------
// Draws a line, between 2 points
// Replaces the line() of TC++
//-----------------------------------------------------------------
void MyLine(int x1,int y1,int x2,int y2)
{
//line(x1,y1,x2,y2);
	//Compute the radius
float   DA = (x1*1.*x1+(x2*1.*x2)+(y1*1.*y1)+(y2*1.*y2));
float   cosu =  (x2-x1)/sqrt( DA ),
	sinu =  (y2-y1)/sqrt( DA );
int 	Ycoef,Xcoef;

Ycoef=Xcoef = 1;

if (sinu <0) {  //third && fourth tetarthmorio
       y1 = -y1;
       y2 = -y2;
       Ycoef = -1;
}
if (cosu <0 ) { //third && second tetarthmorio
	x1 = -x1;
	x2 = -x2;
	Xcoef = -1;
}
     if (x1==x2) {  // a horizontal line
	int tempX = x1*Xcoef;
	for (int i = y1;i<=y2;i++)
		putpixel(tempX,i*Ycoef,CurrentColour);

     }
     else {        // non-horizontal line
	int x,y,xend,Dx,Dy,D,Incr1,Incr2,
	l = 1;
	Dx = abs(x2-x1);
	Dy = abs(y2-y1);
	#define swap(x,y); {int temp=x;x=y;y=temp;}
	if (Dx < Dy){        // We must walk through y
	     swap(x1,y1);
	     swap(x2,y2);
	     swap(Dx,Dy);
	     swap(Xcoef,Ycoef);
	     l = 0;
	   }
	#undef swap(x,y);
	x=x1;
	y=y1;
	xend=x2;
	D  = 2*Dy - Dx;
	Incr1 = 2 * Dy;
	Incr2 = 2 * (Dy - Dx);
	 putpixel(l*x*Xcoef+(1-l)*y*Ycoef,
		 (1-l)*x*Xcoef+l*y*Ycoef,CurrentColour);
	   while (x<xend) {
		x++;
		if (D<0)
			D += Incr1;
		else {
			y++;
			D += Incr2;
		}
		putpixel(l*x*Xcoef+(1-l)*y*Ycoef,
			 (1-l)*x*Xcoef+l*y*Ycoef,CurrentColour);
	   }
    } // else
}
