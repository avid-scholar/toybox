#ifndef AEON__LIBS_MEM_MAF_H
#define AEON__LIBS_MEM_MAF_H 1

inline byte * ma (size_t s)
{
   return new char [s];
}

inline void mf (byte * t, size_t s)
{
   delete[] t;
}

template <typename T>
inline
T *
tma ()
{
   return new T; 
}

template <typename T>
void
tmf (T *t)
{
   delete t;
}

#endif //AEON__LIBS_MEM_MAF_H
