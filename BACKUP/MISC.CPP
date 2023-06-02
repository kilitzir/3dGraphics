#include <gsp.h>
#pragma hdrstop
//------------ R E A L L O C
template <class T>
T _FAR * _Cdecl Realloc(T *p,unsigned NewSize)
    {
     T Temp= new T[NewSize];
     memcpy(Temp,p,NewSize * sizeof(T));
     delete p;
     return(Temp);
    }
template <class T>
void _FAR  _Cdecl swap (T &x,T &y)
{
T temp = x;
x = y;
y = Temp;
}

