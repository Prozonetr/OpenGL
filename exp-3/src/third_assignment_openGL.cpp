#include "lib/Angel.h"
#include "lib/InitShader.cpp"
#include <iostream>
#include <GL/glui.h>

///usr/lib/x86_64-linux-gnu

using namespace std;

#define WIDTH 500
#define HEIGHT 500
const float PI = 3.14159265;

GLuint program1;
GLuint program2;

GLuint vPosition1;
GLuint vPosition2;

GLuint vao;

GLuint buffer;

GLuint theta;
GLuint scale;
GLuint xy;
GLUI_EditText  *edittext;
int mainWindow;

GLfloat Theta[4] = { 0.0, 0.0, 0.0,-1.0 };
GLfloat fx = 0.0;
GLfloat fy = 0.0;
GLfloat coordinates[2] = {fx , fy};
GLfloat scaling = 0.5;
GLfloat angle = 0.0;

bool check_half=0;
bool *half=&check_half;
bool check_rot=0;
bool *rot=&check_rot;
bool check_trarot=0;
bool *trarot=&check_trarot;

//# of vertices.
int gen = 400;
vec2 circles[13][400];
float speed1 = 1;
float speed2 = 2;
// Square's coordinates.
float square[] = {
  -0.5f,0.5f,
  -0.5f,-0.5f,
   0.5f,-0.5f,
   0.5f,0.5f,
  };
//__________________________________________________________________________________________________________________
  //Adjusting transition for states 2 and 3.
bool scbool = 0;
bool angbool = 0;
    void idle( void )
  {
    glutSetWindow(mainWindow);
    if(*rot){
      if(!coordinates[0] && !coordinates[1]){
        coordinates[0] = -coordinates[0] ;
        coordinates[1] = - coordinates[1];
      }
      Theta[2] -= speed1;
      if (Theta[2] < -360.0) {
  		Theta[2] += 360.0;
  	}
    }
    if(*trarot){
      scaling = 0.3;
      coordinates[0]=(angle * cos(angle))/13;
      coordinates[1]=-(angle * sin(angle))/13;
      if(angle < 0.05 && angbool){
        angbool = 0;
      }
      if(angle < 2 * PI && !angbool)
        angle += 0.04;
      else{
        angle -= 0.04;
        angbool = 1;
        coordinates[1] = -coordinates[1];
      }
      std::cout << angle << endl;
      Theta[2] += speed2;
      if (Theta[2] > 360.0) {
  		Theta[2] -= 360.0;
  	}
    }
    else if(*half){
      Theta[2] = 0.0;
      if(!coordinates[0] && !coordinates[1]){
        coordinates[0] = -coordinates[0] ;
        coordinates[1] = - coordinates[1];
      }
      if(scaling < 0.51 && scbool){
        scbool = 0;
      }
      if(scaling < 1.5 && !scbool)
        scaling += 0.02;
      else{
        scaling -= 0.02;
        scbool = 1;
      }
    }
    //edittext->set_float_val(speed);
    glutPostRedisplay();
  }

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
}

void control(int state)
{
	switch (state) {
    case 1:
      *half = 0;
      *rot = 1;
      *trarot = 0;
      break;
    case 2:
      *rot = 0;
      break;
	  case 3: if(speed1 < 10) speed1 += 1;  break;
	  case 4: if(speed1 > -10) speed1 -= 1;  break;
    case 5:
      *trarot = 1;
      *rot = 0;
      *half = 0;
      break;
    case 6:
      *trarot = 0;
      break;
    case 7: if(speed2 < 10) speed2 += 1;  break;
  	case 8: if(speed2 > -10) speed2 -= 1;  break;
    case 9:
      *half = 1;
      *rot = 0;
      *trarot = 0;
      break;
    case 10:
      *half = 0;
      break;
	}
}
//__________________________________________________________________________________________________________________
void display(void){
  glClear(GL_COLOR_BUFFER_BIT);

  // Passing uniform variables.
  glUniform2fv( xy,1,coordinates);

  glUniform3fv( theta, 1, Theta );

  glUniform1f( scale,scaling);

  //Choose right program.
  glUseProgram(program1);
  glBindVertexArray(vao);
  for(int i=0;i<4;i++){
    glDrawArrays(GL_TRIANGLE_FAN, i*gen, gen);
  }

  //Choose right program.
  glUseProgram(program2);
  glDrawArrays(GL_TRIANGLE_FAN, 4*gen, 4);

  //Display square.
  if(*rot){
    glUniform2fv( xy,1,coordinates);
    coordinates[0] = 0.0;
    coordinates[1] = 0.0;
  }
  else{
    glUniform2fv( xy,1,coordinates);
  }

  glUniform3fv( theta, 1, Theta );

  glUniform1f( scale,scaling);
  if(*half){
      coordinates[0] = 0.0;
      coordinates[1] = 0.0;
  }
  glUseProgram(program1);
  for(int i=4;i<12;i++){
    glDrawArrays(GL_TRIANGLE_FAN, (i*gen)+4, gen);
  }

   //swapping buffers
  glutSwapBuffers();
  glFlush();
}
//__________________________________________________________________________________________________________________
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
  // Setting up vao and buffering objects.
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

  //Shader initialization
  program1 = InitShader("shaders/vshader1.glsl", "shaders/fshader1.glsl");
  vPosition1 = glGetAttribLocation(program1, "vPosition1");
  glEnableVertexAttribArray(vPosition1);
  glVertexAttribPointer(vPosition1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  //Shader initialization
  program2 = InitShader("shaders/vshader1.glsl", "shaders/fshader2.glsl");
  vPosition2 = glGetAttribLocation(program2, "vPosition1");
  glEnableVertexAttribArray(vPosition2);

  //Setting up uniform varibles.
  xy = glGetUniformLocation( program1, "xy" );
  scale = glGetUniformLocation( program1, "scale" );
  theta = glGetUniformLocation( program1, "theta" );


  glClearColor(0, 0.65, 0, 0);
}
GLUI * glui;
//GLUI environment
void setupGLUI ()
{
	//  Set idle function
	GLUI_Master.set_glutIdleFunc (idle);

	//  Create GLUI window
	glui = GLUI_Master.create_glui ("Options", 0, 200, 200);
  GLUI_Panel* Animation1Panel = glui->add_panel("Animation 1", GLUI_PANEL_EMBOSSED);
	GLUI_Button* start1 = glui->add_button_to_panel(Animation1Panel, "Start", 1, (GLUI_Update_CB)control);
	glui->add_column_to_panel(Animation1Panel, true);
	GLUI_Button* stop1 = glui->add_button_to_panel(Animation1Panel, "Stop", 2, (GLUI_Update_CB)control);
	glui->add_column_to_panel(Animation1Panel, true);
//  new GLUI_Button( glui_window, "my button", 2, (GLUI_Update_CB)control ); different approach
  GLUI_Panel* speedPanel = glui->add_panel("Speed of Animation 1", GLUI_PANEL_EMBOSSED);
  GLUI_Button* speedUp = glui->add_button_to_panel(speedPanel, "Speed Up", 3, (GLUI_Update_CB)control);
  glui->add_column_to_panel(speedPanel, true);
  GLUI_Button* slowDown = glui->add_button_to_panel(speedPanel, "Slow Down", 4, (GLUI_Update_CB)control);
  glui->add_column_to_panel(speedPanel, true);
//
  GLUI_Panel* Animation2Panel = glui->add_panel("Animation 2", GLUI_PANEL_EMBOSSED);
  GLUI_Button* start2 = glui->add_button_to_panel(Animation2Panel, "Start", 9, (GLUI_Update_CB)control);
  glui->add_column_to_panel(Animation2Panel, true);
  GLUI_Button* stop2 = glui->add_button_to_panel(Animation2Panel, "Stop", 10, (GLUI_Update_CB)control);
  glui->add_column_to_panel(Animation2Panel, true);
//
  GLUI_Panel* Animation3Panel = glui->add_panel("Animation 3", GLUI_PANEL_EMBOSSED);
  GLUI_Button* start3 = glui->add_button_to_panel(Animation3Panel, "Start", 5, (GLUI_Update_CB)control);
	glui->add_column_to_panel(Animation3Panel, true);
	GLUI_Button* stop3 = glui->add_button_to_panel(Animation3Panel, "Stop", 6, (GLUI_Update_CB)control);
	glui->add_column_to_panel(Animation3Panel, true);
//
  GLUI_Panel* speedPanel2 = glui->add_panel("Speed of Animation 3", GLUI_PANEL_EMBOSSED);
  GLUI_Button* speedUp2 = glui->add_button_to_panel(speedPanel2, "Speed Up", 7, (GLUI_Update_CB)control);
  glui->add_column_to_panel(speedPanel2, true);
  GLUI_Button* slowDown2 = glui->add_button_to_panel(speedPanel2, "Slow Down", 8, (GLUI_Update_CB)control);
  glui->add_column_to_panel(speedPanel2, true);

}


//__________________________________________________________________________________________________________________
int main(int argc, char **argv)
  {
    cout << glGetString(GL_SHADING_LANGUAGE_VERSION);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(650, 300);

    //for compatibility issue
    glutInitContextVersion(3, 1);
  	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  	glutInitContextProfile(GLUT_CORE_PROFILE);
    mainWindow = glutCreateWindow("Thanos");

    glewExperimental = GL_TRUE;
    glewInit();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glui compatibility issue.
    glutInitContextVersion(2, 0);
    setupGLUI();


    glutMainLoop();

    return 0;
  }
