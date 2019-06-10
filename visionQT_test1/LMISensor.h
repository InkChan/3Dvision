#pragma once
#include "Sensor.h"
#include <stdio.h>
#include <tchar.h>
#include <GoSdk\GoSdk.h>
#include <memory.h>
#include <stdlib.h>
#include <vector>
#include <exception> 

#define RECEIVE_TIMEOUT         (20000000) 
#define INVALID_RANGE_16BIT     ((signed short)0x8000)          // gocator transmits range data as 16-bit signed integers. 0x8000 signifies invalid range data. 
#define DOUBLE_MAX              ((k64f)1.7976931348623157e+308) // 64-bit double - largest positive value.  
#define INVALID_RANGE_DOUBLE    ((k64f)-DOUBLE_MAX)             // floating point value to represent invalid range data.                         

#define NM_TO_MM(VALUE) (((k64f)(VALUE))/1000000.0)
#define UM_TO_MM(VALUE) (((k64f)(VALUE))/1000.0)

typedef struct
{
	double x;   // x-coordinate in engineering units (mm) - position along laser line
	double z;   // z-coordinate in engineering units (mm) - height (at the given x position)
	unsigned char intensity;
}ProfilePoint;

class LMISensor :
	public Sensor
{
public:
	LMISensor() :Sensor()
	{
		LMIsensor = kNULL;
		setup = kNULL;
	}
	~LMISensor();

	virtual std::string getSensorType();					//get sensor type
	virtual std::string getSerialNumber();			//get serial number

	//Range<size_t> getMeasureRange();	    //get measurement range
	//Range<size_t> getzStartRange();		//get z start range
	virtual int getStatus();						//get sensor status
	virtual std::string getSensorIP();				//get sensor IP	
	virtual std::string getSensorTriggerMode();		//get sensor trigger mode
	virtual int getSensorTriggerDelay();			//get sensor trigger delay	
	virtual std::string getSensorExposureMode();	//get exposure mode
	virtual int getSensorExposureTime();			//get exposure time

	virtual int connect();									//connect
	virtual int disconnect();								//disconnect sensor
	/*virtual */int setSensorIP(std::string IP);				//set sensor IP	
	virtual int setSensorTriggerMode(SensorTriggerMode);	//set sensor trigger mode
	virtual int setSensorTriggerDelay(int);					//set sensor trigger delay	
	virtual int setSensorExposureMode(ExposureMode);		//set exposure mode
	virtual int setSensorExposureTime(int);					//set exposure time
	int setSensor(GoSensor sensor);
private:
	GoSensor LMIsensor;
	GoSetup setup;
};

