#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  CHECK (create ("file1", 0), "create file1");
  CHECK (create ("file2", 0), "create file2");
  CHECK (create ("file3", 0), "create file3");
  
  // Create a subdirectory and some files in it
  CHECK (mkdir ("subdir"), "create subdir");
  CHECK (chdir ("subdir"), "change to subdir");
  CHECK (create ("file4", 0), "create file4 in subdir");
  CHECK (create ("file5", 0), "create file5 in subdir");
  
  // Return to root directory
  CHECK (chdir (".."), "return to root");
  
  // Verify files exist by trying to open them
  CHECK (open ("file1") > 1, "open file1");
  CHECK (open ("file2") > 1, "open file2");
  CHECK (open ("file3") > 1, "open file3");
  CHECK (open ("subdir/file4") > 1, "open file4");
  CHECK (open ("subdir/file5") > 1, "open file5");
}