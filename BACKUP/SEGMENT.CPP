#include <gsp.h>
#pragma hdrstop

//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
/* Member classes of class segment. Please try to understand the
   segment::show(), especially the case SEG_SEGMENT.
   Function ShowClass is also important. When you add a new class to
   segment, it must have a member function show() which will show
   the results to graphic screen.
   What to do to add a new graphics class to segment class.
   1.Make sure that the folowing functions are defined :
      a) xxxx::reset();
      b) xxxx::show();
   2. If you add operators make sure you add the boolean <set> in data.
      It's life saving in debug mode.
   4.Define the folowing new variables to class segment:
      a) xxxx *pxxx; //A pointer to the classes xxx;
      b) int  noxxx; // No of elements pointed by pxxx;
   3.Define the SEG_xxx in GSP.H .
   4.Define a Extern *Currentxxxx in vars.h
   5.Add the folowing lines in class segment
     a) xxxx *pxxx; // This will show to the current xxx
     b) pxxx-reset() // optional.
   6.Change the routine segment::segment();
   6.Add a function Xxxx in Util.cpp. Follow the guidelines of Color(int)
   7.Add a case in function AddSegmentRoutine ,like that :
      case SEG_xxx:
     and follow the guidelines for other cases.
   8. Add a case in function segment::show like that  :
      case SEG_xxx:
         and follow the guidelines for the case SEG_LINE.
   NOTE. If you want to store TRM's for that new class , you have to change
   the case SEG_SEGMENT for functions AddSegmentRoutine and segment::show();

*/
//------------------------------------------------------------------------
//-----------------------------------------------------------------
//                     S E G M E N T
//-----------------------------------------------------------------
template <class T>
void ShowClass(T &t,int &index, int limit)

{
if (index>limit)
    perror("SHOW_SEGMENT FOUND A LIMIT!");
index++;
t.show();
}

/**class segment;
class segment {
matrix4_4  *TRMS_S; // First Translation array
                    // Second Rotation     >>
                    // Third  Scaling >>

Line *pl;      // The list of lines
int nol;       //       No of  >>
polyline *pll; // The list of polylines
int noll;      //       No of  >>
text  *pt;     // The list of text
int not;       //      No of  texts;
color *pco;    // The List of pco;
int noco;      //      No of colors;
int *ps;   // The list of segments
int nos;       //       No of  >>
int  *pc;      // The list of choises
int noc;       //      No of   >>
**/

segment::segment()
         {
         pl   = NULL;
         pll  = NULL;
         ps   = NULL;
	 pc   = NULL;
	 pt   = NULL;
	 pel  = NULL;
	 noco = NULL;
	 noel = NULL;

	 nol = noll = nos = noc  = not = noco = noel = 0;
         TRMS_S = NULL;
         }
void segment::show()
        {
	int LineIndex,PolylineIndex,ColorIndex,TextIndex,SegmentIndex,
	    EllipseIndex;
        int i;
	LineIndex = PolylineIndex=ColorIndex=TextIndex=SegmentIndex = 0;
	EllipseIndex= 0;

        for (i=0;i<noc;i++) {
             switch(pc[i]) {
          case SEG_LINE:ShowClass(pl[LineIndex],LineIndex,nol);
                  break;
          case SEG_COLOR:ShowClass(pco[ColorIndex],ColorIndex,noco);
                  break;
	  case SEG_TEXT:ShowClass(pt[TextIndex],TextIndex,not);
		    break;
	  case SEG_ELLIPSES:ShowClass(pel[EllipseIndex],EllipseIndex,noel);
		   break;
          case SEG_SEGMENT:int psi = ps[SegmentIndex];
                            if ( (psi>=MAX_SEGMENTS)|| (psi<0)) {
                              perror("show segment error2");
                              break;
                            }
                   // SAVE OLD VIEWMATRIX, Color, PROJECTIONMATRIX
			    int OldColor = CurrentColour;
                            matrix4_4 OldViewMatrix = *CurrentViewMatrix;
                            matrix4_4 OldTransformMatrix =
                                                 *CurrentTransformMatrix;
                   // POP TRM's  FOR THAT SEGMENT
                   // REMEMBER THE SEQUENSE IS TRANSLATE-
                   // ROTATE-SCALING
                            int k = SegmentIndex*3;
                            matrix4_4 TRMt,TRMr,TRMs;

                            TRMt = TRMS_S[k];
                            TRMr = TRMS_S[k+1];
                            TRMs = TRMS_S[k+2];
                    // First apply the trans to transform matrix and then to
                    // the Viewmatrix for projection

                            *CurrentTransformMatrix = TRMt * TRMr * TRMs*
                                                  *CurrentTransformMatrix;

                            RecalcViewMatrix();
                    // Transfer to the next segment
                            ShowClass(*SegmentArray[psi],SegmentIndex,nos);
                    // Restore old options
                            *CurrentViewMatrix = OldViewMatrix;
                            *CurrentTransformMatrix = OldTransformMatrix;
			    CurrentColour = OldColor;
                  break;
          case SEG_POLYLINE:ShowClass(pll[PolylineIndex],PolylineIndex,noll);
                  break;
             default:perror("found a default for show segment");
             }
             }

	}

