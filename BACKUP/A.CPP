#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
// Routines that make the projection matrix
/* There are 2 routines MakeProjectionMatrixPerspective and
   MakeProjectionMatrixParallel() for perspective and parallel
   projection respectively. If we are in 2d it returns I4_4 .
   If an error occurs it returns also I4_4.
   For information how these routines work look at pages 284-295.
*/
//------------------------------------------------------------------------

static /**inline**/ matrix4_4 MakeProjectionMatrixParallel();
static /**inline**/ matrix4_4 MakeProjectionMatrixPerspective();

#define abs(t)   sqrt(t*t)
//----------- M A K E   V I E W   M A T R I X
matrix4_4 MakeProjectionMatrix()
{
     if (ProjectionType == PERSPECTIVE)
          return MakeProjectionMatrixPerspective();
else if  (ProjectionType == PARALLEL)
          return MakeProjectionMatrixParallel();
else if  (ProjectionType == D2){
       perror("2D PROJECTON");
       return I4_4;
     }
else perror("MAKEPROJECTIONMATRIX-NO PROJECTION FOUND");
return I4_4;
}
//----------- M A K E   V I E W   M A T R I X   P A R A L L E L
static /**inline**/ matrix4_4 MakeProjectionMatrixParallel()
{
matrix1_4 P1P2 = VPN,
          P1P3 = VUV,
          P1   = VPR;
matrix4_4 Temp1 = I4_4,
          Temp2 = I4_4,    // Not needed but ...
          Temp3 = I4_4,
          Temp4 = I4_4,
          equ   = I4_4;    // Not needed but ...
matrix1_4 Rz,
          Rx,
          Ry,
          DOP1;

  Window *pw = CurrentWindow;
  float a1,b1;

P1   = homo2can(P1);
P1P2 = homo2can(P1P2);
P1P3 = homo2can(P1P3);

                                         // 1. Translate VPR to the origin
  Temp1.set_line(3,-P1.getx(),-P1.gety(),-P1.getz(),1);

                                        /** 2. Rotate so that VPN becomes
                                               the negative z-axis;
                                            3. Rotate so that the projection
                                               of VUP onto the view plane
                                               becomes the y-axis
                                         **/
  Rz  = homo2can(P1P2/(abs(P1P2) * (-1)));
  Rx  = homo2can((P1P2%P1P3));
  if (Rx == O1_4) {
                   perror("MAKEPROJECTIONMATRIXPARALLEL normals are parallel");
                   return I4_4 ;
                  }
  Rx =  homo2can(Rx/abs(Rx));
  Ry  = homo2can(Rz%Rx);


  Temp2.set_col(0,Rx.getx(),Ry.getx(),Rz.getx(),0);
  Temp2.set_col(1,Rx.gety(),Ry.gety(),Rz.gety(),0);
  Temp2.set_col(2,Rx.getz(),Ry.getz(),Rz.getz(),0);
  Temp2.set_col(3,        0,        0,        0,1);

                                        /** 4. Change from right-handed(World)
                                               to left-handed(viewing) coord's
                                         **/
  Temp3.set_ij(2,2,-1);

  equ = Temp1 * Temp2 * Temp3;
                                        /** 5. Shear so that all the planes
                                               defining the view volume become
                                               normal to axes of the viewing
                                               coordinate system
                                         **/
  DOP1 = homo2can(DOP * equ);
  if (DOP1.getz() == 0) {
                          perror("MAKEPROJECTIONMATRIXPARALLEL DOPz == 0");
                          return I4_4 ;
                        }

  a1 = DOP1.getx()/DOP1.getz() * (-1.);
  b1 = DOP1.gety()/DOP1.getz() * (-1.);

  Temp4.set_col(2,a1,b1,1,0);

  equ *= Temp4;

                                        /** 6. Translate and scale the
                                               view volume into the unit cube
                                         **/
  if ((pw->getUmax()-pw->getUmin()==0) || (pw->getVmax()-pw->getVmin() == 0)
      ||(BackwardDistance - ForwardDistance == 0)) {
                             perror("MAKEPROJECTIONMATRIXPARALLEL LAST ERROR");
                             return I4_4;
  }

  equ *= TRANSLATE3(-(pw->getUmin()),-(pw->getVmin()),-ForwardDistance)
        * SCALE3(1/(pw->getUmax()-pw->getUmin()),1/(pw->getVmax()-pw->getVmin()),
                 1/(BackwardDistance - ForwardDistance));
  return equ;
}
//----------- M A K E   V I E W   M A T R I X   P E R S P E C T I V E
static /**inline**/ matrix4_4 MakeProjectionMatrixPerspective()
{
matrix1_4 P1P2 = VPN,
          P1P3 = VUV,
          P1   = VPR;
matrix4_4 Temp1 = I4_4,
          Temp2 = I4_4,    // Not needed but ...
          Temp3 = I4_4,
          Temp4 = I4_4,
          Temp5 = I4_4,    // Not needed but ...
          equ   = I4_4;    // Not needed but ...
matrix1_4 Rz,
          Rx,
          Ry;

  Window *pw = CurrentWindow;

P1   = homo2can(P1);
P1P2 = homo2can(P1P2);
P1P3 = homo2can(P1P3);
COP  = homo2can(COP);
                                        /** 1. Translate the center of
                                               projection to the origin
                                         **/

  Temp1.set_line(3,-(P1.getx()+COP.getx()) ,
                   -(P1.gety()+COP.gety()) ,
                   -(P1.getz()+COP.getz()) ,1);

                                        /** 2. Rotate so that VPN becomes
                                               the negative z-axis;
                                            3. Rotate so that the projection
                                               of VUP onto the view plane
                                               becomes the y-axis
                                         **/


  Rz  = homo2can(P1P2/(abs(P1P2) * (-1)));
  Rx  = homo2can(P1P2%P1P3);
  if (Rx == O1_4) {
                   perror("MAKEPROJECTIONMATRIXPERSPECTIVE normals are parallel");
                   return I4_4;
                  }
  Rx =  homo2can(Rx/abs(Rx));
  Ry  = homo2can(Rz%Rx);

  Temp2.set_col(0,Rx.getx(),Ry.getx(),Rz.getx(),0);
  Temp2.set_col(1,Rx.gety(),Ry.gety(),Rz.gety(),0);
  Temp2.set_col(2,Rx.getz(),Ry.getz(),Rz.getz(),0);
  Temp2.set_col(3,        0,        0,        0,1);
                                        /** 4. Change from right-handed(World)
                                               to left-handed(viewing) coord's
                                         **/

  Temp3.set_ij(2,2,-1);

  equ = Temp1 * Temp2 * Temp3;
                                        /** 5. Shear so the center line of the
                                               view volume becomes the z axis
                                         **/



  VPR1 = homo2can(VPR * equ);

  float umin,umax, // window xmin,xmax
        vmin,vmax; // window ymin,ymax
  float a2,b2,
         VPR1z = VPR1.getz();

  if (VPR1z == 0) {
                 perror("MAKEPROJECTIONMATRIX VPR.Z == 0");
                 return I4_4;
  }
  umin = pw->getUmin();
  umax = pw->getUmax();
  vmin = pw->getVmin();
  vmax = pw->getVmax();
  a2 = -( VPR1.getx() + (((umin+umax)/2)) )/
                    VPR1z;
  b2 = -( VPR1.gety() + (((vmin+vmax)/2)) )/
                    VPR1z;

  Temp4.set_col(2,a2,b2,1,0);

  equ *= Temp4;
                                          /** Scale so the view volume becomes
                                            the truncated right pyramid
                                            defined by the six planes in
                                            page 284
                                         **/

  float VPRZ_B = VPR1z + BackwardDistance;

  if ( (umax-umin == 0) || (vmax-vmin == 0) || (VPRZ_B == 0)) {
         perror("MAKEPROJECTIONMATRIX DIVISION WITH 0");
         cout << (umax-umin) << (vmax-vmin) << VPRZ_B<< endl;
         return I4_4;
  }



  Temp5 = SCALE3(2*VPR1z/ ( (umax-umin) * VPRZ_B),
                2*VPR1z/ ( (vmax-vmin) * VPRZ_B),
                1/(VPRZ_B) );



  equ *= Temp5 ;
  return equ;
}

