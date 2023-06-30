//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
// The variable definition. Note the #ifdef main ... Please use it
// wisely.
//------------------------------------------------------------------------
#ifdef MAIN
#define Extern /** **/
#else
#define Extern extern
#endif

Extern float CPx,CPy,CPz;          // The Cursor position.It's not used as matrix1_4
                                   // because we use it in defines .
Extern int ScreenMaxX,ScreenMaxY;  // The maximum pixels for x,y
Extern float AspectRatioX,AspectRatioY;// The aspectRatio for these.

Extern matrix1_4 VPR,     // View Referrence Point
                 COP,     // Center    of Projection
		 DOP,     // Direction of  Projection
                 VPN,     // View Plan Normal
                 VUV,     // View up Vector
                 VPR1,    // Used by the clipping.
               Temp1_4;   // For debugging

Extern int     ProjectionType; // Holds The projection Type

Extern Line     *CurrentLine;
Extern polyline *CurrentPolyline;
Extern text     *CurrentText;
Extern Window    *CurrentWindow;    // The current Window
Extern Viewport  *CurrentViewport;  // The current viewport
Extern color     *CurrentColor;
Extern int        CurrentColour;
Extern Ellipse   *CurrentEllipse;   // The current Ellipsis
			// the mattrices for the given segment
Extern matrix4_4 *CurrentTRMt,       // Transfer  matrix
                 *CurrentTRMr,       // Rotate      >>
                 *CurrentTRMs;       // Scaling     >>
Extern segment   *CurrentSegment;    // The current segment
Extern int     SegmentNo;            // The number we'll give to the current Seg
Extern segment *SegmentArray[MAX_SEGMENTS];// Array holding all the segments
Extern matrix4_4 *CurrentProjectMatrix;// The current Projection matrix
Extern matrix4_4 *CurrentTransformMatrix;// The current Transformation matrix
Extern matrix4_4 *CurrentViewMatrix;// The multiplier of the above - see
                                    //   #define Recalcviewmatrix() It's
                                    // used for having one matrix for mult.
                                    // with the point -optimization
Extern matrix4_4 Temp4_4;           // For debugging

// Distances for projection
Extern float ForwardDistance,       // Forward
             BackwardDistance;      // Backward
                                    // Clipping front-back
Extern int ClippingFront;           // booleans if we want to clip front
Extern int ClippingBack;	    // or back.
Extern boolean noclipping;          // Boolean, if we want clipping.


Extern boolean W2Vchanged;          // If the window or viewport coords has
                                    // changed, this becomes TRUE;

Extern float W2Vx,                  // Window 2 Viewport scaling factor for x
             W2Vy,                  // Window 2 Viewport scaling factor for y
	     W2Va,                  //  -//       -//-    additive factors
	     W2Vb;
Extern int debug;                   // used to triger some breakpoints.

// defining some neutron elements
#ifndef MAIN
Extern matrix4_4 I4_4;
Extern matrix4_4 O4_4;
Extern matrix1_4 O1_4;
#endif
