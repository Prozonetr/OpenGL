#include "Angel.h"
#include "InitShader.cpp"
#include <iostream>

using namespace std;

#define WIDTH 500
#define HEIGHT 500
const float PI = 3.14159265;

GLuint program1;                //contains shader
GLuint program2;                //contains shader
GLuint vPosition1;
GLuint vPosition2;
GLuint vao;
GLuint buffer;
GLuint theta;
GLuint scale;
GLuint fcolor;
GLfloat Theta[4] = { 0.0, 0.0, 0.0,-1.0 };
bool check_half=0;
bool *half=&check_half;
bool check_rot=0;
bool *rot=&check_rot;
bool check_color=0;
bool *color=&check_color;
float colorVal=0.0;
float *fcolorVal=&colorVal;

int gen = 400;                  //# of vertices
vec2 circles[13][400];
float square[] = {              // square's coordinates
  -0.5f,0.5f,
  -0.5f,-0.5f,
   0.5f,-0.5f,
   0.5f,0.5f,
  };

    void idle( void ) //function used for adjusting transition for states 2 and 3
  {
    if(Theta[3]==-1.0){
      Theta[2] -= 0.01;
    }

    else{
      Theta[2] += 0.01;
    }
    if ( Theta[2] <= -45.0 )
    {
      Theta[3] =1.0;
    }
    if ( Theta[2] >= 45.0 )
    {
      Theta[3] =-1.0;
    }
    if(*color==1.0 && Theta[2] < 0){
      *fcolorVal = -Theta[2]/70.0;
    }
    else if(*color==1.0 && Theta[2] > 0){
      *fcolorVal = Theta[2]/70.0;
    }
    glutPostRedisplay();
  }

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
}

void keyboard(unsigned char key, int x, int y) //adjusting state
{
	switch (key) {
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
  case '1':
    *half = 1;
    *rot = 0;
    *color = 0;
    break;
  case '2':
    *half = 0;
    *rot = 1;
    *color = 0;
    break;
  case '3':
    *half = 0;
    *rot = 1;
    *color = 1;
    break;
	}
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  if(*rot==1.0) //checking state 2 and passing uniform vector
    glUniform3fv( theta, 1, Theta );
  else{
    Theta[2]=0.0;
    glUniform3fv( theta, 1, Theta );
  }
  if(*color==1.0) //checking state 3 and passing uniform vector
    glUniform1f( fcolor,*fcolorVal);
  else
    glUniform1f( fcolor,0.0);

  if(*half==1.0) //checking state 1 and passing uniform variable
    glUniform1f( scale,0.5);
  else
    glUniform1f( scale,0.8);

  glUseProgram(program1); //choosing right program
  glBindVertexArray(vao);
  for(int i=0;i<4;i++){
    glDrawArrays(GL_TRIANGLE_FAN, i*gen, gen);
  }
  glUseProgram(program2); //choosing right program
  glDrawArrays(GL_TRIANGLE_FAN, 4*gen, 4); //for displaying square
  if(*rot==1.0)
    glUniform3fv( theta, 1, Theta );
  else{
    Theta[2]=0.0;
    glUniform3fv( theta, 1, Theta );
  }
  if(*half==1.0)
    glUniform1f( scale,0.5);
  else
    glUniform1f( scale,0.8);
  glUseProgram(program1); //choosing right program
  for(int i=4;i<12;i++){
    glDrawArrays(GL_TRIANGLE_FAN, (i*gen)+4, gen);
  }

  glutSwapBuffers(); //swapping buffers
  glFlush();
}

void init(){
  /*
    Every circle has been drawn one by one.
  */

  //1
  for (int i = 0; i < gen; i++) {
		circles[0][i].x =  -0.5 +0.5*( (cos(i * 2 *  PI / gen)));
		circles[0][i].y =   0.5 +0.5*( (sin(i * 2 * PI / gen)));
	}
  //2
  for (int i = 0; i < gen; i++) {
		circles[1][i].x =   0.5 +0.5*( (cos(i * 2 *  PI / gen)));
		circles[1][i].y =   0.5 +0.5*( (sin(i * 2 * PI / gen)));
	}
  //3
  for (int i = 0; i < gen; i++) {
		circles[2][i].x =   -0.5 +0.5*( (cos(i * 2 *  PI / gen)));
		circles[2][i].y =   -0.5 +0.5*( (sin(i * 2 * PI / gen)));
	}
  //4
  for (int i = 0; i < gen; i++) {
		circles[3][i].x =   0.5 +0.5*( (cos(i * 2 *  PI / gen)));
		circles[3][i].y =   -0.5 +0.5*( (sin(i * 2 * PI / gen)));
	}
  //big ones

    //little ones
    //5
    for (int i = 0; i < gen; i++) {
  		circles[4][i].x =  -0.5 +0.1*( (cos(i * 2 *  PI / gen)));
  		circles[4][i].y =   0.5 +0.1*( (sin(i * 2 * PI / gen)));
  	}
    //6
    for (int i = 0; i < gen; i++) {
  		circles[5][i].x =   0.5 +0.1*( (cos(i * 2 *  PI / gen)));
  		circles[5][i].y =   0.5 +0.1*( (sin(i * 2 * PI / gen)));
  	}
    //7
    for (int i = 0; i < gen; i++) {
  		circles[6][i].x =   -0.5 +0.1*( (cos(i * 2 *  PI / gen)));
  		circles[6][i].y =   -0.5 +0.1*( (sin(i * 2 * PI / gen)));
  	}
    //8
    for (int i = 0; i < gen; i++) {
  		circles[7][i].x =   0.5 +0.1*( (cos(i * 2 *  PI / gen)));
  		circles[7][i].y =   -0.5 +0.1*( (sin(i * 2 * PI / gen)));
  	}
    //9
    for (int i = 0; i < gen; i++) {
  		circles[8][i].x =  -0.6 +0.1*( (cos(i * 2 *  PI / gen)));
  		circles[8][i].y =   0.1*( (sin(i * 2 * PI / gen)));
  	}
    //10
    for (int i = 0; i < gen; i++) {
  		circles[9][i].x =   0.1*( (cos(i * 2 *  PI / gen)));
  		circles[9][i].y =   0.6 +0.1*( (sin(i * 2 * PI / gen)));
  	}
    //11
    for (int i = 0; i < gen; i++) {
  		circles[10][i].x =    0.1*( (cos(i * 2 *  PI / gen)));
  		circles[10][i].y =   -0.6 +0.1*( (sin(i * 2 * PI / gen)));
  	}
    //12
    for (int i = 0; i < gen; i++) {
  		circles[11][i].x =   0.6 +0.1*( (cos(i * 2 *  PI / gen)));
  		circles[11][i].y =   0.1*( (sin(i * 2 * PI / gen)));
  	}

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(circles[0])*12+sizeof(square), 0, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(circles[0]), circles[0]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0]), sizeof(circles[1]), circles[1]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*2, sizeof(circles[2]), circles[2]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*3, sizeof(circles[3]), circles[3]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*4, sizeof(square), square);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*4+sizeof(square), sizeof(circles[4]), circles[4]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*5+sizeof(square), sizeof(circles[5]), circles[5]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*6+sizeof(square), sizeof(circles[6]), circles[6]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*7+sizeof(square), sizeof(circles[7]), circles[7]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*8+sizeof(square), sizeof(circles[8]), circles[8]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*9+sizeof(square), sizeof(circles[9]), circles[9]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*10+sizeof(square), sizeof(circles[10]), circles[10]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(circles[0])*11+sizeof(square), sizeof(circles[11]), circles[11]);


  program1 = InitShader("vshader1.glsl", "fshader1.glsl"); //shader initialization
  vPosition1 = glGetAttribLocation(program1, "vPosition1");
  glEnableVertexAttribArray(vPosition1);
  glVertexAttribPointer(vPosition1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  program2 = InitShader("vshader1.glsl", "fshader2.glsl"); //shader initialization
  vPosition2 = glGetAttribLocation(program2, "vPosition1");
  glEnableVertexAttribArray(vPosition2);

  scale = glGetUniformLocation( program1, "scale" ); //setting up uniform varible
  theta = glGetUniformLocation( program1, "theta" ); //setting up uniform varible
  fcolor = glGetUniformLocation( program1, "color_inc" ); //setting up uniform varible

  glClearColor(0, 0.65, 0, 0);
}

int main(int argc, char **argv)
  {
    cout << glGetString(GL_SHADING_LANGUAGE_VERSION);
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(650, 300);
    glutInitContextVersion(3, 1); //for compatibility issue
  	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  	glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Thanos");

    glewInit();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); //custom keyboard function
    glutReshapeFunc(reshape);
    glutIdleFunc(idle); //custom idle function
    init();
    glutMainLoop();

    return 0;
  }
