#pragma once

#include "Sensor.h"
#include "LMISensor.h"
#include "WenglorSensor.h"
#include <vector>

extern std::vector<Sensor*> SensorVector;

extern void check_sensor();

