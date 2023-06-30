#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
/* The clipping routines.There are 3 clipping routines , 1 for 2d
   1 for perspective and one for parallel. Clipping parallel uses
   the 2d clipping because it's identical for x,y. For more info.
   for the clipping methods look pages 144-149 and 295-297.
*/

//------------------------------------------------------------------------

//- CLIPPING DEFINES
#define Above   1
#define Below   2
#define Right   4
#define Left    8
#define Front  16
#define Back   32

#define PointAbove(p)  ((p) & Above)
#define PointBelow(p)  ((p) & Below)
#define PointRight(p)  ((p) & Right)
#define PointLeft(p)   ((p) & Left)
#define PointFront(p)  ((p) & Front)
#define PointBack(p)   ((p) & Back)

#define OUTCODE_1(x,min,max,op_min,op_max) \
              (x<min?op_min:0) | (x>max?op_max:0)

#define  OUTCODE2D(x,y)        OUTCODE_1(x,xmin,xmax,Left,Right) |\
                               OUTCODE_1(y,ymin,ymax,Below,Above)
#define OUTCODE3D(x,y,z)       OUTCODE2D(x,y) | \
                               OUTCODE_1(z,zmin,zmax,Back,Front)



#define InsideWindow2d(p)   ((p) == 0)
#define InsideWindow3dpl(p) InsideWindow2d(p)

#define RejectCheck2d(p1,p2)     (((p1) & (p2)) != 0)
#define RejectCheck3dpl(p1,p2)   RejectCheck2d(p1,p2)

#define AcceptCheck2d(p1,p2)   ( (InsideWindow2d(p1)) &&\
                                 (InsideWindow2d(p2)) )
#define AcceptCheck3dpl(p1,p2)  AcceptCheck2d(p1,p2)

/** defines for perspective
    Outcode is different
    above/below , right/left, behind/front)
**/
#define OUTCODE3DP(x,y,z)  OUTCODE_1((y),(-z),(z),Below,Above) | \
			   OUTCODE_1((x),(-z),(z),Left,Right) | \
			   OUTCODE_1((z),zmin,zmax,Front,Back)
// if we don't have clipping in front & back
#define UnsetClip_1(p,clip,unset) ((clip) ? (p) : (p) & (~unset))
#define UnsetClip(p) ( UnsetClip_1(p,ClippingFront,Front) | \
		       UnsetClip_1(p,ClippingBack,Back)\
		     )
//------------------------------------------------------------------------
//-------- C L I P   L I N E S   I N   2 D
boolean  ClipLine2(matrix1_4 &mx1,matrix1_4  mx2)
{
int OutCode1,OutCode2;
boolean accept,reject,done;
float x1,x2,y1,y2,xmax,ymax,xmin,ymin;
int count = 0;

mx1 = homo2can(mx1);
mx2 = homo2can(mx2);

x1 = mx1.getx();
x2 = mx2.getx();
y1 = mx1.gety();
y2 = mx2.gety();


accept = reject = done = FALSE;
if (!CurrentWindow)
{
     perror("Clipline2:CurrentWindow === NULL!!!");
     return FALSE;
}

xmin = CurrentWindow->getXmin();
xmax = CurrentWindow->getXmax();
ymin = CurrentWindow->getYmin();
ymax = CurrentWindow->getYmax();


do {
   count ++;
   if (count > 500) {
		     perror("Clipping2D Eroor: MORE THAN 500 ITERATIONS");
                          return(FALSE);
                    }
   OutCode1 = OutCode2 = 0;// Needed ?
   OutCode1  = OUTCODE2D(x1,y1);
   OutCode2  = OUTCODE2D(x2,y2);
   // If trivially reject
   reject = RejectCheck2d(OutCode1,OutCode2);
   if (reject) { done = TRUE;break;}
   // If trivially accept
   accept = AcceptCheck2d(OutCode1,OutCode2);
   if (accept) { done = TRUE;break;}
   // Make sure P1 is outside
   if (InsideWindow2d(OutCode1))
   { swap(x1,x2);swap(y1,y2);swap(OutCode1,OutCode2);}
        char ll = (PointRight(OutCode2));
   if (PointAbove(OutCode1)) {
      if (y2 != y1)
          x1= x1 + ((x2-x1) * (ymax-y1)/(y2-y1));
      y1 = ymax;
   }
   else if (PointBelow(OutCode1)) {
            if (y2 != y1)
               x1= x1 + ((x2-x1) * (ymin-y1)/(y2-y1));
            y1 = ymin;
        }
   else if (PointRight(OutCode1) ) {
          if (x2 != x1)
		 y1 = y1 + ((y2-y1) * (xmax-x1)/(x2-x1));
           x1 = xmax;
        }
   else if (PointLeft(OutCode1)) {
          if (x2 != x1)
                 y1 = y1 + ((y2-y1) * (xmin-x1)/(x2-x1));
           x1 = xmin;
        }
}//repeat
while (!done);
if (accept)
{
mx1.setm(x1,y1,x2,y2);
return TRUE;
}
return FALSE ;
}
//------------------------------------------------------------------------
//                     P A R A L L E L   C L I P P I N G
//------------------------------------------------------------------------
inline boolean AcceptCheck3dplz(int p1,int p2)
// we see if we are OK with Z axis
{
#define k1  (Front | Back)
#define k2  (p1 & k1)
#define k3  (p2 & k1)
#define ret  p1 | p2

return ret;

#undef k1
#undef k2
#undef k3
#undef ret
}
//-----------------------
boolean  ClipLineParallel (matrix1_4 &mx1,matrix1_4  mx2)
/** Clipping for parallel projection
    We use the ClipLine2 for the x,y
    Here we just clip for z .
    **/
{
int OutCode1,OutCode2;
boolean accept,reject,zaccept,done;
float x1,x2,y1,y2,z1,z2,xmin,xmax,ymin,ymax,zmin,zmax;
int count = 0;

mx1 = homo2can(mx1);
mx2 = homo2can(mx2);

x1 = mx1.getx();
y1 = mx1.gety();
z1 = mx1.getz();

x2 = mx2.getx();
y2 = mx2.gety();
z2 = mx2.getz();
if (noclipping) {
   mx1.setm(x1,y1,x2,y2);
   return TRUE;
}
		  // default for parallel projection
xmin = ymin = zmin = 0;
xmax = ymax = zmax = 1.0;
accept = reject = done = FALSE;

do {
   count ++;
   if (count > 500) {
		     perror("Clipping2dP Error:more than 500 iterations");
			  return(FALSE);
                    }
   OutCode1 = OUTCODE3D(x1,y1,z1);
   OutCode2 = OUTCODE3D(x2,y2,z2);
   OutCode1 = UnsetClip(OutCode1);
   OutCode2 = UnsetClip(OutCode2);
                                           // If trivially reject
   reject = RejectCheck3dpl(OutCode1,OutCode2);
   if (reject) { done = TRUE;break;}
					   // If trivially accept
   accept = AcceptCheck3dpl(OutCode1,OutCode2);
   if (accept) { done = TRUE;break;}
   zaccept = AcceptCheck3dplz(OutCode1,OutCode2);
   if (zaccept) { done = TRUE;break;}
                                           // Make sure P1 is outside
   if (InsideWindow3dpl(OutCode1))
   { swap(x1,x2);swap(y1,y2);swap(z1,z2);swap(OutCode1,OutCode2);}

   char ll = (PointRight(OutCode2));
   float z2_z1 = z2 - z1;

   if (PointFront(OutCode1)) {
   if (z2_z1) {
          float a  =  (-z1) / (z2_z1);
          x1= x1 + ((x2-x1) * a);
          y1= y1 + ((y2-y1) * a);
      }
      z1 = zmax;
   }
   else if (PointBack(OutCode1)) {
            if (z2_z1) {
            float a = (1-z1)/(z2-z1);
	       x1= x1 + ((x2-x1) * a);
               x1= x1 + ((y2-y1) * a);
            }
            z1 = ymin;
        }

}while (!done);


if (accept)  { // if it's trivially accept
   mx1.setm(x1,y1,x2,y2);
   return TRUE;
}
else if (zaccept) { // the z coordinate is ok->search the others
			  // Save the old window
	Window t1(0,1,0,1),
	       t2 = *CurrentWindow;
	*CurrentWindow = t1;
			 // Prepare the mx1,mx2;
	mx1.setm(x1,y1,0,1);
	mx2.setm(x2,y2,0,1);
	boolean xyaccept = ClipLine2(mx1,mx2);
			// mx1 holds the 2 values we want that
			// Restore the old window
	*CurrentWindow = t2;
	return(xyaccept);
     }
else
    return FALSE ;
}
//------------------------------------------------------------------------
//           P E R S P E C T I V E   C L I P P I N G
//------------------------------------------------------------------------
boolean ClipLinePerspective(matrix1_4 &mx1,matrix1_4  mx2)
{
int OutCode1,OutCode2;
boolean accept,reject,done;
float x1,x2,y1,y2,z1,z2,zmin,zmax;
int count = 0;

mx1 = homo2can(mx1);
mx2 = homo2can(mx2);

x1 = mx1.getx();
y1 = mx1.gety();
z1 = mx1.getz();

x2 = mx2.getx();
y2 = mx2.gety();
z2 = mx2.getz();
if (noclipping) {
   mx1.setm(x1,y1,x2,y2);
   return TRUE;
}
	 // in pespective x = � z , y = �z , z = zmin,z = 1;
	 // we can only define zmin ;
zmin = ( VPR1.getz()+ForwardDistance)/(VPR1.getz()+BackwardDistance);
zmax = 1.0;
if (zmin>=zmax) {
     perror("ClipLinePerspective:zmin>=zmax!?!");
     return FALSE;
}
accept = reject = done = FALSE;

do {
   count ++;
   if (count > 500) {
		     perror("Clipping3DP error:More than 500 iterations");
			  return(FALSE);
		    }
   OutCode1 = OutCode2 = 0;                  // Not needed but ...
   OutCode1 = OUTCODE3DP(x1,y1,z1);
   OutCode2 = OUTCODE3DP(x2,y2,z2);
   OutCode1 = UnsetClip(OutCode1);
   OutCode2 = UnsetClip(OutCode2);

                                           // If trivially reject
   reject = RejectCheck3dpl(OutCode1,OutCode2);
   if (reject) { done = TRUE;break;}
                                           // If trivially accept
   accept = AcceptCheck3dpl(OutCode1,OutCode2);
   if (accept) { done = TRUE;break;}
                                           // Make sure P1 is outside
   if (InsideWindow3dpl(OutCode1))
      { swap(x1,x2);swap(y1,y2);swap(z1,z2);swap(OutCode1,OutCode2);}
	if (PointAbove(OutCode1)) { //y>z
	   float t1 = (y2-y1) - (z2-z1) ;
	   if (t1) {
	      float t2 = (z1-y1)/t1;
	      x1 = ( (x2-x1) * t2) + x1;
	      y1 = ((y2-y1) * t2) + y1; /** Possible bug . We might want
					     z1  = y1 inside the if(t1)
					     and out the y1 = z1;
					  **/

	   }
	   z1 = y1 ;
	}
   else if (PointBelow(OutCode1)) {  //y<-z  C
	   float t1 = (y2-y1)+ (z2-z1) ;
	   if (t1) {
	      float t2 = (-1) * (z1+y1)/t1;
	      x1 = ( (x2-x1) * t2) + x1;
	      y1 = ((y2-y1) * t2) + y1;
	   }
	   z1 = - y1 ;
	}
   else if (PointRight(OutCode1) ) { //x>z
	   float t1 = (x2-x1) - (z2-z1) ;
	   if (t1) {
	      float t2 = (z1-x1)/t1;
	      x1 = ( (x2-x1) * t2) + x1;
	      y1 = ((y2-y1) * t2) + y1;
	   }
	   z1 = x1 ;
	}
   else if (PointLeft(OutCode1)) { // x<-z  C
	   float t1 = (x2-x1)+ (z2-z1) ;
	   if (t1) {
	      float t2 = (-1) * (z1+x1)/t1;
	      x1 = ( (x2-x1) * t2) + x1;
	      y1 = ((y2-y1) * t2) + y1;
	   }
	   z1 = - x1 ;

	}
   else if (PointFront(OutCode1)) { //z<zmin
	float t1= z2-z1;
	if (t1) {
	      float t2 = (zmin-z1)/t1;
	      x1 = ((x2-x1) * t2) + x1;
	      y1 = ((y2-y1) * t2) + x2;
	}
	z1 = zmin;
	}
   else if (PointBack(OutCode1)) { //z>1
	float t1= z2-z1;
	if (t1) {
	      float t2 = (1-z1)/t1;
	      x1 = ((x2-x1) * t2) + x1;
	      y1 = ((y2-y1) * t2) + x2;
	}
	z1 = 1;

	}
}while (!done);


if (accept)  {
   mx1.setm(x1,y1,x2,y2);
   return TRUE;
}
else
    return FALSE ;
}

