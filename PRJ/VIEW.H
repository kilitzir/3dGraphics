/* file view.h */

#include "sphigs.h"  /* added ADR 8/19/91 */

#define SIDE_ORTHO_VIEW  1
#define TOP_ORTHO_VIEW   2
#define PERSPECTIVE_VIEW 3
#define TEXT_VIEW 	 4

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2


extern short persptype1;

extern point vrp1, prp1;
extern double umin1, umax1, vmin1, vmax1;
extern double fplane1, bplane1;
extern vector vpn1, vupv1;
extern double viewportxmin, viewportxmax, viewportymin, viewportymax;
extern short persptype1;
