#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
/* Projection routines
*/
//------------------------------------------------------------------------
static /**inline**/ matrix4_4 MakeProjectionMatrixParallel();
static /**inline**/ matrix4_4 MakeProjectionMatrixPerspective();
//----------- M A K E   V I E W   M A T R I X
matrix4_4 MakeProjectionMatrix()
{
Temp4_4 = *CurrentProjectMatrix;
     if (ProjectionType == PERSPECTIVE)
          return MakeProjectionMatrixPerspective();
else if  (ProjectionType == PARALLEL)
          return MakeProjectionMatrixParallel();
else if  (ProjectionType == D2){
       perror("2D PROJECTON !!!!");
       return I4_4;
     }
else perror("MAKEPROJECTIONMATRIX-NO PROJECTION FOUND");
return I4_4;
}
//------------C H E C K   P A R M S
static void CheckParms(int choise)
// Checks if the dianismata have been given
// If they don't , It tries to put something,
// actually, it should tries to put something ...
{
}
//-------------------------------------------------------------------------
//M A K E   V I E W   M A T R I X   P A R A L L E L
//-------------------------------------------------------------------------
static /**inline**/ matrix4_4 MakeProjectionMatrixParallel()
{


matrix4_4 equ   = I4_4;    // Not needed but ...
matrix1_4 debug;

  Window *pw = CurrentWindow;


CheckParms(PARALLEL);
matrix1_4 P1   = homo2can(VPR),
	  P1P2 = homo2can(VPN),
	  P1P3 = homo2can(VUV);

  matrix4_4 Temp1 = I4_4;
                                         // 1. Translate VPR to the origin
  Temp1.set_line(3,-P1.getx(),-P1.gety(),-P1.getz(),1);
  debug = P1*Temp1;
                                        /** 2. Rotate so that VPN becomes
                                               the negative z-axis;
                                            3. Rotate so that the projection
					       of VUV onto the view plane
                                               becomes the y-axis
					 **/
matrix1_4  Rz  = homo2can(P1P2/-abs(P1P2) ),
	   Rx  = homo2can((P1P2%P1P3));
  if (Rx == O1_4) {
		   perror("MakeProjectionMatrixParallel:normals are parallel");
		   return I4_4 ;
		  }
  Rx =  homo2can(Rx/abs(Rx));
matrix1_4  Ry  = homo2can(Rz%Rx);

matrix4_4 Temp2 = I4_4;    // Not needed but ...
  Temp2.set_col(0,Rx.get0(),Ry.get0(),Rz.get0(),0);
  Temp2.set_col(1,Rx.get1(),Ry.get1(),Rz.get1(),0);
  Temp2.set_col(2,Rx.get2(),Ry.get2(),Rz.get2(),0);
  Temp2.set_col(3,        0,        0,        0,1);
  debug = VPN * Temp1 * Temp2;
  debug = VUV * Temp1 * Temp2;
					/** 4. Change from right-handed(World)
					       to left-handed(viewing) coord's.
					       It is in our book, but NOT in
					       his !?!. BUT, if we comment it,
					       the object comes upside-down.
					 **/
matrix4_4  Temp3 = I4_4;
  Temp3.set_ij(2,2,-1);

  equ = Temp1 * Temp2 * Temp3;
  debug = VUV * equ;
  debug = VPN * equ;
					/** 5. Shear so that all the planes
					       defining the view volume become
					       normal to axes of the viewing
					       coordinate system
					 **/
 matrix1_4 DOP1 = homo2can(DOP * equ);
  if (DOP1.getz() == 0) {
			  perror("MakeProjectionMatrixParallel:DOP1z == 0");
			  perror("Have you put the DOP???");
			  return I4_4 ;
			}
  float a1 = -DOP1.getx()/DOP1.getz(),
	b1 = -DOP1.gety()/DOP1.getz();
  matrix4_4  Temp4 = I4_4;
  Temp4.set_col(2,a1,b1,1,0);

  equ *= Temp4;
  debug = DOP*equ;
					/** 6. Translate and scale the
					       view volume into the unit cube
					 **/
  if ((pw->getUmax()-pw->getUmin()==0) || (pw->getVmax()-pw->getVmin() == 0)
      ||(BackwardDistance - ForwardDistance == 0)) {
				perror("MakeProjectionMatrixParallel:Last Error");
				return I4_4;
  }
/**** This is defined in his book.....
  equ *= TRANSLATE3(-((pw->getUmax()+pw->getUmin()))/2,
		    -(pw->getVmax()+pw->getVmin()/2),
		    -ForwardDistance)
	* SCALE3(2/(pw->getUmax()-pw->getUmin()),
		 2/(pw->getVmax()-pw->getVmin()),
		 1/(BackwardDistance - ForwardDistance));
***/
  equ *= TRANSLATE3(-pw->getUmin(),
		    -pw->getVmin(),
		    -ForwardDistance)
	* SCALE3(1/(pw->getUmax()-pw->getUmin()),
		 1/(pw->getVmax()-pw->getVmin()),
		 1/(BackwardDistance - ForwardDistance));

  return equ;
}
//-------------------------------------------------------------------------
//   M A K E   V I E W   M A T R I X   P E R S P E C T I V E
//-------------------------------------------------------------------------
static /**inline**/ matrix4_4 MakeProjectionMatrixPerspective()
{

CheckParms(PERSPECTIVE);
COP  = homo2can(COP);
					/** 1. Translate the center of
					       projection to the origin
					 **/
matrix4_4 Temp1 = I4_4; //we could use TRANSLATE3 but i prefare it this way.
  Temp1.set_line(3,-(VPR.getx()+COP.getx()) ,
		   -(VPR.gety()+COP.gety()) ,
		   -(VPR.getz()+COP.getz()) ,1);

					/** 2. Rotate so that VPN becomes
					       the negative z-axis;
                                            3. Rotate so that the projection
					       of VUP onto the view plane
					       becomes the y-axis
					 **/
matrix1_4 P1   = homo2can(VPR),
	  P1P2 = homo2can(VPN),
	  P1P3 = homo2can(VUV);

matrix1_4  Rz  = homo2can(P1P2/(-abs(P1P2))),
	   Rx  = homo2can(P1P2%P1P3);
  if (Rx == O1_4) {
		   perror("MakeProjectionMatrixPerspective:normals are parallel");
		   return I4_4;
  }
  Rx =  homo2can(Rx/abs(Rx));

  matrix1_4  Ry  = homo2can(Rz%Rx);
  matrix4_4 Temp2 = I4_4;
  Temp2.set_col(0,Rx.getx(),Ry.getx(),Rz.getx(),0);
  Temp2.set_col(1,Rx.gety(),Ry.gety(),Rz.gety(),0);
  Temp2.set_col(2,Rx.getz(),Ry.getz(),Rz.getz(),0);
  Temp2.set_col(3,        0,        0,        0,1);
					/** 4. Change from right-handed(World)
					       to left-handed(viewing) coord's
					 **/
matrix4_4 Temp3 = I4_4;
  Temp3.set_ij(2,2,-1);
					/** 5. Shear so the center line of the
					       view volume becomes the z axis
					 **/
matrix4_4  equ =  Temp1 * Temp2 * Temp3;

  VPR1 = homo2can(VPR * equ);


  float VPR1z = VPR1.getz();
  Window *pw = CurrentWindow;


  if (VPR1z == 0) {
		 perror("MakeProjectionMatrix: VPR1.Z == 0");
		 return I4_4;
  }
  float  umin = pw->getUmin(),  // window xmin,xmax
	 umax = pw->getUmax(),
	 vmin = pw->getVmin(),  // window ymin,ymax
	 vmax = pw->getVmax();
  float a2 = -( VPR1.getx() + ((umin+umax)/2) ) /  VPR1z,
	b2 = -( VPR1.gety() + ((vmin+vmax)/2) )/   VPR1z;
  matrix4_4 Temp4 = I4_4;
  Temp4.set_col(2,a2,b2,1,0);

  equ *= Temp4;

					/** Scale so the view volume becomes
					    the truncated right pyramid
                                            defined by the six planes in
                                            page 284
                                         **/

  float VPRZ_B = VPR1z + BackwardDistance;

  if ( (umax-umin == 0) || (vmax-vmin == 0) || (VPRZ_B == 0)) {
	 perror("MakeprojectionMatrix:window or VPR wrong");
         return I4_4;
  }


  matrix4_4  Temp5 = SCALE3(2*VPR1z/ ( (umax-umin) * VPRZ_B),
		2*VPR1z/ ( (vmax-vmin) * VPRZ_B),
		1/(VPRZ_B) );
  equ *= Temp5 ;
  return equ;
}

