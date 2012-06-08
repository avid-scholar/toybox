print "digraph map { rankdir = BT ;\n";
my %e;
my %v;
my $w;

sub add_edge
{
   my ($beg, $end) = (@_);
   $e{$beg} = {} unless exists $e{$beg};
   $e{$beg}->{$end} = 1;
   #print "add_edge $beg , $end\n";
}

while (<STDIN>)
{
   chomp;
   next unless m/^( *)([^ ][-_0-9A-Za-z\/ ]+[-_0-9a-zA-Z])( +[^-_a-zA-Z ].*)?$/;
   my $is_root = $1 eq "";
   my $node = $2;
   my $ext = $3;
   if ($is_root)
   {
      $w = $node;
   }
   elsif ($node =~ m!^/!)
   {
      $node = $w . $node;
   }

   my $done;
   #print "ext=$ext\n";
   my @ext;
   while ($ext =~ s/^ *([^ ][a-zA-Z_ ]*)(.*)$/$2/)
   {
      my $x = $1;
      $x =~ s/^ *(.*?) *$/$1/;
      $done = 1 if $x eq "+";
      push @ext, $x;
   }

   if ($is_root)
   {
      die "vertice $node mentioned twice as root vertice" if exists $v{$node};
      $v{$node} = 1 if $done;
      print "\"$w\" [ style = filled, fillcolor = palegreen ] ;\n" if $done;
   }
   else
   {
      add_edge ($node, $w);
   }

   for my $x (@ext)
   {
      next if $x eq "+";
      if ($x =~ m/^:(.*)$/)
      {
         add_edge ($1, $node);
      }
      elsif ($x =~ m!^/$!)
      {
         add_edge ($node . $x, $node);
      }
   }
}

for my $k (keys (%e))
{
   my $ref = $e{$k}; 
   for my $k2 (keys (%$ref))
   {
      print (" \"$k\" -> \"$k2\" ", exists $v{$k} ? " [ color = green ] " : "", "; \n");
   }
}

print "}\n";
