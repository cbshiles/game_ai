void set_callbacks();
void call_game(int x, int y);

class Screen : public Follower {
  int xdim,ydim;

  // Initialization routine.
void GL_init(void) 
{
    // Set background (or clearing) color.
    glClearColor(1.0, 1.0, .0, 0.0); 
    glClear(GL_COLOR_BUFFER_BIT);
    glClearDepth(1.0);
    glDepthFunc(GL_LEQUAL);
    glewInit(); //Don't forget this guy
}

  //fns for giving pieces a border (not touching edges of square)
  float min(int z){return -.9 + z*2.0/3;}
  float max(int z){return -.433 + z*2.0/3;} 
  
public:
  Screen(int x, int y):xdim(x),ydim(y){
    // Initialize GLUT.
    char fakeParam[] = "GameDriver.cpp";
    char *fakeargv[] = { fakeParam, NULL };
    int fakeargc = 1;
    glutInit(&fakeargc, fakeargv);
 
    // Set display mode as single-buffered and RGB color.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
   
    // Set OpenGL window size.
    glutInitWindowSize(xdim,ydim);

    // Set position of OpenGL window upper-left corner.
    glutInitWindowPosition(100, 100); 
   
    // Create OpenGL window with title.
    glutCreateWindow("Tic-Tac-Toe");
   
    // Initialize.
    GL_init(); 

    set_callbacks();
    
    glLineWidth(3);
    black->setBackground();
    white->set();
        printf("DANE\n");
  }

  void mouseInput(int button, int state, int x, int y){
    if (!button && state==1){
      call_game(x*3/xdim, y = y*3/ydim);
    }
  }
  
  void resize(int x, int y){
    printf("resize\n");
    //# doesnt reallly resize..
    xdim = x, ydim = y;
  }


  void drawShape(int x, int y){

    int shape = board[x][y];
    y = 2-y; //# because poistive y is down in GL

    int minx=min(x),miny=min(y),maxx=max(x),maxy=max(y);
      
    if (shape == 1){//draw x
      glBegin(GL_LINES);
      glVertex3f(minx,miny,0);
      glVertex3f(maxx,maxy,0);

      glVertex3f(minx,maxy,0);
      glVertex3f(maxx,miny,0);
    
      glEnd();
    } else if (shape == 2) { //draw o
      glBegin(GL_LINE_STRIP);
      glVertex3f(minx,miny,0);
      glVertex3f(minx,maxy,0);
      glVertex3f(maxx,maxy,0);
      glVertex3f(maxx,miny,0);
      glVertex3f(minx,miny,0);
      glEnd();
    }
  }


  void drawScene(){
    printf("DA\n");
   glMatrixMode(GL_MODELVIEW);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

    printf("DB\n");
   
    float ix = 1.0/3, iy = 1.0/3;
    glBegin(GL_LINES);
    white->set();

    int i; loop(i,2){
      glVertex3f(ix, -1, 0);
      glVertex3f(ix, 1, 0);
      ix *= -1;

      glVertex3f(-1, iy, 0);
      glVertex3f(1, iy, 0);
      iy *= -1;
    }
    glEnd();

        printf("DC\n");
    
    int j;
    loop(i,3){loop(j,3){
	if (board[j][i]) {drawShape(j,i);}
      }}
  glFlush();
  //not sure when/why needed
  }

};
