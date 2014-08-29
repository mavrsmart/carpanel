// objects.c
//
// Copyright (C) 2014 mavrsmart <mavr@smarts.zp.ua>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//           objects.c
//  Чт Август 21 23:36:30 2014
//  Copyright  2014  user
//  <user@host>

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "FreeImage.h"
  
#include <math.h>
#include <assert.h>

#include <zlib.h>
#include <unistd.h>
#include "setings.h"
#include "vars.h"
#include "objects.h"

using namespace std;

void* imgPixels;  
int imgWidth;   // Width of the texture image.
int imgHeight;  // Height of the texture image.

void* dashPixels;  // Pointer to raw RGB data for texture.
int dashWidth;   // Width of the texture image.
int dashHeight;  // Height of the texture image.


GLuint loadTexture( char* fileName ) {
        // Loads a texture image using the FreeImage library, and stores
        // the required info in global variables imgPixels, imgWidth, imgHeight.
        // The parameter fileName is a string that contains the name of the
        // image file from which the image is to be loaded.  If the
        // image can't be loaded, then imgPixels will be set to be a null pointer.
        
    imgPixels = 0; // Null pointer to signal that data has not been read.
    
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(fileName);
         // FREE_IMAGE_FORMAT is a type defined by the FreeImage library.
         // Here, the format is determined from the file extension in
         // the file name, such as .png, .jpg, or .gif.  Many formats
         // are supported.
    
    if (format == FIF_UNKNOWN) {
        printf("Unknown file type for texture image file %s\n", fileName);
        return 0;
    }
    
    FIBITMAP* bitmap = FreeImage_Load(format, fileName, 0);
          // FIBITMAP is a type defined by the FreeImage library, representing
          // the raw image data plus some metadata such as width, height,
          // and the format of the image data.  This actually tries to
          // read the data from the specified file.
          
    if (!bitmap) {
        printf("Failed to load image %s\n", fileName);
        return 0;
    }
    
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);
          // This creates a copy of the image, with the data represented
          // in standard RGB (or BGR) format, for use with OpenGL.
    
    FreeImage_Unload(bitmap);
          // After finishing with a bitmap, it should be disposed.
          // We are finished with bitmap, but not with bitmap2, since
          // we will continue to use the data from bitmap2.
          
    imgPixels = FreeImage_GetBits(bitmap2);  // Get the data we need!
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);
    
    if (imgPixels) {
        printf("Texture image loaded from file %s, size %dx%d\n", 
                         fileName, imgWidth, imgHeight);
    }
    else {
        printf("Failed to get texture data from %s\n", fileName);
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, imgPixels);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return texture;
	
} // end loadTexture


void drawquad(GLuint texture,int x,int y,int x1,int y1){
glBindTexture(GL_TEXTURE_2D, texture);
glBegin(GL_QUADS);
        glTexCoord2f( 0, 1);
        glVertex2i(x, y1);
        glTexCoord2i( 0, 0);
        glVertex2i(x, y);
        glTexCoord2i( 1, 0);
        glVertex2i(x1, y);
        glTexCoord2i( 1, 1);
        glVertex2i(x1, y1);
        glEnd();
}

void drawtriangle(GLuint texture,int x,int y,int x1,int y1){
glBindTexture(GL_TEXTURE_2D, texture);
glBegin(GL_TRIANGLES);
        glTexCoord2f( 0, 1);
        glVertex2i(x, y1);
        glTexCoord2i( 0, 0);
        glVertex2i(x, y);
        glTexCoord2i( 1, 0);
        glVertex2i(x1, y);
        glTexCoord2i( 0, 1);
        glVertex2i(x, y1);
        glEnd();
}

void drawdashboard(GLuint texture,int x,int y,int x1,int y1){
if(sets.dashboardenable==1){
	
   glPushMatrix();
glTranslated(0,250,0);


			
drawquad(texture,x,y,x1,y1);
glPopMatrix();
}
}	

void drawstrela(GLuint texture,int x,int y,int xlen,int ylen,float angle,int triangle){
	int x1,y1;
   x1=x+xlen;
   y1=y+ylen;	
   glPushMatrix();
   glTranslated(x+((x1-x)/sets.div_centr_strela),y+((y1-y)/2),0);
   glRotatef(angle,0,0,1);
   glTranslated(-1*(x+((x1-x)/sets.div_centr_strela)),-1*(y+((y1-y)/2)),0);
   if(triangle==1){
   drawtriangle(texture,x,y,x1,y1);
   }else{
	   drawquad(texture,x,y,x1,y1);
   }
   glPopMatrix();
}

void drawspeedometr(float speed){
	float speedangl=0;
	float korrektir=0;
	float korrektirspeed=0;

    if (sets.speedometr_enable==1){
	if(speed<=10){
    	korrektirspeed=(speed/sets.speedometr_koef10);
		korrektir=sets.speedometr_defangle10;
	}else
	if(speed<=20){
    	korrektirspeed=(speed/sets.speedometr_koef20);
		korrektir=sets.speedometr_defangle20;
	}else
	if(speed<=30){
    	korrektirspeed=(speed/sets.speedometr_koef30);
		korrektir=sets.speedometr_defangle30;
	}else
	if(speed<=40){
    	korrektirspeed=(speed/sets.speedometr_koef40);
		korrektir=sets.speedometr_defangle40;
	}else
	if(speed<=50){
    	korrektirspeed=(speed/sets.speedometr_koef50);
		korrektir=sets.speedometr_defangle50;
	}else
	if(speed<=60){
    	korrektirspeed=(speed/sets.speedometr_koef60);
		korrektir=sets.speedometr_defangle60;
	}else
	if(speed<=70){
    	korrektirspeed=(speed/sets.speedometr_koef70);
		korrektir=sets.speedometr_defangle70;
	}else
	if(speed<=80){
    	korrektirspeed=(speed/sets.speedometr_koef80);
		korrektir=sets.speedometr_defangle80;
	}else
	if(speed<=90){
    	korrektirspeed=(speed/sets.speedometr_koef90);
		korrektir=sets.speedometr_defangle90;
	}else
	if(speed<=100){
    	korrektirspeed=(speed/sets.speedometr_koef100);
		korrektir=sets.speedometr_defangle100;
	}else
	if(speed<=110){
    	korrektirspeed=(speed/sets.speedometr_koef110);
		korrektir=sets.speedometr_defangle110;
	}else
	if(speed<=120){
    	korrektirspeed=(speed/sets.speedometr_koef120);
		korrektir=sets.speedometr_defangle120;
	}else
	if(speed<=130){
    	korrektirspeed=(speed/sets.speedometr_koef130);
		korrektir=sets.speedometr_defangle130;
	}else
	if(speed<=140){
    	korrektirspeed=(speed/sets.speedometr_koef140);
		korrektir=sets.speedometr_defangle140;
	}else
	if(speed<=150){
    	korrektirspeed=(speed/sets.speedometr_koef150);
		korrektir=sets.speedometr_defangle150;
	}else
	if(speed<=160){
    	korrektirspeed=(speed/sets.speedometr_koef160);
		korrektir=sets.speedometr_defangle160;
	}else
	if(speed<=170){
    	korrektirspeed=(speed/sets.speedometr_koef170);
		korrektir=sets.speedometr_defangle170;
	}else
	if(speed<=180){
    	korrektirspeed=(speed/sets.speedometr_koef180);
		korrektir=sets.speedometr_defangle180;
	}else
	if(speed<=190){
    	korrektirspeed=(speed/sets.speedometr_koef190);
		korrektir=sets.speedometr_defangle190;
	}else
	if(speed<=200){
    	korrektirspeed=(speed/sets.speedometr_koef200);
		korrektir=sets.speedometr_defangle200;
	}else{
		if(speed>=210){speed=210;};
    	korrektirspeed=(speed/sets.speedometr_koef200);
		korrektir=sets.speedometr_defangle200;
	}

	
	speedangl=korrektir-korrektirspeed;
	if(speedangl<oldanglespeedometr-sets.speedometr_speed){speedangl=oldanglespeedometr-sets.speedometr_speed;}
	if(speedangl>oldanglespeedometr+sets.speedometr_speed){speedangl=oldanglespeedometr+sets.speedometr_speed;}
	oldanglespeedometr=speedangl;

	drawstrela(textspeed,sets.speedometr_x,sets.speedometr_y,sets.speedometr_lenx,sets.speedometr_leny,speedangl,sets.speedometr_triangle);//Скорость
	}
}


void drawtahometr(float speed){
	float speedangl=0;
	float korrektir=0;
	float korrektirspeed=0;

	if(speed<=500){
    	korrektirspeed=(speed/sets.tahometr_koef500);
		korrektir=sets.tahometr_defangle500;
	}else
	if(speed<=1000){
    	korrektirspeed=(speed/sets.tahometr_koef1000);
		korrektir=sets.tahometr_defangle1000;
	}else
	if(speed<=1500){
    	korrektirspeed=(speed/sets.tahometr_koef1500);
		korrektir=sets.tahometr_defangle1500;
	}else
	if(speed<=2000){
    	korrektirspeed=(speed/sets.tahometr_koef2000);
		korrektir=sets.tahometr_defangle2000;
	}else
	if(speed<=2500){
    	korrektirspeed=(speed/sets.tahometr_koef2500);
		korrektir=sets.tahometr_defangle2500;
	}else
	if(speed<=3000){
    	korrektirspeed=(speed/sets.tahometr_koef3000);
		korrektir=sets.tahometr_defangle3000;
	}else
	if(speed<=3500){
    	korrektirspeed=(speed/sets.tahometr_koef3500);
		korrektir=sets.tahometr_defangle3500;
	}else
	if(speed<=4000){
    	korrektirspeed=(speed/sets.tahometr_koef4000);
		korrektir=sets.tahometr_defangle4000;
	}else
	if(speed<=4500){
    	korrektirspeed=(speed/sets.tahometr_koef4500);
		korrektir=sets.tahometr_defangle4500;
	}else
	if(speed<=5000){
    	korrektirspeed=(speed/sets.tahometr_koef5000);
		korrektir=sets.tahometr_defangle5000;
	}else
	if(speed<=5500){
    	korrektirspeed=(speed/sets.tahometr_koef5500);
		korrektir=sets.tahometr_defangle5500;
	}else
	if(speed<=6000){
    	korrektirspeed=(speed/sets.tahometr_koef6000);
		korrektir=sets.tahometr_defangle6000;
	}else
	if(speed<=6500){
    	korrektirspeed=(speed/sets.tahometr_koef6500);
		korrektir=sets.tahometr_defangle6500;
	}else
	if(speed<=7000){
    	korrektirspeed=(speed/sets.tahometr_koef7000);
		korrektir=sets.tahometr_defangle7000;
	}else
	if(speed<=7500){
    	korrektirspeed=(speed/sets.tahometr_koef7500);
		korrektir=sets.tahometr_defangle7500;
	}else
	if(speed<=8000){
    	korrektirspeed=(speed/sets.tahometr_koef8000);
		korrektir=sets.tahometr_defangle8000;
	}else{
		if(speed>=8100){speed=8100;};
    	korrektirspeed=(speed/sets.tahometr_koef8000);
		korrektir=sets.tahometr_defangle8000;
	}

	
	speedangl=korrektir-korrektirspeed;
	if(speedangl<oldangletahometr-sets.tahometr_speed){speedangl=oldangletahometr-sets.tahometr_speed;}
	if(speedangl>oldangletahometr+sets.tahometr_speed){speedangl=oldangletahometr+sets.tahometr_speed;}
	oldangletahometr=speedangl;

    drawstrela(texttahometr,sets.tahometr_x,sets.tahometr_y,sets.tahometr_lenx,sets.tahometr_leny,speedangl,sets.tahometr_triangle);//Тахометр
}

void drawfuel(float speed){
	float speedangl=0;
	float korrektir=0;
	float korrektirspeed=0;

	korrektirspeed=(speed/sets.fuel_koef);
    korrektir=sets.fuel_defangle;

	speedangl=korrektir-korrektirspeed;
	if(speedangl<oldanglefuel-sets.fuel_speed){speedangl=oldanglefuel-sets.fuel_speed;}
	if(speedangl>oldanglefuel+sets.fuel_speed){speedangl=oldanglefuel+sets.fuel_speed;}
	oldanglefuel=speedangl;

    drawstrela(textfuel,sets.fuel_x,sets.fuel_y,sets.fuel_lenx,sets.fuel_leny,speedangl,sets.fuel_triangle);//Топливомер
}

void drawtemp(float speed){
	float speedangl=0;
	float korrektir=0;
	float korrektirspeed=0;
	if(speed<=45){speed=0;}else{speed=speed-45;}
	if(speed>105-45){speed=105-45;}
	korrektirspeed=((speed)/sets.temp_koef);
    korrektir=sets.temp_defangle;

	speedangl=korrektir-korrektirspeed;
	if(speedangl<oldangletemp-sets.temp_speed){speedangl=oldangletemp-sets.temp_speed;}
	if(speedangl>oldangletemp+sets.temp_speed){speedangl=oldangletemp+sets.temp_speed;}
	oldangletemp=speedangl;
	
    drawstrela(texttemp,sets.temp_x,sets.temp_y,sets.temp_lenx,sets.temp_leny,speedangl,sets.temp_triangle);//Температура 
}

void drawzn(GLuint texture,int x,int y,int lenx,int leny,int active){
    //drawquad(texture,x,y,lenx,leny);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 1);
        	glVertex2i(x, y+leny);
        	glTexCoord2i( 0, 0);
        	glVertex2i(x, y);
        	glTexCoord2i( 1, 0);
        	glVertex2i(x+lenx, y);
        	glTexCoord2i( 1, 1);
        	glVertex2i(x+lenx, y+leny);
        glEnd();
}

