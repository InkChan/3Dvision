#pragma once
#include <iostream>
#include <string.h>
#include <qcolor.h>

/*
//Time:     trigger on time
//IS:		independent,internal trigger via software
//HW:		hardware trigger
//Encoder:	external trigger via trigger
*/
enum SensorTriggerMode
{
	Time=0,
	IS=3,					
	HW=2,						
	Encoder=1					
};

/*
//exposure Mode
//Dynamic:	bounce in a range
//Single:	single Exposure value
*/
enum ExposureMode
{
	Dynamic=2,
	Single=0,
	Multiple=1
};

template <typename T>
struct Range
{
	T minValue;
	T maxValue;
	T Value;
};

class Sensor
{
public:
	Sensor();
	virtual std::string getSensorName();				//get sensor name
	
	virtual std::string getSensorType();				//get sensor type
	virtual std::string getSerialNumber();				//get serial number

	virtual Range<int> getMeasureRange();				//get measurement range
	virtual Range<int> getzStartRange();				//get z start range

	virtual int getStatus();							//get sensor status

	virtual std::string getSensorIP();					//get sensor IP
	virtual int setSensorIP(std::string);				//set sensor IP

	virtual std::string getSensorTriggerMode();				//get sensor trigger mode
	virtual int getSensorTriggerDelay();					//get sensor trigger delay
	virtual int setSensorTriggerDelay(int);					//set sensor trigger delay

	virtual int setSensorTriggerMode(SensorTriggerMode);	//set sensor trigger mode
	virtual int setSensorExposureTime(int);					//set sensor exposure time
	std::string getSensorExposureMode();					//get exposure mode
	virtual int getSensorExposureTime();					//get exposure time

	virtual int connect();									//connect sensor
	virtual int disconnect();								//disconnect sensor
	virtual ~Sensor();

public :
	int setSensorName(std::string name);		//set sensor name

	int IsMaster();										//is master
	int setMaster();									//set master
	int getSequenceIndex();								//get sequence index
	int setSequenceIndex(int);							//set sequenct index
	int setSensorType(std::string);						//set sensor type
	QColor getColor();									//get sensor color
	void setColor(QColor);								//set sensor color
	int getTransformation();					//get transformation
	int setTransformation(int);					//set transformation
	

protected:
	std::string m_sensorName;				//sensor Name
	QColor m_sensorColor;					//sensor color shown in SetSensor UI
	std::string m_sensorType;				//sensor Type
	std::string m_serialNumber;				//sensor serial number
	std::string m_ipAddress;				//sensor ip address

	Range<int> m_MeasureRange;				//measure range
	Range<int> m_zstartRange;				//z start range
	int m_transformation;					//z transformation

	ExposureMode m_exposureMode;			//sensor exposure Mode
	Range<int> m_dynamaicExposureValue;		//sensor exposure dynamic range
	int m_exposureValue;					//sensor single exposure value

	SensorTriggerMode m_triggerMode;		//sensor Trigger mode
	int m_triggerDelay;						//trigger delay

	int m_isMaster;						//set up the sensor as the master
	int m_sequenceIndex;					//assignment to a position within the measuring sequence
	
	bool m_isActive;						//indicate if sensor is active
	int m_pulseWidth;						//pulse width of sensor
};

