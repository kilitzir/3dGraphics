//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Copyright 1995
//                            No rights reserved
//------------------------------------------------------------------------
// Fuction prototypes and defines. As you see, many of the most common
// functions are #defined.
//------------------------------------------------------------------------
void OpenSegment(int no);
void CloseSegment();
#define AddSegment(x) AddSegmentRoutine(SEG_SEGMENT,(x))
void ShowSegment(int x);
void AddSegmentRoutine(int no,int SegmentNo);
void OpenDev();
void CloseDev();
void menu();
//-------------------------------------------
// F R I E N D S   O F   P O L Y / L I N E
void AddLine(float x,float x1,float y,float y1,float z=CPz,float z1 = CPz);

matrix1_4 homo2can1(matrix1_4 x);
matrix1_4 WC2PC(matrix1_4 s);
matrix1_4 NDC2DC(matrix1_4 s);
matrix4_4 MakeProjectionMatrix();
#define RecalcProjectionMatrix(); *CurrentProjectMatrix = MakeProjectionMatrix();
#define RecalcViewMatrix() *CurrentViewMatrix = *CurrentTransformMatrix * \
						 *CurrentProjectMatrix



//-------- M O V E A B S 3
#define MoveAbs3(x,y,z)    CPx = x;CPy = y;CPz = z;
#define MoveRel3(x,y,z)    MoveAbs3(CPx+(x),CPy+(y),CPz+(z))
#define MoveAbs2(x,y)      MoveAbs3((x),(y),CPz)
#define MoveRel2(x,y)      MoveRel3((x),(y),0)
//---- L I N E   R O U T I N E S
#define LineAbs3(x,y,z) AddLine(CPx,(x),CPy,(y),CPz,(z))
#define LineRel3(x,y,z) AddLine(CPx,CPx+(x),CPy,CPy+(y),CPz,CPz+(z))
#define LineAbs2(x,y)   LineAbs3((x),(y),CPz)
#define LineRel2(x,y)   LineRel3((x),(y),0)
void MyLine(int x1,int y1,int x2,int y2);
//---- P O L Y L I N E   R O U T I N E S
void Add2Poly(float x,float y,float z);
#define Add2PolyRel(x,y,z) Add2Poly(CPx+(x),CPy+(y),Pz+(z))
void AddPoly();
inline void ResetPoly() {
	if (!CurrentPolyline) {
		cerr<<"ResetPoly:No CurrentPolyline!!!"<<endl;
		CurrentPolyline = new polyline;
	}
	else
		CurrentPolyline->reset();
}
//---- O T H E R   O B J E C T S   R O U T I N E S
void AddEllipses(point x1,point x2,point x3);
void AddEllipses(point x1,float x2,float x3);
void Color(int color);
void Text(const char *s);

//---- T R A N S F O R M A T I O N   R O U T I N E S
// we don't forget that the arcs are in degrees !!!
matrix4_4 TRANSLATE3(float dx,float dy,float dz);
	  #define TRANSLATE2(x,y) TRANSLATE3((x),(y),0)
matrix4_4 SCALE3(float Sx,float Sy,float Sz);
	  #define SCALE2(x,y) SCALE3((x),(y),0)

matrix4_4 ROTATEX3(float arc);
matrix4_4 ROTATEY3(float arc);
matrix4_4 ROTATEZ3(float arc);
matrix4_4 ROTATE3(float thetax,float thetay,float thetaz);
	  #define ROTATE2(y) ROTATE3(0,0,(y))

matrix4_4 ROTATEPOINT2(float x,float y,float arc);
matrix4_4 ROTATEPOINT2(matrix1_4 t,float arc);
matrix4_4 SCALEPOINT2(float x,float y, float Sx,float Sy);

#define ROTATEPOINT3(x,y,z,arcx,arcy,arcz)\
	 ( TRANSLATE3(-(x),-(y),-(z)) * ROTATE3((arcx),(arcy),(arcz)) * \
	 TRANSLATE3((x),(y),(z)) )
#define SCALEPOINT3(x,y,z,Sx,Sy,Sz)       \
	 ( TRANSLATE3(-(x),-(y),-(z)) * SCALE3((Sx),(Sy),(Sy)) * \
	  TRANSLATE3((x),(y),(z)) )
#define  Rotate3(thetax,thetay,thetaz) (*CurrentTRMr = *CurrentTRMr * \
					 ROTATE3((thetax),(thetay),(thetaz)))
#define  Scale3(Sx,Sy,Sz)(*CurrentTRMs = *CurrentTRMs * \
					 SCALE3((Sx),(Sy),(Sz)))
#define Translate3(dx,dy,dz)  (*CurrentTRMt = *CurrentTRMt * \
					    TRANSLATE3((dx),(dy),(dz)))

#define Translate2(dx,dy)  Translate3((dx),(dy),0)
#define Scale2(Sx,Sy) Scale3((Sx),(Sy),0)
#define Rotate2(arc) Rotate3(0,0,(arc))
//-----S E T T I N G   R O U T I N E S
#define SetVPR(x,y,z)   VPR.setm((x),(y),(z),1)
#define SetVUV(x,y,z)   VUV.setm((x),(y),(z),1)
#define SetVPN(x,y,z)   VPN.setm((x),(y),(z),1)
#define SetCOP(x,y,z)   COP.setm((x),(y),(z),1)
#define SetDOP(x,y,z)   DOP.setm((x),(y),(z),1)

void SetWindow(float xmin,float ymin,float xmax,float ymax);
void SetWindow(matrix1_4 min,matrix1_4 max);
void SetViewport2(float xmin,float ymin,float xmax,float ymax);
void SetViewport3(float xmin,float ymin,float zmin,
		 float xmax,float ymax,float zmax);
//------------------------
// right 2 left coordinates
matrix1_4 r2l(matrix1_4 t);
matrix1_4 r2l(float x,float y,float z);

void InitVariables();
//------------------------

#define limit(x,up_x,down_x) ( ((x)>=(up_x)) && ( (x)<= (down_x)) )
//---------------------------
//------ C L I P P I N G   R O U T I N E S
#define SetClippingFront(x)  ClippingFront = (x)
#define SetClippingBack(x)   ClippingBack  = (x)
boolean  ClipLine2(matrix1_4 &mx1,matrix1_4  mx2);
boolean  ClipLineParallel (matrix1_4 &mx1,matrix1_4  mx2);
boolean  ClipLinePerspective(matrix1_4 &mx1,matrix1_4  mx2);

#define ClipLine3(x1,x2)    (ProjectionType == PERSPECTIVE) ? \
                              ClipLinePerspective((x1),(x2)):  \
                              ClipLineParallel((x1),(x2))


#define ClipLine(x1,x2)    (ProjectionType == D2)?ClipLine2((x1),(x2)):\
                                                 ClipLine3((x1),(x2))

#define ClipPoly(x,y)   ProjectionType == D2?ClipPoly2((x),(y)):ClipPoly3((x),(y))
#define ClipPoly3(x,y)  ClipPoly2((x),(y))
#define ClipPoly2(x,y)  (y=new int,y[0] = 0)
#define ClipText(p)     (p)

//-----------
// MISCELANOUS ROUTINES
#define SetWorld(x)  (ProjectionType = (x))
float abs(matrix1_4 t);
void Predefsegments();
void test();