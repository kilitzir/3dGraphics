#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
//The main menu. Calls all the routines
//------------------------------------------------------------------------
int  *NULLPOINTER = (int*) 0;
void test1();
#include <conio.h>
int main()
{

OpenDev();
InitVariables();
Predefsegments();
/**SetVPR(0,0,0);
SetVPN(0,0,-1);
SetVUV(0,1,0);
SetDOP(0,0,1);

SetWindow(-15,25,-15,25);
SetViewport2(0,0,1,1);
**/
menu();
CloseDev();
if (*NULLPOINTER != 0)
cerr << " Null Pointer !!!"<<endl;
return(0);
}
