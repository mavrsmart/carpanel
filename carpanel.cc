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
#include "nets.h"
#include <pthread.h>

using namespace std;


 #define TEXTURE_LOAD_ERROR 0


float i=0;
float i2=0;
float i3=0;

int64_t timertick=0;

dialgauge* dgp; 
znak* znp; 

void display()
        {
			int w;

				//Очистка экрана
                glClear(GL_COLOR_BUFFER_BIT);
				glLoadIdentity();                                       // Сброс просмотра
			//Отрисовка панели

    	drawdashboard(dashboard,sets.dashboardtemp_x,sets.dashboardtemp_y,sets.dashboardtemp_x1,sets.dashboardtemp_y1);

			
glPushMatrix();

        for(w=0;w<127;w++){
			if(objects[w].enable==1){
				if(objects[w].type==0){
					//Рисуем класс dialgauge
					objects[w].dgp->draw(variables[w]);
				}
				if(objects[w].type==1){
					//Рисуем класс znak
					objects[w].znp->setactive(variables[w]);
					objects[w].znp->draw();
				}
			}
		}

			
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
			
			glutPostRedisplay();
        }



int main(int argc, char * argv[])
{
	int w,h;
	
	pthread_t thread_sock;
    int  iret_sock;
	
	   for(w=0;w<128;w++){variables[w]=0;}
	   for(w=0;w<128;w++){objects[w].enable=0;}
       readini();

	//socket thread

	iret_sock =pthread_create( &thread_sock,NULL,startsocket, &iret_sock);
	     if(iret_sock)
	     {
	         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret_sock);
	         exit(EXIT_FAILURE);
	     }
	
	///socket thread
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

        for(w=0;w<127;w++){
			if(objects[w].enable==1){
				if(objects[w].type==0){
					//Создаем класс dialgauge
					objects[w].dgp=new dialgauge;
					objects[w].dgp->loadconfig(objects[w].name);
				}
				if(objects[w].type==1){
					//Создаем класс znak
					objects[w].znp=new znak;
					objects[w].znp->loadconfig(objects[w].name);
				}
			}
		}


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

