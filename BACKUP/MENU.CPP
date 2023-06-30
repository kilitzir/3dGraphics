#include <gsp.h>
#pragma hdrstop
#undef perror
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
extern int _wscroll;

//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
// The interactive routine.
//------------------------------------------------------------------------

//-----T Y P E D E F S
// proc that takes 3 floats and returns a 4_4 - used for taking transforma
// tions
typedef  matrix4_4 (f4_4)(float,float,float);

//-----P R O T O T Y P E S
int GraphicsScreen();
float Take1arg(char *s);
void Take2arg(float &x,float &y,char *s);
void Take3arg(float &x,float &y,float &z , char *s);

void Print1arg(float x);
void Print2arg(float x,float y);
void Print3arg(float x,float y,float z);
void Print3arg(matrix1_4 s1,char *s);

void TakeVxx(matrix1_4 &m,char *s);
matrix4_4 TakeTrans(f4_4 fff ,char *s,char add=1);
void TakePoint();
void DefaultValues();
//-----S T A T I C  V A R I A B L E S
/**static**/ int ShowedSegment;   // Segment no to be shown
/**static**/ int Indexy;          //
/**static**/ matrix1_4  PointR;   // Point of rotation
/**static**/ matrix1_4  PointS;   // Point of scaling

//------------H E L P   R O U T I N E S

void  DefaultValues()
// Give the default values
{
ShowedSegment = SHAPE_CGP_HOUSE;
SetWorld(PARALLEL);
*CurrentTRMt =*CurrentTRMs =*CurrentTRMr = I4_4;
//*CurrentTRMr = ROTATEY3(45);
PointR.setm(0,0,0,1);
PointS = PointR;
VPR.setm(8,8,29,1);
VPN.setm(1,1,1,1);
VUV.setm(0,1,0,1);
DOP.setm(0,0,1,1);
COP.setm(8,6,30,1);
SetWindow(-5,5,-5,5);
SetViewport2(.3,.5,.3,.5);
ForwardDistance = 80;
SetClippingFront(TRUE);
SetClippingBack(TRUE);
BackwardDistance =0;
*CurrentTransformMatrix = I4_4;
RecalcProjectionMatrix();
RecalcViewMatrix();
}
//--- Taking Arguments
float Take1arg(char *s)
{
float x;
puts(s);
scanf("%f",&x);
return x;
}
void Take2arg(float &x,float &y,char *s)
{
puts(s);
scanf("%f %f",&x,&y);
}
void Take3arg(float &x,float &y,float &z,char *s)
{
puts(s);
scanf("%f %f %f",&x,&y,&z);
}
//--- Print Arguments
void Print1arg(float x)
{
printf("%f\n",x);
}
void Print2arg(float x,float y)
{
printf("%f %f\n",x,y);
}
void Print2arg(float x,float y,char *s)
{
printf("%s\t\t %f %f\n",s,x,y);
}

void Print3arg(float x,float y,float z)
{
printf("%f   %f   %f\n",x,y,z);
}
void Print3arg(matrix1_4 s1,char *s)
{
printf("%s\t",s);
Print3arg(s1.getx(),s1.gety(),s1.getz());
}
template <class T>
void PrintWV(T t,char *s )
{
char ss[20];
strcpy(ss,s);
strcat(ss,"  DOWN-LEFT");
Print2arg(t.getXmin(),t.getYmin(),ss);
strcpy(ss,s);
strcat(ss,"  UP-RIGHT");
Print2arg(t.getXmax(),t.getYmax(),ss);
}

//---Taking input
void TakeVxx(matrix1_4 &m,char *s)
{
float x,y,z;
Take3arg(x,y,z,s);
m.setm(x,y,z,1);
RecalcProjectionMatrix();
RecalcViewMatrix();
}

template <class T>
void TakeWV(T &t,char *s )
{
float x1,y1,x2,y2;
char ss[20];
strcpy(ss,s);
strcat(ss," DOWN-LEFT");
Take2arg(x1,y1,ss);
strcpy(ss,s);
strcat(ss," UP-RIGHT");
Take2arg(x2,y2,ss);
t.set(x1,x2,y1,y2);
W2Vchanged = TRUE;
RecalcProjectionMatrix();
RecalcViewMatrix();
}

matrix4_4 TakeTrans(f4_4 fff ,char *s,char add)
{
float x,y,z;
matrix4_4 a;
Take3arg(x,y,z,s);
a =  fff(x,y,z);
if (add ) {
      *CurrentTransformMatrix = a * *CurrentTransformMatrix ;
      RecalcViewMatrix();
}
return a;
}

void TakePointR()
{
float x,y,z;
float thetax,thetay,thetaz;
Take3arg(x,y,z,"Point ? x y z");
Take3arg(thetax,thetay,thetaz," theta ? thetax thetay thetaz");
*CurrentProjectMatrix *= ROTATEPOINT3(x,y,z,thetax,thetay,thetaz);
RecalcViewMatrix();
}
void TakePointS()
{
float x,y,z;
float Sx,Sy,Sz;
Take3arg(x,y,z,"Point ? x y z");
Take3arg(Sx,Sy,Sz," scale ? Sx Sy Sz");
*CurrentTransformMatrix *= SCALEPOINT3(x,y,z,Sx,Sy,Sz);
RecalcViewMatrix();
}
int NullSegment()
{
for (int i=0;i<MAX_SEGMENTS;i++)
    if (SegmentArray[i] == NULL )
        return i ;
return -1;
}

void MakeSegment()
{
int x = NullSegment();

if (x == -1 )
    return;
OpenSegment(x);
printf("The new segment has a number of %2d\n",x);

for (;;) {
    x = Take1arg("Give the NO of Seg to add,-1 to exit.");
    if ( (x<-1) || (x>MAX_SEGMENTS) || (SegmentArray[x] == NULL) ) {
          perror("NULL SEGMENT");
	 // continue;
    }
    if (x == -1 )  {
          CloseSegment();
          return;
    }
    puts(" Give the matrixes for that segment\n");
    *CurrentTRMt = TakeTrans(TRANSLATE3,"TRANSLATE? x y z",0);
    *CurrentTRMr = TakeTrans(ROTATE3,"ROTATE thetax thetay thetaz",0);
    *CurrentTRMs = TakeTrans(SCALE3,"SCALE? Sx Sy Sz",0);
    AddSegment(x);
    *CurrentTRMt = *CurrentTRMr = *CurrentTRMs = I4_4;
}
}
//---------------- G R A P H I C S  S C R E E N
int GraphicsScreen()
{
int  c;

cleardevice();
setactivepage(0);
setvisualpage(0);
CurrentViewport->show();
ShowSegment(ShowedSegment);
for(;;) {
   gotoxy(27,24);
   printf("<1> for menu ,<2> for cls <99> for exit");
   scanf("%2d",&c);
   switch(c) {
   case 1 :setactivepage(1);
	    setvisualpage(1);
	    cleardevice();
	    return(0);
     break;// Not needed but better safe than sorry
   case 2 :cleardevice();
	    CurrentViewport->show();
	    ShowSegment(ShowedSegment);
     break;
   case 99:
	    return -1;
     break; // Not needed but better safe than sorry
   default :break;
   }// switch
ShowSegment(ShowedSegment);

}// For
}// menu();
//------------S C R E E N  M E N U
void ScreenMenu()
{
moveto(0,0);
gotoxy(1,1);
setcolor(3);
puts("1. VPR      11.Rotate         21. 2D           31.Show Segment.");
puts("2. VPN      12.Scale          22. Parallel     32.Made Segment.");
puts("3. VUV      13.Translate      23. Perspect.    33.List Segment.");
puts("4. COP      14.Point Rotate   24. ClipFront    34.Show Menu");
puts("5. DOP      15.Point Scalse   25. ClipBack     35.Show variables");
puts("6. Window   16.Zero Transf.   26. BackDistance 36.Debug mode.");
puts("7. Viewport 28.Clipping (T/F) 27. ForwDistance 41.Return");
}
//---------P R I N T   V A R I A B  L E S
void PrintVariables()
// Print all the variables
{
    puts("Current Values");
    Print3arg(VPR,"VPR");
    Print3arg(VPN,"VPN");
    Print3arg(VUV,"VUV");
    Print3arg(COP,"COP");
    Print3arg(DOP,"DOP");
    PrintWV(*CurrentWindow,"WINDOW" );
    PrintWV(*CurrentViewport,"VIEWPORT" );
    Print3arg(PointR,"POINT OF ROTATING");
    Print3arg(PointS,"POINT OF SCALING");
    puts(ProjectionType == D2 ?"2D" :
         ProjectionType == PARALLEL ? "PARALLEL" :"PERSPECTIVE");
    printf("CLIPPING FRONT/BACK On/Off\t %2d/%2d %2d\n",
		ClippingFront,ClippingBack,!noclipping);
    printf("FORWARD / BACKWARD DISTANCE\t%8.3f %8.3f\n",
	     (float)ForwardDistance,(float)BackwardDistance );
}
//--------- THE MAIN MENU
void menu()
{
int i;
DefaultValues();
i = 41;
do {
    switch (i) {
    case  1:TakeVxx(VPR,"VPR ? x y z");
      break;
    case  2:TakeVxx(VPN,"VPN ? x y z");
      break;
    case  3:TakeVxx(VUV,"VUV ? x y z");
      break;
    case  4:TakeVxx(COP,"COP ? x y z");
      break;
    case  5:TakeVxx(DOP,"DOP ? x y z");
      break;
    case  6:TakeWV(*CurrentWindow,"WINDOW" );
      break;
    case  7:TakeWV(*CurrentViewport,"VIEWPORT" );
      break;
    case 11:TakeTrans(ROTATE3 ,"ROTATE thetax thetay thetaz" );
      break;
    case 12:TakeTrans(SCALE3 ,"SCALE Sx,Sy,Sz");
      break;
    case 13:TakeTrans(TRANSLATE3 ,"TRANSLATE x1,y1,z1");
      break;
    case 14:TakePointR();
      break;
    case 15:TakePointS();
      break;
    case 16:*CurrentTransformMatrix = I4_4;
	    RecalcViewMatrix();
      break;

    case 21:SetWorld(D2);
	    RecalcProjectionMatrix();
	    RecalcViewMatrix();
      break;
    case 22:SetWorld(PARALLEL);
	    RecalcProjectionMatrix();
	    RecalcViewMatrix();
      break;
    case 23:SetWorld(PERSPECTIVE);
	    RecalcProjectionMatrix();
	    RecalcViewMatrix();
      break;
    case 24:SetClippingFront(!ClippingFront);
      break;
    case 25:SetClippingBack(!ClippingBack);
      break;
    case 26:BackwardDistance = Take1arg("BACK DISTANCE ?");
	    RecalcProjectionMatrix();
	    RecalcViewMatrix();
      break;
    case 27:ForwardDistance = Take1arg("FORWARD DISTANCE ?");
	    RecalcProjectionMatrix();
	    RecalcViewMatrix();
      break;
    case 28:noclipping = !noclipping;
      break;
   case 31:int x = Take1arg("Give the NO of Seg to show");
	  if ( (x<0) || (x>MAX_SEGMENTS) || (SegmentArray[x] == NULL) ){
	       perror("NULL SEGMENT");
	   }
	   else ShowedSegment = x;
       break;
   case  32:MakeSegment();
      break;
   case 33:for (int i=0;i<MAX_SEGMENTS;i++)
	       if (SegmentArray[i] != NULL)
		   printf(" [%3d] ",i);
	   printf("\n");
      break;
   case 36 :debug = !debug;
      break;
   case  41:
	    if (GraphicsScreen() == -1 )
		    return;
   case  34: ScreenMenu();
       break;
   case  42:exit(-1);
       break;
   case 35 :PrintVariables();
       break;
   // here we start by putting the parms on the book.
   case 244:
	    VPR.setm(0,0,0,1);
	    VPN.setm(0,0,-1,1);
	    VUV.setm(0,1,0,1);
	    COP.setm(.5,.5,1,1);
	    CurrentWindow->set(0,0,1,1);
	    W2Vchanged = TRUE;
	    SetWorld(PARALLEL);
	    RecalcProjectionMatrix();
	    RecalcViewMatrix();
       break;
   case 245:
	    VPR.setm(0,0,0,1);
	    VPN.setm(0,0,1,1);
	    VUV.setm(0,1,0,1);
	    COP.setm(8,6,84,1);
	    CurrentWindow->set(-50,50,-50,50);
	    W2Vchanged = TRUE;
	    SetWorld(PERSPECTIVE);
	    RecalcProjectionMatrix();
	    RecalcViewMatrix();
       break;
   case 246:
       break;
   case 2471:
       break;
   case 2472:
       break;
   case 248:
       break;
   case 2501:VPR.setm(0,0,0,1);
	     VPN.setm(0,0,1,1);
	     VUV.setm(0,1,0,1);
	     COP.setm(8,8,100,1);
	     CurrentWindow->set(-1,17,-1,17);
	     W2Vchanged = TRUE;
	     SetWorld(PARALLEL);
	     RecalcProjectionMatrix();
	     RecalcViewMatrix();
       break;
   case 2502:VPR.setm(0,0,54,1);
	     VPN.setm(1,0,0,1);
	     VUV.setm(0,1,0,1);
	     COP.setm(12,8,16,1);
	     CurrentWindow->set(-1,25,-1,25);
	     W2Vchanged = TRUE;
	     SetWorld(PARALLEL);
	     RecalcProjectionMatrix();
	     RecalcViewMatrix();
       break;
   case 251:
	     VPR.setm(16,0,54,1);
	     VPN.setm(0,1,0,1);
	     VUV.setm(-1,0,0,1);
	     COP.setm(12,8,30,1);
	     CurrentWindow->set(-5,-1,25,25);
	     W2Vchanged = TRUE;
	     SetWorld(PARALLEL);
	     RecalcProjectionMatrix();
	     RecalcViewMatrix();
       break;
   case 2521:
       break;
   case 2522:
       break;
   case 253:
       break;
   case 3141:
	     VPR.setm(0,0,54,1);
	     VPN.setm(-1,0,0,1);
	     VUV.setm( 0,1,0,1);//not needed.
	     DOP.setm(-1,0,0,1);
	     CurrentWindow->set(-5,25,-1,21);
	     W2Vchanged = TRUE;
	     SetWorld(PARALLEL);
	     RecalcProjectionMatrix();
	     RecalcViewMatrix();
       break;
   case 99: return;
    }//switch
    i = Take1arg("EPILOGH ?<34> menu , <35> variables <41> return <99> exit");

}while (TRUE);
}

