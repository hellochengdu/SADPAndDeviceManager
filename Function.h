#pragma once
#include <windows.h>
// �������ӶϿ��ص�����ԭ��
#define  LDWORD  DWORD
#define  LLONG  LONG
typedef long LONG;
#define DH_MAX_MAIL_ADDR_LEN              128              // �ʼ���(��)��ַ��󳤶�
#define DH_MAX_MAIL_SUBJECT_LEN           64               // �ʼ�������󳤶�
#define DH_MAX_IPADDR_LEN                 16               // IP��ַ�ַ�������
#define DH_MAX_IPADDR_LEN_EX              40               // ��չIP��ַ�ַ�������, ֧��IPV6
#define DH_MACADDR_LEN                    40               // MAC��ַ�ַ�������
#define DH_MAX_URL_LEN                    128              // URL�ַ�������
#define DH_MAX_DEV_ID_LEN                 48               // ���������󳤶�
#define DH_MAX_HOST_NAMELEN               64               // ����������,
#define DH_MAX_HOST_PSWLEN                32               // ���볤��
#define DH_MAX_NAME_LEN                   16               // ͨ�������ַ�������
#define DH_MAX_ETHERNET_NUM               2                // ��̫����������
#define DH_MAX_ETHERNET_NUM_EX            10               // ��չ��̫����������
#define DH_DEV_SERIALNO_LEN               48               // ���к��ַ�������
#define DH_DEV_CLASS_LEN                  16               // �豸�����ַ�������"IPC"������
#define DH_DEV_TYPE_LEN                   32               // �豸�ͺ��ַ�������"IPC-F725"������
#define DH_MAX_SAERCH_IP_NUM              256              // �������IP����
#define DH_MAX_STRING_LEN                 128        
#define DH_MACHINE_NAME_NUM               64               // �������Ƴ���
#define DH_USER_NAME_LENGTH_EX       16                 // �û�������
#define DH_USER_PSW_LENGTH_EX        16                 // ����
#define MAX_IPV6_LEN              64   //IPv6��ַ��󳤶�
#define CFG_MAX_CHANNEL_NAME_LEN            256     // ͨ��������󳤶� 
#define NET_DVR_DEV_ADDRESS_MAX_LEN 129
#define NET_DVR_LOGIN_USERNAME_MAX_LEN 64
#define NET_DVR_LOGIN_PASSWD_MAX_LEN 64
#define SERIALNO_LEN		    48      //���кų���
#define NET_DVR_SET_PICCFG_V40                      6180    //����ͼ������� ֧�ֱ䳤
#define CFG_CMD_CHANNELTITLE                "ChannelTitle"              // ͨ������(��Ӧ AV_CFG_ChannelName)
#define NET_DVR_GET_PICCFG_V40                      6179    //��ȡͼ����� ֧�ֱ䳤    NetSDK
#define MAX_TIMESEGMENT_V30        8       //9000�豸���ʱ�����
#define NAME_LEN			    32      //�û�������
#define MAX_SHELTERNUM            4       //8000�豸����ڵ�������
#define MAX_IP_ALARMOUT_V40     4096    //����������౨�������
#define MAX_ALARMOUT_V40             (MAX_IP_ALARMOUT_V40 +MAX_ANALOG_ALARMOUT) //4128
#define MAX_ANALOG_ALARMOUT     32      //���32·ģ�ⱨ�����
#define MAX_DAYS                7       //ÿ������
#define MAX_MULTI_AREA_NUM      24
#define MAX_CHANNUM_V40         512
#define DH_SERIALNO_LEN                   48    


typedef int					AV_int32;



// ��ӦCLIENT_SearchDevicesByIPs�ӿ�
typedef struct
{
	DWORD               dwSize;                                 // �ṹ���С
	int                 nIpNum;                                 // ��ǰ������IP����
	char                szIP[DH_MAX_SAERCH_IP_NUM][64];         // �����������IP��Ϣ
}DEVICE_IP_SEARCH_INFO;
// ��ӦCLIENT_StartSearchDevices�ӿ�
typedef struct
{
	int                 iIPVersion;                             // 4 for IPV4, 6 for IPV6
	char                szIP[64];                               // IP IPV4����"192.168.0.1" IPV6����"2008::1/64"
	int                 nPort;                                  // tcp�˿�
	char                szSubmask[64];                          // �������� IPV6����������
	char                szGateway[64];                          // ����
	char                szMac[DH_MACADDR_LEN];                  // MAC��ַ
	char                szDeviceType[DH_DEV_TYPE_LEN];          // �豸����
	BYTE                byManuFactory;                          // Ŀ���豸����������,����ο�EM_IPC_TYPE��    
	BYTE                byDefinition;                           // 1-���� 2-����
	bool                bDhcpEn;                                // Dhcpʹ��״̬, true-��, false-��
	BYTE                byReserved1;                            // �ֽڶ���
	char                verifyData[88];                         // У������ ͨ���첽�����ص���ȡ(���޸��豸IPʱ���ô���Ϣ����У��)
	char                szSerialNo[DH_DEV_SERIALNO_LEN];        // ���к�
	char                szDevSoftVersion[DH_MAX_URL_LEN];       // �豸����汾��    
	char                szDetailType[DH_DEV_TYPE_LEN];          // �豸�ͺ�
	char                szVendor[DH_MAX_STRING_LEN];            // OEM�ͻ�����
	char                szDevName[DH_MACHINE_NAME_NUM];         // �豸����
	char                szUserName[DH_USER_NAME_LENGTH_EX];     // ��½�豸�û��������޸��豸IPʱ��Ҫ��д��
	char                szPassWord[DH_USER_NAME_LENGTH_EX];     // ��½�豸���루���޸��豸IPʱ��Ҫ��д��
	unsigned short      nHttpPort;                              // HTTP����˿ں�
	WORD                wVideoInputCh;                          // ��Ƶ����ͨ����
	WORD                wRemoteVideoInputCh;                    // Զ����Ƶ����ͨ����
	WORD                wVideoOutputCh;                         // ��Ƶ���ͨ����
	WORD                wAlarmInputCh;                          // ��������ͨ����
	WORD                wAlarmOutputCh;                         // �������ͨ����
	char                cReserved[244];
}DEVICE_NET_INFO_EX;
// �ṹ��
typedef struct tagSADP_DEVICE_INFO
{
	char			szSeries[12];
	char			szSerialNO[48];
	char			szMAC[20];
	char			szIPv4Address[16];
	char			szIPv4SubnetMask[16];
	unsigned int	dwDeviceType;
	unsigned int	dwPort;
	unsigned int	dwNumberOfEncoders;
	unsigned int	dwNumberOfHardDisk;
	char			szDeviceSoftwareVersion[48];
	char			szDSPVersion[48];
	char			szBootTime[48];
	int				iResult;
	char			szDevDesc[24];       //�豸��������
	char			szOEMinfo[24];       //OEM������Ϣ
	char			szIPv4Gateway[16];   //IPv4����
	char			szIPv6Address[46];	 //IPv6��ַ
	char			szIPv6Gateway[46];   //IPv6����
	unsigned char   byIPv6MaskLen;       //IPv6����ǰ׺����
	unsigned char   bySupport;           //��λ��ʾ,��ӦΪΪ1��ʾ֧��,0x01:�Ƿ�֧��Ipv6,0x02:�Ƿ�֧���޸�Ipv6����,0x04:�Ƿ�֧��Dhcp	0x08: �Ƿ�֧��udp�ಥ 0x10:�Ƿ񺬼��ܽڵ�,0x20:�Ƿ�֧�ָֻ�����,0x40:�Ƿ�֧����������,0x80:�Ƿ�֧��ͬ��IPC����			 
	unsigned char   byDhcpEnabled;       //Dhcp״̬, 0 ������ 1 ����
	unsigned char   byDeviceAbility;	//0���豸��֧�֡����豸���������� 'OEM����' 'IPv4����' ��IPv6��ַ�� 'IPv6����' ��IPv6����ǰ׺����DHCP����  1��֧�����߹���
	unsigned short	wHttpPort;			// Http �˿�
	unsigned short	wDigitalChannelNum;
	char			szCmsIPv4[16];
	unsigned short	wCmsPort;
	unsigned char	byOEMCode;  //0-�����豸 1-OEM�豸
	unsigned char   byActivated; //�豸�Ƿ񼤻�;0-���1-δ����ϵ��豸�����Ѽ���״̬��
	char			szBaseDesc[24];	//���߶��ͺţ����涨�ƶ��޸ĵ��ͺţ�����өʯƽ̨�����ͺŶԱ�
	unsigned char   bySupport1; //��λ��ʾ,  1��ʾ֧�֣�0��ʾ��֧��
								//0x01:�Ƿ�֧���������뷽ʽ2 
								//0x02;�Ƿ�֧���豸��������
	unsigned char   byRes[2];
	unsigned char   byEZVIZCode;    //0- �����豸 1- өʯ�豸
	unsigned int    dwDetailOEMCode;    //��ϸOEMCode��Ϣ:oemcode�ɿͻ���ţ��ɱ�λ,��1��ʼ��1~429496)+�˵����2λ��+����ţ�2λ�������ֹ��ɡ�										//����˵����oemcode���ֵΪ4294967295�������ʮλ����
	unsigned char    byRes2[8];
}SADP_DEVICE_INFO, *LPSADP_DEVICE_INFO;

typedef struct DeviceInfo_admin
{
	char hk_admin[30];
	SADP_DEVICE_INFO hk_device_info;
	char hk_pwchar[30];
};

// �豸��Ϣ��չ
typedef struct
{
	BYTE                sSerialNumber[DH_SERIALNO_LEN];     // ���к�
	int                 nAlarmInPortNum;                    // DVR�����������
	int                 nAlarmOutPortNum;                   // DVR�����������
	int                 nDiskNum;                           // DVRӲ�̸���
	int                 nDVRType;                           // DVR����,��ö��NET_DEVICE_TYPE
	int                 nChanNum;                           // DVRͨ������
	BYTE                byLimitLoginTime;                   // ���߳�ʱʱ��,Ϊ0��ʾ�����Ƶ�½,��0��ʾ���Ƶķ�����
	BYTE                byLeftLogTimes;                     // ����½ʧ��ԭ��Ϊ�������ʱ,ͨ���˲���֪ͨ�û�,ʣ���½����,Ϊ0ʱ��ʾ�˲�����Ч
	BYTE                bReserved[2];                       // �����ֽ�,�ֽڶ���
	int                 nLockLeftTime;                      // ����½ʧ��,�û�����ʣ��ʱ�䣨������, -1��ʾ�豸δ���øò���
	char                Reserved[24];                       // ����
} NET_DEVICEINFO_Ex, *LPNET_DEVICEINFO_Ex;
typedef enum tagEM_LOGIN_SPAC_CAP_TYPE
{
	EM_LOGIN_SPEC_CAP_TCP = 0,    // TCP��½, Ĭ�Ϸ�ʽ
	EM_LOGIN_SPEC_CAP_ANY = 1,    // ��������½
	EM_LOGIN_SPEC_CAP_SERVER_CONN = 2,    // ����ע��ĵ���
	EM_LOGIN_SPEC_CAP_MULTICAST = 3,    // �鲥��½
	EM_LOGIN_SPEC_CAP_UDP = 4,    // UDP��ʽ�µĵ���
	EM_LOGIN_SPEC_CAP_MAIN_CONN_ONLY = 6,    // ֻ���������µĵ���
	EM_LOGIN_SPEC_CAP_SSL = 7,    // SSL���ܷ�ʽ��½

	EM_LOGIN_SPEC_CAP_INTELLIGENT_BOX = 9,    // ��¼���ܺ�Զ���豸
	EM_LOGIN_SPEC_CAP_NO_CONFIG = 10,   // ��¼�豸����ȡ���ò���
	EM_LOGIN_SPEC_CAP_U_LOGIN = 11,   // ��U���豸�ĵ���
	EM_LOGIN_SPEC_CAP_LDAP = 12,   // LDAP��ʽ��¼
	EM_LOGIN_SPEC_CAP_AD = 13,   // AD��ActiveDirectory����¼��ʽ
	EM_LOGIN_SPEC_CAP_RADIUS = 14,   // Radius ��¼��ʽ 
	EM_LOGIN_SPEC_CAP_SOCKET_5 = 15,   // Socks5��½��ʽ
	EM_LOGIN_SPEC_CAP_CLOUD = 16,   // �Ƶ�½��ʽ
	EM_LOGIN_SPEC_CAP_AUTH_TWICE = 17,   // ���μ�Ȩ��½��ʽ
	EM_LOGIN_SPEC_CAP_TS = 18,   // TS�����ͻ��˵�½��ʽ
	EM_LOGIN_SPEC_CAP_P2P = 19,   // ΪP2P��½��ʽ
	EM_LOGIN_SPEC_CAP_MOBILE = 20,   // �ֻ��ͻ��˵�½
	EM_LOGIN_SPEC_CAP_INVALID                   // ��Ч�ĵ�½��ʽ
}EM_LOGIN_SPAC_CAP_TYPE;


// ͨ������
struct AV_CFG_ChannelName
{
	AV_int32			nStructSize;
	AV_int32			nSerial;						// ����ͷΨһ���
	char				szName[CFG_MAX_CHANNEL_NAME_LEN];// ͨ����
};

//NET_DVR_Login_V30()�����ṹ
typedef struct
{
	BYTE sSerialNumber[SERIALNO_LEN];  //���к�
	BYTE byAlarmInPortNum;                //�����������
	BYTE byAlarmOutPortNum;                //�����������
	BYTE byDiskNum;                    //Ӳ�̸���
	BYTE byDVRType;                    //�豸����, 1:DVR 2:ATM DVR 3:DVS ......
	BYTE byChanNum;                    //ģ��ͨ������
	BYTE byStartChan;                    //��ʼͨ����,����DVS-1,DVR - 1
	BYTE byAudioChanNum;                //����ͨ����
	BYTE byIPChanNum;                    //�������ͨ����������λ  
	BYTE byZeroChanNum;            //��ͨ��������� //2010-01-16
	BYTE byMainProto;            //����������Э������ 0-private, 1-rtsp,2-ͬʱ֧��private��rtsp
	BYTE bySubProto;                //����������Э������0-private, 1-rtsp,2-ͬʱ֧��private��rtsp
	BYTE bySupport;        //������λ����Ϊ0��ʾ��֧�֣�1��ʾ֧�֣�
						   //bySupport & 0x1, ��ʾ�Ƿ�֧����������
						   //bySupport & 0x2, ��ʾ�Ƿ�֧�ֱ���
						   //bySupport & 0x4, ��ʾ�Ƿ�֧��ѹ������������ȡ
						   //bySupport & 0x8, ��ʾ�Ƿ�֧�ֶ�����
						   //bySupport & 0x10, ��ʾ֧��Զ��SADP
						   //bySupport & 0x20, ��ʾ֧��Raid������
						   //bySupport & 0x40, ��ʾ֧��IPSAN Ŀ¼����
						   //bySupport & 0x80, ��ʾ֧��rtp over rtsp
	BYTE bySupport1;        // ���������䣬λ����Ϊ0��ʾ��֧�֣�1��ʾ֧��
							//bySupport1 & 0x1, ��ʾ�Ƿ�֧��snmp v30
							//bySupport1 & 0x2, ֧�����ֻطź�����
							//bySupport1 & 0x4, �Ƿ�֧�ֲ������ȼ�    
							//bySupport1 & 0x8, �����豸�Ƿ�֧�ֲ���ʱ�����չ
							//bySupport1 & 0x10, ��ʾ�Ƿ�֧�ֶ������������33����
							//bySupport1 & 0x20, ��ʾ�Ƿ�֧��rtsp over http    
							//bySupport1 & 0x80, ��ʾ�Ƿ�֧�ֳ����±�����Ϣ2012-9-28, �һ���ʾ�Ƿ�֧��NET_DVR_IPPARACFG_V40�ṹ��
	BYTE bySupport2; /*������λ����Ϊ0��ʾ��֧�֣���0��ʾ֧��
					 bySupport2 & 0x1, ��ʾ�������Ƿ�֧��ͨ��URLȡ������
					 bySupport2 & 0x2,  ��ʾ֧��FTPV40
					 bySupport2 & 0x4,  ��ʾ֧��ANR
					 bySupport2 & 0x8,  ��ʾ֧��CCD��ͨ����������
					 bySupport2 & 0x10,  ��ʾ֧�ֲ��������ش���Ϣ����֧��ץ�Ļ����� ���ϱ����ṹ��
					 bySupport2 & 0x20,  ��ʾ�Ƿ�֧�ֵ�����ȡ�豸״̬����
					 bySupport2 & 0x40,  ��ʾ�Ƿ������������豸*/
	WORD wDevType;              //�豸�ͺ�
	BYTE bySupport3; //��������չ��λ����Ϊ0��ʾ��֧�֣�1��ʾ֧��
					 //bySupport3 & 0x1, ��ʾ�Ƿ������
					 // bySupport3 & 0x4 ��ʾ֧�ְ������ã� ������� ͨ��ͼ��������������������IP�������롢������������
					 // �û��������豸����״̬��JPEGץͼ����ʱ��ʱ��ץͼ��Ӳ��������� 
					 //bySupport3 & 0x8Ϊ1 ��ʾ֧��ʹ��TCPԤ����UDPԤ�����ಥԤ���е�"��ʱԤ��"�ֶ���������ʱԤ������������ʹ�����ַ�ʽ������ʱԤ����������bySupport3 & 0x8Ϊ0ʱ����ʹ�� "˽����ʱԤ��"Э�顣
					 //bySupport3 & 0x10 ��ʾ֧��"��ȡ����������Ҫ״̬��V40��"��
					 //bySupport3 & 0x20 ��ʾ�Ƿ�֧��ͨ��DDNS��������ȡ��

	BYTE byMultiStreamProto;//�Ƿ�֧�ֶ�����,��λ��ʾ,0-��֧��,1-֧��,bit1-����3,bit2-����4,bit7-��������bit-8������
	BYTE byStartDChan;        //��ʼ����ͨ����,0��ʾ��Ч
	BYTE byStartDTalkChan;    //��ʼ���ֶԽ�ͨ���ţ�������ģ��Խ�ͨ���ţ�0��ʾ��Ч
	BYTE byHighDChanNum;        //����ͨ����������λ
	BYTE bySupport4;        //��������չ��λ����Ϊ0��ʾ��֧�֣�1��ʾ֧��
							//bySupport4 & 0x4��ʾ�Ƿ�֧��ƴ��ͳһ�ӿ�
							// bySupport4 & 0x80 ֧���豸�ϴ����ı���ʹ�ܡ���ʾ�жϵ��ýӿ��� NET_DVR_PDC_RULE_CFG_V42���� NET_DVR_PDC_RULE_CFG_V41
	BYTE byLanguageType;// ֧����������,��λ��ʾ,ÿһλ0-��֧��,1-֧��  
						//  byLanguageType ����0 ��ʾ ���豸
						//  byLanguageType & 0x1��ʾ֧������
						//  byLanguageType & 0x2��ʾ֧��Ӣ��
	BYTE byVoiceInChanNum;   //��Ƶ����ͨ���� 
	BYTE byStartVoiceInChanNo; //��Ƶ������ʼͨ���� 0��ʾ��Ч
	BYTE  bySupport5;  //��λ��ʾ,0-��֧��,1-֧��,bit0-֧�ֶ�����
					   //bySupport5 &0x01��ʾ֧��wEventTypeEx ,����dwEventType ���¼����ͣ�֧����Ϊ�¼���չ��--��ռס����ֹ��ͻ
					   //bySupport5 &0x04��ʾ�Ƿ�֧��ʹ����չ�ĳ���ģʽ�ӿ�
					   /*
					   bySupport5 &0x08 �豸���ظ�ֵ��ʾ�Ƿ�֧�ּƻ�¼������V40�ӿ�Э��(DVR_SET_RECORDCFG_V40/ DVR_GET_RECORDCFG_V40)(�ڸ�Э�����豸֧����������13������)
					   ֮ǰ�Ĳ��ַ������豸��֧��¼������13��������¼������13�������֧�֣�ͳһת����¼������3���ݴ���SDKͨ������̽�⴦��)
					   */
	BYTE  bySupport6;   //��������λ��ʾ��0-��֧��,1-֧��
						//bySupport6 0x1  ��ʾ�豸�Ƿ�֧��ѹ�� 
						//bySupport6 0x2 ��ʾ�Ƿ�֧����ID��ʽ��������Դ��չ���DVR_SET_STREAM_SRC_INFO_V40
						//bySupport6 0x4 ��ʾ�Ƿ�֧���¼�����V40�ӿ�
						//bySupport6 0x8 ��ʾ�Ƿ�֧����չ���������������
						//bySupport6 0x40��ʾͼƬ��ѯ���V40��չ
	BYTE  byMirrorChanNum;    //����ͨ��������<¼�����������ڱ�ʾ����ͨ��>
	WORD wStartMirrorChanNo;  //��ʼ����ͨ����
	BYTE bySupport7;   //����,��λ��ʾ,0-��֧��,1-֧��
					   // bySupport7 & 0x1  ��ʾ�豸�Ƿ�֧�� INTER_VCA_RULECFG_V42 ��չ
					   // bySupport7 & 0x2  ��ʾ�豸�Ƿ�֧�� IPC HVT ģʽ��չ
					   // bySupport7 & 0x04  ��ʾ�豸�Ƿ�֧�� ��������ʱ��
					   // bySupport7 & 0x08  ��ʾ������̨PTZλ��ʱ���Ƿ�֧�ִ�ͨ����
					   // bySupport7 & 0x10  ��ʾ�豸�Ƿ�֧��˫ϵͳ��������
					   // bySupport7 & 0x20  ��ʾ�豸�Ƿ�֧�� OSD�ַ����� V50
					   // bySupport7 & 0x40  ��ʾ�豸�Ƿ�֧�� ���Ӹ��٣����������
					   // bySupport7 & 0x80  ��ʾ�豸�Ƿ�֧�� ���ļ���
	BYTE  byRes2;        //����
}NET_DVR_DEVICEINFO_V30, *LPNET_DVR_DEVICEINFO_V30;

typedef void (CALLBACK *fLoginResultCallBack) (LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void* pUser);
typedef struct
{
	char sDeviceAddress[NET_DVR_DEV_ADDRESS_MAX_LEN];
	BYTE byUseTransport;    //�Ƿ�����������͸����0--������͸����Ĭ�ϣ�1--����͸��
	WORD wPort;
	char sUserName[NET_DVR_LOGIN_USERNAME_MAX_LEN];
	char sPassword[NET_DVR_LOGIN_PASSWD_MAX_LEN];
	fLoginResultCallBack cbLoginResult;
	void *pUser;
	BOOL bUseAsynLogin;
	BYTE byProxyType; //0:��ʹ�ô���1��ʹ�ñ�׼����2��ʹ��EHome����
	BYTE byUseUTCTime;    //0-������ת����Ĭ��,1-�ӿ����������ȫ��ʹ��UTCʱ��,SDK���UTCʱ�����豸ʱ����ת��,2-�ӿ����������ȫ��ʹ��ƽ̨����ʱ�䣬SDK���ƽ̨����ʱ�����豸ʱ����ת��
	BYTE byJiaFaEncypt;	//0-Ĭ�ϣ������豸����1-��������1���ѷ�Ѳ���豸����2-��������2���ѷ�ƽ���豸��
	BYTE byRes2;
	LONG iProxyID;    //�����������ţ���Ӵ����������Ϣʱ�����Ӧ�ķ����������±�ֵ    
	BYTE byRes3[120];
}NET_DVR_USER_LOGIN_INFO, *LPNET_DVR_USER_LOGIN_INFO;
typedef struct tagNET_DVR_DEVICEINFO_V40
{
	NET_DVR_DEVICEINFO_V30 struDeviceV30;
	BYTE  bySupportLock;        //�豸֧���������ܣ����ֶ���SDK�����豸����ֵ����ֵ�ġ�bySupportLockΪ1ʱ��dwSurplusLockTime��byRetryLoginTime��Ч
	BYTE  byRetryLoginTime;        //ʣ��ɳ��Ե�½�Ĵ������û������������ʱ���˲�����Ч
	BYTE  byPasswordLevel;      //admin���밲ȫ�ȼ�0-��Ч��1-Ĭ�����룬2-��Ч����,3-���սϸߵ����롣���û�������Ϊ����Ĭ�����루12345�����߷��սϸߵ�����ʱ���ϲ�ͻ�����Ҫ��ʾ�û��������롣      
	BYTE  byProxyType;  //�������ͣ�0-��ʹ�ô���, 1-ʹ��socks5����, 2-ʹ��EHome����
	DWORD dwSurplusLockTime;    //ʣ��ʱ�䣬��λ�룬�û�����ʱ���˲�����Ч
	BYTE  byCharEncodeType;     //�ַ���������
	BYTE  bySupportDev5;//֧��v50�汾���豸������ȡ���豸���ƺ��豸�������Ƴ�����չΪ64�ֽ�
	BYTE  byRes2[254];
}NET_DVR_DEVICEINFO_V40, *LPNET_DVR_DEVICEINFO_V40;
typedef struct
{
	BYTE byBrightness;      /*����,0-255*/
	BYTE byContrast;        /*�Աȶ�,0-255*/
	BYTE bySaturation;      /*���Ͷ�,0-255*/
	BYTE byHue;                /*ɫ��,0-255*/
}NET_DVR_COLOR, *LPNET_DVR_COLOR;
//ʱ���(�ӽṹ)
typedef struct
{
	//��ʼʱ��
	BYTE byStartHour;
	BYTE byStartMin;
	//����ʱ��
	BYTE byStopHour;
	BYTE byStopMin;
}NET_DVR_SCHEDTIME, *LPNET_DVR_SCHEDTIME;

typedef struct
{
	NET_DVR_COLOR      struColor[MAX_TIMESEGMENT_V30];/*ͼ�����(��һ����Ч��������������)*/
	NET_DVR_SCHEDTIME  struHandleTime[MAX_TIMESEGMENT_V30];/*����ʱ���(����)*/
}NET_DVR_VICOLOR, *LPNET_DVR_VICOLOR;

//�ڵ�����(�ӽṹ)
typedef struct
{
	WORD wHideAreaTopLeftX;                /* �ڵ������x���� */
	WORD wHideAreaTopLeftY;                /* �ڵ������y���� */
	WORD wHideAreaWidth;                /* �ڵ�����Ŀ� */
	WORD wHideAreaHeight;                /*�ڵ�����ĸ�*/
}NET_DVR_SHELTER, *LPNET_DVR_SHELTER;

typedef struct
{
	DWORD dwEnableVILostAlarm;                /* �Ƿ������źŶ�ʧ���� ,0-��,1-��*/
											  /* �źŶ�ʧ����������� */
	DWORD   dwHandleType;        //�쳣����,�쳣����ʽ��"��"���   
								 /*0x00: ����Ӧ*/
								 /*0x01: �������Ͼ���*/
								 /*0x02: ��������*/
								 /*0x04: �ϴ�����*/
								 /*0x08: �����������*/
								 /*0x10: ����JPRGץͼ���ϴ�Email*/
								 /*0x20: �������ⱨ��������*/
								 /*0x40: �������ӵ�ͼ(Ŀǰֻ��PCNVR֧��)*/
								 /*0x200: ץͼ���ϴ�FTP*/
								 /*0x1000:ץͼ�ϴ�����*/
	DWORD   dwMaxRelAlarmOutChanNum; //�����ı������ͨ������ֻ�������֧������
	DWORD   dwRelAlarmOut[MAX_ALARMOUT_V40]; /*������������ţ���ֵ��ʾ,���ý��������У����±�0 - dwRelAlarmOut -1��Ч������м�����0xffffffff,�������Ч*/
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]; /*����ʱ��*/
	BYTE    byVILostAlarmThreshold;    /*�źŶ�ʧ������ֵ����ֵ������ֵ����Ϊ�źŶ�ʧ��ȡֵ0-99*/
	BYTE    byRes[63]; //����
}NET_DVR_VILOST_V40, *LPNET_DVR_VILOST_V40;    //�źŶ�ʧ����
typedef struct tagNET_DVR_ETHERNET_IPV6_CFG
{
	DWORD        dwSize;
	BYTE  byState; //IPv6״̬��0-·�ɷ��䣬1-�Զ�����
	BYTE  byRes1[3];
	BYTE  byIPv6[MAX_IPV6_LEN]; //IPv6��ַ
	BYTE  byRes[64];      //����
}NET_DVR_ETHERNET_IPV6_CFG, *LPNET_DVR_ETHERNET_IPV6_CFG;

typedef struct
{
	BYTE byHour;//0~24
	BYTE byMinute;//0~60
	BYTE bySecond;//0~60
	BYTE byRes;
	WORD wMilliSecond; //0~1000
	BYTE byRes1[2];
}NET_DVR_DAYTIME, *LPNET_DVR_DAYTIME;

typedef struct
{
	NET_DVR_DAYTIME  struStartTime; //��ʼʱ��
	NET_DVR_DAYTIME  struStopTime; //����ʱ��
}NET_DVR_SCHEDULE_DAYTIME, *LPNET_DVR_SCHEDULE_DAYTIME;
//�����ṹ
typedef struct
{
	BYTE byObjectSize;//ռ�Ȳ���(0~100)
	BYTE byMotionSensitive; /*�ƶ����������, 0 - 5,Խ��Խ����,0xff�ر�*/
	BYTE byRes[6];
}NET_DVR_DNMODE, *LPNET_DVR_DNMODE;
typedef struct tagNET_VCA_RECT
{
	float fX;               //�߽�����Ͻǵ��X������, 0.001~1
	float fY;               //�߽�����Ͻǵ��Y������, 0.001~1
	float fWidth;           //�߽��Ŀ��, 0.001~1
	float fHeight;          //�߽��ĸ߶�, 0.001~1
}NET_VCA_RECT, *LPNET_VCA_RECT;
typedef struct
{
	BYTE byAreaNo;//������(IPC- 1~8)
	BYTE byRes[3];
	NET_VCA_RECT struRect;//���������������Ϣ(����) size = 16;
	NET_DVR_DNMODE  struDayNightDisable;//�ر�ģʽ
	NET_DVR_DNMODE  struDayModeParam;//����ģʽ
	NET_DVR_DNMODE  struNightModeParam;//ҹ��ģʽ
	BYTE byRes1[8];
}NET_DVR_MOTION_MULTI_AREAPARAM, *LPNET_DVR_MOTION_MULTI_AREAPARAM;
typedef struct
{
	BYTE byDayNightCtrl;//��ҹ���� 0~�ر�,1~�Զ��л�,2~��ʱ�л�(Ĭ�Ϲر�)
	BYTE byAllMotionSensitive; /*�ƶ����������, 0 - 5,Խ��Խ����,0xff�رգ�ȫ������������ȷ�Χ*/
	BYTE byRes[2];//
	NET_DVR_SCHEDULE_DAYTIME struScheduleTime;//�л�ʱ��  16
	NET_DVR_MOTION_MULTI_AREAPARAM struMotionMultiAreaParam[MAX_MULTI_AREA_NUM];//���֧��24������
	BYTE byRes1[60];
}NET_DVR_MOTION_MULTI_AREA, *LPNET_DVR_MOTION_MULTI_AREA; //1328

typedef struct
{
	BYTE byMotionScope[64][96];        /*�������,0-96λ,��ʾ64��,����96*64��С���,Ŀǰ��Ч����22*18,Ϊ1��ʾ���ƶ��������,0-��ʾ����*/
	BYTE byMotionSensitive;            /*�ƶ����������, 0 - 5,Խ��Խ����,0xff�ر�*/
	BYTE byRes[3];
}NET_DVR_MOTION_SINGLE_AREA, *LPNET_DVR_MOTION_SINGLE_AREA;

typedef struct
{
	NET_DVR_MOTION_SINGLE_AREA  struMotionSingleArea; //��ͨģʽ�µĵ�������
	NET_DVR_MOTION_MULTI_AREA struMotionMultiArea; //ר��ģʽ�µĶ���������    
}NET_DVR_MOTION_MODE_PARAM, *LPNET_DVR_MOTION_MODE_PARAM;
typedef struct
{
	NET_DVR_MOTION_MODE_PARAM  struMotionMode; //(5.1.0����)
	BYTE byEnableHandleMotion;        /* �Ƿ����ƶ���� 0���� 1����*/
	BYTE byEnableDisplay;    /*�����ƶ���������ʾ��0-��1-��*/
	BYTE byConfigurationMode; //0~��ͨ,1~ר��(5.1.0����)
	BYTE byRes1; //�����ֽ�
				 /* �쳣����ʽ */
	DWORD   dwHandleType;        //�쳣����,�쳣����ʽ��"��"���   
								 /*0x00: ����Ӧ*/
								 /*0x01: �������Ͼ���*/
								 /*0x02: ��������*/
								 /*0x04: �ϴ�����*/
								 /*0x08: �����������*/
								 /*0x10: ����JPRGץͼ���ϴ�Email*/
								 /*0x20: �������ⱨ��������*/
								 /*0x40: �������ӵ�ͼ(Ŀǰֻ��PCNVR֧��)*/
								 /*0x200: ץͼ���ϴ�FTP*/
								 /*0x1000: ץͼ�ϴ�����*/
	DWORD   dwMaxRelAlarmOutChanNum; //�����ı������ͨ������ֻ�������֧������
	DWORD   dwRelAlarmOut[MAX_ALARMOUT_V40]; //ʵ�ʴ����ı�������ţ���ֵ��ʾ,���ý��������У����±�0 - dwRelAlarmOut -1��Ч������м�����0xffffffff,�������Ч
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]; /*����ʱ��*/
																	/*������¼��ͨ��*/
	DWORD     dwMaxRecordChanNum;   //�豸֧�ֵ�������¼��ͨ����-ֻ��
	DWORD     dwRelRecordChan[MAX_CHANNUM_V40];     /* ʵ�ʴ���¼��ͨ������ֵ��ʾ,���ý��������У����±�0 - dwRelRecordChan -1��Ч������м�����0xffffffff,�������Ч*/
	BYTE  byRes[128]; //�����ֽ�
}NET_DVR_MOTION_V40, *LPNET_DVR_MOTION_V40;
typedef struct
{
	DWORD dwEnableHideAlarm;                /* �Ƿ������ڵ�������0-��1-�������ȣ�2-�������ȣ�3-��������*/
	WORD wHideAlarmAreaTopLeftX;            /* �ڵ������x���� */
	WORD wHideAlarmAreaTopLeftY;            /* �ڵ������y���� */
	WORD wHideAlarmAreaWidth;                /* �ڵ�����Ŀ� */
	WORD wHideAlarmAreaHeight;                /*�ڵ�����ĸ�*/
											  /* �źŶ�ʧ����������� */
	DWORD   dwHandleType;        //�쳣����,�쳣����ʽ��"��"���   
								 /*0x00: ����Ӧ*/
								 /*0x01: �������Ͼ���*/
								 /*0x02: ��������*/
								 /*0x04: �ϴ�����*/
								 /*0x08: �����������*/
								 /*0x10: ����JPRGץͼ���ϴ�Email*/
								 /*0x20: �������ⱨ��������*/
								 /*0x40: �������ӵ�ͼ(Ŀǰֻ��PCNVR֧��)*/
								 /*0x200: ץͼ���ϴ�FTP*/
								 /*0x1000:ץͼ�ϴ�����*/
	DWORD   dwMaxRelAlarmOutChanNum; //�����ı������ͨ������ֻ�������֧������
	DWORD   dwRelAlarmOut[MAX_ALARMOUT_V40]; /*������������ţ���ֵ��ʾ,���ý��������У����±�0 - dwRelAlarmOut -1��Ч������м�����0xffffffff,�������Ч*/
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]; /*����ʱ��*/
	BYTE  byRes[64]; //����
}NET_DVR_HIDEALARM_V40, *LPNET_DVR_HIDEALARM_V40; //�ڵ�����
typedef struct
{
	BYTE byRed;        //RGB��ɫ�������еĺ�ɫ
	BYTE byGreen;    //RGB��ɫ�������е���ɫ
	BYTE byBlue;    //RGB��ɫ�������е���ɫ
	BYTE byRes;        //����
}NET_DVR_RGB_COLOR, *LPNET_DVR_RGB_COLOR;
typedef struct
{
	DWORD  dwSize;
	BYTE  sChanName[NAME_LEN];
	DWORD  dwVideoFormat;    /* ֻ�� ��Ƶ��ʽ 1-NTSC 2-PAL  */
	NET_DVR_VICOLOR struViColor;//    ͼ�������ʱ�������
								//��ʾͨ����
	DWORD  dwShowChanName; // Ԥ����ͼ�����Ƿ���ʾͨ������,0-����ʾ,1-��ʾ
	WORD    wShowNameTopLeftX;                /* ͨ��������ʾλ�õ�x���� */
	WORD    wShowNameTopLeftY;                /* ͨ��������ʾλ�õ�y���� */
											  //��˽�ڵ�
	DWORD  dwEnableHide;        /* �Ƿ������ڵ� ,0-��,1-��*/
	NET_DVR_SHELTER struShelter[MAX_SHELTERNUM];
	//OSD
	DWORD  dwShowOsd;// Ԥ����ͼ�����Ƿ���ʾOSD,0-����ʾ,1-��ʾ
	WORD   wOSDTopLeftX;                /* OSD��x���� */
	WORD   wOSDTopLeftY;                /* OSD��y���� */
	BYTE    byOSDType;                    /* OSD����(��Ҫ�������ո�ʽ) */
										  /* 0: XXXX-XX-XX ������ */
										  /* 1: XX-XX-XXXX ������ */
										  /* 2: XXXX��XX��XX�� */
										  /* 3: XX��XX��XXXX�� */
										  /* 4: XX-XX-XXXX ������*/
										  /* 5: XX��XX��XXXX�� */
										  /*6: xx/xx/xxxx(��/��/��) */
										  /*7: xxxx/xx/xx(��/��/��) */
										  /*8: xx/xx/xxxx(��/��/��)*/
	BYTE    byDispWeek;                /* �Ƿ���ʾ���� */
	BYTE    byOSDAttrib;                /* OSD����:͸������˸ */
										/* 0: ����ʾOSD */
										/* 1: ͸������˸ */
										/* 2: ͸��������˸ */
										/* 3: ��͸������˸ */
										/* 4: ��͸��������˸ */
	BYTE    byHourOSDType;                /* OSDСʱ��:0-24Сʱ��,1-12Сʱ�� */
	BYTE    byFontSize;      //16*16(��)/8*16(Ӣ)��1-32*32(��)/16*32(Ӣ)��2-64*64(��)/32*64(Ӣ)  3-48*48(��)/24*48(Ӣ) 4-24*24(��)/12*24(Ӣ) 5-96*96(��)/48*96(Ӣ) 6-128*128(��)/64*128(Ӣ) 0xff-����Ӧ(adaptive)
	BYTE    byOSDColorType;     //0-Ĭ�ϣ��ڰף���1-�Զ���
	BYTE    byAlignment;//���뷽ʽ 0-����Ӧ��1-�Ҷ���, 2-�����
	BYTE    byOSDMilliSecondEnable;//��Ƶ����ʱ��֧�ֺ��룻0~������, 1-����
	NET_DVR_VILOST_V40 struVILost;  //��Ƶ�źŶ�ʧ������֧���飩
	NET_DVR_VILOST_V40 struAULost;  /*��Ƶ�źŶ�ʧ������֧���飩*/
	NET_DVR_MOTION_V40 struMotion;  //�ƶ���ⱨ����֧���飩
	NET_DVR_HIDEALARM_V40 struHideAlarm;  //�ڵ�������֧���飩
	NET_DVR_RGB_COLOR    struOsdColor;//OSD��ɫ
	BYTE    byRes[124];
}NET_DVR_PICCFG_V40, *LPNET_DVR_PICCFG_V40;
//���޸ĵ��豸�������
typedef struct tagSADP_DEV_NET_PARAM
{
	char			szIPv4Address[16];		// IPv4��ַ
	char			szIPv4SubNetMask[16];	// IPv4��������
	char			szIPv4Gateway[16];		// IPv4����
	char			szIPv6Address[128];		// IPv6��ַ
	char			szIPv6Gateway[128];		// IPv6����
	unsigned short	wPort;					// �豸�����˿�
	unsigned char	byIPv6MaskLen;			// IPv6���볤��
	unsigned char	byDhcpEnable;			// DHCPʹ��
	unsigned short	wHttpPort;				//HTTP�˿�
	unsigned char	byRes[126];
}SADP_DEV_NET_PARAM, *LPSADP_DEV_NET_PARAM;
// ��ʼ������
typedef struct tagNETSDK_INIT_PARAM
{
	int                 nThreadNum;         // ָ��NetSDK�������紦���߳���, ��ֵΪ0ʱ, ʹ���ڲ�Ĭ��ֵ
	BYTE                bReserved[1024];    // �����ֽ�
}NETSDK_INIT_PARAM, *LPNETSDK_INIT_PARAM;
// ���õ���ʱ����ز���
typedef struct
{
	int                 nWaittime;                              // �ȴ���ʱʱ��(����Ϊ��λ),Ϊ0Ĭ��5000ms
	int                 nConnectTime;                           // ���ӳ�ʱʱ��(����Ϊ��λ),Ϊ0Ĭ��1500ms
	int                 nConnectTryNum;                         // ���ӳ��Դ���,Ϊ0Ĭ��1��
	int                 nSubConnectSpaceTime;                   // ������֮��ĵȴ�ʱ��(����Ϊ��λ),Ϊ0Ĭ��10ms
	int                 nGetDevInfoTime;                        // ��ȡ�豸��Ϣ��ʱʱ��,Ϊ0Ĭ��1000ms
	int                 nConnectBufSize;                        // ÿ�����ӽ������ݻ����С(�ֽ�Ϊ��λ),Ϊ0Ĭ��250*1024
	int                 nGetConnInfoTime;                       // ��ȡ��������Ϣ��ʱʱ��(����Ϊ��λ),Ϊ0Ĭ��1000ms
	int                 nSearchRecordTime;                      // ��ʱ���ѯ¼���ļ��ĳ�ʱʱ��(����Ϊ��λ),Ϊ0Ĭ��Ϊ3000ms
	int                 nsubDisconnetTime;                      // ��������Ӷ��ߵȴ�ʱ��(����Ϊ��λ),Ϊ0Ĭ��Ϊ60000ms
	BYTE                byNetType;                              // ��������, 0-LAN, 1-WAN
	BYTE                byPlaybackBufSize;                      // �ط����ݽ��ջ����С��MΪ��λ��,Ϊ0Ĭ��Ϊ4M
	BYTE                bDetectDisconnTime;                     // ����������ʱ��(��λΪ��),Ϊ0Ĭ��Ϊ60s,��Сʱ��Ϊ2s
	BYTE                bKeepLifeInterval;                      // ���������ͼ��(��λΪ��),Ϊ0Ĭ��Ϊ10s,��С���Ϊ2s
	int                 nPicBufSize;                            // ʵʱͼƬ���ջ����С���ֽ�Ϊ��λ��,Ϊ0Ĭ��Ϊ2*1024*1024
	BYTE                bReserved[4];                           // �����ֶ��ֶ�
} NET_PARAM;

// �첽�����豸�ص�(pDevNetInfo�ڴ���SDK�ڲ������ͷ�)
typedef void (CALLBACK *fSearchDevicesCB)(DEVICE_NET_INFO_EX *pDevNetInfo, void* pUserData);
typedef void (CALLBACK *fDisConnect)(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
// �������ӻָ��ص�����ԭ��
typedef void (CALLBACK *fHaveReConnect)(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
typedef void (CALLBACK *PDEVICE_FIND_CALLBACK)(const SADP_DEVICE_INFO *lpDeviceInfo, void *pUserData);

typedef BOOL (__stdcall *cLIENT_Init)(fDisConnect cbDisConnect, LDWORD dwUser);
typedef void (__stdcall *cLIENT_SetAutoReconnect)(fHaveReConnect cbAutoConnect, LDWORD dwUser);
typedef void (__stdcall *cLIENT_SetConnectTime)(int nWaitTime, int nTryTimes);
typedef LLONG (__stdcall *cLIENT_StartSearchDevices)(fSearchDevicesCB cbSearchDevices, void* pUserData, char* szLocalIp );
typedef BOOL (__stdcall *cLIENT_SearchDevicesByIPs)(DEVICE_IP_SEARCH_INFO* pIpSearchInfo, fSearchDevicesCB cbSearchDevices, LDWORD dwUserData, char* szLocalIp, DWORD dwWaitTime);
typedef BOOL (__stdcall *sADP_Start_V30)(PDEVICE_FIND_CALLBACK pDeviceFindCallBack, int bInstallNPF, void* pUserData);
typedef BOOL (__stdcall *sADP_Stop)(void);
typedef BOOL (__stdcall *sADP_GetDeviceConfig)(const char* sDevSerialNO, unsigned int dwCommand, void* lpInBuffer, unsigned int  dwinBuffSize, void *lpOutBuffer, unsigned int  dwOutBuffSize);
typedef LLONG (__stdcall *cLIENT_LoginEx2)(const char *pchDVRIP, WORD wDVRPort, const char *pchUserName, const char *pchPassword, EM_LOGIN_SPAC_CAP_TYPE emSpecCap, void* pCapParam, LPNET_DEVICEINFO_Ex lpDeviceInfo, int *error);
typedef BOOL  (__stdcall *cLIENT_PacketData)(char* szCommand, LPVOID lpInBuffer, DWORD dwInBufferSize, char* szOutBuffer, DWORD dwOutBufferSize);
typedef BOOL (__stdcall *cLIENT_SetNewDevConfig)(LLONG lLoginID, char* szCommand, int nChannelID, char* szInBuffer, DWORD dwInBufferSize, int *error, int *restart, int waittime);
typedef LONG (__stdcall *nET_DVR_Login_V40)(LPNET_DVR_USER_LOGIN_INFO pLoginInfo, LPNET_DVR_DEVICEINFO_V40 lpDeviceInfo);
typedef BOOL (__stdcall *nET_DVR_Init)();
typedef BOOL (__stdcall *nET_DVR_SetReconnect)(DWORD dwInterval, BOOL bEnableRecon);
typedef BOOL (__stdcall *nET_DVR_GetDVRConfig)(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
typedef BOOL (__stdcall *nET_DVR_SetDVRConfig)(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize);
typedef DWORD (__stdcall *cLIENT_GetLastError)();
typedef BOOL  (__stdcall *cLIENT_GetNewDevConfig)(LLONG lLoginID, char* szCommand, int nChannelID, char* szOutBuffer, DWORD dwOutBufferSize, int *error, int waittime);
typedef BOOL  (__stdcall *cLIENT_ParseData)(char* szCommand, char* szInBuffer, LPVOID lpOutBuffer, DWORD dwOutBufferSize, void* pReserved);
typedef BOOL (__stdcall *cLIENT_ModifyDevice)(DEVICE_NET_INFO_EX   *pDevNetInfo,DWORD dwWaitTime,int *iError,char *szLocalIp,void *reserved);
typedef BOOL (__stdcall *sADP_ModifyDeviceNetParam)(const char* sMAC, const char* sPassword, const SADP_DEV_NET_PARAM* lpNetParam);
typedef BOOL (__stdcall *cLIENT_Logout)(LLONG lLoginID);
typedef BOOL (__stdcall *nET_DVR_Logout)(LONG lUserID);
typedef BOOL (__stdcall *cLIENT_InitEx)(fDisConnect cbDisConnect, LDWORD dwUser, LPNETSDK_INIT_PARAM lpInitParam);
typedef void (__stdcall *cLIENT_SetNetworkParam)(NET_PARAM *pNetParam);
typedef unsigned int(__stdcall *sADP_GetLastError)(void);
typedef BOOL (__stdcall *sADP_ActivateDevice)(const char* sDevSerialNO, const char* sCommand);
typedef DWORD (__stdcall *nET_DVR_GetLastError)();



