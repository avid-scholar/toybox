#!/bin/bash

find -name '*.h' -o -name '*.hxx' |
while read f
do
   ff=$(tr -- '-a-z./' '_A-Z__' <<< "$(pwd | sed 's!^.*/!!')$f")
   m=$(md5sum $f)
   perl -i -pe 'BEGIN{undef $/;} s!^[ \n]*#ifndef +[A-Z_]+ *\n#define +[A-Z_]+ +1 *\n[ \n]*((\n *)?[^ \n].*[^ \n])[ \n]*#endif *[^\n]*[ \n]*$|^(.*[^ \n])[ \n]*$!#ifndef '$ff'\n#define '$ff' 1\n\n$1$3\n\n#endif //'$ff'\n!smg' "$f"
   m2=$(md5sum $f)
   [ "x$m" == "x$m2" ] || echo $f
done
