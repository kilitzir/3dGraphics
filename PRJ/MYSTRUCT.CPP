extern "C" {
#include "SPHDEMO.h"
#include "struct.h"
#include "view.h"
}
#pragma hdrstop

void InitVariables() {
//SPH_setEdgeFlag(EDGE_VISIBLE);
//SPH_setEdgeStyle(CONTINUOUS);
//SPH_setEdgeColor(5);
}
static point Vetrices[] = {
		{ 3., 9., 10.},   //0
		{ 3., 9.,  0.},   //1
		{ 3., 0.,  0.},   //2
		{ 3., 0., 10.},   //3
		{ 0., 0., 10.},   //4
		{ 0., 0.,  0.},   //5
		{ 0., 9.,  0.},   //6
		{ 0., 9., 10.} }; //7
static vertex_index Facets[] = {
		 0,3,2,1,-1,  //1
		 0,7,4,3,-1,  //2
		 0,1,6,7,-1,  //3
		 1,2,5,6,-1,  //4
		 4,7,6,5,-1,  //5
		 3,2,5,4,-1}; //6

//------------------------------------------------------------------
void test1() {
point array[] = {
		{10,10,10},
		{20,20,20}};
SPH_openStructure(20);
SPH_polyLine(2,array);
point a  = {0,0,0};
SPH_text(a,"here we go again");
SPH_closeStructure();
//SPH_postRoot (20, PERSPECTIVE_VIEW);
}
//------------------------------------------------------------------
// Builds the finger
void BuildFinger() {
     SPH_openStructure(FINGER_STRUCT);
     SPH_setInteriorColor (yellow);
     SPH_setEdgeStyle(CONTINUOUS);
     SPH_setEdgeColor(red);
     SPH_polyhedron(8,6,Vetrices,Facets);
     SPH_closeStructure();
}
//----------------
void BuildArms() {
// we first add the 2 fingers
matrix temp;
SPH_openStructure (LEFT_ARM_STRUCT);
      //making the LEFT arm now,
      SPH_scale(3,3,1,temp);
	      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure (FINGER_STRUCT);
      // making the 2 fingers
      SPH_setInteriorColor (yellow);
      SPH_scale(1/3.,1/3.,1,temp);
	      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_translate (0.0,-9.0,0.0, temp);
	      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure (FINGER_STRUCT);
      SPH_setInteriorColor (red);
      SPH_translate (6.0,0.0,0.0, temp);
      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure (FINGER_STRUCT);
SPH_closeStructure();
SPH_openStructure(ALL_LEFT_ARM_STRUCT);
      MAT3identity(temp);
	      SPH_setModelingTransformation (temp, ASSIGN);
      SPH_executeStructure (LEFT_ARM_STRUCT);
SPH_closeStructure();

SPH_openStructure(ALL_RIGHT_ARM_STRUCT);
      MAT3identity(temp);
	      SPH_setModelingTransformation (temp, ASSIGN);
      SPH_executeStructure (LEFT_ARM_STRUCT);
SPH_closeStructure();

}
//---------------

void BuildRobot() {
matrix temp;
SPH_openStructure (ROBOT_STRUCT);
      float x1=5 ,y1=3,z1=0 ;
      SPH_translate (x1,y1,z1,temp);
	      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_scale (6,3.2,1,temp);
	      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure(FINGER_STRUCT);
      SPH_scale (1/6.,1/3.2,1,temp);
		SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_translate (x1+10,y1+5,z1-2,temp);
	      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure(ALL_LEFT_ARM_STRUCT);
      SPH_translate (x1+23,y1-3,z1,temp);
	      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure(ALL_RIGHT_ARM_STRUCT);
SPH_closeStructure();
}

//------------------------------------------------
void RotateArm(int object, int label, float arc) {
//we rotate about a point , this point is (1.5,4.5,2)
float x1=28.0,y1=24.0,z1=0;
matrix t1; // getting to the (0,0,0)
	SPH_translate(-x1,-y1,-z1,t1);
matrix t2; // we rotate along the x axis
	SPH_rotateX(arc,t2);
matrix t3; // getting back
	SPH_translate(x1,y1,z1,t3);
	// now multiplying
matrix mult1;
	MAT3mult(mult1,t1,t2);
matrix mult2;
	MAT3mult(mult2,mult1,t3);

// Let's put it in place
SPH_openStructure (object);
SPH_setElementPointer (1);
//SPH_moveElementPointerToLabel (label);
//SPH_offsetElementPointer(1);
//SPH_deleteElement();
SPH_setModelingTransformation(mult2,PRECONCATENATE);
SPH_closeStructure();
}