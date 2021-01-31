#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>


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
  //  ,const int * attrib_list, /* NULL-terminated array w. (opt, val) pairs */
  //  ,int * nelements          /* Number of elements returned by function. */
  //);


  int num_configs = 0;
  GLXFBConfig * config = glXChooseFBConfig(display, 0, NULL, &num_configs);
  if (config == NULL) {
    printf("%s\n", "glXGetFBConfig returned NULL, aborting.");
    return (EXIT_FAILURE);
  }
  printf("Got %d, configs.\n", num_configs);


  //XVisualInfo *
  //glXGetVisualFromFBConfig(
  //  Display * display
  //  ,GLXFBConfig config
  //);

  XVisualInfo * visual = NULL;
  for (int i=0; i<num_configs; i++) {
    visual = glXGetVisualFromFBConfig(display, config[i]);
    if (visual != NULL) {
      printf("Found visual that matched configuration: %d\n", i);
      break;
    }
    if (i+1 == num_configs) {
      printf("%s\n", "No visual matching the config, aborting.");
      return EXIT_FAILURE;
    }
  }

  //GLXContext
  //glXCreateContext(
  //  Display * display
  //  ,XVisualInfo * visual
  //  ,GLXContext share_list
  //  ,Bool direct
  //);


  GLXContext context = glXCreateContext(display, visual, 0, 1);
  glXMakeCurrent(display, window, context);

  int glx_major= 0, glx_minor = 0;
  glXQueryVersion(display, &glx_major, &glx_minor);

  printf("Running on GLX %d.%d\n", glx_major, glx_minor);

  int gl_major = 0, gl_minor = 0;
  glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
  glGetIntegerv(GL_MINOR_VERSION, &gl_minor);

  printf("Running context with OpenGL version %d.%d\n", gl_major, gl_minor);

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
