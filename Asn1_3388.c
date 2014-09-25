/* Name: Hasan Almawi
 * Assignment: 1
 * Date: September 13th, 2014
 * Course: CS3388A - Computer Graphics I
 * Western University
 * Professor Steven S. Beauchemin 
 */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SX   512
#define SY   512

#define POSX 10
#define POSY 10

int quad;

Display *InitX(Display *d, Window *w, int *s) {
  d = XOpenDisplay(NULL) ;
  if(d == NULL) {
    printf("Cannot open display\n") ;
    exit(1) ;
  }
  *s = DefaultScreen(d) ;
  *w = XCreateSimpleWindow(d, RootWindow(d, *s), POSX, POSY, SX, SY, 1, BlackPixel(d, *s), WhitePixel(d, *s)) ;
  Atom delWindow = XInternAtom(d, "WM_DELETE_WINDOW", 0) ;
  XSetWMProtocols(d, *w, &delWindow, 1) ;
  XSelectInput(d, *w, ExposureMask | KeyPressMask) ;
  XMapWindow(d, *w) ;
  return(d) ;
}

void QuitX(Display *d, Window w) {
  XDestroyWindow(d,w) ;
  XCloseDisplay(d) ;
}

void SetPixelX(Display *d, Window w, int s, int i, int j) {
  XDrawPoint(d, w, DefaultGC(d, s), i, j) ;
}

void SetCurrentColorX(Display *d, GC *gc, unsigned int r, unsigned int g, unsigned int b) {
  XSetForeground(d, *gc, r << 16 | g << 8 | b) ;
}
/*  DrawLineX
 *  Author: Hasan Almawi
 *  Date of Creation: 13th September, 2014
 *  Purpose: Draws a line using Bresenham's Line Algorithm with the specified parameters
 *  Input Parameters: 
 *      - *d: Display reference
 *      -  w: Window that will be drawn on
 *      -  s: The color of the lines drawn
 *      -  sX: The starting point of the x axis
 *      -  sY: The starting point of the y axis
 *      -  eX: The end point of the x axis
 *      -  eY: The end point of the y axis
 *  Output Parameters: A line with color s drawn from starting point (sX, sY) to (eX, eY) on the window w
*/
void DrawLineX(Display *d, Window w, int s, int sX, int sY, int eX, int eY){
  //Initializing the difference in X and Y, the incrementation of X and Y, the Delta, calculated increase (c1 and c2)
  int dX, dY, inc_X, inc_Y, Delta, c1, c2;
  //Getting the difference between the start and end point of x
  dX = abs(eX - sX); 
  //Getting the difference between the start and end point of y
  dY = abs(eY - sY); 
  //Checking to see if the slope is decreasing in the x axis (left to right, or right to left)
  if(sX < eX) inc_X = 1;
    else inc_X = -1;
  //Checking to see if the slope is decreasing in the y axis (top to bottom, or bottom to top)
  if(sY < eY) inc_Y = 1;
    else inc_Y = -1;
  //In case the slope is not steep
  if(dX > dY){
    //We will be moving along the x axis and the y axis will be calculated
    //Delta represents pi
    Delta = 2*dY - dX; 
    //In case yi+1 - yi = 1, c1 is
    c1 = 2*dY-2*dX;
    //In case yi+1 - yi =0, c2 is
    c2 = 2*dY;
    //Starting from the beginning point to the end point
    while(sX!=eX){
      //Incase Delta is greater than 0
    if(Delta > 0){
      //Increment the y axis for the point
      sY+=inc_Y;
      //Draw the pixel
      SetPixelX(d, w, s, sX, sY);
      //Increment Delta by c1
      Delta = Delta + c1;
    }
    //If Delta is less than zero
    else{
      //Draw the pixel
      SetPixelX(d, w, s, sX, sY);
      //Increment Delta by c2
      Delta = Delta + c2;
    }
    //Increment X
    sX+=inc_X;
    }
  }
  //If the slope is steep
  else{
    //We will be moving along the y axis and the x axis will be calculated
    //Delta represents pi
    Delta = 2*dX - dY;
    //In case xi+1 - xi = 1, c1 is 
    c1 = 2*dX-2*dY;
    //In case xi+1 - xi =0, c2 is
    c2 = 2*dX;
    //Starting from the beginning point to the end point
    while(sY!=eY){
    //Incase Delta is greater than 0
    if(Delta > 0){
      //Increment the x axis for the point
      sX+=inc_X;
      //Draw the pixel
      SetPixelX(d, w, s, sX, sY);
      //Increment Delta by c1
      Delta = Delta + c1;
    }
    //If Delta is less than zero
    else{
      //Draw the pixel
      SetPixelX(d, w, s, sX, sY);
      //Increment Delta by c2
      Delta = Delta + c2;
    }
    //Increment Y
    sY+=inc_Y;
  }
  }
}

/*  Main Method
 *  Author: Hasan Almawi
 *  Date of Creation: 13th September, 2014
 *  Purpose: Calls upon the other functions to draw the lines with the specified point of origin and point of termination
 *  Input Parameters: None
 *  Output Parameters: A 512x512 white window with lines drawn on it.
*/
int main() {
  Display *d;
  Window w;
  XEvent e;
  int s, i, j;
  unsigned int r, g, b;
  KeySym key;
  char text[255];
  d = InitX(d, &w, &s);
  while (1) {
    XNextEvent(d, &e);
    if (e.type == Expose) {
      SetCurrentColorX(d, &(DefaultGC(d, s)), 0, 0, 0);
      DrawLineX(d, w, s, 256, 256, 500, 300); //Eighth Octant
      DrawLineX(d, w, s, 256, 256, 300, 500); //Seventh Octant
      DrawLineX(d, w, s, 256, 256, 200, 500); //Sixth Octant
      DrawLineX(d, w, s, 256, 256, 50, 300); //Fifth Octant
      DrawLineX(d, w, s, 256, 256, 50, 200); //Fourth Octant
      DrawLineX(d, w, s, 256, 256, 200, 50); //Third Octant
      DrawLineX(d, w, s, 256, 256, 300, 50); //Second Octant
      DrawLineX(d, w, s, 256, 256, 500, 200); //First Octant
      DrawLineX(d, w, s, 511, 511, 256, 256); //First Quadrant
      DrawLineX(d, w, s, 256, 256, 0, 511); //Second Quadrant
      DrawLineX(d, w, s, 1, 1, 256, 256); //Third Quadrant
      DrawLineX(d, w, s, 256, 256, 511, 0); //Fourth Quadrant
      DrawLineX(d, w, s, 0, 256, 512, 256); //Horizontal Line
      DrawLineX(d, w, s, 256, 0, 256, 512); //Vertical Line
    }
    if(e.type == KeyPress && XLookupString(&e.xkey,text,255,&key,0)==1){ //If q key is pressed, then quit
      if(text[0]=='q') break;
    }
    if(e.type == ClientMessage) break;
  }
  QuitX(d,w);
}