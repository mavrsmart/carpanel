// setings.h
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
//           setings.h
//  Чт Август 21 21:55:09 2014
//  Copyright  2014  user
//  <user@host>

#ifndef _SETINGS_H_
#define _SETINGS_H_

#include "iniparser.h"


using namespace std;

extern struct
{
	int sleepu;
	int timerticks;

	int testmode;
    int xres;
    int yres;
	float div_centr_strela;
    int dashboardenable;
	char* dashboardtexture;
    int dashboardtemp_x;
    int dashboardtemp_y;
    int dashboardtemp_x1;
    int dashboardtemp_y1;
	int speedometr_enable;
	char* speedometrtexture;
	int speedometr_x;
	int speedometr_y;
	int speedometr_lenx;
	int speedometr_leny;
	int speedometr_triangle;
	float speedometr_speed;
	float speedometr_startangle;
	float speedometr_defangle10;
	float speedometr_koef10;
	float speedometr_defangle20;
	float speedometr_koef20;
	float speedometr_defangle30;
	float speedometr_koef30;
	float speedometr_defangle40;
	float speedometr_koef40;
	float speedometr_defangle50;
	float speedometr_koef50;
	float speedometr_defangle60;
	float speedometr_koef60;
	float speedometr_defangle70;
	float speedometr_koef70;
	float speedometr_defangle80;
	float speedometr_koef80;
	float speedometr_defangle90;
	float speedometr_koef90;
	float speedometr_defangle100;
	float speedometr_koef100;
	float speedometr_defangle110;
	float speedometr_koef110;
	float speedometr_defangle120;
	float speedometr_koef120;
	float speedometr_defangle130;
	float speedometr_koef130;
	float speedometr_defangle140;
	float speedometr_koef140;
	float speedometr_defangle150;
	float speedometr_koef150;
	float speedometr_defangle160;
	float speedometr_koef160;
	float speedometr_defangle170;
	float speedometr_koef170;
	float speedometr_defangle180;
	float speedometr_koef180;
	float speedometr_defangle190;
	float speedometr_koef190;
	float speedometr_defangle200;
	float speedometr_koef200;

	int tahometr_enable;
	char* tahometrtexture;
	int tahometr_x;
	int tahometr_y;
	int tahometr_lenx;
	int tahometr_leny;
	int tahometr_triangle;
	float tahometr_speed;
	float tahometr_startangle;
	float tahometr_defangle500;
	float tahometr_koef500;
	float tahometr_defangle1000;
	float tahometr_koef1000;
	float tahometr_defangle1500;
	float tahometr_koef1500;
	float tahometr_defangle2000;
	float tahometr_koef2000;
	float tahometr_defangle2500;
	float tahometr_koef2500;
	float tahometr_defangle3000;
	float tahometr_koef3000;
	float tahometr_defangle3500;
	float tahometr_koef3500;
	float tahometr_defangle4000;
	float tahometr_koef4000;
	float tahometr_defangle4500;
	float tahometr_koef4500;
	float tahometr_defangle5000;
	float tahometr_koef5000;
	float tahometr_defangle5500;
	float tahometr_koef5500;
	float tahometr_defangle6000;
	float tahometr_koef6000;
	float tahometr_defangle6500;
	float tahometr_koef6500;
	float tahometr_defangle7000;
	float tahometr_koef7000;
	float tahometr_defangle7500;
	float tahometr_koef7500;
	float tahometr_defangle8000;
	float tahometr_koef8000;


	int fuel_enable;
	char* fueltexture;
	int fuel_x;
	int fuel_y;
	int fuel_lenx;
	int fuel_leny;
	int fuel_triangle;
	float fuel_speed;
	float fuel_startangle;
	float fuel_defangle;
	float fuel_koef;
	
	int temp_enable;
	char* temptexture;
	int temp_x;
	int temp_y;
	int temp_lenx;
	int temp_leny;
	int temp_triangle;
	float temp_speed;
	float temp_startangle;
	float temp_defangle;
	float temp_koef;

	
} sets;

extern	dictionary* ini;


void readini();

#endif // _SETINGS_H_
