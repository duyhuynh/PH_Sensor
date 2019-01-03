/*
 *  DTH_PH Sensor library.
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
#ifndef DTH_PH_SENSOR_H_
#define DTH_PH_SENSOR_H_

/*------------------------------------------------------------------*
 *                           Includes                               *
 *------------------------------------------------------------------*/
#include "Arduino.h"

/*------------------------------------------------------------------*
 *                          Define macro                            *
 *------------------------------------------------------------------*/
#define DTH_PH_SAMPLE 16
#define DTH_PH4_VOLTAGE_DEFAULT 1402  
#define DTH_PH7_VOLTAGE_DEFAULT 2000  
#define DTH_PH10_VOLTAGE_DEFAULT 2558 

/*------------------------------------------------------------------*
 *                        Class declaration                         *
 *------------------------------------------------------------------*/
class DTH_PHSensor
{
	public:
		//! Class constructor.
		DTH_PHSensor();
		DTH_PHSensor(int sensorPin, int powerPin);
		DTH_PHSensor(int sensorPin);
		~DTH_PHSensor();

		void begin(int sensorPin, int powerPin);
		/* The normal range for PH in surface water systems is 6.5 to 8.5 and for groundwater systems 6 to 8.5 */
		void setPH4AcidVolt(float volt);      //0 – 6.5 is Acidic
		void setPH7NeutralVolt(float volt);  //7 is Neutral
		void setPH10BasicVolt(float volt);   //7.5 - 14 is Basic       
		void setSampe(int sample);
		float readPH(void);
		float getVoltage(void);

	private:		
		float getVoltageFilterAvg(int sample, int sensorPin);		
		float convertVoltageToPH(float volt);
		void selectionSort(float *buff, int len);

	protected:
		float _calib_point_10;
		float _calib_point_7;
		float _calib_point_4;
		int _sample;    
		uint8_t _sensorPin;
		uint8_t _powerPin;
};

#endif //DTH_PH_SENSOR_H_
