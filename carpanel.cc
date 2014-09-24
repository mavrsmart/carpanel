/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2014 mavrsmart <mavr@smarts.zp.ua>
 * 
 * carpanel is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * carpanel is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
#include "znak.h"
#include "dialgauge.h"

using namespace std;


 #define TEXTURE_LOAD_ERROR 0


float i=0;
float i2=0;
float i3=0;

int64_t timertick=0;


void display()
        {
			//Очистка экрана
                glClear(GL_COLOR_BUFFER_BIT);
				glLoadIdentity();                                       // Сброс просмотра
			//Отрисовка панели

    	drawdashboard(dashboard,sets.dashboardtemp_x,sets.dashboardtemp_y,sets.dashboardtemp_x1,sets.dashboardtemp_y1);

			
glPushMatrix();
			
//Эмуляция значений в деморежиме
if (sets.testmode==1){
	if(i<=70){speed=0;}else{speed=180;}

	if(i2<=4000){tahometr=0;maslo=1;}else{tahometr=6000;maslo=0;}
	fuel=i3;
	temp=i3;
}

//Отображение знаков по порогам
if(temp>90){zn_peregrev.setactive(1);} else {zn_peregrev.setactive(0);};
if(fuel<5){zn_fuel.setactive(1);} else {zn_fuel.setactive(0);};

//Активация знаков по значениям
zn_dalnsvet.setactive(dalnsvet);
zn_imobilizer.setactive(imobilizer);
zn_maslo.setactive(maslo);
zn_opendoor.setactive(opendoor);
zn_povorlevo.setactive(povorlevo);
zn_povorpravo.setactive(povorpravo);
zn_power.setactive(power);
zn_protivotuman.setactive(protivotuman);
zn_torm.setactive(torm);


//Отображение знаков			
zn_fuel.draw();
zn_dalnsvet.draw();
zn_imobilizer.draw();
zn_maslo.draw();
zn_opendoor.draw();
zn_peregrev.draw();
zn_povorlevo.draw();
zn_povorpravo.draw();
zn_power.draw();
zn_protivotuman.draw();
zn_torm.draw();

//Отображение стрелок
dg_speed.draw(speed);
dg_tahometr.draw(tahometr);
dg_fuel.draw(fuel);
dg_temp.draw(temp);
//drawspeedometr(speed);			
//drawtahometr(tahometr);
//drawfuel(fuel);
//drawtemp(temp);

glPopMatrix();

glutSwapBuffers();
		}


        void reshape(int w, int h)
        {
                glViewport(0, 0, w, h);
               
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluOrtho2D(0, w, 0, h);
               
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
        }

        void idle()
        {

			usleep(sets.sleepu);//1ms
			timertick++;
			if (sets.testmode==1){
			if(timertick==1){
				//Для демо режима
				if(i>=220){i=0;}else{i=i+0.1;}
				if(i2>=8000){i2=0;}else{i2=i2+1;}
				if(i3>=100){i3=0;}else{i3=i3+0.01;}
				timertick=0;
			}
			}


				//Для настройки
				if (sets.testmode==2){
				if(timertick==sets.timerticks){
					speed=speed+10;
					if(speed==220){speed=0;}
					tahometr=tahometr+500;
					if(tahometr==8500){tahometr=0;}
					fuel=fuel+25;
					if(fuel==125){fuel=0;}
					temp=temp+10;
					if(temp==120){temp=0;}
				timertick=0;
				}
				}


			
			glutPostRedisplay();
        }



int main(int argc, char * argv[])
{
	int w,h;
       readini();	
       glutInit(&argc, argv);
        //glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); /*Включаем двойную буферизацию*/
  		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(sets.xres, sets.yres);
        glutCreateWindow("CarPanel");

//		glDisable(GL_VSYNC);
	
		glEnable(GL_TEXTURE_2D);
        dashboard=loadTexture(sets.dashboardtexture);
		dashPixels=imgPixels;
		dashWidth=imgWidth;
		dashHeight=imgHeight;

		dg_speed.loadconfig("speedometr");
		dg_tahometr.loadconfig("tahometr");
		dg_fuel.loadconfig("fuel");
		dg_temp.loadconfig("temp");
	
		zn_power.loadconfig("zn_power");
		zn_fuel.loadconfig("zn_fuel");
		zn_dalnsvet.loadconfig("zn_dalnsvet");
		zn_imobilizer.loadconfig("zn_imobilizer");
		zn_maslo.loadconfig("zn_maslo");
		zn_opendoor.loadconfig("zn_opendoor");
		zn_peregrev.loadconfig("zn_peregrev");
		zn_povorlevo.loadconfig("zn_povorlevo");
		zn_povorpravo.loadconfig("zn_povorpravo");
		zn_power.loadconfig("zn_power");
		zn_protivotuman.loadconfig("zn_protivotuman");
		zn_torm.loadconfig("zn_torm");


		glEnable(GL_BLEND); //Прозрачность
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    	glShadeModel(GL_SMOOTH); 
    
    	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST); 
    	glEnable(GL_POLYGON_SMOOTH);
 
    	glDisable( GL_DEPTH_TEST ); 
    	glEnable( GL_ALPHA_TEST );

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		// Сглаживание точек
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		// Сглаживание линий
		glEnable(GL_LINE_SMOOTH);               
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		// Сглаживание полигонов    
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	  glClearDepth( 1.0f );              // Разрешить очистку буфера глубины
   // glEnable( GL_DEPTH_TEST );            // Разрешить тест глубины
 //  glDepthFunc( GL_LEQUAL );            // Тип теста глубины
	

  glEnable(GL_LIGHT0); 
                         
  glEnable(GL_LIGHTING); 
  glEnable(GL_COLOR_MATERIAL);  
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
          


	
        glutReshapeFunc(reshape);

        glutIdleFunc(idle);
		glutDisplayFunc(display);
       
        glutMainLoop();
 
        return 0;
}

