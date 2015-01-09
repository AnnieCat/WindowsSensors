// annie1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <initguid.h>
#include <SensorsApi.h>
#include <sensors.h>
#include <iostream>
#include <cstdarg>
using namespace std;
#pragma comment(lib, "Sensorsapi.lib")

//void CheckPropertyOriginal(int sensorId, ISensor * pSensor, const PROPERTYKEY & key, const char * what)
//{
//	VARIANT_BOOL bSupported;
//	HRESULT hr = pSensor->SupportsDataField(key, bSupported);
//	if (FAILED(hr))
//	{
//		::MessageBox(NULL, _T("shit be fucked"), _T("Sensor C++ Sample"), MB_OK | MB_ICONERROR);
//		exit(-1);
//	}
//	if (bSupported == VARIANT_TRUE) printf("Sensor %d supports %s!\n", sensorId, what);
//	else printf("Sensor %d does not support %s!\n", sensorId, what);
//}

void CheckProperty(int sensorId, ISensor * pSensor)
{
	BSTR name;
	pSensor->GetFriendlyName(&name);
	wprintf(L"Sensor %d says its name is %s.\n", sensorId, name);
}



void Error(const char * format, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	printf("\nPress any key to continue...");
	cin.get();
	exit(-1);
}


int _tmain(int argc, _TCHAR* argv[])
{

	::CoInitialize(NULL);
	
	ISensorManager * pSensorManager = NULL;
	HRESULT hr = ::CoCreateInstance(CLSID_SensorManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pSensorManager));	if (FAILED(hr)) Error("Unable to CoCreateInstance() the SensorManager.");

	
	ISensorCollection* pSensorCollection = NULL;
	hr = pSensorManager->GetSensorsByCategory(SENSOR_CATEGORY_ALL, &pSensorCollection);
	if (FAILED(hr)) Error("Unable to find any Sensors on the computer.");
	
	
	
	ULONG count;
	hr = pSensorCollection->GetCount(&count);
	if (FAILED(hr))
	{
		::MessageBox(NULL, _T("shit be fucked"), _T("sensor C++ sample"), MB_OK | MB_ICONERROR);
		return -1;
	}

	for (ULONG i = 0; i < count; ++i)
	{
		ISensor * pSensor;
		hr = pSensorCollection->GetAt(i, &pSensor);
		if (FAILED(hr))
		{
			::MessageBox(NULL, _T("Shit be fucked"), _T("Sensor C++ sample"), MB_OK | MB_ICONERROR);
			return -1;
		}

		CheckProperty(i,pSensor);
	}
	::CoUninitialize();
	
	printf("\nWe found Gyros! Press any key to continue...");
	cin.get();
	return 0;
}

