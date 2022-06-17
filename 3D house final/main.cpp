#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
	double x,y,z;
}Point;

bool drawAxes = true;
float tyreAngle = 0;

float quadAngle = 0;
float boxAngle = 0;
float boxAngle2 = 0;
float boxScaleFactor = 1;
float tyreScaleFactor = 1;
float windowAngle = 0;
float tinyBoxAngle = 0;
float dMove=0;  //**unit for sliding door displacement
float wMove=0;  //**unit for sliding window displacement
float dAngle=140;  //**unit for Rotating door angle
float dRotateController=0; //Unit to  control rotating door initialization and termination
float fanAngle = 0;  //Rotates the fan
float spinDirection =  0;  //Changes orientation or rotation
float backgroundcolorr = 0;
float backgroundcolorg = 0;
float backgroundcolorb = 0;
float RoomLightR = 0;
float RoomLightG = 0;
float RoomLightB = 0;
float DoorR = 0.522;
float DoorG = 0.3373;
float DoorB = 0.2274;


Point pos, u, r, l;

void displayAxes()
{
	if(drawAxes)
	{
		glBegin(GL_LINES);
		{
		    glColor3f(1.0, 0, 0);

			glVertex3f( 500,0,0); // a point on pos x axis
			glVertex3f(-500,0,0); // a point on neg x axis

			glColor3f(0, 1.0, 0);

			glVertex3f(0,-500,0); // a point on pos y axis
			glVertex3f(0, 500,0); // a point on neg y axis

			glColor3f(0, 0, 1.0);

			glVertex3f(0,0, 500);  // a point on pos z axis
			glVertex3f(0,0,-500);   // a point on neg z axis
		}
		glEnd();
	}
}



Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

/**Function to move the camera**/
Point CamPos(Point vect, Point perp,int dir)
{
    double s = dir*2.0;
    Point point;
    point.x = vect.x + s*perp.x;
    point.y = vect.y + s*perp.y;
    point.z = vect.z + s*perp.z;

    return point;
}
void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1': {
            Point l1 = func(l, r, -1);
            r = func(r, l, 1);
            l = l1;
            break;
		}
		case '2': {
            Point l1 = func(l, r, 1);
            r = func(r, l, -1);
            l = l1;
            break;
		}

		case '3': {
            Point u1 = func(u, l, -1);
            l = func(l, u, 1);
            u = u1;
            break;
        }
        case '4': {
            Point u1 = func(u, l, 1);
            l = func(l, u, -1);
            u = u1;
            break;
        }
        case '5': {
            Point r1 = func(r, u, -1);
            u = func(u, r, 1);
            r = r1;
            break;
        }
        case '6':{
            Point r1 = func(r, u, 1);
            u = func(u, r, -1);
            r = r1;
            break;
        }
        case '7':{
            tyreScaleFactor += 0.2;
            break;
        }
        case '8':{
            tyreScaleFactor -= 0.2;
            break;
        }
        case '9':{  /***rotates window open **/
            if(windowAngle<90)
            {
                windowAngle += 5;

            }
            //windowAngle += 5;
            printf("Window Angle %f\n", windowAngle);
            break;
        }
        case '0':{  /***rotates window close **/


            if(windowAngle>0)
            {
                windowAngle -= 5;
            }
            printf("Window Angle %f\n", windowAngle);
            break;
        }
        /**button**/
        case 'l':{
            boxAngle += 5;
		        printf("Box Angle %f\n", boxAngle);

            break;
        }
        case 'r':{
            boxAngle -= 5;
		        printf("Box Angle %f\n", boxAngle);

            break;
        }
        case 'u':{
            if(boxScaleFactor<2)
            {
                boxScaleFactor += 0.02;
            break;
            }
        }
        case 'd':{
            if(boxScaleFactor>0)
            {
                boxScaleFactor -= 0.02;
            break;
            }
        }

        /**/
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN: // down arrow
		    {
		        point pos1=CamPos(pos,l,-1);
		        pos=pos1;
		        /*quadAngle += 5;
		        printf("Quad Angle %f\n", quadAngle);*/
		        break;
		    }

		case GLUT_KEY_UP:   // up arrow
		    {
		        /*quadAngle -= 5;
		        printf("Quad Angle %f\n", quadAngle);*/
		        point pos1=CamPos(pos,l,1);
		        pos=pos1;
		        break;

		    }

		case GLUT_KEY_RIGHT:    // right arrow
		    {
		        /*boxAngle += 5;
		        printf("Box Angle %f\n", boxAngle);*/

		        point pos1=CamPos(pos,r,1);
		        pos=pos1;

		        break;
		    }

		case GLUT_KEY_LEFT:     // left arrow
		    {
		        /*boxAngle -= 5;
		        printf("Box Angle %f\n", boxAngle);*/

		        point pos1=CamPos(pos,r,-1);
		        pos=pos1;

		        break;
		    }

		case GLUT_KEY_PAGE_UP:
		    {
                //boxScaleFactor += 0.02;
                point pos1=CamPos(pos,u,1);
		        pos=pos1;

                break;
		    }

		case GLUT_KEY_PAGE_DOWN:
		    {
		        //boxScaleFactor -= 0.02;
		        point pos1=CamPos(pos,u,-1);
		        pos=pos1;

                break;
		    }

		case GLUT_KEY_HOME:
		    {
		        if(dMove<40)
                {
                   dMove+=5;
                }

		        //tyreAngle += 5;
		        break;
		    }

        case GLUT_KEY_END:
            {
                if(dMove>0)
                {
                   dMove-=5;
                }
                //tyreAngle -= 5;
                break;
            }

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
            {
                printf("Mouse Left Button Clicked\n");
			}
			else if(state == GLUT_UP)
            {
                printf("Mouse Left Button Released\n");
            }
            break;
		default:
			break;
	}
}

void displayTyre(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 12;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    /*glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
        glVertex3f(halfTyreWidth, -tyreRadius, 0);
    }
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, 0, tyreRadius);
        glVertex3f(halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, tyreRadius);
    }
    glEnd();*/


    glColor3f(1, 1, 0);
    for(int i=0; i<tyreSlices; i++)
    {
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            if(i%2==0){
                glColor3f(1, 1, 1);
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }

            else{
                glColor3f(0, 0, 0);
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }

            /*glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);*/
        }
        glEnd();
        glPopMatrix();

    }
}
/**modifying Tyre function for inner ring with blades**/

void displayTyre2(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 12;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    /*glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
        glVertex3f(halfTyreWidth, -tyreRadius, 0);
    }
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, 0, tyreRadius);
        glVertex3f(halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, tyreRadius);
    }
    glEnd();*/


    glColor3f(.5, 0, 1);
    for(int i=0; i<tyreSlices; i++)
    {
        /**inner wheel**//*glPushMatrix();
        glPopMatrix();
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();*/
        /*glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();*/
        /*glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
        glVertex3f(halfTyreWidth, -tyreRadius, 0);
    }
    glEnd();*/

    glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            if(i%2==0){
                glColor3f(1, 1, 1);
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }

            else{
                glColor3f(0, 0, 0);
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }

            /*glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);*/
        }
        glEnd();

    /**Fan baldes**/
    glTranslatef(0, tyreRadius/2, 0);
    glBegin(GL_QUADS);
    {
        if(i%2==0)
        {
            glColor3f(0, 0.5, 1);
        glVertex3f(halfTyreWidth, tyreRadius/2, 0);
        glVertex3f(-halfTyreWidth, tyreRadius/2, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius/2, 0);
        glVertex3f(halfTyreWidth, -tyreRadius/2, 0);

        }
        else{
                glColor3f(0, 1, 0.5);
        glVertex3f(halfTyreWidth, tyreRadius/2, 0);
        glVertex3f(-halfTyreWidth, tyreRadius/2, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius/2, 0);
        glVertex3f(halfTyreWidth, -tyreRadius/2, 0);

        }

    }
    glEnd();

        glPopMatrix();

    }

}

void displayQuad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/

        glColor3f(0, 0.5, 1);


        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

        /** Gradient Fill Quad **/


        /*glColor3f(1, 1, 0);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(0, 1, 1);

        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);*/

    }
    glEnd();
}

void displayQuadRoom(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/

        /*glColor3f(0, 0, 0);


        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);*/

        /** Gradient Fill Quad **/


        glColor3f(RoomLightR, RoomLightG, RoomLightB);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        //glColor3f(RoomLightR, RoomLightG, RoomLightB);

        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

    }
    glEnd();
}
///window light
void displayQuadRoomWindow(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/

        /*glColor3f(0, 0, 0);


        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);*/

        /** Gradient Fill Quad **/


        glColor3f(RoomLightR, RoomLightG, RoomLightB);

        glVertex3f( 0, -quadLength, 0);
        glVertex3f( 0, quadLength, 0);
        glVertex3f( 0, quadLength,-halfQuadWidth);
        glVertex3f( 0, -quadLength, -halfQuadWidth);


    }
    glEnd();
}
    /** Function to display doorpartleft**/
    void displayDoorLeft(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/


        /** Gradient Fill Quad **/


        glColor3f(DoorR, DoorG, DoorB);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(DoorR+0.4, DoorB+0.4, DoorG+0.4);

        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

    }
    glEnd();
}

    /** Function to display doorPartright**/
    void displayDoorRight(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/


        /** Gradient Fill Quad **/

        glColor3f(DoorR+0.4, DoorB+0.4, DoorG+0.4);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(DoorR, DoorG, DoorB);

        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

    }
    glEnd();
}


    /** Function to display  Rotating doorpartleft **/
    void displayRDoorLeft(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/


        /** Gradient Fill Quad **/



        glColor3f(DoorR+0.4, DoorB+0.4, DoorG+0.4);

        glVertex3f(-quadWidth, 0, -halfQuadLength);
        glVertex3f(-quadWidth, 0, halfQuadLength);

        glColor3f(DoorR, DoorG, DoorB);

        glVertex3f( 0, 0, halfQuadLength);
        glVertex3f( 0, 0, -halfQuadLength);


    }
    glEnd();
}


/** Function to display  Rotating doorpartRight **/
    void displayRDoorRight(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {

        /** Gradient Fill Quad **/


        glColor3f(DoorR+0.4, DoorB+0.4, DoorG+0.4);

        glVertex3f(quadWidth, 0, -halfQuadLength);
        glVertex3f(quadWidth, 0, halfQuadLength);

        glColor3f(DoorR, DoorG, DoorB);

        glVertex3f( 0, 0, halfQuadLength);
        glVertex3f( 0, 0, -halfQuadLength);



    }
    glEnd();
}

    /**Function to display window that will rotate along y axis**/

    void displayWindow(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/

        glColor3f(0, 0.5, 1);


        glVertex3f( 0, -quadLength, 0);
        glVertex3f( 0, quadLength, 0);
        glVertex3f( 0, quadLength, halfQuadWidth);
        glVertex3f( 0, -quadLength, halfQuadWidth);

        /** Gradient Fill Quad **/


        /*glColor3f(1, 1, 0);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(0, 1, 1);

        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);*/

    }
    glEnd();
}


void displayBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.435, 0.588, 0.553);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.419, 0.329, 0.3058);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.62, 0.57, 0.56);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

/** Function for Base**/

void displayBase(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.706, 0.706, 0.706);///LIGHT GRAY

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.48, 0.48, 0.48);///DARK GRAY

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(.831, .831, .831);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


/**Function for House Main Body**/


void displayBody(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.5607, 0.1882, 0.14117);//LIGHT BRICK color

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.431, 0.1451, 0.1059);//DARK BRICK color

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.66, 0.165, 0.0981);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
/**Function for House Roof**/


void displayRoof(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.361, 0.4, 0.2667);//LIGHT Olive color

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.298, 0.3294, 0.2196);//DARK olive color

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

/**Function for Stairs**/

void displayStair(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.788, 0.788, 0.569);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.839, 0.839, 0.604);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.945, 0.945, 0.647);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayScene()
{
    //Primitive Object dimensions

    float quadLength = 100, quadWidth = 60;
    float largeBoxLength = 200, largeBoxWidth = 100, largeBoxHeight = 50;
    float smallBoxLength = 150, smallBoxWidth = 70, smallBoxHeight = 30;
    float tinyBoxLength = 10, tinyBoxWidth = 10, tinyBoxHeight = 10;
    float tyreRadius = 100, tyreWidth = 40;

    /**House elements size**/
    float baseLenght = 400, baseWidth = 400, baseHeight = 30;
    float bodyLength = 380, bodyWidth = 380, bodyHeight = 150;
    float roofLenght = 420, roofWidth = 420, roofHeight = 20;
    float stair1Lenght = 160, stair1Width = 60, stair1Height = 10;
    float stair2Lenght = 160, stair2Width = 40, stair2Height = 10;
    float stair3Lenght = 160, stair3Width = 20, stair3Height = 10;
    float chimneyLenght =200 , chimneyWidth = 80, chimneyHeight=160;

    float windowLenght = 80, windowWidth = 150;
    float doorWidth=45, doorHeight=110;


    /** Principal Axes **/

    displayAxes();

    /**/

    /** Quad **/

    //glRotatef(quadAngle, 1, 0, 0); // rotates with respect to x axis
    //glRotatef(quadAngle, 0, 1, 0); // rotates with respect to y axis
    //glRotatef(quadAngle, 0, 0, 1); // rotates with respect to z axis
    //displayQuad(quadLength, quadWidth);

    /**/

    /** Single Box **/

    //glTranslatef(150, 0, 0); // rotation applied first, translation applied second
    //glRotatef(boxAngle, 1, 0, 0); // rotates with respect to x axis
    //glRotatef(boxAngle, 0, 1, 0); // rotates with respect to y axis
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    //glTranslatef(150, 0, 0);    // translation applied first, rotation applied second
    //displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight);

    /**/

    /** Double Box Stack **/

    //glRotatef(boxAngle, 0, 0, 1); // rotation applied to both boxes
    //glTranslatef(-300, 100, 100); // translation applied to both boxes
    //displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    //glRotatef(boxAngle, 0, 0, 1);   // rotation applied only on the small box
    //glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    //displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box

    /**/

    /** Double Box Stack - Push Pop Matrix **/


    /*glRotatef(boxAngle, 0, 0, 1); // rotation applied to both boxes

    //glPushMatrix(); // saves the matrix just before scaling, to prevent scale effect to anything other than the large box
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor); // without push-pop, scale will be applied to both boxes
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    //glPopMatrix();

    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    */


    /**/

    /** Tyre **/

    /*glRotatef(tyreAngle, 1, 0, 0); // roates the tyre w.r.t x axis
    glRotatef(tyreAngle, 0, 1, 0); // roates the tyre w.r.t y axis
    glRotatef(tyreAngle, 0, 0, 1); // roates the tyre w.r.t z axis
    displayTyre(tyreRadius, tyreWidth);
    */
    /**/

    /** Tyre Double Box Stack **/

    /*glPushMatrix();
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();
    //*********Kawser Rashid , Kazi Mahadi, Zakir Hossain, Farzahan Akhi, Shoheb Tanin*********

    glPushMatrix();
    glTranslatef(0, 0, tyreRadius+smallBoxHeight+(largeBoxHeight/2)); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(tyreRadius, tyreWidth);
    glPopMatrix();
    */

    /**House main structure**/
    glRotatef(boxAngle,0,0,1);
    //glRotatef(boxAngle2,0,0,1);
    glRotatef(quadAngle, 1, 0, 0);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glPushMatrix();

    glTranslatef(0,0,((bodyHeight/2)+(baseHeight/2)));
    displayBody(bodyLength,bodyWidth,bodyHeight);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,((bodyHeight)+(baseHeight/2)+(roofHeight/2)));
    displayRoof(roofLenght,roofWidth,roofHeight);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,baseWidth/2,-((baseHeight/2)-(stair1Height/2)));
    displayStair(stair1Lenght,stair1Width,stair1Height);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,baseWidth/2,-((baseHeight/2)-(stair2Height/2)-stair1Height));
    displayStair(stair2Lenght,stair2Width,stair2Height);


    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,baseWidth/2,-((baseHeight/2)-(stair3Height/2)-stair1Height-stair2Height));
    displayStair(stair3Lenght,stair3Width,stair3Height);


    /*glPopMatrix();//Working window without y axis rotation
    glPushMatrix();
    glTranslatef(1+(bodyLength/2),0,((baseHeight/2)+(bodyHeight/2)));
    glRotatef(90,0,0,1);
    displayQuad(windowLenght, windowWidth);*/

    /**working window with y rotation FINAL**/

    glPopMatrix();
    glPushMatrix();
    glTranslatef(2+(bodyLength/2),0,((baseHeight)*1.5+(bodyHeight/2))-windowLenght);
    //displayBox(20,windowWidth*1.2,5);
    glRotatef(windowAngle,0,1,0);
    displayWindow(windowLenght, windowWidth);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(2+(bodyLength/2),0,((baseHeight)*1.5+(bodyHeight/2)));
    displayBox(20,windowWidth*1.2,5);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(1+(bodyLength/2),0,((baseHeight)*1.5+(bodyHeight/2)));
    displayQuadRoomWindow(windowLenght,windowWidth);

    /**Functioning Sliding window Final**/
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(2+(bodyLength/2)),0,((baseHeight)*1.5+(bodyHeight/2)));
    displayBox(20,windowWidth*1.2,5);
    //glRotatef(windowAngle,0,1,0);
    glTranslatef(0,0,wMove);///sliding functional variable
    displayWindow(windowLenght, windowWidth);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(1+(bodyLength/2)),0,((baseHeight)*1.5+(bodyHeight/2)));
    displayQuadRoomWindow(windowLenght,windowWidth);


    /**Functioning sliding door FINAL**/
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,1+(bodyWidth/2),(baseHeight/2) + (doorHeight));
    displayBox(doorWidth*2.2,20,5);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,1+(bodyWidth/2),(baseHeight/2) + (doorHeight/2));
    displayQuadRoom(doorHeight,doorWidth*2);

    glPopMatrix();
    glPushMatrix();
    glTranslatef((doorWidth/2)+dMove,2+(bodyWidth/2),(baseHeight/2) + (doorHeight/2));
    displayDoorLeft(doorHeight,doorWidth);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-((doorWidth/2)+dMove),2+(bodyWidth/2),(baseHeight/2) + (doorHeight/2));
    displayDoorRight(doorHeight,doorWidth);

    /**Functioning Rotating Door FINAL**/


    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-(1+(bodyWidth/2)),(baseHeight/2) + (doorHeight));
    displayBox(doorWidth*2.2,20,5);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(doorWidth,-(2+(bodyWidth/2)),(baseHeight/2) + (doorHeight/2));
    glRotatef(dAngle,0,0,1);
    displayRDoorLeft(doorHeight,doorWidth);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-doorWidth,-(2+(bodyWidth/2)),(baseHeight/2) + (doorHeight/2));
    glRotatef(-dAngle,0,0,1);
    displayRDoorRight(doorHeight,doorWidth);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-(1+(bodyWidth/2)),(baseHeight/2) + (doorHeight/2));
    displayQuadRoom(doorHeight,doorWidth*2);

    /**Function for Fan Box**/

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,bodyHeight+baseHeight/2+(roofHeight)+chimneyHeight/2);
    displayBox(chimneyLenght,chimneyWidth,chimneyHeight);

    /**functioning Fan Rotating along y axis **/

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0,1+(chimneyWidth/2)+tyreWidth/2,bodyHeight+baseHeight/2+(roofHeight)+chimneyHeight/2);
    glRotatef(fanAngle,0,1,0);
    glRotatef(90,0,0,1);
    displayTyre2(tyreRadius/4,tyreWidth);
    displayTyre(tyreRadius/2,tyreWidth);



    glPopMatrix();

    displayBase(baseLenght,baseWidth,baseHeight);


    /** Animate Function **/
   /* glPushMatrix();
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, tyreRadius+smallBoxHeight+(largeBoxHeight/2)); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();*/

    /*glPushMatrix();
    glRotatef(tinyBoxAngle, 0, 0, 1); // angle is updated in animate function
    glTranslatef(250, 40, 50);
    displayBox(tinyBoxLength, tinyBoxWidth, tinyBoxHeight);
    glPopMatrix();*/

}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backgroundcolorr, backgroundcolorg, backgroundcolorb,0);	//sets background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();


	glutSwapBuffers();
}

/***** WORKING HERE*****/

void animate(){
    tinyBoxAngle += 0.05;

	if(dRotateController==1&&dAngle<140)
    {
        dAngle += 0.05;
    }
    if(dRotateController==0 && dAngle>0)
    {
        dAngle -= 0.05;
    }
    if( spinDirection ==1)
    {
        fanAngle -= 0.05;
    }
    if( spinDirection ==2)
    {
        fanAngle += 0.05;
    }
    if( spinDirection ==0)
    {
        fanAngle = 0;
    }

	glutPostRedisplay();
}

void init(){
    glClearColor(backgroundcolorr, backgroundcolorg, backgroundcolorb,0); 	//sets background color

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

	// to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    pos = {400, 400, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu(int id)
{
    if(id == 3)
    {
        backgroundcolorr = 0.459;
        backgroundcolorg = 0.9373;
        backgroundcolorb = 1;
    }
    else if(id == 4)
    {
        backgroundcolorr = 0;
        backgroundcolorg = 0;
        backgroundcolorb = 0;
    }
    else if(id == 5)
    {
        wMove = 40;
    }
    else if(id == 6)
    {
        wMove = 0;
    }
    else if(id == 7)
    {
        dRotateController= 1;
    }
    else if(id == 8)
    {
        dRotateController= 0;
    }
    else if(id == 9)
    {
        spinDirection= 1;
    }
    else if(id == 10)
    {
        spinDirection= 2;
    }
    else if(id == 11)
    {
        spinDirection= 0;
    }
    else if(id == 12)
    {
        RoomLightR= (0.8431);
        RoomLightG= (1);
        RoomLightB= (0.01569) ;
    }
    else if(id == 13)
    {
        RoomLightR= 0;
        RoomLightG= 0;
        RoomLightB=0;
    }
}

void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	glutCreateWindow("Kawser Mahadi Zakir AKhi Shoheb 3D house");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	int subMenuNo = glutCreateMenu(subMenu);
    glutAddMenuEntry("Day", 3);
	glutAddMenuEntry("Night", 4);

	int subMenuNo1 = glutCreateMenu(subMenu);
    glutAddMenuEntry("SWindow Open", 5);
	glutAddMenuEntry("SWindow Close", 6);

	int subMenuNo2 = glutCreateMenu(subMenu);
    glutAddMenuEntry("RDoor open", 7);
	glutAddMenuEntry("Rdoor Close", 8);

	int subMenuNo3 = glutCreateMenu(subMenu);
    glutAddMenuEntry("Fan Clockwise", 9);
	glutAddMenuEntry("Fan AntiClockwise", 10);
	glutAddMenuEntry("Fan Off", 11);

	int subMenuNo4 = glutCreateMenu(subMenu);
    glutAddMenuEntry("Lights ON", 12);
	glutAddMenuEntry("Lights OFF", 13);



    glutCreateMenu(mainMenu);
	glutAddMenuEntry("Axes On", 1);
	glutAddMenuEntry("Axes Off", 2);
	glutAddSubMenu("Background", subMenuNo);
	glutAddSubMenu("Sliding Window", subMenuNo1);
	glutAddSubMenu("Rotating Door", subMenuNo2);
	glutAddSubMenu("Exhaust Fan", subMenuNo3);
	glutAddSubMenu("Lights", subMenuNo4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();		//The main loop of OpenGL, this function never returns

	return 0;
}
