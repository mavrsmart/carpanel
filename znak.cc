/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * znak.cc
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

#include "znak.h"
#include "iniparser.h"
#include "vars.h"
#include "objects.h"
#include <GL/gl.h>
#include <GL/glut.h>



void znak::setactive(int tru){
	enable=tru;
	if((enable==0)&&(cor<=0)){cor=0;cor_cur=0;}
	if(enable==1){
		if(cor_cur==0){
			cor=cor+koef;
			if(cor>=active_size){cor_cur=1;}
		}else{
			cor=cor-koef;
			if(cor<=0){cor_cur=0;}
		}
	}else{
			cor=cor-koef;
			if(cor<=0){cor_cur=0;}
		}
	
}



void znak::loadconfig(char* zn_name){
	char* st;
	str_cp(&st,zn_name,":enable");
	enable=iniparser_getint(ini,st,0);
	str_cp(&st,zn_name,":texture");
	texturefile=iniparser_getstring(ini,st,"");
	str_cp(&st,zn_name,":x");
	x=iniparser_getint(ini,st,0);
	str_cp(&st,zn_name,":y");
	y=iniparser_getint(ini,st,0);
	str_cp(&st,zn_name,":lenx");
	lenx=iniparser_getint(ini,st,0);
	str_cp(&st,zn_name,":leny");
	leny=iniparser_getint(ini,st,0);

	str_cp(&st,zn_name,":active_size");
	active_size=iniparser_getint(ini,st,0);

	str_cp(&st,zn_name,":koef");
	koef=iniparser_getint(ini,st,0);
	
	texture=loadTexture(texturefile);
	cor=0;
	cor_cur=0;
}; 

void znak::draw(){
	if(enable==0){
		glColor3f(0.2,0.2,0.2);
	}
		drawzn(texture,x-cor/2,y-cor/2,lenx+cor,leny+cor,active);
		glColor3f(1,1,1);
}
