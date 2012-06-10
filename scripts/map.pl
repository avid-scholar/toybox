print "digraph map { rankdir = BT ;\n";
my %e;
my %v;
my $w;

sub add_edge
{
   my ($beg, $end) = (@_);
   $e{$beg} = {} unless exists $e{$beg};
   $e{$beg}->{$end} = 1;
   $v{$beg} = 0 unless exists $v{$beg};
   #print "edge: $beg -> $end\n";
}

sub shname
{
   my $w = $_[0];
   $w =~ s!.*/([^/]*)$!...$1!;
   return $w;
}

while (<STDIN>)
{
   chomp;
   next unless m/^( *)([^ ]+)( +[^ ].*)?$/;
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
   my @ext;
   while ($ext =~ s/^ *([^ ]+)( .*)?$/$2/)
   {
      my $x = $1;
      $done = 1 if $x eq "+";
      push @ext, $x;
   }

   if ($is_root)
   {
      $v{$node} = $done;
   }
   else
   {
      $v{$node} = 0 unless exists $v{$node};
      add_edge ($node, $w);
   }

   for my $x (@ext)
   {
      next if $x eq "+";
      if ($x =~ m/^:(.*)$/)
      {
         add_edge ($1, $node);
      }
      elsif ($x =~ m!^/!)
      {
         add_edge ($node . $x, $node);
      }
   }
}

for my $k (keys %v)
{
   print '"', $k, "\" [ ", $v{$k} ? "style = filled, fillcolor = palegreen,": "", " label = \"", shname ($k), "\" ] ;\n";
}

for my $k (keys %e)
{
   my $ref = $e{$k}; 
   for my $k2 (keys (%$ref))
   {
      print (" \"", $k, "\" -> \"", $k2, "\" ", $v{$k} ? " [ color = green ] " : "", "; \n");
   }
}

print "}\n";
