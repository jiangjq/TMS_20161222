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
		
//常量定义 
#define  DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else    
#define  TRUE       1
#define  FALSE      0

//#define  DISCHRGTIME      0.2         //四线圈焦点切换时，放电时间（s）

//#define  MaxTemp          35          //允许工作的最高温度
		
/* 线圈类型 */
#define  COIL_FAIL     -2  
#define  COIL_NO       -1
#define  COIL_CC_1      0  
#define  COIL_SGL_8     1
#define  COIL_DBL_8     2  
#define  COIL_CC_4      3
		
/* 焦点类型 */  
#define  FCS_DISABLE   -1
#define  FCS_NO         0 		
#define  FCS_4_TLBR     1
#define  FCS_1_TOP      2  
#define  FCS_1_LFT      3
#define  FCS_1_BTM      4  
#define  FCS_1_RT       5
#define  FCS_L_HZ       6  
#define  FCS_L_VTC      7

/* TAB页 */  		
#define PAGE_CC_1       0
#define PAGE_SGL_8      1
#define PAGE_DBL_8      2
#define PAGE_CC_4       3
		
/* 刺激类型 */  
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
/* 与电刺激通信协议************************************************************ 
 * 电刺激程序启动，给磁刺激发送字符串"connect"
 * 开始刺激指令，磁刺激发送字符串"start"，返回应答："start ok"     
 * 停止刺激指令：磁刺激发送字符串"end"，返回应答："end ok"  
 * 其余指令应答："error cmd"
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


//定义一个结构体
typedef struct{
		int   power;              //刺激强度
		float volt; 			  //刺激电压
		float frequency;	      //最高频率
	}StimPara;

StimPara *pStimPara_CC1      = 0;		//圆环线圈 刺激参数 
StimPara *pStimPara_SGL8     = 0;		//单8线圈 刺激参数 
StimPara *pStimPara_DBL8_A   = 0;		//双8线圈A 刺激参数  
StimPara *pStimPara_DBL8_B   = 0;		//双8线圈B 刺激参数
StimPara *pStimPara_CC4      = 0;		//四线圈 刺激参数 

//float64     *data = NULL;  
char strMsg[1024];

// Static TaskHandle 
static	TaskHandle  TempAcqtaskHandle = 0; 		  //温度采集
static	TaskHandle  PwrOktaskHandle = 0; 		  //电源OK 
static	TaskHandle  SglDisOktaskHandle = 0;  	  //单次刺激按钮 
static	TaskHandle  CoilDetecttaskHandle = 0;  	  //线圈监测   
static	TaskHandle  Ctrl00usTaskHandle = 0; 		  //100uS CTRL2输出   

static CmtThreadPoolHandle  StimpoolHandle = 0;   //刺激线程池


// 全局变量
static int nSelCoilNum 		= COIL_NO;		  	// 代表线圈类型，-2：线圈故障；   -1：没接线圈；  0：圆环线圈；1：8字线圈；2：双8字线圈；3：四线圈 
static int nSelFcsNum 		= FCS_DISABLE; 		// 代表焦点类型，-1：不能选择焦点；0：没选择焦点；1：焦点1；   2：焦点2；3：焦点3；...    
static int nSelStimNum 		= NO_SEL_STIM;  	//刺激方式选择
volatile int bStim_Quit  	= FALSE;	 	 	//刺激停止标志
volatile int bStatus_Quit 	= FALSE;  			//状态监测停止标志

volatile int bElectroStim  	= FALSE;	 	 	//电刺激程序启动标志 
volatile int bElectroReady 	= FALSE;	 	 	//电刺激程序准备好标志
												
static int nTempAcqNum  = 0;	            	//第一路温度测量个数计数
float64  TempAcqArray[10];						//第一路温度计算数组
static int nTempAcqNum2  = 0;	            	//第二路温度测量个数计数
float64  TempAcqArray2[10];						//第二路温度计算数组

static double DisChrgTime       = 0.20;             //放电时间
static int    CoilTempMax       = 0;                //最高温度
static int    TempCoeffi       = 10;                //温度模块系数 
static int    nPowerErrorNum    = 0;

static int          nSelRow           = 0;   
static int          bFirstTemp        = TRUE;
static float64		OldTempVal        = 0;
static int          bFirstTemp2        = TRUE;
static float64		OldTempVal2        = 0;
static int  		bStimIng          = FALSE; 
//刺激相关任务

static uInt8        *pACircle  	= NULL ; 
static uInt8        *pBCircle  	= NULL ; 	 
static uInt8        *pWave  	= NULL ; 	 //刺激波形

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
void Sys_Init( );                     										//系统初始化  
void Focus_Sel(int n);				                                        //焦点选择命令
int  DisplayImage( );														//加载图片  
int  StatusDetect_Task( );                                                  //数据采集任务 
void StatusDetect_Exit( );                                                  //停止状态监测 
void StimProgress_Exit( );                                                  //停止刺激  
void CoilDetect_Task( );  										    		//线圈探测 
void PwrOk_Task( );															//电源探测  
void SglDisOk_Task( );														//单次刺激  
void TmpAcq_Task( );														//温度采集  
void SendMsgToLog( char str[] );											//保存到日志
void ClearAllStimMode( );
void ShowStimSlide( double stimtime );
void SetFullScreen( );
void Send_FCS_SEL_Command(int nChnlNum);
int  ReadSysPara( );
int  WriteSysPara( );
void ClearFocusSel( ) ;
void DisCharge( double second );
int  CVICALLBACK StatusAsyncTimerCallback (int reserved, int theTimerId, int event,	  //异步时钟处理函数 
                                 void *callbackData, int eventData1,int eventData2);
int CVICALLBACK StimAsyncTimerCallback (int reserved, int theTimerId, int event,
                                 void *callbackData, int eventData1,int eventData2);
int CVICALLBACK StatusDetectThreadFunction (void *functionData);                   //数据采集函数
int CVICALLBACK Stim_ThreadFunction (void *functionData);
int Send_Stim_Volt_Command( float64 volt[] );
int Send_CHRG_DisCHRG_Command(  int stim_cycle,double stim_time,double stim_freq  );
void Send_Ctr0_Command (int clock_num );
void ShowSysTime();
int DelayTime( double second );
void Free_Memory( );
int IsComputerAuthorized( );

//刺激函数
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

/*异步定时时钟*/
static int          g_StatusTimerId = 0; 								     		//异步定时器ID
static int          g_StatusTimerDelay = 10;	                                    //异步定时器时间（毫秒）
static int          g_StimTimerId = 0; 								     	   		//异步定时器ID
static int          g_StimTimerDelay = 10;	                                   		//异步定时器时间（毫秒）
/*全局事件计时，作为系统测量的基准*/
static int	   		gTimeCounter = 0;
static int	   		gStimTime = 0; 
static int	   		gStimCounter = 0; 

//static int          bFirstTemp = 1;                                                 //第一次测量的温度值
//static int          Temp_Old   = 1;                                                 //第一次测量的温度值 
/*数据采集线程终止命令*/
volatile int gQuitStatusAcqTread = 0;  


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Self_Def_H__ */
