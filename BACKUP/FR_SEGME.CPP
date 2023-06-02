#include <gsp.h>
#pragma hdrstop
#include <alloc.h>
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
// Functions concernig the class segment. Some of them can be inlined. I
// leave it to the next programmer to do it ...
//------------------------------------------------------------------------

//-----------------------------------------------------------------
//    F R I E N D   O F   S E G M E N T   R O U T I N E S
//-----------------------------------------------------------------
//--------A D D  S E G M E N T   R O U T I N E
/* Adds classes to the current segment.
   Notes.
   1. When we add a new segment, we don't add an instance but an index
      to the SegmentArray.
   2. When we add a new segment, we also add the trm's for that segment.
      We also add the CP ( in the TRMt matrix) so as the added segment
      to start showing itsself at the current CP.
   3. If you want to add a new class, you are advised to take a close look
      to this function.
*/
void AddSegmentRoutine(int choise,int What)
{
segment    *ps = CurrentSegment;
boolean    bool = TRUE;
 if (ps == NULL) {
		       perror("AddSegmentRoutine:CurrentSegment = NULL!!!");
		       return;
		    }
switch (choise) {

case  SEG_LINE    :if (CurrentLine == NULL) {
			 perror("AddSegmentRoutine.SEG_LINE:NO LINE TO ADD !");
		       break;
                    }
		    if (ps->nol == 0)
                             ps->pl = (Line*) malloc(sizeof(Line));
                    else     ps->pl = (Line*) realloc(ps->pl,sizeof(Line) *
                                              (ps->nol+1));
                    ps->pl[ps->nol] = *CurrentLine;
                    ps->nol++;
                    AddSegmentRoutine(SEG_CHOISE,SEG_LINE);
                    CurrentLine->reset();
              break;
case SEG_POLYLINE   :if (CurrentPolyline == NULL) {
			 perror("AddSegmentRoutine.SEG_POLYLINE:NO POLYLINE TO ADD !");
		       break;
                    }
                    if (ps->noll == 0)
                             ps->pll = (polyline*) malloc(sizeof(polyline));
                    else     ps->pll = (polyline*) realloc(ps->pll,
                                        sizeof(polyline) * (ps->noll+1));
                    ps->pll[ps->noll] = *CurrentPolyline;
		    ps->noll++;
                    AddSegmentRoutine(SEG_CHOISE,SEG_POLYLINE);
		    CurrentPolyline->reset();
              break;
case SEG_TEXT       :if (CurrentText == NULL) {
			 perror("AddSegmentRoutine.SEG_TEXT:NO TEXT TO ADD !");
                         break;
                     }
                     if (ps->not == 0)
                             ps->pt = (text*) malloc(sizeof(text));
                    else     ps->pt = (text*) realloc(ps->pt,
                                        sizeof(text) * (ps->not+1));
                    ps->pt[ps->not] = *CurrentText;
		    ps->not++;
                    AddSegmentRoutine(SEG_CHOISE,SEG_TEXT);
                    CurrentText->reset();
              break;
case SEG_COLOR      :if (CurrentColor == NULL) {
			 perror("AddSegmentRoutine.SEG_COLOR:NO Color TO ADD !");
                         break;
		     }
                     if (ps->noco == 0)
                             ps->pco = (color*) malloc(sizeof(color));
                    else     ps->pco = (color*) realloc(ps->pco,
                                        sizeof(color) * (ps->noco+1));
                    ps->pco[ps->noco] = *CurrentColor;
                    ps->noco++;
                    AddSegmentRoutine(SEG_CHOISE,SEG_COLOR);
                    CurrentColor->reset();
              break;

case SEG_SEGMENT    : if  ( (( What>=0) && (What<=MAX_SEGMENTS)) &&
                         (SegmentArray[What] != NULL) )
		      {
                      if (ps->nos == 0) {
                             if (ps->ps != NULL)
				 perror ("AddSegmentRoutine.SEG_SEGMENT: IF  PS->PS != PS->NOS");
			     ps->ps = (int*) malloc(sizeof(int));
			     }
		    else     {
			      if (ps->ps == NULL)
				 perror ("AddSegmentRoutine.SEG_SEGMENT: ELSE PS->PS != PS->NOS");
                              ps->ps = (int*) realloc(ps->ps,
                                           sizeof(int) * (ps->nos+1));
                              }
                    ps->ps[ps->nos] = What;
                    ps->nos++;
                    // Making the new segment start at the CP point
                    // We copy it because we'll take it back afterwards
                    matrix4_4 x = TRANSLATE3(CPx,CPy,CPz);
                    matrix4_4 x1 = *CurrentTRMt;
                    *CurrentTRMt *= x;            //Translate3(CP.getx(),
                                                  // CP.gety(),CP.getz());
		    AddSegmentRoutine(SEG_TRMS_S,0);
                    AddSegmentRoutine(SEG_CHOISE,SEG_SEGMENT);
                    *CurrentTRMt = x1;

                      }
		      else perror("AddSegmentRoutine.SEG_SEGMENT: TRIED TO ADD A NULL SEGMENT ");
                break;
case SEG_TRMS_S     :// EACH TIME A SEGMENT IS ADDED THE 3 TRMS'S ARE ADDED
                     int k = (ps->nos)*3;

                     ps->TRMS_S = (matrix4_4*)(ps->TRMS_S == NULL
                                 ?  calloc(k,sizeof(matrix4_4))
                                 :  realloc(ps->TRMS_S,k*sizeof(matrix4_4))
                                 );
                       k = (((ps->nos)-1) * 3);
                   if (*CurrentTRMt == O4_4) {
                       bool = FALSE;
                       ps->TRMS_S[k] = I4_4;
                      }
                      else
			 ps->TRMS_S[k] = *CurrentTRMt;
                     k++;
                     if (*CurrentTRMr == O4_4)  {
                        bool = FALSE;
                       ps->TRMS_S[k] = I4_4;
                     }
                     else
			 ps->TRMS_S[k] = *CurrentTRMr;
                     k++;
                     if (*CurrentTRMs == O4_4) {
                       ps->TRMS_S[k] = I4_4;
			 bool = FALSE;
		     }
		     else
			 ps->TRMS_S[k] = *CurrentTRMs;
		     if (!bool)
			 perror (" AddSegmentRoutine:FOUND AN <0> TRM!");

		     *CurrentTRMt = *CurrentTRMr = *CurrentTRMs = I4_4;
   break;
case SEG_CHOISE     :if (ps->pc == NULL)
			     ps->pc = (int*) malloc(sizeof(int));
		    else     ps->pc = (int*) realloc(ps->pc,sizeof(int) *
						    (ps->noc+1));
		    ps->pc[ps->noc] = What;
		    ps->noc++;
	     break;
case  SEG_ELLIPSES  :if (CurrentEllipse == NULL) {
			 perror("NO Ellipse TO ADD !");
		       break;
		    }
		    if (ps->noel == 0)
			     ps->pel = (Ellipse*) malloc(sizeof(Ellipse));
		    else     ps->pel = (Ellipse*) realloc(ps->pl,sizeof(Ellipse) *
					      (ps->noel+1));
		    ps->pel[ps->noel] = *CurrentEllipse;
		    ps->noel++;
		    AddSegmentRoutine(SEG_CHOISE,SEG_ELLIPSES);
		    CurrentEllipse->reset();
	      break;

default            :perror("AddSegmentRoutine: caught a default :(");
	     break;

}
}
//-----------------------------------------------------------
//---O P E N   S E G M E N T
// Opens a new segment
void OpenSegment(int no)
{

 if (CurrentSegment != NULL ) {
    perror("THERE'S ALREADY AN OPENED SEGMENT");
    return;
 }
 if (SegmentArray[no] != NULL)
    perror("That number has already been defined");
CurrentSegment = new segment ;
SegmentNo = no;
CPx = CPy = CPz = 0;
*CurrentTRMt = *CurrentTRMs = *CurrentTRMr = I4_4;
}
//-----------------------------------------------------------
//--- C L O S E   S E G M E N T
// Closes the segment. You can see why the CurrentSegment must be
// a pointer to an object, rather than an instance.
void CloseSegment()
{
 if (CurrentSegment == NULL ) {
    perror("ATTEMPT TO CLOSE AN UNOPENED SEGMENT");
    return;
 }
 if (SegmentArray[SegmentNo] != NULL) {
    perror(" the segment already exists");
    delete (SegmentArray[SegmentNo]);
 }
 SegmentArray[SegmentNo] = CurrentSegment;
 CurrentSegment = NULL;
}
//-----------------------------------------------------------
void ShowSegment(int x)
//------S H O W   S E G M E N T
// Nothing partiqular with this function
{
 if ( (x<0) || (x>=MAX_SEGMENTS) || (!SegmentArray[x]))
     perror("SHOWSEGMENT WRONG NUMBER");
 else
    SegmentArray[x]->show();
}
