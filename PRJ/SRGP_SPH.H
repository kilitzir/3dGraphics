/** PUBLIC CONSTANTS AND TYPES COMMON TO BOTH PACKAGES
**/

/* implementation-specific constants */
#define PATTERN_SPEC_SIZE	16
#define MAX_PATTERN_INDEX      150
#define MAX_CURSOR_INDEX	25
#define MAX_FONT_INDEX          50
#define MAX_CANVAS_COUNT       100
#define MAX_STRING_SIZE		80
#define MAX_POINTLIST_SIZE     100


/*!*/
/* EXTRA DATA TYPES */
/*
typedef unsigned char boolean;
*/

#define TRUE  1
#define FALSE 0



/*!*/
/* ATTRIBUTES */

/* fill style or pen style */
#define SOLID			       	0	/*FillSolid in X.h*/
#define PIXMAP_PATTERN		 	1	/*FillTiled*/
#define BITMAP_PATTERN_TRANSPARENT     	2	/*FillStippled*/
#define BITMAP_PATTERN_OPAQUE		3	/*FillOpaqueStippled*/

/* line style */
/*    If you change any of these numbers, see attribute.c!!! */
#define NUMBER_OF_LINE_STYLES		4
#define CONTINUOUS			0
#define DASHED				2
#define DOTTED				4
#define DOT_DASHED			7


/* marker style */
#define NUMBER_OF_MARKER_STYLES		3
#define MARKER_CIRCLE			0
#define MARKER_SQUARE			1
#define MARKER_X			2


/*!*/
/* INPUT RELATED STUFF */

/* input device */
#define NO_DEVICE		0
#define TIMEOUT			NO_DEVICE
#define KEYBOARD		1
#define LOCATOR			2

/* input mode */
#define INACTIVE		1
#define SAMPLE			2
#define EVENT			3

/* locator measure */
#define LEFT_BUTTON   0
#define MIDDLE_BUTTON 1
#define RIGHT_BUTTON  2
#define    LEFT_BUTTON_MASK   1
#define    MIDDLE_BUTTON_MASK 2
#define    RIGHT_BUTTON_MASK  4
#define SHIFT   0
#define CONTROL 1
#define META    2


/* keyboard processing mode */
#define EDIT			1
#define RAW			2

/* locator/pointer echo type */
#define NO_ECHO			0
#define CURSOR			1
#define RUBBER_LINE		2
#define RUBBER_RECT		3

/* button status */
#define UP		0
#define DOWN		1

/* time-out spec */
#define INDEFINITE              -1


/* conveniences */
#define		NIL		0

/* explosions of geometric records */
#define ExplodeRect(R)   R.bottom_left.x,R.bottom_left.y,R.top_right.x,R.top_right.y
#define ExplodePt(P)     P.x,P.y


/* Graphics Adaptor Definitions */
#define ATI800x600   533   /* ATI VGAWonder                    */
#define ATI640x480X  534   /*   640x480 256-color					*/
#define ATI1024x768F 535   /*   1024x768 16-color					*/
#define ATT          128   /* AT&T Std. Color & DEB Adaptors   */
#define ATT640x400   128   /*   640x400 monochrome             */
#define DEB640x200   129   /*   640x200 16-color               */
#define DEB640x400   130   /*   640x400 16-color               */
#define CGA          6     /* IBM Color Graphics Adaptor (CGA) */
#define CGA320x200   4     /*   320x200 4-color                */
#define CGA640x200   6     /*   640x200 2-color                */
#define COR             34 /* Cornerstone                      */
#define COR1600x1280V   34 /*   Vista 1600 1600x1280 mono      */
#define COR1600x1280VA  37 /*   Vista 1600 1600x1280 no em, 2 mon */
#define COR1600x1280DP  35 /*   DualPage   1600x1280 mono      */
#define COR1600x1280DPA 36 /*   DualPage 1600x1280, no JP1     */
#define COR1600x1280MCA 39 /* DualPage 1600x1280 Micro Channel */
#define EGA          512   /* IBM Enhanced Graphics Adaptor    */
#define EGAMono      512   /*   640x350 monochrome             */
#define EGA320x200   544   /*   320x200 16-color               */
#define EGA640x200   528   /*   640x200 16-color               */
#define EGA640x350   560   /*   640x350 16-color (128k EGA)    */
#define MGA640x350   561   /*   640x350 2-color                */
#define EGA640x480   562   /*   640x480 16-color  (VGA)        */
#define MGA640x480   563   /*   640x480 2-color   (MCGA)       */
#define VGA320x200   564   /*   320x200 256-color (PS2 VGA)    */
#define EGA640x350S  565   /*   640x350 16-color (no bios-EGA) */
#define VGA640x350S  566   /*   640x350 16-color (no bios-VGA) */ 
#define VGA640x480S  567   /*   640x480 16-color (no bios-VGA) */   
#define EGA640x350MP 131   /* IBM EGA, in multi planar setting */	
#define JRT320x200   569   /*   320x200 16-color IBM PCjr & Tandy 1000 EX */
#define EVA          516   /* Tseng Labs EVA/480               */
#define EVA640x480   516   /*   640x480 16-color               */
#define EVR          1024  /* Everex Graphics Edge Adaptor     */
#define EVR640x200   1024  /*   640x200 16-color               */
#define EVR640x400   1025  /*   640x400 4-color                */
#define EVX800x600   532   /* Everex EVGA EV-673 Adaptor       */
#define FKY1120x750  2200  /* Fujitsu FMR 70 16 color          */	
#define FKY640x400   2201  /* Fujitsu FMR 60 16 color          */
#define FKY1120x750m 2202  /* Fujitsu FMR 70 monochrome        */	
#define GEN          529   /* Genoa SuperEGA HiRes             */
#define GEN640x480   529   /*   640x480 16-color               */
#define GEN800x600   518   /*   800x600 16-color               */
#define GEN1024x768  519   /* Genoa SuperVGA HiRes-10 16-color */ 
#define GEN640x350X  530   /*   640x350 256-color              */  
#define GEN640x480X  531   /*   640x480 256-color              */  
#define HER          8     /* Hercules/AST Monochrome Adaptor  */
#define HER720x348   8     /*   720x348 monochrome             */
#define MDS          2     /* MDS Genius Graphics Display      */
#define MDS736x1008  2     /*   736x1008 monochrome            */
#define NNR512x512   4096  /* Number Nine 512x485 256-color    */
#define NNR1024x768  4097  /*    2048x4 @ 1024x768x16          */
#define NSI          514   /* NSI Logic Smart EGA/Plus         */
#define NSI800x600   514   /*   800x600 16-color               */
#define OCD800x600   571   /* Orchid Designer VGA 800x600x16   */ 
#define OCD1024x768  572   /*   1024x768 16 color              */
#define OCD640x350X  573   /*   640x350 256 color              */   
#define OCD640x480X  574   /*   640x480 256 color              */   
#define PAR          517   /* Paradise AutoSwitch EGA/480      */
#define PAR640x480   517   /*   640x480 16-color               */
#define PAR800x600   579   /* Paradise OEM 8/16 800x600 16-color */
#define SIG          32    /* Sigma Design                     */
#define SIG640x400   32    /*   640x400 16-color, Color-400    */
#define SIG1664x1200 33    /*   LaserView 1664x1200 monochome  */
#define SIG1664x1200A 38   /*   1664x1200 @0A000               */
#define SIG1664x1200MCA 41 /*   1664x1200 Micro channel        */
#define STB          256   /* STB GraphicsPlus-II Adaptor      */
#define STB640x352   256   /*   640x352 monochrome             */
#define STB320x200   257   /*   320x200 16-color               */
#define STB640x200   258   /*   640x200 4-color                */
#define STB640x400   384   /*   640x400 monochrome             */
#define STB800x600   571   /* STB VGA Extra/EM 800x600x16      */       
#define STB1024x768  572   /*   1024x768 16 color              */       
#define STB640x350X  573   /*   640x350 256 color              */ 
#define STB640x480X  574   /*   640x480 256 color              */ 
#define TEC          16    /* Tecmar Graphics-Master Adaptor   */
#define TEC720x352   16    /*   720x352 monochrome             */
#define TEC720x704   17    /*   720x704 monochrome             */
#define TEC320x200   18    /*   320x200 16-color               */
#define TEC640x200   19    /*   640x200 16-color               */
#define TEC640x400   20    /*   640x400 16-color               */
#define TEC640x350X  575   /* Tecmar VGA/AD, 640x350 256-color */
#define TEC640x480X  576   /*   640x480 256-color              */
#define TEC800x600   577   /*   800x600 16-color               */
#define TEC1024x768  578   /*   1024x768 16-color              */ 
#define TOS          16384 /* Toshiba 3100                     */
#define TOS640x400   16384 /*   640x400 monochrome             */
#define TARG512x482  8192  /* TrueVision Targa M8 512x482 256-color */
#define TTS          2048  /* IBM 3270 PC                      */
#define TTS720x350   2048  /*   720x350 monochrome             */
#define TTS360x350   2049  /*   360x350 4-color                */
#define VESA800x600  526   /* V.E.S.A. std 800x600 16-color    */
#define VGA          520   /* Video-7 VEGA Deluxe              */
#define VGA640x480   520   /*   640x480 16-color               */
#define VGA752x410   521   /*   752x410 16-color               */
#define VGA720x540   522   /* V7 VGA  720x540 16-color         */
#define VGA800x600   523   /*   800x600 16-color  (VGA)        */
#define VGA640x480X  525   /* V7 640x480 256-color             */
#define VGA1024x768x2 527  /*   1024x768 2-color               */
#define VGA1024x768  536   /* VGA 1024 i 1024x768 16-color     */
#define WYS          64    /* Wyse WY-700 Graphics Display     */
#define WYS1280x800  64    /*   1280x800 monochrome            */
#define WYS1280x400  65    /*   1280x400 monochrome            */
#define WYS640x400   66    /*   640x400 monochrome             */
#define MEC1120x750  610   /* NEC PC 98XA monochrome           */
#define MEC640x400   611   /* NEC PC 98VM monochrome           */
#define NEC1120x750  626   /* NEC PC 98XA 16-color             */
#define NEC640x400   627   /* NEC PC 98VM 16-color             */

/* Defines for National Design Genesis-1024/1280 */
#define NDI640x480x4D   0x4140   /* 640x480   16-color, digitl */
#define NDI640x480x4A   0x4141   /* 640x480   16-color, analog */
#define NDI1024x768x4J  0x4148   /* 1024x768  16-color, JVC    */
#define NDI1024x768x4M  0x4149   /* 1024x768  16-color, Mitsu. */
#define NDI1280x1024x4J 0x414A   /* 1280x1024 16-color, JVC    */
#define NDI960x720x4N   0x414B   /* 960x720   16-color, NEC XL */

/* Defines for RenaissanceGRX Rendition-II       */
#define GRX640x480x4A   0x4240   /* 640x480   16-color, analog */
#define GRX800x600x4A   0x4242   /* 800x600   16-color, analog */
#define GRX1024x768x4A  0x4246   /* 1024x768  16-color, analog */
#define GRX640x480x8A   0x4248   /* 640x480  256-color, analog */
#define GRX800x600x8A   0x424A   /* 800x600  256-color, analog */
#define GRX1024x768x8A  0x424C   /* 1024x768 256-color, analog */

/* Defines for Hewlett-Packard HP82328 IGC       */
#define HP1024x768x4    0x664A /* 1024x768  16-color         */

/* Defines for IBM 8514A (and compatibles)       */
#define EFF640x480x4    0x7000 /*  640x480   16-color          */
#define EFF640x480x8    0x7001 /*  640x480  256-color          */
#define EFF1024x768x4I  0x7040 /* 1024x768   16-color, intlacd */
#define EFF1024x768x4N  0x7041 /* 1024x768   16-color, non-inl */
#define EFF1024x768x8I  0x7042 /* 1024x768  256-color, intlacd */
#define EFF1024x768x8N  0x7043 /* 1024x768  256-color, non-inl */
#define EFF1280x1024x4I 0x7080 /* 1280x1024  16-color, intlacd */
#define EFF1280x1024x4N 0x7081 /* 1280x1024  16-color, non-inl */
#define EFF1280x1024x8I 0x7082 /* 1280x1024 256-color, intlacd */
#define EFF1280x1024x8N 0x7083 /* 1280x1024 256-color, non-inl */

#define CUST_LIN   CGA640x200  /* User defined linear memory */
#define CUST_BS    SIG640x400  /* User defined Bank select   */
#define CUST_EGA   EGA640x350  /* User defined EGA Superset  */
