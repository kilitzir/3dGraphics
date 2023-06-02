.AUTODEPEND

.PATH.obj = C:.

#		*Translator Definitions*
CC = bcc +GSP.CFG
TASM = tasm
TLIB = tlib
TLINK = tlink
LIBPATH = C:\BC\LIB
INCLUDEPATH = C:\BC\INCLUDE;C:.


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
 ellipse.obj \
 clipping.obj \
 color.obj \
 const.obj \
 copy.obj \
 fliteco.obj \
 fr_matri.obj \
 fr_segme.obj \
 line.obj \
 main.obj \
 matrix.obj \
 menu.obj \
 pre_seg.obj \
 projectm.obj \
 segment.obj \
 test.obj \
 text.obj \
 util.obj \
 viewport.obj \
 window.obj

#		*Explicit Rules*
c:.\gsp.exe: gsp.cfg $(EXE_dependencies)
  $(TLINK) /v/x/i/c/P-/L$(LIBPATH)/o @&&|
/o- c0m.obj+
c:.\ellipse.obj+
c:.\clipping.obj+
c:.\color.obj+
c:.\const.obj+
c:.\copy.obj+
c:.\fliteco.obj+
c:.\fr_matri.obj+
c:.\fr_segme.obj+
c:.\line.obj+
c:.\main.obj+
c:.\matrix.obj+
c:.\menu.obj+
c:.\pre_seg.obj+
c:.\projectm.obj+
c:.\segment.obj+
c:.\test.obj+
c:.\text.obj+
c:.\util.obj+
c:.\viewport.obj+
c:.\window.obj
c:.\gsp
		# no map file
overlay.lib+
graphics.lib+
fp87.lib+
mathm.lib+
cm.lib
|


#		*Individual File Dependencies*
ellipse.obj: gsp.cfg ellipse.cpp 

clipping.obj: gsp.cfg clipping.cpp 

color.obj: gsp.cfg color.cpp 

const.obj: gsp.cfg const.cpp 

copy.obj: gsp.cfg copy.cpp 

fliteco.obj: gsp.cfg fliteco.cpp 

fr_matri.obj: gsp.cfg fr_matri.cpp 

fr_segme.obj: gsp.cfg fr_segme.cpp 

line.obj: gsp.cfg line.cpp 

main.obj: gsp.cfg main.cpp 

matrix.obj: gsp.cfg matrix.cpp 

menu.obj: gsp.cfg menu.cpp 

pre_seg.obj: gsp.cfg pre_seg.cpp 

projectm.obj: gsp.cfg projectm.cpp 

segment.obj: gsp.cfg segment.cpp 

test.obj: gsp.cfg test.cpp 

text.obj: gsp.cfg text.cpp 

util.obj: gsp.cfg util.cpp 

viewport.obj: gsp.cfg viewport.cpp 

window.obj: gsp.cfg window.cpp 

#		*Compiler Configuration File*
gsp.cfg: gsp.mak
  copy &&|
-mm
-2
-a
-f287
-C
-w+
-N
-v
-y
-G
-O
-Og
-Oe
-Om
-Ov
-Ol
-Ob
-Oa
-Op
-Oi
-Z
-r-
-d
-Y
-vi
-H=GSP.SYM
-nC:.
-I$(INCLUDEPATH)
-L$(LIBPATH)
-D_Only_Compile
| gsp.cfg


