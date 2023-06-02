#ifndef _H_face_
#define _H_face_


typedef enum { objFace, objLine, objText, objPoint } objType;

typedef struct _typeFace {
     int		numPoints;   	/* passed (need minimum 3 points) */
     vertex_index *	points;		/* passed (no sentinel) */
} typeFace;

typedef struct _typeLine {
     MAT3hvec			end1, end2;			/* passed */
} typeLine;

typedef struct _typeText {
     char *			text;
} typeText;

typedef struct _typePoint {
   char dummy;
} typePoint;


typedef struct _obj {
     
     /* object type */
     objType			type;		/* face, line, or text */
     
     /* pointer to the next object */
     struct _obj * 		next;

     /* normal (for face, text) */
     MAT3hvec 			normal;		/* passed for face */
     
     /* bounding cube */
     /* for face: we calculate */
     /* for point: pass coordinates in min[x], min[y], min[z] */
     /* for line: we calculate */
     /* for text: pass z in min[z], pass min and max [x] and [y] */
     MAT3hvec			min;
     MAT3hvec			max;
     
     /* color intensity */
     double	intensity;  	/* should actually be a field in "typeFace" structure */
     
     /* pointer to specifics */
     attribute_group 		attributes;

     /* plane equation */
     double			directed_distance;
     
     /* object specifics */
     union {
	  typeFace		face;
	  typeLine		line;
	  typeText		text;
	  typePoint		point;
     } data;

     /* stored for all objects */
     MAT3hvec			p_min;
     MAT3hvec			p_max;
     boolean			already_moved;
     MAT3hvec			p_normal;
     unsigned short		traversal_index;  /* used for pick correlation */
} obj;


extern void convexify();
extern void cull( );
extern void clip( );
extern void calc_intensity( );
extern void map_to_canon( );
extern void generate_pdc_vertices( );
extern void zsort( );

#endif
