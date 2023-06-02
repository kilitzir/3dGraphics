#include <stdio.h>

/* the special screen canvas */
#define SCREEN_CANVAS		0

#define SCREEN_WIDTH            -1
#define SCREEN_HEIGHT		-2



/* write mode */
#define WRITE_REPLACE               0
#define WRITE_XOR                   2
#define WRITE_OR                    1
#define WRITE_AND                   7

typedef void (*funcptr)();


/* GEOMETRIC DATA TYPES */
typedef struct {int x, y;} 				srgp__point;
typedef struct {srgp__point bottom_left, top_right;}	srgp__rectangle;


typedef unsigned char boolean;

/*!*/
/* ATTRIBUTE BUNDLE (application should never use internals) */
typedef struct {
   int write_mode;
   srgp__rectangle clip_rectangle;
   int font;
   int line_style, line_width;
   int marker_size, marker_style;
   int color, background_color;
   int plane_mask;
   int fill_style;
   int fill_pixmap_pattern_id;
   int fill_bitmap_pattern_id;
   int pen_style;
   int pen_pixmap_pattern_id;
   int pen_bitmap_pattern_id;
} srgp__attribute_group;


typedef struct {
   srgp__point position;
   int button_chord[3];
   int button_of_last_transition;
} srgp__locator_measure;

typedef struct {
	int seconds;
	int ticks;
} srgp_timestamp;

typedef struct {
   srgp__point position;
   int button_chord[3];
   int button_of_last_transition;
	int modifier_chord[3];
	srgp_timestamp timestamp;
} srgp__deluxe_locator_measure;

typedef struct {
	char *buffer;
	int buffer_length;
	int modifier_chord[3];
	srgp_timestamp timestamp;
} srgp__deluxe_keyboard_measure;

#ifdef SRGP_BOSS
#define DECLARE
#else
#define DECLARE extern
#endif

DECLARE int		COLOR_BLACK, COLOR_WHITE;
#define SRGP_BLACK  COLOR_BLACK
#define SRGP_WHITE  COLOR_WHITE

DECLARE FILE            *SRGP_logStream;

#undef DECLARE



/** SRGP ROUTINES THAT RETURN NON-VOID VALUES
**/

srgp__point SRGP_defPoint (int x, int y);
srgp__rectangle SRGP_defRectangle (int left_x, int lower_y, int right_x, int upper_y);

int SRGP_createCanvas (int width, int height);

int SRGP_waitEvent (int maximum_wait_time);

srgp__rectangle SRGP_inquireClipRectangle (void);
int SRGP_inquireWriteMode (void);
int SRGP_inquireFont (void);
int SRGP_inquireLineStyle (void);
int SRGP_inquireColor (void);
int SRGP_inquireBackgroundColor (void);
int SRGP_inquirePattern (void);

int SRGP_inquireActiveCanvas (void);
int SRGP_inquireCanvasDepth (void);
srgp__rectangle SRGP_inquireCanvasExtent (int canvas_index);


/** SRGP ROUTINES THAT RETURN VOID VALUES
**/
void SRGP_begin (char *name, int width, int height, int planes, boolean please_trace);
void SRGP_beep (void);
void SRGP_copyPixel (int source_canvas_index, srgp__rectangle source_rect, srgp__point dest_corner);
void SRGP_deleteCanvas (int canvas_index);
void SRGP_ellipse (srgp__rectangle rect);
void SRGP_end (void);
void SRGP_fillEllipse (srgp__rectangle rect);
void SRGP_fillPolygon (int vert_count, srgp__point *vertices);
void SRGP_fillPolygonCoord (int vert_count, int *x_coords, int *y_coords);
void SRGP_fillRectangle (srgp__rectangle rect);
void SRGP_fillRectangleCoord (int left_x, int lower_y, int right_x, int upper_y);
void SRGP_fillRectanglePt (srgp__point lower_left, srgp__point upper_right);
void SRGP_getDeluxeKeyboard (srgp__deluxe_keyboard_measure *measure);
void SRGP_getDeluxeLocator (srgp__deluxe_locator_measure *measure);
void SRGP_getKeyboard (char *measure, int bufsize);
void SRGP_getLocator (srgp__locator_measure *measure);
void SRGP_inquireAttributes (srgp__attribute_group *group);
void SRGP_inquireCanvasSize (int canvas_index, int *width, int *height);
void SRGP_inquireColorTable (int index, int count, unsigned short *red, unsigned short *green, unsigned short *blue);
void SRGP_inquireTextExtent (char *str, int *width, int *ascent, int *descent);
void SRGP_line (srgp__point pt1, srgp__point pt2);
void SRGP_lineCoord (int x1, int y1, int x2, int y2);
void SRGP_loadBitmapPattern (int index, char *data);
int  SRGP_loadBitmapPatternsFromFile (FILE *stream);
void SRGP_loadPixmapPattern (int index, int *data);
int  SRGP_loadPixmapPatternsFromFile (FILE *stream);
void SRGP_loadColorTable (int startentry, int count, unsigned short *red, unsigned short *green, unsigned short *blue);
void SRGP_loadCommonColor (int entry, char *colorname);
void SRGP_loadCursorTable (int index, int cursor);
void SRGP_loadFont (int font_index, char *filename);
void SRGP_point (srgp__point pt);
void SRGP_pointCoord (int x, int y);
void SRGP_polygon (int vert_count, srgp__point *vertices);
void SRGP_polygonCoord (int vert_count, int *x_coords, int *y_coords);
void SRGP_polyLine (int vert_count, srgp__point *vertices);
void SRGP_polyLineCoord (int vert_count, int *x_coords, int *y_coords);
void SRGP_polyMarker (int vert_count, srgp__point *vertices);
void SRGP_polyMarkerCoord (int vert_count, int *x_coords, int *y_coords);
void SRGP_polyPoint (int vert_count, srgp__point *vertices);
void SRGP_polyPointCoord (int vert_count, int *x_coords, int *y_coords);
void SRGP_rectangle (srgp__rectangle rect);
void SRGP_rectangleCoord (int left_x, int lower_y, int right_x, int upper_y);
void SRGP_rectanglePt (srgp__point lower_left, srgp__point upper_right);
void SRGP_refresh (void);
void SRGP_sampleDeluxeKeyboard (srgp__deluxe_keyboard_measure *measure);
void SRGP_sampleDeluxeLocator (srgp__deluxe_locator_measure *measure);
void SRGP_sampleKeyboard (char *measure, int bufsize);
void SRGP_sampleLocator (srgp__locator_measure *measure);
void SRGP_setAttributes (srgp__attribute_group *group);
void SRGP_setBackgroundColor (int pixelvalue);
void SRGP_setClipRectangle (srgp__rectangle value);
void SRGP_setColor (int pixelvalue);
void SRGP_setFillBitmapPattern (int index);
void SRGP_setFillPixmapPattern (int index);
void SRGP_setFillStyle (int value /* SOLID, BITMAP_PATTERN_OPAQUE, BITMAP_PATTERN_TRANSPARENT, PIXMAP_PATTERN */);
void SRGP_setFont (int font_index);
void SRGP_setInputMode (int device /* LOCATOR, KEYBOARD */, int mode /* INACTIVE, SAMPLE, EVENT */);
void SRGP_setKeyboardEchoColor (int color_index);
void SRGP_setKeyboardEchoFont (int font_index);
void SRGP_setKeyboardEchoOrigin (srgp__point position);
void SRGP_setKeyboardProcessingMode (int value /* EDIT, RAW */);
void SRGP_setKeyboardMeasure (char *value);
void SRGP_setLineStyle (int value /* CONTINUOUS, DASHED */);
void SRGP_setLineWidth (int width_in_pixels);
void SRGP_setMarkerStyle (int style);
void SRGP_setMarkerSize (int size);
void SRGP_setLocatorButtonMask (int mask);
void SRGP_setLocatorEchoCursorShape (int cursor_index);
void SRGP_setLocatorEchoRubberAnchor (srgp__point position);
void SRGP_setLocatorEchoType (int value /* NO_ECHO, CURSOR, RUBBER_LINE, RUBBER_RECT */);
void SRGP_setLocatorMeasure (srgp__point value);
void SRGP_setPenBitmapPattern (int index);
void SRGP_setPenPixmapPattern (int index);
void SRGP_setPenStyle (int value /* SOLID, BITMAP_PATTERN_OPAQUE, BITMAP_PATTERN_TRANSPARENT, PIXMAP_PATTERN */);
void SRGP_setPlaneMask (int bitmask);
void SRGP_setWriteMode (int value /* REPLACE, XOR, OR, AND */);
void SRGP_text (srgp__point origin, char *str);
void SRGP_tracing (boolean please_trace);
void SRGP_useCanvas (int canvas_index);

void SRGP_forceSquarePixels (void);
void SRGP_setVideoMode (int mode);
