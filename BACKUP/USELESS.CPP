#pragma hdrstop
//---
 matrix4_4 ROTATEPOINT2(matrix1_4 t,float arc)
{
t =  homo2can(t);
 return ROTATEPOINT2(t.get0(),t.get1(),arc) ;
}
/********************* USELESS ROUTINES START








boolean CheckPlane(const float x1,const float y1,const float z1,const float x2,const float y2,const float z2,
                   const float x3,const float y3,const float z3,const float x4,const float y4,const float z4)
// Checks if the 4 points belong 2 the same plane (polyline use)
{
// First make some trivial conditions (if we are in 2d 4 ex.

if ( (z1==z2) && (z2==z3) && (z3==z4) )
   return(TRUE);
if ( (x1==x2) && (x2==x3) && (x3==x4) )
   return(TRUE);
if ( (y1==y2) && (y2==y3) && (y3==y4) )
   return(TRUE);

// Now we make the real check
float x2_1 = x2-x1,x3_1 = x3-x1,
      y2_1 = y2-y1,y3_1 = y3-y1,
      z2_1 = z2-z1,z3_1 = z3-z1;
float temp = x4 * (y2_1*z3_1 - y3_1*z2_1)
           - y4 * (x2_1*z3_1 - x3_1*z2_1)
           + z4 * (x2_1*y3_1 - x3_1*y2_1);
return(fabs(temp)<1e-5);
}
boolean CheckPlane(const float *x,const float *y,const float *z)
{
// Overloading CheckPlane for multiple uses
if (z == NULL)
    return(TRUE);
return (CheckPlane(x[0],y[0],z[0], x[1],y[1],z[1],
           x[2],y[2],z[2], x[3],y[3],z[3]) );
}



#define __IMPLEMENT
#pragma hdrstop

#define MAX_STACK_SIZE 10

template <class T>
class stack {
char *id;                       // If it's first in hierarchy holds the id
T *data[MAX_STACK_SIZE];        // DATA ELEMENT
int no;                         // POINTS TO THE NEXT EMPTY ARRAY SOCKET
stack *next;
public:
        stack();
        stack(char* id);
        ~stack();
void    push(T p);
T       pop();
boolean IsEmpty();
char*   IsA();
char*   Show_Id();
};

//-----------------
template <class T>
void stack<T>::stack() {no = 0;next = NULL;,id = NULL;}
//----------------
template <class T>
void stack<T>::stack(char * s)
            {
            stack();
            id = new char[(strlen(s)+1);
            strcpy(id,s);
            }
//----------------
template <class T>
void stack<T>::~stack()
            {
             int i;
             for (i=0;i<no & (i<MAX_STACK_SIZE);i++)
                delete p[i];
             if (next) delete next;
             if (id)   delete id;
             }
//----------------
template <class T>
void stack<T>::push(T s)
            {
            if (no <MAX_STACK_SIZE)  { p[no] = new T;p[no] = s;}
            else {
                   if (!next) next = new stack;
                   next->push(s);
            }
            no++;
            }
//-----------------
template <class T>
T stack<T>::pop()
           {
           if (no=0) {
                      cerr<<IsA()<<ShowId() << "TRY TO POP FROM AN EMPTY STACK";
                      return(null);
                     }
           else {
                      no--;
                      if (no<MAX_STACK_SIZE-1) return(p[no]);
                      else return(next->pop());
                }
           }
//-----------------
template <class T>
char* stack<T>::IsA()
           {
           return("<STACK>");
           }
//-----------------
/**inline**/  void SetVPR(matrix1_4 &g)
{
  matrix1_4 temp;

  if (!g.checkb())  {
     perror("SETTING VPR WITH A WRONG MATRIX !");
     return;
  }
  temp = homo2can(g);
  SetVPR(temp.get0(),temp.get1(),temp.get2());
}
/**inline**/  void SetVPN(matrix1_4 &g)
{
matrix1_4 temp;
if (!g.checkb())  {
   perror("SETTING VPN WITH AN UNITITIALISED MATRIX !");
   return;
}
temp = homo2can(g);
SetVPN(temp.get0(),temp.get1(),temp.get2());
}
/**inline**/  void SetVUV(matrix1_4 &g)
{
matrix1_4 temp;
if (!g.checkb())  {
   perror("SETTING VUV WITH AN UNITITIALISED MATRIX !");
   return;
}
temp = homo2can(g);
SetVUV(temp.get0(),temp.get1(),temp.get2());

}
//---
 matrix4_4 ROTATEPOINT2(matrix1_4 t,float arc)
{
t =  homo2can(t);
 return ROTATEPOINT2(t.get0(),t.get1(),arc) ;
}
//---- R O T A T E   A B O U T  A  P O I N T ( IN 2D)
/**inline**/ matrix4_4 ROTATEPOINT2(float x,float y,float arc)
{
return TRANSLATE2(-x,-y) * ROTATE2(arc) * TRANSLATE2(x,y);
}
//----- S C A L I N G   A B O U T   A   P O I N T
/**inline**/ matrix4_4 SCALEPOINT2(float x,float y, float Sx,float Sy)
{
return TRANSLATE2(-x,-y) * SCALE2(Sx,Sy) * TRANSLATE2(x,y);
}
/**inline**/ matrix4_4 ROTATEPOINT3(float x,float y,float z,
                                    float arcx,float arcy,float arcz)
/**inline**/ matrix4_4 SCALEPOINT3(float x,float y,float z,
                                   float Sx,float Sy,float Sz)
//---- R O T A T E   A B O U T  A  P O I N T ( IN 3D)
/**inline**/ matrix4_4 ROTATEPOINT3(float x,float y,float z,
                                    float arcx,float arcy,float arcz)
{
return TRANSLATE3(-x,-y,-z) * ROTATE3(arcx,arcy,arcz) * TRANSLATE3(x,y,z);
}
//----- S C A L I N G   A B O U T   A   P O I N T
/**inline**/ matrix4_4 SCALEPOINT3(float x,float y,float z,
                                   float Sx,float Sy,float Sz)
{
return TRANSLATE3(-x,-y,-z) * SCALE2(Sx,Sy,Sy) * TRANSLATE3(x,y,z);
}
/**inline**/  void SetViewport3(float xmin,float xmax,float ymin,float ymax,
               float zmin,float zmax)
{
}
void ClsInput()
// clears the input area();
{
 setviewport(0,20*textheight("W"),getmaxx()/2,getmaxy(),0);
 clearviewport();
 setviewport(0,0,getmaxx(),getmaxy(),0);
// InX = 10;

}
//----------- C H A N G I N G   C O O R D I N A T E S
/**inline**/ matrix1_4 r2l(float x,float y,float z)
{
matrix1_4 temp;
temp.setm(x,y,z,1);
return ( temp * (*CurrentViewMatrix) );
}
//---
/**inline**/ matrix1_4 r2l(matrix1_4 t)
{
t = homo2can(t);
return(r2l(t.getx(),t.gety(),t.getz()));
}

/**inline**/ matrix1_4 VAxis()
{
float ftemp = VPN * VUV; // esoteriko ginomeno
matrix1_4  mtemp;

mtemp.setm(VUV.getx() - ftemp*VPN.getx());
mtemp.setm(VUV.gety() - ftemp*VPN.gety());
mtemp.setm(VUV.getx() - ftemp*VPN.getz());

return(mtemp);
}
/**inline**/  void SetWindow(matrix1_4 min,matrix1_4 max)
{
min = homo2can(min);
max = homo2can(max);
SetWindow(min.getx(),min.gety(),max.getx(),max.gety());
}
#define UAxis()         (V_Axis % VPN)
//-----------------------------------------------------------------
//        M I S C E L A N O U S  R O U T I N E S
//-----------------------------------------------------------------
/**	in ellipse::show
	       int a = x_a;
	       int b = y_b;
	       int x = 0;
	       int y = b;
	       float a2 = a*a;
	       float b2 = b*b;
	       float d1 = b2 - a2*b + a2/4.0;
	       putpixel(10*x*AspectRatioX,10*y*AspectRatioY,12);
	       while (a2*(y-.5) >= b2*(x+1)) {
		     if (d1<=0) {
			d1 += b2*(2*x+3);
			++x;
		     }
		     else {
			d1 += b2*(2*x+3) + a2*2*(1-y);
			++x;
			--y;
		     }
		     putpixel(10*x*AspectRatioX,10*y*AspectRatioY,12);
	       }// while
	       float d2 = b2*pow(x+.5,2)+a2*pow(y-1,2) - a2*b2;
	       while (y>0) {
		if (d2<=0) {
			d2 += 2*b2*(x+1) + a2*(3-2*y);
			++x;
			--y;
		}
		else {
			d2 += a2*(3-2*y);
			--y;
		}
		putpixel(10*x*AspectRatioX,10*y*AspectRatioY,12);
	       }//while
**/


********************* USELESS ROUTINES ENDS ****/

