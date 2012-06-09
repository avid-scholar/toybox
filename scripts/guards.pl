find -name '*.h' | xargs -n 1 perl -e 'local$/;$f=$ARGV[0];open $h "<" "$f";$t=read_file($f);print"file: $f\n";'
