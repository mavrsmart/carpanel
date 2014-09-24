// vars.c
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
//           vars.c
//  Чт Август 21 23:28:15 2014
//  Copyright  2014  user
//  <user@host>

#include <GL/gl.h>
#include <GL/glut.h>
#include "znak.h"
#include "dialgauge.h"
#include "iniparser.h"

dictionary* ini;

//Значения отображения
float speed=0;
float tahometr=0;
float fuel=0;
float temp=0;
//знаки
int power=0;
int dalnsvet=0;
int imobilizer=0;
int maslo=0;
int opendoor=0;
int povorlevo=0;
int povorpravo=0;
int protivotuman=0;
int torm=0;
//***


GLuint dashboard;

dialgauge dg_speed,dg_tahometr,dg_fuel,dg_temp;
znak zn_fuel,zn_dalnsvet,zn_imobilizer,zn_maslo,zn_opendoor,zn_peregrev,zn_povorlevo,zn_povorpravo,zn_power,zn_protivotuman,zn_torm;
