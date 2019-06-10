#include "Sensor.h"
Sensor::Sensor() :
	m_isActive(false),
	m_isMaster(0),
	m_triggerDelay(0),
	m_transformation(0),
	m_sequenceIndex(0),
	m_ipAddress("1"),
	m_exposureValue(0),
	m_sensorName("1"),
	m_sensorType("1"),
	m_serialNumber("1"),
	m_pulseWidth(0)
{
	m_MeasureRange.maxValue = 0;
	m_MeasureRange.minValue = 0;
	m_MeasureRange.Value = 0;

	m_zstartRange.maxValue = 0;
	m_zstartRange.minValue = 0;
	m_zstartRange.Value = 0;
	m_exposureMode = ExposureMode::Single;
	m_sensorColor = QColor(Qt::red);
	m_dynamaicExposureValue = Range<int>{ 0, 0, 0 };
	m_triggerMode = SensorTriggerMode::IS;
}

QColor Sensor::getColor()
{
	return m_sensorColor;
}

void Sensor::setColor(QColor color)
{
	m_sensorColor = color;
}

std::string Sensor::getSensorName()
{
	return m_sensorName;
}

std::string Sensor::getSensorType()
{
	return m_sensorType;
}

std::string Sensor::getSerialNumber()
{
	return m_serialNumber;
}

Range<int> Sensor::getMeasureRange()
{
	return m_MeasureRange;
}

Range<int> Sensor::getzStartRange()
{
	return m_zstartRange;
}

int Sensor::getTransformation()
{
	return m_transformation;
}

std::string Sensor::getSensorIP()
{
	return m_ipAddress;
}

int Sensor::setSensorIP(std::string ip)
{
	return 0;
}

std::string Sensor::getSensorTriggerMode()
{
	if (m_triggerMode == IS)
	{
		return "IS";
	}
	else if (m_triggerMode == HW)
	{
		return "HW";
	}
	else if (m_triggerMode == Encoder)
	{
		return "Encoder";
	}
	else if (m_triggerMode == Time)
	{
		return "Time";
	}
	else
	{
		return "None";
	}
}

int Sensor::getStatus()
{
	return m_isActive;
}

int Sensor::getSequenceIndex()
{
	return m_sequenceIndex;
}

int Sensor::IsMaster()
{
	return m_isMaster;
}

int Sensor::setMaster()
{
	m_isMaster = 1;
	return 0;
}

int setSensorTriggerDelay(int time)
{
	return 0;
}

std::string Sensor::getSensorExposureMode()
{
	if (m_exposureMode == Dynamic)
	{
		return "Dynamic";
	}
	else if (m_exposureMode == Single)
	{
		return "Single";
	}
	else if (m_exposureMode == Multiple)
	{
		return "Multiple";
	}
	else
	{
		return "None";
	}
}

int Sensor::setSensorTriggerMode(SensorTriggerMode mode)
{
	return 0;
}

int Sensor::getSensorTriggerDelay()
{
	return m_triggerDelay;
}

int Sensor::setSensorTriggerDelay(int triggerDelay)
{
	m_triggerDelay = triggerDelay;
	return 0;
}

int Sensor::getSensorExposureTime()
{
	return m_exposureValue;
}

int Sensor::setSensorType(std::string type)
{
	m_sensorType = type;
	return 0;
}

int Sensor::connect()
{
	return 0;
}

int Sensor::disconnect()
{
	return 0;
}

int Sensor::setTransformation(int transform)
{
	m_transformation = transform;
	return 0;
}

int Sensor::setSensorName(std::string name)
{
	m_sensorName = name;
	return 0;
}

int Sensor::setSequenceIndex(int index)
{
	m_sequenceIndex = index;
	return 0;
}

int Sensor::setSensorExposureTime(int time)
{
	return 0;
}

Sensor::~Sensor()
{
}
