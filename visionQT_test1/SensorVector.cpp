#include "SensorsVector.h"

std::vector<Sensor*> SensorVector(NULL);

void check_sensor()
{
#pragma region LMI
	kAssembly api = kNULL;
	kStatus status;
	GoSystem system = kNULL;
	if ((status = GoSdk_Construct(&api)) != kOK)
	{
		return;
	}
	if ((status = GoSystem_Construct(&system, kNULL)) != kOK)
	{
		return;
	}
	kSize count1 = GoSystem_SensorCount(system);

	for (size_t i = 0; i < count1; ++i)
	{
		LMISensor *lmisensor = new LMISensor();
		lmisensor->setSensor(GoSystem_SensorAt(system, i));
		SensorVector.push_back(lmisensor);	
	}

#pragma endregion
}