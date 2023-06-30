#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
// Friend of matrix1_4. It's the homogeneus 2 canonical coordinates.
// homo2can() is implemented as a macro because most of the times the
// w== 1. If it's not the homo2can() calls homo2can1.
//------------------------------------------------------------------------

//-----------------------------------------------------------------------
//         M A T R I X   1 * 4
//-----------------------------------------------------------------------

matrix1_4 homo2can1( matrix1_4 source)
{
matrix1_4 temp;
int i;

source.errorb();
if (source.ar[3] == 0) { // if we have any problems, we'll debug it
	source.ar[3] = 1;
}
 for (i=0;i<3;i++)
    temp.ar[i] = source.ar[i]/source.ar[3];

temp.ar[3] = 1;
temp.setb();
return(temp);
}
