#include <gsp.h>
#pragma hdrstop
#include <string.h>
//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
/* Member functions of the text class. All the functions can be inlined.
*/
/**
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
**/
//------------------------------------------------------------------------

/**inline**/ void text::text()
           { p = NULL; }
/**inline**/ void text::text(const char *source)
           {
           if (source == NULL)
                    p = NULL;
           else {
              int Temp = strlen(source);
              p = new char[Temp+1];
              if (!p) perror("Not enough memory for a text");
              strncpy(p,source,Temp);
           }
           }
/**inline**/ void text::~text()
          {
           if (p) delete p;
          }
/**inline**/ text    text::operator=(text &g)
          {
          if (p) delete p;
          if (!g.p)
              p = NULL;
          else {
              int Temp = strlen(g.p);
              p = new char[Temp+1];
              if (!p) perror("Not enough memory for a text");
              strncpy(p,g.p,Temp);
          }
          return *this;
          }
/**inline**/ void   text::reset() { if (p) delete p;}
/**inline**/ void   text::add(const char* s)
           {
           if (p == NULL) {
             p = new char[strlen(s)+1];
             p[0] = 0; // We need it for strcat
           }
           else
             {
             p = Realloc(p,(strlen(p)+strlen(s)+1) * sizeof(char));
             strcat(p,s);
             // free(s);
             }
           }
/**inline**/ void text::show() {outtext(p);}
