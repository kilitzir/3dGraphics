extern "C" {
#include "SPHDEMO.h"
#include "struct.h"
#include "view.h"
#include <conio.h>
#include <ctype.h>
}
#include <prototypes.h>
#pragma hdrstop
void RotateArm(int,int,float);

static int currenderitem = 4;
static int curgridmenuitem = 1, curvpmenuitem = 'A';
static int curCamDialogID = 0;

static int curHelpDialogID = 0;


#define rendermenuID   200
#define cameramenuID   202
#define viewportmenuID 204
#define pickmenuID     205
#define gridmenuID     203
#define modelmenuID    206
#define applemenuID    209



static void InstallCameraDialog (int whichitem)
{
   curCamDialogID = whichitem + 300;
   switch (whichitem) {
    case 1:
      fprintf (stderr, "You are now controlling the VRP along the UVN axes...\n");
      break;
    case 2:
      fprintf (stderr, "You are now controlling the VRP along the XYZ axes...\n");
      break;
    case 3:
      fprintf (stderr, "You are now controlling the VPN...\n\
      You can 'yaw' (rotate about the V axis) by using the S and D keys\n\
      You can 'pitch' (rotate about the U axis) by using the E and X keys\n");
      break;
    case 4:
      fprintf (stderr, "You are now controlling the PRP...\n\
      Move it towards the viewplane (reduce the focal length) using - key\n\
      Move it away from the viewplane (increase focal length) using = key\n");
      break;
    case 5:
      fprintf (stderr, "You are now controlling the Front clipping plane\n\
      Use = to bring it towards eye, - to push away from eye\n");
      break;
    case 6:
      fprintf (stderr, "You are now controlling the Back clipping plane\n\
      Use = to bring it towards eye, - to push away from eye\n");
      break;
   }
}

static void InstallHelpDialog (int whichmenuid)
{
}


static int motion_granularity =  1;

static void DisplayMotionGranularity (void)
{
   fprintf (stderr,  "Current motion granularity is %d\n", motion_granularity);
}



static void AddGridInFrontOfRoot (int structID, int viewID)
{
   SPH_unpostRoot (structID, viewID);
   SPH_postRoot (GRID_STRUCT, viewID);
   SPH_postRoot (structID, viewID);
}




static void ChangeCameraOnAxis (int axis, double bias)
{
   double pitch=0.0, yaw=0.0;
   switch (curCamDialogID) {
    case 301:
      ChangeVRP_relativeUVN (bias*motion_granularity, axis);
      break;
    case 302:
      ChangeVRP_relativeWC (bias*motion_granularity, axis);
      break;
    case 303:
      switch (axis) {
       case X_AXIS:
	 yaw = bias * motion_granularity; break;
       case Y_AXIS:
	 pitch = bias * motion_granularity; break;
       default:
	 return;
      }
      ChangeVPN (pitch, yaw);
      break;
    case 304:
      if (axis != Z_AXIS)
	 return;
      ChangePRP (bias*motion_granularity);
      break;
    case 305:
      if (axis != Z_AXIS)
	 return;
      ChangeFrontClipPlane (bias*motion_granularity);
      break;
    case 306:
      if (axis != Z_AXIS)
	 return;
      ChangeBackClipPlane (bias*motion_granularity);
      break;
   }
   ShowUsingNewView1 ();
}



static void PrintCorrelationInfo (pickInformation *pinfo)
{
   if (pinfo->pickLevel == 4)
      printf ("You picked the chimney on ");
   else
      printf ("You picked ");

   printf ("house #%d ", 1 + (int)((pinfo->path[1].elementIndex-1)/3));

   printf ("on street #%d.\n", 1 + (int)(pinfo->path[0].elementIndex/2));
}



main (argc, argv)
int argc;
char **argv;
{
   double bias;
   long result;
   int whichmenu, whichitem, keycode;
   int numplanes=7, numshades=10;
   FILE *debugfile;
   char buffer[100];
   boolean READ_FROM_STDIN = FALSE;
   locator_measure locmeas;
   pickInformation pickinfo;
   int Arcbias = 10;

   READ_FROM_STDIN = FALSE;

   /* STARTUP SPHIGS */
   if (READ_FROM_STDIN) {
      printf ("\nPlease enter number of framebuffer planes to allocate:\n");
      scanf ("%d", &numplanes);
      printf ("\nPlease enter number of shades per flexicolor:\n");
      printf
	 ("   (Note: this affects how many different flexicolors will be ");
      printf ("available.)\n");
      scanf ("%d", &numshades);
   }

   SPH_begin (640, 480, numplanes, numshades);

   printf ("\nThis is what I was able to provide re: colors...\n");
   printf ("     Number of custom, flexible colors: %d\n", NUM_OF_FLEXICOLORS);
   printf ("     Number of custom, non-flexible colors: %d\n\n",
	   (NUM_OF_APPL_SETTABLE_COLORS-NUM_OF_FLEXICOLORS));
   SPH_setImplicitRegenerationMode (ALLOWED);
   /**
   SPH_setImplicitRegenerationMode (SUPPRESSED);
   **/
   /* We hope there are enough flexicolors for these. */
   SPH_loadCommonColor (2, "yellow");
   SPH_loadCommonColor (3, "green");
   SPH_loadCommonColor (4, "turquoise");
   SPH_loadCommonColor (5, "pink");
   SPH_loadCommonColor (6, "goldenrod");
   SPH_loadCommonColor (7, "firebrick");

   /* But these need not be flexicolors. */
   SPH_loadCommonColor (red, "red");
   SPH_loadCommonColor (grey, "lightgrey");
   SPH_loadCommonColor (orange, "orange");
   SPH_loadCommonColor (yellow, "yellow");
   SPH_loadCommonColor (limegreen, "yellowgreen");
   SPH_loadCommonColor (forestgreen, "forestgreen");
   SPH_loadCommonColor (blue, "blue");

   InitAllViews();
   BuildEverything ();

   DisplayAllViews ();
   ShowUsingNewView1();
   SPH_postRoot (ROBOT_STRUCT,PERSPECTIVE_VIEW);
//    SPH_postRoot (LEFT_ARM_STRUCT,PERSPECTIVE_VIEW);
   /* INITIALIZE THE GRANULARITY DIALOG BOX */
   DisplayMotionGranularity();

   InstallCameraDialog (2);

   SRGP_setKeyboardProcessingMode (RAW);
   SRGP_setInputMode (KEYBOARD, EVENT);
//   SRGP_setInputMode (LOCATOR, EVENT);

 top:
   SPH_setImplicitRegenerationMode (ALLOWED);
   READ_FROM_STDIN = TRUE;
   if (READ_FROM_STDIN)
//      gets(buffer);
	buffer[0] = getch();
   else {
      switch (SRGP_waitEvent (INDEFINITE)) {
       case KEYBOARD:
	 SRGP_getKeyboard (buffer, 2);
	 break;
       case LOCATOR:
	 SPH_getLocator (&locmeas);
	 if (locmeas.button_chord[0] == DOWN)
	    if (locmeas.view_index == PERSPECTIVE_VIEW) {
	       SPH_pickCorrelate
		  (locmeas.position, locmeas.view_index, &pickinfo);
	       if (pickinfo.pickLevel > 0)
		  PrintCorrelationInfo (&pickinfo);
	    }
	 goto top;
      }
   }

   SPH_setImplicitRegenerationMode (SUPPRESSED);

   bias = 1.0;

   switch (buffer[0]) {

     case '<':
       if ((motion_granularity -= 5) < 1)  motion_granularity =  1;
       DisplayMotionGranularity();
       break;

     case '>':
       if ((motion_granularity += 5) > 99) motion_granularity = 99;
       DisplayMotionGranularity();
       break;
     case '0':
       RestoreCameraToDefault ();
       ShowUsingNewView1 ();
       break;

     case '1':
     case '2':
     case '3':
     case '4':
     case '5':
     case '6':
       InstallCameraDialog (buffer[0] - '0');
       break;

     case 's':
     case 'S':
       bias = -1.0; /*nobreak*/
     case 'd':
     case 'D':
       ChangeCameraOnAxis (X_AXIS, bias);
       break;

     case 'x':
     case 'X':
       bias = -1.0; /*nobreak*/
     case 'E':
     case 'e':
       ChangeCameraOnAxis (Y_AXIS, bias);
       break;

     case '-':
       bias = -1.0; /*nobreak*/
     case '=':
       ChangeCameraOnAxis (Z_AXIS, bias);
       break;
     case 'n':
     case 'N':
       SPH_setRenderingMode (PERSPECTIVE_VIEW, LIT_FLAT); break;

     case 'm':
     case 'M':
       SPH_setRenderingMode (PERSPECTIVE_VIEW, WIREFRAME); break;

     case '}':
       /* Undocumented */
       ChangePRPforOrtho();
       ShowUsingNewView1 ();
       break;
     case '{':
       /* Undocumented */
       ChangePRPforClosestPerspective();
       ShowUsingNewView1 ();
       break;
     case 'q':   /* added option to exit the program 8/24/91 ADR */
     case 'Q':
     case 27 :
       SPH_end();
       exit(0);
       break;
     case 'R':
     case 'r':RotateArm(ALL_RIGHT_ARM_STRUCT,LABEL_RIGHT_ARM,
	      isupper(buffer[0])?-10:10);
     break;
     case 'L':
     case 'l':RotateArm(ALL_LEFT_ARM_STRUCT,LABEL_RIGHT_ARM,
	      isupper(buffer[0])?-10:10);
     break;

    }
   goto top;
}
