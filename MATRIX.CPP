#include <gsp.h>
#pragma hdrstop
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
/* The member functions of the MATRIX1_4 and MATRIX4_4 classes
   The class MATRIX1_4 cannot be used for mathematic operations , just for
   this program. Please note the variable set. It's used by the operators
   to define if the left side has been initialized.
   The matrix matrix1_4::operator*(matrix1_4) give the esoteriko ginomeno.
   The matrix matrix1_4::operator%(matrix1_4) give the eksoteriko ginomeno.
   The functions  homo2can, can2homo translate a point from homogeneus coor-
   dinates to canonical coordinates respectively.
   Some functions can be inlined. At first I did that , but when I start
   debugging the program it was frustrating to need to recompile all files
   for just one change.
*/
/**
//-----------------------------------------------------------------
//                     4 * 4
//-----------------------------------------------------------------
class matrix4_4 {
     size_ar ar[4][4];
     boolean set;
public:
     matrix4_4();
     matrix4_4(size_ar  x1,size_ar  x2, size_ar x3,size_ar  x4,
               size_ar  x5,size_ar  x6, size_ar x7,size_ar  x8,
               size_ar  x9,size_ar x10,size_ar x11,size_ar x12,
               size_ar x13,size_ar x14,size_ar x15,size_ar x16);

void set_line(int no,size_ar x1=0,size_ar x2=0,size_ar x3=0,size_ar x4=0);
void set_col(int no,size_ar x1=0,size_ar x2=0,size_ar x3=0,size_ar x4=0);
void set_ij(int i,int j,float no);
float get_ij(int i,int j);
void setb();
void unsetb();
boolean checkb();

matrix4_4 operator+(matrix4_4 &b);
matrix4_4 operator-(matrix4_4 &b);
matrix4_4 operator*(matrix4_4 &b);
matrix4_4 operator=(matrix4_4 &b);
matrix4_4 operator*=(matrix4_4&b);
matrix4_4 operator+=(matrix4_4 &b);
boolean matrix4_4::operator==(matrix4_4 &b);
friend matrix1_4 operator*(matrix1_4 &x,matrix4_4 &y);
};

//-----------------------------------------------------------------
//                     1 * 4
//-----------------------------------------------------------------
class matrix1_4 {
        size_ar ar[4];
        boolean set;
public:
    matrix1_4();
    matrix1_4(size_ar x1,size_ar x2,size_ar x3,size_ar x4);
    void setm(size_ar x1=0,size_ar x2=0,size_ar x3=0,size_ar x4=0);

    size_ar get0();
    size_ar get1();
    size_ar get2();
    size_ar get3();
#define getx get0
#define gety get1
#define getz get2
#define getw get3
    void setb();
    void unsetb();
    boolean checkb();
    void errorb();

    matrix1_4 operator+(matrix1_4 &b);
    matrix1_4 operator-(matrix1_4 &b);
    float operator*(matrix1_4 &s2);    //esoteriko  ginomeno
    matrix1_4 operator%(matrix1_4 &s2);//eksoteriko   >>
    matrix1_4 operator/(float i);
    boolean operator==(matrix1_4 &s);

    friend matrix1_4 operator*(matrix1_4 &x,matrix4_4 &y);

    friend char check_plane(matrix1_4 x1,matrix1_4 x2,
                                 matrix1_4 x3,matrix1_4 z);

    friend matrix1_4 homo2can1(matrix1_4 source);
    friend matrix1_4 can2homo(matrix1_4 source);
};


**/
//------------------------------------------------------------------------

//---------------
void matrix1_4::matrix1_4()
                {int i;for (i=0;i<4;ar[i++]=0);set=0;}
//---------------
matrix1_4 matrix1_4::operator+(matrix1_4 &b)
                {
                int i;
                matrix1_4 temp;
                if (!b.checkb()) perror("+ WITHOUT INITIALISATION1_4 ");
                for (i=0;i<4;i++)
                    temp.ar[i] = ar[i] + b.ar[i];
                temp.setb();
                return temp;
                }
//---------------
matrix1_4 matrix1_4::operator-(matrix1_4 &b)
                {
                int i;
                matrix1_4 temp;
                if (!b.checkb()) perror("- WITHOUT INITIALISATION1_4");
                for (i=0;i<4;i++)
                  temp.ar[i] = ar[i] - b.ar[i];
                temp.setb();
                 return temp;
                }
//----------------------------------------------------------------------
//                     M A T R I X    4 * 4
//----------------------------------------------------------------------
matrix4_4::matrix4_4()
  {
    int i,j;
    for (i=0;i<4;i++)
       for (j=0;j<4;j++)
         ar[i][j]=0;
    set = FALSE;
  }
matrix4_4 matrix4_4::operator+(matrix4_4 &b)
{
int i,j;
matrix4_4 temp;
    if (!b.checkb()) perror("+ WITHOUT INITIALISATION 4x4");

    for (i=0;i<4;i++)
       for (j=0;j<4;j++)
         temp.ar[i][j] = ar[i][j] + b.ar[i][j];
         temp.setb();
return temp;
}
//---------------
matrix4_4 matrix4_4::operator-(matrix4_4 &b)
{
int i,j;
matrix4_4 temp;
    if (!b.checkb()) perror("- WITHOUT INITIALISATION 4x4");

    for (i=0;i<4;i++)
       for (j=0;j<4;j++)
         temp.ar[i][j] = ar[i][j]-b.ar[i][j];
         temp.setb();
return temp;
}
//---------------
matrix4_4  matrix4_4::operator=(matrix4_4 &b)
{
int i,j;
    if (!b.checkb()) perror("= WITHOUT INITIALISATION 4x4");
    for (i=0;i<4;i++)
       for (j=0;j<4;j++)
         ar[i][j] = b.ar[i][j];

   setb();
   return *this;
}
boolean matrix4_4::operator==(matrix4_4 &b)
                  {
                  int i,j;
                  for (i=0;i<4;i++)
                     for (j=0;j<4;j++)
                        if (fabs(ar[i][j] - b.ar[i][j])>=1e-5)
                         return(FALSE);
                  return(TRUE);
                  }
//-----------------
matrix1_4 operator*(matrix1_4 &x , matrix4_4 &y)
               {
               int i,j;
               matrix1_4 temp;
               register size_ar sum;

               for (i=0;i<4;i++) {
                  for (sum=0,j=0; j<4; j++)
                    sum += (x.ar[j] * y.ar[j][i]);
                  temp.ar[i] = sum;
               }
               if (temp.ar[3] == 0)
                 temp.ar[3] = 1;
               temp.setb();
               return temp;
               }

//---------------
matrix4_4  matrix4_4::operator*(matrix4_4 &b)
{
int i,j,k;
matrix4_4 temp;
size_ar sum;

    if (!b.checkb()) perror("* WITHOUT INITIALISATION 4x4");

     for (i=0;i<4;i++)
       for (j=0;j<4;j++) {
         for (k=0,sum=0;k<4;k++)
//              if ( (*p != 0) && (b.ar[k][j] != 0) )
             sum += ar[i][k] * b.ar[k][j];
         temp.ar[i][j] = sum;
      }
      temp.setb();

return temp;
}
matrix4_4 matrix4_4::operator*= (matrix4_4 &b)
          {
          *this = *this * b;
          return *this ;
          }
matrix4_4 matrix4_4::operator+= (matrix4_4 &b)
         {
          *this = *this + b;
          return *this;
          }

//-----------------------------------------------------------------------
//         M A T R I X   1 * 4
//-----------------------------------------------------------------------
//---------------
/**inline**/ void matrix1_4::matrix1_4(size_ar x1,size_ar x2,size_ar x3,size_ar x4)
                {set = TRUE;ar[0]=x1;ar[1]=x2;ar[2]=x3;ar[3]=x4;}
//---------------
/**inline**/ size_ar &matrix1_4::get0()
			 {
			     if (!checkb())
				    perror("GET0 WITHOUT INITIALISATION1_4 ");
			  return ar[0];
			 }
/**inline**/ size_ar &matrix1_4::get1(){
			     if (!checkb())
				    perror("GET1 WITHOUT INITIALISATION1_4 ");
			  return ar[1];
			 }

/**inline**/ size_ar &matrix1_4::get2(){
			     if (!checkb())
				    perror("GET2 WITHOUT INITIALISATION1_4 ");
			  return ar[2];
			 }

/**inline**/ size_ar &matrix1_4::get3(){
			     if (!checkb())
				    perror("GET3 WITHOUT INITIALISATION1_4 ");
			  return ar[3];
			 }
//---------------
/**inline**/ void matrix1_4::setb() {set = TRUE;}
/**inline**/ void matrix1_4::unsetb(){set = FALSE;}
/**inline**/ boolean matrix1_4::checkb(){return set;}

/**inline**/ void matrix1_4::errorb() { if (!set) perror("matrix 1x4 used without ini");}
//---------------
/**inline**/ void matrix1_4::setm(size_ar x1,size_ar x2,size_ar x3,size_ar x4)
{
{set = TRUE;ar[0]=x1;ar[1]=x2;ar[2]=x3;ar[3]=x4;}
}
//-------------------
/**inline**/ float    matrix1_4::operator*(matrix1_4 &s2)
//esoteriko  ginomeno
{

*this = homo2can(*this); // We doing this because for speed opt.
   s2 = homo2can(s2);    // We may use s2 again-why not homo ?
return   ( getx()*s2.getx()) +
         ( gety()*s2.gety()) +
         ( getz()*s2.getz())
       ;
}
//-------------------------
/**inline**/ matrix1_4 matrix1_4::operator%(matrix1_4 &s2)
// Eksoteriko ginomeno
{
matrix1_4 temp;

*this = homo2can(*this);
s2    = homo2can(s2);
temp.setm(  (gety() * s2.getz()) - (getz() * s2.gety()) ,
            (getz() * s2.getx()) - (getx() * s2.getz()) ,
            (getx() * s2.gety()) - (gety() * s2.getx()) ,  1
         );
temp.setb();
return temp;
}
//-----------------
/**inline**/ matrix1_4 matrix1_4::operator/(float i)
                     {
                     if (i == 0) {
                                  perror("/ 0 found");
                                  return O1_4;
                                 }
                     matrix1_4 temp(ar[0],ar[1],ar[2],ar[3]*i);
                     return(temp);
                     }
/**inline**/ boolean matrix1_4::operator==(matrix1_4 &s)
                   {
                   matrix1_4 x1 = homo2can(*this);
                   matrix1_4 x2 = homo2can(s);

                   float sum = fabs (x1.getx()-x2.getx()) +
                               fabs (x1.gety()-x2.gety()) +
                               fabs (x1.getz()-x2.getz()) ;
                   return(fabs(sum) < 1e-5);
                   }

/**inline**/ void matrix4_4::setb()   {set = TRUE;}
/**inline**/ void matrix4_4::unsetb() {set = FALSE;}
//----------------------
/**inline**/ boolean matrix4_4::checkb() {return set;}
//----------------------
/**inline**/ matrix4_4::matrix4_4(size_ar  x1,size_ar  x2, size_ar x3,size_ar  x4,
               size_ar  x5,size_ar  x6, size_ar x7,size_ar  x8,
               size_ar  x9,size_ar x10,size_ar x11,size_ar x12,
               size_ar x13,size_ar x14,size_ar x15,size_ar x16)
{
          ar[0][0] =  x1;ar[0][1] =  x2;ar[0][2] =  x3;ar[0][3] =  x4;
          ar[1][0] =  x5;ar[1][1] =  x6;ar[1][2] =  x7;ar[1][3] =  x8;
          ar[2][0] =  x9;ar[2][1] = x10;ar[2][2] = x11;ar[2][3] = x12;
          ar[3][0] = x13;ar[3][1] = x14;ar[3][2] = x15;ar[3][3] = x16;
          set = TRUE;

}
//---------------
/**inline**/ void matrix4_4::set_line(int no,size_ar x1,size_ar x2,size_ar x3,size_ar x4)
{
          ar[no][0] =  x1;ar[no][1] =  x2;ar[no][2] =  x3; ar[no][3] =  x4;
          set = TRUE;
}
//---------------
/**inline**/ void matrix4_4::set_col(int no,size_ar x1,size_ar x2,size_ar x3,size_ar x4)
{
          ar[0][no] =  x1;ar[1][no] =  x2;ar[2][no] =  x3; ar[3][no] =  x4;
          set = TRUE;
}
/**inline**/ void   matrix4_4::set_ij(int i,int j,float no)
                  {
                   if ( (i>3) || (i<0) || (j>3) || (j<0) ) {
                     perror("WRONG NOS 4 SET_IJ");
                     return;
                   }
                   ar[i][j] = no;
                   set = TRUE;
                  }

/**inline**/ float  matrix4_4::get_ij(int i,int j)
                  {
                   if ( (i>3) || (i<0) || (j>3) || (j<0) || (!set) ){
                     perror("WRONG NOS 4 GET_IJ");
                     return(0);
                   }
                   return (ar[i][j]);
                  }
//---------------
