#ifndef AEON__EXE_LU_DATA_H
#define AEON__EXE_LU_DATA_H 1

#include <string>

typedef std::string bytes;
typedef std::string data;

inline
bytes
bytes_construct () { return bytes (); }

#define bytes_cstr(b) (b).c_str ()

inline
data
data_construct () { return data (); }

#define data_free(d) (d).clear ()

#define data_reset(d) ({data_free(*(d)); *(d) = data_construct ();})

#define data_check_null(d) (d).empty ()

#endif //AEON__EXE_LU_DATA_H
