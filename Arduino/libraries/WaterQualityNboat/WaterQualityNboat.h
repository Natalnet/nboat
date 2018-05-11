/*

	WaterQualityNboat.h - Library for monitoring water quality into system
	Created by Andouglas Goncalves da Silva Junior, April 4, 2018
	Released into Nboat private folder
*/

#ifndef WaterQualityNboat_h
#define WaterQualityNboat_h

#include "Arduino.h"

class WaterQualityNboat
{
	public:
		static WaterQualityNboat* getInstance();
		
		WaterQualityNboat();
		WaterQualityNboat(int addr_ph, int addr_por, int addr_oxigen, int addr_temperature, int addr_condutivity);

		void startCommunication(int address);
		void closeCommunication();

		
		char * getData(int sensorId, char * cmd);
		void sendData(char * cmd);
		void requestData(int address);
		bool dataAvailable();
		byte read();
		float * getAllData(int *);
		float getDataTemperature();
		String * i2cScanner();
		int * findAvailableSensors();
		int getNumberSensors();
		void setNumberSensors(int);
		

	private:

		int _sensorId;
		char * _cmd;
		byte code;
		int _addr_ph = 99;
		int _addr_por = 98;
		int _addr_oxigen = 97;
		int _addr_temperature;
		int _addr_condutivity = 100;
		int time_ = 900;
		char * _data;
		float _dataFloat;		
		static WaterQualityNboat* wqNboat;
		int numberSensors = 0;
		//int * sensors= new int[5];
		String * list;

};

#endif