extern "C" {
#include "SPHDEMO.h"
#include "view.h"
}
void CreateCameraStructure ();
#pragma hdrstop


   /* WARNING: must be reset to zero whenever camera restored to default */
   int totalpitch, totalyaw;   /* in degrees */

   matrix temp;

   /* DEFAULT VALUES */
   point vrpdef={33.0,36.0,42.0}, prpdef={0.0,0.0,80.0};
   vector vpndef={0.0,0.0,1.0}, vupvdef={0.0,1.0,0.0};
   double umindef=-50.0, umaxdef=50.0, vmindef=-50.0, vmaxdef=50.0;
   double fplanedef=-30.0, bplanedef=-160.0;
   short persptypedef=PERSPECTIVE;

   /* CURRENT PERSPECTIVE VIEW */
   point vrp1, prp1;
   double umin1, umax1, vmin1, vmax1;
   double fplane1, bplane1;
   vector vpn1, vupv1;
   double viewportxmin, viewportxmax, viewportymin, viewportymax;
   short persptype1;

   /* CURRENT INVERSE OF ViewOrientation MATRIX FOR RENDERED VIEW */
   matrix inverseVO;


void FullScreenRenderView ()
{
   viewportxmin = viewportymin = (double)0;
   viewportxmax = viewportymax = (double)1;
}

void PartialScreenRenderView ()
{
   viewportxmin = viewportymin = (double)0;
   viewportxmax = viewportymax = 0.7;
}



void ShowUsingNewView1 (void)
{
   matrix vo_matrix, vm_matrix;

   SPH_evaluateViewOrientationMatrix
      (vrp1,
       vpn1,
       vupv1,
       vo_matrix);

   MAT3invert (inverseVO, vo_matrix);

   SPH_evaluateViewMappingMatrix
      (umin1, umax1,   vmin1, vmax1, persptype1,
       prp1,
       fplane1, bplane1,
       viewportxmin,viewportxmax, viewportymin,viewportymax, 0.0,1.0,
       vm_matrix);

   SPH_setViewRepresentation
      (PERSPECTIVE_VIEW,
       vo_matrix, vm_matrix,
       viewportxmin,viewportxmax, viewportymin,viewportymax, 0.0,1.0);

   CreateCameraStructure ();
}


void InitTextView (void)
{
   /* KIDS: Don't try this at home! */
   /*AAAA It may get you pregnant, just like you FXXXing moron*/
   /*** Adition */
   matrix vo,vm;
   int i,j;
   for (i=0;i<4;i++)
	for (j=0;j<4;j++)
   vo[i][j] = vm[i][j] = i==j?1:0;

  SPH_setViewRepresentation
      (TEXT_VIEW, // we change TEXT_VIEW to 0
       vo,vm, 0.0,0.8,  0.75,1.0, 0.0,1.0);


}



void InitSideOrthoView (void)
{
   matrix vo_matrix, vm_matrix;
   vector vpnvec = {1.0,0.0,0.0};
   vector vrpvec = {100.0,0.0,-50.0};

   SPH_evaluateViewOrientationMatrix 
      (vrpvec,
       vpnvec,
       vupvdef,
       vo_matrix);

#define RADIUS 165.0
   SPH_evaluateViewMappingMatrix
      (-RADIUS,RADIUS, -RADIUS,RADIUS,  ORTHOGRAPHIC,
       prpdef,
       fplanedef, bplanedef,
       0.8,1.28,  0.0,0.48, 0.0,1.0,
       vm_matrix);
#undef RADIUS

   SPH_setViewRepresentation
      (SIDE_ORTHO_VIEW,
       vo_matrix, vm_matrix,
       0.8,1.28,  0.0,0.48, 0.0,1.0);
}



void InitTopOrthoView (void)
{
   matrix vo_matrix, vm_matrix;
   vector vpnvec = {0.0,1.0,0.0};
   vector vupvec = {0.0,0.0,-1.0};
   vector vrpvec = {50.0,100.0,-50.0};

   SPH_evaluateViewOrientationMatrix 
      (vrpvec,
       vpnvec,
       vupvec,
       vo_matrix);

#define RADIUS 165.0
   SPH_evaluateViewMappingMatrix
      (-RADIUS,RADIUS, -RADIUS,RADIUS,  ORTHOGRAPHIC,
       prpdef,
       fplanedef, bplanedef,
       0.8,1.28,  0.50,1.0, 0.0,1.0,
       vm_matrix);
#undef RADIUS

   SPH_setViewRepresentation
      (TOP_ORTHO_VIEW,
       vo_matrix, vm_matrix,
       0.8,1.28,  0.50,1.0, 0.0,1.0);
}



void RestoreCameraToDefault (void)
{
   /* COPY DEFAULTS INTO VIEW 1's DATA */
   MAT3_COPY_VEC (vrp1, vrpdef);
   MAT3_COPY_VEC (vpn1, vpndef);
   MAT3_COPY_VEC (vupv1, vupvdef);
   MAT3_COPY_VEC (prp1, prpdef);
   fplane1 = fplanedef;
   bplane1 = bplanedef;
   umin1 = umindef;
   vmin1 = vmindef;
   umax1 = umaxdef;
   vmax1 = vmaxdef;
   persptype1 = persptypedef;

   totalpitch = totalyaw = 0;
}



void InitAllViews()
{
   RestoreCameraToDefault();
   InitSideOrthoView();
   InitTopOrthoView();
   InitTextView();

   SPH_setViewBackgroundColor (PERSPECTIVE_VIEW, grey);
   SPH_setViewBackgroundColor (SIDE_ORTHO_VIEW, grey);
   SPH_setViewBackgroundColor (TOP_ORTHO_VIEW, grey);

   SPH_setRenderingMode (PERSPECTIVE_VIEW, LIT_FLAT);
   SPH_setRenderingMode (SIDE_ORTHO_VIEW, WIREFRAME_RAW);
   SPH_setRenderingMode (TOP_ORTHO_VIEW, WIREFRAME_RAW);
   SPH_setRenderingMode (TEXT_VIEW, WIREFRAME_RAW);

   SPH_setViewPointLightSource (PERSPECTIVE_VIEW,   0.0, 195000.0, 195000.0);
}






void ChangeVRP_relativeUVN (double delta, int whichaxis)
{
   vector deltavecUVN={0.0,0.0,0.0};
   
   deltavecUVN[whichaxis] = delta;
   MAT3mult_vec (vrp1, deltavecUVN, inverseVO);
}

void ChangeVRP_relativeWC (double delta, int whichaxis)
{
   vrp1[whichaxis] += delta;
}

void ChangeFrontClipPlane (double delta)
{
	 fplane1 += delta; 
	 if (fplane1 >= prp1[Z])
	    fplane1 = prp1[Z]-1.0;
	 if (fplane1 <= bplane1)
	    fplane1 = bplane1+1.0;
}
 
void ChangeBackClipPlane (double delta)
{
	 bplane1 += delta; 
	 if (bplane1 >= fplane1)
	    bplane1 = fplane1-1.0;
}



void ChangeVPN (double pitch, double yaw)
{
   double alpha, beta;
   
   totalpitch+=pitch;
   if (totalpitch > 89)
      totalpitch = 89;
   else if (totalpitch < -89)
      totalpitch = -89;
   totalyaw = (totalyaw+=yaw)%360;
   alpha = totalyaw*PI/180.0;
   beta = totalpitch*PI/180.0;
   MAT3_SET_VEC (vpn1, 
		       sin(alpha)*cos(beta),
		       sin(beta)*cos(alpha),
		       cos(alpha) );
}


void ChangePRP (double delta)
{
	 prp1[2] += delta;
	 if (prp1[2] <= 0.0) {
	    prp1[2] = 0.1;
	 }
}

void ChangePRPforOrtho (void)
{
   persptype1 = ORTHOGRAPHIC;
   prp1[Z] = HUGE_VAL;
}

void ChangePRPforClosestPerspective (void)
{
   persptype1 = PERSPECTIVE;
   prp1[Z] = (double)10;
}

