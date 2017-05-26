//==============================================================================
//
// Title:       TMS
// Purpose:     TMS ����ƽ̨
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

	//��ȡ�̼������ļ�
	if( ReadStimPara( ) == FALSE)
	{
		SendMsgToLog("�̼������ļ���ʧ������ѹر�...");
		return 0;
	}
	
	Sys_Init();                                                                          //ϵͳ��ʼ��
	StatusDetect_Task( ); //״̬���
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
	//	//���붯̬����ʹ�õ��ڴ��
		
		pStimPara = (StimPara *)malloc(sizeof(StimPara)*100);
		if ( pStimPara == NULL )        // �ڴ�����ʧ��,��ʾ�˳�
		{
			fclose(fp);
			return FALSE ;             // ��ֹ��������,���ز���ϵͳ
		}
		 
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%d %f  %f ",&pStimPara[i].power,&pStimPara[i].volt,&pStimPara[i].frequency);
		}
	}
	fclose(fp);	
	return TRUE;
}


void Focus_Sel(int n)														//����ѡ������  
{

	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle );
//	GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_A,&bAState );
	
	if ( nSelFcsNum == n )  //������ظ�����������κβ���
	{
		return;
	}
	
	nSelFcsNum = n;

	switch( n )
	
	{
		case FCS_4_TLBR:   //����1��4������
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_DK_RED); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_WHITE); 
			SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_WHITE); 
			
			break;
			
		case FCS_1_TOP:    //����2���������㣨�ϣ�
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
void Sys_Init( )                     												             		//ϵͳ��ʼ�� 
{
	
	/* ��������ͼƬ */

	DisplayImage( );   
	
	gOneSecondMeasureEnable = 0;
	gOneTenthSecondMeasureEnable = 0; 
	
	
	//��Ȧ�ͽ���	
	nSelCoilNum = COIL_NO;   
	nSelFcsNum = FCS_NO;
	nSelStimNum = FALSE;
	
	/* ���õ�Դ����Ȧָʾ��Ĭ����ɫ��״̬*/
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_POWER, ATTR_ON_COLOR, VAL_RED);
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_POWER, ATTR_OFF_COLOR, VAL_GREEN); 
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_COIL, ATTR_ON_COLOR, VAL_RED);
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_COIL, ATTR_OFF_COLOR, VAL_GREEN); 
	SetCtrlVal ( panelHandle,PANEL_SYS_STATE_POWER , TRUE);
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "��Դ����"); 
	SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , TRUE);
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "δ����Ȧ"); 

	
	/* ��һ��ҳ�� */
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
	
	
	
	/* �ڶ���ҳ�� */
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
	
	/* ������ҳ�� */
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
	
	/* ���ĸ�ҳ�� */
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
	
	
	/* �̼���ť������ */
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);  
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
	
	/* �ϴ���Ȧѡ���� */   
	Pre_Coil[0]=0;     //P1.4
	Pre_Coil[1]=0;     //P1.5 
	Pre_Coil[2]=0;	   //P1.6 
	Pre_Coil[3]=1;     //�ж�λ

	/* ��ʾ״̬ */
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "ϵͳ��ʼ�����..." );
	SendMsgToLog("ϵͳ��ʼ�����..."); 
	
}


/* ��ʾͼƬ */
void DisplayImage( )										   
{
	char *fileName;
	char projectDir[ MAX_PATHNAME_LEN ];
	char fullPath[ MAX_PATHNAME_LEN ];

	if (GetProjectDir (projectDir) < 0)
	
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��ȡ�����Ŀ¼ʧ�ܣ�ͼƬ����ʧ��" );	

	else
	
	{
		/* ��Ȧָʾ --- ����Ȧ */
		fileName = "Coil\\COIL_CC_1.png";  
		MakePathname (projectDir, fileName, fullPath);
//		FmtOut(fullPath)  ;
		DisplayImageFile (panelHandle, PANEL_COIL_CC_1, fullPath); 
		
		/* ��Ȧָʾ --- ��8�� */
		fileName = "Coil\\COIL_SGL_8.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_COIL_SGL_8, fullPath); 
		
		/* ��Ȧָʾ --- ˫8�� */
		fileName = "Coil\\COIL_DBL_8.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_COIL_DBL_8, fullPath); 
		
		/* ��Ȧָʾ --- ����Ȧ */
		fileName = "Coil\\COIL_CC_4.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_COIL_CC_4, fullPath); 
		
		/* ������� --- ����LGOO */       
		fileName = "Logo\\Logo_PKU.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_LOGO_PKU, fullPath);          	//����logo   
		
		/* ������� --- ����LGOO */
		fileName = "Logo\\Logo_XW.png";  
		MakePathname (projectDir, fileName, fullPath); 
		DisplayImageFile (panelHandle, PANEL_LOGO_XW, fullPath);    	        //����logo   
		
		
		/* �̼�ģʽ --- ���δ̼� */  	
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
		
		/* �̼�ģʽ --- �ظ��̼� */  	
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
		
		
		/* �̼�ģʽ --- ���д̼� */  	
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

void StatusDetect_Task( )                                   //���ݲɼ�ʱ��
{
	SendMsgToLog("����״̬���...");
	g_StatusTimerId = NewAsyncTimer (((double)g_StatusTimerDelay) / 1000.0, -1,1, StatusAsyncTimerCallback, NULL);		   //�����첽ʱ��
	
	CmtScheduleThreadPoolFunction ( DEFAULT_THREAD_POOL_HANDLE, StatusDetectThreadFunction, NULL, NULL );   //���ݲɼ��߳� 
	
}

/* �첽ʱ�Ӵ����� */
int CVICALLBACK StatusAsyncTimerCallback (int reserved, int theTimerId, int event,
                                 void *callbackData, int eventData1,int eventData2)
{                                                   
   
 //��ʱʱ�䵽
    if (event == EVENT_TIMER_TICK)
	{
		gTimeCounter++;
	
		
		if ((gTimeCounter%3) == 0)  		//ÿʮ��֮һ�����һ�� 
		{
			gOneTenthSecondMeasureEnable = 1;
//			putchar('a'); 
		}
		if ((gTimeCounter%10) == 0)		    //ÿһ�����һ��
		{
			gOneSecondMeasureEnable  = 1;
			gTimeCounter = 0;			    //ÿ������һ�£���ֹ���۹������
//			putchar('b'); 
		}
	}
	
 //ȡ����ʱ  
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
		
		if(gOneSecondMeasureEnable == 1)          	//  ��������ȼ���
		{
 
			TmpAcq_Task(); 
			gOneSecondMeasureEnable  = 0; 
			
		}
		
		else if(gOneTenthSecondMeasureEnable == 1)      //  ʮ��֮һ��������ȼ���                                 
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
		
		/* ��ֵ�˲� */
		for(i=0;i<sampsPerChan;i++)
		{
			TempVal += data[i];
		}
		TempVal = TempVal/sampsPerChan;
		
		TempVal = TempVal*20;
		SetCtrlVal ( panelHandle, PANEL_SYS_STATE_TEMP ,TempVal );
		/* �¶��ж� */
		if( TempVal < 60 )
		{
			/* �޲��� */
			
			
		}
		else if( (TempVal >= 60) && (TempVal < 80) )
		{
			/* ���� */
			SendMsgToLog("�¶ȴﵽ�ٽ�״̬��60��~80�ȣ�...");
			
			
		}
		else if((TempVal >= 80))
		{
			/* ǿ��ֹͣ�̼� */
			SendMsgToLog("�¶�̫�ߣ�����80�ȣ����Ժ��ٽ��д̼�..."); 
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
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "�¶ȼ���������..." );
	    SendMsgToLog("�¶ȼ���������..."); 
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
		/* �˴���ӵ��δ̼����� */
		
		
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
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "���δ̼���������ʧ�ܣ�" );				 //��ʾ״̬	
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
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "��Դ����");    
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "ϵͳ��Դ���ϣ�" );	
		 SendMsgToLog("��Դ���ֹ���...");
	}
	else
	{
		 SetCtrlVal ( panelHandle,PANEL_SYS_STATE_POWER , FALSE); 
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "��Դ����"); 
		  
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
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��Դ��������ʧ��..." );				 //��ʾ״̬
		SendMsgToLog("��Դ��������ʧ��..."); 
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
	
	/* ����ר��  */
	data[0] = 0;  	
	data[1] = 0;
	data[2] = 1;
	
	if(Pre_Coil[3] == 1)    //��һ�β���
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
	if((data[0] == 0)&&(data[1] == 1)&&(data[2] == 1))                               // Բ����Ȧ
	{
		/* ��Ȧͼ�� */
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , FALSE);
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "��Ȧ����"); 
		nSelCoilNum = COIL_CC_1;
		SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1); 
	
		
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_DK_RED); 	   //Բ��
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);       //8��
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	   //˫8��
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 	   //����Ȧ 
	
		
		
	    /* ���ô̼���ť */
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  		
		SendMsgToLog("��ǰʹ��Բ����Ȧ..."); 
		
	}
	else if((data[0] == 1)&&(data[1] == 0)&&(data[2] == 0))	                         // 8����Ȧ 
	{
		/* ��Ȧͼ�� */   
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , FALSE); 
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "��Ȧ����");  
		nSelCoilNum = COIL_SGL_8;
		SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8); 
	
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_DK_RED);       
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 	   
	
   		
	    /* ���ô̼���ť */
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
		SendMsgToLog("��ǰʹ��8����Ȧ...");  
	}
	else if((data[0] == 0)&&(data[1] == 1)&&(data[2] == 0))	                        // ˫8����Ȧ 
	{
		/* ��Ȧͼ�� */  
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , FALSE); 
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "��Ȧ����");  
		
		nSelCoilNum = COIL_DBL_8;
		SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8); 
		
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);       
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_DK_RED); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 	   
	
   		
	    /* ���ô̼���ť */
		
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
		SendMsgToLog("��ǰʹ��˫8����Ȧ...");    
	}
	else if((data[0] == 0)&&(data[1] == 0)&&(data[2] == 1))	                         // ����Ȧ 
	{
		/* ��Ȧͼ�� */ 
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , FALSE);
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "��Ȧ����");  
		
		nSelCoilNum = COIL_CC_4;
		SetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4); 
		
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	  
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);      
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_DK_RED); 	   
	
	    /* ��ֹ�̼���ť */
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);  
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);  
		SendMsgToLog("��ǰʹ������Ȧ...");  
	}														    
 	else 	                                                                         // û����Ȧ 
	{
		  
		if((data[0] == 1)&&(data[1] == 1)&&(data[2] == 1))
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "û����Ȧ" );				 //��ʾ״̬ 
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "û����Ȧ");  
			SendMsgToLog("��ǰû����Ȧ...");  
			nSelCoilNum = COIL_NO;
		
		}
		else
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��Ȧ�ź��д���" );				 //��ʾ״̬
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "��Ȧ����"); 
			SendMsgToLog("��Ȧ��������δ֪״̬..."); 
			nSelCoilNum = COIL_FAIL;  	                         
		}
		/* ��Ȧͼ�� */ 
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , TRUE);  
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);       
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	  
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 	 
		GetActiveTabPage (panelHandle, PANEL_TAB_STIM_MODE, &nAtvPageNum);
		GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, nAtvPageNum, &TabPanelHandle);
		

		 /* ��ֹ�̼���ť */
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
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��Ȧ��������ʧ�ܣ�" );				 //��ʾ״̬	
	    SendMsgToLog("��Ȧ��������ʧ��..."); 
		SendMsgToLog( errBuff ); 
	}	
		
}

int CVICALLBACK Cmd_Start_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
			
	if(event == EVENT_COMMIT )
	{

		CmtScheduleThreadPoolFunction ( DEFAULT_THREAD_POOL_HANDLE, Stim_ThreadFunction, NULL, NULL );   //�̼��߳�   

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
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��Ȧ�źų���" );				 //��ʾ״̬	
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, eventData2, &TabPanelHandle); 
		}
		else if( nSelCoilNum == -1 )
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "δ����Ȧ��" );				 //��ʾ״̬	
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





/* ֹͣ�̼� */   
void StimProgress_Exit( )
{

	
	bStim_Quit = 1;            //�̼�ֹͣ��־λ��Ϊ��Ч
	
	if(g_StimTimerId != 0)	  //�رս����� 
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
	
	if( pWave != NULL )     //��ֹ�ڴ�й¶
	{
		free(pWave);
		pWave = NULL;
		
	}
	
}

/* ֹͣ��� */ 
void StatusDetect_Exit( )
{
	   /* �رղ����첽��ʱ�� */
	if( g_StatusTimerId != 0)
	{
		DiscardAsyncTimer( g_StatusTimerId );
		g_StatusTimerId = 0;	
	}
	
	/* �رղ����첽��ʱ�� */ 
	gQuitStatusAcqTread == 1;
	/* �¶Ȳ������� ֹͣ */
	if(TempAcqtaskHandle != 0)
	{
		DAQmxStopTask( TempAcqtaskHandle );
		DAQmxClearTask( TempAcqtaskHandle );
		TempAcqtaskHandle = 0;	
	}
	/* ������ڴ��ͷ� */ 
	if( data != NULL )
	{
		free( data ); 
		data = NULL;
	}
	/* ��Դ���� */    	
	if( PwrOktaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(PwrOktaskHandle);
		DAQmxClearTask(PwrOktaskHandle);
		PwrOktaskHandle = 0;
	}
		
	/* ���δ̼����� */  
	if( SglDisOktaskHandle!=0 ) 
	{
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(SglDisOktaskHandle);
		DAQmxClearTask(SglDisOktaskHandle);
		SglDisOktaskHandle = 0;
	}
	
	/* ��Ȧ������� */ 
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_SGL_8 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_SGL_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_SGL_STIM, TRUE ); 
				nSelStimNum = CC1_SGL_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
			
		//	printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);

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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_SGL_8 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle );
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_RPT_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_RPT_STIM, TRUE ); 
				nSelStimNum = CC1_RPT_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum); 
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_SGL_8 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_SQC_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_CC_1_CB_CC1_SQC_STIM, TRUE ); 
				nSelStimNum = CC1_SQC_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	   //  	printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum); 	
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_SGL_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_SGL_STIM, TRUE ); 
				nSelStimNum = SGL8_SGL_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
		//	printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_RPT_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_RPT_STIM, TRUE ); 
				nSelStimNum = SGL8_RPT_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
		//	printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_DBL_8 ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_SQC_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_SGL_8_CB_SGL8_SQC_STIM, TRUE ); 
				nSelStimNum = SGL8_SQC_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SGL_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SGL_STIM, TRUE ); 
				nSelStimNum = DBL8_SGL_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_STIM, TRUE ); 
				nSelStimNum = DBL8_RPT_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_CC_4 ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SQC_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SQC_STIM, TRUE ); 
				nSelStimNum = DBL8_SQC_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_DBL_8  ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_SQC_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_SQC_STIM, TRUE ); 
				nSelStimNum = CC4_SQC_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_DBL_8  ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_RPT_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_RPT_STIM, TRUE ); 
				nSelStimNum = CC4_RPT_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
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
				
				ClearAllStimMode( ); //�������ѡ��
				
				if( ( nSelCoilNum == COIL_CC_1 ) || ( nSelCoilNum == COIL_SGL_8  ) || ( nSelCoilNum == COIL_DBL_8  ) )
				{
					SetActiveTabPage ( panelHandle, PANEL_TAB_STIM_MODE, nSelCoilNum );
					
				}
				else if( nSelCoilNum == COIL_FAIL  )
				{
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч��");
					
				}
				else if( nSelCoilNum == COIL_NO  )
				{
					MessagePopup ("��Ȧ����", "û����Ȧ���̼�ģʽѡ����Ч��");
					
				}
				
				return 1;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_SGL_STIM, &bState );
			if ( bState == TRUE )
			{
				ClearAllStimMode( ); //�������ѡ��
				SetCtrlVal( TabPanelHandle,TAB_CC_4_CB_CC4_SGL_STIM, TRUE ); 
				nSelStimNum = CC4_SGL_STIM ; 
			}
			else
			{
				ClearAllStimMode( ); //�������ѡ�� 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}
void SendMsgToLog( char str[] )
{
	//��ȡ��ǰ����
	int year,month,day,hour,mimute,second;
	char sysdate[100];
	char filename[100];
	char projectDir[ MAX_PATHNAME_LEN ];
	char fullPath[ MAX_PATHNAME_LEN ]; 
	FILE  *fp = NULL; 
	
	if (GetProjectDir (projectDir) < 0)
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��ȡ�����Ŀ¼ʧ�ܣ���־����ʧ��" );
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
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��־�ļ���ʧ�ܣ�" );
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
	/* ��һ��ҳ�� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle_Temp); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_1_CB_CC1_SGL_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_1_CB_CC1_RPT_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_1_CB_CC1_SQC_STIM, FALSE );
	/* �ڶ���ҳ�� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle_Temp); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_SGL_8_CB_SGL8_SGL_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_SGL_8_CB_SGL8_RPT_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_SGL_8_CB_SGL8_SQC_STIM, FALSE );
	/* ������ҳ�� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle_Temp); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
	/* ���ĸ�ҳ�� */
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
	
	/* ���ݺϷ�����֤ */
	
	if( nSelCoilNum == COIL_FAIL )
	{
//		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��Ȧ���ֹ��ϣ����ܽ��д̼�..." );				 //��ʾ״̬	
		SendMsgToLog("��Ȧ���ֹ��ϣ����ܽ��д̼�...");                                               //��¼��־״̬
		return -1;
	}
			
	if( nSelCoilNum == COIL_NO )
	{
//		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "û����Ȧ�����ܽ��д̼�..." );				 //��ʾ״̬	
		SendMsgToLog("û����Ȧ�����ܽ��д̼�...");                                               //��¼��־״̬
		return -1;
		
	}
			
	if( nSelStimNum == NO_SEL_STIM )
	{
//		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "û��ѡ��̼����ͣ����ܽ��д̼�..." );				 //��ʾ״̬	
		SendMsgToLog("û��ѡ��̼����ͣ����ܽ��д̼�...");                                               //��¼��־״̬
		return -1;
	}
	
	if( pWave != NULL )     //��ֹ�ڴ�й¶
	{
		free(pWave);
		pWave = NULL;
	}
	
	
	
	if( nSelCoilNum == COIL_CC_1 )
	{
		 if( nSelStimNum == CC1_SGL_STIM )		  //Բ����Ȧ  ���δ̼�
		 {
		 	
			/* �̼��������� */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_SGL_INT, &intensity_A );
		
			/* ���͵�ѹ */
			stim_cycle_A = 1000;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* ���β��� */
		
			// port0:line2----A·���
			// port0:line0----A·�ŵ� 
			// port0:line6----B·��� 
			// port0:line3----B·�ŵ�
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("ϵͳ����", "�����ڴ����");
				return -1;    
			}
			for( i=0;i<stim_cycle_A;i++ )
			{
				pWave[stim_cycle_A*0+i] = 1;
				pWave[stim_cycle_A*1+i] = 0;
				pWave[stim_cycle_A*2+i] = 0;
				pWave[stim_cycle_A*3+i] = 0;
			}
			/* ����ź����5��Ϊ�� */
			pWave[stim_cycle_A*1-5] = 0;
			pWave[stim_cycle_A*1-4] = 0;
			pWave[stim_cycle_A*1-3] = 0;
			pWave[stim_cycle_A*1-2] = 0;
			pWave[stim_cycle_A*1-1] = 0;
			/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
			pWave[stim_cycle_A*2-3] = 1;
			pWave[stim_cycle_A*2-2] = 1;
			/* ��ʼ�̼� */
	//		FmtOut("�̼�����֮ǰ\n");
			Send_CHRG_DisCHRG_Command( stim_cycle_A,1,1 );
	//		FmtOut("�̼�����֮��\n"); 
			
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
			
		 }
		else if( nSelStimNum == CC1_RPT_STIM )		 //Բ����Ȧ  �ظ��̼�  
		{
			
			
			/* �̼�������ȡ */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_INT, &intensity_A );
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_FQC, &frequency_A ); 
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TT, &train_time_A ); 
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TN, &train_num_A ); 
			GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TITV, &train_interval_A ); 
			/* �Ϸ�����֤ */
			
			//ǿ�Ⱥ�Ƶ��Ҫƥ��
			if((int)(frequency_A*train_time_A)<1)  //ÿ�������ٴ̼�һ��
			{
				MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
				return -1;
			}
			
			if(frequency_A >= pStimPara[intensity_A-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
			{
				MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
				return -1;	
			}
			
			
			if((frequency_A*train_time_A*train_num_A) > 6000 )   //������������ܳ���6000 
			{
				MessagePopup ("��������", "�������������6000��");
				return -1;	
			}

			/* ���͵�ѹ */
		//	;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* ���β��� */
		
			// port0:line2----A·���
			// port0:line0----A·�ŵ� 
			// port0:line6----B·��� 
			// port0:line3----B·�ŵ�
			stim_cycle_A = (int)(1000.0/frequency_A);
			
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("ϵͳ����", "�����ڴ����");
				return -1;    
			}
			
			for( i=0;i<stim_cycle_A;i++ )
			{
				pWave[stim_cycle_A*0+i] = 1;
				pWave[stim_cycle_A*1+i] = 0;
				pWave[stim_cycle_A*2+i] = 0;
				pWave[stim_cycle_A*3+i] = 0;
			}
			/* ����ź����5��Ϊ�� */
			pWave[stim_cycle_A*1-5] = 0;
			pWave[stim_cycle_A*1-4] = 0;
			pWave[stim_cycle_A*1-3] = 0;
			pWave[stim_cycle_A*1-2] = 0;
			pWave[stim_cycle_A*1-1] = 0;
			/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
			pWave[stim_cycle_A*2-3] = 1;
			pWave[stim_cycle_A*2-2] = 1;
		
			/* ���������� */
			ShowStimSlide( train_time_A*train_num_A+train_interval_A*(train_num_A-1) );
			/* ��ʼ�̼� */
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
		 else if( nSelStimNum == CC1_SQC_STIM )		 //Բ����Ȧ  ���д̼�  
		 {
			
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, &numberOfRows);
		
			if(numberOfRows <1)
			{
			    bStim_Quit = 0; 
				return -1; 
			}
			//��֤������Ч��
			nPluse = 0;
			for(i=1;i<=numberOfRows;i++ )
			{
				/* ��ȡ���� */
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (1, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (2, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (4, i) ,&train_interval_A );
				
				//ǿ�Ⱥ�Ƶ��Ҫƥ��
				if((int)(frequency_A*train_time_A)<1)  //ÿ�������ٴ̼�һ��
				{
					MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
					return -1;
				}
			
				if(frequency_A >= pStimPara[intensity_A-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
				{
					MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
					return -1;	
				}
				nPluse += (int)( frequency_A*train_time_A );
			
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0; 
					return -1;
				}
			}
			
			if( nPluse > 6000 )   //������������ܳ���6000 
			{
				MessagePopup ("��������", "�������������6000��");
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
			/* ���������� */
			ShowStimSlide( Stim_Time_A );
			
			
			/*�̼���ʼ*/
			
			for(i=1;i<=numberOfRows-1;i++ )
			{
				/* ��ȡ���� */
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (1, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (2, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (4, i) ,&train_interval_A );
				
				/* ���͵�ѹ */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = pStimPara[intensity_A-1].volt;		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
					
				/* ���β��� */
		
				// port0:line2----A·���
				// port0:line0----A·�ŵ� 
				// port0:line6----B·��� 
				// port0:line3----B·�ŵ�
				if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
				{
					MessagePopup ("ϵͳ����", "�����ڴ����");
					return -1;    
				}
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* ����ź����5��Ϊ�� */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
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
				
			
				//���һ�δ̼�
			
				/* ��ȡ���� */
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (1, numberOfRows) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (2, numberOfRows) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, numberOfRows) ,&train_time_A );
			//	GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_RPT_SQC,MakePoint (4, numberOfRows) ,&train_interval_A );
				
				/* ���͵�ѹ */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = pStimPara[intensity_A-1].volt;		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
					
				/* ���β��� */
		
				// port0:line2----A·���
				// port0:line0----A·�ŵ� 
				// port0:line6----B·��� 
				// port0:line3----B·�ŵ�
				if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
				{
					MessagePopup ("ϵͳ����", "�����ڴ����");
					return -1;    
				}
				
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* ����ź����5��Ϊ�� */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
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
		 else                                  //Բ����Ȧ  �̼���ʽ����
		 {
			
//			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "�̼�ģʽ�뵱ǰ��Ȧ�����䣬�뷵�ص�ǰ��Ȧ����Ӧ�Ĵ̼�ģʽѡ���ѡ����ȷ�Ĵ̼�ģʽ..." );				 //��ʾ״̬	
			SendMsgToLog("�̼�ģʽ�뵱ǰ��Ȧ�����䣬�뷵�ص�ǰ��Ȧ����Ӧ�Ĵ̼�ģʽѡ���ѡ����ȷ�Ĵ̼�ģʽ...");                                               //��¼��־״̬
			return -1; 
		
		 }
				
				
	}
	else if( nSelCoilNum == COIL_SGL_8 )
	{
		if( nSelStimNum == SGL8_SGL_STIM )	  //8����Ȧ  ���δ̼� 
		 {
			 
			/* �̼��������� */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_SGL_INT, &intensity_A );
		
			/* ���͵�ѹ */
			stim_cycle_A = 1000;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* ���β��� */
		
			// port0:line2----A·���
			// port0:line0----A·�ŵ� 
			// port0:line6----B·��� 
			// port0:line3----B·�ŵ�
			
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("ϵͳ����", "�����ڴ����");
				return -1;    
			}
		
			for( i=0;i<stim_cycle_A;i++ )
			{
				pWave[stim_cycle_A*0+i] = 1;
				pWave[stim_cycle_A*1+i] = 0;
				pWave[stim_cycle_A*2+i] = 0;
				pWave[stim_cycle_A*3+i] = 0;
			}
			/* ����ź����5��Ϊ�� */
			pWave[stim_cycle_A*1-5] = 0;
			pWave[stim_cycle_A*1-4] = 0;
			pWave[stim_cycle_A*1-3] = 0;
			pWave[stim_cycle_A*1-2] = 0;
			pWave[stim_cycle_A*1-1] = 0;
			/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
			pWave[stim_cycle_A*2-3] = 1;
			pWave[stim_cycle_A*2-2] = 1;
			/* ��ʼ�̼� */
	//		FmtOut("�̼�����֮ǰ\n");
			Send_CHRG_DisCHRG_Command( stim_cycle_A,1,1 );
	//		FmtOut("�̼�����֮��\n"); 
			
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
		
					 
					 
					 
		 }
		 else if( nSelStimNum == SGL8_RPT_STIM )   //8����Ȧ  �ظ��̼� 
		 {
				    
			/* �̼�������ȡ */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_INT, &intensity_A );
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_FQC, &frequency_A ); 
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TT, &train_time_A ); 
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TN, &train_num_A ); 
			GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TITV, &train_interval_A ); 
				//ǿ�Ⱥ�Ƶ��Ҫƥ��
			if((int)(frequency_A*train_time_A)<1)  //ÿ�������ٴ̼�һ��
			{
				MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
				return -1;
			}
			
			if(frequency_A >= pStimPara[intensity_A-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
			{
				MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
				return -1;	
			}
			
			
			if((frequency_A*train_time_A*train_num_A) > 6000 )   //������������ܳ���6000 
			{
				MessagePopup ("��������", "�������������6000��");
				return -1;	
			}

			/* ���͵�ѹ */
		//	;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* ���β��� */
		
			// port0:line2----A·���
			// port0:line0----A·�ŵ� 
			// port0:line6----B·��� 
			// port0:line3----B·�ŵ�
			stim_cycle_A = (int)(1000.0/frequency_A);
			
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("ϵͳ����", "�����ڴ����");
				return -1;    
			}
			
			for( i=0;i<stim_cycle_A;i++ )
			{
				pWave[stim_cycle_A*0+i] = 1;
				pWave[stim_cycle_A*1+i] = 0;
				pWave[stim_cycle_A*2+i] = 0;
				pWave[stim_cycle_A*3+i] = 0;
			}
			/* ����ź����5��Ϊ�� */
			pWave[stim_cycle_A*1-5] = 0;
			pWave[stim_cycle_A*1-4] = 0;
			pWave[stim_cycle_A*1-3] = 0;
			pWave[stim_cycle_A*1-2] = 0;
			pWave[stim_cycle_A*1-1] = 0;
			/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
			pWave[stim_cycle_A*2-3] = 1;
			pWave[stim_cycle_A*2-2] = 1;
		
			/* ���������� */
			ShowStimSlide( train_time_A*train_num_A+train_interval_A*(train_num_A-1) );
			/* ��ʼ�̼� */
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
		 else if( nSelStimNum == SGL8_SQC_STIM )  //8����Ȧ  ���д̼�
		 {
				     
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
			GetNumTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, &numberOfRows);
		
			if(numberOfRows <1)
			{
			   return -1; 
			}
			//��֤������Ч��
			 for(i=1;(i<=numberOfRows-1)&&(bStim_Quit !=1);i++ )
			{
				/* ��ȡ���� */
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (1, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (2, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (4, i) ,&train_interval_A );
				
				//ǿ�Ⱥ�Ƶ��Ҫƥ��
				if((int)(frequency_A*train_time_A)<1)  //ÿ�������ٴ̼�һ��
				{
					MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
					return -1;
				}
			
				if(frequency_A >= pStimPara[intensity_A-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
				{
					MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
					return -1;	
				}
				nPluse += (int)( frequency_A*train_time_A );
			
				if( bStim_Quit == 1 )
				{
					bStim_Quit = 0; 
					return -1;
				}
				
			}
			
			if( nPluse > 6000 )   //������������ܳ���6000 
			{
				MessagePopup ("��������", "�������������6000��");
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
			/* ���������� */
			
			ShowStimSlide( Stim_Time_A );
			 
			
			
			
			
			/*�̼���ʼ*/
			
			for(i=1;(i<=numberOfRows-1)&&(bStim_Quit !=1);i++ )
			{
				/* ��ȡ���� */
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (1, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (2, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (4, i) ,&train_interval_A );
				
				/* ���͵�ѹ */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = pStimPara[intensity_A-1].volt;		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
					
				/* ���β��� */
		
				// port0:line2----A·���
				// port0:line0----A·�ŵ� 
				// port0:line6----B·��� 
				// port0:line3----B·�ŵ�
				if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
				{
					MessagePopup ("ϵͳ����", "�����ڴ����");
					return -1;    
				}
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* ����ź����5��Ϊ�� */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
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
				
			
				//���һ�δ̼�
			
				/* ��ȡ���� */
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (1, numberOfRows) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (2, numberOfRows) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, numberOfRows) ,&train_time_A );
			//	GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_RPT_SQC,MakePoint (4, numberOfRows) ,&train_interval_A );
			
				//���͵�ѹ
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = pStimPara[intensity_A-1].volt;		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
					
				/* ���β��� */
		
				// port0:line2----A·���
				// port0:line0----A·�ŵ� 
				// port0:line6----B·��� 
				// port0:line3----B·�ŵ�
			
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
				{
					MessagePopup ("ϵͳ����", "�����ڴ����");
					return -1;    
				}
				
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* ����ź����5��Ϊ�� */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
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
		 else   //8����Ȧ  �̼���ʽ����
		 {
				    
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "�̼�ģʽ�뵱ǰ��Ȧ�����䣬�뷵�ص�ǰ��Ȧ����Ӧ�Ĵ̼�ģʽѡ���ѡ����ȷ�Ĵ̼�ģʽ..." );				 //��ʾ״̬	
			SendMsgToLog("�̼�ģʽ�뵱ǰ��Ȧ�����䣬�뷵�ص�ǰ��Ȧ����Ӧ�Ĵ̼�ģʽѡ���ѡ����ȷ�Ĵ̼�ģʽ...");                                               //��¼��־״̬
			return -1; 
				
		 }	
				
	}
	else if( nSelCoilNum == COIL_DBL_8 )
	{
				
		if( nSelStimNum == DBL8_SGL_STIM ) //˫8����Ȧ  ���δ̼�
		 {
				 	
					 
					 
		 }
		 else if( nSelStimNum == DBL8_RPT_STIM )  //˫8����Ȧ  �ظ��̼�
		 {
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle );
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_A,&bAState );
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_B,&bBState ); 
			if((bAState == 0)&&(bBState == 0))		  //AB ��û��ѡ��
			{
				return -1;	
			}
			else if((bAState == 1)&&(bBState == 0))   //ѡ����A
			{
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_INT, &intensity_A );
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_FQC, &frequency_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TT, &train_time_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TN, &train_num_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_A_DBL8_RPT_TITV, &train_interval_A ); 
				/* �Ϸ�����֤ */
				//�б�1-100
				//��ʱ��
				//�������
				//�¶�����
			
			
			
			
			
				/* ���͵�ѹ */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = (8.0)*((float64)intensity_A/100.0);		 
				volt[1] = 0.8;
				Send_Stim_Volt_Command( volt );
		
				/* ���β��� */
		
				// port0:line2----A·���
				// port0:line0----A·�ŵ� 
				// port0:line6----B·��� 
				// port0:line3----B·�ŵ�
			
				for( i=0;i<stim_cycle_A;i++ )
				{
					wave[stim_cycle_A*0+i] = 1;
					wave[stim_cycle_A*1+i] = 0;
					wave[stim_cycle_A*2+i] = 0;
					wave[stim_cycle_A*3+i] = 0;
				}
				/* ����ź����5��Ϊ�� */
				wave[stim_cycle_A*1-5] = 0;
				wave[stim_cycle_A*1-4] = 0;
				wave[stim_cycle_A*1-3] = 0;
				wave[stim_cycle_A*1-2] = 0;
				wave[stim_cycle_A*1-1] = 0;
				/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
				wave[stim_cycle_A*2-3] = 1;
				wave[stim_cycle_A*2-2] = 1;
		
				/* ���������� */
				ShowStimSlide( train_time_A*train_num_A+train_interval_A*(train_num_A-1) );
				/* ��ʼ�̼� */
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
			else if((bAState == 0)&&(bBState == 1))   //ѡ����B
			{
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_INT, &intensity_A );
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_FQC, &frequency_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TT, &train_time_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TN, &train_num_A ); 
				GetCtrlVal( TabPanelHandle,TAB_DBL_8_B_DBL8_RPT_TITV, &train_interval_A ); 
				/* �Ϸ�����֤ */
				//�б�1-100
				//��ʱ��
				//�������
				//�¶�����
			
			
			
			
			
				/* ���͵�ѹ */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);;
				volt[0] = 0.8;		 
				volt[1] = (8.0)*((float64)intensity_A/100.0);
				Send_Stim_Volt_Command( volt );
		
				/* ���β��� */
		
				// port0:line2----A·���
				// port0:line0----A·�ŵ� 
				// port0:line6----B·��� 
				// port0:line3----B·�ŵ�
			
				for( i=0;i<stim_cycle_A;i++ )
				{
					wave[stim_cycle_A*0+i] = 0;
					wave[stim_cycle_A*1+i] = 0;
					wave[stim_cycle_A*2+i] = 1;
					wave[stim_cycle_A*3+i] = 0;
				}
				/* ����ź����5��Ϊ�� */
				wave[stim_cycle_A*3-5] = 0;
				wave[stim_cycle_A*3-4] = 0;
				wave[stim_cycle_A*3-3] = 0;
				wave[stim_cycle_A*3-2] = 0;
				wave[stim_cycle_A*3-1] = 0;
				/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
				wave[stim_cycle_A*4-3] = 1;
				wave[stim_cycle_A*4-2] = 1;
		
				/* ���������� */
				ShowStimSlide( train_time_A*train_num_A+train_interval_A*(train_num_A-1) );
				/* ��ʼ�̼� */
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
			else									   //ͬʱѡ��AB
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
				/* �Ϸ�����֤ */
				//�б�1-100
				//��ʱ��
				//�������
				//�¶�����
			
			
			
			
			
				/* ���͵�ѹ */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);
				stim_cycle_B = (int)(1000.0/(float64)frequency_B);
				
				volt[0] = (8.0)*((float64)intensity_A/100.0); 		 
				volt[1] = (8.0)*((float64)intensity_B/100.0);
				
				Send_Stim_Volt_Command( volt );
				
				/* ���β��� */
		
				// port0:line2----A·���
				// port0:line0----A·�ŵ� 
				// port0:line6----B·��� 
				// port0:line3----B·�ŵ�
				
				Stim_Time_A = (train_time_A + train_interval_A)*(train_num_A-1)+train_time_A;	 // A �ܵĴ̼�ʱ��
				Stim_Time_B = (train_time_B + train_interval_B)*(train_num_B-1)+train_time_B;    // B �ܵĴ̼�ʱ�� 
			
				APlseNum = (int)(Stim_Time_A*1000);
				BPlseNum = (int)(Stim_Time_B*1000);
				
				/*	 
				Stim_Time_A = 12.999;
				APlseNum = (int)Stim_Time_A;
				FmtOut( "��������%f��������%d\n",Stim_Time_A,APlseNum );
				*/
				
				/*
				
				if( Stim_Time_A >= Stim_Time_B )    // A ��ʱ�䳤
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
				else	                //B��ʱ�䳤
				{
					
					
				}
				*/
			
			
			}			 
		 }
			
		 else if( nSelStimNum == DBL8_SQC_STIM )  //˫8����Ȧ  ���д̼�
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
			/* ���������� */
			
			ShowStimSlide( Stim_Time_A );
			
			
			/*�̼���ʼ*/
			
			for(i=1;(i<=numberOfRows-1)&&(bStim_Quit !=1);i++ )
			{
				/* ��ȡ���� */
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (1, i) ,coil ); 
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (2, i) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (3, i) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, i) ,&train_time_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (5, i) ,&train_interval_A );
				
				/* ���͵�ѹ */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);
				
				if(coil[0] == 'A')	               //�����A·
				{
					volt[0] = (8.0)*((float64)intensity_A/100.0);		 
					volt[1] = 0.8;
					/* ���β��� */
		
				// port0:line2----A·���
				// port0:line0----A·�ŵ� 
				// port0:line6----B·��� 
				// port0:line3----B·�ŵ�
			
					for( i=0;i<stim_cycle_A;i++ )
					{
						wave[stim_cycle_A*0+i] = 1;
						wave[stim_cycle_A*1+i] = 0;
						wave[stim_cycle_A*2+i] = 0;
						wave[stim_cycle_A*3+i] = 0;
					}
					/* A����ź����5��Ϊ�� */
					wave[stim_cycle_A*1-5] = 0;
					wave[stim_cycle_A*1-4] = 0;
					wave[stim_cycle_A*1-3] = 0;
					wave[stim_cycle_A*1-2] = 0;
					wave[stim_cycle_A*1-1] = 0;
					/* A�ŵ��źŵ����ڶ��͵���Ϊ�� */
					wave[stim_cycle_A*2-3] = 1;
					wave[stim_cycle_A*2-2] = 1;
					
				}
				else	                                          //�����B· 
				{
					volt[0] = 0.8; 
					volt[1] = (8.0)*((float64)intensity_A/100.0);		 
					
					/* ���β��� */
		
					// port0:line2----A·���
					// port0:line0----A·�ŵ� 
					// port0:line6----B·��� 
					// port0:line3----B·�ŵ�
			
					for( i=0;i<stim_cycle_A;i++ )
					{
						wave[stim_cycle_A*0+i] = 0;
						wave[stim_cycle_A*1+i] = 0;
						wave[stim_cycle_A*2+i] = 1;
						wave[stim_cycle_A*3+i] = 0;
					}
					/* B����ź����5��Ϊ�� */
					wave[stim_cycle_A*3-5] = 0;
					wave[stim_cycle_A*3-4] = 0;
					wave[stim_cycle_A*3-3] = 0;
					wave[stim_cycle_A*3-2] = 0;
					wave[stim_cycle_A*3-1] = 0;
					/* B�ŵ��źŵ����ڶ��͵���Ϊ�� */
					wave[stim_cycle_A*4-3] = 1;
					wave[stim_cycle_A*4-2] = 1;
					
				}
				
				Send_Stim_Volt_Command( volt );
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A + train_interval_A );
			}
				
			
				//���һ�δ̼�
			
				/* ��ȡ���� */
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (1, numberOfRows) ,coil ); 	
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (2, numberOfRows) ,&intensity_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (3, numberOfRows) ,&frequency_A );
				GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, numberOfRows) ,&train_time_A );
				
				/* ���͵�ѹ */
				stim_cycle_A = (int)(1000.0/(float64)frequency_A);
			
				if(coil[0] == 'A')               //A����Ȧ            
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
					/* A����ź����5��Ϊ�� */
					wave[stim_cycle_A*1-5] = 0;
					wave[stim_cycle_A*1-4] = 0;
					wave[stim_cycle_A*1-3] = 0;
					wave[stim_cycle_A*1-2] = 0;
					wave[stim_cycle_A*1-1] = 0;
					/* A�ŵ��źŵ����ڶ��͵���Ϊ�� */
					wave[stim_cycle_A*2-3] = 1;
					wave[stim_cycle_A*2-2] = 1;	
					
				}
				else							//B����Ȧ
				{
					volt[0] = 0.8;  
					volt[1] = (8.0)*((float64)intensity_A/100.0);
					/* ���β��� */
		
					// port0:line2----A·���
					// port0:line0----A·�ŵ� 
					// port0:line6----B·��� 
					// port0:line3----B·�ŵ�
			
					for( i=0;i<stim_cycle_A;i++ )
					{
						wave[stim_cycle_A*0+i] = 0;
						wave[stim_cycle_A*1+i] = 0;
						wave[stim_cycle_A*2+i] = 1;
						wave[stim_cycle_A*3+i] = 0;
					}
					/* B����ź����5��Ϊ�� */
					wave[stim_cycle_A*3-5] = 0;
					wave[stim_cycle_A*3-4] = 0;
					wave[stim_cycle_A*3-3] = 0;
					wave[stim_cycle_A*3-2] = 0;
					wave[stim_cycle_A*3-1] = 0;
					/* B�ŵ��źŵ����ڶ��͵���Ϊ�� */
					wave[stim_cycle_A*4-3] = 1;
					wave[stim_cycle_A*4-2] = 1;
					
				}
				
				Send_Stim_Volt_Command( volt );
				Send_CHRG_DisCHRG_Command( stim_cycle_A,train_time_A,frequency_A );
				Delay( train_time_A );	     
					 
					 
		 }
		 else  //˫8��Ȧ  �̼���ʽ����
		 {
  

			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "�̼�ģʽ�뵱ǰ��Ȧ�����䣬�뷵�ص�ǰ��Ȧ����Ӧ�Ĵ̼�ģʽѡ���ѡ����ȷ�Ĵ̼�ģʽ..." );				 //��ʾ״̬	
			SendMsgToLog("�̼�ģʽ�뵱ǰ��Ȧ�����䣬�뷵�ص�ǰ��Ȧ����Ӧ�Ĵ̼�ģʽѡ���ѡ����ȷ�Ĵ̼�ģʽ...");                                               //��¼��־״̬
			return -1; 
				
		 }
				
	}
	else if( nSelCoilNum == COIL_CC_4 )
	{
		if((nSelFcsNum > 7 )||(nSelFcsNum < 1 ))
		{
			 MessagePopup ("����ѡ��", "����ȷѡ�񽹵㣡");
			 return -1;
		}
		
		if( nSelStimNum == CC4_SGL_STIM )        //����Ȧ  ���δ̼�
		 {
			/* �̼��������� */
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_CC_4_CC4_SGL_INT, &intensity_A );
		
			/* ���͵�ѹ */
			stim_cycle_A = 1000;
			volt[0] = pStimPara[intensity_A-1].volt;		 
			volt[1] = 0.8;
			Send_Stim_Volt_Command( volt );
		
			/* ���β��� */
		
			// port0:line2----A·���
			// port0:line0----A·�ŵ� 
			// port0:line6----B·��� 
			// port0:line3----B·�ŵ�
			
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*4))==NULL)
			{
				MessagePopup ("ϵͳ����", "�����ڴ�ʧ�ܣ�");
				return -1;    
			}
		
				for( i=0;i<stim_cycle_A;i++ )
				{
					pWave[stim_cycle_A*0+i] = 1;
					pWave[stim_cycle_A*1+i] = 0;
					pWave[stim_cycle_A*2+i] = 0;
					pWave[stim_cycle_A*3+i] = 0;
				}
				/* ����ź����5��Ϊ�� */
				pWave[stim_cycle_A*1-5] = 0;
				pWave[stim_cycle_A*1-4] = 0;
				pWave[stim_cycle_A*1-3] = 0;
				pWave[stim_cycle_A*1-2] = 0;
				pWave[stim_cycle_A*1-1] = 0;
				/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
				pWave[stim_cycle_A*2-3] = 1;
				pWave[stim_cycle_A*2-2] = 1;
			
			
			/* ��ʼ�̼� */

			Send_CHRG_DisCHRG_Command( stim_cycle_A,1,1 );

			
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
		
					 
					 	 	
					 
					 
		 }
		 else if( nSelStimNum == CC4_RPT_STIM )  //����Ȧ  �ظ��̼�
		 {
				     
					 
					 
		 }
		 else if( nSelStimNum == CC4_SQC_STIM )  //����Ȧ  ���д̼� 
		 {
				    
		  	
					 
		 }
		 else    //����Ȧ  �̼���ʽ����
		 {
				    
//			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "�̼�ģʽ�뵱ǰ��Ȧ�����䣬�뷵�ص�ǰ��Ȧ����Ӧ�Ĵ̼�ģʽѡ���ѡ����ȷ�Ĵ̼�ģʽ..." );				 //��ʾ״̬	
			SendMsgToLog("�̼�ģʽ�뵱ǰ��Ȧ�����䣬�뷵�ص�ǰ��Ȧ����Ӧ�Ĵ̼�ģʽѡ���ѡ����ȷ�Ĵ̼�ģʽ...");                                               //��¼��־״̬
			return -1; 
				
		 }
				
	}
			

	if( pWave != NULL )     //��ֹ�ڴ�й¶
	{
		free(pWave);
		pWave = NULL;
		
	}
	
	return 0;
}
/* �첽ʱ�Ӵ����� */
int CVICALLBACK StimAsyncTimerCallback (int reserved, int theTimerId, int event,
                                 void *callbackData, int eventData1,int eventData2)
{                                                   
   
 //��ʱʱ�䵽
  
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
	
 //ȡ����ʱ  
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
	g_StimTimerId = NewAsyncTimer (((double)g_StimTimerDelay) / 1000.0, -1,1, StimAsyncTimerCallback, NULL);		   //�����첽ʱ��
	SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 );    //�̼���ɺ󣬽������ع���
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
		/* ������Ч����֤ */
		 if( Stim_Frequency > pStimPara[Stim_Power-1].frequency)
		 {
			MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		 	return -1;
		 }
		 
		 if(Stim_Frequency*Train_Duration <1 )
		 {
			MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
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
		/* �ӵ��� */
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
	
		/* ������Ч����֤ */
		 if( Stim_Frequency > pStimPara[Stim_Power-1].frequency)
		 {
			MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		 	return -1;
		 }
		 
		 if(Stim_Frequency*Train_Duration <1 )
		 {
			MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
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
		/* �ӵ��� */
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
	
		/* ������Ч����֤ */
		if( Stim_Frequency > pStimPara[Stim_Power-1].frequency)
		 {
			MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		 	return -1;
		 }
		 
		 if(Stim_Frequency*Train_Duration <1 )
		 {
			MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
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
		/* �ӵ��� */
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
//			MessagePopup ("", "Ĭ��");  
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
	
		/* ������Ч����֤ */
		 if( Stim_Frequency > pStimPara[Stim_Power-1].frequency)
		 {
			MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		 	return -1;
		 }
		 
		 if((int)(Stim_Frequency*Train_Duration) <1 )
		 {
			MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
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
		/* �ӵ��� */
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
