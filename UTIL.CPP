#include <gsp.h>
#pragma hdrstop
#include <conio.h>
#include <process.h>
static const float pii = M_PI / 180;
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
// Miscelanus routines. Most of these functions can be inlined.
//------------------------------------------------------------------------
//----- W I N D O W   R O U T I N E S
/**inline**/  void window(float xmin,float xmax,float ymin,float ymax)
{
SetWindow(xmin,xmax,ymin,ymax);
}
/**inline**/  void SetWindow(float xmin,float xmax,float ymin,float ymax)
{
   if (CurrentWindow == NULL) {
       perror("SETWINDOW- CurrentWinodw found 0 !");
       CurrentWindow = new Window(xmin,xmax,ymin,ymax);
   }
   else
       CurrentWindow->set(xmin,xmax,ymin,ymax);
}
//-------- V I E W P O R T   R O U T I N E S
 /**inline**/ void SetViewport2(float xmin,float xmax,float ymin,float ymax)
{
if (!CurrentViewport) {
  perror("SETVIEWPORT2 CURRENTVIEWPORT = NULL");
  CurrentViewport = new Viewport;
}
CurrentViewport->set(xmin,xmax,ymin,ymax);
}
//----abs
// find the metro of a vector
/**inline**/ float abs(matrix1_4 t)
{
matrix1_4 x = t;
x.get3() = 0;
return sqrt(x*x);
}
//-----------------------------------------------------------------
//  T R A N S F O R M A T I O N   R O U T I N E S
//-----------------------------------------------------------------
/* Please note that the functions with CAPITAL letters should not be
   called directly when we make a segment. These functions are called
   internally. We call the functions which include small letters as well.
   Look at prototyp.h
   We assume that arc is in degrees.
*/
//----------- R O T A T E X 3
/**inline**/ matrix4_4 ROTATEX3(float arc)
{
matrix4_4 temp = I4_4;

if (fabs(arc) > 360 )
           perror("ROTATEY3 ARC>360 !");
float CosArc = cos(arc*pii);
float SinArc = sin(arc*pii);

temp.set_line(1,0,CosArc,SinArc);
temp.set_line(2,0,-SinArc,CosArc);
return(temp);
}
//------- R O T A T E Y 3
/**inline**/ matrix4_4 ROTATEY3(float arc)
{
matrix4_4 temp = I4_4;

if (fabs(arc) > 360 )
           perror("ROTATEY3 ARC>360 !");
float CosArc = cos(arc*pii);
float SinArc = sin(arc*pii);

temp.set_line(0,CosArc,0,-SinArc);
temp.set_line(2,SinArc,0,CosArc);

return(temp);
}
//------ R O T A T E Z 3
/**inline**/ matrix4_4 ROTATEZ3(float arc)
{
matrix4_4 temp = I4_4;


if (fabs(arc) > 360 )
           perror("ROTATEX3 ARC>360 !");

float CosArc = cos(arc*pii);
float SinArc = sin(arc*pii);

temp.set_line(0,CosArc,SinArc);
temp.set_line(1,-SinArc,CosArc);
return(temp);
}//-----------------------------------------------------------------
//----------   T R A N S L A T I O N
/**inline**/ matrix4_4 TRANSLATE3(float dx,float dy,float dz)
{
matrix4_4 temp = I4_4;
temp.set_line(3,dx,dy,dz,1);
return(temp);
}
//----------   S C A L I N G
/**inline**/ matrix4_4 SCALE3(float Sx,float Sy,float Sz)
{
matrix4_4 temp = I4_4;
temp.set_ij(0,0,Sx);
temp.set_ij(1,1,Sy);
temp.set_ij(2,2,Sz);
return(temp);
}

//------------ R O T A T I O N
/**inline**/ matrix4_4 ROTATE3(float thetax,float thetay,float thetaz)
{
matrix4_4 temp = I4_4;
if (thetax)
  temp = temp * ROTATEX3(thetax);
if (thetay)
  temp = temp * ROTATEY3(thetay);
if (thetaz)
  temp = temp * ROTATEZ3(thetaz);
  return(temp);
}
//-----------------------------------------------------------------
//        D E V I C E S   R O U T I N E S
//-----------------------------------------------------------------
 /**inline**/  void calcW2V(void)
// This routine is called when then parms for the window or viewport
// has changed. Look at page 154.
{
Viewport *pv = CurrentViewport;
float
      vXmax = pv->getXmax() , vXmin = pv->getXmin(),
      vYmax = pv->getYmax() , vYmin = pv->getYmin(),
      wYmax,wXmax,wXmin,wYmin;

      //we change only the window coords
if  (ProjectionType == PARALLEL) {
      wXmax = 1; wXmin = 0;
      wYmax = 1; wYmin = 0;
}
else if (ProjectionType == PERSPECTIVE){ //ok. here we have problems
	if (VPR1.getz() == -BackwardDistance) {
		perror("Clipping:VRP1 is wrong");
		BackwardDistance = VPR1.getz();
	}    // following page 295 && 301
//float zmin = (VPR1.getz() + ForwardDistance)/
//     (VPR1.getz() + BackwardDistance) ;
//	zmin = fabs((1-zmin)/zmin);

	wXmax = 1; wXmin = -1;
	wYmax = 1; wYmin = -1;
}
else  { //we are in 2d
      Window   *pw = CurrentWindow;
      wXmax = pw->getXmax() , wXmin = pw->getXmin(),
      wYmax = pw->getYmax() , wYmin = pw->getYmin();

}
if ((wXmax - wXmin)*(wYmax - wYmin)==0) {
	perror("CalcW2V: an error found");
	exit(0);
}
W2Vx = (vXmax - vXmin) /(wXmax - wXmin);

W2Vy = (vYmax - vYmin) /(wYmax - wYmin);

W2Va = - W2Vx*wXmin + vXmin; //pp 154
W2Vb = - W2Vy*wYmin + vYmin;

W2Vchanged = FALSE;
}
//-------------- W C 2 N D C
   inline   matrix1_4 WC2NDC(matrix1_4 s)
// Window coordinates 2 normalised device coordinates
// Page 154
// We know that WC2NDC is defined in 2d so
// We assume that 2 points are given in one matrix
// That speeds the execution because line-polyline,
// most of the times use 2 points !
{

if (W2Vchanged)
    calcW2V();
matrix1_4 temp(W2Vx*s.get0()+W2Va,W2Vy*s.get1()+W2Vb,
	       W2Vx*s.get2()+W2Va,W2Vy*s.get3()+W2Vb);
return(temp);
}
//-------------- N D C 2 D C
/**inline**/  matrix1_4 NDC2DC(matrix1_4 s)
// Normalised device coordinates 2 Device coordinates
// We have to put the aspect ratio - also to show the
// object accoarding that (0,0) is at bottom left.
// PC defines (0,0) is at up-left .
{
float Xmult = ScreenMaxX * AspectRatioX;// BC Optimization is gosty ...
float Ymult = ScreenMaxY * AspectRatioY;

 s.setm(s.get0()*Xmult,(1-s.get1())* Ymult,
         s.get2()*Xmult,(1-s.get3())* Ymult);
 return s ;
}
//------------- WC 2 P C
/**inline**/  matrix1_4 WC2PC(matrix1_4 s)
/* Device coordinates 2 pc coordinates
   It calls the above 2 routines.
   Question:Why not use only one routine ?
   Answer  :1. Add flexiblity
            2. Some functions are used independenly --> look viewport
            3. We can inline it and made it quicker.
*/
{
return NDC2DC(WC2NDC(s)) ;

}
//-----------------------------------------------------------------
//        I N I T I A L I S A T I O N  R O U T I N E S
//-----------------------------------------------------------------
//---O P E N  D E V I C E
// BC specific for entering to graphics
 /**inline**/ void OpenDev()
{
   // request auto detection
   int gdriver = DETECT, gmode, errorcode;
   // initialize graphics mode
   initgraph(&gdriver, &gmode, "");
   // read result of initialization
   errorcode = graphresult();

   if (errorcode != grOk)  // an error occurred
   {
      cerr << "Graphics error:" << grapherrormsg(errorcode) << endl;
      exit(errorcode);
   }
}
//--------------------
 /**inline**/ void CloseDev()
//---C L O S E  D E V I C E
// BC specific for closing to graphics
{
   closegraph();
   clrscr();
 cout << "This was created thanks 2 Chris K.\n" << endl;
}
//--------------------
