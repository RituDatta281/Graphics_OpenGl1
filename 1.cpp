#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//#include <windows.h>
#include <GL/glut.h>

#define pi (2*acos(0.0))
#define MAX_LENGTH 20
double cameraHeight;
double cameraAngle;
int drawgrid;
double var;
int drawaxes;
double angle;

struct point
{
	double x,y,z;
}pos,u,l,r;

void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a,a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a,a,0);
	}glEnd();
}




void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*pi/2);
			points[i][j].y=r*sin(((double)j/(double)slices)*pi/2);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
       // glColor3f(1,1,1);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                //glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				//glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				//glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				//glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

void drawCylinder(double radius, int segments)
{
    int i;
    struct point points[100];
    glColor3f(0,1,0);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*pi/2);
        points[i].y=radius*sin(((double)i/(double)segments)*pi/2);
        points[i].z=MAX_LENGTH-radius;
    }
    //draw segments using generated points
    /*for(i=0;i<segments;i++)       //making 1/4th circle
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,points[i].z);
            glVertex3f(points[i+1].x,points[i+1].y,points[i+1].z);
            glVertex3f(points[i].x,points[i].y,-points[i].z);
            glVertex3f(points[i+1].x,points[i+1].y,-points[i+1].z);
        }
        glEnd();
    }*/

    for(i=0;i<segments;i++)
    {

        glBegin(GL_QUADS);
        {
			glVertex3f(points[i].x,points[i].y,points[i].z);
            glVertex3f(points[i+1].x,points[i+1].y,points[i+1].z);
            glVertex3f(points[i+1].x,points[i+1].y,-points[i+1].z);
            glVertex3f(points[i].x,points[i].y,-points[i].z);

        }
        glEnd();
    }
}



void drawCubeSphere(double length)
{

    glPushMatrix(); //upper
    {
    glColor3f(1,1,1);
    glTranslatef(0,0,MAX_LENGTH);
    drawSquare(length);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glColor3f(1,1,1); // lower
    glTranslatef(0,0,-MAX_LENGTH);
    drawSquare(length);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glColor3f(1,1,1);
    glTranslatef(MAX_LENGTH,0,0);
    glRotatef(90,0,1,0);
    drawSquare(length);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glColor3f(1,1,1);
    glTranslatef(-MAX_LENGTH,0,0);
    glRotatef(90,0,1,0);
    drawSquare(length);
    }
    glPopMatrix();

        glPushMatrix();
    {
     glColor3f(1,1,1);
    glTranslatef(0,MAX_LENGTH,0);
    glRotatef(90,1,0,0);
    drawSquare(length);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glColor3f(1,1,1);
    glTranslatef(0,-MAX_LENGTH,0);
    glRotatef(90,1,0,0);
    drawSquare(length);
    }
    glPopMatrix();

    ///-----------------CUBE DONE----------------

    glPushMatrix();
    {
    glTranslatef(var,var,var);
    glColor3f(1,0,0);
    drawSphere(MAX_LENGTH-var,24,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glTranslatef(var,-var,var);
    glRotatef(90,1,0,0);
    glColor3f(1,0,0);
    drawSphere(MAX_LENGTH-var,24,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glTranslatef(var,-var,-var);
    glRotatef(90,0,1,0);
    glRotatef(90,1,0,0);
    glColor3f(1,0,0);
    drawSphere(MAX_LENGTH-var,24,20);
    }
    glPopMatrix();


    glPushMatrix();
    {
    glTranslatef(var,var,-var);
    glRotatef(90,0,1,0);
    glColor3f(1,0,0);
    drawSphere(MAX_LENGTH-var,24,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glTranslatef(-var,var,var);
    glRotatef(90,0,0,1);
    glColor3f(1,0,0);
    drawSphere(MAX_LENGTH-var,24,20);
    }
    glPopMatrix();


    glPushMatrix();
    {
    glTranslatef(-var,var,-var);
    glRotatef(-90,0,1,0);
    glRotatef(90,0,0,1);
    glColor3f(1,0,0);
    drawSphere(MAX_LENGTH-var,24,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glTranslatef(-var,-var,var);
    glRotatef(180,0,0,1);
    glColor3f(1,0,0);
    drawSphere(MAX_LENGTH-var,24,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glTranslatef(-var,-var,-var);
    glRotatef(-90,0,1,0);
    glRotatef(180,0,0,1);
    glColor3f(1,0,0);
    drawSphere(MAX_LENGTH-var,24,20);
    }
    glPopMatrix();
    ///----------------------- SPHERE DONE------------------

    glPushMatrix();
    {
    glTranslatef(var,var,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glTranslatef(-var,-var,0);
    glRotatef(180,0,0,1);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();

    glPushMatrix();  //front left up
    {
    glTranslatef(var,0,var);
    glRotatef(90,1,0,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();
     glPushMatrix();
    {
    glTranslatef(0,var,var);   //front right up
    glRotatef(-90,0,1,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();

    glPushMatrix();     //front left down
    {
    glTranslatef(var,0,-var);
    glRotatef(-90,1,0,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();
     glPushMatrix();
    {
    glTranslatef(0,var,-var);   //front right down
    glRotatef(90,0,1,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();

    glPushMatrix();  //back right up
    {
    glTranslatef(-var,0,var);
    glRotatef(180,0,0,1);
    glRotatef(90,1,0,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();
     glPushMatrix();
    {
    glTranslatef(0,-var,var);   //back left up
    glRotatef(180,0,0,1);
    glRotatef(-90,0,1,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();

    glPushMatrix();     //back right down
    {
    glTranslatef(-var,0,-var);
    glRotatef(180,0,0,1);
    glRotatef(-90,1,0,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();

     glPushMatrix();
    {
    glTranslatef(0,-var,-var);   //back left down
    glRotatef(180,0,0,1);
    glRotatef(90,0,1,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glTranslatef(var,-var,0); //left corner
    glRotatef(180,1,0,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();

    glPushMatrix();
    {
    glTranslatef(-var,var,0); //right corner
    glRotatef(180,0,1,0);
    drawCylinder(MAX_LENGTH-var,24);
    }
    glPopMatrix();
    ///-------------------Cylinder done--------------

}


void keyboardListener(unsigned char key, int x,int y){
    struct point temp;
	switch(key){
        		case '1': //rotate/ look left  (r,l will be changed)
            r.x = r.x*cos(angle) + l.x* sin(angle);
            r.y = r.y*cos(angle) + l.y* sin(angle);
            r.z = r.z*cos(angle) + l.z* sin(angle);
            l.x = u.y * r.z - r.y * u.z;
            l.y = r.x * u.z - u.x * r.z;
            l.z = u.x * r.y - r.x * u.y;
			break;

		case '2': //rotate/ look right  (r,l will be changed)
		    r.x = r.x*cos(-angle) + l.x* sin(-angle);
		    r.y = r.y*cos(-angle) + l.y* sin(-angle);
            r.z = r.z*cos(-angle) + l.z* sin(-angle);
            l.x = u.y * r.z - r.y * u.z;
            l.y = r.x * u.z - u.x * r.z;
            l.z = u.x * r.y - r.x * u.y;
			break;

		case '3': //look up (u,l)
            l.x = l.x*cos(angle) + u.x* sin(angle);
            l.y = l.y*cos(angle) + u.y* sin(angle);
            l.z = l.z*cos(angle) + u.z* sin(angle);
            u.x = r.y * l.z - l.y * r.z;
            u.y = l.x * r.z - r.x * l.z;
            u.z = r.x * l.y - l.x * r.y;
			break;
        case '4':
            l.x = l.x*cos(-angle) + u.x* sin(-angle);
            l.y = l.y*cos(-angle) + u.y* sin(-angle);
            l.z = l.z*cos(-angle) + u.z* sin(-angle);
            u.x = r.y * l.z - l.y * r.z;
            u.y = l.x * r.z - r.x * l.z;
            u.z = r.x * l.y - l.x * r.y;
			break;
		case '5':
            u.x = u.x*cos(-angle) + r.x* sin(-angle);
            u.y = u.y*cos(-angle) + r.y* sin(-angle);
            u.z = u.z*cos(-angle) + r.z* sin(-angle);
            r.x = l.y * u.z - u.y * l.z;
		    r.y = u.x * l.z - l.x * u.z;
            r.z = l.x * u.y - u.x * l.y;
			break;
		case '6':
		    u.x = u.x*cos(angle) + r.x* sin(angle);
            u.y = u.y*cos(angle) + r.y* sin(angle);
            u.z = u.z*cos(angle) + r.z* sin(angle);
            r.x = l.y * u.z - u.y * l.z;
		    r.y = u.x * l.z - l.x * u.z;
            r.z = l.x * u.y - u.x * l.y;
			break;


		case '9':
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_UP:
			pos.x -= 3.0;
			pos.y -= 3.0;
			break;
		case GLUT_KEY_DOWN:
			pos.x += 3.0;
			pos.y += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			pos.x -= 3.0;
			break;
		case GLUT_KEY_LEFT:
			pos.x += 3.0;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.z += 2.0;
			break;
		case GLUT_KEY_PAGE_DOWN:
		    pos.z -= 2.0;
			break;
        case GLUT_KEY_HOME:
            if(var>0)  var-= 1;
            break;
        case GLUT_KEY_END:
            if(var<MAX_LENGTH)  var += 1;
            break;
		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;
		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

    gluLookAt(pos.x, pos.y, pos.z, pos.x + l.x, pos.y + l.y, pos.z + l.z, u.x, u.y, u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

   
    drawCubeSphere(var);






	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	var=10.0;
	drawgrid=0;
	drawaxes=1;
	pos.x=100;
	pos.y=100;
	pos.z=2;
	u.x=0.0;
	u.y=0.0;
	u.z=1.0;
	l.x=-(1/sqrt(2));
	l.y=-(1/sqrt(2));
	l.z=0.0;
	r.x=-(1.0/sqrt(2));
	r.y=(1.0/sqrt(2));
	r.z=0.0;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0.03;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL2 Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}


