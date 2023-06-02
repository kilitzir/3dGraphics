#include <gsp.h>
#pragma hdrstop
#include <process.h>
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
// The routines for the ellipsis - circle.
//------------------------------------------------------------------------
/****
class Ellipse {
point len1,len2; // we need 3 points the define the ellipsis,in 3d
point Center;    // and in this way, we have it !;
float x_a,y_b;   //the 2 lengths of the ellipsis
matrix4_4 elC2WC;// the tran matrix, from ellipse's coordinates to world
public:	         // coordinates
	Ellipse();
	Ellipse(point CenterP,point len1P,point len2P);
	Ellipse(point CenterP,float a,float b);
	~Ellipse();
void    show();
void    reset();
private: // used by the show, to show the regions
void stage_1(float a,float b,int l,int &x, int &y);
void stage_2(float a,float b,int l,int x, int y);
void CalcMatrix(); //calcs the elC2WC
void putpoint(float x, float y);  // calcs the ElC2WC 2 PC, it does the clipping
				  // puts the pixel.
};
****/
void Ellipse::set(point CenterP,point len1P,point len2P) {
		Center = homo2can(CenterP);
		if (len1P*len2P != 0) {
			perror("ellipse::ellipse:not vertical vectors");
			x_a = y_b = 0;
			return ;
		}

		len1 = homo2can(len1P);
		len2 = homo2can(len2P);
		point p1 = len1P - CenterP,
		      p2 = len2P - CenterP;
		p1.getw() = p2.getw() = 1;

		x_a = abs(p1 * p1); // returns the differrences
		y_b = abs(p2 * p2);
		CalcMatrix();
}

void  Ellipse::set(point CenterP,float a,float b) {
	    Center=homo2can(CenterP);
	    x_a = a; y_b = b;
	    len2 = len1 = CenterP;
	    len1.getx() += x_a;
	    len2.gety() += y_b;
	    CalcMatrix();
	    }

void Ellipse::Ellipse() {
	x_a = y_b = 0;
	}

void Ellipse::Ellipse(point CenterP,point len1P,point Len2P) {
	set(CenterP, len1P, Len2P);
}
void Ellipse::~Ellipse(){}
void Ellipse::Ellipse(point CenterP,float a,float b) {
	set(CenterP,a,b);
}
void Ellipse::show() {
	       if  ( (x_a==0) || (y_b==0) ) //you never know ....
	       return;
/***           {  // playing with the BC
	       int x = x_a;
	       int y = y_b;
	       int oldc = getcolor();
	       setcolor(WHITE);
	       ellipse(0,0,0,360,x,y);//(int)x_a,(int)y_b);
	       setcolor(oldc);
	       }
***/
	       if (x_a >y_b) {
			int x,y;
			stage_1(x_a,y_b,1,x,y);
			stage_2(x_a,y_b,1,x,y);
	       }
	       else  {
			int x,y;
			stage_1(y_b,x_a,0,x,y);
			stage_2(y_b,x_a,0,x,y);
	       }
}// ellipse::show
void Ellipse::reset() { x_a = y_b = 0;}

void Ellipse::stage_1(float a,float b,int l,int &x, int &y) {
// implements the first stage ....
 x = 0;
 y = b;
 float a2 = a*a;
 float b2 = b*b;
 float d1 = b2 - a2*b + a2/4.0;
 putpoint(x*l  + (1-l)*y,
	  l*y  + x*(1-l));
 while (a2*(y-.5) >= b2*(x+1)) {
    if (d1<=0) {
	d1 += b2*(2*x+3);
	++x;
    }
    else {
       d1 += b2*(2*x+3) + a2*2*(1-y);
       ++x;
       --y;
    }
    putpoint(x*l + (1-l)*y,
	     l*y + x*(1-l));
 }// while
 }//stage_1

// implements the second stage ....
void Ellipse::stage_2(float a,float b,int l,int x, int y) {
	float a2 = a*a;
	float b2 = b*b;

	putpoint(x*l + (1-l)*y,
		 l*y + x*(1-l));
	float d2 = b2*pow(x+.5,2)+a2*pow(y-1,2) - a2*b2;
	while (y>0) {
		if (d2<=0) {
			d2 += 2*b2*(x+1) + a2*(3-2*y);
			++x;
			--y;
		}
		else {
			d2 += a2*(3-2*y);
			--y;
		}
		putpoint(x*l + (1-l)*y,
			 l*y + x*(1-l));
       }//while

}//stage_2
//------------------------------------------------------------------------
// makes a matrix, that transform the ellipses form its plane to
// the origin. It returns the inverse matrix, which is used to transform
// the points given by the show routine.
//------------------------------------------------------------------------
void Ellipse::CalcMatrix() {
//let's first find the matrices, and then we play games.
// we assume len1 is going to x axis, and len2 is going to y axis.

// we translate to the origin.
matrix4_4 m1 = TRANSLATE3(-Center.get0(),-Center.get1(),-Center.get2());

// we rotate along y axis so that the len1p sits on the yx plane, thus minimizing the z coord
// of len1.
//we don't forget that LenxxxP were points, but now they are also vectors!!!
matrix1_4 t1 = len1 * m1;
matrix1_4 t2 = len2 * m1;
float D = t1.getx()*t1.getx() + t1.getz()*t1.getz();
float thetay = 180/M_PI* acos (t1.getx()/sqrt(D));
matrix4_4 m2 = ROTATEY3(thetay);

// Now, we will attach len1 to the x axis => rotate along z axis.
t1 = t1 * m2;
t2 = t2 * m2;
D = t1.getx()*t1.getx()+t1.gety()*t1.gety();
float thetaz = 180/M_PI*acos(t1.getx()/sqrt(D));
matrix4_4 m3 = ROTATEZ3(thetaz);

// it's time to deal with len2 (now called t2). Where is it?? it should be
// either in y axis or z axis, because the two vectors are vertical.
// let's see what's going on. Either way, we rotate along x axis.
t1 = t1 * m3;
t2 = t2 * m3;
matrix4_4 m4;
float thetax;
#define sign(x) ( (x)>0?1:-1)
if (t2.getz() != 0 )    // ok, we know where we are, we hope !!!
     thetax = M_PI_2 * sign(-t2.getz()); // don't forget right-handed coord's
#undef sign(x)
else if (t2.gety() < 0 )
     thetax = M_PI;
     else if (t2.gety()>0)
     thetax = 0;

m4 = ROTATEX3(thetax);
t1 = t1 * m4;
t2 = t2 * m4;
// why are we doing this?? who cares about debugging???
// t1 should be in x axis
#define small(x) ( abs(x) >1e-6?FALSE:TRUE)
if ( (t1.getx()>=0) && small(t1.gety()) && small(t1.getz()) )
;
else perror("Ellipse::calcmatric: len1 didn't make it!\n");
if ( (t2.getx()==0) && small(t1.gety()) && small(t1.getz()) )
;
else perror("Ellipse::calcmatric: len2 is MIA!\n");

// let's make the return matrix. don't forget that we apply them in the
// reverse order, and reverse signs !!!

elC2WC = ROTATEX3(-thetax) * ROTATEZ3(-thetaz) * ROTATEY3(-thetax)
	 * TRANSLATE3(Center.getx(),Center.gety(),Center.getz());
// hopefully, this is the end.
}
//------------------------------------------------------------------------
// takes the x,y coords in ellipses coordinates, puts it in World
// coordinates, does the clipping, transforms it to PC coords and (Oyf!)
// displays it . actually is more easier to see it.
//------------------------------------------------------------------------
void Ellipse::putpoint(float x, float y) {
	for (int i=-1;i<=1;i+=2) //i= -1,1
	   for (int j=-1;j<=1;j+=2)  {//j= -1,1
		point  a(x*i,y*j,0,1);
		point a1 = a * elC2WC ;
		point a2 = homo2can(a1 * *CurrentTransformMatrix);
		point a3 = homo2can(a2 * *CurrentProjectMatrix);
		if ( ClipLine(a3,a3) ) {
		point c = WC2PC(a3);
		  putpixel(c.getx(),c.gety(),CurrentColour);
		}
	   }

}



