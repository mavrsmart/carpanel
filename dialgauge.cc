/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * dialgauge.cc
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

#include <GL/gl.h>
#include <GL/glut.h>
#include "iniparser.h"
#include "dialgauge.h"
#include "objects.h"
#include "vars.h"

//#include "vars.h"
//#include "objects.h"


void dialgauge::loadconfig(char* name){
	char* st;
	char st2 [250];
	int i;
	str_cp(&st,name,":enable");
	enable=iniparser_getint(ini,st,0);
	str_cp(&st,name,":texture_temp");
	texturefile_temp=iniparser_getstring(ini,st,"");

	str_cp(&st,name,":xtemp");
	xtemp=iniparser_getint(ini,st,0);
	str_cp(&st,name,":ytemp");
	ytemp=iniparser_getint(ini,st,0);
	str_cp(&st,name,":lenxtemp");
	lenxtemp=iniparser_getint(ini,st,0);
	str_cp(&st,name,":lenytemp");
	lenytemp=iniparser_getint(ini,st,0);
	
	str_cp(&st,name,":div_centr_arrow");
	div_centr_arrow=iniparser_getdouble(ini,st,6);
	str_cp(&st,name,":texture_arrow");
	texturefile_arrow=iniparser_getstring(ini,st,"");
	str_cp(&st,name,":xarrow");
	xarrow=iniparser_getint(ini,st,0);
	str_cp(&st,name,":yarrow");
	yarrow=iniparser_getint(ini,st,0);
	str_cp(&st,name,":lenxarrow");
	lenxarrow=iniparser_getint(ini,st,0);
	str_cp(&st,name,":lenyarrow");
	lenyarrow=iniparser_getint(ini,st,0);

	str_cp(&st,name,":triangle");
	triangle=iniparser_getint(ini,st,1);

	str_cp(&st,name,":speed");
	speed=iniparser_getdouble(ini,st,0);
	
	str_cp(&st,name,":startangle");
	startangle=iniparser_getdouble(ini,st,0);

	str_cp(&st,name,":minporog");
	minporog=iniparser_getdouble(ini,st,0);
	
	str_cp(&st,name,":maxporog");
	maxporog=iniparser_getdouble(ini,st,0);

	for(i=0;i<koeflenght;i++){
	sprintf(st2,":porog_%d",i);
	str_cp(&st,name,st2);
	porog[i]=iniparser_getdouble(ini,st,-100000);
	if(porog[i]!=-100000){nummaxporog=i;}

	sprintf(st2,":koef_%d",i);
	str_cp(&st,name,st2);
	koef[i]=iniparser_getdouble(ini,st,-100000);
		
	sprintf(st2,":defangle_%d",i);
	str_cp(&st,name,st2);
	defangle[i]=iniparser_getdouble(ini,st,-100000);
		
//	printf("%s\n",st);	
	}
	
	texture_arrow=loadTexture(texturefile_arrow);
	texture_temp=loadTexture(texturefile_temp);

	oldangle=startangle;
}; 

void dialgauge::drawstrela(GLuint texture,int x,int y,int xlen,int ylen,float angle,int triangle){
	int x1,y1;
   x1=x+xlen;
   y1=y+ylen;	
   glPushMatrix();
   glTranslated(x+((x1-x)/div_centr_arrow),y+((y1-y)/2),0);
   glRotatef(angle,0,0,1);
   glTranslated(-1*(x+((x1-x)/div_centr_arrow)),-1*(y+((y1-y)/2)),0);
   if(triangle==1){
   drawtriangle(0,x-2,y-0.5,x1+15,y1+2);
   drawtriangle(texture,x,y,x1,y1);
   }else{
	   drawquad(texture,x,y,x1,y1);
   }
   glPopMatrix();
}

void dialgauge::draw(float value){
	float valueangl=0;
	float korrektir=0;
	float korrektirvalue=0;
	int i;
	float values;

	if(enable==1){

	values=value;	

	if(values<=minporog){values=0;}else{values=values-minporog;}
	if(values>maxporog-minporog){values=maxporog-minporog;}
		
	
	for(i=0;i<=nummaxporog;i++){
	if(values<=porog[i]){
    	korrektirvalue=(values/koef[i]);
		korrektir=defangle[i];
	}
	}



	if(values>=porog[nummaxporog]){
		values=porog[nummaxporog];
    	korrektirvalue=(values/koef[nummaxporog]);
		korrektir=defangle[nummaxporog];
	}


	valueangl=korrektir-korrektirvalue;
	if(valueangl<oldangle-speed){valueangl=oldangle-speed;}
	if(valueangl>oldangle+speed){valueangl=oldangle+speed;}
	oldangle=valueangl;
	//printf("Value %f\n",speed);

	drawdashboard(texture_temp,xtemp,ytemp,xtemp+lenxtemp,ytemp+lenytemp);
	drawstrela(texture_arrow,xtemp+xarrow,ytemp+yarrow,lenxarrow,lenyarrow,valueangl,triangle);//Рисуем стрелу
	}


}


