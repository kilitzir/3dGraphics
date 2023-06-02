#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
// Here the extern variables take space. Also we define the value of
// global variables.
//------------------------------------------------------------------------


#define MAIN
#include <gsp.h>
#include <stdlib.h>
#ifdef __BORLANDC__
	extern unsigned _stklen = (unsigned) 0x8f90;
#endif

void InitVariables()
{
int   x,y;
ScreenMaxX  = getmaxx();
ScreenMaxY  = getmaxy();

getaspectratio(&x,&y);

int aspect;
aspect = (x>=y?x:y);

AspectRatioX = x/(float)aspect;
AspectRatioY = y/(float)aspect;


COP.setm(0,0,0,1);
DOP.setm(0,0,0,1);
VPN.setm(0,0,0,1);
VPR.setm(0,0,0,1);
VPR.setm(0,0,0,1);
VPR.setm(0,0,0,1);
VUV.setm(0,0,0,1);

ProjectionType = PARALLEL;

CurrentLine     = new Line;
CurrentPolyline = new polyline;
CurrentSegment  = NULL;
CurrentText     = new text;
CurrentColor    = new color(DEFAULT_COLOR);
CurrentWindow   = new Window;
CurrentViewport = new Viewport;
CurrentEllipse  = new Ellipse;

CurrentTRMt             = new matrix4_4;
CurrentTRMs             = new matrix4_4;
CurrentTRMr             = new matrix4_4;
CurrentViewMatrix       = new matrix4_4;
CurrentProjectMatrix    = new matrix4_4;
CurrentTransformMatrix  = new matrix4_4;
*CurrentTRMt             = I4_4;
*CurrentTRMs             = I4_4;
*CurrentTRMr             = I4_4;
*CurrentViewMatrix       = I4_4;
*CurrentProjectMatrix    = I4_4;
*CurrentTransformMatrix  = I4_4;
SegmentNo = -1;

for (int i=0;i<MAX_SEGMENTS;i++)
       SegmentArray[i] = NULL;

ForwardDistance = -20;
BackwardDistance = 30;
noclipping = TRUE;
SetWorld(D3);
W2Vchanged = TRUE;
W2Vx = W2Vy = W2Va =  W2Vb = 1;
CurrentColour = WHITE;
debug = FALSE;
}