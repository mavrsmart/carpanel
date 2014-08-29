// setings.c
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
//           setings.c
//  Чт Август 21 21:55:09 2014
//  Copyright  2014  user
//  <user@host>


#include "iniparser.h"
#include "vars.h"

using namespace std;




struct sets
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


void readini(){
	ini=iniparser_load("carpanel.ini");
	sets.sleepu=iniparser_getint(ini,"system:sleepu",1000);
	sets.timerticks=iniparser_getint(ini,"system:timerticks",1000);
	
	sets.testmode=iniparser_getint(ini,"system:testmode",0);
	sets.xres=iniparser_getint(ini,"system:xres",1280);
	sets.yres=iniparser_getint(ini,"system:yres",800);
	sets.div_centr_strela=iniparser_getdouble(ini,"system:div_centr_strela",6);
	sets.dashboardenable=iniparser_getint(ini,"dashboard:enable",1);
	sets.dashboardtexture=iniparser_getstring(ini,"dashboard:texture","textures/dashboard.png");
	sets.dashboardtemp_x=iniparser_getint(ini,"dashboard:temp_x",0);
	sets.dashboardtemp_y=iniparser_getint(ini,"dashboard:temp_y",0);
	sets.dashboardtemp_x1=iniparser_getint(ini,"dashboard:temp_x1",1280);
	sets.dashboardtemp_y1=iniparser_getint(ini,"dashboard:temp_y1",600);

	sets.speedometr_enable=iniparser_getint(ini,"speedometr:enable",1);
	sets.speedometrtexture=iniparser_getstring(ini,"speedometr:texture","textures/deftexture.png");
	sets.speedometr_x=iniparser_getint(ini,"speedometr:x",620);
	sets.speedometr_y=iniparser_getint(ini,"speedometr:y",510);
	sets.speedometr_lenx=iniparser_getint(ini,"speedometr:lenx",300);
	sets.speedometr_leny=iniparser_getint(ini,"speedometr:leny",20);
	sets.speedometr_triangle=iniparser_getint(ini,"speedometr:triangle",1);
	sets.speedometr_speed=iniparser_getdouble(ini,"speedometr:speed",0.3);
	sets.speedometr_startangle=iniparser_getdouble(ini,"speedometr:startangle",-145);
	sets.speedometr_koef10=iniparser_getdouble(ini,"speedometr:koef10",2);
	sets.speedometr_defangle10=iniparser_getdouble(ini,"speedometr:defangle10",-146);
	sets.speedometr_koef20=iniparser_getdouble(ini,"speedometr:koef20",2);
	sets.speedometr_defangle20=iniparser_getdouble(ini,"speedometr:defangle20",-147);
	sets.speedometr_koef30=iniparser_getdouble(ini,"speedometr:koef30",1.25);
	sets.speedometr_defangle30=iniparser_getdouble(ini,"speedometr:defangle30",-145);
	sets.speedometr_koef40=iniparser_getdouble(ini,"speedometr:koef40",1.05);
	sets.speedometr_defangle40=iniparser_getdouble(ini,"speedometr:defangle40",-145);
	sets.speedometr_koef50=iniparser_getdouble(ini,"speedometr:koef50",0.97);
	sets.speedometr_defangle50=iniparser_getdouble(ini,"speedometr:defangle50",-145);
	sets.speedometr_koef60=iniparser_getdouble(ini,"speedometr:koef60",0.925);
	sets.speedometr_defangle60=iniparser_getdouble(ini,"speedometr:defangle60",-145);
	sets.speedometr_koef70=iniparser_getdouble(ini,"speedometr:koef70",0.905);
	sets.speedometr_defangle70=iniparser_getdouble(ini,"speedometr:defangle70",-145);
	sets.speedometr_koef80=iniparser_getdouble(ini,"speedometr:koef80",0.890);
	sets.speedometr_defangle80=iniparser_getdouble(ini,"speedometr:defangle80",-145);
	sets.speedometr_koef90=iniparser_getdouble(ini,"speedometr:koef90",0.883);
	sets.speedometr_defangle90=iniparser_getdouble(ini,"speedometr:defangle90",-145);
	sets.speedometr_koef100=iniparser_getdouble(ini,"speedometr:koef100",0.880);
	sets.speedometr_defangle100=iniparser_getdouble(ini,"speedometr:defangle100",-145);
	sets.speedometr_koef110=iniparser_getdouble(ini,"speedometr:koef110",0.878);
	sets.speedometr_defangle110=iniparser_getdouble(ini,"speedometr:defangle110",-145);
	sets.speedometr_koef120=iniparser_getdouble(ini,"speedometr:koef120",0.875);
	sets.speedometr_defangle120=iniparser_getdouble(ini,"speedometr:defangle120",-145);
	sets.speedometr_koef130=iniparser_getdouble(ini,"speedometr:koef130",0.872);
	sets.speedometr_defangle130=iniparser_getdouble(ini,"speedometr:defangle130",-145);
	sets.speedometr_koef140=iniparser_getdouble(ini,"speedometr:koef140",0.865);
	sets.speedometr_defangle140=iniparser_getdouble(ini,"speedometr:defangle140",-145);
	sets.speedometr_koef150=iniparser_getdouble(ini,"speedometr:koef150",0.858);
	sets.speedometr_defangle150=iniparser_getdouble(ini,"speedometr:defangle150",-145);
	sets.speedometr_koef160=iniparser_getdouble(ini,"speedometr:koef160",0.85);
	sets.speedometr_defangle160=iniparser_getdouble(ini,"speedometr:defangle160",-145);
	sets.speedometr_koef170=iniparser_getdouble(ini,"speedometr:koef170",0.841);
	sets.speedometr_defangle170=iniparser_getdouble(ini,"speedometr:defangle170",-145);
	sets.speedometr_koef180=iniparser_getdouble(ini,"speedometr:koef180",0.832);
	sets.speedometr_defangle180=iniparser_getdouble(ini,"speedometr:defangle180",-145);
	sets.speedometr_koef190=iniparser_getdouble(ini,"speedometr:koef190",0.826);
	sets.speedometr_defangle190=iniparser_getdouble(ini,"speedometr:defangle190",-145);
	sets.speedometr_koef200=iniparser_getdouble(ini,"speedometr:koef200",0.822);
	sets.speedometr_defangle200=iniparser_getdouble(ini,"speedometr:defangle200",-145);

	sets.tahometr_enable=iniparser_getint(ini,"tahometr:enable",1);
	sets.tahometrtexture=iniparser_getstring(ini,"tahometr:texture","textures/deftexture.png");
	sets.tahometr_x=iniparser_getint(ini,"tahometr:x",240);
	sets.tahometr_y=iniparser_getint(ini,"tahometr:y",470);
	sets.tahometr_lenx=iniparser_getint(ini,"tahometr:lenx",280);
	sets.tahometr_leny=iniparser_getint(ini,"tahometr:leny",20);
	sets.tahometr_triangle=iniparser_getint(ini,"tahometr:triangle",1);
	sets.tahometr_speed=iniparser_getdouble(ini,"tahometr:speed",1);
	sets.tahometr_startangle=iniparser_getdouble(ini,"tahometr:startangle",-145);
	sets.tahometr_koef500=iniparser_getdouble(ini,"tahometr:koef500",125);
	sets.tahometr_defangle500=iniparser_getdouble(ini,"tahometr:defangle500",-149.5);
	sets.tahometr_koef1000=iniparser_getdouble(ini,"tahometr:koef1000",75);
	sets.tahometr_defangle1000=iniparser_getdouble(ini,"tahometr:defangle1000",-149.5);
	sets.tahometr_koef1500=iniparser_getdouble(ini,"tahometr:koef1500",66);
	sets.tahometr_defangle1500=iniparser_getdouble(ini,"tahometr:defangle1500",-149.5);
	sets.tahometr_koef2000=iniparser_getdouble(ini,"tahometr:koef2000",59);
	sets.tahometr_defangle2000=iniparser_getdouble(ini,"tahometr:defangle2000",-148);
	sets.tahometr_koef2500=iniparser_getdouble(ini,"tahometr:koef2500",57.5);
	sets.tahometr_defangle2500=iniparser_getdouble(ini,"tahometr:defangle2500",-148);
	sets.tahometr_koef3000=iniparser_getdouble(ini,"tahometr:koef3000",57);
	sets.tahometr_defangle3000=iniparser_getdouble(ini,"tahometr:defangle3000",-148);
	sets.tahometr_koef3500=iniparser_getdouble(ini,"tahometr:koef3500",56.3);
	sets.tahometr_defangle3500=iniparser_getdouble(ini,"tahometr:defangle3500",-148);
	sets.tahometr_koef4000=iniparser_getdouble(ini,"tahometr:koef4000",56.1);
	sets.tahometr_defangle4000=iniparser_getdouble(ini,"tahometr:defangle4000",-148);
	sets.tahometr_koef4500=iniparser_getdouble(ini,"tahometr:koef4500",56.2);
	sets.tahometr_defangle4500=iniparser_getdouble(ini,"tahometr:defangle4500",-148);
	sets.tahometr_koef5000=iniparser_getdouble(ini,"tahometr:koef5000",56.5);
	sets.tahometr_defangle5000=iniparser_getdouble(ini,"tahometr:defangle5000",-148);
	sets.tahometr_koef5500=iniparser_getdouble(ini,"tahometr:koef5500",56.7);
	sets.tahometr_defangle5500=iniparser_getdouble(ini,"tahometr:defangle5500",-148);
	sets.tahometr_koef6000=iniparser_getdouble(ini,"tahometr:koef6000",56.9);
	sets.tahometr_defangle6000=iniparser_getdouble(ini,"tahometr:defangle6000",-148);
	sets.tahometr_koef6500=iniparser_getdouble(ini,"tahometr:koef6500",57.2);
	sets.tahometr_defangle6500=iniparser_getdouble(ini,"tahometr:defangle6500",-148);
	sets.tahometr_koef7000=iniparser_getdouble(ini,"tahometr:koef7000",57.4);
	sets.tahometr_defangle7000=iniparser_getdouble(ini,"tahometr:defangle7000",-148);
	sets.tahometr_koef7500=iniparser_getdouble(ini,"tahometr:koef7500",57.6);
	sets.tahometr_defangle7500=iniparser_getdouble(ini,"tahometr:defangle7500",-148);
	sets.tahometr_koef8000=iniparser_getdouble(ini,"tahometr:koef8000",57.7);
	sets.tahometr_defangle8000=iniparser_getdouble(ini,"tahometr:defangle8000",-148);

	sets.fuel_enable=iniparser_getint(ini,"fuel:enable",1);
	sets.fueltexture=iniparser_getstring(ini,"fuel:texture","textures/deftexture.png");
	sets.fuel_x=iniparser_getint(ini,"fuel:x",1100);
	sets.fuel_y=iniparser_getint(ini,"fuel:y",628);
	sets.fuel_lenx=iniparser_getint(ini,"fuel:lenx",160);
	sets.fuel_leny=iniparser_getint(ini,"fuel:leny",5);
	sets.fuel_triangle=iniparser_getint(ini,"fuel:triangle",0);
	sets.fuel_speed=iniparser_getdouble(ini,"fuel:speed",0.1);
	sets.fuel_startangle=iniparser_getdouble(ini,"fuel:startangle",-140);
	sets.fuel_koef=iniparser_getdouble(ini,"fuel:koef",1.375);
	sets.fuel_defangle=iniparser_getdouble(ini,"fuel:defangle",-143);

	sets.temp_enable=iniparser_getint(ini,"temp:enable",1);
	sets.temptexture=iniparser_getstring(ini,"temp:texture","textures/deftexture.png");
	sets.temp_x=iniparser_getint(ini,"temp:x",1180);
	sets.temp_y=iniparser_getint(ini,"temp:y",420);
	sets.temp_lenx=iniparser_getint(ini,"temp:lenx",140);
	sets.temp_leny=iniparser_getint(ini,"temp:leny",5);
	sets.temp_triangle=iniparser_getint(ini,"temp:triangle",0);
	sets.temp_speed=iniparser_getdouble(ini,"temp:speed",0.1);
	sets.temp_startangle=iniparser_getdouble(ini,"temp:startangle",-139);
	sets.temp_koef=iniparser_getdouble(ini,"temp:koef",0.72);
	sets.temp_defangle=iniparser_getdouble(ini,"temp:defangle",-141);


};
