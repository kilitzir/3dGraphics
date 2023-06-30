#include <gsp.h>
#pragma hdrstop
#include <stdlib.h>
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
/* friends of line / text / color .All the functions that have the word
   /**inline**/ can (and should) be inlined .
*/
//------------------------------------------------------------------------

//-----------------------------------------------------------------
//    L I N E   R O U T I N E S
//-----------------------------------------------------------------
//------A D D  L I N E
// This function should be called to add a line in the current segment.
// Note the MoveAbs3() at the end.

 /**inline**/  void AddLine(float x,float x1,float y,
			    float y1,float z,float z1)
// Add a line to the Current Segment
{
if (!CurrentLine) {
	    perror("ADDLINE CURRENTLINE==NULL");
	    CurrentLine = new Line;
}

CurrentLine->set_Line(x,x1,y,y1,z,z1);
AddSegmentRoutine(SEG_LINE,0);
MoveAbs3(x1,y1,z1);
}
//-----------------------------------------------------------------
//    P O L Y L I N E   R O U T I N E S
//-----------------------------------------------------------------
//------A D D   TO  P O L Y L I N E
// This function should be called to add a line in the current polyline.
// Note the MoveAbs3() at the end.

 /**inline**/  void Add2Poly(float x,float y,float z)
// Add a line to the Current PolyLine
{
if (!CurrentPolyline) {
	    perror("ADD2POLYLINE CURRENTPOLYLINE==NULL");
	    CurrentPolyline = new polyline(&x,&y,&z,1);
}
else CurrentPolyline->add(x,y,z);
MoveAbs3(x,y,z);
}
//------A D D  P O L Y L I N E
// This function should be called to add a polyline in the current segment.
// Note the MoveAbs3() at the end.
 /**inline**/  void AddPoly()
// Adds a polyline to the Current Segment
{
if (!CurrentPolyline) {
	perror("ADDPOLYLINE CURRENTPOLYLINE==NULL");
	CurrentPolyline = new polyline;
	return; // we can't do nothing !!!
}
else AddSegmentRoutine(SEG_POLYLINE,0);
}
//-----------------------------------------------------------------
//    T E X T   R O U T I N E S
//-----------------------------------------------------------------
//------T E X T
// This function should be called to add a text in the current segment.
// Note the CurrentText->reset() at the end .
void Text(const char *s)
{
if (!CurrentText) {
         perror ("TEXT CURRENTTEXT=NULL");
         CurrentText = new text;
}
CurrentText->add(s);
AddSegmentRoutine(SEG_TEXT,0);
CurrentText->reset();
}
//-----------------------------------------------------------------
//    C O L O R   R O U T I N E S
//-----------------------------------------------------------------
// This function should be called to add a color in the current segment.
// Note the CurrentLine->reset() at the end .
 /**inline**/  void Color(int Colour)
// Add color
{
if (!CurrentColor) {
	perror("COLOR: currentcolor was NULL !!!");
        CurrentColor = new color;
}

CurrentColor->set(Colour);
AddSegmentRoutine(SEG_COLOR,0);
CurrentColor->reset();
}
//-----------------------------------------------------------------
//  E L L I P S E S   R O U T I N E S
//-----------------------------------------------------------------
void AddEllipses(point x1,point x2,point x3) {
if (!CurrentEllipse) {
	perror("AddEllipse: CurrentEllipse = =NULL !!!");
	CurrentEllipse = new Ellipse(x1,x2,x3);
}
else
   CurrentEllipse->set(x1,x2,x3);
AddSegmentRoutine(SEG_ELLIPSES,0);
}
//---------------
void AddEllipses(point x1,float x2,float x3) {
if (!CurrentEllipse) {
	perror("AddEllipse: CurrentEllipse = =NULL !!!");
	CurrentEllipse = new Ellipse(x1,x2,x3);
}
else
   CurrentEllipse->set(x1,x2,x3);
AddSegmentRoutine(SEG_ELLIPSES,0);
}
//-----------------------------------------------------------------
//
//-----------------------------------------------------------------

