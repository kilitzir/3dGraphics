#include <gsp.h>
#pragma hdrstop
#include <conio.h>
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
/* Small interactive routine. It's used for debugging with the help
   of F7, F8, F4, ALT-4, CTRL-4, CTRL-F7 and option 8.
*/
//------------------------------------------------------------------------
void test1() {
point x1(0,0,0,1);
Ellipse a(x1,10,10);
a.show();
point x2(0, 0,20,1); //on z
point x3(0,10, 0,1); //on y
Ellipse b(x1,x2,x3);
b.show();
}
void test()
{

float f= NULL;
cerr << "...";
Line l;
Window(-50,50,-50,50);
SetViewport2(0,0,1,1);

// PERSPECTIVE
// OK
SetVPR(0,0,0);
SetVPN(0,0,-1);
SetVUV(0,1,0);
SetCOP(8,6,84);
ClippingFront = ClippingBack = FALSE;
SetWorld(PERSPECTIVE);


/**
// PERSPECTIVE
// OK
SetVPR(16,0,54);
SetVPN(-1,0,-1);
SetVUV(0,1,0);///!
SetCOP(8,6,84);
SetWorld(PERSPECTIVE);
**/
/**
// PARALLEL
SetVPR(16,0,54);
SetVPN(1,1,0);
SetVUV(0,1,0);///!
SetCOP(20,25,20);
SetDOP(-1,0,0);///!
SetWorld(PARALLEL);
**/
*CurrentTransformMatrix = I4_4;
*CurrentProjectMatrix = MakeProjectionMatrix();
RecalcViewMatrix();
int i=1;
float lmin,lmax,mmin,mmax ;
for (i=-1;i!=0;) {
gotoxy(1,1);
switch(i) {
case 1: outtextxy(100,200," VIEWPORT DOWNLEFT x,y, UPRIGHT x,y ");
        cin >> lmin >> lmax >> mmin >> mmax ;
        SetViewport2(lmin,lmax,mmin,mmax);
    break;

case 2: outtextxy(100,200," WINDOW DOWNLEFT x,y UPRIGHT x,y ");
        cin >> lmin >> lmax >> mmin >> mmax ;
        SetWindow(lmin,mmin,lmax,mmax);
   break;
case 3 :outtextxy(100,200," ROTATE THETA?");
         float theta;
         cin >> theta;
         *CurrentTransformMatrix  *= ROTATEZ3(theta);
         RecalcViewMatrix();

   break;
case 4 :outtextxy(100,200," SCALE SX,SY");
         float sx,sy;
         cin >> sx >> sy;
         *CurrentTransformMatrix  *= SCALE3(sx,sy,0);
         RecalcViewMatrix();
   break;
case 5 :outtextxy(100,200," TRANSLATE SX,SY");
         cin >> sx >> sy;
         *CurrentTransformMatrix  *= TRANSLATE3(sx,sy,0);
         RecalcViewMatrix();

   break;
case 6: cleardevice();
   break;
case 7: CurrentViewport->show();
    break;
case 8: *CurrentViewMatrix = I4_4;
        *CurrentProjectMatrix = MakeProjectionMatrix();
        RecalcViewMatrix();
    break;
}// switch
ShowSegment(SHAPE_HOUSE3);
outtextxy(100,100, " 1 viewport 2 window 3 ROTATE 4 SCALE 5 TRANSLATE 6 CLS");
cin >> i;

}// for
}// test