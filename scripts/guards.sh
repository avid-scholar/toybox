#!/usr/bin/bash
find -name '*.h' | xargs -n 1 |
while read f
do
   ff=$(tr -- '-a-z./' '_A-Z__' <<< "$(pwd | sed 's!^.*/!!')$f")
   echo ff=$ff
   perl -i -pe 'BEGIN{undef $/;} s!^[ \n]*#ifndef +[A-Z_]+ *\n#define +[A-Z_]+ +1 *\n(.*)#endif *[^\n]*[ \n]*$|^(.*)$!#ifndef '$ff'\n#define '$ff' 1\n$1$2#endif //'$ff'\n!smg' "$f"
done
