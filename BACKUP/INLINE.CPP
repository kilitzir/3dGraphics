//------------------------------------------------------------------------
//                   SIMPLE GRAPHIC INTERACTIVE PROGRAM
//                        MADE BY CHRIS KILITZIRAKIS
//                              Clopyright
//                            No rights reserved
//------------------------------------------------------------------------
// Some inlined functios. Use Realloc with doubt. It's not fully
// debug yet. On the other hand, if t's so easy, why BC didn't implemented ?
//------------------------------------------------------------------------
//------------ R E A L L O C
template <class T>
       T _FAR * _Cdecl Realloc(T *p,unsigned NewSize)
    {
     T *Temp= new T[NewSize];
     if (Temp) {
        memcpy((void*)Temp,(void*)p,NewSize * sizeof(T));
        delete p;
     }
     else
        perror("REALLOC NO MEMORY");
     return(Temp);
    }
//------------ S W A P
template <class T>
       void _FAR  _Cdecl swap (T &x,T &y)
{
T Temp = x;
x = y;
y = Temp;
}
//-------- C A N 2 H O M O
inline matrix1_4 can2homo(matrix1_4 source)
{

if ( (source.get3() == 0) || (source.set == 0))
        perror("NO TRANS CAN BE DONE");

source.ar[3] = 1;
return (source);
}
//----------- HOMO2CAN
inline  matrix1_4  homo2can(matrix1_4 t)
     { return t.get3() == 1 ?t :homo2can1(t); }

