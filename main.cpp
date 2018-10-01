#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#define CONTINUE 1
#define QUIT 0


struct bricks
{
	float x,y,w,h;
	bool alive;
} b[45];

float red1,red2,green1,green2,blue1,blue2;

struct ball
{
	float ballx,bally,ballwh,velx,vely;
	float red;
	float green;
	float blue;
	bool left,right,up,down;
} ball;

struct block
{
	float myx;
	float myy;
	float width;
	float height;
	bool lft;
	bool rgt;
	float red;
	float green;
	float blue;
}block;

float red=0.0;
float green=0.0;
float blue=0.0;

void specialUp(int,int,int);	//To check for key press
void specialDown(int,int,int);  //To check for key release
void reshape(void);		//To Modify the co-ordinates of the game objects according to the events
void draw(void);		//To Render the Game objects on the screen
void revert(void);


void initialize()	//To set the initial co-ordinates of the objects on the screen
{
	for(int n=0,x=4,y=390;n<45;n++,x+=66)
	{
	   if(x>560)
	   {
	     x=4;
	     y-=25;

	   }
	   b[n].x=x;
	   b[n].y=y;
	   b[n].w=60;
	   b[n].h=20;
	   b[n].alive=true;
	}

	block.myx=300;
	block.myy=0;
	block.width=80;
	block.height=20;
	block.lft=false;
	block.rgt=false;

	ball.ballx=300;
	ball.bally=200;
	ball.ballwh=30;
	ball.velx=0.35;
	ball.vely=0.35;

	red1=0.96;
 	green1=0.8;
 	blue1=0.69;
 	red2=0.6;
 	green2=0.8;
	blue2=0.196078;

	ball.red=0.65;
	ball.green=0.49;
	ball.blue=0.24;

	block.red=0.137255;
	block.green=0.556863;
	block.blue=0.419608;

}
bool check_collision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) //Function for checking collision
{
  if ( Ay+Ah < By ) return false; //if A is more to the lft than B
  else if ( Ay > By+Bh ) return false; //if A is more to rgt than B
  else if ( Ax+Aw < Bx ) return false; //if A is higher than B
  else if ( Ax > Bx+Bw ) return false; //if A is lower than B

  return true; //There is a collision because none of above returned false
}

void reshape()		//Modify the co-ordinates according to the key-presses and collisions etc...
{
	if(block.myx<0)
	  block.myx=0;
	if(block.myx+block.width>600)
	  block.myx=520;
	if(block.lft==true)

	  block.myx=block.myx-0.2; //block speed x
	if(block.rgt==true)
	  block.myx=block.myx+0.2; // block speed y



	ball.ballx+=0.3*ball.velx; // block speed x
	ball.bally+=0.3*ball.vely; //block speed y

	for(int n=0;n<45;n++)
	{
	   if(b[n].alive==true)
	   {
	   	if(check_collision(ball.ballx,ball.bally,ball.ballwh,ball.ballwh,b[n].x,b[n].y,b[n].w,b[n].h)==true)
	   	{
	   	  ball.vely=-ball.vely;
	   	  b[n].alive=false;
	   	  ball.down=true;
	   	  ball.up=false;
	   	  break;
	   	}
	   }
	}
	if(ball.ballx<0)
	{
		ball.velx=-ball.velx;
		ball.right=true;
		ball.left=false;
	}
	if(ball.ballx+ball.ballwh>600)
	{
		ball.right=false;
		ball.left=true;
		ball.velx=-ball.velx;
	}
	if(ball.bally+ball.ballwh>400)
		ball.vely=-ball.vely;
	else if(ball.bally<0)
		exit(0);

	if(check_collision(ball.ballx,ball.bally,ball.ballwh,ball.ballwh,block.myx,block.myy,block.width,block.height)==true)
	{
			ball.vely=-ball.vely;
			ball.up=true;
			ball.down=false;
	}
	draw();
}
void specialUp(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_LEFT): block.lft=false;break;
		case (GLUT_KEY_RIGHT): block.rgt=false;break;
	}
}
void specialDown(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_LEFT): block.lft=true;break;
		case (GLUT_KEY_RIGHT): block.rgt=true;break;
	}
}
void keyboard(unsigned char key,int x,int y)
{
	if(key==27) 		//27 corresponds to the esc key
	{
		ball.velx=0;
		ball.vely=0;	//To stop the ball from moving
	}
}
void myinit()
{
	glViewport(0,0,600,400);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,600,0,400);
}
void draw()		//Render the objects on the screen using the latest updated co-ordinates
{



	for(int i=0;i<45;i++)
	{
		if(b[i].alive==true)
		{
		   if(i%2==0) glColor3f(red1,green1,blue1);
		   else glColor3f(red2,green2,blue2);
		   glBegin(GL_POLYGON);
			   glVertex2f(b[i].x,b[i].y);
			   glVertex2f(b[i].x+b[i].w,b[i].y);
			   glVertex2f(b[i].x+b[i].w,b[i].y+b[i].h);
			   glVertex2f(b[i].x,b[i].y+b[i].h);
		   glEnd();
		}
	}



	glColor3f(block.red,block.green,block.blue);
	glBegin(GL_POLYGON);
		glVertex2f(block.myx,block.myy);
		glVertex2f(block.myx+block.width,block.myy);
		glVertex2f(block.myx+block.width,block.myy+block.height);
		glVertex2f(block.myx,block.myy+block.height);
	glEnd();

	glColor3f(ball.red,ball.green,ball.blue);
	glBegin(GL_POLYGON);
		glVertex2f(ball.ballx,ball.bally);
		glVertex2f(ball.ballx+ball.ballwh,ball.bally);
		glVertex2f(ball.ballx+ball.ballwh,ball.bally+ball.ballwh);
		glVertex2f(ball.ballx,ball.bally+ball.ballwh);
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red,green,blue,1);
	glDisable(GL_DEPTH_TEST);
	draw();
	glFlush();
	reshape();
}

void revert()
{
	ball.velx=0.35;
	ball.vely=0.35;
	if(ball.up==true)
	{
		if(ball.right==true)
		{
			ball.velx=ball.velx;
			ball.vely=ball.vely;
		}
		else if(ball.left==true)
		{
			ball.velx=-ball.velx;
			ball.vely=ball.vely;
		}
	}
	else if(ball.down=true)
	{
		if(ball.right=true)
		{
			ball.velx=ball.velx;
			ball.vely=-ball.vely;
		}
		else if(ball.left==true)
		{
			ball.velx=-ball.velx;
			ball.vely=-ball.vely;
		}
	}
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Block Breaker");
	initialize();
	myinit();
	draw();

	glutDisplayFunc(display);
        glutSpecialFunc(specialDown);
    	glutSpecialUpFunc(specialUp);
    	glutKeyboardFunc(keyboard);
	glutIdleFunc(reshape);
	glutMainLoop();
	return 0;
}

