/*
 *  PH sensor library.
 *
 *  Copyright (C) 2018 Duy Huynh
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version 0.1
 *  Author: Duy Huynh
 *  Email: duytel@gmail.com
 */
 
#include "DTH_PHSensor.h"
#include <stdlib.h>


DTH_PHSensor::DTH_PHSensor()
{
	_calib_point_10 = DTH_PH10_VOLTAGE_DEFAULT;
	_calib_point_7 = DTH_PH7_VOLTAGE_DEFAULT;
	_calib_point_4 = DTH_PH4_VOLTAGE_DEFAULT;
	_sample = DTH_PH_SAMPLE;	
}

DTH_PHSensor::DTH_PHSensor(int sensorPin, int powerPin)
{
	_calib_point_10 = DTH_PH10_VOLTAGE_DEFAULT;
	_calib_point_7 = DTH_PH7_VOLTAGE_DEFAULT;
	_calib_point_4 = DTH_PH4_VOLTAGE_DEFAULT;
	_sample = DTH_PH_SAMPLE;	
	begin(sensorPin, powerPin);
}

DTH_PHSensor::DTH_PHSensor(int sensorPin)
{
	_calib_point_10 = DTH_PH10_VOLTAGE_DEFAULT;
	_calib_point_7 = DTH_PH7_VOLTAGE_DEFAULT;
	_calib_point_4 = DTH_PH4_VOLTAGE_DEFAULT;
	_sample = DTH_PH_SAMPLE;	
	begin(sensorPin, -1);
}

DTH_PHSensor::~DTH_PHSensor()
{
}

void DTH_PHSensor::begin(int sensorPin, int powerPin)
{
	_sensorPin = sensorPin;
	_powerPin = powerPin;
	pinMode(_sensorPin, INPUT_PULLUP);
	if(_powerPin != -1)
	{
		pinMode(_powerPin, OUTPUT);
		digitalWrite(_powerPin, LOW); /* Power off */
	}	
}

void DTH_PHSensor::selectionSort(float *buff, int len)
{
	int i,z, pos;
	float tmp;
		
	for (i = 0; i < (len - 1); i++)
	{
		pos = i;

		for (z = i + 1; z < len; z++)
		{
			if (buff[pos] > buff[z])
				pos = z;
		}
		if (pos != i)
		{
			tmp = buff[i];
			buff[i] = buff[pos];
			buff[pos] = tmp;
		}
	}
}

float DTH_PHSensor::getVoltageFilterAvg(int sample, int sensorPin)
{	
	int i;
	float val_buff[sample];
	float voltage = 0.0f;

	for(i = 0; i < sample; i++)
	{
		val_buff[i] = analogRead(sensorPin);
		delayMicroseconds(10);
	}
	/* Sort buffer */
	selectionSort(val_buff, sample); 
	/* get averages in the middle of the buffer */
	for(i = sample/4; i < (3*(sample/4)); i++)
		voltage += val_buff[i];
	voltage = voltage/(sample/2);
	voltage = (voltage * 5000.0)/1024;
	return voltage;
}

float DTH_PHSensor::convertVoltageToPH(float volt)
{
	float resolution;
	
	/* resolution = PHVariationVolttage / PHVariation. */
	if (volt < _calib_point_7) {
		
		/******************************************************************		   
		   PHVariation = (PH) 7 - (PH) 4 = 3
		   PHVariationVolttage = (_calib_point_4 - _calib_point_7) 		   		   
		******************************************************************/
		resolution = (_calib_point_7 - _calib_point_4) / 3;				
	}
	else {	
		/******************************************************************		   
		   PHVariation = (PH) 7 - (PH) 10 = 3
		   PHVariationVolttage = (_calib_point_7 - _calib_point_10) 		   		   
		******************************************************************/
		resolution = (_calib_point_10 - _calib_point_7) / 3;		
	}
	/* The value at PH 7.0 is taken as reference => (PH 7 voltage - Measured volts) = Variation from the reference */
	return 7.0 + (volt - _calib_point_7) / resolution;
}

void DTH_PHSensor::setSampe(int sample)
{
	_sample = sample;	
}

float DTH_PHSensor::getVoltage(void)
{
	float volt;
	
	if(_powerPin != -1)
	{
		digitalWrite(_powerPin, HIGH); /* Power on */
		delay(100);
	}
	/* Read data */
	volt = getVoltageFilterAvg(_sample,  _sensorPin);
	if(_powerPin != -1)
		digitalWrite(_powerPin, LOW); /* Power off */ 
	return volt;
}

float DTH_PHSensor::readPH()
{
	float volt;  

	/* Read data */
	volt = getVoltage();	
	/* Convert to DTH_PH */	
	return convertVoltageToPH(volt);	
}

void DTH_PHSensor::setPH4AcidVolt(float volt)
{
	_calib_point_4 = volt;
}
void DTH_PHSensor::setPH7NeutralVolt(float volt)
{
	_calib_point_7 = volt;
}
void DTH_PHSensor::setPH10BasicVolt(float volt)
{
	_calib_point_10 = volt;
}

