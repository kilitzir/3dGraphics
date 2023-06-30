#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
// Here we predefine some segments.
//------------------------------------------------------------------------

void Predefsegments()
{
                        // define square
OpenSegment(SHAPE_SQUARE);
MoveAbs2(0,0);
LineAbs2(1,0);
LineAbs2(1,1);
LineAbs2(0,1);
LineAbs2(0,0);
CloseSegment();
                        // define triangle
OpenSegment(SHAPE_TRIANGLE);
LineAbs2(1,0);
LineAbs2(0,1);
LineAbs2(0,0);
CloseSegment();
                        // define HOUSE
OpenSegment(SHAPE_HOUSE);
MoveAbs2(0,0);
LineAbs2(10,0);
LineAbs2(10,10);
LineAbs2(0,10);
LineAbs2(0,0);
MoveAbs2(0,10);
LineAbs2(5,15);
LineAbs2(10,10);
MoveAbs2(2,7);
AddSegment(SHAPE_SQUARE);
MoveAbs2(6,7);
AddSegment(SHAPE_SQUARE);
MoveAbs2(4,0);
Scale2(1.5,2.5);
AddSegment(SHAPE_SQUARE);
CloseSegment();
                        // DEFINE HOUSES in 2D
OpenSegment(SHAPE_HOUSES);
MoveAbs2(0,0);
AddSegment(SHAPE_HOUSE);
MoveAbs2(20,20);
AddSegment(SHAPE_HOUSE);
CloseSegment();
                        // HOUSE IN 3D
                        // as defined in page 304
OpenSegment(SHAPE_HOUSE3);
//draw front of house at z = 30
MoveAbs3(0,0,30);
LineRel2(16,0);
LineRel2(0,10);
LineRel2(-8,6);
LineRel2(-8,-6);
LineRel2(0,-10);
// draw face at z = 54
// It can also be done if we define the above as segment !
// 54 --> 54
MoveAbs3(0,0,54);
LineRel2(16,0);
LineRel2(0,10);
LineRel2(-8,6);
LineRel2(-8,-6);
LineRel2(0,-10);

// now connect front and rear faces
// We can also define the following 4 lines as a segment !
// 24 ->> 24
MoveAbs3(0,0,30);
 LineRel3(0,0,24);
MoveAbs3(16,0,30);
 LineRel3(0,0,24);

MoveAbs3(16,10,30);
 LineRel3(0,0,24);
MoveAbs3(8,16,30);
 LineRel3(0,0,24);

MoveAbs3(0,10,30);
 LineRel3(0,0,24);
 CloseSegment();
//-----------
			// DEFINE HOUSES in 3D
OpenSegment(14);
AddSegment(SHAPE_HOUSE3);
MoveAbs3(10,10,10);
Rotate3(45,45,45);
AddSegment(SHAPE_HOUSE3);
CloseSegment();
//-----------
Add2Poly(16,10,30);  // polyline segment
Add2Poly(16,10,54);
Add2Poly(8,16,30);
OpenSegment(99);
AddPoly();
CloseSegment();
ResetPoly();
//------------     // ellipses segment
OpenSegment(SHAPE_ELLIPSES);
Color(RED);
point x1(0,0,0,1);
AddEllipses(x1,10,10);
//point x2(0, 0,20,1); //on z
//point x3(0,10, 0,1); //on y
//AddEllipses(x1,x2,x3);
CloseSegment();
//-----------    C O N S T R U C T I N G
//-----------    the house given in cgp&p. Actually, it's the same
		//with the above.
OpenSegment(SHAPE_CGP_B_F);
// constructing the back in z=0,x=0;
// we could use 2d routines
MoveAbs3(  0, 0, 0);
LineRel3(-16, 0, 0); // 1->2
LineRel3(  0,10, 0); // 2->3
LineRel3( +8, 6, 0); // 3->4
LineAbs3(  0,10, 0); // 4->5
LineAbs3(  0, 0, 0); //  5->1
CloseSegment();
 // constructing the sides in x = 0,z=0;
OpenSegment(SHAPE_CGP_SIDE);
MoveAbs3(0, 0, 0);
LineRel3(0, 0,24);  //1->7
MoveAbs3(0,10, 0);
LineAbs3(0,10,24);  // 5->6
CloseSegment();
// constructing the roof in z=y=x=0;
OpenSegment(SHAPE_CGP_ROOF);
MoveAbs3(0,0,0);
LineRel3(0,0,24);
CloseSegment();
// constructing the house
//----------------------------------------------
OpenSegment(SHAPE_CGP_HOUSE);
		// constructing the front-back3
Color(RED);
MoveAbs3(16,0,30);
AddSegment(SHAPE_CGP_B_F);
Color(BLUE);
MoveAbs3(16,0,54);
AddSegment(SHAPE_CGP_B_F);
		// constructing the sides
Color(WHITE);
MoveAbs3(16,0,30);
AddSegment(SHAPE_CGP_SIDE);
Color(GREEN);
MoveAbs3(0,0,30);
AddSegment(SHAPE_CGP_SIDE);
Color(MAGENTA);
MoveAbs3(8,16,30);
AddSegment(SHAPE_CGP_ROOF);
CloseSegment();



}