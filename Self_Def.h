//==============================================================================
//
// Title:       Self_Def.h
// Purpose:     A short description of the interface.
//
// Created on:  2015/11/16 at 14:52:56 by tms.
// Copyright:   PKU. All Rights Reserved.
//
//==============================================================================

#ifndef __Self_Def_H__
#define __Self_Def_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
		
//�������� 
#define  DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else    
#define  TRUE       1
#define  FALSE      0

//#define  DISCHRGTIME      0.2         //����Ȧ�����л�ʱ���ŵ�ʱ�䣨s��

//#define  MaxTemp          35          //������������¶�
		
/* ��Ȧ���� */
#define  COIL_FAIL     -2  
#define  COIL_NO       -1
#define  COIL_CC_1      0  
#define  COIL_SGL_8     1
#define  COIL_DBL_8     2  
#define  COIL_CC_4      3
		
/* �������� */  
#define  FCS_DISABLE   -1
#define  FCS_NO         0 		
#define  FCS_4_TLBR     1
#define  FCS_1_TOP      2  
#define  FCS_1_LFT      3
#define  FCS_1_BTM      4  
#define  FCS_1_RT       5
#define  FCS_L_HZ       6  
#define  FCS_L_VTC      7

/* TABҳ */  		
#define PAGE_CC_1       0
#define PAGE_SGL_8      1
#define PAGE_DBL_8      2
#define PAGE_CC_4       3
		
/* �̼����� */  
#define  NO_SEL_STIM     	0  
#define  CC1_SGL_STIM     	1
#define  CC1_RPT_STIM       2 		
#define  CC1_SQC_STIM       3
		
#define  SGL8_SGL_STIM      4
#define  SGL8_RPT_STIM      5 		
#define  SGL8_SQC_STIM      6
		
#define  DBL8_SGL_STIM      7
#define  DBL8_RPT_STIM      8 		
#define  DBL8_SQC_STIM      9
		
#define  CC4_SGL_STIM      10
#define  CC4_RPT_STIM      11 		
#define  CC4_SQC_STIM      12

 //UDP By Wangcz 20161204
/* ���̼�ͨ��Э��************************************************************ 
 * ��̼��������������Ŵ̼������ַ���"connect"
 * ��ʼ�̼�ָ��Ŵ̼������ַ���"start"������Ӧ��"start ok"     
 * ֹͣ�̼�ָ��Ŵ̼������ַ���"end"������Ӧ��"end ok"  
 * ����ָ��Ӧ��"error cmd"
 *****************************************************************************/ 		
#define SENDER_PORT          60100      // arbitrarily chosen from the Dynamic/Private port range (49152-65535)
#define READER_PORT          50100      //
#define HOST_IP 			 "127.0.0.1" 
		
#define MAX_IP_INPUT_LENGTH 20
		
//==============================================================================    
static unsigned int     readerChannel = 0;   
static unsigned int     writerChannel = 0;     
//-----------------------------------------------------------------------------
int CVICALLBACK UDPCallback (unsigned channel, int eventType, int errCode, void *callbackData);

//==============================================================================
// panelHandle
static int panelHandle;
static int panelSysHandle;   
static int panelPatientHandle;
static int TabPanelHandle;
static int TabPanelHandle_Temp; 


//����һ���ṹ��
typedef struct{
		int   power;              //�̼�ǿ��
		float volt; 			  //�̼���ѹ
		float frequency;	      //���Ƶ��
	}StimPara;

StimPara *pStimPara_CC1      = 0;		//Բ����Ȧ �̼����� 
StimPara *pStimPara_SGL8     = 0;		//��8��Ȧ �̼����� 
StimPara *pStimPara_DBL8_A   = 0;		//˫8��ȦA �̼�����  
StimPara *pStimPara_DBL8_B   = 0;		//˫8��ȦB �̼�����
StimPara *pStimPara_CC4      = 0;		//����Ȧ �̼����� 

//float64     *data = NULL;  
char strMsg[1024];

// Static TaskHandle 
static	TaskHandle  TempAcqtaskHandle = 0; 		  //�¶Ȳɼ�
static	TaskHandle  PwrOktaskHandle = 0; 		  //��ԴOK 
static	TaskHandle  SglDisOktaskHandle = 0;  	  //���δ̼���ť 
static	TaskHandle  CoilDetecttaskHandle = 0;  	  //��Ȧ���   
static	TaskHandle  Ctrl00usTaskHandle = 0; 		  //100uS CTRL2���   

static CmtThreadPoolHandle  StimpoolHandle = 0;   //�̼��̳߳�


// ȫ�ֱ���
static int nSelCoilNum 		= COIL_NO;		  	// ������Ȧ���ͣ�-2����Ȧ���ϣ�   -1��û����Ȧ��  0��Բ����Ȧ��1��8����Ȧ��2��˫8����Ȧ��3������Ȧ 
static int nSelFcsNum 		= FCS_DISABLE; 		// ���������ͣ�-1������ѡ�񽹵㣻0��ûѡ�񽹵㣻1������1��   2������2��3������3��...    
static int nSelStimNum 		= NO_SEL_STIM;  	//�̼���ʽѡ��
volatile int bStim_Quit  	= FALSE;	 	 	//�̼�ֹͣ��־
volatile int bStatus_Quit 	= FALSE;  			//״̬���ֹͣ��־

volatile int bElectroStim  	= FALSE;	 	 	//��̼�����������־ 
volatile int bElectroReady 	= FALSE;	 	 	//��̼�����׼���ñ�־
												
static int nTempAcqNum  = 0;	            	//��һ·�¶Ȳ�����������
float64  TempAcqArray[10];						//��һ·�¶ȼ�������
static int nTempAcqNum2  = 0;	            	//�ڶ�·�¶Ȳ�����������
float64  TempAcqArray2[10];						//�ڶ�·�¶ȼ�������

static double DisChrgTime       = 0.20;             //�ŵ�ʱ��
static int    CoilTempMax       = 0;                //����¶�
static int    TempCoeffi       = 10;                //�¶�ģ��ϵ�� 
static int    nPowerErrorNum    = 0;

static int          nSelRow           = 0;   
static int          bFirstTemp        = TRUE;
static float64		OldTempVal        = 0;
static int          bFirstTemp2        = TRUE;
static float64		OldTempVal2        = 0;
static int  		bStimIng          = FALSE; 
//�̼��������

static uInt8        *pACircle  	= NULL ; 
static uInt8        *pBCircle  	= NULL ; 	 
static uInt8        *pWave  	= NULL ; 	 //�̼�����

static float64      volt[2]					={0.8,0.8};
static TaskHandle	gFcsSeltaskHandle 		= 0;
static TaskHandle	gStimVolttaskHandle 	= 0; 
static TaskHandle	gCtr0taskHandle 		= 0;  
static TaskHandle	gChrgDisChrgtaskHandle 	= 0;
static TaskHandle	gDisChargetaskHandle 	= 0;        


static int Pre_Coil[4] = {0,0,0,1};								    
static int gHighRateMeasureEnable = 0;
static int gLowRateMeasureEnable = 0;   
static int bCB_State = TRUE;  
static int nAtvPageNum = 0;  
static int gStatusDetectThreadFunctionId = 0;
static int gStim_ThreadFunctionId = 0; 


// Global functions
void Sys_Init( );                     										//ϵͳ��ʼ��  
void Focus_Sel(int n);				                                        //����ѡ������
int  DisplayImage( );														//����ͼƬ  
int  StatusDetect_Task( );                                                  //���ݲɼ����� 
void StatusDetect_Exit( );                                                  //ֹͣ״̬��� 
void StimProgress_Exit( );                                                  //ֹͣ�̼�  
void CoilDetect_Task( );  										    		//��Ȧ̽�� 
void PwrOk_Task( );															//��Դ̽��  
void SglDisOk_Task( );														//���δ̼�  
void TmpAcq_Task( );														//�¶Ȳɼ�  
void SendMsgToLog( char str[] );											//���浽��־
void ClearAllStimMode( );
void ShowStimSlide( double stimtime );
void SetFullScreen( );
void Send_FCS_SEL_Command(int nChnlNum);
int  ReadSysPara( );
int  WriteSysPara( );
void ClearFocusSel( ) ;
void DisCharge( double second );
int  CVICALLBACK StatusAsyncTimerCallback (int reserved, int theTimerId, int event,	  //�첽ʱ�Ӵ����� 
                                 void *callbackData, int eventData1,int eventData2);
int CVICALLBACK StimAsyncTimerCallback (int reserved, int theTimerId, int event,
                                 void *callbackData, int eventData1,int eventData2);
int CVICALLBACK StatusDetectThreadFunction (void *functionData);                   //���ݲɼ�����
int CVICALLBACK Stim_ThreadFunction (void *functionData);
int Send_Stim_Volt_Command( float64 volt[] );
int Send_CHRG_DisCHRG_Command(  int stim_cycle,double stim_time,double stim_freq  );
void Send_Ctr0_Command (int clock_num );
void ShowSysTime();
int DelayTime( double second );
void Free_Memory( );
int IsComputerAuthorized( );

//�̼�����
int Cc1_Sgl_Stim( );
int Cc1_Rpt_Stim( );   
int Cc1_Sqc_Stim( );

int Sgl8_Sgl_Stim( );
int Sgl8_Rpt_Stim( );   
int Sgl8_Sqc_Stim( ); 

int Dbl8_Sgl_Stim( );
int Dbl8_Rpt_Stim( );   
int Dbl8_Sqc_Stim( ); 

int Cc4_Sgl_Stim( );
int Cc4_Rpt_Stim( );   
int Cc4_Sqc_Stim( ); 

/*�첽��ʱʱ��*/
static int          g_StatusTimerId = 0; 								     		//�첽��ʱ��ID
static int          g_StatusTimerDelay = 10;	                                    //�첽��ʱ��ʱ�䣨���룩
static int          g_StimTimerId = 0; 								     	   		//�첽��ʱ��ID
static int          g_StimTimerDelay = 10;	                                   		//�첽��ʱ��ʱ�䣨���룩
/*ȫ���¼���ʱ����Ϊϵͳ�����Ļ�׼*/
static int	   		gTimeCounter = 0;
static int	   		gStimTime = 0; 
static int	   		gStimCounter = 0; 

//static int          bFirstTemp = 1;                                                 //��һ�β������¶�ֵ
//static int          Temp_Old   = 1;                                                 //��һ�β������¶�ֵ 
/*���ݲɼ��߳���ֹ����*/
volatile int gQuitStatusAcqTread = 0;  


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Self_Def_H__ */
