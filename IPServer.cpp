#include "IPServer.h"
#include "ExcelBase.h"
#include <iostream>
#include <string.h>
#include <map>
#include <cstring>
#include <string>
#include <stdio.h>
#include <regex>
#include <QSqlError>
#include <QHeaderView>
#include <vector>
#include "QHostInfo"
#include <QDialog>
using  namespace std;

std::vector<DEVICE_NET_INFO_EX> g_lDeviceVec;
std::vector<DeviceInfo_admin> hk_lDeviceVec;
int RowRecord[256];//��¼���������
int RowAmonut=0;//����ĸ���
int TableCustom = 0;//�������
int CheckNumber = 0;//��ѡ������
int DoubleRow = 0;
QWaitCondition wc_newTask;//���ƿ����λص�
//QWaitCondition wc_flushDownnloadInfo;
QMutex mx_newTask;//���ƿ����λص�������
//QMutex mx_downloadingTaskRun;
//�ֶ������Ϣ��¼
QString IPstringofhand = "";
QString Portstringofhand = "";
QString Adminstrngofhand = "";
QString Pawwsdstringofhand = "";
QTableWidgetItem *InfoemationItem = new QTableWidgetItem;
HMODULE moduleOfHC;
IPServer* g_ipserver;
sADP_ActivateDevice SADP_ActivateDevice=nullptr;
BOOL isAscending = FALSE;
BOOL isAscending_one = FALSE;
BOOL isAscending_two = FALSE;
BOOL isAscending_three = FALSE;
BOOL isAscending_seven = FALSE;
BOOL isAscending_series_dh = FALSE;
BOOL isAscending_series_hk = FALSE;
BOOL isCreateTable = FALSE;
//�����ص� DH
void CALLBACK SearchDevicesCB(DEVICE_NET_INFO_EX *pDevNetInfo, void*  pUserData)
{
	if (NULL == pDevNetInfo| strncmp(pDevNetInfo->szDetailType, "JF-NC", 5) != 0| pDevNetInfo->iIPVersion == 6)
	{
		printf("warning param is null\n");
		return;
	}
	DEVICE_NET_INFO_EX SadpInfo = { 0 };
	memcpy(&SadpInfo, pDevNetInfo, sizeof(DEVICE_NET_INFO_EX));
    std::vector<DEVICE_NET_INFO_EX>* pDeviceList =(std::vector<DEVICE_NET_INFO_EX>*)pUserData;
	for (std::vector<DEVICE_NET_INFO_EX>::iterator iter = g_lDeviceVec.begin(); iter != g_lDeviceVec.end(); ++iter)
	{
		if (strncmp(SadpInfo.szMac ,iter->szMac,40)==0)
		{
			return;
		}
	}
	char db_char[200] = { '\0' };
	sprintf(db_char, "select * from Device_Sheet where ip='%s'", SadpInfo.szIP);
	g_ipserver->db_query->exec(db_char);
	BOOL db_up = FALSE;
	QString adminstring_b;
	QString pwstring_b;
	while (g_ipserver->db_query->next())
	{
		adminstring_b = g_ipserver->db_query->value(1).toString();
		pwstring_b = g_ipserver->db_query->value(2).toString();
		strcpy(SadpInfo.szUserName, adminstring_b.toLatin1().data());
		strcpy(SadpInfo.szPassWord, pwstring_b.toLatin1().data());
		db_up = TRUE;
	}
	if(!db_up)
	{
		if (SadpInfo.szUserName[0] == '\0')
		{
			strcpy(SadpInfo.szUserName, "admin");
		}
		if (SadpInfo.szPassWord[0] == '\0')
		{
			strcpy(SadpInfo.szPassWord, "admin");
		}
	}
	//BOOL OnLine = g_ipserver->Login_dh((void*)&SadpInfo);
	pDeviceList->push_back(SadpInfo);
	//emit g_ipserver->TimerSingal((void*)&SadpInfo, 0);
	return;
}
//�����λص�����
void CALLBACK SearchDevicesCB_Searce(DEVICE_NET_INFO_EX *pDevNetInfo, void*  pUserData)
{
	if (NULL == pDevNetInfo | strncmp(pDevNetInfo->szDetailType, "JF-NC", 5) != 0 | pDevNetInfo->iIPVersion == 6)
	{
		printf("warning param is null\n");
		return;
	}
	DEVICE_NET_INFO_EX SadpInfo = { 0 };
	memcpy(&SadpInfo, pDevNetInfo, sizeof(DEVICE_NET_INFO_EX));
	std::vector<DEVICE_NET_INFO_EX>* pDeviceList = (std::vector<DEVICE_NET_INFO_EX>*)pUserData;
	for (std::vector<DEVICE_NET_INFO_EX>::iterator iter = g_lDeviceVec.begin(); iter != g_lDeviceVec.end(); ++iter)
	{
		if (strncmp(SadpInfo.szMac, iter->szMac, 40) == 0)
		{
			return;
		}
	}
	char db_char[200] = { '\0' };
	sprintf(db_char, "select * from Device_Sheet where ip='%s'", SadpInfo.szIP);
	g_ipserver->db_query->exec(db_char);
	BOOL db_up = FALSE;
	QString adminstring_b;
	QString pwstring_b;
	while (g_ipserver->db_query->next())
	{
		adminstring_b = g_ipserver->db_query->value(1).toString();
		pwstring_b = g_ipserver->db_query->value(2).toString();
		strcpy(SadpInfo.szUserName, adminstring_b.toLatin1().data());
		strcpy(SadpInfo.szPassWord, pwstring_b.toLatin1().data());
		db_up = TRUE;
	}
	if (!db_up)
	{
		if (SadpInfo.szUserName[0] == '\0')
		{
			strcpy(SadpInfo.szUserName, "admin");
		}
		if (SadpInfo.szPassWord[0] == '\0')
		{
			strcpy(SadpInfo.szPassWord, "admin");
		}
	}
	pDeviceList->push_back(SadpInfo);
	//emit g_ipserver->SearchSingal((void*)&SadpInfo, 2);
	return;
}
//�����ص� HK
void CALLBACK SearchDeviceHk(const SADP_DEVICE_INFO *lpDeviceInfo, void* pUserData)
{
	if (NULL == lpDeviceInfo|strncmp(lpDeviceInfo->szSerialNO,"JF-NC",5)!=0)
	{
		printf("warning param is null\n");
		return;
	}
	DeviceInfo_admin SadpInfo = { 0 };
	memcpy(&SadpInfo.hk_device_info, lpDeviceInfo, sizeof(SADP_DEVICE_INFO));
	std::vector<DeviceInfo_admin>* pDeviceList = (std::vector<DeviceInfo_admin>*)pUserData;
	for (std::vector<DeviceInfo_admin>::iterator iter = hk_lDeviceVec.begin(); iter != hk_lDeviceVec.end(); ++iter)
	{
		if (strncmp(SadpInfo.hk_device_info.szMAC ,iter->hk_device_info.szMAC,20)==0)
		{
			return;
		}
	}
	char db_char[200] = { '\0' };
	sprintf(db_char, "select * from Device_Sheet where ip='%s'", SadpInfo.hk_device_info.szIPv4Address);
	g_ipserver->db_query->exec(db_char);
	BOOL db_up = FALSE;
	QString adminstring_b;
	QString pwstring_b;
	while (g_ipserver->db_query->next())
	{
		adminstring_b = g_ipserver->db_query->value(4).toString();
		pwstring_b = g_ipserver->db_query->value(5).toString();
		strcpy(SadpInfo.hk_admin, adminstring_b.toLatin1().data());
		strcpy(SadpInfo.hk_pwchar, pwstring_b.toLatin1().data());
		db_up = true;
	}
	if(!db_up)
	{
		strcpy(SadpInfo.hk_admin, "admin");
	}
	pDeviceList->push_back(SadpInfo);
	//emit g_ipserver->TimerSingal((void*)&SadpInfo, 1);
	if (SadpInfo.hk_device_info.byActivated == 0)
	{
		SADP_ActivateDevice(SadpInfo.hk_device_info.szSerialNO, "admin");
	}
	return;
}
//��ʼ��
IPServer::IPServer(QWidget *parent)
	: QObject(parent)
{
	Thread_Search = new QThread();
	ThreadOperEntry *entry = new ThreadOperEntry();
	entry->moveToThread(Thread_Search);
	connect(Thread_Search, SIGNAL(started()), entry, SLOT(slot_search()));
	//connect(this, &JF_VRC::Sig_ExitChildThread, entry, &ThreadOperEntry::ExitCurrentThread, Qt::BlockingQueuedConnection);
	connect(entry, &ThreadOperEntry::signal_search, this, &IPServer::UpdateTransmitPanel,Qt::BlockingQueuedConnection);
	connect(Thread_Search, &QThread::finished, entry, &QObject::deleteLater);
	connect(Thread_Search, &QThread::finished, Thread_Search, &QObject::deleteLater);
	Thread_Search->start();


	int adden = GetCurrentThreadId();
	char work_path[_MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, work_path, _MAX_PATH);  //�õ�����ģ��.exeȫ·��  
													 //QString sExeFilePath = QDir::currentPath();
	QString sExeFilePath = QString::fromLocal8Bit(work_path);
	sExeFilePath.remove("SADPAndDeviceManager.exe");
	QByteArray byteArr = sExeFilePath.toLocal8Bit();
	byteArr.append("sadp.dll");

	moduleOfHC = LoadLibraryExA(byteArr.data(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (moduleOfHC)
	{
		SADP_Start_V30 = (sADP_Start_V30)GetProcAddress(moduleOfHC, "SADP_Start_V30");
		SADP_Stop = (sADP_Stop)GetProcAddress(moduleOfHC, "SADP_Stop");
		SADP_GetDeviceConfig = (sADP_GetDeviceConfig)GetProcAddress(moduleOfHC, "SADP_GetDeviceConfig");
		SADP_ModifyDeviceNetParam = (sADP_ModifyDeviceNetParam)GetProcAddress(moduleOfHC, "SADP_ModifyDeviceNetParam");
		SADP_GetLastError=(sADP_GetLastError)GetProcAddress(moduleOfHC, "SADP_GetLastError");
		SADP_ActivateDevice = (sADP_ActivateDevice)GetProcAddress(moduleOfHC, "SADP_ActivateDevice");
	}
	byteArr = sExeFilePath.toLocal8Bit();
	byteArr.append("dhnetsdk.dll");
	moduleOfHC = LoadLibraryExA(byteArr.data(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (moduleOfHC)
	{
		CLIENT_Init = (cLIENT_Init)GetProcAddress(moduleOfHC, "CLIENT_Init");
		CLIENT_InitEx = (cLIENT_InitEx)GetProcAddress(moduleOfHC, "CLIENT_InitEx");
		CLIENT_SetAutoReconnect = (cLIENT_SetAutoReconnect)GetProcAddress(moduleOfHC, "CLIENT_SetAutoReconnect");
		CLIENT_SetNetworkParam = (cLIENT_SetNetworkParam)GetProcAddress(moduleOfHC, "CLIENT_SetNetworkParam");
		CLIENT_SetConnectTime = (cLIENT_SetConnectTime)GetProcAddress(moduleOfHC, "CLIENT_SetConnectTime");
		CLIENT_SearchDevicesByIPs = (cLIENT_SearchDevicesByIPs)GetProcAddress(moduleOfHC, "CLIENT_SearchDevicesByIPs");
		CLIENT_StartSearchDevices = (cLIENT_StartSearchDevices)GetProcAddress(moduleOfHC, "CLIENT_StartSearchDevices");
		CLIENT_LoginEx2 = (cLIENT_LoginEx2)GetProcAddress(moduleOfHC, "CLIENT_LoginEx2");
		CLIENT_Logout = (cLIENT_Logout)GetProcAddress(moduleOfHC, "CLIENT_Logout");
		CLIENT_SetNewDevConfig = (cLIENT_SetNewDevConfig)GetProcAddress(moduleOfHC, "CLIENT_SetNewDevConfig");
		CLIENT_GetNewDevConfig = (cLIENT_GetNewDevConfig)GetProcAddress(moduleOfHC, "CLIENT_GetNewDevConfig");
		CLIENT_GetLastError = (cLIENT_GetLastError)GetProcAddress(moduleOfHC, "CLIENT_GetLastError");
		CLIENT_ModifyDevice = (cLIENT_ModifyDevice)GetProcAddress(moduleOfHC, "CLIENT_ModifyDevice");
	}
	byteArr = sExeFilePath.toLocal8Bit();
	byteArr.append("dhconfigsdk.dll");
	moduleOfHC = LoadLibraryExA(byteArr.data(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (moduleOfHC)
	{
		CLIENT_PacketData = (cLIENT_PacketData)GetProcAddress(moduleOfHC, "CLIENT_PacketData");
		CLIENT_ParseData = (cLIENT_ParseData)GetProcAddress(moduleOfHC, "CLIENT_ParseData");
	}
	byteArr = sExeFilePath.toLocal8Bit();
	byteArr.append("HCNetSDK.dll");
	moduleOfHC = LoadLibraryExA(byteArr.data(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (moduleOfHC)
	{
		NET_DVR_Login_V40 = (nET_DVR_Login_V40)GetProcAddress(moduleOfHC, "NET_DVR_Login_V40");
		NET_DVR_Logout = (nET_DVR_Logout)GetProcAddress(moduleOfHC, "NET_DVR_Logout");
		NET_DVR_Init = (nET_DVR_Init)GetProcAddress(moduleOfHC, "NET_DVR_Init");
		NET_DVR_SetReconnect = (nET_DVR_SetReconnect)GetProcAddress(moduleOfHC, "NET_DVR_SetReconnect");
		NET_DVR_GetDVRConfig = (nET_DVR_GetDVRConfig)GetProcAddress(moduleOfHC, "NET_DVR_GetDVRConfig");
		NET_DVR_SetDVRConfig = (nET_DVR_SetDVRConfig)GetProcAddress(moduleOfHC, "NET_DVR_SetDVRConfig");
		NET_DVR_GetLastError = (nET_DVR_GetLastError)GetProcAddress(moduleOfHC, "NET_DVR_GetLastError");
	}
	NET_DVR_Init();        //��ʼ��
	//NET_DVR_SetReconnect(2000, 0);
	BOOL Inta = CLIENT_InitEx(NULL, 0, NULL);
	//CLIENT_SetAutoReconnect(NULL, 0);
	NET_PARAM netParam = { 0 };
	netParam.nConnectTime = 2000;
	netParam.nConnectTryNum = 1;
	CLIENT_SetNetworkParam(&netParam);
	//���ݿ����Ӳ���
	sExeFilePath.append("data\\vrc.db");
	QByteArray byteArr_db = sExeFilePath.toLocal8Bit();
	db = nullptr;
	if (!db)
	{
		db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));

		if (!QFile::exists(byteArr_db.data()))
		{
			HANDLE dbHandle = CreateFileA(byteArr_db.data(), GENERIC_ALL, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, NULL, NULL);
			if (dbHandle != INVALID_HANDLE_VALUE)
			{
				isCreateTable = true;
				CloseHandle(dbHandle);
			}
		}
		db->setDatabaseName(byteArr_db.data());//�̶�λ��
		if (!db->open())
		{
			qDebug() << db->lastError();
		}
	}
	db_query = nullptr;
	if (!db_query)
	{
		db_query = new QSqlQuery(*db);
	}

	if (isCreateTable)
	{
		bool ab=db_query->exec("create table Device_Sheet(mold char(20) not null,series char(10) not null,ip char(15) not null primary key,port char(10) not null,admin_h varchar(255) not null,pw_h varchar(255) not null)");
		//db_query->exec("create table Device_Sheet(ip [not null] [primary key], admin_h [not null], pw_h [not null])");
	}
	//this->EquipmentSearch();
	g_ipserver = this;
	DWORD dwWaitTime = 5000;
	// �û���Ҫע�⣬�ýӿڻ�ȵ���ʱʱ�䵽ʱ�ŷ��أ��û���Ҫ���������������������ʱʱ��
	if (FALSE == CLIENT_StartSearchDevices(SearchDevicesCB, &g_lDeviceVec, NULL))
	{
		return;
	}

	//���������豸
	if (SADP_Start_V30(SearchDeviceHk, 1, &hk_lDeviceVec))
	{
	}
	
}
//��ʼ�����Ĳۺ���
void IPServer::EquipmentSearch()
{
	

}
//�޸�iP�Ի�����ʾ
void IPServer::WriteInformationToTable_dh(int state)
{
	//����������״̬
	if (state == 0)
	{
		//RowRecord[row] = -1;
		--CheckNumber;
	}
	else
	{
		//RowRecord[row] = 1;
		CheckNumber++;
	}
	return;
}
/** ��IPv4�ַ���ת��Ϊ��Ӧ�ĳ��������� */
LONG IPCString2DWORD(char* ip) 
{
	int IPV1 = 0;
	int IPV2 = 0;
	int IPV3 = 0;
	int IPV4 = 0;
	sscanf_s(ip, "%3d.%3d.%3d.%3d", &IPV1, &IPV2, &IPV3, &IPV4);
	unsigned long ipLong = 0;
	ipLong = IPV1 << 24;
	ipLong += IPV2 << 16;
	ipLong += IPV3 << 8;
	ipLong += IPV4 ;
	return ipLong;
}
void LONGToIPChar(char*IP, unsigned long IPlong)
{
	int IPV1 = 0;
	int IPV2 = 0;
	int IPV3 = 0;
	int IPV4 = 0;
	IPV1 = IPlong >> 24;
	IPV2 = (IPlong >> 16) & 255;
	IPV3 = (IPlong >> 8) & 255;
	IPV4 = IPlong & 255;
	sprintf(IP, "%d.%d.%d.%d", IPV1, IPV2, IPV3, IPV4);

}
void IPServer::ModifiyLine()
{
	//this->LogOutputMessage->append(QStringLiteral("�޸�IP��ʼ��"));
	int numshu = 0;
	QString OldIPstring = "";
	QString Portstring="";
	QString NewIPstring="";
	QString PasswdString="";
	QString KvStype = "";
	QByteArray NewIPByte = "";
	char* NewIpchar=new char[17];
	char Passwdchar[20];
	RtlZeroMemory(NewIpchar,17);
	LLONG g_lLogin=0;
	BOOL ret=FALSE;
	int error;
	//ping IP �Ƿ���Ч
	//QProcess cmd;
	unsigned long IPs;
	QString AdminString = "";
	strcpy(Passwdchar, PasswdString.toLatin1().data());
	NewIPByte = NewIPstring.toLocal8Bit();
	strcpy(NewIpchar, NewIPByte.data());
	QString PingChar = "";
	QString outlog;

	NET_DEVICEINFO_Ex stuInfo = { 0 };
	int nError = 0;
	int nSpecialValue = 90106;
	int aerror;
	QTableWidgetItem *item = new QTableWidgetItem();
	DEVICE_NET_INFO_EX SadpInfo = { 0 };
	//memcpy(&SadpInfo, Device_d, sizeof(DEVICE_NET_INFO_EX));
	//LLONG g_lLogin;
	//��¼
	QString KVty = "";
	QString IPString = "";
	QString PortString = "";
	QString PwString = "";
	
	QByteArray IPByte = "";
	QByteArray PWByte = "";
	QByteArray AdminByte = "";
	QByteArray PortByte = "";
	AdminByte = AdminString.toLatin1();
	NET_DVR_USER_LOGIN_INFO  plogininfo = { 0 };
	NET_DVR_DEVICEINFO_V40 HikDeviceInfo_V40 = { 0 };
	char db_char[200];
	RtlZeroMemory(&plogininfo, sizeof(NET_DVR_USER_LOGIN_INFO));
	RtlZeroMemory(&HikDeviceInfo_V40, sizeof(NET_DVR_DEVICEINFO_V40));
//	for (int i = 0; i < DeviceSheet->rowCount(); i++)
//	{
//		if (((QCheckBox*)DeviceSheet->cellWidget(i, 0))->checkState() == Qt::Checked|(CheckNumber==0&&i==DoubleRow))
//		{
//			OldIPstring=this->DeviceSheet->item(i, 3)->text();
//			Portstring = this->DeviceSheet->item(i, 6)->text();
//			if (NewIPstring.isEmpty()|NewIPstring==OldIPstring)
//			{
//				KVty = this->DeviceSheet->item(i, 1)->text();
//				//PortString = this->DeviceSheet->item(i, 7)->text();
//				IPByte = OldIPstring.toLatin1();
//				PortByte = Portstring.toLatin1();
//				PWByte = PwString.toLatin1();
//				if (strcmp(KVty.toLocal8Bit(), "Kϵ") == 0)
//				{
//					g_lLogin = CLIENT_LoginEx2(IPByte.data(), PortByte.toInt(), AdminByte.data(), PWByte.data(), (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
//					if (g_lLogin == 0)
//					{
//						Sleep(100);
//						nError = CLIENT_GetLastError()&(0x7fffffff);
//						nSpecialValue = 90106;
//						g_lLogin = CLIENT_LoginEx2(IPByte.data(), PortByte.toInt(), AdminByte.data(), PWByte.data(), (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
//						if(g_lLogin==0)
//						{
//							Sleep(100);
//							nError = CLIENT_GetLastError()&(0x7fffffff);
//							g_lLogin = CLIENT_LoginEx2(IPByte.data(), PortByte.toInt(), AdminByte.data(), PWByte.data(), (EM_LOGIN_SPAC_CAP_TYPE)0, NULL, &stuInfo, &nError);
//							if (0 == g_lLogin)
//							{
//								this->DeviceSheet->setItem(i, 9, new QTableWidgetItem(QString::fromLocal8Bit("��¼ʧ��")));
//								outlog = OldIPstring;
//								outlog += QStringLiteral("<font color = 'red'>��¼ʧ��< / font> ԭ��:");
//								nError = CLIENT_GetLastError()&(0x7fffffff);
//								outlog += QString::number(nError, 10);
//								this->LogOutputMessage->append(outlog);
//								outlog.clear();
//								continue;
//							}
//						}
//					}
//					if (g_lLogin != 0)
//					{
//						this->DeviceSheet->setItem(i, 9, new QTableWidgetItem(QString::fromLocal8Bit("��¼�ɹ�")));
//						outlog = OldIPstring;
//						outlog += QStringLiteral("��¼�ɹ�");
//						this->LogOutputMessage->append(outlog);
//						outlog.clear();
//						sprintf(db_char, "select * from Device_Sheet where ip='%s'", OldIPstring.toLatin1().data());
//						db_query->exec(db_char);
//						BOOL db_up = FALSE;
//						while (db_query->next())
//						{
//							RtlZeroMemory(db_char, 200);
//							sprintf(db_char, "update Device_Sheet set admin_h='%s',pw_h='%s' where ip='%s'", AdminByte.data(), PWByte.data(), OldIPstring.toLatin1().data());
//							db_query->exec(db_char);
//							db_up = TRUE;
//						}
//
//						if (!db_up)
//						{
//							RtlZeroMemory(db_char, 200);
//							sprintf(db_char, "insert into Device_Sheet(ip,admin_h,pw_h) values('%s','%s','%s')", OldIPstring.toLatin1().data(), AdminByte.data(), PWByte.data());
//							bool adc = db_query->exec(db_char);
//						}
//						this->DeviceSheet->setItem(i, 8, new QTableWidgetItem(PwString));
//						for (std::vector<DEVICE_NET_INFO_EX>::iterator iter = g_lDeviceVec.begin(); iter != g_lDeviceVec.end(); ++iter)
//						{
//							if (strncmp(this->DeviceSheet->item(i, 10)->text().toLatin1().data(), iter->szMac, 40) == 0)
//							{
//								strcpy(iter->szUserName, AdminByte.data());
//								strcpy(iter->szPassWord, PWByte.data());
//								break;
//							}
//						}
//						continue;
//					}
//				}
//				if (strcmp(KVty.toLocal8Bit(), "Vϵ") == 0)
//				{
//					memcpy_s(plogininfo.sDeviceAddress, 129, IPByte.data(), 16);
//					memcpy_s(plogininfo.sPassword, 64, PWByte.data(), 64);
//					strcpy(plogininfo.sUserName, AdminByte.data());
//					plogininfo.wPort = PortByte.toInt();
//					plogininfo.bUseAsynLogin = 0;
//					plogininfo.byJiaFaEncypt = 2;
//					g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
//					if (g_lLogin == -1)
//					{
//						plogininfo.byJiaFaEncypt = 1;
//						g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
//						if (g_lLogin == -1)
//						{
//							plogininfo.byJiaFaEncypt = 0;
//							g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
//							if (g_lLogin == -1)
//							{
//								this->DeviceSheet->setItem(i, 9, new QTableWidgetItem(QString::fromLocal8Bit("��¼ʧ��")));
//								outlog = OldIPstring;
//								outlog += QStringLiteral("<font color = 'red'>��¼ʧ��< / font> ԭ��:");
//								nError = NET_DVR_GetLastError();
//								outlog += QString::number(nError, 10);
//								this->LogOutputMessage->append(outlog);
//								outlog.clear();
//								continue;
//							}
//						}
//					}
//					if (g_lLogin != -1)
//					{
//						this->DeviceSheet->setItem(i, 9, new QTableWidgetItem(QString::fromLocal8Bit("��¼�ɹ�")));
//						outlog = OldIPstring;
//						outlog += QStringLiteral("��¼�ɹ�");
//						this->LogOutputMessage->append(outlog);
//						sprintf(db_char, "select * from Device_Sheet where ip='%s'", OldIPstring.toLatin1().data());
//						db_query->exec(db_char);
//						BOOL db_up = FALSE;
//						while (db_query->next())
//						{
//							RtlZeroMemory(db_char, 200);
//							sprintf(db_char, "update Device_Sheet set admin_h='%s',pw_h='%s' where ip='%s'", AdminByte.data(), PWByte.data(), OldIPstring.toLatin1().data());
//							db_query->exec(db_char);
//							db_up = TRUE;
//						}
//						
//						if (!db_up)
//						{
//							RtlZeroMemory(db_char, 200);
//							sprintf(db_char, "insert into Device_Sheet(ip,admin_h,pw_h) values('%s','%s','%s')", OldIPstring.toLatin1().data(), AdminByte.data(), PWByte.data());
//							bool adc=db_query->exec(db_char);
//						}
//						outlog.clear();
//						this->DeviceSheet->setItem(i, 8, new QTableWidgetItem(PwString));
//						for (std::vector<DeviceInfo_admin>::iterator iter = hk_lDeviceVec.begin(); iter != hk_lDeviceVec.end(); ++iter)
//						{
//							if (strncmp(this->DeviceSheet->item(i, 10)->text().toLatin1().data(), iter->hk_device_info.szMAC, 20) == 0)
//							{
//								strcpy(iter->hk_admin, AdminByte.data());
//								strcpy(iter->hk_pwchar, PWByte.data());
//								break;
//							}
//						}
//						continue;
//					}
//				}
//			}
//			KvStype = this->DeviceSheet->item(i, 1)->text();
//			if (strcmp(KvStype.toLocal8Bit().data(), "Kϵ") == 0)
//			{
//				for (std::vector<DEVICE_NET_INFO_EX>::iterator iter = g_lDeviceVec.begin(); iter != g_lDeviceVec.end(); ++iter)
//				{
//					if (strncmp(OldIPstring.toLatin1().data(), iter->szIP, 64) == 0)
//					{
//						PingChar+= "ping";
//						PingChar+=" ";
//						PingChar+= QString(NewIpchar);
//						PingChar += "-w 1000";
//						cmd.start(PingChar);
//						cmd.waitForReadyRead(1000);
//						cmd.waitForFinished(1000);
//						QString response = cmd.readAllStandardOutput();
//						if (response.indexOf("TTL") == -1)
//						{
//							//�޸�IP
//							strcpy(iter->szIP, NewIpchar);
//							strcpy(iter->szUserName, AdminByte.data());
//							strcpy(iter->szPassWord, Passwdchar);
//							ret = CLIENT_ModifyDevice(&(DEVICE_NET_INFO_EX)*iter, 5000, &error, NULL, NULL);
//							if (ret == FALSE)
//							{
//								outlog = OldIPstring;
//								outlog += QStringLiteral("<font color = 'red'>�޸�ʧ��< / font> ԭ��:");
//								nError = CLIENT_GetLastError()&(0x7fffffff);
//								outlog += QString::number(nError, 10);
//								this->LogOutputMessage->append(outlog);
//								outlog.clear();
//								strcpy(iter->szIP, OldIPstring.toLatin1().data());
//								strcpy(iter->szUserName, this->DeviceSheet->item(i, 7)->text().toLatin1().data());
//								strcpy(iter->szPassWord, this->DeviceSheet->item(i, 8)->text().toLatin1().data());
//							}else
//							{
//								outlog = OldIPstring;
//								outlog += QStringLiteral("�޸ĳɹ�");
//								this->LogOutputMessage->append(outlog);
//								outlog.clear();
//								this->DeviceSheet->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit(NewIpchar)));
//								this->DeviceSheet->setItem(i, 7, new QTableWidgetItem(QString::fromLocal8Bit(AdminByte.data())));
//								this->DeviceSheet->setItem(i, 8, new QTableWidgetItem(QString::fromLocal8Bit(Passwdchar)));
//								for (std::vector<DEVICE_NET_INFO_EX>::iterator iter = g_lDeviceVec.begin(); iter != g_lDeviceVec.end(); ++iter)
//								{
//									if (strncmp(this->DeviceSheet->item(i, 10)->text().toLatin1().data(), iter->szMac, 40) == 0)
//									{
//										strcpy(iter->szIP, NewIpchar);
//										strcpy(iter->szUserName,AdminByte.data());
//										strcpy(iter->szPassWord, Passwdchar);
//										break;
//									}
//								}
//							}
//						}
//						else
//						{
//							outlog = NewIPstring;
//							outlog += QStringLiteral("<font color = 'red'>��ռ��< / font>");
//							this->LogOutputMessage->append(outlog);
//							outlog.clear();
//						}
//						response.clear();
//						IPs = IPCString2DWORD(NewIpchar);
//						IPs++;
//						LONGToIPChar(NewIpchar, IPs);
//						NewIPstring = QString::fromLocal8Bit(NewIpchar);
//						PingChar.clear();
//						break;
//					}
//				}
//			}
//			if (ret)
//			{
//				ret = 0;
//				continue;
//			}
//			SADP_DEV_NET_PARAM ModifiyStruct = { 0 };
//			if (strcmp(KvStype.toLocal8Bit().data(), "Vϵ") == 0)
//			{
//				for (std::vector<DeviceInfo_admin>::iterator iter = hk_lDeviceVec.begin(); iter != hk_lDeviceVec.end(); ++iter)
//				{
//					if (strncmp(OldIPstring.toLatin1().data(), iter->hk_device_info.szIPv4Address, 16) == 0)
//					{
//						strcpy(ModifiyStruct.szIPv4Address, NewIpchar);
//						if (iter->hk_device_info.szIPv4Gateway[0]=='\0'|strncmp(iter->hk_device_info.szIPv4Gateway,"0.0.0.0",16)==0)
//						{
//							strcpy(ModifiyStruct.szIPv4Gateway, this->InputEdit[1]->text().toLocal8Bit().data());
//						}
//						else 
//						{
//							strcpy(ModifiyStruct.szIPv4Gateway, iter->hk_device_info.szIPv4Gateway);
//						}
//						if (iter->hk_device_info.szIPv4SubnetMask[0]=='\0'|strncmp(iter->hk_device_info.szIPv4SubnetMask,"0.0.0.0",16)==0)
//						{
//							strcpy(ModifiyStruct.szIPv4SubNetMask,this->InputEdit[2]->text().toLocal8Bit().data());
//						}
//						else
//						{
//							strcpy(ModifiyStruct.szIPv4SubNetMask, iter->hk_device_info.szIPv4SubnetMask);
//						}
//						strcpy(ModifiyStruct.szIPv6Address, iter->hk_device_info.szIPv6Address);
//						strcpy(ModifiyStruct.szIPv6Gateway, iter->hk_device_info.szIPv6Gateway);
//						ModifiyStruct.wPort = iter->hk_device_info.dwPort;
//						ModifiyStruct.byIPv6MaskLen = iter->hk_device_info.byIPv6MaskLen;
//						ModifiyStruct.byDhcpEnable = iter->hk_device_info.byDhcpEnabled;
//						ModifiyStruct.wHttpPort = iter->hk_device_info.wHttpPort;
//						PingChar += "ping";
//						PingChar += " ";
//						PingChar += QString(NewIpchar);
//						PingChar += "-w 1000";
//						cmd.start(PingChar);
//						cmd.start(PingChar);
//						cmd.waitForReadyRead(1000);
//						cmd.waitForFinished(1000);
//						QString response = cmd.readAllStandardOutput();
//						if (response.indexOf("TTL") == -1)
//						{
//							ret = SADP_ModifyDeviceNetParam(iter->hk_device_info.szMAC, Passwdchar, &ModifiyStruct);
//							if (ret == FALSE)
//							{
//								outlog = OldIPstring;
//								outlog += QStringLiteral("<font color = 'red'>�޸�ʧ��< / font> ԭ��:");
//								error = SADP_GetLastError();
//								outlog += QString::number(error, 10);
//								this->LogOutputMessage->append(outlog);
//								outlog.clear();
//							}
//							else
//							{
//								outlog = OldIPstring;
//								outlog += QStringLiteral("�޸ĳɹ�");
//								this->LogOutputMessage->append(outlog);
//								outlog.clear();
//								this->DeviceSheet->setItem(i, 3, new QTableWidgetItem(QString::fromLocal8Bit(NewIpchar)));
//								this->DeviceSheet->setItem(i, 7, new QTableWidgetItem(QString::fromLocal8Bit(AdminByte.data())));
//								this->DeviceSheet->setItem(i, 8, new QTableWidgetItem(QString::fromLocal8Bit(Passwdchar)));
//								for (std::vector<DeviceInfo_admin>::iterator iter = hk_lDeviceVec.begin(); iter != hk_lDeviceVec.end(); ++iter)
//								{
//									if (strncmp(this->DeviceSheet->item(i, 10)->text().toLatin1().data(), iter->hk_device_info.szMAC, 20) == 0)
//									{
//										strcpy(iter->hk_device_info.szIPv4Address, NewIpchar);
//										strcpy(iter->hk_admin, AdminByte.data());
//										strcpy(iter->hk_pwchar, Passwdchar);
//										break;
//									}
//								}
//							}
//						}
//						else
//						{
//							outlog = NewIPstring;
//							outlog += QStringLiteral("<font color = 'red'>��ռ��< / font>");
//							this->LogOutputMessage->append(outlog);
//							outlog.clear();
//						}
//						response.clear();
//						IPs = IPCString2DWORD(NewIpchar);
//						IPs++;
//						LONGToIPChar(NewIpchar, IPs);
//						ret = 0;
//						NewIPstring = QString::fromLocal8Bit(NewIpchar);
//						PingChar.clear();
//						break;
//					}
//				}
//			}
//		}
//		
//	}
}
//�������
void IPServer::ExportFunction()
{
	QScopedPointer<ExcelBase> m_xls;
	if (m_xls.isNull())
		m_xls.reset(new ExcelBase);
	QString filepath = QFileDialog::getSaveFileName((QWidget *)this, QStringLiteral("���Ϊ"), ".", tr("*.xlsx *.xls"));//��ȡ����·��
	if (!m_xls->create(filepath))//����ʧ��,����
	{
		//emit Signal_progressBar();
		QMessageBox::warning(NULL, QStringLiteral("��ʾ"),QStringLiteral("����ʧ��!"), QMessageBox::Ok);
		return;
	}
	m_xls->setCurrentSheet(1);
	m_xls->SetFreezeSelCell(1, 2);

	//�����û����ģ��
	int rowStart = 1;
	int mergeRow = 0;
	int row = 1;
	int tmp = 1;

	//��¼Ҫ�����ĵ�Ԫ��
	QList<QList<QVariant>> m_datas;
	QList<QVariant> rows;

	rows <<QStringLiteral("ϵ��")<< QStringLiteral("IP") <<QStringLiteral("�˿�")<< QStringLiteral("OSD")<<QStringLiteral("���к�");
	m_datas.append(rows);
	rows.clear();
	int IPcd=0;
	/*for (int i = 0; i < DeviceSheet->rowCount(); i++)
	{
		if (((QCheckBox*)DeviceSheet->cellWidget(i, 0))->checkState() == Qt::Checked)
		{
			rows <<this->DeviceSheet->item(i,1)->text()<< this->DeviceSheet->item(i, 3)->text() << this->DeviceSheet->item(i, 6)->text()<< "" << this->DeviceSheet->item(i, 12)->text();
			m_datas.append(rows);
			rows.clear();
		}
		
	}*/
	m_xls->writeCurrentSheet(m_datas);
	m_xls->save();
	m_xls->close();
	//this->LogOutputMessage->append(QStringLiteral("����������"));

}
//������
void IPServer::ImportFunction()
{
	QString filepathStr = QFileDialog::getOpenFileName((QWidget *)this, QStringLiteral("ѡ���ļ�"), ".", tr("*.xlsx *.xls"));
	if (filepathStr.isEmpty())
	{
		return;
	}
	int Lostshu = 0;
	QScopedPointer<ExcelBase> m_xls;
	QList< QList<QVariant> > m_datas;
	//��ѯ����
	if (m_xls.isNull())
		m_xls.reset(new ExcelBase);
	m_xls->open(filepathStr);
	m_xls->setCurrentSheet(1);
	m_xls->readAll(m_datas);
	//��������������
	NET_DEVICEINFO_Ex stuInfo = { 0 };
	int nError = 0;
	int nSpecialValue = 90106;
	int aerror;
	LLONG g_lLogin = 0;
	AV_CFG_ChannelName stInfo = { sizeof(stInfo) };
	char ALLchar[256] = { 0 };
	int allLen;
	int nBufSize = 1024 * 1024;
	char* pBuf = new char[nBufSize];
	RtlZeroMemory(pBuf, nBufSize);
	int nerror;
	NET_DVR_USER_LOGIN_INFO  plogininfo = {0};
	NET_DVR_DEVICEINFO_V40 HikDeviceInfo_V40 = {0};
	NET_DVR_PICCFG_V40 OSD_Struct = {0};
	DWORD sizeout;
	int ret;
	QString IPString="";
	QString PortString="";
	QString PwString="";
	QString OSDString = "";
	QString KvStype = "";
	QByteArray IPByte = "";
	QByteArray PWByte = "";
	QByteArray OSDByte="";
	QByteArray PortByte = "";
	char* bachar = NULL;
	BOOL bSuccess=TRUE;
	LONG hk_login = 0;
	int aSuccess=0;
	char IPv4char[17];
	char PWchar[17];
	char Userchar[20] = "";
	DWORD PortDwr = 0;
	RtlZeroMemory(IPv4char, 16);
	RtlZeroMemory(PWchar,16);
	QString outLog;
	QRegularExpressionMatch match;
	for (int i = 1; i < m_datas.length(); i++)
	{
		KvStype = m_datas.at(i).at(0).toString();
		IPString = m_datas.at(i).at(1).toString();
		PortString = m_datas.at(i).at(2).toString();
		OSDString = m_datas.at(i).at(3).toString();
		IPByte = IPString.toLatin1();
		PortByte = PortString.toLatin1();
		OSDByte = OSDString.toLocal8Bit();
		if (strcmp(KvStype.toLocal8Bit().data(), "Kϵ")==0)
		{
			for (std::vector<DEVICE_NET_INFO_EX>::iterator iter = g_lDeviceVec.begin(); iter != g_lDeviceVec.end(); ++iter)
			{
				if (strncmp(IPString.toLatin1().data(), iter->szIP, 64) == 0)
				{
					strcpy(IPv4char, IPByte.data());
					strcpy(PWchar, iter->szPassWord);
					strcpy(Userchar, iter->szUserName);
					if (iter->szPassWord[0]=='\0'|iter->szUserName[0]=='\0')
					{
						outLog = IPString;
						outLog += QStringLiteral("<font color = 'red'>�û�����������Ϊ��< / font> ");
						//this->LogOutputMessage->append(outLog);
						outLog.clear();
						continue;
					}
					PortDwr = atoi(PortString.toLatin1().data());
					g_lLogin = CLIENT_LoginEx2(IPv4char, PortDwr, Userchar, PWchar, (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
					if (g_lLogin == 0)
					{
						Sleep(100);
						nError = CLIENT_GetLastError()&(0x7fffffff);
						nSpecialValue = 90106;
						g_lLogin = CLIENT_LoginEx2(IPv4char, PortDwr, Userchar, PWchar, (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
						if (g_lLogin == 0)
						{
							Sleep(100);
							nError = CLIENT_GetLastError()&(0x7fffffff);
							g_lLogin = CLIENT_LoginEx2(IPv4char, PortDwr, Userchar, PWchar, (EM_LOGIN_SPAC_CAP_TYPE)0, NULL, &stuInfo, &nError);
							if (0 == g_lLogin)
							{
								outLog = IPString;
								outLog += QStringLiteral("<font color = 'red'>��¼ʧ��< / font> ԭ��:");
								nError = CLIENT_GetLastError()&(0x7fffffff);
								outLog += QString::number(nError, 10);
								//this->LogOutputMessage->append(outLog);
								outLog.clear();
								Lostshu++;
								goto loookset;
							}
						}
					}
					bachar = OSDByte.data();
					memcpy_s(ALLchar, 256, bachar, 64);
					allLen = strlen(ALLchar);
					memset(pBuf, 0, nBufSize);
					stInfo.nStructSize = sizeof(stInfo);
					memcpy_s(stInfo.szName, 256, ALLchar, allLen);
					if (CLIENT_PacketData(CFG_CMD_CHANNELTITLE, &stInfo, sizeof(stInfo), pBuf, nBufSize))
					{
						ret = CLIENT_SetNewDevConfig(g_lLogin, CFG_CMD_CHANNELTITLE, 0, pBuf, nBufSize, &nerror, &aSuccess, 8000);
						if (0 == ret)
						{
							Lostshu++;
							outLog = IPString;
							outLog += QStringLiteral("<font color = 'red'>����OSDʧ��< / font> ԭ��;");
							nError = CLIENT_GetLastError()&(0x7fffffff);
							outLog += QString::number(nError, 10);
							//this->LogOutputMessage->append(outLog);
							outLog.clear();	
						}
						else
						{
							outLog = IPString;
							outLog += QStringLiteral("���óɹ�");
							//this->LogOutputMessage->append(outLog);
							outLog.clear();
						}

					}
					else
					{
						Lostshu++;
						outLog = IPString;
						outLog += QStringLiteral("<font color = 'red'>����ת��ʧ��< / font> ԭ��:");
						nError = CLIENT_GetLastError()&(0x7fffffff);
						outLog += QString::number(nError, 10);
						//this->LogOutputMessage->append(outLog);
						outLog.clear();
					}
					if (g_lLogin)
					{
						CLIENT_Logout(g_lLogin);
					}
					break;
				}
			}
		}
		if (g_lLogin)
		{
loookset:	g_lLogin = 0;
			continue;
		}
		if (strcmp(KvStype.toLocal8Bit().data(), "Vϵ") == 0)
		{
			for (std::vector<DeviceInfo_admin>::iterator iter = hk_lDeviceVec.begin(); iter != hk_lDeviceVec.end(); ++iter)
			{
				if (strncmp(IPString.toLatin1().data(), iter->hk_device_info.szIPv4Address, 16) == 0)
				{
					RtlZeroMemory(&plogininfo, sizeof(NET_DVR_USER_LOGIN_INFO));
					RtlZeroMemory(&HikDeviceInfo_V40, sizeof(NET_DVR_DEVICEINFO_V40));
					strcpy(IPv4char, IPByte.data());
					if (iter->hk_admin[0] == '\0' | iter->hk_pwchar[0] == '\0')
					{
						outLog = IPString;
						outLog += QStringLiteral("<font color = 'red'>�û�����������Ϊ��< / font> ");
						//this->LogOutputMessage->append(outLog);
						outLog.clear();
						continue;
					}
					strcpy(PWchar, iter->hk_pwchar);
					strcpy(Userchar, iter->hk_admin);
					PortDwr = atoi(PortString.toLatin1().data());
					memcpy_s(plogininfo.sDeviceAddress, 129, IPv4char, 16);
					memcpy_s(plogininfo.sPassword, 64, PWchar, 64);
					strcpy(plogininfo.sUserName, iter->hk_admin);
					plogininfo.wPort = PortDwr;
					plogininfo.bUseAsynLogin = 0;
					plogininfo.byJiaFaEncypt = 2;
					hk_login = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
					if (hk_login == -1)
					{
						plogininfo.byJiaFaEncypt = 1;
						hk_login = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
						if (hk_login==-1)
						{
							plogininfo.byJiaFaEncypt = 0;
							hk_login = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
							if (hk_login == -1)
							{
								Lostshu++;
								outLog = IPString;
								outLog += QStringLiteral("<font color='red'>��¼ʧ��</font> ԭ��:");
								nError = NET_DVR_GetLastError();
								outLog += QString::number(nError, 10);
								//this->LogOutputMessage->append(outLog);
								outLog.clear();
								break;
							}
						}	
					}
					ret = NET_DVR_GetDVRConfig(hk_login, NET_DVR_GET_PICCFG_V40, 1, (void*)&OSD_Struct, sizeof(OSD_Struct), &sizeout);
					if (ret)
					{
						memcpy_s((char*)OSD_Struct.sChanName, 32, OSDByte.data(), 32);
					}
					else
					{
						Lostshu++;
						outLog = IPString;
						outLog += QStringLiteral("<font color='red'>��ȡ��Ϣʧ��</font> ԭ��:");
						nError = NET_DVR_GetLastError();
						outLog += QString::number(nError, 10);
						//this->LogOutputMessage->append(outLog);
						outLog.clear();
						g_lLogin = 0;
						break;
					}
					ret = NET_DVR_SetDVRConfig(hk_login, NET_DVR_SET_PICCFG_V40, 1, &OSD_Struct, sizeof(NET_DVR_PICCFG_V40));
					if (ret)
					{
						outLog = IPString;
						outLog += QStringLiteral("���óɹ�");
						//this->LogOutputMessage->append(outLog);
						outLog.clear();
					}
					else
					{
						Lostshu++;
						outLog = IPString;
						outLog += QStringLiteral("<font color='red'>����ʧ��</font> ԭ��:");
						nError = NET_DVR_GetLastError();
						outLog+= QString::number(nError, 10);
						//this->LogOutputMessage->append(outLog);
						outLog.clear();
					}
					if (hk_login != -1)
					{
						NET_DVR_Logout(hk_login);
					}
					g_lLogin = 0;
					break;
				}
			}
		}
	}
	m_xls->close();
	//this->LogOutputMessage->append(QStringLiteral("���������"));
}
//�ֶ���ӶԻ�����ʾ
void IPServer::ManualAddDeviceFunc()
{
	
}
//�ֶ���ӵĲۺ���
void IPServer::ManualAddDfunc() 
{
	
	/*QString TypeString= DeviceTypeBox->currentText();
	QByteArray TypeByte = TypeString.toLocal8Bit();
	QString ManualIPstring = DeviceEdit[0]->text();
	QString ManualPortstring = DeviceEdit[1]->text();
	QString ManualAdminstring = DeviceEdit[2]->text();
	QString ManualPasswstring= DeviceEdit[3]->text();
	IPstringofhand = DeviceEdit[0]->text();
	Portstringofhand = DeviceEdit[1]->text();
	Adminstrngofhand = DeviceEdit[2]->text();
	Pawwsdstringofhand = DeviceEdit[3]->text();
	if (ManualAdminstring.isEmpty()==TRUE|ManualPasswstring.isEmpty()==TRUE)
	{
		this->LogOutputMessage->append(QString::fromLocal8Bit("�û�����������Ϊ��"));
		return;
	}
	this->ManualAddDeviceDialog->hide();
	QByteArray ManualIPbyte = ManualIPstring.toLocal8Bit();
	QByteArray ManualPortbyte = ManualPortstring.toLatin1();
	QByteArray ManuslAdminbyte = ManualAdminstring.toLatin1();
	QByteArray ManualPasswbyte = ManualPasswstring.toLocal8Bit();
	char ManualIPchar[17];
	DWORD ManualPortchar = atoi(ManualPortstring.toLatin1().data());
	char ManualUserchar[16];
	char ManualPwchar[16];
	RtlZeroMemory(ManualIPchar, 17);
	RtlZeroMemory(ManualPwchar, 16);
	RtlZeroMemory(ManualUserchar, 16);
	strcpy(ManualIPchar, ManualIPbyte.data());
	strcpy(ManualUserchar, ManuslAdminbyte.data());
	strcpy(ManualPwchar, ManualPasswbyte.data());
	LLONG g_lLogin = 0;
	int nSpecialValue = 90106;
	NET_DEVICEINFO_Ex stuInfo = { 0 };
	int nError = 0;
	NET_DVR_USER_LOGIN_INFO  plogininfo = { 0 };
	NET_DVR_DEVICEINFO_V40 HikDeviceInfo_V40 = { 0 };
	BOOL hk_login=FALSE;
	QString outLog;
	char db_char[200] = { '\0' };
	if (strcmp(TypeByte.data(),"Kϵ")==0)
	{
		g_lLogin = CLIENT_LoginEx2(ManualIPchar, ManualPortchar, ManualUserchar, ManualPwchar, (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
		if (g_lLogin == 0)
		{
			Sleep(100);
			nSpecialValue = 90106;
			g_lLogin = CLIENT_LoginEx2(ManualIPchar, ManualPortchar, ManualUserchar, ManualPwchar, (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
			if (g_lLogin == 0)
			{
				Sleep(100);
				g_lLogin = CLIENT_LoginEx2(ManualIPchar, ManualPortchar, ManualUserchar, ManualPwchar, (EM_LOGIN_SPAC_CAP_TYPE)0, NULL, &stuInfo, &nError);
				if (0 == g_lLogin)
				{
					outLog = ManualIPstring;
					outLog += QStringLiteral("<font color='red'>��¼ʧ��</font> ԭ��:");
					nError = CLIENT_GetLastError()&(0x7fffffff);
					outLog += QString::number(nError, 10);
					this->LogOutputMessage->append(outLog);
					outLog.clear();
					return;
				}
			}
		}
		if (g_lLogin)
		{
			DEVICE_NET_INFO_EX ManualStruct = { 0 };
			strcpy(ManualStruct.szIP, ManualIPchar);
			strcpy(ManualStruct.szSerialNo, (const char*)stuInfo.sSerialNumber);
			strcpy(ManualStruct.szUserName, ManualUserchar);
			strcpy(ManualStruct.szPassWord, ManualPwchar);
			ManualStruct.iIPVersion = 4;
			ManualStruct.nPort = ManualPortchar;
			g_lDeviceVec.push_back(ManualStruct);
			g_ipserver->TimerSlotd((void*)&ManualStruct, 0);
			outLog = ManualIPstring;
			sprintf(db_char, "select * from Device_Sheet where ip='%s'", ManualIPchar);
			db_query->exec(db_char);
			BOOL db_up = FALSE;
			while (db_query->next())
			{
				RtlZeroMemory(db_char, 200);
				sprintf(db_char, "update Device_Sheet set admin_h='%s',pw_h='%s' where ip='%s'", ManualUserchar, ManualPwchar, ManualIPchar);
				db_query->exec(db_char);
				db_up = TRUE;
			}
			if (!db_up)
			{
				RtlZeroMemory(db_char, 200);
				sprintf(db_char, "insert into Device_Sheet(ip,admin_h,pw_h) values('%s','%s','%s'", ManualIPchar, ManualUserchar, ManualPwchar);
				db_query->exec(db_char);
			}
			outLog += QStringLiteral("��¼�ɹ�");
			this->LogOutputMessage->append(outLog);
			outLog.clear();
		}
	}
	else if (strcmp(TypeByte.data(), "Vϵ") == 0)
	{
		RtlZeroMemory(&plogininfo, sizeof(NET_DVR_USER_LOGIN_INFO));
		RtlZeroMemory(&HikDeviceInfo_V40, sizeof(NET_DVR_DEVICEINFO_V40));
		memcpy_s(plogininfo.sDeviceAddress, 129, ManualIPchar, 16);
		memcpy_s(plogininfo.sPassword, 64, ManualPwchar, 64);
		strcpy(plogininfo.sUserName, ManualUserchar);
		plogininfo.wPort = ManualPortchar;
		plogininfo.bUseAsynLogin = 0;
		plogininfo.byJiaFaEncypt = 2;
		g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
		if(g_lLogin==-1)
		{
			plogininfo.byJiaFaEncypt = 1;
			g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
			if(g_lLogin==-1)
			{
				plogininfo.byJiaFaEncypt = 0;
				g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
				if(g_lLogin==-1)
				{
					outLog = ManualIPstring;
					outLog += QStringLiteral("<font color='red'>��¼ʧ��</font> ԭ��:");
					nError = NET_DVR_GetLastError();
					outLog += QString::number(nError, 10);
					this->LogOutputMessage->append(outLog);
					outLog.clear();
					return;
				}
			}
		}
		DeviceInfo_admin Manual_hk = { 0 };
		strcpy(Manual_hk.hk_device_info.szSerialNO, (const char*)HikDeviceInfo_V40.struDeviceV30.sSerialNumber);
		strcpy(Manual_hk.hk_device_info.szIPv4Address,ManualIPchar);
		strcpy(Manual_hk.hk_admin, ManualUserchar);
		strcpy(Manual_hk.hk_pwchar, ManualPwchar);
		Manual_hk.hk_device_info.dwPort = ManualPortchar;
		hk_lDeviceVec.push_back(Manual_hk);
		g_ipserver->TimerSlotd((void*)&Manual_hk, 1);
		sprintf(db_char, "select * from Device_Sheet where ip='%s'", ManualIPchar);
		db_query->exec(db_char);
		BOOL db_up = FALSE;
		while (db_query->next())
		{
			RtlZeroMemory(db_char, 200);
			sprintf(db_char, "update Device_Sheet set admin_h='%s',pw_h='%s' where ip='%s'", ManualUserchar, ManualPwchar, ManualIPchar);
			db_query->exec(db_char);
			db_up = TRUE;
		}
		if (!db_up)
		{
			RtlZeroMemory(db_char, 200);
			sprintf(db_char, "insert into Device_Sheet(ip,admin_h,pw_h) values('%s','%s','%s'", ManualIPchar, ManualUserchar, ManualPwchar);
			db_query->exec(db_char);
		}
		outLog = ManualIPstring;
		outLog += QStringLiteral("��¼�ɹ�");
		this->LogOutputMessage->append(outLog);
		outLog.clear();
	}*/
	return;
}
//�������ú���
void IPServer::DatabaseConnectFunc()
{
	/*OSDResuit = new QDialog;
	OSDResuit->setGeometry(500, 400, 300, 200);

	SuccessOSD = new QLabel(QStringLiteral("��ʼIP"), OSDResuit);
	SuccessOSD->setGeometry(80, 50, 100, 30);
	SuccessOsd = new QLineEdit(OSDResuit);
	SuccessOsd->setGeometry(150, 50, 100, 30);

	LostOSD = new QLabel(QStringLiteral("��ֹIP"), OSDResuit);
	LostOSD->setGeometry(80, 100, 50, 30);
	LostOsd = new QLineEdit(OSDResuit);
	LostOsd->setGeometry(150, 100, 100, 30);

	SearchSetting = new QPushButton(OSDResuit);
	SearchSetting->setText(QStringLiteral("ȷ��"));
	SearchSetting->setGeometry(220, 140, 60, 30);
	OSDResuit->show();
	QRegExp rx("((1?\\d{1,2}|2[0-5]{2})\\.){3}(1?\\d{1,2}|2[0-5]{2})");
	QValidator * validator = new QRegExpValidator(rx, this);
	SuccessOsd->setValidator(validator);
	LostOsd->setValidator(validator);
	SuccessOsd->setInputMask("000.000.000.000");
	LostOsd->setInputMask("000.000.000.000");
	connect(SearchSetting, SIGNAL(clicked()), this, SLOT(SearchFunc()));*/
}
void IPServer::RefreshDeviceList()
{
	EquipmentSearch();
}
void IPServer::QDoubleWfunc(int aitem, int cuttonds)
{
	DoubleRow = aitem;
	if (2==cuttonds)
	{
		/*ConfigDialog_o = new QDialog();
		ConfigDialog_o->setModal(true);
		ConfigDialog_o->setGeometry(100, 100, 400, 300);

		LabelOfE[0] = new QLabel(QStringLiteral("IP"), ConfigDialog_o);
		LabelOfE[0]->setGeometry(100, 10, 100, 30);
		InputEdit[0] = new QLineEdit(ConfigDialog_o);
		InputEdit[0]->setGeometry(150, 10, 100, 30);

		LabelOfE[1] = new QLabel(QStringLiteral("����"), ConfigDialog_o);
		LabelOfE[1]->setGeometry(100, 50, 50, 30);
		InputEdit[1] = new QLineEdit(ConfigDialog_o);
		InputEdit[1]->setGeometry(150, 50, 100, 30);

		LabelOfE[2] = new QLabel(QStringLiteral("��������"), ConfigDialog_o);
		LabelOfE[2]->setGeometry(100, 100, 50, 30);
		InputEdit[2] = new QLineEdit(ConfigDialog_o);
		InputEdit[2]->setGeometry(150, 100, 100, 30);

		LabelOfE[3] = new QLabel(QStringLiteral("�û���"), ConfigDialog_o);
		LabelOfE[3]->setGeometry(100, 150, 50, 30);
		InputEdit[3] = new QLineEdit(ConfigDialog_o);
		InputEdit[3]->setGeometry(150, 150, 100, 30);

		LabelOfE[4] = new QLabel(QStringLiteral("����"), ConfigDialog_o);
		LabelOfE[4]->setGeometry(100, 200, 50, 30);
		InputEdit[4] = new QLineEdit(ConfigDialog_o);
		InputEdit[4]->setGeometry(150, 200, 100, 30);

		ModifiyButton->setParent(ConfigDialog_o, Qt::Widget);
		ModifiyButton->setGeometry(230, 270, 50, 30);
		if (0 == CheckNumber|1==CheckNumber)
		{
			LabelOfE[0]->setText(QStringLiteral("IP"));
			InputEdit[0]->setText(DeviceSheet->item(aitem, 3)->text().trimmed());
			InputEdit[1]->setText(DeviceSheet->item(aitem, 4)->text().trimmed());
			InputEdit[2]->setText(DeviceSheet->item(aitem, 5)->text().trimmed());
			InputEdit[3]->setText(DeviceSheet->item(aitem, 7)->text().trimmed());
			InputEdit[4]->setText(DeviceSheet->item(aitem, 8)->text().trimmed());
		}
		else if (CheckNumber > 1)
		{
			LabelOfE[0]->setText(QStringLiteral("��ʼIP"));
			InputEdit[0]->setText("");
			InputEdit[1]->setText(DeviceSheet->item(aitem, 4)->text().trimmed());
			InputEdit[2]->setText(DeviceSheet->item(aitem, 5)->text().trimmed());
			InputEdit[3]->setText(DeviceSheet->item(aitem, 7)->text().trimmed());
			InputEdit[4]->setText(DeviceSheet->item(aitem, 8)->text().trimmed());
		}
		ConfigDialog_o->show();*/
	}
	if (1==cuttonds)
	{
		/*QString Series = DeviceSheet->item(aitem, cuttonds)->text();
		if (Series==QString::fromLocal8Bit("Kϵ"))
		{
			for (int i = 0; i < this->DeviceSheet->rowCount(); i++)
			{
				Series = DeviceSheet->item(i, 1)->text();
				if (Series==QString::fromLocal8Bit("Kϵ"))
				{
					if (isAscending_series_dh == FALSE)
					{
						((QCheckBox*)DeviceSheet->cellWidget(i, 0))->setCheckState(Qt::Checked);
					}else
					{
						((QCheckBox*)DeviceSheet->cellWidget(i, 0))->setCheckState(Qt::Unchecked);
					}
				}
			}
			isAscending_series_dh = !isAscending_series_dh;
		}
		else if(Series==QString::fromLocal8Bit("Vϵ"))
		{
			for (int i = 0; i < this->DeviceSheet->rowCount(); i++)
			{
				Series = DeviceSheet->item(i, 1)->text();
				if (Series == QString::fromLocal8Bit("Vϵ"))
				{
					if (isAscending_series_hk == FALSE)
					{
						((QCheckBox*)DeviceSheet->cellWidget(i, 0))->setCheckState(Qt::Checked);
					}
					else
					{
						((QCheckBox*)DeviceSheet->cellWidget(i, 0))->setCheckState(Qt::Unchecked);
					}
				}
			}
			isAscending_series_hk = !isAscending_series_hk;*/
		//}
	}
}
void IPServer::Login_Type()
{
	NET_DEVICEINFO_Ex stuInfo = { 0 };
	int nError = 0;
	int nSpecialValue = 90106;
	int aerror;
	QTableWidgetItem *item = new QTableWidgetItem();
	DEVICE_NET_INFO_EX SadpInfo = { 0 };
	//memcpy(&SadpInfo, Device_d, sizeof(DEVICE_NET_INFO_EX));
	LLONG g_lLogin;
	//��¼
	//int sheetlong = DeviceSheet->rowCount();
	QString KVty="";
	QString IPString = "";
	QString PortString = "";
	QString PwString = "";
	QString AdminString = "";
	QString LoginString = "";
	QByteArray IPByte = "";
	QByteArray PWByte = "";
	QByteArray AdminByte = "";
	QByteArray PortByte = "";
	QString outLog;
	NET_DVR_USER_LOGIN_INFO  plogininfo = { 0 };
	NET_DVR_DEVICEINFO_V40 HikDeviceInfo_V40 = { 0 };
	RtlZeroMemory(&plogininfo, sizeof(NET_DVR_USER_LOGIN_INFO));
	RtlZeroMemory(&HikDeviceInfo_V40, sizeof(NET_DVR_DEVICEINFO_V40));
	char db_char[200] = {'\0'};
	//for (int i = 0; i <sheetlong; i++)
	//{
	//	KVty = this->DeviceSheet->item(i, 1)->text();
	//	IPString = this->DeviceSheet->item(i, 3)->text();
	//	PortString = this->DeviceSheet->item(i, 6)->text();
	//	AdminString = this->DeviceSheet->item(i, 7)->text();
	//	PwString = this->DeviceSheet->item(i, 8)->text();
	//	//LoginString = this->DeviceSheet->item(i, 3)->text();
	//	if (AdminString.isEmpty()==TRUE|PwString.isEmpty()==TRUE)
	//	{
	//		this->LogOutputMessage->append(QString::fromLocal8Bit("�û�����������Ϊ��"));
	//		continue;
	//	}
	//	IPByte = IPString.toLatin1();
	//	PortByte = PortString.toLatin1();
	//	AdminByte = AdminString.toLatin1();
	//	PWByte = PwString.toLatin1();
	//	if (DeviceSheet->item(i,9)!=NULL)
	//	{
	//		continue;
	//	}
	//	if (strcmp(KVty.toLocal8Bit(),"Kϵ")==0)
	//	{
	//		g_lLogin = CLIENT_LoginEx2(IPByte.data(),PortByte.toInt(), AdminByte.data(), PWByte.data(), (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
	//		if (g_lLogin == 0)
	//		{
	//			Sleep(100);
	//			//nError = CLIENT_GetLastError()&(0x7fffffff);
	//			nSpecialValue = 90106;
	//			g_lLogin = CLIENT_LoginEx2(IPByte.data(), PortByte.toInt(), AdminByte.data(), PWByte.data(), (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
	//			if (g_lLogin == 0)
	//			{
	//				Sleep(100);
	//				//nError = CLIENT_GetLastError()&(0x7fffffff);
	//				g_lLogin = CLIENT_LoginEx2(IPByte.data(), PortByte.toInt(), AdminByte.data(), PWByte.data(), (EM_LOGIN_SPAC_CAP_TYPE)0, NULL, &stuInfo, &nError);
	//				if (0 == g_lLogin)
	//				{
	//					this->DeviceSheet->setItem(i, 9, new QTableWidgetItem(QString::fromLocal8Bit("��¼ʧ��")));
	//					outLog = IPString;
	//					outLog += QStringLiteral("<font color='red'>��¼ʧ��</font> ԭ��:");
	//					nError = CLIENT_GetLastError()&(0x7fffffff);
	//					outLog += QString::number(nError, 10);
	//					this->LogOutputMessage->append(outLog);
	//					outLog.clear();
	//					continue;
	//				}
	//			}
	//		}
	//		if (g_lLogin != 0)
	//		{
	//			this->DeviceSheet->setItem(i, 9, new QTableWidgetItem(QString::fromLocal8Bit("��¼�ɹ�")));
	//			sprintf(db_char, "select * from Device_Sheet where ip='%s'", IPByte.data());
	//			db_query->exec(db_char);
	//			BOOL db_up = FALSE;
	//			while (db_query->next())
	//			{
	//				RtlZeroMemory(db_char, 200);
	//				sprintf(db_char, "update Device_Sheet set admin_h='%s',pw_h='%s'; where ip='%s'", AdminByte.data(), PWByte.data(), IPByte.data());
	//				db_query->exec(db_char);
	//				db_up = TRUE;
	//			}
	//			if (!db_up)
	//			{
	//				RtlZeroMemory(db_char, 200);
	//				sprintf(db_char, "insert into Device_Sheet(ip,admin_h,pw_h) values('%s','%s','%s')", IPByte.data(), AdminByte.data(), PWByte.data());
	//				db_query->exec(db_char);
	//			}
	//			continue;
	//		}
	//	}
	//	if (strcmp(KVty.toLocal8Bit(),"Vϵ")==0)
	//	{
	//		memcpy_s(plogininfo.sDeviceAddress, 129, IPByte.data(), 16);
	//		memcpy_s(plogininfo.sPassword, 64, PWByte.data(), 64);
	//		strcpy(plogininfo.sUserName,AdminByte.data());
	//		plogininfo.wPort = PortByte.toInt() ;
	//		plogininfo.bUseAsynLogin = 0;
	//		plogininfo.byJiaFaEncypt = 2;
	//		g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
	//		if (g_lLogin ==-1)
	//		{
	//			plogininfo.byJiaFaEncypt = 1;
	//			g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
	//			if (g_lLogin == -1)
	//			{
	//				plogininfo.byJiaFaEncypt = 0;
	//				g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
	//				if (g_lLogin == -1)
	//				{
	//					this->DeviceSheet->setItem(i, 9, new QTableWidgetItem(QString::fromLocal8Bit("��¼ʧ��")));
	//					outLog = IPString;
	//					outLog += QStringLiteral("<font color='red'>��¼ʧ��</font> ԭ��:");
	//					nError = NET_DVR_GetLastError();
	//					outLog += QString::number(nError, 10);
	//					this->LogOutputMessage->append(outLog);
	//					outLog.clear();
	//					continue;
	//				}
	//			}
	//		}
	//		if (g_lLogin != -1)
	//		{
	//			this->DeviceSheet->setItem(i, 9, new QTableWidgetItem(QString::fromLocal8Bit("��¼�ɹ�")));
	//			sprintf(db_char, "select * from Device_Sheet where ip='%s'", IPByte.data());
	//			db_query->exec(db_char);
	//			BOOL db_up = FALSE;
	//			while (db_query->next())
	//			{
	//				RtlZeroMemory(db_char, 200);
	//				sprintf(db_char, "update Device_Sheet set admin_h='%s',pw_h='%s'; where ip='%s'", AdminByte.data(), PWByte.data(), IPByte.data());
	//				db_query->exec(db_char);
	//				db_up = TRUE;
	//			}
	//			if (!db_up)
	//			{
	//				RtlZeroMemory(db_char, 200);
	//				sprintf(db_char, "insert into Device_Sheet(ip,admin_h,pw_h) values('%s','%s','%s')", IPByte.data(), AdminByte.data(), PWByte.data());
	//				db_query->exec(db_char);
	//			}
	//			continue;
	//		}
		//}

	//}
}
BOOL IPServer::Login_dh(void* dhs)
{
	DEVICE_NET_INFO_EX Dh_struct = { 0 };
	memcpy(&Dh_struct, dhs, sizeof(DEVICE_NET_INFO_EX));
	NET_DEVICEINFO_Ex stuInfo = { 0 };
	int nError = 0;
	int nSpecialValue = 90106;
	int aerror;
	LLONG g_lLogin;
	QString outLog;
	g_lLogin = CLIENT_LoginEx2(Dh_struct.szIP, Dh_struct.nPort, Dh_struct.szUserName, Dh_struct.szPassWord, (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
	if (g_lLogin == 0)
	{
		nSpecialValue = 90106;
		g_lLogin = CLIENT_LoginEx2(Dh_struct.szIP, Dh_struct.nPort, Dh_struct.szUserName, Dh_struct.szPassWord, (EM_LOGIN_SPAC_CAP_TYPE)28, &nSpecialValue, &stuInfo, &nError);
		if (g_lLogin == 0)
		{
			g_lLogin = CLIENT_LoginEx2(Dh_struct.szIP, Dh_struct.nPort, Dh_struct.szUserName, Dh_struct.szPassWord, (EM_LOGIN_SPAC_CAP_TYPE)0, NULL, &stuInfo, &nError);
			if (0 == g_lLogin)
			{
				outLog = QString::fromLocal8Bit(Dh_struct.szIP,64);
				outLog += QStringLiteral("<font color='red'>��¼ʧ��</font> ԭ��:");
				nError = CLIENT_GetLastError()&(0x7fffffff);
				/*outLog += QString::number(nError, 10);
				this->LogOutputMessage->append(outLog);
				outLog.clear();
				return FALSE;*/
			}
		}
	}
	if (g_lLogin != 0)
	{
		return TRUE;
	}
}
BOOL IPServer::Login_hk(void* hks)
{
	DeviceInfo_admin hk_struct = { 0 };
	memcpy(&hk_struct, hks, sizeof(DeviceInfo_admin));
	NET_DVR_USER_LOGIN_INFO  plogininfo = { 0 };
	NET_DVR_DEVICEINFO_V40 HikDeviceInfo_V40 = { 0 };
	RtlZeroMemory(&plogininfo, sizeof(NET_DVR_USER_LOGIN_INFO));
	RtlZeroMemory(&HikDeviceInfo_V40, sizeof(NET_DVR_DEVICEINFO_V40));
	memcpy_s(plogininfo.sDeviceAddress, 129, hk_struct.hk_device_info.szIPv4Address, 16);
	memcpy_s(plogininfo.sPassword, 64,hk_struct.hk_pwchar, 64);
	strcpy(plogininfo.sUserName, hk_struct.hk_admin);
	plogininfo.wPort =hk_struct.hk_device_info.dwPort;
	plogininfo.bUseAsynLogin = 0;
	plogininfo.byJiaFaEncypt = 2;
	LLONG g_lLogin;
	QString outLog;
	int nError = 0;
	g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
	if (g_lLogin == -1)
	{
		plogininfo.byJiaFaEncypt = 1;
		g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
		if (g_lLogin == -1)
		{
			plogininfo.byJiaFaEncypt = 0;
			g_lLogin = NET_DVR_Login_V40(&plogininfo, &HikDeviceInfo_V40);
			if (g_lLogin == -1)
			{
				outLog = QString::fromLocal8Bit(hk_struct.hk_device_info.szIPv4Address,16);
				outLog += QStringLiteral("<font color='red'>��¼ʧ��</font> ԭ��:");
				nError = NET_DVR_GetLastError();
				outLog += QString::number(nError, 10);
				//this->LogOutputMessage->append(outLog);
				outLog.clear();
	            return FALSE;
			}
		}
	}
	if (g_lLogin != -1)
	{
		return TRUE;
	}
}
void IPServer::Slot_sortDevice(int clounm)
{
	if (clounm == 3)
	{
		if (isAscending == false)
		{
			isAscending = true;
			//DeviceSheet->setUserData(Qt::DisplayRole, 2);
			//DeviceSheet->sortItems(clounm, Qt::AscendingOrder);
			return;
		}
		if (isAscending == true)
		{
			isAscending = false;
			//DeviceSheet->sortItems(clounm, Qt::DescendingOrder);
			return;
		}
	}
	if (clounm==1)
	{
		if (isAscending_one == false)
		{
			isAscending_one = true;
			//DeviceSheet->setUserData(Qt::DisplayRole, 2);
			//DeviceSheet->sortItems(clounm, Qt::AscendingOrder);
			return;
		}
		if (isAscending_one == true)
		{
			isAscending_one = false;
			//DeviceSheet->sortItems(clounm, Qt::DescendingOrder);
			return;
		}
	}
	if (clounm == 2)
	{
		if (isAscending_two == false)
		{
			isAscending_two = true;
			//DeviceSheet->setUserData(Qt::DisplayRole, 2);
			//DeviceSheet->sortItems(clounm, Qt::AscendingOrder);
			return;
		}
		if (isAscending_two == true)
		{
			isAscending_two = false;
			//DeviceSheet->sortItems(clounm, Qt::DescendingOrder);
			return;
		}
	}
	if (clounm == 9)
	{
		if (isAscending_three == false)
		{
			isAscending_three = true;
			//DeviceSheet->setUserData(Qt::DisplayRole, 2);
			//DeviceSheet->sortItems(clounm, Qt::AscendingOrder);
			return;
		}
		if (isAscending_three == true)
		{
			isAscending_three = false;
			//DeviceSheet->sortItems(clounm, Qt::DescendingOrder);
			return;
		}
	}
	if (clounm == 6)
	{
		if (isAscending_seven == false)
		{
			isAscending_seven = true;
			//DeviceSheet->setUserData(Qt::DisplayRole, 2);
			//DeviceSheet->sortItems(clounm, Qt::AscendingOrder);
			return;
		}
		if (isAscending_seven == true)
		{
			isAscending_seven = false;
			//DeviceSheet->sortItems(clounm, Qt::DescendingOrder);
			return;
		}
	}
}
bool NewQTableWight::operator<(const QTableWidgetItem &other) const
{
	LLONG OIPs=IPCString2DWORD(other.text().toLatin1().data());
	LLONG TIPs = IPCString2DWORD(this->text().toLatin1().data());
	if (OIPs>TIPs)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void IPServer::SearchFunc()
{
	DEVICE_IP_SEARCH_INFO SearhStruct = { 0 };
	SearhStruct.dwSize = sizeof(DEVICE_IP_SEARCH_INFO);
	//QString StartIP = SuccessOsd->text();
	//QString StopIP = LostOsd->text();
	//if (StartIP.isEmpty()==TRUE|StopIP.isEmpty()==TRUE)
	//{
	//	//this->LogOutputMessage->append(QString::fromLocal8Bit("��ʼIPΪ��"));
	//	return;
	//}
	//OSDResuit->hide();
	char StatIPchar[64] = { '\0' };
	//strcpy(StatIPchar, StartIP.toLatin1().data());
	LONG Iplong;
	SearhStruct.nIpNum = 0;
	for (int i=0;;i++)
	{
		SearhStruct.nIpNum++;
		strcpy(SearhStruct.szIP[i], StatIPchar);
		Iplong = IPCString2DWORD(StatIPchar);
		Iplong++;
		LONGToIPChar(StatIPchar, Iplong);
		/*if (strcmp(StatIPchar,StopIP.toLatin1().data())==0)
		{
			SearhStruct.nIpNum++;
			strcpy(SearhStruct.szIP[++i], StatIPchar);
			break;
		}*/
	}
	BOOL sae=CLIENT_SearchDevicesByIPs(&SearhStruct, SearchDevicesCB_Searce, (unsigned long)&g_lDeviceVec, NULL, 5000);
	return;
}
void IPServer::TimerSlotd_Search(void* DeviceInfo, BOOL flag)
{
	QString InformationHC = "";
	DEVICE_NET_INFO_EX SadpInfo = { 0 };
	//int nTalbeCount = DeviceSheet->rowCount();
	int adden_2 = GetCurrentThreadId();
	printf("%d", adden_2);
	if (2 == flag)
	{
		wc_newTask.wakeOne();

		/*while (1)
		{
			if (Thread_Search->isFinished())
			{
				this->DeviceSheet->setCellWidget(nTalbeCount, 0, pcheckBox_dh);
			}
		}*/
		//Sleep(100);
		//this->DeviceSheet->setCellWidget(nTalbeCount, 0, pcheckBox_dh);
		//connect(pcheckBox_dh, SIGNAL(stateChanged(int)), this, SLOT(WriteInformationToTable_dh(int)));

		TableCustom++;
	}
}
void IPServer::UpdateTransmitPanel()
{
	/*int nTalbeCount = DeviceSheet->rowCount();
	for (int i=nTalbeCount-1;i>=0;i--)
	{
		if (this->DeviceSheet->cellWidget(i,0)==NULL)
		{
			pcheckBox_dh = new QCheckBox();
			this->DeviceSheet->setCellWidget(i , 0, pcheckBox_dh);
			connect(pcheckBox_dh, SIGNAL(stateChanged(int)), this, SLOT(WriteInformationToTable_dh(int)));
		}
	}*/
}
void ThreadOperEntry::slot_search()
{
	while (1)
	{
		/*mx_newTask.lock();
		while (!wc_newTask.wait(&mx_newTask))
		{
			continue;
		}
		mx_newTask.unlock();*/
		signal_search();
		return;
	}
}
