# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(listing) begin
(listing) create file1
(listing) create file2
(listing) create file3
(listing) create subdir
(listing) change to subdir
(listing) create file4 in subdir
(listing) create file5 in subdir
(listing) return to root
(listing) open file1
(listing) open file2
(listing) open file3
(listing) open file4
(listing) open file5
(listing) end
listing: exit(0)
EOF
pass;