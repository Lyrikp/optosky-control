
#include <windows.h> 
#include <iostream>

#include "DriverType.h"
#include "Driver_app.h"

using namespace std;

int main()
{
	// 打开并识别设备
	bool flag_0 = openSpectraMeter();
	cout << "连接已建立。" << endl;
	spectrum_device_info ATP5020P;
	findSpectraMeters(ATP5020P);
	int device_number = ATP5020P.length;
	cout << ATP5020P.length << " 台设备成功建立连接。" << endl;
	cout << "连接的设备信息: " << ATP5020P.descriptor << endl;

	cout << endl;

	// 进行设备初始化
	cout << "正在进行初始化" << endl;
	ErrorFlag flag = initialize();
	Sleep(1000);
	if (flag == INIT_SUCCESS)
	{
		cout << "初始化完成" << endl;
	}
	else
	{
		cout << "未完成初始化，正在退出程序" << endl;
		Sleep(500);
		return 0;
	}
	Sleep(1000);
	cout << endl;

	// 获取设备信息
	cout << "------------设备信息-------------" << endl;
	u8 dataout[SPECTRUM_SIZE] = { 0 };
	cout << "获取设备的SN号：" << getProductSN(dataout) << endl;
	cout << "设备的PN序号： " << getProductPN(dataout) << endl;
	cout << "设备生产日期： " << getProductDate(dataout) << endl;
	cout << endl;

	// 设备积分时间
	cout << "------------积分设置-------------" << endl;
	int min_integraltime = getIntegrationTimeMinimum();
	int max_integraltime = getIntegrationTimeMaximum();
	int integraltime = getActualIntegrationTime();
	cout << "正在设置积分时间" << endl;
	cout << "当前设备的积分时间 " << integraltime << endl;
	cout << "当前设备的积分时间范围 " << min_integraltime << "~" << max_integraltime << endl;
	cout << "设置积分时间: ";
	int settime;
	cin >> settime;
	setIntegrationTime(settime);
	integraltime = settime;
	cout << "设置完成，当前的积分时间为 " << integraltime << endl;
	Sleep(1000);
	cout << endl;

	// 设置采集平均次数
	cout << "------------采集平均次数设置-------------" << endl;
	cout << "设置采集平均次数: ";
	int average_num;
	cin >> average_num;
	flag = setAverage(average_num);
	if (flag == true)
	{
		cout << "设置完成，当前的采集平均次数为 " << average_num << endl;
	}
	else
	{
		cout << "出现问题，检查输入数据格式与程序问题，正在退出程序" << endl;
		return 0;
	}
	Sleep(1000);
	cout << endl;

	// 暗背景采集
	cout << "------------启用暗背景模式-------------" << endl;
	cout << "在氙灯、光开关情境下，启用暗背景模式(y/n) ?" << endl;
	string yn;
	cin >> yn;
	if (yn == "y")
	{
		bool flag3 = getDarkSpectrum(integraltime);
		if (flag3 == true)
		{
			cout << "暗背景模式已开启" << endl;
			cout << "光谱测试前设置完成" << endl;
		}
		else
		{
			cout << "暗背景模式未能启用，请更新程序，或检查设备问题" << endl;
			cout << "正在退出程序" << endl;
			return 0;
		}
	}
	else
	{
		cout << "正常模式运行中" << endl;
	}
	Sleep(1000);
	cout << endl;

	// 光谱采集
	cout << "光谱测试前设置完成" << endl;
	Sleep(500);
	cout << "光谱获取准备就绪" << endl;

	cout << endl << endl;
	cout << "正在采集光谱数据，请保持光源稳定" << endl;

	flag = getSpectrum(integraltime);

	// 测量光源时等待响应 TODO:可以用while等待
	int count = 0;
	while (count <= 10)
	{
		cout << "■";
		count++;
		Sleep(500);
	}
	cout << endl;

	if (flag == 1)
	{
		flag = getSpectrumDataReadyFlag();
		if (flag == SPECTRUMDATA_READY)
		{
			cout << "光谱数据采集完成" << endl;
			Spectrumsp data;
			data = ReadSpectrum();
			int *wavelength = data.array;
			for (int i = 0; i < 10; i++)
			{
				cout << "第 " << i << " 点： " ;
				cout << *(wavelength + i) << endl;
			}

			float* p = getWavelength();
			Spectrumsp q = ReadSpectrum();
			for (int i = 0; i < 10; i++) {
				cout << "*(p + " << i << ") : ";
				cout << *(p + i) << "     " << *(q.array + i) << endl;
			}


		}
		else
		{
			cout << "光谱数据采集出现错误，请再次尝试，重新采集" << endl;
			return 0;
		}
	}
	else
	{
		cout << "光谱数据采集未能完成，请保持光源稳定，重新采集" << endl;
		return 0;
	}

	cout << "阶段性测试成功，程序正在退出";

	closeSpectraMeter();
	Sleep(1000);
	cin.get();
	return 0;
}

