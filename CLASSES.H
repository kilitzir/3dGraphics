//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
// The classes definition.
//------------------------------------------------------------------------
class matrix1_4;
class matrix4_4;
class Line;
class polyline;
class segment;
class Window;
class Viewport;
class Ellipse;

#define point matrix1_4
#define size_ar float
#define boolean signed char
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

    size_ar& get0();
    size_ar& get1();
    size_ar& get2();
    size_ar& get3();
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

//-----------------------------------------------------------------
//                     L I N E
//-----------------------------------------------------------------
class Line {
protected:
          point first,last;
public :
        Line();
void    set_Line(float x,float y,float z);
void    set_Line(float x1,float x2,float y1,float y2,
                 float z1,float z2);
        void reset();
void    show();
Line operator=(Line &b);
};
//-----------------------------------------------------------------
//                     P O L Y L I N E
//-----------------------------------------------------------------
class polyline {
point *p;
int   no_points;
point *plane[3];  // defines which entries define a plane;
matrix1_4 N; // matrix for the above Plane;
public :
        polyline();
        polyline(float x,float y,float z);
        polyline(float *x,float *y,float *z=NULL,int no=0);
void    add(float x,float y,float z);
void    reset();
void    show();
polyline operator=(polyline &g);
};

//-----------------------------------------------------------------
//                     T E X T
//-----------------------------------------------------------------

class text {
char *p;
public :
        text();
        text(const char *source);
        ~text();
text    operator=(text &g);
void    reset();
void    add(const char *s);
void    show();
};
//-----------------------------------------------------------------
//                     C O L O R
//-----------------------------------------------------------------
class color {
int Color;
public:
     color();
     color(int n);
void set(int n);
int  get();
void reset();
void show();
};

//-----------------------------------------------------------------
//                     S E G M E N T
//-----------------------------------------------------------------
class segment;
class segment {
matrix4_4  *TRMS_S; // First Translation array
                    // Second Rotation     >>
		    // Third  Scaling >>

Line *pl;      // The list of lines
int nol;       //       No of  >>
polyline *pll; // The list of polylines
int noll;      //       No of  >>
text  *pt;     // The list of text
int not;       //      No of  texts;
color *pco;    // The List of pco;
int noco;      //      No of colors;
Ellipse *pel;  // The List of Ellipsis
int noel;      // The No of Ellipsis
int *ps;       // The list of segments
int nos;       //       No of  >>
int  *pc;      // The list of choises
int noc;       //      No of   >>

public:
     segment();
void show();
friend void AddSegmentRoutine(int no,int SegmentNo);
};
//-----------------------------------------------------------------
//                     V I E W P O R T
//-----------------------------------------------------------------

class Viewport {
matrix1_4 dl;  // Left Down
matrix1_4 ur;  // Up   Right

boolean setdl(matrix1_4 t1,matrix1_4 t2);
boolean setur(matrix1_4 t1,matrix1_4 t2);

public:
      Viewport();
      Viewport(float xmin,float xmax,float ymin,float ymax);
      Viewport(matrix1_4 x1,matrix1_4 x2);
void  V(float xmin,float xmax,float ymin,float ymax);
void  V(matrix1_4 x1,matrix1_4 x2);
void  set();
void  set(float xmin,float xmax,float ymin,float ymax);
void  set(matrix1_4 x1,matrix1_4 x2);
void  show();
float getXmin();
float getXmax();
float getYmin();
float getYmax();

};
#define getUmin    getXmin
#define getUmax    getXmax
#define getVmin    getYmin
#define getVmax    getYmax
//-----------------------------------------------------------------
//                       W I N D O W
//-----------------------------------------------------------------

class Window {
float   Xmin,Xmax,
	Ymin,Ymax;
boolean SetX,SetY;
public:
	 Window();
	 Window(float xmin,float xmax,float ymin,float ymax);
void     setY(float xmin,float xmax);
void     setX(float ymin,float ymax);
void     set(float xmin,float xmax,float ymin,float ymax);
float    getXmin();
float    getXmax();
float    getYmin();
float    getYmax();
boolean  checkb();
};
//-----------------------------------------------------------------
//                     E L L I P S E
//-----------------------------------------------------------------
class Ellipse {
point len1,len2; // we need 3 points the define the ellipsis,in 3d
point Center;    // and in this way, we have it !;
float x_a,y_b;   //the 2 lengths of the ellipsis
matrix4_4 elC2WC;// the tran matrix, from ellipse's coordinates to world
public:	         // coordinates
	Ellipse();
	Ellipse(point CenterP,point len1P,point len2P);
	Ellipse(point CenterP,float a,float b);
	~Ellipse();
void    show();
void    set(point CenterP,point len1P,point len2P);
void    set(point CenterP,float a,float b);
void    reset();
private: // used by the show, to show the regions
void stage_1(float a,float b,int l,int &x, int &y);
void stage_2(float a,float b,int l,int x, int y);
void CalcMatrix(); //calcs the elC2WC
void putpoint(float x, float y);  // calcs the ElC2WC 2 PC, it does the clipping
				  // puts the pixel.
};

