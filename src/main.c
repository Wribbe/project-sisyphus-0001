#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>

int
main(void)
{
  Display * display = XOpenDisplay(NULL);
  int num_screens = XScreenCount(display);
  for (int i=0; i<num_screens; i++) {
    int width = XDisplayWidth(display, i);
    printf("Screen[%d] -- width: %d\n", i, width);
  }
}
