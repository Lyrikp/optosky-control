
#include <windows.h> 
#include <iostream>

#include "DriverType.h"
#include "Driver_app.h"

using namespace std;

int main()
{
	// �򿪲�ʶ���豸
	bool flag_0 = openSpectraMeter();
	cout << "�����ѽ�����" << endl;
	spectrum_device_info ATP5020P;
	findSpectraMeters(ATP5020P);
	int device_number = ATP5020P.length;
	cout << ATP5020P.length << " ̨�豸�ɹ��������ӡ�" << endl;
	cout << "���ӵ��豸��Ϣ: " << ATP5020P.descriptor << endl;

	cout << endl;

	// �����豸��ʼ��
	cout << "���ڽ��г�ʼ��" << endl;
	ErrorFlag flag = initialize();
	Sleep(1000);
	if (flag == INIT_SUCCESS)
	{
		cout << "��ʼ�����" << endl;
	}
	else
	{
		cout << "δ��ɳ�ʼ���������˳�����" << endl;
		Sleep(500);
		return 0;
	}
	Sleep(1000);
	cout << endl;

	// ��ȡ�豸��Ϣ
	cout << "------------�豸��Ϣ-------------" << endl;
	u8 dataout[SPECTRUM_SIZE] = { 0 };
	cout << "��ȡ�豸��SN�ţ�" << getProductSN(dataout) << endl;
	cout << "�豸��PN��ţ� " << getProductPN(dataout) << endl;
	cout << "�豸�������ڣ� " << getProductDate(dataout) << endl;
	cout << endl;

	// �豸����ʱ��
	cout << "------------��������-------------" << endl;
	int min_integraltime = getIntegrationTimeMinimum();
	int max_integraltime = getIntegrationTimeMaximum();
	int integraltime = getActualIntegrationTime();
	cout << "�������û���ʱ��" << endl;
	cout << "��ǰ�豸�Ļ���ʱ�� " << integraltime << endl;
	cout << "��ǰ�豸�Ļ���ʱ�䷶Χ " << min_integraltime << "~" << max_integraltime << endl;
	cout << "���û���ʱ��: ";
	int settime;
	cin >> settime;
	setIntegrationTime(settime);
	integraltime = settime;
	cout << "������ɣ���ǰ�Ļ���ʱ��Ϊ " << integraltime << endl;
	Sleep(1000);
	cout << endl;

	// ���òɼ�ƽ������
	cout << "------------�ɼ�ƽ����������-------------" << endl;
	cout << "���òɼ�ƽ������: ";
	int average_num;
	cin >> average_num;
	flag = setAverage(average_num);
	if (flag == true)
	{
		cout << "������ɣ���ǰ�Ĳɼ�ƽ������Ϊ " << average_num << endl;
	}
	else
	{
		cout << "�������⣬����������ݸ�ʽ��������⣬�����˳�����" << endl;
		return 0;
	}
	Sleep(1000);
	cout << endl;

	// �������ɼ�
	cout << "------------���ð�����ģʽ-------------" << endl;
	cout << "��믵ơ��⿪���龳�£����ð�����ģʽ(y/n) ?" << endl;
	string yn;
	cin >> yn;
	if (yn == "y")
	{
		bool flag3 = getDarkSpectrum(integraltime);
		if (flag3 == true)
		{
			cout << "������ģʽ�ѿ���" << endl;
			cout << "���ײ���ǰ�������" << endl;
		}
		else
		{
			cout << "������ģʽδ�����ã�����³��򣬻����豸����" << endl;
			cout << "�����˳�����" << endl;
			return 0;
		}
	}
	else
	{
		cout << "����ģʽ������" << endl;
	}
	Sleep(1000);
	cout << endl;

	// ���ײɼ�
	cout << "���ײ���ǰ�������" << endl;
	Sleep(500);
	cout << "���׻�ȡ׼������" << endl;

	cout << endl << endl;
	cout << "���ڲɼ��������ݣ��뱣�ֹ�Դ�ȶ�" << endl;

	flag = getSpectrum(integraltime);

	// ������Դʱ�ȴ���Ӧ TODO:������while�ȴ�
	int count = 0;
	while (count <= 10)
	{
		cout << "��";
		count++;
		Sleep(500);
	}
	cout << endl;

	if (flag == 1)
	{
		flag = getSpectrumDataReadyFlag();
		if (flag == SPECTRUMDATA_READY)
		{
			cout << "�������ݲɼ����" << endl;
			Spectrumsp data;
			data = ReadSpectrum();
			int *wavelength = data.array;
			for (int i = 0; i < 10; i++)
			{
				cout << "�� " << i << " �㣺 " ;
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
			cout << "�������ݲɼ����ִ������ٴγ��ԣ����²ɼ�" << endl;
			return 0;
		}
	}
	else
	{
		cout << "�������ݲɼ�δ����ɣ��뱣�ֹ�Դ�ȶ������²ɼ�" << endl;
		return 0;
	}

	cout << "�׶��Բ��Գɹ������������˳�";

	closeSpectraMeter();
	Sleep(1000);
	cin.get();
	return 0;
}

