#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"
#include <math.h>
#include "SOIL.h"
 

# define FRONT_F 70 // F
# define FRONT_f 102 // f
# define BACK_B  66 // B
# define BACK_b  98 // b
# define UP_U  85 // U
# define UP_u  117 // u
# define DOWN_D  68 // D
# define DOWN_d  100 // d
# define RIGHT_C_R 82 // R
# define RIGHT_C_r 114 // r
# define LEFT_C_L  76 // L
# define LEFT_C_l  108 // l

 //the variable for our textures
static GLuint array_of_textures[14];
static float eyeX =0.80, eyeY =2.0,eyeZ=15.0,lookXAt=0.0,lookYAt=0.0,lookZAt=-15.0; 
static float  ang = 0.0,ang2 = 0.0,ang3 = 0.0,ratio;
float door_right=0, door_left=0; 
int daylight = 1;


void reshape (int w, int h)
{
   if(h == 0)
   {	h = 1;   }

   ratio = 1.0f * w / h;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glViewport (0, 0, w, h);
   gluPerspective(65, (GLfloat) w/(GLfloat) h, 1.0, 1000.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void moveMeFlat(int direction) {

	eyeX = eyeX + direction*(lookXAt)*0.05;
	eyeZ = eyeZ + direction*(lookZAt)*0.05;
}

void orientMe(float ang) {

	lookXAt = sin(ang);
	lookZAt = -cos(ang);
} 


void illumination (void)
{
   //Material
   GLfloat no_mat_emit[] = {0.0, 0.0, 0.0, 1.0};
   GLfloat mat_amb[] = {0.7, 0.73, 0.7, 1.0};
   GLfloat mat_diff[] = {0.8, 0.8, 0.5, 1.0}; 
   GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
   GLfloat mat_shininess[] = { 50.0 };   

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);  
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat_emit);
   if(daylight == 1){
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
   glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular ); 
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   
	//LIGHT 1
   GLfloat spec_light1[] = {0.8,0.8,0.8}; 
   GLfloat diff_light1[] = {0.8, 0.8, 0.4, 1.0};
   GLfloat light1_position[] = {eyeX, eyeY, eyeZ, 1.0};
   glLightfv(GL_LIGHT1, GL_SPECULAR, spec_light1);
   glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diff_light1);
   }
 
	//Model
	GLfloat lmodel_ambient[] = {0.9, 0.9, 0.9, 1.0}; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); 
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//Enable
	glEnable(GL_LIGHTING); 
	if(daylight == 1){
    glEnable(GL_LIGHT1);
	}

}

void illumination_roof (void)
{
   //Material
   GLfloat no_mat_emit[] = {0.0, 0.0, 0.0, 1.0};
   GLfloat mat_amb[] = {0.7, 0.0, 0.0, 1.0};
   GLfloat mat_diff[] = {0.7, 0.0, 0.0, 1.0};
   GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
   GLfloat mat_shininess[] = { 70.0 };   

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);  
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat_emit);  
   if(daylight == 1){
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,mat_specular );
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
   
	//LIGHT 1
   GLfloat spec_light1[] = {0.8,0.8,0.8};
   GLfloat diff_light1[] = {0.8, 0.8, 0.4, 1.0};
   GLfloat light1_position[] = {eyeX, eyeY, eyeZ, 1.0};
   glLightfv(GL_LIGHT1, GL_SPECULAR, spec_light1);
   glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diff_light1);
   }

	//Model
	GLfloat lmodel_ambient[] = {0.8, 0.8, 0.7, 1.0}; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//Enable
	glEnable(GL_LIGHTING);
	if(daylight == 1){
    glEnable(GL_LIGHT1);
	}

}

void moon (void)
{
   GLfloat mat_emit[] = {0.85, 0.85, 0.5, 1.0};
   GLfloat mat_shininess[] = {50.0};
   GLfloat mat_diff[] = {1.0, 0.89, 0.71, 1.0};

   glMaterialfv(GL_FRONT, GL_EMISSION, mat_emit);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);

   GLfloat lmodel_ambient[] = {0.8, 0.8, 0.1, 1.0}; 
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); 
  
   glEnable(GL_LIGHTING);
}

void illumination_door (void)
{
   //Material
   GLfloat no_mat_emit[] = {0.0, 0.0, 0.0, 1.0};
   GLfloat mat_amb[] = {0.3, 0.0, 0.0, 1.0};
   GLfloat mat_diff[] = {0.3, 0.0, 0.0, 1.0}; 
   GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
   GLfloat mat_shininess[] = { 50.0 };   
   

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb); 
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat_emit);
   if(daylight == 1){
	   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
       glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,mat_specular );
       glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
  
	//LIGHT 1
       GLfloat spec_light1[] = {0.8,0.8,0.8}; 
       GLfloat diff_light1[] = {0.8, 0.8, 0.4, 1.0};
       GLfloat light1_position[] = {eyeX, eyeY, eyeZ, 1.0};
       glLightfv(GL_LIGHT1, GL_SPECULAR, spec_light1);
       glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
       glLightfv(GL_LIGHT1, GL_DIFFUSE, diff_light1);
   }  

   //Model
	GLfloat lmodel_ambient[] = {0.8, 0.6, 0.6, 1.0}; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//Enable
	glEnable(GL_LIGHTING);
	if(daylight == 1){
		glEnable(GL_LIGHT1);
	}
}

void sun (void)
{
   GLfloat mat_emit[] = {0.7, 0.7, 0.09, 1.0};
   GLfloat mat_shininess[] = {50.0};
   GLfloat mat_diff[] = {0.7,0.7,0.09,1.0};

   glMaterialfv(GL_FRONT, GL_EMISSION, mat_emit);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);

   GLfloat lmodel_ambient[] = {0.8, 0.8, 0.0, 1.0}; 
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  
   glEnable(GL_LIGHTING);
}



void init(void) 
{
   glClearColor (0.55,0.89,0.93,0.0);
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_CULL_FACE);
   glShadeModel (GL_FLAT);
   glCullFace( GL_BACK );
   glEnable(GL_NORMALIZE);
   glEnable(GL_DEPTH_TEST);

}

void loadTextureFromFile(char *filename)
{    
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );

	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,theTexMap.GetNumCols(), theTexMap.GetNumRows(),
					 GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

}

void texture_load( char* filenames[] )
{
	glGenTextures( 14, array_of_textures );	
	for ( int i=0; i<14; i++ ) {
		glBindTexture(GL_TEXTURE_2D, array_of_textures[i]);	
		loadTextureFromFile( filenames[i] );			
	}
}

 char* texture_array[14] = { 
		"wood01.bmp",				// toixoi spitiou
		"LightningTexture.bmp",		// styl kanape
		"grass3_thum.bmp" ,			// aylh
		"Stonewall.bmp" ,			// monopati
		"WOOD_016.bmp",				// eksoporta
		"PinkFloyd.bmp" ,			// pinakas sto ypnodomatio
		"PinkFloyd2.bmp",			// pinakas aristera apo kanape
		"PinkFloyd3.bmp",			// pinakas deksia apo kanape
		"Dali.bmp",					// pinakas sto piano
		"Windows.bmp" ,				// para8yro
		"texture.bmp" ,				// patoma
		"wood01.bmp",				// esoterikoi toixoi spitiou
		"WOOD_016.bmp" ,
		"WOOD_016.bmp"				// porta apo thn mesa pleura
};

void display(void){
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, eyeX + lookXAt, eyeY + lookYAt, eyeZ + lookZAt, 0.0f, 1.0f, 0.0f);

    if(daylight == 1){
	   glPushMatrix();
	   glClearColor (0.55,0.89,0.93,0.0);
	   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   sun();
       glTranslatef(8.0,8.0,2.5);
       glScalef(1.0,1.0,0.7);
       glutSolidSphere(0.5,20,16);
       glPopMatrix();
       glDisable(GL_LIGHTING);
   }
	if(daylight == 0){
	   glPushMatrix();
	   glClearColor (0.06,0.06,0.23,0.0);
	   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   moon();
       glTranslatef(-6.0,8.0,2.5);
       glScalef(1.0,1.0,0.7);
       glutSolidSphere(0.4,20,16);
       glPopMatrix();
       glDisable(GL_LIGHTING);
   }

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glScalef(0.08,0.07,0.01);
	glTranslatef (20.0, 26.0, -800.0);
	glRotatef(15,1,0,0);
	glPopMatrix();

	 glDisable(GL_LIGHTING);
	//sofa
	glPushMatrix();
	glTranslatef(0.5,0,-6);
	glPushMatrix();
	glTranslatef(3.0,0.8,-2.5);
    //sofasides
	glPushMatrix();
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTranslatef(-0.925,0.1,-0.1);
	//frontsofa
	glPushMatrix();
	glTranslatef(0.0,0.0,0.4);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.075,-0.3,0.0); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.075,-0.3,0.0); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.075,0.3,0.0);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.075,0.3, 0.0);
	glEnd();
	glPopMatrix();
	//backsofa
	glPushMatrix();
	glTranslatef(0.0,0.0,-0.4);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.075,-0.3,0.0); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.075,-0.3,0.0);
	glTexCoord2d(1.0,1.0); glVertex3d(-0.075,0.3,0.0);
	glTexCoord2d(0.0,1.0); glVertex3d(0.075,0.3, 0.0);
	glEnd();
	glPopMatrix();
	//upside
	glPushMatrix();
	glTranslatef(0.0,0.3,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.075,0.0,0.4); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.075,0.0,0.4); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.075,0.0,-0.4);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.075,0.0,-0.4);
	glEnd();
	glPopMatrix();
	//outside view
	glPushMatrix();
	glTranslatef(-0.075,0.0,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.3,-0.4); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.3,0.4); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.3,0.4);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.3,-0.4);
	glEnd();
	glPopMatrix();
	//inside view
	glPushMatrix();
	glTranslatef(0.075,0.0,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.3,0.4); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.3,-0.4); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.3,-0.4);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.3,0.4);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.925,0.1,-0.1);
   //coucharms
	glPushMatrix();
	glTranslatef(0.0,0.0,0.4);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.075,-0.3,0.0); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.075,-0.3,0.0); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.075,0.3,0.0);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.075,0.3, 0.0);
	glEnd();
	glPopMatrix();

   //backview couharms
	glPushMatrix();
	glTranslatef(0.0,0.0,-0.4);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.075,-0.3,0.0); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.075,-0.3,0.0); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.075,0.3,0.0);
	glTexCoord2d(0.0,1.0); glVertex3d(0.075,0.3, 0.0);
	glEnd();
	glPopMatrix();

   //upview
	glPushMatrix();
	glTranslatef(0.0,0.3,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.075,0.0,0.4);
	glTexCoord2d(1.0,0.0); glVertex3d(0.075,0.0,0.4); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.075,0.0,-0.4);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.075,0.0,-0.4);
	glEnd();
	glPopMatrix();

   //inview
	glPushMatrix();
	glTranslatef(-0.075,0.0,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.3,-0.4); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.3,0.4); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.3,0.4);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.3,-0.4);
	glEnd();
	glPopMatrix();
	
	//outview
	glPushMatrix();
	glTranslatef(0.075,0.0,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.3,0.4); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.3,-0.4); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.3,-0.4);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.3,0.4);
	glEnd();
	glPopMatrix();
	glPopMatrix();

    //couch back
	glPushMatrix();
	glTranslatef(0.0,0.2,-0.4);
	//frontview
	glPushMatrix();
	glTranslatef(0.0,0.0,0.1);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.85,-0.4,0.0); //with our vertices we have to assign a texcoord
	glTexCoord2d(1.0,0.0); glVertex3d(0.85,-0.4,0.0); //so that our texture has some points to draw to
	glTexCoord2d(1.0,1.0); glVertex3d(0.85,0.4,0.0);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.85,0.4,0.0);
	glEnd();
	glPopMatrix();
	//backview
	glPushMatrix();
	glTranslatef(0.0,0.0,-0.1);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.85,-0.4,0.0); //with our vertices we have to assign a texcoord
	glTexCoord2d(1.0,0.0); glVertex3d(-0.85,-0.4,0.0); //so that our texture has some points to draw to
	glTexCoord2d(1.0,1.0); glVertex3d(-0.85,0.4,0.0);
	glTexCoord2d(0.0,1.0); glVertex3d(0.85,0.4,0.0);
	glEnd();
	glPopMatrix();
	//upview
	glPushMatrix();
	glTranslatef(0.0,0.4,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.85,0.0,0.1); //with our vertices we have to assign a texcoord
	glTexCoord2d(1.0,0.0); glVertex3d(0.85,0.0,0.1); //so that our texture has some points to draw to
	glTexCoord2d(1.0,1.0); glVertex3d(0.85,0.0,-0.1);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.85,0.0,-0.1);
	glEnd();
	glPopMatrix();
	//leftview
	glPushMatrix();
	glTranslatef(-0.85,0.0,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.4,-0.1); //with our vertices we have to assign a texcoord
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.4,0.1); //so that our texture has some points to draw to
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.4,0.1);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.4,-0.1);
	glEnd();
	glPopMatrix();
	//outview
	glPushMatrix();
	glTranslatef(0.85,0.0,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.4,0.1); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.4,-0.1); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.4,-0.1);	
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.4,0.1);
	glEnd();
	glPopMatrix();
	glPopMatrix();
   
      //couchpillow
	
	//frontview
	glPushMatrix();
	glTranslatef(0.0,0.0,0.3);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.85,-0.2,0.0); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.85,-0.2,0.0); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.85,0.2,0.0);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.85,0.2,0.0);
	glEnd();
	glPopMatrix();
	//upview
	glPushMatrix();
	glTranslatef(0.0,0.2,0.0);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[1]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.85,0.0,0.3); //with our vertices we have to assign a texcoord
	glTexCoord2d(1.0,0.0); glVertex3d(0.85,0.0,0.3); //so that our texture has some points to draw to
	glTexCoord2d(1.0,1.0); glVertex3d(0.85,0.0,-0.3);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.85,0.0,-0.3);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glColor3f(1,1,1);
	
	//Roof
	//frontpart
	illumination_roof();

	glBegin(GL_POLYGON);
	glVertex3f(-4.125,5,-5.0);	
	glVertex3f(-8.125,3.5,-1.0);
	glVertex3f(8.875,3.5,-1.0);
	glVertex3f(4.875,5,-5.0);
	glEnd(); 

	//backpart
	glBegin(GL_POLYGON);
		glVertex3f(-8.125,3.5,-10);
		glVertex3f(-4.125,5,-5.0);
		glVertex3f(4.875,5,-5.0);
		glVertex3f(8.875,3.5,-10);
	glEnd(); 

	//leftpart
	glBegin(GL_TRIANGLES);
		glVertex3f(-8.125,3.5,-10.0);
		glVertex3f(-8.125,3.5,-1.0);
		glVertex3f(-4.875,5,-5.0);
	glEnd();

	//rightpart
	glBegin(GL_TRIANGLES);
		glVertex3f(8.875,3.5,-10);
		glVertex3f(3.875,5,-5.0);
		glVertex3f(8.875,3.5,-1.0);
	glEnd();


	//backwall
	glPushMatrix();
    glTranslatef(-5,2.0,-10.0);


	glPushMatrix();//left wall from window
	
	illumination();
	glScalef(2.0,3.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//right wall from window

	illumination();
	glTranslatef(5.0,0.0,0.0);
	glScalef(6.0,3.0,0.25);
	glutSolidCube(1.0);

	glPopMatrix();

	glPushMatrix();

	illumination();
	glTranslatef(10.55,0.0,0.0);
	glScalef(3.0,3.0,0.25);
	glutSolidCube(1.0);
	
	glPopMatrix();

	
	glPushMatrix();//down part from left window
	illumination();
	glTranslatef(1.5,-1.0,0.0);
	glScalef(1.5,1.0,0.25);
	glutSolidCube(1.0);

	glPopMatrix();

	glPushMatrix();//up part from left window

	illumination();
	glTranslatef(1.5,1.0,0.0);
	glScalef(1.5,1.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();//Down tha right window

	illumination();
	glTranslatef(8.5,-1.0,0.0);
	glScalef(1.5,1.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

		
	glPushMatrix();//down the right window

	illumination();
	glTranslatef(8.5,1.0,0.0);
	glScalef(1.5,1.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	glPopMatrix();

	//left wall

	glPushMatrix();
    glTranslatef(-6,2.0,-9.625);

	glPushMatrix();
	illumination();
	glScalef(0.25,3.0,1.0);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,2.525);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,3.0,2.05);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0.0,0.0,5.05);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,3.0,2.0);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,8.0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,3.0,1.0);
	glutSolidCube(1.0);
	 
	glPopMatrix();


	glPushMatrix();//down part of the wall beside the window
	glTranslatef(0.0,-1.0,1.0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,1.01);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//up part of the wall beside the window
	glTranslatef(0.0,1.0,1.0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,1.01);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();//down part of the wall beside the 2ndwindow
	glTranslatef(0.0,-0.75,3.8);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.5,0.6);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//up part of the wall beside the 2ndwindow
	glTranslatef(0.0,1.0,3.8);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,0.6);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//down part of the wall beside the 3ndwindow
	glTranslatef(0.0,-1.0,6.775);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,1.46);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//up part of the wall beside the 2ndwindow
	glTranslatef(0.0,1.0,6.775);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,1.46);
	glutSolidCube(1.0);
	 
	glPopMatrix();
    glPopMatrix();


	//rear wall

	glPushMatrix();
    glTranslatef(-5.125,2.0,-1.0);
	 


	glPushMatrix();//left
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(2.0,3.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//right
	glColor3f(0.0,1.0,0.0);
	illumination();
	glTranslatef(1.5,-1.0,0.0);
	glScalef(1.5,1.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//up
	glColor3f(0.0,1.0,0.0);
	illumination();
	glTranslatef(1.5,1.0,0.0);
	glScalef(1.5,1.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();//right
	glTranslatef(3.8,0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(3.6,3.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();//down door
	glColor3f(0.0,1.0,0.0);
	illumination();
	glTranslatef(6.1,-1.475,0.0);
	glScalef(1.0,0.05,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//up door
	glColor3f(0.0,1.0,0.0);
	illumination();
	glTranslatef(6.1,1.275,0.0);
	glScalef(1.0,0.45,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();//right from the door
	glTranslatef(7.6,0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(2.0,3.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//front door
	glTranslatef(6.1,-0.225,0);
	glTranslatef(-0.5,0,0);
	glRotatef(door_left,0,1,0);
	glTranslatef(0.5,0,0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1,2.5,0.001);
	 
	glPopMatrix();

	

	glPushMatrix();//down the 2nd door
	glColor3f(0.0,1.0,0.0);
	illumination();
	glTranslatef(9.6,-1.475,0.0);
	glScalef(2.0,0.05,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//up the 2nd door
	glColor3f(0.0,1.0,0.0);
	illumination();
	glTranslatef(9.6,1.275,0.0);
	glScalef(2.0,0.45,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();

		glPushMatrix();//right the 2 nd door
	glTranslatef(11.325,0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1.45,3.0,0.25);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	
	glPushMatrix();//left from the 2nd door
	glTranslatef(9.1,-0.225,0);
	glTranslatef(-0.5,0,0);
	glRotatef(door_left,0,1,0);
	glTranslatef(0.5,0,0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1,2.5,0.1);
	
	 
	glPopMatrix();

	glPushMatrix();//fyllo deksi 2hs portas
	glTranslatef(10.1,-0.225,0);
	glTranslatef(0.5,0,0);
	glRotatef(door_right,0,1,0);
	glTranslatef(-0.5,0,0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1,2.5,0.1);
	glPopMatrix();
	glPopMatrix();

	//right wall
	glPushMatrix();
    glTranslatef(7.0,2.0,-9.125);

	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,3.0,2.0);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,3.5);
    glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,3.0,3.0);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//wall piece up the 1st window 
	glTranslatef(0.0,1.0,1.5);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,1.01);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();//down
	glTranslatef(0.0,-1.0,1.5);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,1.01);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0.0,0.0,7.0);
    glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,3.0,2.5);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPushMatrix();//wall piece up the 2nd window 
	glTranslatef(0.0,1.0,5.5);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,1.0);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	
	glPushMatrix();//down
	glTranslatef(0.0,-1.0,5.5);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.25,1.0,1.0);
	glutSolidCube(1.0);
	 
	glPopMatrix();
    glPopMatrix();

	//OUtside walls

	
	glPushMatrix();
    glTranslatef(-0.825,2.0,-9.625);

	glPushMatrix();
	 glTranslatef(0,0.0,1.475);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.1,3.0,3.35);
	glutSolidCube(1.0);
	 


	glPopMatrix();
	glPopMatrix();

	

	
	glPushMatrix();
    glTranslatef(-0.825,2.0,-9.625);

	
	glPushMatrix();
	glTranslatef(0.0,0.0,6.7);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.1,3.0,3.7);
	glutSolidCube(1.0);
	 
	glPopMatrix();

    glPopMatrix();

	//wall left from the door
	glPushMatrix();
    glTranslatef(-4.125,2.0,-10.0);

    glPushMatrix();
	glTranslatef(0.0,0.0,3.475);
	glColor3f(0.0,1.0,0.0);
	illumination();
	
	glScalef(3.5,3.0,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	

	//wall right from the door
    glPushMatrix();
	glTranslatef(3.0,0.0,3.475);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.5,3.0,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	
	
	//wallpiece up  the door(room)
	glPushMatrix();
	glTranslatef(2.275,1.275,3.475);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1.20,0.45,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	//down
	glPushMatrix();
	glTranslatef(2.275,-1.475,3.475);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1.20,0.05,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	//room door
	glPushMatrix();
	glTranslatef(2.275,-0.225,3.475);
	glTranslatef(-0.5,0,0);
	glRotatef(door_left,0,1,0);
	glTranslatef(0.5,0,0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1,2.5,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPopMatrix();

	//wall left as you enter
	glPushMatrix();
   glTranslatef(-4.125,2.0,-10.0);


	glPushMatrix();
	glTranslatef(0.0,0.0,5.275);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(3.5,3.0,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	

	//wall right from the door as you enter
	glPushMatrix();
	glTranslatef(3.0,0.0,5.275);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.5,3.0,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	//up
	glPushMatrix();
	glTranslatef(2.275,1.275,5.275);
	glColor3f(0.0,1.0,0.0);
	illumination();
	
	glScalef(1.20,0.45,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	//down
	glPushMatrix();
	glTranslatef(2.275,-1.475,5.275);
	illumination();
	glScalef(1.20,0.05,0.1);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	//room door
	glPushMatrix();
	glTranslatef(2.275,-0.225,5.275);
	glTranslatef(-0.5,0,0);
	glRotatef(door_right,0,1,0);
	glTranslatef(0.5,0,0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1,2.5,0.01);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	glPopMatrix();

	//door room
	glPushMatrix();
   glTranslatef(-5,2.0,-10.0);
	//right from the door
	glPushMatrix();
	 glTranslatef(2.2,0.0,3.625);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.1,3.0,0.4);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	//left
	glPushMatrix();
	glTranslatef(2.2,0.0,5.025);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.1,3.0,0.6);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	//down
	glPushMatrix();
	 glTranslatef(2.2,-1.475,4.225);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.1,0.05,1.5);
	glutSolidCube(1.0);
	 
	glPopMatrix();

	//roomdoor
	glPushMatrix();
	glTranslatef(2.2,-0.225,4.225);
	glTranslatef(0,0,-0.4);
	glRotatef(door_left,0,1,0);
	glTranslatef(0,0,0.40);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.01,2.5,1);
	glutSolidCube(1.0);
	 
	glPopMatrix();
	//up the door
	glPushMatrix();
	glTranslatef(2.2,1.275,4.225);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.1,0.45,1.5);
	glutSolidCube(1.0);
	 
	glPopMatrix();
    
	
	glPopMatrix();
	
	glDisable(GL_LIGHTING);  
	glDisable(GL_LIGHT1); 
	
	//	fence 
   illumination_door();
   
   float bars1=-10.0;
   for(int j=0; j<=20; j++){
   
   glPushMatrix();
   glTranslatef(bars1,0.2,8.3);
   //bars
   glPushMatrix();
   glScalef(0.03,1.5,0.03);
   glutSolidCube (1.0);
   glPopMatrix();
    
   glPushMatrix();
	glTranslatef(0.0,0.68,0.0);
	
	glRotatef(-90,1.0,0.0,0.0);
	glutSolidCone(0.05,0.1,15,15);//kwnos kagkelou
    glPopMatrix();
   
   glPopMatrix();
   bars1=bars1+1;
   }
	
   float bars2=8.0;
   for(int k=0; k<=20; k++){// left fence
   
   glPushMatrix();
   glTranslatef(-10,0.2,bars2);

   glPushMatrix();
   glScalef(0.03,1.5,0.03);
   glutSolidCube (1.0);
   glPopMatrix();
    
   glPushMatrix();
	glTranslatef(0.0,0.68,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	glutSolidCone(0.05,0.1,15,15);
    glPopMatrix();
   
   glPopMatrix();
   bars2=bars2-1;
   }

     float bars3=8.0;
   for(int k=0; k<=20; k++){// right fence
   
   glPushMatrix();
   glTranslatef(10,0.2,bars3);

   glPushMatrix();
   glScalef(0.03,1.5,0.03);
   glutSolidCube (1.0);
   glPopMatrix();
    
   glPushMatrix();
	glTranslatef(0.0,0.68,0.0);
	
	glRotatef(-90,1.0,0.0,0.0);
	glutSolidCone(0.05,0.1,15,15);
    glPopMatrix();
   
   glPopMatrix();
   bars3=bars3-1;
   }

    float bars4=-10.0;
   for(int k=0; k<=20; k++){// back fence
   
   glPushMatrix();
   glTranslatef(bars4,0.2,-13);

   glPushMatrix();
   glScalef(0.03,1.5,0.03);
   glutSolidCube (1.0);
   glPopMatrix();
    
   glPushMatrix();
	glTranslatef(0.0,0.68,0.0);

	glRotatef(-90,1.0,0.0,0.0);
	glutSolidCone(0.05,0.1,15,15);
    glPopMatrix();
   
   glPopMatrix();
   bars4=bars4+1;
   }

   //horizontal bars
	
   glPushMatrix();
   glTranslatef(0.0,0.2,8.3);

   glPushMatrix();
   
   glScalef(20.0,0.05,0.03);
   glRotatef(90,1.0,0.0,0.0);
   glutSolidCube (1.0);
   glPopMatrix();

    glPopMatrix();

	
   glPushMatrix();//horizontal front
   glTranslatef(0.0,0.7,8.3);

   glPushMatrix();//
   
   glScalef(20.0,0.05,0.03);
   glRotatef(90,1.0,0.0,0.0);
   glutSolidCube (1.0);
   glPopMatrix();

    glPopMatrix();


	
   glPushMatrix();//horizontal  back-down
   glTranslatef(0.0,0.2,-13.0);

   glPushMatrix();
   
   glScalef(20.0,0.05,0.03);
   glRotatef(90,1.0,0.0,0.0);
   glutSolidCube (1.0);
   glPopMatrix();

    glPopMatrix();

	
   glPushMatrix();//horizontal  back-up
   glTranslatef(0.0,0.7,-13.0);

   glPushMatrix();
   
   glScalef(20.0,0.05,0.03);
   glRotatef(90,1.0,0.0,0.0);
   glutSolidCube (1.0);
   glPopMatrix();

    glPopMatrix();



   glPushMatrix();//horizontal back-left
   glTranslatef(-10.0,0.2,-2.5);

   glPushMatrix();//kagelo.
   glRotatef(90,0.0,1.0,0.0);
   glScalef(21.6,0.05,0.03);
  
   glutSolidCube (1.0);
   glPopMatrix();
   glPopMatrix();

	
   glPushMatrix();//up-left
    glTranslatef(-10.0,0.7,-2.5);

   glPushMatrix();
   glRotatef(90,0.0,1.0,0.0);
   glScalef(21.6,0.05,0.03);
  
   glutSolidCube (1.0);
   glPopMatrix();

    glPopMatrix();

	
   glPushMatrix();//down right
   glTranslatef(10.0,0.2,-2.5);

   glPushMatrix();
   glRotatef(90,0.0,1.0,0.0);
   glScalef(21.6,0.05,0.03);

   glutSolidCube (1.0);
   glPopMatrix();
   glPopMatrix();

	//up-right
   glPushMatrix();
    glTranslatef(10.0,0.7,-2.5);

   glPushMatrix();
   glRotatef(90,0.0,1.0,0.0);
   glScalef(21.6,0.05,0.03);
  
   glutSolidCube (1.0);
   glPopMatrix();

    glPopMatrix();


	
	//piano
	glPushMatrix();
	glTranslatef(0.2,0,-6.9);   
   
    glPushMatrix();
	

	illumination_door();
    glTranslatef(5.8,0.8,1.65);
	glPushMatrix();// back side
    glTranslatef(0.0,0.4,0.0);
    glScalef(0.55,1.4,1.6);
    glutSolidCube (1.0);
    glPopMatrix();
	glPushMatrix();//front
    glTranslatef(0.475,-0.1,0.0);
    glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.3,0.52,-0.78);
	glScalef(0.3,0.15,0.05);
    glutSolidCube (1.0);
    glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.3,0.52,0.78);
	glScalef(0.3,0.15,0.05);
    glutSolidCube (1.0);
    glPopMatrix();

	glDisable(GL_LIGHTING); 
	glDisable(GL_LIGHT1);

    glPushMatrix();//  keyboard white
    glColor3f(0.9,0.9,0.9);
	glTranslatef(-0.3,0.52,0.0);
	glScalef(0.3,0.05,1.55);
    glutSolidCube (1.0);
    glPopMatrix();
	 
	//glPushMatrix();// keyboard blck
	float pianokey=-0.7;
	for(int i=0; i<=14; i++){
	glPushMatrix();
	glColor3f(0.0,0.0,0.0); 
	glTranslatef(-0.3,0.52,pianokey);
	glScalef(0.25,0.08,0.01);
    glutSolidCube (1.0);
	pianokey=pianokey+0.1;
	glPopMatrix();
	}
	glColor3d(1,1,1);
	//piano chair

	illumination_door();

	glTranslatef(-0.95,0.0,0.0);

	glPushMatrix();// back side
    glScalef(0.3,0.5,0.3);
    glutSolidCube (1.0);
    glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glDisable(GL_LIGHTING); 
	glDisable(GL_LIGHT1);


	//table 

	illumination_door();
	glPushMatrix();
	glTranslatef(1.5,0.4,-16.5);
	glPushMatrix();
   
	glTranslatef(-2.0,0.2,7.3);
	
	// table
	glPushMatrix();//back-left leg
	glScalef(0.1,0.6,0.1);
	glutSolidCube (1.0);
	glPopMatrix();

	glPushMatrix();//front-left
	glTranslatef(0.7,0.0,0.0);
	glScalef(0.1,0.6,0.1);
	glutSolidCube (1.0);
	glPopMatrix();

   
	glPushMatrix();//front-right 
	glTranslatef(0.0,0.0,0.7);
	glScalef(0.1,0.6,0.1);
	glutSolidCube (1.0);
	glPopMatrix();

    glPushMatrix();
	glTranslatef(0.7,0.0,0.7);
	glScalef(0.1,0.6,0.1);
	glutSolidCube (1.0);
	glPopMatrix();

	//tavla
    glPushMatrix();
	glTranslatef(0.35,0.25,0.35);
	glScalef(0.8,0.1,0.8);
	glutSolidCube (1.0);
	glPopMatrix();
   
	glPopMatrix();

	//TV

	glPushMatrix();
	glTranslatef(-2.0,0.2,7.3);


    glPushMatrix();//box
	glTranslatef(0.35,0.55,0.35);
	glScalef(0.75,0.6,0.5);
	glutSolidCube (1.0);
	glPopMatrix();
   
    glDisable(GL_LIGHTING);   
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();//screen
	glTranslatef(0.3,0.55,0.46);
	glScalef(0.55,0.4,0.3);
	glutSolidCube (1.0);
	glPopMatrix();
	
	float tvbutton=0.75;
	for(int k=0; k<=4; k++){

	glPushMatrix();//buttons
	glTranslatef(0.68,tvbutton,0.6);
	glScalef(0.03,0.03,0.03);
	glutSolidCube (1.0);
	tvbutton=tvbutton-0.08;
	glPopMatrix();
	}

	
    glPushMatrix();//antenna
	glTranslatef(0.0,1.0,0.35);
	glScalef(0.01,0.6,0.01);
	glutSolidCube (1.0);
	glPopMatrix();

   
    glPushMatrix();//antenna2
    glTranslatef(0.0,1.0,0.2);
	glRotatef(-45,1.0,0.0,0.0);
	glScalef(0.01,0.6,0.01);
    
	glutSolidCube (1.0);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//bed
	illumination_door();
	glPushMatrix();
	glTranslatef(-7,0.5,-9.7);

	glPushMatrix();
   
	glTranslatef(3.0,0.2,7.3);
  
	glPushMatrix();
	glScalef(1.7,0.32,1.4);
	glutSolidCube (1.0);
	glPopMatrix();

	glPushMatrix();// back side bed
	glTranslatef(-0.9,0.3,0);
    glScalef(0.1,0.92,1.4);
    glutSolidCube (1.0);
	glPopMatrix();

	  
	glPushMatrix();
	glTranslatef(-0.9,0.6,0);
    glScalef(0.05,0.52,1.2);
    glutSolidCube (1.0);
	glPopMatrix();

	glDisable(GL_LIGHTING);    
	glPushMatrix();// matress
	glColor3f(0.8,0.9,1.0);
	glTranslatef(0.0,0.2,0);
    glScalef(1.6,0.1,1.1);
    glutSolidCube (1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//lamp
	glPushMatrix();
	glTranslatef(6,0.8,-6.3); 
	sun();
	glPushMatrix();
	glTranslatef(-3.0,0.7,0);
	glRotatef(-90,1.0,0.0,0.0);
    glScalef(0.2,0.2,0.2);
	glutSolidSphere(0.7,15,15);
	glPopMatrix();
	glDisable(GL_LIGHTING);
	//vase
	glPushMatrix();
	glColor3f(0.4,0.3,0.3);
	glTranslatef(-3.0,0.2,0);
	glRotatef(-90,1.0,0.0,0.0);
    glScalef(0.2,0.2,0.2);
	glutSolidCone(0.4,2,15,15);
	glPopMatrix();

	  
	glPushMatrix();//up side
	glColor3f(0.4,0.3,0.3);
	glTranslatef(-3.0,0.7,0);
	glRotatef(90,1.0,0.0,0.0);
    glScalef(0.2,0.2,0.2);
	glutSolidCone(0.4,2,15,15);
	glPopMatrix();

	glColor3f(1,1,1);

    illumination_door();

	glPushMatrix();//down side
	glTranslatef(-0.6,0.2,0);
    glScalef(0.3,0.3,0.4);
    glutSolidCube (1.0);
	glPopMatrix();
	glPopMatrix();

	//table2
	glPushMatrix();
	glTranslatef(0,0,-5);
	illumination_door();
	glPushMatrix();
	glTranslatef(3.0,0.96,-1.3);
     
	glPushMatrix();// back right leg
	glTranslatef(0.475,-0.1,0.0);
	glScalef(0.15,0.32,0.4);
	glutSolidCube (1.0);
	glPopMatrix();

	glPushMatrix();// back left
	glTranslatef(-0.475,-0.1,0.0);
	glScalef(0.15,0.32,0.4);
	glutSolidCube (1.0);
	glPopMatrix();

    //tavla
	 
	glScalef(1.0,0.08,1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glDisable(GL_LIGHTING); 
	glDisable(GL_LIGHT1);
	glPopMatrix();
	glFlush();

	//yard
   
	glEnable( GL_TEXTURE_2D );
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[2]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-25.0,0.0,25.0); 
	glTexCoord2d(50.0,0.0); glVertex3d(25.0,0.0,25.0); 
	glTexCoord2d(50.0,50.0); glVertex3d(25.0,0.0,-25.0);
	glTexCoord2d(0.0,50.0); glVertex3d(-25.0,0.0, -25.0);
	glEnd();
	glDisable( GL_TEXTURE_2D );

	//path
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(0.0,0.01,0.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[3]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.35,0.1,25.0); 
	glTexCoord2d(2.0,0.0); glVertex3d(1.65,0.1,25.0); 
	glTexCoord2d(2.0,20.0); glVertex3d(1.65,0.1,-2);
	glTexCoord2d(0.0,20.0); glVertex3d(0.35,0.1,-2);
	glEnd();
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();

	

	//texture1
	glPushMatrix();
	glTranslatef(0.97,1.785,-1.0);
	glTranslatef(0.6,0.0,0.0);
	glRotatef((GLfloat) door_right, 0.0, 1.0, 0.0);
	glTranslatef(-0.6,0.0,0.0);
     //front view
	glPushMatrix();
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[4]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-1.25,0.1); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.5,-1.25,0.1); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.5,1.25,0.1);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.5,1.25, 0.1);
	glEnd();
	
     //back view
	glPushMatrix();
	glTranslatef(0,0,-0.25);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[13]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-1.25,0.1); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.5,-1.25,0.1); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.5,1.25,0.1);
	glTexCoord2d(0.0,1.0); glVertex3d(0.5,1.25, 0.1);
	glEnd();   
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glEnable (GL_BLEND);
	glDepthMask (GL_FALSE);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	GLfloat balkonoporta[] = {0.8,0.,1,1};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, balkonoporta);
	glColor4fv(balkonoporta);

	//2nd door texture
	glPushMatrix();
	glTranslatef(3.95 ,1.785,-1.0);
	glTranslatef(-0.6,0.0,0.0);
	glRotatef((GLfloat) door_left, 0.0, 1.0, 0.0);
	glTranslatef(0.6,0.0,0.0);
     
	glPushMatrix();
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[12]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-1.25,0.1);
	glTexCoord2d(1.0,0.0); glVertex3d(0.5,-1.25,0.1); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.5,1.25,0.1);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.5,1.25, 0.1);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(4.95,1.785,-1.0);
	glTranslatef(0.6,0.0,0.0);
	glRotatef((GLfloat) door_right, 0.0, 1.0, 0.0);
	glTranslatef(-0.6,0.0,0.0);
	glPushMatrix();
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[12]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-1.25,0.1); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.5,-1.25,0.1); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.5,1.25,0.1);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.5,1.25, 0.1);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(3.95 ,1.785,-1.0);
	glTranslatef(-0.6,0.0,0.0);
	glRotatef((GLfloat) door_left, 0.0, 1.0, 0.0);
	glTranslatef(0.6,0.0,0.0);
     //mprostini pleura
	glPushMatrix();
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[12]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-1.25,0.1); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.5,-1.25,0.1); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.5,1.25,0.1);
	glTexCoord2d(0.0,1.0); glVertex3d(0.5,1.25, 0.1);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//2nd door texture 
	
	glPushMatrix();
	glTranslatef(4.95,1.785,-1.0);
	glTranslatef(0.6,0.0,0.0);
	glRotatef((GLfloat) door_right, 0.0, 1.0, 0.0);
	glTranslatef(-0.6,0.0,0.0);
	glPushMatrix();
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D,array_of_textures[12]);
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-1.25,0.1); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.5,-1.25,0.1); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.5,1.25,0.1);
	glTexCoord2d(0.0,1.0); glVertex3d(0.5,1.25, 0.1);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);

	//front wall texture
	glPushMatrix();
	glTranslatef(-5.125,2.0,-0.85);

	// left from window
	
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-1,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(1,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(1,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-1,1.5,0.01);
	glEnd();
	glPopMatrix();

	// down the window
	glTranslatef(-3.625,1.0,-0.85);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.5,0.5,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.5,0.5,0.01);
	glEnd();
	
	//Window

	glPushMatrix();
	glTranslatef(0,1.0,0.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.5,0.5,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.5,0.5,0.01);
	glEnd();
	glPopMatrix();

	//Inside view window

	glPushMatrix();
	glTranslatef(0,1.0,-0.2);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.5,0.5,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(0.5,0.5,0.01);
	glEnd();
	glPopMatrix();




	
	// Up the window
	glTranslatef(0.0,2.0,0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.5,0.5,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.5,0.5,0.01);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	

	// Right
	glPushMatrix();
	glTranslatef(2.3,-1.0,0.01);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-1.8,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(1.8,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(1.8,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-1.8,1.5,0.01);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//Up the door
	glPushMatrix();
	glTranslatef(4.6,0.255,0.01);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-0.225,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.5,-0.225,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.5,0.225,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.5,0.225,0.01);
	glEnd();
	glPopMatrix();

		//Down
	glPushMatrix();
	glTranslatef(4.6,-2.45,0.01);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-0.05,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.5,-0.05,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.5,0.05,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.5,0.05,0.01);
	glEnd();
	glPopMatrix();

		//Right
	glPushMatrix();
	glTranslatef(6.1,-1.0,0.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-1,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(1,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(1,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-1,1.5,0.01);
	glEnd();
	glPopMatrix();

	//Up the door
	glPushMatrix();
	glTranslatef(8.1,0.255,0.01);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-1.0,-0.225,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(1.0,-0.225,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(1.0,0.225,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(-1.0,0.225,0.01);
	glEnd();
	glPopMatrix();

	//Down the 2nd door
	glPushMatrix();
	glTranslatef(8.1,-2.45,-0.01);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-1,-0.05,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(1,-0.05,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(1,0.05,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(-1,0.05,0.01);
	glEnd();
	glPopMatrix();

	//Right
	glPushMatrix();
	glTranslatef(9.925,-1.0,-0.01);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.85,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.85,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.85,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.85,1.5,0.01);
	glEnd();
	glPopMatrix();

	glPopMatrix();





	
	//front wall texture
	glPushMatrix();
	glTranslatef(-1.5,-1.0,-0.3);

	// left from the window
	
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(1,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-1,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(-1,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(1,1.5,0.01);
	glEnd();
	glPopMatrix();

	// down from the window
	glTranslatef(0.0,-2.0,-0.3);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.5,0.5,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(0.5,0.5,0.01);
	glEnd();
	
	
	// up from the window
	glTranslatef(0.0,2.0,0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.5,0.5,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(0.5,0.5,0.01);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	

	// right
	glPushMatrix();
	glTranslatef(2.3,-1.0,0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(1.8,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-1.8,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(-1.8,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(1.8,1.5,0.01);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//up from the door
	glPushMatrix();
	glTranslatef(4.6,0.255,-0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-0.2255,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.5,-0.2255,0.01);
	glTexCoord2d(1.0,1.0); glVertex3d(-0.5,0.2255,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(0.5,0.2255,0.01);
	glEnd();
	glPopMatrix();

		//down
	glPushMatrix();
	glTranslatef(4.6,-2.45,-0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-0.05,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.5,-0.05,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.5,0.05,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(0.5,0.05,0.01);
	glEnd();
	glPopMatrix();

		//right
	glPushMatrix();
	glTranslatef(6.1,-1.0,-0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(1,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-1,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(-1,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(1,1.5,0.01);
	glEnd();
	glPopMatrix();

	//up
	glPushMatrix();
	glTranslatef(8.1,0.255,-0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(1.01,-0.2255,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(-1.01,-0.2255,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(-1.01,0.2255,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(1.01,0.2255,0.01);
	glEnd();
	glPopMatrix();

	//down
	glPushMatrix();
	glTranslatef(8.1,-2.45,-0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(1,-0.05,0.01); 
	glTexCoord2d(1.0,0.0); glVertex3d(-1,-0.05,0.01); 
	glTexCoord2d(1.0,1.0); glVertex3d(-1,0.05,0.01);
	glTexCoord2d(0.0,1.0); glVertex3d(1,0.05,0.01);
	glEnd();
	glPopMatrix();

	//right from the 2nd door

	glPushMatrix();
	glTranslatef(9.925,-1.0,-0.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.85,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-0.85,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(-0.85,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(0.85,1.5,0.01);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	//Left wall

	//backfrom the window
	glPushMatrix();
    glTranslatef(-12.45,0.0,-8.5);

	glPushMatrix();
	glTranslatef(9.925,-1.0,0.03);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-1.5,-0.55); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-1.5,0.55); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.5,0.55);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,1.5,-0.55);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//up from the window
	glPushMatrix();
	glTranslatef(-2.55,-0.02,-7.482);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,-0.5); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();

	// Window
	glPushMatrix();
	glTranslatef(-2.55,-1.0,-7.482);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,-0.5); 
	glTexCoord2d(2.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(2.0,2.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,2.0); glVertex3d(-0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();
 
	// inside window
	glPushMatrix();
	glTranslatef(-2.45,-1.0,-7.482);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,0.5); 
	glTexCoord2d(2.0,0.0); glVertex3d(0.0,-0.5,-0.5);
	glTexCoord2d(2.0,2.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,2.0); glVertex3d(-0.0,0.5,0.5);
	glEnd();
	glPopMatrix();

	//down frlom the window
	glPushMatrix();
	glTranslatef(-2.55,-2.0,-7.482);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,-0.5); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();

	//infront of the window
	glPushMatrix();
	glTranslatef(-2.55,-1.0,-5.985);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-1.5,-1.025); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-1.5,1.025); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.5,1.025);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,1.5,-1.025);
	glEnd();
	glPopMatrix();

	//paint1
	glPushMatrix();
    glTranslatef(7.0,0.0,-9.125);
	glPushMatrix();
	glTranslatef(1.8,-1.0,0.4);
    glColor3f(0.0,1.0,0.0);
	illumination();	
	glScalef(1.5,1,0.05);
	glutSolidCube(1.0);
	 
	

	//glPushMatrix();
	glTranslatef(0,0,1.3);
	
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[7] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.45,-0.45,0); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.45,-0.45,0); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.45,0.45,0);
	glTexCoord2d(0.0,1.0); glVertex3d(-.45,0.45,0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	//paint#2
	glPushMatrix();
    glTranslatef(7.0,0.0,-9.125);
	glPushMatrix();
	glTranslatef(-2,-1.0,0.4);
    glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1.5,1,0.05);
	glutSolidCube(1.0);
	 
	

	//glPushMatrix();
	glTranslatef(0,0,1.3);
	//glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[6] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.45,-0.45,0); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.45,-0.45,0); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.45,0.45,0);
	glTexCoord2d(0.0,1.0); glVertex3d(-.45,0.45,0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//paint #3
	glPushMatrix();
    glTranslatef(7.0,0.0,-9.125);
	glPushMatrix();
	glTranslatef(3.3,-0.7,4.5);
    glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(0.05,0.5,0.5);
	glutSolidCube(1.0);
	 
	

	glTranslatef(-0.6,0,0.0);
	
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[8] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0,-0.45,-0.45); 
	glTexCoord2d(1.0,0.0); glVertex3d(0,-0.45,0.45); 
	glTexCoord2d(1.0,1.0); glVertex3d(0,0.45,0.45);
	glTexCoord2d(0.0,1.0); glVertex3d(0,0.45,-0.45);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//paint4

	glPushMatrix();
    glTranslatef(-5.125,0.0,-1.0);
	glPushMatrix();
	glTranslatef(7.0,-1.0,1.0);
	glColor3f(0.0,1.0,0.0);
	illumination();
	glScalef(1.5,1.5,0.05);
	glutSolidCube(1.0);
	 
	
	glTranslatef(-0.0,0,-0.7);
	
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[5] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.45,-0.45,0); 
	glTexCoord2d(1.0,0.0); glVertex3d(-0.45,-0.45,0); 
	glTexCoord2d(1.0,1.0); glVertex3d(-0.45,0.45,0);
	glTexCoord2d(0.0,1.0); glVertex3d(0.45,0.45,0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	
	
	




	//down from wc window
	glPushMatrix();
	glTranslatef(-2.55,-1.75,-4.7);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.75,-0.35); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.75,0.35); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.75,0.35);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.75,-0.35);
	glEnd();
	glPopMatrix();

	//  wc window
	glPushMatrix();
	glTranslatef(-2.55,-0.75,-4.7);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.25,-0.3); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.25,0.3); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.25,0.3);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.0,0.25,-0.3);
	glEnd();
	glPopMatrix();

	// wc window inside view
	glPushMatrix();
	glTranslatef(-2.25,-0.75,-4.7);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.25,0.3); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.25,-0.3); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.25,-0.3);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.0,0.25,0.3);
	glEnd();
	glPopMatrix();

	//upview wc wind
	glPushMatrix();
	glTranslatef(-2.55,0.0,-4.7);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,-0.35); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,0.35); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,0.35);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,-0.35);
	glEnd();
	glPopMatrix();

	//frontview of wcwind
	glPushMatrix();
	glTranslatef(-2.55,-1.0,-3.4);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-1.5,-1); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-1.5,1); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.5,1);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,1.5,-1);
	glEnd();
	glPopMatrix();

	//up from the window
	glPushMatrix();
	glTranslatef(-2.55,0.0,-1.65);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,-0.75); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,0.75); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,0.75);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,-0.75);
	glEnd();
	glPopMatrix();

	// down
	glPushMatrix();
	glTranslatef(-2.55,-1.0,-1.65);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,-0.75); 
	glTexCoord2d(2.0,0.0); glVertex3d(0.0,-0.5,0.75); 
	glTexCoord2d(2.0,2.0); glVertex3d(0.0,0.5,0.75);
	glTexCoord2d(0.0,2.0); glVertex3d(-0.0,0.5,-0.75);
	glEnd();
	glPopMatrix();

	// inside view window
	glPushMatrix();
	glTranslatef(-2.15,-1.0,-1.65);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,0.75); 
	glTexCoord2d(2.0,0.0); glVertex3d(0.0,-0.5,-0.75);
	glTexCoord2d(2.0,2.0); glVertex3d(0.0,0.5,-0.75);
	glTexCoord2d(0.0,2.0); glVertex3d(-0.0,0.5,0.75);
	glEnd();
	glPopMatrix();

	//down from the window
	glPushMatrix();
	glTranslatef(-2.55,-2.0,-1.65);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,-0.75); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,0.75); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,0.75);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,-0.75);
	glEnd();
	glPopMatrix();

	
	//infront of the window
	glPushMatrix();
	glTranslatef(-2.55,-1.0,-0.3);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-1.5,-0.6); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-1.5,0.6); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.5,0.6);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,1.5,-0.6);
	glEnd();
	glPopMatrix();

	glPopMatrix();

		//Left wall texture

		//behind the window
	glPushMatrix();
    glTranslatef(-12.15,0.0,-8.5);

	glPushMatrix();
	glTranslatef(9.925,-1.0,0.03);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-1.5,0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-1.5,-0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.5,-0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.5,0.5);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//above the window
	glPushMatrix();
	glTranslatef(-2.15,-0.02,-7.482);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,0.5); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,-0.5);
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,0.5);
	glEnd();
	glPopMatrix();

	//below the window
	glPushMatrix();
	glTranslatef(-2.15,-2.0,-7.482);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,0.5); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,0.5);
	glEnd();
	glPopMatrix();

	//infront
	glPushMatrix();
	glTranslatef(-2.15,-1.0,-5.985);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-1.5,1.025); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-1.5,-1.025); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.5,-1.025);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,1.5,1.025);
	glEnd();
	glPopMatrix();

	//down the wc window
	glPushMatrix();
	glTranslatef(-2.15,-1.75,-4.7);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.75,0.35); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.75,-0.35); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.75,-0.35);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.75,0.35);
	glEnd();
	glPopMatrix();

	//up
	glPushMatrix();
	glTranslatef(-2.15,0.0,-4.7);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,0.35); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,-0.35);
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,-0.35);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,0.35);
	glEnd();
	glPopMatrix();

	//infront wc
	glPushMatrix();
	glTranslatef(-2.15,-1.0,-3.4);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-1.5,1); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-1.5,-1); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.5,-1);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,1.5,1);
	glEnd();
	glPopMatrix();

	//above the window
	glPushMatrix();
	glTranslatef(-2.15,0.0,-1.65);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,0.75); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,-0.75);
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,-0.75);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,0.75);
	glEnd();
	glPopMatrix();

	//below the window
	glPushMatrix();
	glTranslatef(-2.15,-2.0,-1.65);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-0.5,0.75); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-0.5,-0.75);
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,0.5,-0.75);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,0.5,0.75);
	glEnd();
	glPopMatrix();

	
	//infront of the window
	glPushMatrix();
	glTranslatef(-2.15,-1.0,-0.3);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.0,-1.5,0.6); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.0,-1.5,-0.6); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.5,-0.6);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.0,1.5,0.6);
	glEnd();
	glPopMatrix();

		glPopMatrix();
			glPopMatrix();

	//rear wall

	glPushMatrix();
    glTranslatef(-1.4,-1.0,-9.0);

	// left from the window1st
	

	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(1.1,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-1.1,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(-1.1,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(1.1,1.5,0.01);
	glEnd();

	glPopMatrix();

	
	//above the window

	glPushMatrix();
    glTranslatef(0.2,0.0,-9.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(-0.5,0.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(0.5,0.5,0.01);
	glEnd();
	glPopMatrix();

	//Window

	glPushMatrix();
    glTranslatef(0.2,-1.0,-9.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(2.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(2.0,2.0); glVertex3d(-0.5,0.5,0.01);
	glTexCoord2d(0.0,2.0); glVertex3d(0.5,0.5,0.01);
	glEnd();
	glPopMatrix();

	//Inside view of window

	glPushMatrix();
    glTranslatef(0.2,-1.0,-8.8);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(2.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(2.0,2.0); glVertex3d(0.5,0.5,0.01);
	glTexCoord2d(0.0,2.0); glVertex3d(-0.5,0.5,0.01);
	glEnd();
	glPopMatrix();

	//below the window

	glPushMatrix();
    glTranslatef(0.2,-2.0,-9.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(-0.5,0.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(0.5,0.5,0.01);
	glEnd();
	glPopMatrix();

	//right from the window

	glPushMatrix();
    glTranslatef(3.6,-1.0,-9.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(3.0,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-3.0,-1.5,0.01);
	glTexCoord2d(4.0,4.0); glVertex3d(-3.0,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(3.0,1.5,0.01);
	glEnd();
	glPopMatrix();

	//up from the window

	glPushMatrix();
	glTranslatef(7.15,0.0,-9.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.55,-0.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-0.55,-0.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(-0.55,0.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(0.55,0.5,0.01);
	glEnd();
	glPopMatrix();

	//inside view of the window

	glPushMatrix();
    glTranslatef(7.15,-1.0,-8.8);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.55,-0.5,0.01); 
	glTexCoord2d(2.0,0.0); glVertex3d(0.55,-0.5,0.01);
	glTexCoord2d(2.0,2.0); glVertex3d(0.55,0.5,0.01);
	glTexCoord2d(0.0,2.0); glVertex3d(-0.55,0.5,0.01);
	glEnd();
	glPopMatrix();

	//window

	glPushMatrix();
    glTranslatef(7.15,-1.0,-9.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.55,-0.5,0.01); 
	glTexCoord2d(2.0,0.0); glVertex3d(-0.55,-0.5,0.01); 
	glTexCoord2d(2.0,2.0); glVertex3d(-0.55,0.5,0.01);
	glTexCoord2d(0.0,2.0); glVertex3d(0.55,0.5,0.01);
	glEnd();
	glPopMatrix();

	//below the window

	glPushMatrix();
    glTranslatef(7.15,-2.0,-9.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.55,-0.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-0.55,-0.5,0.01);
	glTexCoord2d(4.0,4.0); glVertex3d(-0.55,0.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(0.55,0.5,0.01);
	glEnd();
	glPopMatrix();

	//right from the window
	glPushMatrix();
    glTranslatef(9.225,-1.0,-9.0);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(1.55,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(-1.55,-1.5,0.01);
	glTexCoord2d(4.0,4.0); glVertex3d(-1.55,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(1.55,1.5,0.01);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	//inside wallpaper

	glPushMatrix();
    glTranslatef(-1.4,-1.0,-8.73);

	// left from window
	
	
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-1.0,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(1.0,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(1.0,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-1.0,1.5,0.01);
	glEnd();

	glPopMatrix();

	
	//above the window

	glPushMatrix();
    glTranslatef(0.1,0.0,-8.73);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.5,-0.5,0.01);
	glTexCoord2d(4.0,4.0); glVertex3d(0.5,0.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.5,0.5,0.01);
	glEnd();
	glPopMatrix();

	//below the window

	glPushMatrix();
    glTranslatef(0.1,-2.0,-8.73);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,-0.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.5,-0.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.5,0.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.5,0.5,0.01);
	glEnd();
	glPopMatrix();

	//Right from the window

	glPushMatrix();
    glTranslatef(3.6,-1.0,-8.73);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-3.0,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(3.0,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(3.0,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-3.0,1.5,0.01);
	glEnd();
	glPopMatrix();

	//Above the window

	glPushMatrix();
	glTranslatef(7.15,0.0,-8.73);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.55,-0.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.55,-0.5,0.01);
	glTexCoord2d(4.0,4.0); glVertex3d(0.55,0.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.55,0.5,0.01);
	glEnd();
	glPopMatrix();

	//Belowthe window
	glPushMatrix();
    glTranslatef(7.15,-2.0,-8.73);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.55,-0.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(0.55,-0.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(0.55,0.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-0.55,0.5,0.01);
	glEnd();
	glPopMatrix();

	//right from the window
	glPushMatrix();
    glTranslatef(9.225,-1.0,-8.73);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-1.55,-1.5,0.01); 
	glTexCoord2d(4.0,0.0); glVertex3d(1.55,-1.5,0.01); 
	glTexCoord2d(4.0,4.0); glVertex3d(1.55,1.5,0.01);
	glTexCoord2d(0.0,4.0); glVertex3d(-1.55,1.5,0.01);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Right wall

	glPushMatrix();
    glTranslatef(0.85,0.0,-8.0);
	
	glPushMatrix();
	glTranslatef(9.925,-1.0,0.03);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-1.5,1.03); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-1.5,-1.03); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.5,-1.03);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.5,1.03);
	glEnd();
	glPopMatrix();

	//above the window
	
	glPushMatrix();
	glTranslatef(10,0,1.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,0.5);
	glEnd();
	glPopMatrix();

	
	// window
	glPushMatrix();
	glTranslatef(10,-1,1.6);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,0.5);
	glEnd();
	glPopMatrix();


	// inside view of the window
	glPushMatrix();
	glTranslatef(9.5,-1,1.6);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();

	//below
	
	glPushMatrix();
	glTranslatef(10.0,-2,1.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,0.5);
	glEnd();
	glPopMatrix();

	//infront
	
	glPushMatrix();
	glTranslatef(10.0,-1,3.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-1.5,1.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-1.5,-1.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.5,-1.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.5,1.5);
	glEnd();
	glPopMatrix();

	//above
	
	glPushMatrix();
	glTranslatef(10.0,0,5.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,0.5);
	glEnd();
	glPopMatrix();

		// 2ndwindow
	
	glPushMatrix();
	glTranslatef(10,-1,5.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,0.5);
	glEnd();
	glPopMatrix();

	// inside view of the window
	
	glPushMatrix();
	glTranslatef(9.5,-1,5.4);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[9] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,-0.5);
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();

	//below the window
	
	glPushMatrix();
	glTranslatef(10.0,-2,5.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,0.5);
	glEnd();
	glPopMatrix();

	//infront
	
	glPushMatrix();
	glTranslatef(10.0,-1,7.1);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[0] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-1.5,1.25); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-1.5,-1.25);
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.5,-1.25);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.5,1.25);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	//Inside wallpaper

	glPushMatrix();
    glTranslatef(0.45,0.0,-8.0);
	
	glPushMatrix();
	glTranslatef(9.93,-1.0,0.03);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-1.5,-1.03); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-1.5,1.03); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.5,1.03);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.5,-1.03);
	glEnd();
	glPopMatrix();

	//above the window
	
	glPushMatrix();
	glTranslatef(10.0,0,1.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();

	//below the window
	
	glPushMatrix();
	glTranslatef(10.0,-2,1.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();

	//infront
	
	glPushMatrix();
	glTranslatef(10.0,-1,3.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-1.5,-1.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-1.5,1.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.5,1.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.5,-1.5);
	glEnd();
	glPopMatrix();

	//above the window
	
	glPushMatrix();
	glTranslatef(10.0,0,5.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();

	//below the window
	
	glPushMatrix();
	glTranslatef(10.0,-2,5.5);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-0.5,-0.5); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-0.5,0.5); 
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.5,0.5);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.5,-0.5);
	glEnd();
	glPopMatrix();

	//infront
	glPushMatrix();
	glTranslatef(10.0,-1,7.1);
	glColor3f(1.0,1.0,1.0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[11] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(0.0,-1.5,-1.23); 
	glTexCoord2d(1.0,0.0); glVertex3d(0.0,-1.5,1.23);
	glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.5,1.23);
	glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.5,-1.23);
	glEnd();
	glPopMatrix();

	glPopMatrix();



	//floor
   glPushMatrix();
   glTranslatef(4.15,-2.55,-3.75);
   glScalef(13.5,0.1,10.5);
   glutSolidCube(1.0);
  


	glPushMatrix();
	glTranslatef(0,0.5,0);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[10] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,0.01,0.5); 
	glTexCoord2d(8.0,0.0); glVertex3d(0.5,0.01,0.5); 
	glTexCoord2d(8.0,8.0); glVertex3d(0.5,0.01,-0.5);
	glTexCoord2d(0.0,8.0); glVertex3d(-0.5,0.01,-0.5);
	glEnd();
    glPopMatrix();

	glPushMatrix();
	glTranslatef(0,.7,0.445);
	glEnable( GL_TEXTURE_2D );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture( GL_TEXTURE_2D, array_of_textures[10] );
	glBegin (GL_POLYGON);
	glTexCoord2d(0.0,0.0); glVertex3d(-0.5,0.01,0.07); 
	glTexCoord2d(10.0,0.0); glVertex3d(0.5,0.01,0.07); 
	glTexCoord2d(10.0,10.0); glVertex3d(0.5,0.01,-0.07);
	glTexCoord2d(0.0,10.0); glVertex3d(-0.5,0.01,-0.07);
	glEnd();

	glPopMatrix();
    glPopMatrix();


   //ceiling
   glPushMatrix();
   glColor3f(1.0,1.0,1.0);
   //floor texture left side
   glEnable( GL_TEXTURE_2D );
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glBindTexture( GL_TEXTURE_2D, array_of_textures[10] );
   glBegin (GL_POLYGON);
   glTexCoord2d(0.0,0.0); glVertex3d(-6.25,0.601,4.75); 
   glTexCoord2d(1.0,0.0); glVertex3d(-0.75,0.601,4.75); 
   glTexCoord2d(1.0,1.0); glVertex3d(-0.75,0.601,-4.75);
   glTexCoord2d(0.0,1.0); glVertex3d(-6.25,0.601,-4.75);
   glEnd();
   //floor texture right side
   glBindTexture( GL_TEXTURE_2D, array_of_textures[10] );
   glBegin (GL_POLYGON);
   glTexCoord2d(0.0,0.0); glVertex3d(-0.75,0.601,2.55); 
   glTexCoord2d(1.0,0.0); glVertex3d(6.25,0.601,2.55);
   glTexCoord2d(1.0,1.0); glVertex3d(6.25,0.601,-4.75);
   glTexCoord2d(0.0,1.0); glVertex3d(-0.75,0.601,-4.75);
   glEnd();
   //
   glBindTexture( GL_TEXTURE_2D, array_of_textures[10] );
   glBegin (GL_POLYGON);
   glTexCoord2d(0.0,0.0); glVertex3d(-0.75,0.601,4.75); 
   glTexCoord2d(3.0,0.0); glVertex3d(6.25,0.601,4.75); 
   glTexCoord2d(3.0,2.0); glVertex3d(6.25,0.601,2.549);
   glTexCoord2d(0.0,2.0); glVertex3d(-0.75,0.601,2.549);
   glEnd();   
   glDisable( GL_TEXTURE_2D );
   glColor3f(0.2,0.2,0.2);
   glTranslatef(4.0,0.55,-4.25);
   glScalef(13.0,0.1,9.0);
   glutSolidCube(1.0);
   glPopMatrix();   
 
	glDisable( GL_TEXTURE_2D );



	glutSwapBuffers();

	glFlush();
}




void moveCamera(int key)
{
	
	// m: to mhkos tou dianysmatos (lookAt-eye), sto XZ epipedo
	double m = sqrt((lookXAt -eyeX)*(lookXAt-eyeX)+(lookZAt -eyeZ)*(lookZAt-eyeZ));
	double stepX = 0.05* (lookXAt -eyeX)/m;
	double stepZ = 0.05* (lookZAt -eyeZ)/m;

	if (key == FRONT_F || key == FRONT_f)
	{
		eyeX = eyeX + stepX;
		eyeZ = eyeZ + stepZ;
	}	
	
	else if (key == BACK_B || key == BACK_b)
	{
		eyeX = eyeX - stepX;
		eyeZ = eyeZ - stepZ;

	}
	

	if (key == UP_U || key == UP_u)
	{
		lookYAt += 0.3;
	}	
	
	else if (key == DOWN_D || key == DOWN_d)
	{
		lookYAt -= 0.3;

	}

	if (key == LEFT_C_L || key == LEFT_C_l) {	

		if ((lookXAt <= eyeX) && (lookZAt < eyeZ)) {

			lookXAt -= 0.3;
			lookZAt += 0.3;

		}
		else if ((lookXAt < eyeX) && (lookZAt >= eyeZ)) {

			lookXAt += 0.3;
			lookZAt += 0.3;
			
		}
		else if ((lookXAt >= eyeX) && (lookZAt > eyeZ)) {
            
			lookXAt += 0.3;
			lookZAt -= 0.3;
			
		}
		else if ((lookXAt > eyeX) && (lookZAt <= eyeZ)) {

			lookXAt -= 0.3;
			lookZAt -= 0.3;

		} 
	}
	else if  (key == RIGHT_C_R || key == RIGHT_C_r) {	

		if ((lookXAt >= eyeX) && (lookZAt < eyeZ)) {

			lookXAt += 0.3;
			lookZAt += 0.3;

		}
		else if ((lookXAt > eyeX) && (lookZAt >= eyeZ)) {

			lookXAt -= 0.3;
			lookZAt += 0.3;
			
		}
		else if ((lookXAt <= eyeX) && (lookZAt > eyeZ)) {

			lookXAt -= 0.3;
			lookZAt -= 0.3;
			
		}
		else if ((lookXAt < eyeX) && (lookZAt <= eyeZ)) {

			lookXAt += 0.3;
			lookZAt -= 0.3;
			
		}		
	}
	
}


void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'f': // FRONT
	    moveMeFlat(1);
		glutPostRedisplay();
		break;
	 case 'F': // FRONT
	    moveMeFlat(1);
		glutPostRedisplay();
		break;
	  case 'b': // BACK
	    moveMeFlat(-1);
		glutPostRedisplay();
		break;
	 case 'B': // BACK
		moveMeFlat(-1);
		glutPostRedisplay();
		break;
	case 'u': // UP
		lookYAt += 0.04;
		glutPostRedisplay();
		break;
	 case 'U': // UP
		lookYAt += 0.04;
		glutPostRedisplay();
		break;
	case 'd': // DOWN
		lookYAt -= 0.04;
		glutPostRedisplay();
		break;
	 case 'D': // DOWN
		lookYAt -= 0.04;
		glutPostRedisplay();
		break;
	  case 'r': // RIGHT 
	    ang +=0.05f;
	    orientMe(ang);
		//moveCamera(key);
		glutPostRedisplay();
		break;
	  case 'R': // RIGHT 
		ang +=0.05f;
		orientMe(ang);
		//moveCamera(key);
		glutPostRedisplay();
		break;
	  case 'l': // LEFT 
	    ang -= 0.05f;
		orientMe(ang);
//		moveCamera(key);
		glutPostRedisplay();
		break;
	 case 'L': // LEFT 
		ang -= 0.05f;
		orientMe(ang);
//		moveCamera(key);
		glutPostRedisplay();
		break;
	 case 'o':   //open the doors
         door_right = (door_right - 5.0);
		  if(door_right < -90.0){
			  door_right = -90.0;
		  }
		  door_left = (door_left + 5.0);
		  if(door_left > 90.0){
			  door_left = 90.0;
		  }
         glutPostRedisplay(); 
		 break;
	 case 'O':   //open the doors
          door_right = (door_right - 5.0);
		  if(door_right < -90.0){
			  door_right = -90.0;
		  }
		  door_left = (door_left + 5.0);
		  if(door_left > 90.0){
			  door_left = 90.0;
		  }
         glutPostRedisplay(); 
		 break;
	 case 'N': // RIGHT 
		 if(daylight == 1){
			 daylight = 0;
		 }
		 else if(daylight == 0){
			 daylight = 1;
		 }
		glutPostRedisplay();
		break;
	case 'n': // RIGHT
		if(daylight == 1){
			 daylight = 0;
		 }
		 else if(daylight == 0){
			 daylight = 1;
		 }
		glutPostRedisplay();
		break;
     case 27:
       exit(0);
       break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);

   //get the textures
	texture_load( texture_array );	

   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);

   glutMainLoop();

   return 0;
}
