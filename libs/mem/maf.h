#ifndef AEON__LIBS_MEM_MAF_H
#define AEON__LIBS_MEM_MAF_H 1

inline byte * alloc_bytes (size_t s)
{
   return new char [s];
}

inline void free_bytes (byte * t, size_t s)
{
   delete[] t;
}

template <typename T>
inline
T *
alloc_obj ()
{
   return new T; 
}

template <typename T>
void
free_obj (T *t)
{
   delete t;
}

#endif //AEON__LIBS_MEM_MAF_H
