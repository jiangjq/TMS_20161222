//==============================================================================
//
// Title:       TMS
// Purpose:     TMS 控制平台
//
// Created on:  2015/11/1 at 18:25:26 by lxh.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <windows.h> 
#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include <NIDAQmx.h>    
#include <stdio.h>     
#include "TMS.h"
#include "toolbox.h"
#include "Self_Def.h" 
#include "asynctmr.h" 
#include "string.h"
 

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
    
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "TMS.uir", PANEL));
    
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));

	//读取刺激参数文件
	if( ReadStimPara( ) == FALSE)
	{
		SendMsgToLog("刺激参数文件丢失，软件已关闭...");
		return 0;
	}
	
	Sys_Init();                                                                          //系统初始化
	StatusDetect_Task( ); //状态监测
	SetFullScreen( );
	
		
	
	errChk (RunUserInterface ());
	
Error:
    /* clean up */
    DiscardPanel (panelHandle);
    return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
	{
		StatusDetect_Exit( );
		StimProgress_Exit( ); 
		QuitUserInterface (0); 
	}
        
		
    return 0;
}
void SetFullScreen( )
{
	SetPanelSize (panelHandle, 1080, 1920 );
	SetPanelPos (panelHandle, 0, 0);
}
int ReadStimPara( )
{
	FILE *fp = NULL;  
	char filename[100];
	char projectDir[ MAX_PATHNAME_LEN ];
	char fullPath[ MAX_PATHNAME_LEN ]; 
	int  i;
	
	if (GetProjectDir (projectDir) < 0)
	{
		return FALSE ;
	}
	
    strcpy(filename, "para\\StimPara.txt");
	MakePathname (projectDir, filename, fullPath); 

	if(( fp = fopen(fullPath,"r")) != NULL )
	{
	//	fscanf(fp,"%d",&countPT100);
	//	//申请动态数组使用的内存块
		
		pStimPara = (StimPara *)malloc(sizeof(StimPara)*100);
		if ( pStimPara == NULL )        // 内存申请失败,提示退出
		{
			fclose(fp);
			return FALSE ;             // 终止程序运行,返回操作系统
		}
		 
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%d %f  %f ",&pStimPara[i].power,&pStimPara[i].volt,&pStimPara[i].frequency);
		}
	}
	fclose(fp);	
	return TRUE;
}


void Focus_Sel(int n)														//焦点选择命令  
{

	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle );
//	GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_A,&bAState );
	
	if ( nSelFcsNum == n )  //如果是重复点击，则不做任何操作
	{
		return;
	}
	
	nSelFcsNum = n;

	switch( n )
	
	{
		case FCS_4_TLBR:   //焦点1：4个焦点
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_DK_RED); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_WHITE); 
			
			break;
			
		case FCS_1_TOP:    //焦点2：单个焦点（上）
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_DK_RED); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_WHITE);
		
			break;	
			
		case FCS_1_LFT:
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_DK_RED); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_WHITE);
		
			break;	
			
		case FCS_1_BTM:
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_DK_RED); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_WHITE); 
		 
			break;
			
		case FCS_1_RT:
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_DK_RED); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_WHITE); ; 
		
			break;
			
		case FCS_L_HZ:
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_DK_RED); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_WHITE); ; 
		
			break;
			
		case FCS_L_VTC:
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_DK_RED); ;
		
			break;			
		
		
	}
	
}
void Sys_Init( )                     												             		//系统初始化 
{
	
	/* 加载所有图片 */

	DisplayImage( );   
	
	gOneSecondMeasureEnable = 0;
	gOneTenthSecondMeasureEnable = 0; 
	
	
	//线圈和焦点	
	nSelCoilNum = COIL_NO;   
	nSelFcsNum = FCS_NO;
	nSelStimNum = FALSE;
	
	/* 设置电源和线圈指示灯默认颜色和状态*/
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_POWER, ATTR_ON_COLOR, VAL_RED);
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_POWER, ATTR_OFF_COLOR, VAL_GREEN); 
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_COIL, ATTR_ON_COLOR, VAL_RED);
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_COIL, ATTR_OFF_COLOR, VAL_GREEN); 
	SetCtrlVal ( panelHandle,PANEL_SYS_STATE_POWER , TRUE);
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "电源故障"); 
	SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , TRUE);
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "未接线圈"); 

	
	/* 第一个页面 */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_SGL_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_SGL_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_1_CB_CC1_SGL_STIM , FALSE); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_RPT_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_RPT_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_1_CB_CC1_RPT_STIM , FALSE);  
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_SQC_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_SQC_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_1_CB_CC1_SQC_STIM , FALSE);   
	
	
	
	/* 第二个页面 */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle); 
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_SGL_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_SGL_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_SGL_8_CB_SGL8_SGL_STIM , FALSE);  
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_RPT_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_RPT_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_SGL_8_CB_SGL8_RPT_STIM , FALSE);  
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_SQC_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_SQC_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_SGL_8_CB_SGL8_SQC_STIM , FALSE); 
	
	/* 第三个页面 */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle); 
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_SGL_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_SGL_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_DBL_8_CB_DBL8_SGL_STIM , FALSE); 
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_RPT_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_RPT_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_STIM , FALSE); 
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_SQC_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_SQC_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_DBL_8_CB_DBL8_SQC_STIM , FALSE); 
	
	/* 第四个页面 */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_SGL_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_SGL_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_4_CB_CC4_SGL_STIM , FALSE); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_RPT_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_RPT_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_4_CB_CC4_RPT_STIM , FALSE); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_SQC_STIM, ATTR_ON_COLOR, VAL_DK_RED);
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_SQC_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_4_CB_CC4_SQC_STIM , FALSE);  
	
	
	/* 刺激按钮不能用 */
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);  
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
	
	/* 上次线圈选择结果 */   
	Pre_Coil[0]=0;     //P1.4
	Pre_Coil[1]=0;     //P1.5 
	Pre_Coil[2]=0;	   //P1.6 
	Pre_Coil[3]=1;     //判断位

	/* 显示状态 */
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "系统初始化完成..." );
	SendMsgToLog("系统初始化完成..."); 
	
}


/* 显示图片 */
void DisplayImage( )										   
{
	char *fileName;
	char projectDir[ MAX_PATHNAME_LEN ];
	char fullPath[ MAX_PATHNAME_LEN ];

	if (GetProjectDir (projectDir) < 0)
	
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "获取程序根目录失败！图片更新失败" );	

	else
	
	{
		/* 线圈指示 --- 单线圈 */
		fileName = "Coil\\COIL_CC_1.png";  
		MakePathname (projectDir, fileName, fullPath);
//		FmtOut(fullPath)  ;
		DisplayImageFile (panelHandle, PANEL_COIL_CC_1, fullPath); 
		
		/* 线圈指示 --- 单8字 */
		fileName = "Coil\\COIL_SGL_8.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_COIL_SGL_8, fullPath); 
		
		/* 线圈指示 --- 双8字 */
		fileName = "Coil\\COIL_DBL_8.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_COIL_DBL_8, fullPath); 
		
		/* 线圈指示 --- 四线圈 */
		fileName = "Coil\\COIL_CC_4.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_COIL_CC_4, fullPath); 
		
		/* 软件声明 --- 北大LGOO */       
		fileName = "Logo\\Logo_PKU.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_LOGO_PKU, fullPath);          	//北大logo   
		
		/* 软件声明 --- 北大LGOO */
		fileName = "Logo\\Logo_XW.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_LOGO_XW, fullPath);    	        //宣武logo   
		
		
		/* 刺激模式 --- 单次刺激 */  	
		fileName = "Pulse\\PULSE_SGL.png";  
		MakePathname (projectDir, fileName, fullPath); 
	
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_CC_1_PULSE_SGL, fullPath);    	        
				
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_SGL_8_PULSE_SGL, fullPath); 
		
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_DBL_8_PULSE_SGL, fullPath); 
		
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_CC_4_PULSE_SGL, fullPath); 
		
		/* 刺激模式 --- 重复刺激 */  	
		fileName = "Pulse\\PULSE_RPT.png";  
		MakePathname (projectDir, fileName, fullPath); 
	
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_CC_1_PULSE_RPT, fullPath);    	        
				
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_SGL_8_PULSE_RPT, fullPath); 
		
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_DBL_8_PULSE_RPT, fullPath); 
		
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_CC_4_PULSE_RPT, fullPath); 
		
		
		/* 刺激模式 --- 序列刺激 */  	
		fileName = "Pulse\\PULSE_SQC.png";  
		MakePathname (projectDir, fileName, fullPath); 
	
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_CC_1_PULSE_SQC, fullPath);    	        
				
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_SGL_8_PULSE_SQC, fullPath); 
		
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_DBL_8_PULSE_SQC, fullPath); 
		
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle); 
		DisplayImageFile (TabPanelHandle, TAB_CC_4_PULSE_SQC, fullPath); 

	}

}

void StatusDetect_Task( )                                   //数据采集时钟
{
	SendMsgToLog("启动状态监测...");
	g_StatusTimerId = NewAsyncTimer (((double)g_StatusTimerDelay) / 1000.0, -1,1, StatusAsyncTimerCallback, NULL);		   //创建异步时钟
	
	CmtScheduleThreadPoolFunction ( DEFAULT_THREAD_POOL_HANDLE, StatusDetectThreadFunction, NULL, NULL );   //数据采集线程 
	
}

/* 异步时钟处理函数 */
int CVICALLBACK StatusAsyncTimerCallback (int reserved, int theTimerId, int event,
                                 void *callbackData, int eventData1,int eventData2)
{                                                   
   
 //定时时间到
    if (event == EVENT_TIMER_TICK)
	{
		gTimeCounter++;
	
		
		if ((gTimeCounter%3) == 0)  		//每十分之一秒测量一次 
		{
			gOneTenthSecondMeasureEnable = 1;
//			putchar('a'); 
		}
		if ((gTimeCounter%10) == 0)		    //每一秒测量一次
		{
			gOneSecondMeasureEnable  = 1;
			gTimeCounter = 0;			    //每秒重置一下，防止积累过多溢出
//			putchar('b'); 
		}
	}
	
 //取消定时  
    if (event == EVENT_DISCARD) 
	{	
		g_StatusTimerId = 0;
	}
	
	return 0;
}

int CVICALLBACK StatusDetectThreadFunction (void *functionData)
{
	while (gQuitStatusAcqTread == 0) 
	{
		
		if(gOneSecondMeasureEnable == 1)          	//  秒测量优先级高
		{
 
			TmpAcq_Task(); 
			gOneSecondMeasureEnable  = 0; 
			
		}
		
		else if(gOneTenthSecondMeasureEnable == 1)      //  十分之一秒测量优先级低                                 
		{
		 	
			CoilDetect_Task( ); 
			PwrOk_Task();
			SglDisOk_Task();
			gOneTenthSecondMeasureEnable = 0;
		}
	}
  
	return 0;
}

void TmpAcq_Task( )
{
	int32       error=0;
	bool32      bComplete = TRUE;
	char        chan[256];
	float64     min,max,rate;
	float64		TempVal = 0;
	uInt32      sampsPerChan;
	int32       numRead;
	uInt32      numChannels;
	char        errBuff[2048]={'\0'};
	uInt32      i;
	

	
	min = 0;
	max = 10;
	rate = 100000; //100k
	sampsPerChan = 1000;
	numChannels = 1;
	strcpy(chan,"Dev1/ai1");
	TempVal = 0;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
//	SetWaitCursor(1);
	DAQmxErrChk (DAQmxCreateTask("",&TempAcqtaskHandle));
	DAQmxErrChk (DAQmxCreateAIVoltageChan(TempAcqtaskHandle,chan,"",DAQmx_Val_Diff ,min,max,DAQmx_Val_Volts,NULL));
	DAQmxErrChk (DAQmxCfgSampClkTiming(TempAcqtaskHandle,"",rate,DAQmx_Val_Rising,DAQmx_Val_FiniteSamps,sampsPerChan));


	if( (data = malloc(sampsPerChan*numChannels*sizeof(float64))) == NULL ) 
	{
		goto Error;
	}

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk (DAQmxStartTask(TempAcqtaskHandle));

//	SetCtrlAttribute(panel,PANEL_ACQUIRE,ATTR_DIMMED,1);
//	ProcessDrawEvents();

	/*********************************************/
	// DAQmx Read Code
	/*********************************************/
	DAQmxErrChk (DAQmxReadAnalogF64(TempAcqtaskHandle,sampsPerChan,10.0,DAQmx_Val_GroupByChannel,data,sampsPerChan*numChannels,&numRead,NULL));
//	DAQmx_Task_Complete

	if( numRead>0 )
	{
		
		/* 均值滤波 */
		for(i=0;i<sampsPerChan;i++)
		{
			TempVal += data[i];
		}
		TempVal = TempVal/sampsPerChan;
		
		TempVal = TempVal*20;
		SetCtrlVal ( panelHandle, PANEL_SYS_STATE_TEMP ,TempVal );
		/* 温度判断 */
		if( TempVal < 60 )
		{
			/* 无操作 */
			
			
		}
		else if( (TempVal >= 60) && (TempVal < 80) )
		{
			/* 警告 */
			SendMsgToLog("温度达到临界状态（60度~80度）...");
			
			
		}
		else if((TempVal >= 80))
		{
			/* 强制停止刺激 */
			SendMsgToLog("温度太高（大于80度），稍后再进行刺激..."); 
			StimProgress_Exit( );
		}
	}
	
	Delay(1000);
	
Error:

	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	if( TempAcqtaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(TempAcqtaskHandle);
		DAQmxClearTask(TempAcqtaskHandle);
		TempAcqtaskHandle = 0;

	}
	if( data != NULL )
	{
		free( data ); 
		data = NULL;
	}
		
	
	if( DAQmxFailed(error) )
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "温度检测任务出错..." );
	    SendMsgToLog("温度检测任务出错..."); 
		SendMsgToLog( errBuff );  
	}
			
}



void SglDisOk_Task( )
{
	int32       error=0;
	uInt8       data[1];
	char		errBuff[2048]={'\0'};
	int32		read,bytesPerSamp;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
//	SetWaitCursor(1);
	DAQmxErrChk (DAQmxCreateTask("",&SglDisOktaskHandle));
	DAQmxErrChk (DAQmxCreateDIChan(SglDisOktaskHandle,"Dev1/port0/line5","",DAQmx_Val_ChanForAllLines));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk (DAQmxStartTask(SglDisOktaskHandle));

	/*********************************************/
	// DAQmx Read Code
	/*********************************************/
	DAQmxErrChk (DAQmxReadDigitalLines(SglDisOktaskHandle,1,10.0,DAQmx_Val_GroupByChannel,data,1,&read,&bytesPerSamp,NULL));
	
	if( data[0]== 1 )
	{
		/* 此处添加单次刺激任务 */
		
		
	}

Error:
//	SetWaitCursor(0);
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	
	if( SglDisOktaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(SglDisOktaskHandle);
		DAQmxClearTask(SglDisOktaskHandle);
		SglDisOktaskHandle = 0;
	}
	
	if( DAQmxFailed(error) )
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "单次刺激测量任务失败！" );				 //显示状态	
		SendMsgToLog( errBuff ); 
	}
		
}


void PwrOk_Task( )
{
	
	int32       error=0;
//	TaskHandle  taskHandle=0;
	uInt8       data[1];
	char		errBuff[2048]={'\0'};
	int32		read,bytesPerSamp;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
//	SetWaitCursor(1);
	DAQmxErrChk (DAQmxCreateTask("",&PwrOktaskHandle));
	DAQmxErrChk (DAQmxCreateDIChan(PwrOktaskHandle,"Dev1/port0/line1","",DAQmx_Val_ChanForAllLines));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk (DAQmxStartTask(PwrOktaskHandle));

	/*********************************************/
	// DAQmx Read Code
	/*********************************************/
	DAQmxErrChk (DAQmxReadDigitalLines(PwrOktaskHandle,1,10.0,DAQmx_Val_GroupByChannel,data,1,&read,&bytesPerSamp,NULL));
	
	if( data[0]== 1 )
	{
		 SetCtrlVal ( panelHandle,PANEL_SYS_STATE_POWER , TRUE);
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "电源故障");    
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "系统电源故障！" );	
		 SendMsgToLog("电源出现故障...");
	}
	else
	{
		 SetCtrlVal ( panelHandle,PANEL_SYS_STATE_POWER , FALSE); 
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "电源正常"); 
		  
	}

Error:
//	SetWaitCursor(0);
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	if( PwrOktaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(PwrOktaskHandle);
		DAQmxClearTask(PwrOktaskHandle);
		PwrOktaskHandle = 0;
	}
	if( DAQmxFailed(error) )
	{	
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "电源测量任务失败..." );				 //显示状态
		SendMsgToLog("电源测量任务失败..."); 
		SendMsgToLog( errBuff );
	}
}


void CoilDetect_Task( ) 													
{
	int32       error=0;
	uInt8       data[3];
	char		errBuff[2048]={'\0'};
	int32		read,bytesPerSamp;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
//	SetWaitCursor(1);
	DAQmxErrChk (DAQmxCreateTask("",&CoilDetecttaskHandle));
	DAQmxErrChk (DAQmxCreateDIChan(CoilDetecttaskHandle,"Dev1/port1/line4:6","",DAQmx_Val_ChanForAllLines));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk (DAQmxStartTask(CoilDetecttaskHandle));

	/*********************************************/
	// DAQmx Read Code
	/*********************************************/
	DAQmxErrChk (DAQmxReadDigitalLines(CoilDetecttaskHandle,1,10.0,DAQmx_Val_GroupByChannel,data,3,&read,&bytesPerSamp,NULL));
	
	/* 测试专用  */
	data[0] = 0;  	
	data[1] = 0;
	data[2] = 1;
	
	if(Pre_Coil[3] == 1)    //第一次测试
	{
		Pre_Coil[0] = data[0]; 
		Pre_Coil[1] = data[1]; 
		Pre_Coil[2] = data[2]; 
		Pre_Coil[3] = 0;
	
		goto   Ciol;
	}
	
	else if((data[0] == Pre_Coil[0])&&(data[1] == Pre_Coil[1])&&(data[2] == Pre_Coil[2]))
	{
		goto  Error;
	}
	
Ciol: 	
	if((data[0] == 0)&&(data[1] == 1)&&(data[2] == 1))                               // 圆环线圈
	{
		/* 线圈图标 */
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , FALSE);
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "线圈正常"); 
		nSelCoilNum = COIL_CC_1;
		SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1); 
	
		
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_DK_RED); 	   //圆环
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);       //8字
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	   //双8字
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 	   //四线圈 
	
		
		
	    /* 启用刺激按钮 */
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  		
		SendMsgToLog("当前使用圆环线圈..."); 
		
	}
	else if((data[0] == 1)&&(data[1] == 0)&&(data[2] == 0))	                         // 8字线圈 
	{
		/* 线圈图标 */   
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , FALSE); 
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "线圈正常");  
		nSelCoilNum = COIL_SGL_8;
		SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8); 
	
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_DK_RED);       
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 	   
	
   		
	    /* 启用刺激按钮 */
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
		SendMsgToLog("当前使用8字线圈...");  
	}
	else if((data[0] == 0)&&(data[1] == 1)&&(data[2] == 0))	                        // 双8字线圈 
	{
		/* 线圈图标 */  
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , FALSE); 
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "线圈正常");  
		
		nSelCoilNum = COIL_DBL_8;
		SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8); 
		
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);       
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_DK_RED); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 	   
	
   		
	    /* 启用刺激按钮 */
		
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
		SendMsgToLog("当前使用双8字线圈...");    
	}
	else if((data[0] == 0)&&(data[1] == 0)&&(data[2] == 1))	                         // 四线圈 
	{
		/* 线圈图标 */ 
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , FALSE);
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "线圈正常");  
		
		nSelCoilNum = COIL_CC_4;
		SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4); 
		
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	  
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);      
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_DK_RED); 	   
	
	    /* 禁止刺激按钮 */
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
		SendMsgToLog("当前使用四线圈...");  
	}														    
 	else 	                                                                         // 没有线圈 
	{
		  
		if((data[0] == 1)&&(data[1] == 1)&&(data[2] == 1))
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "没有线圈" );				 //显示状态 
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "没有线圈");  
			SendMsgToLog("当前没插线圈...");  
			nSelCoilNum = COIL_NO;
		
		}
		else
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "线圈信号有错误" );				 //显示状态
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "线圈错误"); 
			SendMsgToLog("线圈测量出现未知状态..."); 
			nSelCoilNum = COIL_FAIL;  	                         
		}
		/* 线圈图标 */ 
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , TRUE);  
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);       
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	  
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 	 
		GetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, &nAtvPageNum);
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, nAtvPageNum, &TabPanelHandle);
		

		 /* 禁止刺激按钮 */
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
		
	}
	

Error:
//	SetWaitCursor(0);
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	if( CoilDetecttaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(CoilDetecttaskHandle);
		DAQmxClearTask(CoilDetecttaskHandle);
		CoilDetecttaskHandle = 0;
	}
	if( DAQmxFailed(error) )
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "线圈测量任务失败！" );				 //显示状态	
	    SendMsgToLog("线圈测量任务失败..."); 
		SendMsgToLog( errBuff ); 
	}	
		
}

int CVICALLBACK Cmd_Start_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
			
	if(event == EVENT_COMMIT )
	{

		CmtScheduleThreadPoolFunction ( DEFAULT_THREAD_POOL_HANDLE, Stim_ThreadFunction, NULL, NULL );   //刺激线程   

	}

	return 0;
}
void DisCharge(double time)
{
	int         error=0;    
	char        errBuff[2048]={'\0'};
	uInt8       data[1]={0};   		
      



		/*********************************************/
		// DAQmx Configure Code
		/*********************************************/
	
		DAQmxErrChk (DAQmxCreateTask("",&gDisChargetaskHandle));
		DAQmxErrChk (DAQmxCreateDOChan(gDisChargetaskHandle,"Dev1/port0/line4","",DAQmx_Val_ChanForAllLines));

		/*********************************************/
		// DAQmx Start Code
		/*********************************************/
		DAQmxErrChk (DAQmxStartTask(gDisChargetaskHandle));

		/*********************************************/
		// DAQmx Write Code
		/*********************************************/
		SetWaitCursor(1); 
		data[0] = 1;
		DAQmxErrChk (DAQmxWriteDigitalLines(gDisChargetaskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL));
	    Delay( time );
		data[0] = 0; 
		DAQmxErrChk (DAQmxWriteDigitalLines(gDisChargetaskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL));

Error:
	SetWaitCursor(0);
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	if( gDisChargetaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(gDisChargetaskHandle);
		DAQmxClearTask(gDisChargetaskHandle);
		gDisChargetaskHandle = 0;
		
	}
	if( DAQmxFailed(error) )
		MessagePopup("DAQmx Error",errBuff);	
}

int CVICALLBACK Fcs_4_Tblr (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_4_TLBR );
		DisCharge( 0.2 );
		Send_FCS_SEL_Command(FCS_4_TLBR);
	}
	
	return 0;
}

int CVICALLBACK Fcs_1_Top (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_1_TOP );
		DisCharge( 0.2 );
		Send_FCS_SEL_Command(FCS_1_TOP);
	}
	return 0;
}

int CVICALLBACK Fcs_1_Lft (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_1_LFT );
		DisCharge( 0.2 );
		Send_FCS_SEL_Command(FCS_1_LFT);
	}
	return 0;
}

int CVICALLBACK Fcs_1_Btm (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_1_BTM );
		DisCharge( 0.2 );
		Send_FCS_SEL_Command(FCS_1_BTM);
	}
	
	return 0;
}

int CVICALLBACK Fcs_1_Rt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_1_RT );
		DisCharge( 0.2 );
		Send_FCS_SEL_Command(FCS_1_RT);
	}
	
	return 0;
}

int CVICALLBACK Fcs_L_Hz (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_L_HZ );
		DisCharge( 0.2 );
		Send_FCS_SEL_Command(FCS_L_HZ);
	}
	return 0;
}

int CVICALLBACK Fcs_L_Vtc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_L_VTC );
		DisCharge( 0.2 );
		Send_FCS_SEL_Command(FCS_L_VTC);
	}
	
	return 0;
}

int CVICALLBACK Tab_Stim_Mode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	if( event == EVENT_ACTIVE_TAB_CHANGE  )
	{
		//printf("%d\n%d\n",eventData1,eventData2);
		if( nSelCoilNum == -2 )
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "线圈信号出错！" );				 //显示状态	
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, eventData2, &TabPanelHandle); 
		}
		else if( nSelCoilNum == -1 )
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "未接线圈！" );				 //显示状态	
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, eventData2, &TabPanelHandle);  
		}
		else if( eventData2 != nSelCoilNum)
		{
			SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum);
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum, &TabPanelHandle); 
		}
	
	}
	
	return 0;
}





/* 停止刺激 */   
void StimProgress_Exit( )
{

	
	bStim_Quit = 1;            //刺激停止标志位设为有效
	
	if(g_StimTimerId != 0)	  //关闭进度条 
	{
		DiscardAsyncTimer ( g_StimTimerId );
		g_StimTimerId = 0;
		SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 );  
	}
	
	
	if( gCtr0taskHandle != 0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(gCtr0taskHandle);
		DAQmxClearTask(gCtr0taskHandle);
		gCtr0taskHandle = 0;
			
	}
	
	
	if( gChrgDisChrgtaskHandle != 0 ) 
	{
		//********************************************/
		// DAQmx Stop Code
		/*********************************************/
		
		DAQmxStopTask(gChrgDisChrgtaskHandle);
		DAQmxClearTask(gChrgDisChrgtaskHandle);
		gChrgDisChrgtaskHandle = 0;
	}
	
	if( pWave != NULL )     //防止内存泄露
	{
		free(pWave);
		pWave = NULL;
		
	}
	
}

/* 停止监测 */ 
void StatusDetect_Exit( )
{
	   /* 关闭测量异步定时器 */
	if( g_StatusTimerId != 0)
	{
		DiscardAsyncTimer( g_StatusTimerId );
		g_StatusTimerId = 0;	
	}
	
	/* 关闭测量异步定时器 */ 
	gQuitStatusAcqTread == 1;
	/* 温度测量任务 停止 */
	if(TempAcqtaskHandle != 0)
	{
		DAQmxStopTask( TempAcqtaskHandle );
		DAQmxClearTask( TempAcqtaskHandle );
		TempAcqtaskHandle = 0;	
	}
	/* 申请的内存释放 */ 
	if( data != NULL )
	{
		free( data ); 
		data = NULL;
	}
	/* 电源故障 */    	
	if( PwrOktaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(PwrOktaskHandle);
		DAQmxClearTask(PwrOktaskHandle);
		PwrOktaskHandle = 0;
	}
		
	/* 单次刺激任务 */  
	if( SglDisOktaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(SglDisOktaskHandle);
		DAQmxClearTask(SglDisOktaskHandle);
		SglDisOktaskHandle = 0;
	}
	
	/* 线圈监测任务 */ 
	if( CoilDetecttaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(CoilDetecttaskHandle);
		DAQmxClearTask(CoilDetecttaskHandle);
		CoilDetecttaskHandle = 0;
	}
}



int CVICALLBACK Cmd_Exit_Sw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	
	switch (event)
	{
		case EVENT_COMMIT:
			
			StatusDetect_Exit( );
			StimProgress_Exit( ); 
			QuitUserInterface (0);   
			
			break;
	}
	return 0;
}

int CVICALLBACK Cmd_Reboot_Sys (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	switch (event)
	{
		case EVENT_COMMIT:
			for(i=0;i<100;i++)
			{
				FmtOut("%d  %f  %f \n",pStimPara[i].power,pStimPara[i].volt,pStimPara[i].frequency );
			
			}
			break;
	}
	return 0;
}


int CVICALLBACK Cb_Cc1_Sgl_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_CC_1 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_SGL_8 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_SGL_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_SGL_STIM, TRUE ); 
				nSelStimNum = CC1_SGL_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
			
		//	printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);

			break;
	}
	return 0;
}

int CVICALLBACK Cb_Cc1_Rpt_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_CC_1 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_SGL_8 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle );
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_RPT_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_RPT_STIM, TRUE ); 
				nSelStimNum = CC1_RPT_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	//		printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum); 
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Cc1_Sqc_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_CC_1 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_SGL_8 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_SQC_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_SQC_STIM, TRUE ); 
				nSelStimNum = CC1_SQC_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	   //  	printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum); 	
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Sgl8_Sgl_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_SGL_8 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_SGL_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_SGL_STIM, TRUE ); 
				nSelStimNum = SGL8_SGL_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
		//	printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Sgl8_Rpt_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_SGL_8 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_RPT_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_RPT_STIM, TRUE ); 
				nSelStimNum = SGL8_RPT_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
		//	printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Sgl8_Sqc_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_SGL_8 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_SQC_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_SQC_STIM, TRUE ); 
				nSelStimNum = SGL8_SQC_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	//		printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Dbl8_Sgl_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_DBL_8 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SGL_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SGL_STIM, TRUE ); 
				nSelStimNum = DBL8_SGL_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	//		printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Dbl8_Rpt_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_DBL_8 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_STIM, TRUE ); 
				nSelStimNum = DBL8_RPT_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	//		printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Dbl8_Sqc_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_DBL_8 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SQC_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SQC_STIM, TRUE ); 
				nSelStimNum = DBL8_SQC_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	//		printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Cc4_Sqc_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_CC_4 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_DBL_8  ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_SQC_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_SQC_STIM, TRUE ); 
				nSelStimNum = CC4_SQC_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	//		printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Cc4_Rpt_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_CC_4 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_DBL_8  ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_RPT_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_RPT_STIM, TRUE ); 
				nSelStimNum = CC4_RPT_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	//		printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Cc4_Sgl_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bState;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if( nSelCoilNum != COIL_CC_4 )
			{
				
				ClearAllStimMode( ); //清空所有选择
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_DBL_8  ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("线圈错误", "线圈监测出错，刺激模式选择无效！");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("线圈错误", "没有线圈，刺激模式选择无效！");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_SGL_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //清空所有选择
				SetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_SGL_STIM, TRUE ); 
				nSelStimNum = CC4_SGL_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //清空所有选择 
			}
	//		printf("线圈：%d 刺激模式：%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}
void SendMsgToLog( char str[] )
{
	//获取当前日期
	int year,month,day,hour,mimute,second;
	char sysdate[100];
	char filename[100];
	char projectDir[ MAX_PATHNAME_LEN ];
	char fullPath[ MAX_PATHNAME_LEN ]; 
	FILE  *fp = NULL; 
	
	if (GetProjectDir (projectDir) < 0)
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "获取程序根目录失败！日志更新失败" );
		return ;
	}
	
	GetSystemDate (&month,&day ,&year );
	sprintf(sysdate,"%4d%02d%02d",year,month,day);
    strcpy(filename, "Log\\TMS_LOG_");
	strcat(filename,sysdate);
	strcat(filename,".txt");
	MakePathname (projectDir, filename, fullPath); 

	if((fp = fopen(fullPath, "a+")) == NULL )
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "日志文件打开失败！" );
		return ;
	}
	
	GetSystemTime ( &hour, &mimute ,&second );
	sprintf(sysdate,"%4d-%02d-%02d %02d:%02d:%02d  ",year,month,day,hour,mimute,second );
	fwrite(sysdate,1,strlen(sysdate),fp); 
	fwrite(str,1,strlen(str),fp); 
	fwrite("\r\n",1,strlen("\r\n"),fp);
	fflush( fp );
	fclose( fp );
	
}


int CVICALLBACK Cmd_Stop_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			StimProgress_Exit( );  
			break;
	}
	return 0;
}

void ClearAllStimMode( )
{
	/* 第一个页面 */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle_Temp); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_1_CB_CC1_SGL_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_1_CB_CC1_RPT_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_1_CB_CC1_SQC_STIM, FALSE );
	/* 第二个页面 */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle_Temp); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_SGL_8_CB_SGL8_SGL_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_SGL_8_CB_SGL8_RPT_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_SGL_8_CB_SGL8_SQC_STIM, FALSE );
	/* 第三个页面 */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle_Temp); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
	/* 第四个页面 */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE );
	
	nSelStimNum = NO_SEL_STIM ;
		
}


int CVICALLBACK Stim_ThreadFunction (void *functionData)
{
	int       intensity_A = 0;
	int       intensity_B = 0;
	double    frequency_A = 0;
	double    frequency_B = 0;
	double    train_time_A = 0;
	double    train_time_B = 0;
	int       train_num_A = 0;
	int       train_num_B = 0; 
	double    train_interval_A = 0;
	double    train_interval_B = 0;
	float64   voltgiven_A = 0.8;
	float64   voltgiven_B = 0.8;
	int       i = 0;
	int       j = 0;
	int       stim_cycle_A = 0; 
	int       stim_cycle_B = 0;
	int       numberOfRows = 0;
	double    Stim_Time_A = 0;
	double    Stim_Time_B = 0; 
	char      coil[2]		 ;
	int       bAState     = 0;
	int       bBState     = 0;
	int       APlseNum     = 0;
	int       BPlseNum     = 0;
	int       nPluse       =0;
	
	/* 数据合法性验证 */
	
	if( nSelCoilNum == COIL_FAIL )
	{
//		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "线圈出现故障，不能进行刺激..." );				 //显示状态	
		SendMsgToLog("线圈出现故障，不能进行刺激...");                                               //记录日志状态
		return -1;
	}
			
	if( nSelCoilNum == COIL_NO )
	{
//		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "没有线圈，不能进行刺激..." );				 //显示状态	
		SendMsgToLog("没有线圈，不能进行刺激...");                                               //记录日志状态
		return -1;
		
	}
			
	if( nSelStimNum == NO_SEL_STIM )
	{
//		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "没有选择刺激类型，不能进行刺激..." );				 //显示状态	
		SendMsgToLog("没有选择刺激类型，不能进行刺激...");                                               //记录日志状态
		return -1;
	}
	
	if( pWave != NULL )     //防止内存泄露
	{
		free(pWave);
		pWave = NULL;
	}
	
	
	
	if( nSelCoilNum == COIL_CC_1 )
	{
		 if( nSelStimNum == CC1_SGL_STIM )		  //圆环线圈  单次刺激
		 {
		 	
			/* 刺激参数计算 */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_SGL_INT, &intensity_A );
		
			/* 发送电压 */
			stim_cycle_A = 1000;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* 波形产生 */
		
			// port0:line2----A路充电
			// port0:line0----A路放电 
			// port0:line6----B路充电 
			// port0:line3----B路放电
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("系统错误", "申请内存错误！");
				return -1;    
			}
			for( i=0;i<stim_cycle_A;i++ )
			{
				pWave[stim_cycle_A*0+i] = 1;
				pWave[stim_cycle_A*1+i] = 0;
				pWave[stim_cycle_A*2+i] = 0;
				pWave[stim_cycle_A*3+i] = 0;
			}
			/* 充电信号最后5个为低 */
			pWave[stim_cycle_A*1-5] = 0;
			pWave[stim_cycle_A*1-4] = 0;
			pWave[stim_cycle_A*1-3] = 0;
			pWave[stim_cycle_A*1-2] = 0;
			pWave[stim_cycle_A*1-1] = 0;
			/* 放电信号倒数第二和第三为高 */
			pWave[stim_cycle_A*2-3] = 1;
			pWave[stim_cycle_A*2-2] = 1;
			/* 开始刺激 */
	//		FmtOut("刺激命令之前\n");
			Send_CHRG_DisCHRG_Command( stim_cycle_A,1,1 );
	//		FmtOut("刺激命令之后\n"); 
			
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
			
		 }
		else if( nSelStimNum == CC1_RPT_STIM )		 //圆环线圈  重复刺激  
		{
			
			
			/* 刺激参数读取 */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_INT, &intensity_A );
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_FQC, &frequency_A ); 
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TT, &train_time_A ); 
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TN, &train_num_A ); 
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TITV, &train_interval_A ); 
			/* 合法性验证 */
			
			//强度和频率要匹配
			if((int)(frequency_A*train_time_A)<1)  //每个串至少刺激一次
			{
				MessagePopup ("参数错误", "刺激频率和串时间不匹配！");
				return -1;
			}
			
			if(frequency_A >= pStimPara[intensity_A-1].frequency )   //刺激强度和刺激频率要匹配
			{
				MessagePopup ("参数错误", "刺激强度和刺激频率不匹配！");
				return -1;	
			}
			
			
			if((frequency_A*train_time_A*train_num_A) > 6000 )   //总脉冲个数不能超过6000 
			{
				MessagePopup ("参数错误", "总脉冲个数超过6000！");
				return -1;	
			}

			/* 发送电压 */
		//	;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* 波形产生 */
		
			// port0:line2----A路充电
			// port0:line0----A路放电 
			// port0:line6----B路充电 
			// port0:line3----B路放电
			stim_cycle_A = (int)(1000.0/frequency_A);
			
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("系统错误", "申请内存错误！");
				return -1;    
			}
			
			for( i=0;i<stim_cycle_A;i++ )
			{
				pWave[stim_cycle_A*0+i] = 1;
				pWave[stim_cycle_A*1+i] = 0;
				pWave[stim_cycle_A*2+i] = 0;
				pWave[stim_cycle_A*3+i] = 0;
			}
			/* 充电信号最后5个为低 */
			pWave[stim_cycle_A*1-5] = 0;
			pWave[stim_cycle_A*1-4] = 0;
			pWave[stim_cycle_A*1-3] = 0;
			pWave[stim_cycle_A*1-2] = 0;
			pWave[stim_cycle_A*1-1] = 0;
			/* 放电信号倒数第二和第三为高 */
			pWave[stim_cycle_A*2-3] = 1;
			pWave[stim_cycle_A*2-2] = 1;
		
			/* 启动进度条 */
			ShowStimSlide( train_time_A*train_num_A+train_interval_A*(train_num_A-1) );
			/* 开始刺激 */
			if( (train_num_A == 1))
			{
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A ); 
			}
			else
			{
      
				for(i=1;i<train_num_A;i++)
				{
					Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
					Delay( train_time_A + train_interval_A );
					if( bStim_Quit == 1 )
					{
						bStim_Quit = 0; 
						return -1;
					}
				}
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A );
      
			}
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
		 }
		 else if( nSelStimNum == CC1_SQC_STIM )		 //圆环线圈  序列刺激  
		 {
			
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, &numberOfRows);
		
			if(numberOfRows <1)
			{
			    bStim_Quit = 0; 
				return -1; 
			}
			//验证数据有效性
			nPluse = 0;
			for(i=1;i<=numberOfRows;i++ )
			{
				/* 读取参数 */
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (1, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (2, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (4, i) ,&train_interval_A );
				
				//强度和频率要匹配
				if((int)(frequency_A*train_time_A)<1)  //每个串至少刺激一次
				{
					MessagePopup ("参数错误", "刺激频率和串时间不匹配！");
					return -1;
				}
			
				if(frequency_A >= pStimPara[intensity_A-1].frequency )   //刺激强度和刺激频率要匹配
				{
					MessagePopup ("参数错误", "刺激强度和刺激频率不匹配！");
					return -1;	
				}
				nPluse += (int)( frequency_A*train_time_A );
			
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0; 
					return -1;
				}
			}
			
			if( nPluse > 6000 )   //总脉冲个数不能超过6000 
			{
				MessagePopup ("参数错误", "总脉冲个数超过6000！");
				return -1;	
			}
			
			for(i=1;i<=numberOfRows-1;i++ )
			{
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, i) ,&train_time_A );
				Stim_Time_A += train_time_A;
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (4, i) ,&train_interval_A );
				Stim_Time_A += train_interval_A;
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0; 
					return -1;
				}
			}
			GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, numberOfRows) ,&train_time_A );
			Stim_Time_A += train_time_A;
			/* 启动进度条 */
			ShowStimSlide( Stim_Time_A );
			
			
			/*刺激开始*/
			
			for(i=1;i<=numberOfRows-1;i++ )
			{
				/* 读取参数 */
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (1, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (2, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (4, i) ,&train_interval_A );
				
				/* 发送电压 */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = pStimPara[intensity_A-1].volt;		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
					
				/* 波形产生 */
		
				// port0:line2----A路充电
				// port0:line0----A路放电 
				// port0:line6----B路充电 
				// port0:line3----B路放电
				if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
				{
					MessagePopup ("系统错误", "申请内存错误！");
					return -1;    
				}
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* 充电信号最后5个为低 */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* 放电信号倒数第二和第三为高 */
				pWave[stim_cycle_A*2-3] = 1;
				pWave[stim_cycle_A*2-2] = 1;
				
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A + train_interval_A );
				
				if(pWave != NULL)
				{
					free(pWave);
					pWave = NULL;
				}
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0 ;
					return -1;
				}
			}
				
			
				//最后一次刺激
			
				/* 读取参数 */
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (1, numberOfRows) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (2, numberOfRows) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, numberOfRows) ,&train_time_A );
			//	GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_RPT_SQC,MakePoint (4, numberOfRows) ,&train_interval_A );
				
				/* 发送电压 */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = pStimPara[intensity_A-1].volt;		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
					
				/* 波形产生 */
		
				// port0:line2----A路充电
				// port0:line0----A路放电 
				// port0:line6----B路充电 
				// port0:line3----B路放电
				if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
				{
					MessagePopup ("系统错误", "申请内存错误！");
					return -1;    
				}
				
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* 充电信号最后5个为低 */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* 放电信号倒数第二和第三为高 */
				pWave[stim_cycle_A*2-3] = 1;
				pWave[stim_cycle_A*2-2] = 1;
				
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0;
					return -1;
				}
				
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A );
				
				if(pWave != NULL)
				{
					free(pWave);
					pWave = NULL;
				}
				
			 
		 }
		 else                                  //圆环线圈  刺激方式错误
		 {
			
//			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "刺激模式与当前线圈不搭配，请返回当前线圈所对应的刺激模式选项卡，选择正确的刺激模式..." );				 //显示状态	
			SendMsgToLog("刺激模式与当前线圈不搭配，请返回当前线圈所对应的刺激模式选项卡，选择正确的刺激模式...");                                               //记录日志状态
			return -1; 
		
		 }
				
				
	}
	else if( nSelCoilNum == COIL_SGL_8 )
	{
		if( nSelStimNum == SGL8_SGL_STIM )	  //8字线圈  单次刺激 
		 {
			 
			/* 刺激参数计算 */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_SGL_INT, &intensity_A );
		
			/* 发送电压 */
			stim_cycle_A = 1000;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* 波形产生 */
		
			// port0:line2----A路充电
			// port0:line0----A路放电 
			// port0:line6----B路充电 
			// port0:line3----B路放电
			
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("系统错误", "申请内存错误！");
				return -1;    
			}
		
			for( i=0;i<stim_cycle_A;i++ )
			{
				pWave[stim_cycle_A*0+i] = 1;
				pWave[stim_cycle_A*1+i] = 0;
				pWave[stim_cycle_A*2+i] = 0;
				pWave[stim_cycle_A*3+i] = 0;
			}
			/* 充电信号最后5个为低 */
			pWave[stim_cycle_A*1-5] = 0;
			pWave[stim_cycle_A*1-4] = 0;
			pWave[stim_cycle_A*1-3] = 0;
			pWave[stim_cycle_A*1-2] = 0;
			pWave[stim_cycle_A*1-1] = 0;
			/* 放电信号倒数第二和第三为高 */
			pWave[stim_cycle_A*2-3] = 1;
			pWave[stim_cycle_A*2-2] = 1;
			/* 开始刺激 */
	//		FmtOut("刺激命令之前\n");
			Send_CHRG_DisCHRG_Command( stim_cycle_A,1,1 );
	//		FmtOut("刺激命令之后\n"); 
			
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
		
					 
					 
					 
		 }
		 else if( nSelStimNum == SGL8_RPT_STIM )   //8字线圈  重复刺激 
		 {
				    
			/* 刺激参数读取 */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_INT, &intensity_A );
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_FQC, &frequency_A ); 
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TT, &train_time_A ); 
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TN, &train_num_A ); 
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TITV, &train_interval_A ); 
				//强度和频率要匹配
			if((int)(frequency_A*train_time_A)<1)  //每个串至少刺激一次
			{
				MessagePopup ("参数错误", "刺激频率和串时间不匹配！");
				return -1;
			}
			
			if(frequency_A >= pStimPara[intensity_A-1].frequency )   //刺激强度和刺激频率要匹配
			{
				MessagePopup ("参数错误", "刺激强度和刺激频率不匹配！");
				return -1;	
			}
			
			
			if((frequency_A*train_time_A*train_num_A) > 6000 )   //总脉冲个数不能超过6000 
			{
				MessagePopup ("参数错误", "总脉冲个数超过6000！");
				return -1;	
			}

			/* 发送电压 */
		//	;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* 波形产生 */
		
			// port0:line2----A路充电
			// port0:line0----A路放电 
			// port0:line6----B路充电 
			// port0:line3----B路放电
			stim_cycle_A = (int)(1000.0/frequency_A);
			
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("系统错误", "申请内存错误！");
				return -1;    
			}
			
			for( i=0;i<stim_cycle_A;i++ )
			{
				pWave[stim_cycle_A*0+i] = 1;
				pWave[stim_cycle_A*1+i] = 0;
				pWave[stim_cycle_A*2+i] = 0;
				pWave[stim_cycle_A*3+i] = 0;
			}
			/* 充电信号最后5个为低 */
			pWave[stim_cycle_A*1-5] = 0;
			pWave[stim_cycle_A*1-4] = 0;
			pWave[stim_cycle_A*1-3] = 0;
			pWave[stim_cycle_A*1-2] = 0;
			pWave[stim_cycle_A*1-1] = 0;
			/* 放电信号倒数第二和第三为高 */
			pWave[stim_cycle_A*2-3] = 1;
			pWave[stim_cycle_A*2-2] = 1;
		
			/* 启动进度条 */
			ShowStimSlide( train_time_A*train_num_A+train_interval_A*(train_num_A-1) );
			/* 开始刺激 */
			if( (train_num_A == 1))
			{
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A ); 
			}
			else
			{
      
				for(i=1;i<train_num_A;i++)
				{
					Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
					Delay( train_time_A + train_interval_A );
					if( bStim_Quit == 1 )
					{
						bStim_Quit = 0; 
						return -1;
					}
				}
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A );
      
			}
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
			
		 }
		 else if( nSelStimNum == SGL8_SQC_STIM )  //8字线圈  序列刺激
		 {
				     
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, &numberOfRows);
		
			if(numberOfRows <1)
			{
			   return -1; 
			}
			//验证数据有效性
			 for(i=1;(i<=numberOfRows-1)&&(bStim_Quit !=1);i++ )
			{
				/* 读取参数 */
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (1, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (2, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (4, i) ,&train_interval_A );
				
				//强度和频率要匹配
				if((int)(frequency_A*train_time_A)<1)  //每个串至少刺激一次
				{
					MessagePopup ("参数错误", "刺激频率和串时间不匹配！");
					return -1;
				}
			
				if(frequency_A >= pStimPara[intensity_A-1].frequency )   //刺激强度和刺激频率要匹配
				{
					MessagePopup ("参数错误", "刺激强度和刺激频率不匹配！");
					return -1;	
				}
				nPluse += (int)( frequency_A*train_time_A );
			
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0; 
					return -1;
				}
				
			}
			
			if( nPluse > 6000 )   //总脉冲个数不能超过6000 
			{
				MessagePopup ("参数错误", "总脉冲个数超过6000！");
				return -1;	
			}
			
			
			for(i=1;i<=numberOfRows-1;i++ )
			{
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, i) ,&train_time_A );
				Stim_Time_A += train_time_A;
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (4, i) ,&train_interval_A );
				Stim_Time_A += train_interval_A;
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0; 
					return -1;
				}
			}
			GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, numberOfRows) ,&train_time_A );
			Stim_Time_A += train_time_A;
			/* 启动进度条 */
			
			ShowStimSlide( Stim_Time_A );
			 
			
			
			
			
			/*刺激开始*/
			
			for(i=1;(i<=numberOfRows-1)&&(bStim_Quit !=1);i++ )
			{
				/* 读取参数 */
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (1, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (2, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (4, i) ,&train_interval_A );
				
				/* 发送电压 */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = pStimPara[intensity_A-1].volt;		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
					
				/* 波形产生 */
		
				// port0:line2----A路充电
				// port0:line0----A路放电 
				// port0:line6----B路充电 
				// port0:line3----B路放电
				if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
				{
					MessagePopup ("系统错误", "申请内存错误！");
					return -1;    
				}
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* 充电信号最后5个为低 */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* 放电信号倒数第二和第三为高 */
				pWave[stim_cycle_A*2-3] = 1;
				pWave[stim_cycle_A*2-2] = 1;
				
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A + train_interval_A );
				
				if(pWave != NULL)
				{
					free(pWave);
					pWave = NULL;
				}
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0; 
					return -1;
				}
			}
				
			
				//最后一次刺激
			
				/* 读取参数 */
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (1, numberOfRows) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (2, numberOfRows) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, numberOfRows) ,&train_time_A );
			//	GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_RPT_SQC,MakePoint (4, numberOfRows) ,&train_interval_A );
			
				//发送电压
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = pStimPara[intensity_A-1].volt;		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
					
				/* 波形产生 */
		
				// port0:line2----A路充电
				// port0:line0----A路放电 
				// port0:line6----B路充电 
				// port0:line3----B路放电
			
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
				{
					MessagePopup ("系统错误", "申请内存错误！");
					return -1;    
				}
				
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* 充电信号最后5个为低 */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* 放电信号倒数第二和第三为高 */
				pWave[stim_cycle_A*2-3] = 1;
				pWave[stim_cycle_A*2-2] = 1;
				
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0;
					return -1;
				}
				
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A );
				
				if(pWave != NULL)
				{
					free(pWave);
					pWave = NULL;
				}
		 }
		 else   //8字线圈  刺激方式错误
		 {
				    
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "刺激模式与当前线圈不搭配，请返回当前线圈所对应的刺激模式选项卡，选择正确的刺激模式..." );				 //显示状态	
			SendMsgToLog("刺激模式与当前线圈不搭配，请返回当前线圈所对应的刺激模式选项卡，选择正确的刺激模式...");                                               //记录日志状态
			return -1; 
				
		 }	
				
	}
	else if( nSelCoilNum == COIL_DBL_8 )
	{
				
		if( nSelStimNum == DBL8_SGL_STIM ) //双8字线圈  单次刺激
		 {
				 	
					 
					 
		 }
		 else if( nSelStimNum == DBL8_RPT_STIM )  //双8字线圈  重复刺激
		 {
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle );
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_A,&bAState );
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_B,&bBState ); 
			if((bAState == 0)&&(bBState == 0))		  //AB 都没有选中
			{
				return -1;	
			}
			else if((bAState == 1)&&(bBState == 0))   //选中了A
			{
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_INT, &intensity_A );
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_FQC, &frequency_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TT, &train_time_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TN, &train_num_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TITV, &train_interval_A ); 
				/* 合法性验证 */
				//列表1-100
				//串时间
				//脉冲个数
				//温度限制
			
			
			
			
			
				/* 发送电压 */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = (8.0)*((float64)intensity_A/100.0);		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
		
				/* 波形产生 */
		
				// port0:line2----A路充电
				// port0:line0----A路放电 
				// port0:line6----B路充电 
				// port0:line3----B路放电
			
				for( i=0;i<stim_cycle_A;i++ )
				{
					wave[stim_cycle_A*0+i] = 1;
					wave[stim_cycle_A*1+i] = 0;
					wave[stim_cycle_A*2+i] = 0;
					wave[stim_cycle_A*3+i] = 0;
				}
				/* 充电信号最后5个为低 */
				wave[stim_cycle_A*1-5] = 0;
				wave[stim_cycle_A*1-4] = 0;
				wave[stim_cycle_A*1-3] = 0;
				wave[stim_cycle_A*1-2] = 0;
				wave[stim_cycle_A*1-1] = 0;
				/* 放电信号倒数第二和第三为高 */
				wave[stim_cycle_A*2-3] = 1;
				wave[stim_cycle_A*2-2] = 1;
		
				/* 启动进度条 */
				ShowStimSlide( train_time_A*train_num_A+train_interval_A*(train_num_A-1) );
				/* 开始刺激 */
				if( train_num_A == 1)
				{
					Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
					Delay( train_time_A ); 
				}
				else
				{
					for(i=1;i<train_num_A;i++)
					{
						Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
						Delay( train_time_A + train_interval_A ); 
					}
					Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
					Delay( train_time_A );
      
				}		
			}
			else if((bAState == 0)&&(bBState == 1))   //选中了B
			{
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_INT, &intensity_A );
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_FQC, &frequency_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TT, &train_time_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TN, &train_num_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TITV, &train_interval_A ); 
				/* 合法性验证 */
				//列表1-100
				//串时间
				//脉冲个数
				//温度限制
			
			
			
			
			
				/* 发送电压 */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = 0.8;		 
				volt[1] = (8.0)*((float64)intensity_A/100.0);
				Send_Stim_Volt_Command( volt );
		
				/* 波形产生 */
		
				// port0:line2----A路充电
				// port0:line0----A路放电 
				// port0:line6----B路充电 
				// port0:line3----B路放电
			
				for( i=0;i<stim_cycle_A;i++ )
				{
					wave[stim_cycle_A*0+i] = 0;
					wave[stim_cycle_A*1+i] = 0;
					wave[stim_cycle_A*2+i] = 1;
					wave[stim_cycle_A*3+i] = 0;
				}
				/* 充电信号最后5个为低 */
				wave[stim_cycle_A*3-5] = 0;
				wave[stim_cycle_A*3-4] = 0;
				wave[stim_cycle_A*3-3] = 0;
				wave[stim_cycle_A*3-2] = 0;
				wave[stim_cycle_A*3-1] = 0;
				/* 放电信号倒数第二和第三为高 */
				wave[stim_cycle_A*4-3] = 1;
				wave[stim_cycle_A*4-2] = 1;
		
				/* 启动进度条 */
				ShowStimSlide( train_time_A*train_num_A+train_interval_A*(train_num_A-1) );
				/* 开始刺激 */
				if( train_num_A == 1)
				{
					Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
					Delay( train_time_A ); 
				}
				else
				{
					for(i=1;i<train_num_A;i++)
					{
						Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
						Delay( train_time_A + train_interval_A ); 
					}
					Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
					Delay( train_time_A );
      
				}
				
			}
			else									   //同时选中AB
			{
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_INT, &intensity_A );
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_FQC, &frequency_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TT, &train_time_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TN, &train_num_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TITV, &train_interval_A ); 
				
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_INT, &intensity_B );
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_FQC, &frequency_B ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TT, &train_time_B ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TN, &train_num_B ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TITV, &train_interval_B );
				/* 合法性验证 */
				//列表1-100
				//串时间
				//脉冲个数
				//温度限制
			
			
			
			
			
				/* 发送电压 */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);
				stim_cycle_B = (int)(1000.0/(float64)frequency_B);
				
				volt[0] = (8.0)*((float64)intensity_A/100.0); 		 
				volt[1] = (8.0)*((float64)intensity_B/100.0);
				
				Send_Stim_Volt_Command( volt );
				
				/* 波形产生 */
		
				// port0:line2----A路充电
				// port0:line0----A路放电 
				// port0:line6----B路充电 
				// port0:line3----B路放电
				
				Stim_Time_A = (train_time_A + train_interval_A)*(train_num_A-1)+train_time_A;	 // A 总的刺激时间
				Stim_Time_B = (train_time_B + train_interval_B)*(train_num_B-1)+train_time_B;    // B 总的刺激时间 
			
				APlseNum = (int)(Stim_Time_A*1000);
				BPlseNum = (int)(Stim_Time_B*1000);
				
				/*	 
				Stim_Time_A = 12.999;
				APlseNum = (int)Stim_Time_A;
				FmtOut( "浮点数：%f；整数：%d\n",Stim_Time_A,APlseNum );
				*/
				
				/*
				
				if( Stim_Time_A >= Stim_Time_B )    // A 的时间长
				{
					if( ( p = (uInt8 *)malloc((int)(Stim_Time_A*1000)) ) == NULL ) 
					{
						return -1;		
					}
					
					for( int i=0;i<train_num_A-1;i++ )
					{
						for(j=0;j<stim_cycle_A;j++ )
						{
							
						}
						
					}
					

				
				}
				else	                //B的时间长
				{
					
					
				}
				*/
			
			
			}			 
		 }
			
		 else if( nSelStimNum == DBL8_SQC_STIM )  //双8字线圈  序列刺激
		 {
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, &numberOfRows);
		
			if(numberOfRows <1)
			{
			   return -1; 
			}
			
			for(i=1;i<=numberOfRows-1;i++ )
			{
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, i) ,&train_time_A );
				Stim_Time_A += train_time_A;
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (5, i) ,&train_interval_A );
				Stim_Time_A += train_interval_A;
			
			}
			GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, numberOfRows) ,&train_time_A );
			
			Stim_Time_A += train_time_A;
			/* 启动进度条 */
			
			ShowStimSlide( Stim_Time_A );
			
			
			/*刺激开始*/
			
			for(i=1;(i<=numberOfRows-1)&&(bStim_Quit !=1);i++ )
			{
				/* 读取参数 */
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (1, i) ,coil ); 
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (2, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (3, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (5, i) ,&train_interval_A );
				
				/* 发送电压 */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);
				
				if(coil[0] == 'A')	               //如果是A路
				{
					volt[0] = (8.0)*((float64)intensity_A/100.0);		 
					volt[1] = 0.8;
					/* 波形产生 */
		
				// port0:line2----A路充电
				// port0:line0----A路放电 
				// port0:line6----B路充电 
				// port0:line3----B路放电
			
					for( i=0;i<stim_cycle_A;i++ )
					{
						wave[stim_cycle_A*0+i] = 1;
						wave[stim_cycle_A*1+i] = 0;
						wave[stim_cycle_A*2+i] = 0;
						wave[stim_cycle_A*3+i] = 0;
					}
					/* A充电信号最后5个为低 */
					wave[stim_cycle_A*1-5] = 0;
					wave[stim_cycle_A*1-4] = 0;
					wave[stim_cycle_A*1-3] = 0;
					wave[stim_cycle_A*1-2] = 0;
					wave[stim_cycle_A*1-1] = 0;
					/* A放电信号倒数第二和第三为高 */
					wave[stim_cycle_A*2-3] = 1;
					wave[stim_cycle_A*2-2] = 1;
					
				}
				else	                                          //如果是B路 
				{
					volt[0] = 0.8; 
					volt[1] = (8.0)*((float64)intensity_A/100.0);		 
					
					/* 波形产生 */
		
					// port0:line2----A路充电
					// port0:line0----A路放电 
					// port0:line6----B路充电 
					// port0:line3----B路放电
			
					for( i=0;i<stim_cycle_A;i++ )
					{
						wave[stim_cycle_A*0+i] = 0;
						wave[stim_cycle_A*1+i] = 0;
						wave[stim_cycle_A*2+i] = 1;
						wave[stim_cycle_A*3+i] = 0;
					}
					/* B充电信号最后5个为低 */
					wave[stim_cycle_A*3-5] = 0;
					wave[stim_cycle_A*3-4] = 0;
					wave[stim_cycle_A*3-3] = 0;
					wave[stim_cycle_A*3-2] = 0;
					wave[stim_cycle_A*3-1] = 0;
					/* B放电信号倒数第二和第三为高 */
					wave[stim_cycle_A*4-3] = 1;
					wave[stim_cycle_A*4-2] = 1;
					
				}
				
				Send_Stim_Volt_Command( volt );
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A + train_interval_A );
			}
				
			
				//最后一次刺激
			
				/* 读取参数 */
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (1, numberOfRows) ,coil ); 	
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (2, numberOfRows) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (3, numberOfRows) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, numberOfRows) ,&train_time_A );
				
				/* 发送电压 */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);
			
				if(coil[0] == 'A')               //A组线圈            
				{
					volt[0] = (8.0)*((float64)intensity_A/100.0);		 
					volt[1] = 0.8;
					
					for( i=0;i<stim_cycle_A;i++ )
					{
						wave[stim_cycle_A*0+i] = 1;
						wave[stim_cycle_A*1+i] = 0;
						wave[stim_cycle_A*2+i] = 0;
						wave[stim_cycle_A*3+i] = 0;
					}
					/* A充电信号最后5个为低 */
					wave[stim_cycle_A*1-5] = 0;
					wave[stim_cycle_A*1-4] = 0;
					wave[stim_cycle_A*1-3] = 0;
					wave[stim_cycle_A*1-2] = 0;
					wave[stim_cycle_A*1-1] = 0;
					/* A放电信号倒数第二和第三为高 */
					wave[stim_cycle_A*2-3] = 1;
					wave[stim_cycle_A*2-2] = 1;	
					
				}
				else							//B组线圈
				{
					volt[0] = 0.8;  
					volt[1] = (8.0)*((float64)intensity_A/100.0);
					/* 波形产生 */
		
					// port0:line2----A路充电
					// port0:line0----A路放电 
					// port0:line6----B路充电 
					// port0:line3----B路放电
			
					for( i=0;i<stim_cycle_A;i++ )
					{
						wave[stim_cycle_A*0+i] = 0;
						wave[stim_cycle_A*1+i] = 0;
						wave[stim_cycle_A*2+i] = 1;
						wave[stim_cycle_A*3+i] = 0;
					}
					/* B充电信号最后5个为低 */
					wave[stim_cycle_A*3-5] = 0;
					wave[stim_cycle_A*3-4] = 0;
					wave[stim_cycle_A*3-3] = 0;
					wave[stim_cycle_A*3-2] = 0;
					wave[stim_cycle_A*3-1] = 0;
					/* B放电信号倒数第二和第三为高 */
					wave[stim_cycle_A*4-3] = 1;
					wave[stim_cycle_A*4-2] = 1;
					
				}
				
				Send_Stim_Volt_Command( volt );
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A );	     
					 
					 
		 }
		 else  //双8线圈  刺激方式错误
		 {
  

			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "刺激模式与当前线圈不搭配，请返回当前线圈所对应的刺激模式选项卡，选择正确的刺激模式..." );				 //显示状态	
			SendMsgToLog("刺激模式与当前线圈不搭配，请返回当前线圈所对应的刺激模式选项卡，选择正确的刺激模式...");                                               //记录日志状态
			return -1; 
				
		 }
				
	}
	else if( nSelCoilNum == COIL_CC_4 )
	{
		if((nSelFcsNum > 7 )||(nSelFcsNum < 1 ))
		{
			 MessagePopup ("焦点选择", "请正确选择焦点！");
			 return -1;
		}
		
		if( nSelStimNum == CC4_SGL_STIM )        //四线圈  单次刺激
		 {
			/* 刺激参数计算 */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_4_CC4_SGL_INT, &intensity_A );
		
			/* 发送电压 */
			stim_cycle_A = 1000;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* 波形产生 */
		
			// port0:line2----A路充电
			// port0:line0----A路放电 
			// port0:line6----B路充电 
			// port0:line3----B路放电
			
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("系统错误", "申请内存失败！");
				return -1;    
			}
		
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* 充电信号最后5个为低 */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* 放电信号倒数第二和第三为高 */
				pWave[stim_cycle_A*2-3] = 1;
				pWave[stim_cycle_A*2-2] = 1;
			
			
			/* 开始刺激 */

			Send_CHRG_DisCHRG_Command( stim_cycle_A,1,1 );

			
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
		
					 
					 	 	
					 
					 
		 }
		 else if( nSelStimNum == CC4_RPT_STIM )  //四线圈  重复刺激
		 {
				     
					 
					 
		 }
		 else if( nSelStimNum == CC4_SQC_STIM )  //四线圈  序列刺激 
		 {
				    
		  	
					 
		 }
		 else    //四线圈  刺激方式错误
		 {
				    
//			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "刺激模式与当前线圈不搭配，请返回当前线圈所对应的刺激模式选项卡，选择正确的刺激模式..." );				 //显示状态	
			SendMsgToLog("刺激模式与当前线圈不搭配，请返回当前线圈所对应的刺激模式选项卡，选择正确的刺激模式...");                                               //记录日志状态
			return -1; 
				
		 }
				
	}
			

	if( pWave != NULL )     //防止内存泄露
	{
		free(pWave);
		pWave = NULL;
		
	}
	
	return 0;
}
/* 异步时钟处理函数 */
int CVICALLBACK StimAsyncTimerCallback (int reserved, int theTimerId, int event,
                                 void *callbackData, int eventData1,int eventData2)
{                                                   
   
 //定时时间到
  
	if (event == EVENT_TIMER_TICK)
	{
					
		gStimCounter ++ ;
		
		SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,(int)(100*(double)gStimCounter/(double)gStimTime));
		
		if( abs( gStimCounter-gStimTime )<0.1 )
		{
			gStimCounter = 0;
	   		gStimTime = 0;
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 );
			 
		}

	}
	
 //取消定时  
    if ( event == EVENT_DISCARD ) 
	{	
		g_StimTimerId = 0;

	}
	
	return 0;
}
void ShowStimSlide( double stimtime )
{
	gStimTime = (int)(100*stimtime); 
	gStimCounter = 0;
	g_StimTimerId = NewAsyncTimer (((double)g_StimTimerDelay) / 1000.0, -1,1, StimAsyncTimerCallback, NULL);		   //创建异步时钟
	SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 );    //刺激完成后，进度条回归零
}


void Send_Stim_Volt_Command( float64 volt[] )
{
	int          error=0;
	float64      min = 0.8;
	float64      max = 8.0; 
	char         errBuff[2048]={'\0'};



	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/

	DAQmxErrChk (DAQmxCreateTask("",&gStimVolttaskHandle));
	DAQmxErrChk (DAQmxCreateAOVoltageChan(gStimVolttaskHandle,"Dev1/ao0:1","",min,max,DAQmx_Val_Volts,""));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk (DAQmxStartTask(gStimVolttaskHandle));

	/*********************************************/
	// DAQmx Write Code
	/*********************************************/
	DAQmxErrChk (DAQmxWriteAnalogF64(gStimVolttaskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,volt,NULL,NULL));

	
Error:

	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	
	if( gStimVolttaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(gStimVolttaskHandle);
		DAQmxClearTask(gStimVolttaskHandle);
		gStimVolttaskHandle = 0;
	}
	
	if( DAQmxFailed(error) )
		MessagePopup("DAQmx Error",errBuff);
}

void Send_CHRG_DisCHRG_Command( int stim_cycle,double stim_time,double stim_freq )
{
	int         error=0;
	char        errBuff[2048]={'\0'};

	
	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxCreateTask("",&gChrgDisChrgtaskHandle));
	DAQmxErrChk (DAQmxCreateDOChan(gChrgDisChrgtaskHandle,"Dev1/port0/line2,Dev1/port0/line0,Dev1/port0/line6,Dev1/port0/line3","",DAQmx_Val_ChanPerLine));
	DAQmxErrChk (DAQmxCfgSampClkTiming(gChrgDisChrgtaskHandle,"/Dev1/PFI12",1000,DAQmx_Val_Rising,DAQmx_Val_ContSamps,stim_cycle));
 
	/*********************************************/
	// DAQmx Write Code
	/*********************************************/
	DAQmxErrChk (DAQmxWriteDigitalLines(gChrgDisChrgtaskHandle,stim_cycle,0,10.0,DAQmx_Val_GroupByChannel,pWave,NULL,NULL));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk (DAQmxStartTask(gChrgDisChrgtaskHandle));
	Send_Ctr0_Command (stim_cycle*(  (int)(stim_time*stim_freq)  ) ); 
 Error:


	if( DAQmxFailed(error) ) {
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		if( gChrgDisChrgtaskHandle != 0) 
		{
			/*********************************************/
			// DAQmx Stop Code
			/*********************************************/
			DAQmxStopTask(gChrgDisChrgtaskHandle);
			DAQmxClearTask(gChrgDisChrgtaskHandle);
			gChrgDisChrgtaskHandle = 0;
		}
		MessagePopup("DAQmx Error",errBuff);
	}

}

void Send_Ctr0_Command (int clock_num )
{
	
	int         error = 0;
	char        errBuff[2048] = {'\0'};


	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxCreateTask("",&gCtr0taskHandle));
	DAQmxErrChk (DAQmxCreateCOPulseChanFreq(gCtr0taskHandle,"Dev1/ctr0","",DAQmx_Val_Hz,DAQmx_Val_Low ,0.0,1000,0.5));
	DAQmxErrChk (DAQmxCfgImplicitTiming(gCtr0taskHandle,DAQmx_Val_FiniteSamps,clock_num));
	DAQmxErrChk (DAQmxRegisterDoneEvent(gCtr0taskHandle,0,Ctr0DoneCallback,NULL));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk (DAQmxStartTask(gCtr0taskHandle));
	

Error:

	if( DAQmxFailed(error) ) {
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	
	if( gCtr0taskHandle != 0 ) 
		{
			/*********************************************/
			// DAQmx Stop Code
			/*********************************************/
			DAQmxStopTask(gCtr0taskHandle);
			DAQmxClearTask(gCtr0taskHandle);
			gCtr0taskHandle = 0;
			
		}
	
	
	if( gChrgDisChrgtaskHandle != 0 ) 
		{
			/*********************************************/
			// DAQmx Stop Code
			/*********************************************/
		
			DAQmxStopTask(gChrgDisChrgtaskHandle);
			DAQmxClearTask(gChrgDisChrgtaskHandle);
			gChrgDisChrgtaskHandle = 0;
		}
		MessagePopup("DAQmx Error",errBuff);
	}	
}
int32 CVICALLBACK Ctr0DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData)
{
	int32   error=0;
	char    errBuff[2048]={'\0'};

	
	// Check to see if an error stopped the task.
	DAQmxErrChk (status);

Error:
	DAQmxGetExtendedErrorInfo(errBuff,2048);
	DAQmxClearTask(taskHandle);
	gCtr0taskHandle = 0; 
	
	DAQmxStopTask(gChrgDisChrgtaskHandle);
	DAQmxClearTask(gChrgDisChrgtaskHandle);
	gChrgDisChrgtaskHandle = 0;
	
	
	if( DAQmxFailed(error) )
		MessagePopup("DAQmx Error",errBuff);
	return 0;
}

int CVICALLBACK Cmd_Cc1_Sqc_Stim_Add (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    Stim_Power         = 0;
    double Stim_Frequency     = 0;
    double Train_Duration     = 0;
    double Train_Interval     = 0;
	int    numberOfRows       = 0;
	int    rowIndex           = 0;
	
	if(event == EVENT_COMMIT )
	{
		GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
	//	FmtOut("Stim_Power:%d\n",Stim_Power);
		GetCtrlVal(TabPanelHandle, TAB_CC_1_CC1_SQC_INT,&Stim_Power );
	//	FmtOut("Stim_Power:%d\n",Stim_Power);   
		GetCtrlVal(TabPanelHandle, TAB_CC_1_CC1_SQC_FQC,&Stim_Frequency );
		GetCtrlVal(TabPanelHandle, TAB_CC_1_CC1_SQC_TT,&Train_Duration );
		GetCtrlVal(TabPanelHandle, TAB_CC_1_CC1_SQC_TITV,&Train_Interval );
		/* 数据有效性验证 */
		 if( Stim_Frequency > pStimPara[Stim_Power-1].frequency)
		 {
			MessagePopup ("参数错误", "刺激强度和刺激频率不匹配！");
		 	return -1;
		 }
		 
		 if(Stim_Frequency*Train_Duration <1 )
		 {
			MessagePopup ("参数错误", "刺激频率和串时间不匹配！");
		 	return -1;
		 }
		
		
		GetNumTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, &numberOfRows);
		InsertTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, -1, 1, VAL_CELL_NUMERIC );
		SetTableRowAttribute ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, numberOfRows+1, ATTR_LABEL_POINT_SIZE, 20 ); 
	
		SetTableCellVal ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, MakePoint (1, numberOfRows+1), Stim_Power);
    	SetTableCellVal ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, MakePoint (2, numberOfRows+1), Stim_Frequency);
    	SetTableCellVal ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, MakePoint (3, numberOfRows+1), Train_Duration);
		SetTableCellVal ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, MakePoint (4, numberOfRows+1), Train_Interval);   
		SetTableSelection ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, VAL_TABLE_ROW_RANGE(numberOfRows+1)); 
		/* 加底纹 */
		GetNumTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, &numberOfRows);
		for (rowIndex = 1; rowIndex <= numberOfRows; rowIndex++)
        {
        	if (rowIndex % 2)
            	SetTableCellRangeAttribute (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);
        	else
           	 	SetTableCellRangeAttribute (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,VAL_TABLE_ROW_RANGE(rowIndex), ATTR_TEXT_BGCOLOR, 0xD0D0D0L);
        }
		
		
	}
	return 0;
}

int CVICALLBACK Cmd_Cc1_Sqc_Stim_Clc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
		
			DeleteTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, 1, -1);

			break;
	}
	return 0;
}

int CVICALLBACK Cmd_Cc1_Sqc_Stim_Del (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    numberOfRows = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, &numberOfRows); 
			if( numberOfRows>0 )
			{
			   DeleteTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, numberOfRows, 1);     
			}
			

			break;
	}
	return 0;
}

int CVICALLBACK Cmd_Sgl8_Sqc_Stim_Add (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    Stim_Power         = 0;
    double Stim_Frequency     = 0;
    double Train_Duration     = 0;
    double Train_Interval     = 0;
	int    numberOfRows       = 0;
	int    rowIndex           = 0;
	
	if(event == EVENT_COMMIT )
	{
		GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
		GetCtrlVal(TabPanelHandle, TAB_SGL_8_SGL8_SQC_INT,&Stim_Power );
		GetCtrlVal(TabPanelHandle, TAB_SGL_8_SGL8_SQC_FQC,&Stim_Frequency );
		GetCtrlVal(TabPanelHandle, TAB_SGL_8_SGL8_SQC_TT,&Train_Duration );
		GetCtrlVal(TabPanelHandle, TAB_SGL_8_SGL8_SQC_TITV,&Train_Interval );
	
		/* 数据有效性验证 */
		 if( Stim_Frequency > pStimPara[Stim_Power-1].frequency)
		 {
			MessagePopup ("参数错误", "刺激强度和刺激频率不匹配！");
		 	return -1;
		 }
		 
		 if(Stim_Frequency*Train_Duration <1 )
		 {
			MessagePopup ("参数错误", "刺激频率和串时间不匹配！");
		 	return -1;
		 }
		
		GetNumTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, &numberOfRows);
		InsertTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, -1, 1, VAL_CELL_NUMERIC );
		SetTableRowAttribute ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, numberOfRows+1, ATTR_LABEL_POINT_SIZE, 20 ); 
	
		SetTableCellVal ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, MakePoint (1, numberOfRows+1), Stim_Power);
    	SetTableCellVal ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, MakePoint (2, numberOfRows+1), Stim_Frequency);
    	SetTableCellVal ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, MakePoint (3, numberOfRows+1), Train_Duration);
		SetTableCellVal ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, MakePoint (4, numberOfRows+1), Train_Interval);   
		SetTableSelection ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, VAL_TABLE_ROW_RANGE(numberOfRows+1)); 
		/* 加底纹 */
		GetNumTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, &numberOfRows);
		for (rowIndex = 1; rowIndex <= numberOfRows; rowIndex++)
        {
        	if (rowIndex % 2)
            	SetTableCellRangeAttribute (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);
        	else
           	 	SetTableCellRangeAttribute (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,VAL_TABLE_ROW_RANGE(rowIndex), ATTR_TEXT_BGCOLOR, 0xD0D0D0L);
        }
	}
	return 0;
}

int CVICALLBACK Cmd_Sgl8_Sqc_Stim_Del (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    numberOfRows = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, &numberOfRows); 
			if( numberOfRows>0 )
			{
			   DeleteTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, numberOfRows, 1);     
			}
			

			break;
	}
	return 0;
}

int CVICALLBACK Cmd_Sgl8_Sqc_Stim_Clc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
		
			DeleteTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, 1, -1);

			break;
	}
	return 0;
}

int CVICALLBACK Cmd_Dbl8_Sqc_Stim_Add (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    Stim_Power         = 0;
    double Stim_Frequency     = 0;
    double Train_Duration     = 0;
    double Train_Interval     = 0;
	int    numberOfRows       = 0;
	int    rowIndex           = 0;
	char   coil[2]               ;
	
	if(event == EVENT_COMMIT )
	{
		GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_SQC_COIL,coil ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_SQC_INT,&Stim_Power );
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_SQC_FQC,&Stim_Frequency );
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_SQC_TT,&Train_Duration );
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_SQC_TITV,&Train_Interval );
	
		/* 数据有效性验证 */
		if( Stim_Frequency > pStimPara[Stim_Power-1].frequency)
		 {
			MessagePopup ("参数错误", "刺激强度和刺激频率不匹配！");
		 	return -1;
		 }
		 
		 if(Stim_Frequency*Train_Duration <1 )
		 {
			MessagePopup ("参数错误", "刺激频率和串时间不匹配！");
		 	return -1;
		 }
		 
		GetNumTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, &numberOfRows);
		InsertTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, -1, 1, VAL_USE_MASTER_CELL_TYPE );
		
		SetTableRowAttribute ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, numberOfRows+1, ATTR_LABEL_POINT_SIZE, 20 ); 
		SetTableCellVal ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, MakePoint (1, numberOfRows+1), coil); 
		SetTableCellVal ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, MakePoint (2, numberOfRows+1), Stim_Power);
    	SetTableCellVal ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, MakePoint (3, numberOfRows+1), Stim_Frequency);
    	SetTableCellVal ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, MakePoint (4, numberOfRows+1), Train_Duration);
		SetTableCellVal ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, MakePoint (5, numberOfRows+1), Train_Interval);   
		SetTableSelection ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, VAL_TABLE_ROW_RANGE(numberOfRows+1)); 
		/* 加底纹 */
		GetNumTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, &numberOfRows);
		for (rowIndex = 1; rowIndex <= numberOfRows; rowIndex++)
        {
        	if (rowIndex % 2)
            	SetTableCellRangeAttribute (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);
        	else
           	 	SetTableCellRangeAttribute (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,VAL_TABLE_ROW_RANGE(rowIndex), ATTR_TEXT_BGCOLOR, 0xD0D0D0L);
        }
		
		
	}
	return 0;
}

int CVICALLBACK Cmd_Dbl8_Sqc_Stim_Del (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    numberOfRows = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, &numberOfRows); 
			if( numberOfRows>0 )
			{
			   DeleteTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, numberOfRows, 1);     
			}
			

			break;
	}
	return 0;
}

int CVICALLBACK Cmd_Dbl8_Sqc_Stim_Clc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			DeleteTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, 1, -1);

			break;
	}
	return 0;
}

int CVICALLBACK Dbl8_Sqc_Coil (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char coil[2];
	
	switch (event)
	{
		case EVENT_LOST_FOCUS:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_SQC_COIL,coil ); 
		
			if( (coil[0] == 'A')||(coil[0] == 'B'))
				return 0;
			else if(coil[0] == 'a')
			{
				SetCtrlVal( TabPanelHandle, TAB_DBL_8_DBL8_SQC_COIL,"A" ); 
			}
			else if(coil[0] == 'b')
			{
				SetCtrlVal( TabPanelHandle, TAB_DBL_8_DBL8_SQC_COIL,"B" ); 
			}
			else 
			{
				SetCtrlVal( TabPanelHandle, TAB_DBL_8_DBL8_SQC_COIL,"A" ); 
			}
				

			break;
	}
	return 0;
}

void Send_FCS_SEL_Command(int nChnlNum)
{
	int         error=0;    
	char        errBuff[2048]={'\0'};
	uInt8       data[4]={0,0,0,0};   		
      

	switch(nChnlNum)
	{
		case 1:
			data[3] = 0;
			data[2] = 1;
			data[1] = 1;
   			data[0] = 1; 
//			MessagePopup ("", "1");
			
			break;
		case 2:
			data[3] = 0;
			data[2] = 1;
			data[1] = 1;
   			data[0] = 0; 
//			MessagePopup ("", "2");  
			break;				
		case 3:
			data[3] = 0;
			data[2] = 1;
			data[1] = 0;
   			data[0] = 1;  
//			MessagePopup ("", "3");  
			break;			
		case 4:
			data[3] = 0;
			data[2] = 1;
			data[1] = 0;
   			data[0] = 0; 
//			MessagePopup ("", "4");  
			break;
		case 5:
			data[3] = 0;
			data[2] = 0;
			data[1] = 1;
   			data[0] = 1; 
//			MessagePopup ("", "5");  
			break;
		case 6:
			data[3] = 0;
			data[2] = 0;
			data[1] = 1;
   			data[0] = 0;  
//			MessagePopup ("", "6");  
			break;
		case 7:
			data[3] = 0;
			data[2] = 0;
			data[1] = 0;
   			data[0] = 1;  
//			MessagePopup ("", "7");  
			break;			
		
		
		default:
			data[3] = 1;
			data[2] = 0;
			data[1] = 0;
   			data[0] = 0; 
//			MessagePopup ("", "默认");  
			break;

	}


		/*********************************************/
		// DAQmx Configure Code
		/*********************************************/
	
		DAQmxErrChk (DAQmxCreateTask("",&gFcsSeltaskHandle));
		DAQmxErrChk (DAQmxCreateDOChan(gFcsSeltaskHandle,"Dev1/port1/line0:3","",DAQmx_Val_ChanForAllLines));

		/*********************************************/
		// DAQmx Start Code
		/*********************************************/
		DAQmxErrChk (DAQmxStartTask(gFcsSeltaskHandle));

		/*********************************************/
		// DAQmx Write Code
		/*********************************************/
		DAQmxErrChk (DAQmxWriteDigitalLines(gFcsSeltaskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL));

Error:
	SetWaitCursor(0);
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	if( gFcsSeltaskHandle!=0 ) {
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(gFcsSeltaskHandle);
		DAQmxClearTask(gFcsSeltaskHandle);
		gFcsSeltaskHandle = 0;
		
	}
	if( DAQmxFailed(error) )
		MessagePopup("DAQmx Error",errBuff);

}

int CVICALLBACK Cc4_Sqc_Fcs (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char fcs[2];
	
	switch (event)
	{
		case EVENT_LOST_FOCUS:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal(TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,fcs ); 
		
			if( (fcs[0] == 'A')||(fcs[0] == 'B')||(fcs[0] == 'C')||(fcs[0] == 'D')||(fcs[0] == 'E')||(fcs[0] == 'F')||(fcs[0] == 'G') )
				return 0;
			else if(fcs[0] == 'a')
			{
				SetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,"A" ); 
			}
			else if(fcs[0] == 'b')
			{
				SetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,"B" ); 
			}
			else if(fcs[0] == 'c')
			{
				SetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,"C" ); 
			}
			else if(fcs[0] == 'd')
			{
				SetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,"D" ); 
			}
			else if(fcs[0] == 'e')
			{
				SetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,"E" ); 
			}
			else if(fcs[0] == 'f')
			{
				SetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,"F" ); 
			}
			else if(fcs[0] == 'g')
			{
				SetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,"G" ); 
			}
			else 
			{
				SetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,"A" ); 
			}
				

			break;
	}
	return 0;
}

int CVICALLBACK Cmd_Cc4_Sqc_Stim_Add (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    Stim_Power         = 0;
    double Stim_Frequency     = 0;
    double Train_Duration     = 0;
    double Train_Interval     = 0;
	int    numberOfRows       = 0;
	int    rowIndex           = 0;
	char   fcs[2]               ;  
	
	if(event == EVENT_COMMIT )
	{
		GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
		GetCtrlVal(TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,fcs ); 
		GetCtrlVal(TabPanelHandle, TAB_CC_4_CC4_SQC_INT,&Stim_Power );
		GetCtrlVal(TabPanelHandle, TAB_CC_4_CC4_SQC_FQC,&Stim_Frequency );
		GetCtrlVal(TabPanelHandle, TAB_CC_4_CC4_SQC_TT,&Train_Duration );
		GetCtrlVal(TabPanelHandle, TAB_CC_4_CC4_SQC_TITV,&Train_Interval );
	
		/* 数据有效性验证 */
		 if( Stim_Frequency > pStimPara[Stim_Power-1].frequency)
		 {
			MessagePopup ("参数错误", "刺激强度和刺激频率不匹配！");
		 	return -1;
		 }
		 
		 if((int)(Stim_Frequency*Train_Duration) <1 )
		 {
			MessagePopup ("参数错误", "刺激频率和串时间不匹配！");
		 	return -1;
		 }
		
		GetNumTableRows ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, &numberOfRows);
		InsertTableRows ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, -1, 1, VAL_USE_MASTER_CELL_TYPE );
		SetTableRowAttribute ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, numberOfRows+1, ATTR_LABEL_POINT_SIZE, 20 ); 
	
		SetTableCellVal ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, MakePoint (1, numberOfRows+1), fcs);  
		SetTableCellVal ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, MakePoint (2, numberOfRows+1), Stim_Power);
    	SetTableCellVal ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, MakePoint (3, numberOfRows+1), Stim_Frequency);
    	SetTableCellVal ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, MakePoint (4, numberOfRows+1), Train_Duration);
		SetTableCellVal ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, MakePoint (5, numberOfRows+1), Train_Interval);   
		SetTableSelection ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, VAL_TABLE_ROW_RANGE(numberOfRows+1)); 
		/* 加底纹 */
		GetNumTableRows ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, &numberOfRows);
		for (rowIndex = 1; rowIndex <= numberOfRows; rowIndex++)
        {
        	if (rowIndex % 2)
            	SetTableCellRangeAttribute (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);
        	else
           	 	SetTableCellRangeAttribute (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,VAL_TABLE_ROW_RANGE(rowIndex), ATTR_TEXT_BGCOLOR, 0xD0D0D0L);
        }
	}
	return 0;
}

int CVICALLBACK Cmd_Cc4_Sqc_Stim_Del (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    numberOfRows = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, &numberOfRows); 
			if( numberOfRows>0 )
			{
			   DeleteTableRows ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, numberOfRows, 1);     
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK Cmd_Cc4_Sqc_Stim_Clc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			DeleteTableRows ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, 1, -1);

			break;
	}
	return 0;
}
