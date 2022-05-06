#ifndef __DRIVER_FUNC_H_
#define __DRIVER_FUNC_H_

#include "DriverType.h"
#pragma comment(lib,"C:/Users/Lyrik/Desktop/111111/Qtwindow/Qtwindow_v1/Driver.lib")

//------------ header file --------------//

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long  int u32;

#define EXPORTED extern "C" __declspec(dllimport)
#define STDCALL  __stdcall

//----------- Initializes the return status flag -----------//
typedef  int ErrorFlag;
#define  INIT_SUCCESS       0
#define  THREAD_ERRORFLAG  0X01
#define  GAIT_ERRORFLAG    0X02
#define  RSCFS_ERRORFLAG   0X04
#define  RLCFS_ERRORFLAG   0X08
#define  RWCFS_ERRORFLAG   0X10
#define  RDCFS_ERRORFLAG   0X20

// When the spectral data is ready to be collected, return marks are completed
#define  SPECTRUMDATA_READY     1
#define  SPECTRUMDATA_VALID     1
#define  SPECTRUMDATA_INVALID   0

#define ON_SPECTRUM_MSG_BASE		    (WM_USER + 700	) 	            // The basis point of message number (the query mark bit can be used to determine whether the collection is completed or not, or the message can be received) 
#define ON_SPECTRUM_RECEIVEDATA			(ON_SPECTRUM_MSG_BASE + 0)	

EXPORTED bool       STDCALL openSpectraMeter();                         // Turn on the device, turn on the usb bus
EXPORTED bool       STDCALL closeSpectraMeter();                        // Turn off usb bus
EXPORTED ErrorFlag  STDCALL initialize();                               // Initialization equipment

EXPORTED bool       STDCALL getSpectrum(int integrationtimeMicros);     // Start collecting spectra
EXPORTED bool       STDCALL getDarkSpectrum(int integrationtimeMicros); // Start collecting spectra
EXPORTED Spectrumsp STDCALL ReadSpectrum();                             // Reading spectral data
EXPORTED int        STDCALL getSpectrumDataReadyFlag();                 // When the acquisition of returned spectral data is completed, the signal bit is ready
EXPORTED bool       STDCALL setAverage(int num);

EXPORTED bool       STDCALL setIntegrationTime(int timeMicros);         // Set integral time
EXPORTED int        STDCALL getActualIntegrationTime();                 // Gets the current integral time, count in milliseconds
EXPORTED int        STDCALL getIntegrationTimeMaximum();                // Get the maximum integral time
EXPORTED int        STDCALL getIntegrationTimeMinimum();                // Get the minimum integration time

EXPORTED bool       STDCALL getProductDate(u8 dataout[]);
EXPORTED bool       STDCALL getProductPN(u8 dataout[]);
EXPORTED bool       STDCALL getProductSN(u8 dataout[]);
EXPORTED float*     STDCALL getWavelength();
EXPORTED int        STDCALL getAttribute();

EXPORTED bool       STDCALL getCCDTecTemperature(u8 dataout[]);
EXPORTED bool       STDCALL setCCDTecTemperature(int CCD_Temp);

EXPORTED void       STDCALL findSpectraMeters(spectrum_device_info& device_info);
EXPORTED bool       STDCALL switchSpectraMeters(const char* serial);
EXPORTED bool       STDCALL findSpectraMeterBySerial(const char* serail);

EXPORTED bool       STDCALL getExtTrigSpectrum(int integrationtimeMicros);
EXPORTED void       STDCALL stopexttrig();

EXPORTED bool       STDCALL closeAllSpectroMeter();
EXPORTED bool       STDCALL closeSpectroMeterBySerial(const char* serial);
EXPORTED bool       STDCALL openAllSpectroMeter();
EXPORTED bool       STDCALL openSpectroMeterBySerial(const char* serial);

EXPORTED ErrorFlag  STDCALL initializeBySerial(const char* serial);
EXPORTED ErrorFlag  STDCALL initializeAll();

EXPORTED bool       STDCALL setIntegrationTimeBySerial(const char* serial, int timeMicros);
EXPORTED bool       STDCALL getSpectrumBySerial(const char* serial, int integrationtimeMicros);
EXPORTED Spectrumsp STDCALL readSpectrumBySerial(const char* serial);
EXPORTED int        STDCALL getSpectrumDataReadyFlagBySerial(const char* serial);
EXPORTED bool       STDCALL clearSpectrumDataReadyFlagBySerial(const char* serial);
EXPORTED bool       STDCALL getDarkSpectrumBySerial(const char* serial, int integrationtimeMicros);

EXPORTED bool       STDCALL getProductPNBySerial(const char* serial, u8 dataout[]);
EXPORTED int        STDCALL getActualIntegrationTimeBySerial(const char* serial);
EXPORTED int        STDCALL getIntegrationTimeMaximumBySerial(const char* serial);
EXPORTED int        STDCALL getIntegrationTimeMinimumBySerial(const char* serial);

EXPORTED float*     STDCALL getWavelengthBySerial(const char* serial);
EXPORTED bool       STDCALL setGPIOEnableBySerial(const char* serial, int enabledata);
EXPORTED int        STDCALL getAttributeBySerial(const char* serial);

EXPORTED bool       STDCALL getCCDTecTEMPBySerial(const char* serial, u8 dataout[]);
EXPORTED bool       STDCALL setCCDTecTEMPBySerial(const char* serial, int num);

EXPORTED int        STDCALL getUsedPixelStart(); // ATP5100 get pixel start
EXPORTED int        STDCALL getUsedPixelEnd();   // ATP5100 get pixel end
EXPORTED float*		STDCALL dataProcess(int original_data[], int smoothLevel, bool isDeductDark, bool isNonlinearCorrect, bool isShapeCalibration); // 原始数据改为浮点数

EXPORTED bool       STDCALL getExtTrigSpectrumBySerial(const char* serial, int integrationTime); // start external trigger mode
EXPORTED void       STDCALL stopExtTrigBySerial(const char* serial); // stop external trigger mode

EXPORTED int        STDCALL getPixelCount();
EXPORTED int        STDCALL getPixelCountBySerial(const char* serial);

#endif 
