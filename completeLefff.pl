$num_args = $#ARGV + 1;
if ($num_args != 2) {
    print "\nUsage: ./completeLefff.pl dictionary complement\n";
    exit;
}

$file1=$ARGV[0];
$file2=$ARGV[1];

open($fd1,'<',$file1) or die("open: $!");
open($fd2,'<',$file2) or die("open: $!");

@t2 = <$fd2>;

while( defined( $line1 = <$fd1> ) ) {
  if ($. % 17 == 0){
    print STDERR " line $. \r";
  }
  chomp $line1;
  if ( $line1 =~ /([^\t]+\t)(([^\t]+\t)([^\t]+\t))(.*)/ ) {
    $form = $1;
    $pos1 = $3;
    $lexeme1 = $4;
    $pattern1 = $2;
    $fs1 = $5;
    $ok = 0;
    if ( $form !~ "#" ) {
      foreach $line2 (@t2) {
	chomp $line2;
	if ( $line2 =~ /([^\t]+\t[^\t]+\t)([^\t]*\t)(.*)/ ) {
	  $pattern2 = $1;
	  $lexeme2 = $2;
	  $fs2 = $3;
	  if ( $pattern1 eq $pattern2 ) {
	    $ok = 1;
	    print "$form$pos1$lexeme2$fs1,$fs2\n";
	  }
	}
      }
      if (not $ok) {
	print "$form$pos1$lexeme1$fs1\n";
      }
    }
  }
}
