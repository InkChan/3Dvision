#include "LMISensor.h"

std::string Byte2Hex(kByte bArray[], int bArray_len);
std::vector<std::string> split(std::string str, std::string pattern);

std::string LMISensor::getSensorIP()
{
	GoAddressInfo *AddressInfo = new GoAddressInfo();
	GoSensor_Address(LMIsensor, AddressInfo);

	m_ipAddress = Byte2Hex(AddressInfo->address.address, 4);
	return m_ipAddress;
}

std::string Byte2Hex(kByte bArray[], int bArray_len)
{
	std::string strHex = "";
	int b[4];
	for (size_t i = 0; i < bArray_len; i++)
	{
		b[i] = bArray[i];
	}
	char c[8];
	for (size_t i = 0; i < 4; i++)
	{
		_itoa(b[i], c, 10);
		strHex += c;
		if (i != 3)
		{
			strHex += ".";
		}
	}
	return strHex;
}

std::string LMISensor::getSensorTriggerMode()
{
	if (!GoSensor_IsConnected(LMIsensor))
	{
		return "please connect the sensor first!";
	}
	setup = GoSensor_Setup(LMIsensor);
	GoTrigger trigger = GoSetup_TriggerSource(setup);
	m_triggerMode = (SensorTriggerMode)trigger;
	switch (m_triggerMode)
	{
	case Time:
		return "Time";
	case Encoder:
		return "Encoder";
	case IS:
		return "IS";
	case HW:
		return "HW";
	default:
		return "";
		break;
	}
}

int LMISensor::getSensorTriggerDelay()
{
	if (!GoSensor_IsConnected(LMIsensor))
	{
		return -1;
	}
	setup = GoSensor_Setup(LMIsensor);
	return m_triggerDelay = GoSetup_TriggerDelay(setup);
}

std::string LMISensor::getSensorExposureMode()
{
	if (!GoSensor_IsConnected(LMIsensor))
	{
		return "please connect the sensor first!";
	}
	setup = GoSensor_Setup(LMIsensor);
	m_exposureMode = (ExposureMode)GoSetup_ExposureMode(setup, m_sequenceIndex);
	switch (m_exposureMode)
	{
	case Dynamic:
		return "Dynamic";
		break;
	case Single:
		return "Single";
		break;
	case Multiple:
		return "Multiple";
		break;
	default:
		return "";
		break;
	}
}

int LMISensor::getSensorExposureTime()
{
	if (!GoSensor_IsConnected(LMIsensor))
	{
		return -1;
	}
	setup = GoSensor_Setup(LMIsensor);
	return m_exposureValue = GoSetup_Exposure(setup, m_sequenceIndex);
}

int LMISensor::connect()
{
	getSensorType();
	getSerialNumber();
	getMeasureRange();
	getzStartRange();
	getTransformation();
	getStatus();
	getSequenceIndex();
	IsMaster();
	getSensorIP();
	getSensorTriggerMode();
	getSensorTriggerDelay();
	getSensorExposureMode();
	getSensorExposureTime();
	kStatus status;
	if ((status = GoSensor_Connect(LMIsensor)) != kOK)
	{
		m_isActive = false;
		return status-1;
	}
	m_isActive = true;
	return  status-1;
}

int LMISensor::disconnect()
{	
	kStatus status;
	if ((status = GoSensor_Disconnect(LMIsensor)) != kOK)
	{
		m_isActive = false;
		return status - 1;
	}
	m_isActive = true;
	return  status - 1;
}

int LMISensor::setSensorIP(std::string IP)
{
	GoAddressInfo *AddressInfo = new GoAddressInfo();// = GoSensor_AddressInfo(&sensor);

	GoSensor_Address(LMIsensor, AddressInfo);
	try
	{
		std::vector<std::string> ips = split(IP, ".");
		for (size_t i = 0; i < 4; i++)
		{
			AddressInfo->address.address[i] = atoi(ips.at(i).c_str());
		}
		GoSensor_SetAddress(LMIsensor, AddressInfo, true);
		return 0;
	}
	catch (std::exception ex)
	{
		return -1;
	}
}

//×Ö·û´®·Ö¸îº¯Êý
std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//À©Õ¹×Ö·û´®ÒÔ·½±ã²Ù×÷
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

int LMISensor::setSensorTriggerMode(SensorTriggerMode triggermode)
{
	if (!GoSensor_IsConnected(LMIsensor))
	{
		return -1;
	}
	setup = GoSensor_Setup(LMIsensor);
	GoTrigger trigger = (GoTrigger)triggermode;
	return GoSetup_SetTriggerSource(setup, trigger);
}

int LMISensor::setSensorTriggerDelay(int Delaytime)
{
	if (!GoSensor_IsConnected(LMIsensor))
	{
		return -1;
	}
	setup = GoSensor_Setup(LMIsensor);
	return GoSetup_SetTriggerDelay(setup, Delaytime);
}

int LMISensor::setSensorExposureMode(ExposureMode exposureMode)
{
	if (!GoSensor_IsConnected(LMIsensor))
	{
		return -1;
	}
	setup = GoSensor_Setup(LMIsensor);
	GoExposureMode exposuremode = (GoExposureMode)exposureMode;
	return GoSetup_SetExposureMode(setup, m_sequenceIndex, exposuremode);
}

int LMISensor::setSensorExposureTime(int Exposuretime)
{
	if (!GoSensor_IsConnected(LMIsensor))
	{
		return -1;
	}
	setup = GoSensor_Setup(LMIsensor);
	return GoSetup_SetExposure(setup, m_sequenceIndex, Exposuretime);
}

int LMISensor::setSensor(GoSensor sensor)
{
	LMIsensor = sensor;
	return 0;
}

std::string LMISensor::getSerialNumber()
{
	k32u sernumber = GoSensor_Id(LMIsensor);
	char c[8];
	_itoa(sernumber, c, 10);
	m_serialNumber = c;
	return m_serialNumber;
}

std::string LMISensor::getSensorType()
{
	m_sensorType = "LMI";
	return m_sensorType;
}

int LMISensor::getStatus()
{
	m_isActive = GoSensor_IsConnected(LMIsensor);
	return m_isActive;
}

LMISensor::~LMISensor()
{
}
