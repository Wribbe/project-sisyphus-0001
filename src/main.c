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
  /* Try out som default methods. */
  printf(
     "XDefaultDepth: %d\n"
     "XDefaultScreen: %d\n"
     ,XDefaultDepth(display, 0)
     ,XDefaultScreen(display)
  );

  Window window = XCreateWindow(
    display
    ,XDefaultRootWindow(display)
    ,0
    ,0
    ,800
    ,600
    ,1
    ,XDefaultDepth(display, 0)
    ,InputOutput
    ,XDefaultVisual(display, 0)
    ,0
    ,0
  );


//GLXFBConfig *
//glXChooseFBConfig(
//  Display * display
//  ,int screen
//  ,const int * attrib_list,
//  ,int * nelements
//);


//XVisualInfo *
//glXGetVisualFromFBConfig(
//  Display * display
//  ,GLXFBConfig config
//);


//GLXContext
//glXCreateContext(
//  Display * display
//  ,XVisualInfo * visual
//  ,GLXContext share_list
//  ,Bool direct
//);


  XMapWindow(display, window);
  XSelectInput(display, window, ExposureMask | KeyPressMask);
  XEvent event = {0};

  for(;;) {
    XNextEvent(display, &event);
    switch(event.type) {
      case KeyPress:
        printf("Key press.\n");
        break;
      case KeyRelease:
        printf("%s\n", "Key released");
        break;
    }
  }
}
