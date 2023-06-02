//---------------- INCLUDE BC HEADER FILES
#include <iostream.h>
#include <graphics.h>
#include <math.h>
//---------------- INCLUDE BC HEADER FILES

#ifndef  TRUE
#define TRUE  1
#define FALSE 0
#endif


// The maximum number of segments we can have in array SegmentArray
#define MAX_SEGMENTS 100

// CHOISES FOR ADD SEGMENT
// These choises are used by the AddSegmentRoutine and Segment::show()
// If you add new classes, please follow the folowing conversion.
#define SEG_TRMS_S      1

// Objects directly writing to the screen
#define SEG_LINE       11
#define SEG_POLYLINE   12
#define SEG_SEGMENT    13
#define SEG_TEXT       14
#define SEG_ELLIPSES   15

// Objects changing parms in writing
#define SEG_COLOR      21

// No objects - just giving control parms to the segment
#define SEG_CHOISE    101
// COMMON SHAPES
#define SHAPE_SQUARE         1
#define SHAPE_TRIANGLE       2

#define SHAPE_HOUSE         11
#define SHAPE_HOUSES        12
#define SHAPE_HOUSE3        13
#define SHAPE_HOUSE3S       14
#define SHAPE_ELLIPSES      15

#define SHAPE_CGP_B_F       21
#define SHAPE_CGP_SIDE      22
#define SHAPE_CGP_ROOF      23
#define SHAPE_CGP_HOUSE     24


// CHOISES FOR PROJECTION
// D3  =  ProjectionType[0] == 0
// PARALLEL ProjectionType[0] == 0 && ProjectionType[1] == 0
#define D2            0x1
#define D3            0x0
#define PERSPECTIVE   0x2
#define PARALLEL      0x0

// The default Color .
// Used for using the color defined by the parent segment

#define DEFAULT_COLOR   -1
#define perror          cerr <<
//------------------INCLUDE MY HEADER FILES
extern float CPx,CPy,CPz;
// The classes definition
#include <classes.h>
// The variables defintion
#include <vars.h>
// The function prototypes and the global defines.
#include <prototyp.h>
// Inline functions
#include <inline.cpp>
//------------------INCLUDE MY HEADER FILES
// You can understand what are the following .
#ifdef MAIN
//--------------
matrix4_4 I4_4(1,0,0,0,
	       0,1,0,0,
	       0,0,1,0,
	       0,0,0,1);
matrix4_4 O4_4(0,0,0,0,
	       0,0,0,0,
	       0,0,0,0,
	       0,0,0,0);
matrix1_4 O1_4(0,0,0,1);
#endif