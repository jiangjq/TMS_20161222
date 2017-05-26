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
 

//���������.
int main (int argc, char *argv[])
{
    int error = 0;

    /* ��ʼ��CVI����ʱ���� */
    nullChk (InitCVIRTE (0, argv, 0));
	
	/* �����������Դ */ 
    errChk (panelHandle = LoadPanel (0, "TMS.uir", PANEL));
    
    /* ��ʾ����� */
    errChk (DisplayPanel (panelHandle));

	/* ϵͳ��ʼ�� */
	Sys_Init( );  

	/* �����û����� */
	errChk (RunUserInterface ( ));
	
Error:
    /* �����ڴ� */
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
		StimProgress_Exit( );  // ֹͣ�̼� 
		StatusDetect_Exit( );  // ֹͣ״̬���
		Free_Memory( );        // ��ֹ�ڴ�й¶
		QuitUserInterface (0); 
	}
    
	return 0;
}
void SetFullScreen( )
{
	SetPanelSize (panelHandle, 1080, 1920 );
	SetPanelPos (panelHandle, 0, 0);
}

/* ��ȡ������Ȧ�Ĵ̼����� */
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
	
	/* Բ����Ȧ �̼�������ȡ */
    strcpy(filename, "para\\StimPara_CC1.txt");
	MakePathname (projectDir, filename, fullPath); 

	if(( fp = fopen(fullPath,"r") ) != NULL )
	{
		pStimPara_CC1 = ( StimPara*)malloc(sizeof(StimPara)*100 );
	
		if ( pStimPara_CC1 == NULL )        
		{
			fclose( fp );
			free( pStimPara_CC1 );		
			return FALSE ;             
		}
		 
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%d %f %f ",&pStimPara_CC1[i].power,&pStimPara_CC1[i].volt,&pStimPara_CC1[i].frequency);
		}
	}
	else 
	{
		fclose(fp); 
		return FALSE; 
	}
	
	fclose(fp);

	/* ��8����Ȧ �̼�������ȡ */
    strcpy(filename, "para\\StimPara_SGL8.txt");
	MakePathname (projectDir, filename, fullPath); 
	
	if(( fp = fopen(fullPath,"r")) != NULL )
	{
		pStimPara_SGL8 = ( StimPara*)malloc(sizeof(StimPara)*100 );
		if ( pStimPara_SGL8 == NULL )        
		{
			fclose( fp );
			free( pStimPara_SGL8 );		
			return FALSE ;             
		}
		 
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%d %f %f ",&pStimPara_SGL8[i].power,&pStimPara_SGL8[i].volt,&pStimPara_SGL8[i].frequency);
		}
	}
	else
	{
		fclose(fp); 
		return FALSE; 	
	}
	
	fclose(fp);	

	/* ˫8����ȦA �̼�������ȡ */
    strcpy(filename, "para\\StimPara_DBL8_A.txt");
	MakePathname (projectDir, filename, fullPath); 

	if(( fp = fopen(fullPath,"r")) != NULL )
	{
		pStimPara_DBL8_A = ( StimPara*)malloc(sizeof(StimPara)*100 );
		if ( pStimPara_DBL8_A == NULL )        	
		{
			fclose( fp );
			free( pStimPara_DBL8_A );		
			return FALSE ;             
		}
		 
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%d %f %f ",&pStimPara_DBL8_A[i].power,&pStimPara_DBL8_A[i].volt,&pStimPara_DBL8_A[i].frequency);
		}
	}
	else
	{
		fclose(fp); 
		return FALSE; 	
	}
	fclose(fp);		

	/* ˫8����ȦB �̼�������ȡ */
    strcpy(filename, "para\\StimPara_DBL8_B.txt");
	MakePathname (projectDir, filename, fullPath); 

	if(( fp = fopen(fullPath,"r")) != NULL )
	{
		pStimPara_DBL8_B = ( StimPara*)malloc(sizeof(StimPara)*100 );
		if ( pStimPara_DBL8_A == NULL )        
		{
			fclose( fp );
			free( pStimPara_DBL8_B );		
			return FALSE ;             
		}
		 
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%d %f %f ",&pStimPara_DBL8_B[i].power,&pStimPara_DBL8_B[i].volt,&pStimPara_DBL8_B[i].frequency);
		}
	}
	else
	{
		fclose(fp); 
		return FALSE; 	
	}
	
	fclose(fp);
	
	/* ����Ȧ �̼�������ȡ */
    strcpy(filename, "para\\StimPara_CC4.txt");
	MakePathname (projectDir, filename, fullPath); 
	
	
	if(( fp = fopen(fullPath,"r")) != NULL )
	{
		pStimPara_CC4 = ( StimPara*)malloc(sizeof(StimPara)*100 );
		if ( pStimPara_CC4 == NULL )        
		{
			fclose( fp );
			free( pStimPara_CC4 );		
			return FALSE ;             
		}
		 
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%d %f %f ",&pStimPara_CC4[i].power,&pStimPara_CC4[i].volt,&pStimPara_CC4[i].frequency);
		}
	}
	else
	{
		fclose(fp); 
		return FALSE; 	
	}
	fclose(fp);

	return TRUE;
}
/* Ӳ����Ϣ�� */
int Authorize( )
{
	//TRUE --- ��ȷ
	//FALSE ---����ȷ
	
	return TRUE;	

}

void Focus_Sel(int n)														//����ѡ������  
{

	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle );

	if ( nSelFcsNum == n )  //������ظ�����������κβ���
	{
		SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_4_TBLR,ATTR_FRAME_COLOR,VAL_WHITE); 
		SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_TOP,ATTR_FRAME_COLOR,VAL_WHITE); 
		SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_LFT,ATTR_FRAME_COLOR,VAL_WHITE); 
		SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_BTM,ATTR_FRAME_COLOR,VAL_WHITE); 
		SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_1_RT,ATTR_FRAME_COLOR,VAL_WHITE); 
		SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_HZ,ATTR_FRAME_COLOR,VAL_WHITE); 
		SetCtrlAttribute(TabPanelHandle,TAB_CC_4_FCS_L_VTC,ATTR_FRAME_COLOR,VAL_WHITE); 
		nSelFcsNum = FCS_NO;
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

/* ϵͳ��ʼ�� */  
void Sys_Init( )                     												             		
{
	int thereIsAnother = 0;	
	
	SetWaitCursor ( TRUE );

	/* ��ʾ״̬ */
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "ϵͳ���ڳ�ʼ�������Ժ�..." );
	SendMsgToLog("ϵͳ���ڳ�ʼ�������Ժ�..."); 
	
	/* ��֤������Ƿ���Ȩ */
	if( Authorize( ) == FALSE )
	{
	    MessagePopup ("��ʼ������", "������û�еõ��Ϸ���Ȩ��\n��������Ȩ������ʹ�ñ������"); 
		exit( -1 ); 
	}
	
	/* ֻ������һ������ʵ�� */ 
	if ( CheckForDuplicateAppInstance (ACTIVATE_OTHER_INSTANCE, &thereIsAnother) < 0 )
		exit( -1 ); 
	if ( thereIsAnother == 1 )
	{
		MessagePopup ("��ʼ������", "�����Ѿ��������벻Ҫ�ٴ�������"); 
		exit( 0 );
	}
	
	/* ����ȫ�� */
	SetFullScreen( );
	
	/* ��ȡ��Ȧ�̼������ļ� */
	if( ReadStimPara( ) == FALSE)
	{
		SendMsgToLog("��Ȧ�̼�������ȡʧ�ܣ�����ѹر�...");
		MessagePopup ("��ʼ������", "��Ȧ�̼�������ȡʧ�ܣ���������˳���");
		exit( -1 );
	}
	
	/* ״̬������� */
	if( StatusDetect_Task( ) == FALSE )
	{
		MessagePopup ("��ʼ������", "״̬���������ʧ�ܣ���������˳���"); 
		exit( -1 ); 
	}
	
	// ��������ͼƬ
	if( DisplayImage( )== FALSE )
	{
		MessagePopup ("��ʼ������", "��ȡ�����Ŀ¼ʧ�ܣ�ͼƬ��ʾʧ��!"); 
	}

	//���������־
	gLowRateMeasureEnable  = FALSE;
	gHighRateMeasureEnable = FALSE; 
	
	
	//��Ȧ�ͽ���	
	nSelCoilNum = COIL_NO;   
	nSelFcsNum  = FCS_DISABLE;
	nSelStimNum = NO_SEL_STIM;
	
	//�̼���״ֹ̬ͣ��־
	bStim_Quit  	= FALSE;
	bStatus_Quit 	= FALSE; 
	
	/* ���õ�Դ����Ȧָʾ��Ĭ����ɫ��״̬*/
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_POWER, ATTR_ON_COLOR, VAL_RED );
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_POWER, ATTR_OFF_COLOR, VAL_GREEN ); 
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_COIL, ATTR_ON_COLOR, VAL_RED );
	SetCtrlAttribute ( panelHandle, PANEL_SYS_STATE_COIL, ATTR_OFF_COLOR, VAL_GREEN ); 
	SetCtrlVal ( panelHandle,PANEL_SYS_STATE_POWER , TRUE );
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "��Դ����" ); 
	SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , TRUE );
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE_COIL , "δ����Ȧ" ); 

	
	/* ��һ��ҳ�� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_SGL_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_SGL_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_1_CB_CC1_SGL_STIM , FALSE ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_RPT_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_RPT_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_1_CB_CC1_RPT_STIM , FALSE );  
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_SQC_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_1_CB_CC1_SQC_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_1_CB_CC1_SQC_STIM , FALSE );   

	/* �ڶ���ҳ�� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_SGL_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_SGL_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_SGL_8_CB_SGL8_SGL_STIM , FALSE );  
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_RPT_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_RPT_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_SGL_8_CB_SGL8_RPT_STIM , FALSE );  
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_SQC_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_SGL_8_CB_SGL8_SQC_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_SGL_8_CB_SGL8_SQC_STIM , FALSE ); 
	
	/* ������ҳ�� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_SGL_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_SGL_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_DBL_8_CB_DBL8_SGL_STIM , FALSE ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_RPT_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_RPT_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_STIM , FALSE ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_SQC_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_DBL_8_CB_DBL8_SQC_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_DBL_8_CB_DBL8_SQC_STIM , FALSE ); 
	
	/* ���ĸ�ҳ�� */
	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_SGL_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_SGL_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_4_CB_CC4_SGL_STIM , FALSE ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_RPT_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_RPT_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_4_CB_CC4_RPT_STIM , FALSE ); 
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_SQC_STIM, ATTR_ON_COLOR, VAL_DK_RED );
	SetCtrlAttribute ( TabPanelHandle, TAB_CC_4_CB_CC4_SQC_STIM, ATTR_OFF_COLOR, VAL_DK_GRAY ); 
	SetCtrlVal ( TabPanelHandle,TAB_CC_4_CB_CC4_SQC_STIM , FALSE );  
	

	/* �̼���ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );  
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE );  
	
	//�̵���ȡ������
	DisCharge( DISCHRGTIME );
	Send_FCS_SEL_Command( FCS_NO );
	
	/* ��ʾ״̬ */
	SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "ϵͳ��ʼ�����..." );
	SendMsgToLog("ϵͳ��ʼ�����..."); 
	
	SetWaitCursor ( FALSE ); 
	
}


/* ��ʾͼƬ */
int DisplayImage( )										   
{
	char *fileName;
	char projectDir[ MAX_PATHNAME_LEN ];
	char fullPath[ MAX_PATHNAME_LEN ];

	if (GetProjectDir (projectDir) < 0)
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��ȡ�����Ŀ¼ʧ�ܣ�ͼƬ��ʾʧ��!" );
			/* ��ʾ״̬ */
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��ȡ�����Ŀ¼ʧ�ܣ�ͼƬ��ʾʧ��!" );
		SendMsgToLog("��ȡ�����Ŀ¼ʧ�ܣ�ͼƬ��ʾʧ��!"); 
		return FALSE;
	}
	else
	
	{
		/* ��Ȧָʾ --- ����Ȧ */
		fileName = "Coil\\COIL_CC_1.png";  
		MakePathname (projectDir, fileName, fullPath);
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
	
	return TRUE; 

}

int StatusDetect_Task( )                                                                           //���ݲɼ�ʱ��
{
	int  status = 0;
	char szErrorMsg[1024];
	SendMsgToLog("����״̬���...");
	g_StatusTimerId = NewAsyncTimer (((double)g_StatusTimerDelay) / 1000.0, -1,1, StatusAsyncTimerCallback, NULL);		   //�����첽ʱ��

	if(g_StatusTimerId <=0 )
	{
		MessagePopup("�첽ʱ�Ӵ���", "�����첽ʱ�ӳ������ܽ���״̬��⣡");
        SendMsgToLog("�����첽ʱ�ӳ������ܽ���״̬��⣡");
		g_StatusTimerId = 0;
		return  FALSE;
	}
	else
	{
		status = CmtScheduleThreadPoolFunction ( DEFAULT_THREAD_POOL_HANDLE, StatusDetectThreadFunction, NULL, &gStatusDetectThreadFunctionId );   //���ݲɼ��߳� 
		if(status <0)
		{
		   CmtGetErrorMessage (status, szErrorMsg);
           MessagePopup ("״̬���ʧ��", "״̬����̴߳���ʧ�ܣ����ܽ���״̬��⣡");
		   SendMsgToLog("�����첽ʱ�ӳ������ܽ���״̬��⣡"); 
		   return  FALSE;
		}
	}
	
	return TRUE;
	
}

/* �첽ʱ�Ӵ����� */
int CVICALLBACK StatusAsyncTimerCallback (int reserved, int theTimerId, int event,
                                 void *callbackData, int eventData1,int eventData2)
{                                                   
   
 //��ʱʱ�䵽
    if (event == EVENT_TIMER_TICK)
	{
		gTimeCounter++;
	
		ShowSysTime();
		
		if ((gTimeCounter%3) == 0)  		//ÿ30ms����һ�� 
		{
			gHighRateMeasureEnable = 1;
		}
		if ((gTimeCounter%10) == 0)		    //ÿ100ms����һ��
		{
			gLowRateMeasureEnable  = 1;
			gTimeCounter = 0;			    //ÿ100ms����һ�£���ֹ���۹������
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
	while (bStatus_Quit == 0) 
	{
		if(gLowRateMeasureEnable == 1)          	//���ٲ������ȼ���
		{
			TmpAcq_Task(); 
			gLowRateMeasureEnable  = 0; 
		}
		else if(gHighRateMeasureEnable == 1)      	//���ٲ������ȼ���                                 
		{
			CoilDetect_Task( ); 
			PwrOk_Task();
//			SglDisOk_Task();
			gHighRateMeasureEnable = 0;
		}
	}
	gStatusDetectThreadFunctionId = 0;
	return 0;
}

void TmpAcq_Task( )
{
	int32       error=0;
	bool32      bComplete = TRUE;
	char        chan[256];
	float64     min = 0;
	float64     max =10; 
	float64     rate = 100000; //������100k
	float64		TempVal1 = 0;
	float64		TempVal2 = 0;
	uInt32      sampsPerChan = 100;
	int32       numRead;
	uInt32      numChannels = 1;
	char        errBuff[2048]={'\0'};
	uInt32      i  = 0 ;
	uInt32      j  = 0 ; 

	strcpy(chan,"Dev1/ai1");
	float64 data[100] = {0.0};

	DAQmxErrChk (DAQmxCreateTask("",&TempAcqtaskHandle));
	DAQmxErrChk (DAQmxCreateAIVoltageChan(TempAcqtaskHandle,chan,"",DAQmx_Val_Diff ,min,max,DAQmx_Val_Volts,NULL));
	DAQmxErrChk (DAQmxCfgSampClkTiming(TempAcqtaskHandle,"",rate,DAQmx_Val_Rising,DAQmx_Val_FiniteSamps,sampsPerChan));
	DAQmxErrChk (DAQmxReadAnalogF64(TempAcqtaskHandle,sampsPerChan,10.0,DAQmx_Val_GroupByChannel,data,sampsPerChan*numChannels,&numRead,NULL));
	DAQmxWaitUntilTaskDone (TempAcqtaskHandle, 10.0);

	if( numRead>0 )
	{
		
		/* ��ֵ�˲� */
		for(i=0;i<sampsPerChan;i++)
		{
			TempVal1 += data[i];
		}
		
		TempVal1 = TempVal1/sampsPerChan;
		
		TempVal1 = TempVal1*10;
		
		if( (nTempAcqNum >-1) && (nTempAcqNum <10) )
		{
			TempAcqArray[ nTempAcqNum ] = TempVal1;
			nTempAcqNum++;
			if(nTempAcqNum == 10)
			{
				TempVal1 = 0;
				for( i=0;i<10;i++ )
				{
					TempVal1 += TempAcqArray[i];
				}
				TempVal1 = TempVal1/10;
				
				for( i=0;i<10;i++ ) 
				{
					if( TempAcqArray[i] >= TempVal1 )
					{
						TempVal2 += TempAcqArray[i];
						j++;
					}
				}
				TempVal2 = TempVal2/j;
				SetCtrlVal ( panelHandle, PANEL_SYS_STATE_TEMP ,TempVal2 );
				/* �¶��ж� */
				if((TempVal2 >= 50))
				{
					SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "�¶�̫�ߣ�����50�ȣ������Ժ��ٽ��д̼�..." );
					SendMsgToLog("�¶�̫�ߣ�����50�ȣ������Ժ��ٽ��д̼�..."); 
				//	StimProgress_Exit( );
				}
				nTempAcqNum = 0; 	
			}
		}
		else
		{
			 nTempAcqNum = 0; 
		}
		
	}
	
	 
Error:

	if( DAQmxFailed(error) )
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048); 
	 	SendMsgToLog("�¶ȼ���������..."); 
		SendMsgToLog( errBuff );  
	} 	
	
	DAQmxStopTask(TempAcqtaskHandle); 
	DAQmxClearTask(TempAcqtaskHandle);
	TempAcqtaskHandle = 0;

	
}



void SglDisOk_Task( )
{
	int32       error=0;
	uInt8       data[1];
	char		errBuff[2048]={'\0'};
	int32		read,bytesPerSamp;
	
	DAQmxErrChk (DAQmxCreateTask("",&SglDisOktaskHandle));
	DAQmxErrChk (DAQmxCreateDIChan(SglDisOktaskHandle,"Dev1/port0/line5","",DAQmx_Val_ChanForAllLines));
	DAQmxErrChk (DAQmxReadDigitalLines(SglDisOktaskHandle,1,10.0,DAQmx_Val_GroupByChannel,data,1,&read,&bytesPerSamp,NULL));
	
	if( data[0]== 1 )
	{
		/* �˴���ӵ��δ̼����� */
		
		
	}
	

Error:

	if( DAQmxFailed(error) )
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		SendMsgToLog("���δ̼��������...");	
		SendMsgToLog( errBuff ); 
	}
	
	DAQmxStopTask(SglDisOktaskHandle);
	DAQmxClearTask(SglDisOktaskHandle);
	SglDisOktaskHandle = 0;	
	
}


void PwrOk_Task( )
{
	
	int32       error=0;
	uInt8       data[1];
	char		errBuff[2048]={'\0'};
	int32		read,bytesPerSamp;

	DAQmxErrChk (DAQmxCreateTask("",&PwrOktaskHandle));
	DAQmxErrChk (DAQmxCreateDIChan(PwrOktaskHandle,"Dev1/port0/line1","",DAQmx_Val_ChanForAllLines));
	DAQmxErrChk (DAQmxReadDigitalLines(PwrOktaskHandle,1,10.0,DAQmx_Val_GroupByChannel,data,1,&read,&bytesPerSamp,NULL));
	
	if( data[0]== 1 )
	{
		 SetCtrlVal ( panelHandle,PANEL_SYS_STATE_POWER , TRUE);
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "��Դ����");    
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "ϵͳ��Դ���ϣ�" );	
		 SendMsgToLog("��Դ���ֹ���...");
//		 StimProgress_Exit( ); 
	}
	else
	{
		 SetCtrlVal ( panelHandle,PANEL_SYS_STATE_POWER , FALSE); 
		 SetCtrlVal ( panelHandle,PANEL_TXT_STATE_POWER , "��Դ����"); 
	}
Error:
	if( DAQmxFailed(error) )
	{	
		DAQmxGetExtendedErrorInfo(errBuff,2048); 
		SendMsgToLog("��Դ��������ʧ��..."); 
		SendMsgToLog( errBuff );
	}  
	DAQmxStopTask(PwrOktaskHandle);
	DAQmxClearTask(PwrOktaskHandle);
	PwrOktaskHandle = 0;
 
}


void CoilDetect_Task( ) 													
{
	int32       error=0;
	uInt8       data[3];
	char		errBuff[2048]={'\0'};
	int32		read,bytesPerSamp;

	DAQmxErrChk (DAQmxCreateTask("",&CoilDetecttaskHandle));
	DAQmxErrChk (DAQmxCreateDIChan(CoilDetecttaskHandle,"Dev1/port1/line4:6","",DAQmx_Val_ChanForAllLines));
	DAQmxErrChk (DAQmxReadDigitalLines(CoilDetecttaskHandle,1,10.0,DAQmx_Val_GroupByChannel,data,3,&read,&bytesPerSamp,NULL));
	
	/* ����ר��		*/  
	
	data[0] = 0;  	
	data[1] = 1;
	data[2] = 0;
	
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
 
	}
	
	
Error:

	if( DAQmxFailed(error) )
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048); 	
	    SendMsgToLog("��Ȧ��������ʧ��..."); 
		SendMsgToLog( errBuff ); 
		SetCtrlVal ( panelHandle,PANEL_SYS_STATE_COIL , TRUE);  
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_1,ATTR_FRAME_COLOR,VAL_WHITE); 	   
		SetCtrlAttribute(panelHandle,PANEL_COIL_SGL_8,ATTR_FRAME_COLOR,VAL_WHITE);       
		SetCtrlAttribute(panelHandle,PANEL_COIL_DBL_8,ATTR_FRAME_COLOR,VAL_WHITE); 	  
		SetCtrlAttribute(panelHandle,PANEL_COIL_CC_4,ATTR_FRAME_COLOR,VAL_WHITE); 
	}	
	
	DAQmxStopTask(CoilDetecttaskHandle);
	DAQmxClearTask(CoilDetecttaskHandle);
	CoilDetecttaskHandle = 0;
	

}

int CVICALLBACK Cmd_Start_Stim (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int status;		
	if(event == EVENT_LEFT_CLICK )
	{
		status = CmtScheduleThreadPoolFunction ( DEFAULT_THREAD_POOL_HANDLE, Stim_ThreadFunction, NULL, &gStim_ThreadFunctionId );   //�̼��߳�  
		if( status < 0 )
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "�̼��̴߳���ʧ�ܣ����δ̼���ֹͣ��" );	
		 	SendMsgToLog("�̼��̴߳���ʧ�ܣ����δ̼���ֹͣ��");	
			MessagePopup ("�̼�ʧ��", "�̼��̴߳���ʧ�ܣ����δ̼���ֹͣ��");
			return FALSE;
		}
	}

	return TRUE;
}
void DisCharge( double second )
{
	int         error=0;    
	char        errBuff[2048]={'\0'};
	int         i = 0;
	uInt8       data[1]={1};   		
	SetWaitCursor( TRUE );
	DAQmxErrChk (DAQmxCreateTask("",&gDisChargetaskHandle));
	DAQmxErrChk (DAQmxCreateDOChan(gDisChargetaskHandle,"Dev1/port0/line4","",DAQmx_Val_ChanPerLine));
	DAQmxErrChk (DAQmxWriteDigitalLines(gDisChargetaskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL));
	Delay(second );
	data[0]= 0;	
	DAQmxErrChk (DAQmxWriteDigitalLines(gDisChargetaskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL));  
	DAQmxStopTask(gDisChargetaskHandle);
	DAQmxClearTask( gDisChargetaskHandle );
	gDisChargetaskHandle = 0; 

Error:
   
	if( DAQmxFailed(error) ) 
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		
		if( gDisChargetaskHandle != 0 ) 
		{
			DAQmxStopTask(gDisChargetaskHandle);
			DAQmxClearTask(gDisChargetaskHandle);
			gDisChargetaskHandle = 0;
		}
		
		MessagePopup("DAQmx Error",errBuff);
	}
	SetWaitCursor( FALSE );	
}

int CVICALLBACK Fcs_4_Tblr (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_4_TLBR );
	//	DisCharge( 0.2 );
	//	Send_FCS_SEL_Command(FCS_4_TLBR);
	}
	
	return 0;
}

int CVICALLBACK Fcs_1_Top (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_1_TOP );
	//	DisCharge( 0.2 );
	//	Send_FCS_SEL_Command(FCS_1_TOP);
	}
	return 0;
}

int CVICALLBACK Fcs_1_Lft (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_1_LFT );
	//	DisCharge( 0.2 );
	//	Send_FCS_SEL_Command(FCS_1_LFT);
	}
	return 0;
}

int CVICALLBACK Fcs_1_Btm (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_1_BTM );
	//	DisCharge( 0.2 );
	//	Send_FCS_SEL_Command(FCS_1_BTM);
	}
	
	return 0;
}

int CVICALLBACK Fcs_1_Rt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_1_RT );
	//	DisCharge( 0.2 );
	//	Send_FCS_SEL_Command(FCS_1_RT);
	}
	
	return 0;
}

int CVICALLBACK Fcs_L_Hz (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_L_HZ );
	//	DisCharge( 0.2 );
	//	Send_FCS_SEL_Command(FCS_L_HZ);
	}
	return 0;
}

int CVICALLBACK Fcs_L_Vtc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	if( event == EVENT_LEFT_CLICK )
	{
		Focus_Sel( FCS_L_VTC );
	//	DisCharge( 0.2 );
	//	Send_FCS_SEL_Command(FCS_L_VTC);
	}
	
	return 0;
}

int CVICALLBACK Tab_Stim_Mode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	if( event == EVENT_ACTIVE_TAB_CHANGE  )
	{
		if( nSelCoilNum == -2 )
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��Ȧ�źų���" );				 	
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, eventData2, &TabPanelHandle); 
		}
		else if( nSelCoilNum == -1 )
		{
			SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "δ����Ȧ��" );				   	
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

	bStim_Quit = 1;                                                         //�̼�ֹͣ��־λ��Ϊ��Ч
	
	if(g_StimTimerId != 0)	                                                //�رս����� 
	{
		DiscardAsyncTimer ( g_StimTimerId );
		SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
	}

	if(gStim_ThreadFunctionId !=0)                                          //�رմ̼��߳�
	{
		CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE, gStim_ThreadFunctionId, 0);
        gStatusDetectThreadFunctionId = 0;
	}
	
	if( nSelCoilNum == COIL_CC_4 )										   //��������Ȧ����ָ��̵���û��ѡ�е�״̬
	{
	    DisCharge( DISCHRGTIME );
		Send_FCS_SEL_Command( FCS_NO );
	}
	
	bStim_Quit = 0;                                                        //���Լ����̼�  
	
	//��ť�ָ�
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 

}

/* ֹͣ��� */ 
void StatusDetect_Exit( )
{
	bStatus_Quit = 1;	                                                  //�趨ֹͣλ

	if( g_StatusTimerId != 0)                                             //ֹͣ��ʱ��
	{
		DiscardAsyncTimer( g_StatusTimerId );
		g_StatusTimerId = 0;
		SendMsgToLog("״̬��ⶨʱ���Ѿ��رգ�");
	}

 	if( gStatusDetectThreadFunctionId !=0 )								  //�ر�״̬����߳�
	{
		CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE, gStatusDetectThreadFunctionId, 0);
        gStatusDetectThreadFunctionId = 0;
	}

}


int CVICALLBACK Cmd_Exit_Sw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
 
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			
			StimProgress_Exit( );  // ֹͣ�̼� 
			StatusDetect_Exit( );  // ֹͣ״̬���
			Free_Memory( );        // ��ֹ�ڴ�й¶
			
			QuitUserInterface (0);   
			
			break;
	}
	return 0;
}


/* ��ֹ�ڴ�й¶ */ 
void Free_Memory( )
{
	if( pStimPara_CC1 != NULL )     
	{
		free(pStimPara_CC1);
		pStimPara_CC1 = NULL;
	}

	if( pStimPara_SGL8 != NULL )     
	{
		free(pStimPara_SGL8);
		pStimPara_SGL8 = NULL;
	}

	if( pStimPara_DBL8_A != NULL )     
	{
		free(pStimPara_DBL8_A);
		pStimPara_DBL8_A = NULL;
	}

	if( pStimPara_DBL8_B != NULL )     
	{
		free(pStimPara_DBL8_B);
		pStimPara_DBL8_B = NULL;
	}

	if( pStimPara_CC4 != NULL )     
	{
		free(pStimPara_CC4);
		pStimPara_CC4 = NULL;
	}

	if( pACircle != NULL )     
	{
		free(pACircle);
		pACircle = NULL;
	}

	if( pBCircle != NULL )     
	{
		free(pBCircle);
		pBCircle = NULL;
	}

	if( pWave != NULL )     
	{
		free(pWave);
		pWave = NULL;
	}
	
}

int CVICALLBACK Cmd_Reboot_Sys (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

		

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
				//�������ѡ��
				
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
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE );

				
				nSelStimNum = NO_SEL_STIM ;
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
				//�������ѡ��
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
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE );

			//	nSelStimNum = NO_SEL_STIM ;
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
	int bState ;
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
					MessagePopup ("��Ȧ����", "��Ȧ�������̼�ģʽѡ����Ч!");
					
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
	if(event == EVENT_LEFT_CLICK )
	{
		SetWaitCursor( TRUE ); 
		StimProgress_Exit( );
		SetWaitCursor( FALSE ); 
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
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
	/* ���ĸ�ҳ�� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
	SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE );

	nSelStimNum = NO_SEL_STIM ;
		
}


int CVICALLBACK Stim_ThreadFunction (void *functionData)
{
	/* �����Ϸ�����֤ */
	
	if( nSelCoilNum == COIL_FAIL )
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "��Ȧ���ϣ����δ̼���ֹͣ��" );	
		SendMsgToLog("��Ȧ���ϣ����δ̼���ֹͣ��");	
		MessagePopup ("�̼�ʧ��", "��Ȧ���ϣ����δ̼���ֹͣ��");
		return FALSE;
	}
		
	if( nSelCoilNum == COIL_NO )
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "û����Ȧ�����δ̼���ֹͣ��" );	
		SendMsgToLog("û����Ȧ�����δ̼���ֹͣ��");	
		MessagePopup ("�̼�ʧ��", "û����Ȧ�����δ̼���ֹͣ��");
		return FALSE;
		
	}
		
	if( nSelStimNum == NO_SEL_STIM )
	{
		SetCtrlVal ( panelHandle,PANEL_TXT_STATE , "û��ѡ��̼����ͣ����ܽ��д̼���" );	
		SendMsgToLog("û��ѡ��̼����ͣ����ܽ��д̼���");	
		MessagePopup ("�̼�ʧ��", "û��ѡ��̼����ͣ����ܽ��д̼���");
		return FALSE;
	}

	/* ��ֹ�ڴ�й¶ */
	if( pACircle != NULL )     
	{
		free(pACircle);
		pACircle = NULL;
	}
	
	/* ��ֹ�ڴ�й¶ */
	if( pBCircle != NULL )     
	{
		free(pBCircle);
		pBCircle = NULL;
	}
	
	/* ��ֹ�ڴ�й¶ */
	if( pWave != NULL )     
	{
		free(pWave);
		pWave = NULL;
	}
	
    /* Բ����Ȧ  */
	if( nSelCoilNum == COIL_CC_1 )			     
	{
	    if( nSelStimNum == CC1_SGL_STIM )	     		//Բ��--���δ̼�
		{
	 		Cc1_Sgl_Stim( ); 
		}
		else if( nSelStimNum == CC1_RPT_STIM )   		//Բ��--�ظ��̼�
		{
			Cc1_Rpt_Stim( ); 	
		}
		else if( nSelStimNum == CC1_SQC_STIM )   		//Բ��--���д̼�
		{
			Cc1_Sqc_Stim( ); 	
		}
		else								     		//Բ��--����
		{
			
		}
    }
	/* 8����Ȧ */
	else if( nSelCoilNum == COIL_SGL_8 )		  
	{
		if( nSelStimNum == SGL8_SGL_STIM )	     		//8��--���δ̼� 
		 {
			Sgl8_Sgl_Stim( );
		 }
		 else if( nSelStimNum == SGL8_RPT_STIM )   		//8��--�ظ��̼� 
		 {
			Sgl8_Rpt_Stim( );
		 }
		 else if( nSelStimNum == SGL8_SQC_STIM )   		//8��--���д̼�
		 {
			Sgl8_Sqc_Stim( ); 
		 }
		 else                                      		 //8��--����
		 {
			    

		 }	
				
	}
	/* ˫8����Ȧ */
	else if( nSelCoilNum == COIL_DBL_8 )		    
	{
				
		if( nSelStimNum == DBL8_SGL_STIM )          	//˫8��--���δ̼�
		 {
			Dbl8_Sgl_Stim( );
		 }
		 else if( nSelStimNum == DBL8_RPT_STIM )     	//˫8��--�ظ��̼�
		 {
			Dbl8_Rpt_Stim( );
		 }
		 else if( nSelStimNum == DBL8_SQC_STIM )     	//˫8��--���д̼�
		 {
			Dbl8_Sqc_Stim( );	
		 }
		 else                                         	//˫8��--����
		 {
  
		 }
				
	}
	/* ����Ȧ */
	else if( nSelCoilNum == COIL_CC_4 )			        
	{
		
		if( nSelStimNum == CC4_SGL_STIM )           	//����Ȧ--���δ̼�
		 {
			  Cc4_Sgl_Stim( );
		 }
		 else if( nSelStimNum == CC4_RPT_STIM )     	//����Ȧ--�ظ��̼�
		 {
			  Cc4_Rpt_Stim( );
		 }
		 else if( nSelStimNum == CC4_SQC_STIM )     	//����Ȧ--���д̼� 
		 {
			  Cc4_Sqc_Stim( ); 
		 }
		 else                                       	//����Ȧ---����
		 {

		 }
				
	}
	/* ��ֹ�ڴ�й¶ */
	if( pWave != NULL )     
	{
		free(pWave);
		pWave = NULL;
	}
 
	
	gStim_ThreadFunctionId = 0;
	
	return 0;
}

/* Բ����Ȧ�����δ̼� */
//����ֵ˵��
//0  �����̼���
//-1 �̼�ʧ�ܣ�

int Cc1_Sgl_Stim( )
{
	int       power = 0;
	int       stim_cycle = 0;
	int       i = 0;
 
	/* �̼��������� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
	GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_SGL_PWR, &power );
		

	/* �̼���ť�����ã�ֹͣ��ť���� */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,1 );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,0 ); 
	
	
	/* ���β��� */
	stim_cycle = (int)( 1000.0/pStimPara_CC1[power-1].frequency ); 
	
	if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4)) == NULL )
	{
		free( pWave );
		pWave = NULL;
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	memset(pWave,0,stim_cycle*4);

	for( i=0;i<stim_cycle-4;i++ )
	{
		pWave[i] = 1;	   
	}

	pWave[stim_cycle*2-2] = 1;
	pWave[stim_cycle*2-1] = 1;

	/* ���ʹ̼���ѹ */
	volt[0] = pStimPara_CC1[power-1].volt;		 
	volt[1] = 0.8;
	
	if( Send_Stim_Volt_Command( volt ) == FALSE )
	{
		MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
		SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		return FALSE; 
	}

	//����������
	ShowStimSlide( (double)stim_cycle / 1000.00 );  
	
	/* ���ʹ̼����� */  		
	if( Send_CHRG_DisCHRG_Command( stim_cycle,1,1 ) == FALSE )
	{
		 //�رս����� 
		if(g_StimTimerId != 0)	  
		{
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
		}
		MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
		SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE;
	}
	
	/* �ͷ��ڴ� */
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}

	/* �̼���ť���ã�ֹͣ��ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	

	return TRUE;

}

int Cc1_Rpt_Stim( )
{      
	int       power = 0;
	int       stim_cycle = 0;
	double    frequency = 0.0;
	double    train_time = 0.0;
	double    train_interval = 0.0;
	int       train_num = 0;
	int       i = 0;
	int       j = 0;
	int       k = 0;
	int       nByte = 0;
 
	/* �̼��������� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
	GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_PWR, &power );
	GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_FQC, &frequency ); 
	GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TT, &train_time ); 
	GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TN, &train_num ); 
	GetCtrlVal( TabPanelHandle,TAB_CC_1_CC1_RPT_TITV, &train_interval ); 
		
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE ); 
	/* ���ݺϷ�����֤ */

	//ÿ�������ٴ̼�һ��
	if((int)( frequency * train_time) < 1 )  
	{
		MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;  
	}
	//�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��		
	if(frequency >= pStimPara_CC1[power-1].frequency )   
	{
		MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;	
	}
	
	//������������ܳ���6000 
	if(( frequency * train_time * train_num ) >= 6000 )   
	{
		MessagePopup ("�̼�ʧ��", "�������������6000��");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;	
	}

	stim_cycle = (int)(1000.0/frequency); 
	nByte += stim_cycle * train_num * (int)(frequency * train_time );
	nByte += (int)(train_interval * 1000 ) * (train_num -1 );
	//���δ̼�����
	if((pACircle = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*2)) == NULL )
	{
		free( pACircle );
		pACircle = NULL;
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	//�����̼�����
	if((pWave = (uInt8 *)malloc( sizeof(uInt8) * nByte * 4)) == NULL )
	{
		free( pWave );
		pWave = NULL;
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	//�����ڴ����Ϊ0
	memset( pACircle, 0, stim_cycle*2 );
	memset( pWave, 0, nByte*4 ); 
  
	//����ź����ã����4λΪ0��
	for( i=0;i<stim_cycle-4;i++ )
	{
		pACircle[i] = 1;
	}
	//�ŵ��ź����ã����2λΪ1��  
	pACircle[stim_cycle*2-2] = 1;
	pACircle[stim_cycle*2-1] = 1;

	// �������ŵ��ź� 
	for(i=0;i<train_num;i++)	   //����
	{
		for(j=0;j<(int)(frequency * train_time);j++)   //ÿ�����еĴ̼��� 
		{
			for(k=0;k<stim_cycle;k++)						//	  ÿ�δ̼���������λ
			{
				 pWave[(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 j*stim_cycle+k] = pACircle[k];
				 pWave[nByte+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 j*stim_cycle+k] = pACircle[stim_cycle+k];
			}
		}
	}

	/* ���ʹ̼���ѹ */
	volt[0] = pStimPara_CC1[power-1].volt;		 
	volt[1] = 0.8;
	
	if( Send_Stim_Volt_Command( volt ) == FALSE )
	{
		MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
		SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		
		//�ͷ��ڴ�
		if(pACircle != NULL)
		{
			free(pACircle);
			pACircle = NULL;
		}
		
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		
		return FALSE; 
	}
	/* ���������� */  	
	ShowStimSlide( nByte/1000 );

	/* ���ʹ̼����� */  		
	if( Send_CHRG_DisCHRG_Command( nByte,1,1 ) == FALSE )
	{
		 //�رս����� 
		if(g_StimTimerId != 0)	  
		{
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
		}
		//�ͷ��ڴ�
		if(pACircle != NULL)
		{
			free(pACircle);
			pACircle = NULL;
		}
		
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
		SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE;
	}
	
	//�ͷ��ڴ�
	if(pACircle != NULL)
	{
		free(pACircle);
		pACircle = NULL;
	}
		
	//�ͷ��ڴ�
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}

	/* �̼���ť���ã�ֹͣ��ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	return TRUE;
	
}
int DelayTime( double second )  //��ʱ
{
	int nByte = 0;
	
	if(pWave!= NULL )
	{
		free( pWave );
		pWave = NULL; 
	}
	
	nByte = (int)(second*1000);

	if((pWave = (uInt8 *)malloc( sizeof(uInt8) * nByte * 4)) == NULL )
	{
		free( pWave );
		pWave = NULL;
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ���ʱʧ�ܣ�" );
		SendMsgToLog("�����ڴ�ʧ�ܣ���ʱʧ�ܣ�");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	//�����ڴ����Ϊ0
	memset( pWave, 0, nByte*4 );
	Send_CHRG_DisCHRG_Command( nByte,1,1 );

	if(pWave!= NULL )
	{
		free( pWave );
		pWave = NULL; 
	}
	
	return TRUE;

}
int Cc1_Sqc_Stim( )
{
	int       power = 0;
	int       stim_cycle = 0;
	double    frequency = 0.0;
	double    train_time = 0.0;
	double    train_interval = 0.0;
	int       train_num = 0;
	int       nPluse = 0;
	double    Stim_Time = 0;
	int       numberOfRows = 0;
	int       i = 0;
	int       j = 0;
    
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE); 
	
	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
	GetNumTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, &numberOfRows);
	if(numberOfRows <1)
	{
		MessagePopup ("�̼�ʧ��", "û������̼��������̼���ֹ");  
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE; 
	}
	//��֤������Ч��
	for(i=1;i<=numberOfRows;i++ )
	{
		/* ��ȡ���� */
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (1, i) ,&power );
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (2, i) ,&frequency );
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, i) ,&train_time );
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (4, i) ,&train_interval );
				
		//�̼�Ƶ�ʺʹ̼�ʱ��Ҫƥ��
		if( frequency * train_time<1 )  //ÿ�������ٴ̼�һ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;
		}
			
		if(frequency >= pStimPara_CC1[power-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
		nPluse += (int)( frequency*train_time );
	}
			
	if( nPluse > 6000 )   //������������ܳ���6000 
	{
		MessagePopup ("�̼�ʧ��", "�������������6000��");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;	
	}
			
	for(i=1;i<=numberOfRows;i++ )
	{
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, i) ,&train_time );
		Stim_Time += train_time;
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (4, i) ,&train_interval );
		if( i < numberOfRows )
		{
			Stim_Time += train_interval; 
		}
	}

	/* ���������� */
	ShowStimSlide( Stim_Time );
	
	for(i=1;i<=numberOfRows;i++ )
	{
		/* ��ȡ���� */
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (1, i) ,&power );
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (2, i) ,&frequency );
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (3, i) ,&train_time );
		GetTableCellVal (TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC,MakePoint (4, i) ,&train_interval );
		
		stim_cycle = (int)(1000.0/(float64)frequency);		
		
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4)) == NULL)
		{
			MessagePopup ("�̼�ʧ��", "�����ڴ����");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;    
		}
		
		memset(pWave,0,stim_cycle*4);
		
		for( j=0;j<stim_cycle-4;j++ )
		{
			pWave[j] = 1;
		}
		
		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
		
		/* ���͵�ѹ */
		volt[0] = pStimPara_CC1[power-1].volt;		 
		volt[1] = 0.8;
		
		if(Send_Stim_Volt_Command( volt ) == FALSE)
		{
			MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼���ֹ��");
			SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼���ֹ��"); 
			/* �̼���ť���ã�ֹͣ��ť������ */
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		
			//�ͷ��ڴ�
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
			return FALSE; 
		}
		
		if( Send_CHRG_DisCHRG_Command( stim_cycle,train_time,frequency ) == FALSE )
		{
			//�رս����� 
			if(g_StimTimerId != 0)	  
			{   
				DiscardAsyncTimer ( g_StimTimerId );
				SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
			}
	
			//�ͷ��ڴ�
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
			
			MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
			SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE;	
		}
	
		//ÿ������Ҫ�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		} 
	
		//��������һ�Σ����ٵȺ�
		if( i < numberOfRows )
		{
			DelayTime( train_interval );
		}
		
		//���ֹͣ�̼������˳�ѭ��
		if( bStim_Quit == 1 )
		{
			goto bQuit;
		}
	}
	
bQuit:

	//�ͷ��ڴ� 
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}
	
	/* �̼���ť���ã�ֹͣ��ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	
	return TRUE;	
	
}

int Sgl8_Sgl_Stim( )
{
	int       power = 0;
	int       stim_cycle = 0;
	int       i = 0;
 
	/* �̼��������� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
	GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_SGL_PWR, &power );
		
	/* �̼���ť�����ã�ֹͣ��ť���� */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,1 );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,0 ); 
	
	/* ���β��� */
	stim_cycle = (int)( 1000.0/pStimPara_SGL8[power-1].frequency ); 
	
	if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4)) == NULL )
	{
		free( pWave );
		pWave = NULL;
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	memset(pWave,0,stim_cycle*4);

	for( i=0;i<stim_cycle-4;i++ )
	{
		pWave[i] = 1;	   
	}

	pWave[stim_cycle*2-2] = 1;
	pWave[stim_cycle*2-1] = 1;

	/* ���ʹ̼���ѹ */
	volt[0] = pStimPara_SGL8[power-1].volt;		 
	volt[1] = 0.8;
	
	if( Send_Stim_Volt_Command( volt ) == FALSE )
	{
		MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
		SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		return FALSE; 
	}

	//����������
	ShowStimSlide( (double)stim_cycle / 1000.00 ); 
	
	/* ���ʹ̼����� */  		
	if( Send_CHRG_DisCHRG_Command( stim_cycle,1,1 ) == FALSE )
	{
		 //�رս����� 
		if(g_StimTimerId != 0)	  
		{
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
		}
		MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
		SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE;
	}
	
	/* �ͷ��ڴ� */
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}

	/* �̼���ť���ã�ֹͣ��ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	
	return TRUE;
}
int Sgl8_Rpt_Stim( )
{
	int       power = 0;
	int       stim_cycle = 0;
	double    frequency = 0.0;
	double    train_time = 0.0;
	double    train_interval = 0.0;
	int       train_num = 0;
	int       i = 0;
	int       j = 0;
	int       k = 0;
	int       nByte = 0;
 
	/* �̼��������� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
	GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_PWR, &power );
	GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_FQC, &frequency ); 
	GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TT, &train_time ); 
	GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TN, &train_num ); 
	GetCtrlVal( TabPanelHandle,TAB_SGL_8_SGL8_RPT_TITV, &train_interval ); 
		
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE ); 
	/* ���ݺϷ�����֤ */

	//ÿ�������ٴ̼�һ��
	if((int)( frequency * train_time) < 1 )  
	{
		MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;  
	}
	//�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��		
	if(frequency >= pStimPara_SGL8[power-1].frequency )   
	{
		MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;	
	}
	
	//������������ܳ���6000 
	if(( frequency * train_time * train_num ) >= 6000 )   
	{
		MessagePopup ("�̼�ʧ��", "�������������6000��");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;	
	}

	stim_cycle = (int)(1000.0/frequency); 
	nByte += stim_cycle * train_num * (int)(frequency * train_time );
	nByte += (int)(train_interval * 1000 ) * (train_num -1 );
	//���δ̼�����
	if((pACircle = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*2)) == NULL )
	{
		free( pACircle );
		pACircle = NULL;
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	//�����̼�����
	if((pWave = (uInt8 *)malloc( sizeof(uInt8) * nByte * 4)) == NULL )
	{
		free( pWave );
		pWave = NULL;
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	//�����ڴ����Ϊ0
	memset( pACircle, 0, stim_cycle*2 );
	memset( pWave, 0, nByte*4 ); 
  
	//����ź����ã����4λΪ0��
	for( i=0;i<stim_cycle-4;i++ )
	{
		pACircle[i] = 1;
	}
	//�ŵ��ź����ã����2λΪ1��  
	pACircle[stim_cycle*2-2] = 1;
	pACircle[stim_cycle*2-1] = 1;

	// �������ŵ��ź� 
	for(i=0;i<train_num;i++)	   //����
	{
		for(j=0;j<(int)(frequency * train_time);j++)   //ÿ�����еĴ̼��� 
		{
			for(k=0;k<stim_cycle;k++)						//	  ÿ�δ̼���������λ
			{
				 pWave[(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 j*stim_cycle+k] = pACircle[k];
				 pWave[nByte+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 j*stim_cycle+k] = pACircle[stim_cycle+k];
			}
		}
	}

	/* ���ʹ̼���ѹ */
	volt[0] = pStimPara_SGL8[power-1].volt;		 
	volt[1] = 0.8;
	
	if( Send_Stim_Volt_Command( volt ) == FALSE )
	{
		MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
		SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		
		//�ͷ��ڴ�
		if(pACircle != NULL)
		{
			free(pACircle);
			pACircle = NULL;
		}
		
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		
		return FALSE; 
	}
	/* ���������� */  	
	ShowStimSlide( nByte/1000 );

	/* ���ʹ̼����� */  		
	if( Send_CHRG_DisCHRG_Command( nByte,1,1 ) == FALSE )
	{
		 //�رս����� 
		if(g_StimTimerId != 0)	  
		{
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
		}
		//�ͷ��ڴ�
		if(pACircle != NULL)
		{
			free(pACircle);
			pACircle = NULL;
		}
		
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
		SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE;
	}
	
	//�ͷ��ڴ�
	if(pACircle != NULL)
	{
		free(pACircle);
		pACircle = NULL;
	}
		
	//�ͷ��ڴ�
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}

	/* �̼���ť���ã�ֹͣ��ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	return TRUE;
	
}
int Sgl8_Sqc_Stim( )
{

	int       power = 0;
	int       stim_cycle = 0;
	double    frequency = 0.0;
	double    train_time = 0.0;
	double    train_interval = 0.0;
	int       train_num = 0;
	int       nPluse = 0;
	double    Stim_Time = 0;
	int       numberOfRows = 0;
	int       i = 0;
	int       j = 0;
    
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE); 
	
	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_SGL_8, &TabPanelHandle);
	GetNumTableRows ( TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC, &numberOfRows);
	
	if(numberOfRows <1)
	{
		MessagePopup ("�̼�ʧ��", "û������̼��������̼���ֹ");  
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE; 
	}
	//��֤������Ч��
	for(i=1;i<=numberOfRows;i++ )
	{
		/* ��ȡ���� */
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (1, i) ,&power );
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (2, i) ,&frequency );
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, i) ,&train_time );
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (4, i) ,&train_interval );
				
		//�̼�Ƶ�ʺʹ̼�ʱ��Ҫƥ��
		if( frequency * train_time<1 )  //ÿ�������ٴ̼�һ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;
		}
			
		if(frequency >= pStimPara_SGL8[power-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
		nPluse += (int)( frequency*train_time );
	}
			
	if( nPluse > 6000 )   //������������ܳ���6000 
	{
		MessagePopup ("�̼�ʧ��", "�������������6000��");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;	
	}
			
	for(i=1;i<=numberOfRows;i++ )
	{
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, i) ,&train_time );
		Stim_Time += train_time;
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (4, i) ,&train_interval );
		if( i < numberOfRows )
		{
			Stim_Time += train_interval; 
		}
	}
	
	/* ���������� */
	ShowStimSlide( Stim_Time );
	
	for(i=1;i<=numberOfRows;i++ )
	{
		/* ��ȡ���� */
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (1, i) ,&power );
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (2, i) ,&frequency );
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (3, i) ,&train_time );
		GetTableCellVal (TabPanelHandle, TAB_SGL_8_TABLE_SGL8_SQC,MakePoint (4, i) ,&train_interval );
		
		stim_cycle = (int)(1000.0/(float64)frequency);		
		
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4)) == NULL)
		{
			MessagePopup ("�̼�ʧ��", "�����ڴ����");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;    
		}
		
		memset(pWave,0,stim_cycle*4);
		
		for( j=0;j<stim_cycle-4;j++ )
		{
			pWave[j] = 1;
		}
		
		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
		
		/* ���͵�ѹ */
		volt[0] = pStimPara_SGL8[power-1].volt;		 
		volt[1] = 0.8;
		
		if(Send_Stim_Volt_Command( volt ) == FALSE)
		{
			MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼���ֹ��");
			SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼���ֹ��"); 
			/* �̼���ť���ã�ֹͣ��ť������ */
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		
			//�ͷ��ڴ�
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
			return FALSE; 
		}
		
		if( Send_CHRG_DisCHRG_Command( stim_cycle,train_time,frequency ) == FALSE )
		{
			//�رս����� 
			if(g_StimTimerId != 0)	  
			{   
				DiscardAsyncTimer ( g_StimTimerId );
				SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
			}
	
			//�ͷ��ڴ�
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
			
			MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
			SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE;	
		}
	
		//ÿ������Ҫ�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		} 
	
		//��������һ�Σ����ٵȺ�
		if( i < numberOfRows )
		{
			DelayTime( train_interval );
		}
		
		//���ֹͣ�̼������˳�ѭ��
		if( bStim_Quit == 1 )
		{
			goto bQuit;
		}
	}
	
bQuit:

	//�ͷ��ڴ� 
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}
	
	/* �̼���ť���ã�ֹͣ��ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	
	return TRUE;		
	
}

/* ˫8����Ȧ���δ̼� */
int Dbl8_Sgl_Stim( )
{
    int       power_A = 0;
	int       power_B = 0;
	int       stim_cycle = 0;
	int       i = 0;
	int       state_A = -1;
	int       state_B = -1;
	
	//�̼���ť�����ã�ֹͣ��ť���� 
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE ); 
	//��ȡ��Ȧѡ��״̬
	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
   	GetCtrlVal(TabPanelHandle, TAB_DBL_8_CB_DBL8_SGL_A,&state_A ); 
	GetCtrlVal(TabPanelHandle, TAB_DBL_8_CB_DBL8_SGL_B,&state_B ); 
	//��ȡ�̼�ǿ��
	GetCtrlVal( TabPanelHandle,TAB_DBL_8_DBL8_SGL_PWR_A, &power_A );
	GetCtrlVal( TabPanelHandle,TAB_DBL_8_DBL8_SGL_PWR_B, &power_B );

	if((state_A == 0) && (state_B == 0))		         //��û��ѡ��
	{
		MessagePopup ("�̼�ʧ��", "����ȷѡ��̼���Ȧ!");
		SendMsgToLog("û��ѡ��̼���Ȧ���̼���ֹ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 
		return FALSE;
	}
	
    else if((state_A == 1) && (state_B == 0))			//ѡ����A
	{
		/* ���β��� */
		stim_cycle = (int)( 1000.0/pStimPara_DBL8_A[power_A-1].frequency ); 
	
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4)) == NULL )
		{
			
			free( pWave );
			pWave = NULL;
			MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
			/* �̼���ť���ã�ֹͣ��ť������ */
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
		memset(pWave,0,stim_cycle*4);
		
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[i] = 1;
		}
		
		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
		
		/* �̼���ѹ */
		volt[0] = pStimPara_DBL8_A[power_A-1].volt;		 
		volt[1] = 0.8;
	}
	else if((state_A == 0) && (state_B == 1))         //ѡ����B
	{
		/* ���β��� */
		stim_cycle = (int)( 1000.0/pStimPara_DBL8_B[power_B-1].frequency );
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4)) == NULL )
		{
			free( pWave );
			pWave = NULL;
			MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
			/* �̼���ť���ã�ֹͣ��ť������ */
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
	   	memset(pWave,0,stim_cycle*4);
		
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[stim_cycle*2+i] = 1;
		}
		
		pWave[stim_cycle*4-2] = 1;
		pWave[stim_cycle*4-1] = 1;
	
		/* �̼���ѹ */
		volt[0] = 0.8;		 
		volt[1] = pStimPara_DBL8_B[power_B-1].volt;
	
	}
	else if((state_A == 1) && (state_B == 1))         //ѡ����A��B 
	{
	   /* ���β��� */
		if( pStimPara_DBL8_A[power_A-1].frequency  >= pStimPara_DBL8_B[power_B-1].frequency )
		{
			stim_cycle = (int)( 1000.0/pStimPara_DBL8_B[power_B-1].frequency );   
		}
		else
		{
			stim_cycle = (int)( 1000.0/pStimPara_DBL8_A[power_A-1].frequency );  
		}
		
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4)) == NULL )
		{
			free( pWave );
			pWave = NULL;
			MessagePopup ( "�̼�����", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
			/* �̼���ť���ã�ֹͣ��ť������ */
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
		memset(pWave,0,stim_cycle*4); 
		
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[stim_cycle*0+i] = 1;	  //1--��
			pWave[stim_cycle*2+i] = 1;	  //2--��
		}

		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
		
		pWave[stim_cycle*4-2] = 1;
		pWave[stim_cycle*4-1] = 1;

		/* �̼���ѹ */
		volt[0] = pStimPara_DBL8_A[power_A-1].volt;		 
		volt[1] = pStimPara_DBL8_B[power_B-1].volt;
	
	}
	
	if( Send_Stim_Volt_Command( volt ) == FALSE )
	{
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
		SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}

	//����������
	ShowStimSlide( (double)stim_cycle / 1000.00 ); 
	
	/* ���ʹ̼����� */  		
	if( Send_CHRG_DisCHRG_Command( stim_cycle,1,1 ) == FALSE )
	{
		 //�رս����� 
		if(g_StimTimerId != 0)	  
		{
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
		}
		/* �ͷ��ڴ� */
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
		SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE;
	}
	
	/* �ͷ��ڴ� */
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}

	/* �̼���ť���ã�ֹͣ��ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	
	return TRUE;
}
int Dbl8_Rpt_Stim( )
{
	int       power_A = 0;
	int       power_B = 0;
	int       stim_cycle_A = 0;
	int       stim_cycle_B = 0;
	double    frequency_A = 0.0;
	double    frequency_B = 0.0; 
	double    train_time_A = 0.0;
	double    train_time_B = 0.0;  
	double    train_interval_A = 0.0;
	double    train_interval_B = 0.0; 
	int       train_num_A = 0;
	int       train_num_B = 0;
	int       nByte_A = 0;
	int       nByte_B = 0;
	int       nByte = 0;
	int       i = 0;
	int       j = 0;
	int       k = 0;
	int       state_A = -1;
	int       state_B = -1; 

	/* �̼���ť�����ã�ֹͣ��ť���� */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE ); 

	//��ȡ��Ȧѡ��״̬
	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
   	GetCtrlVal(TabPanelHandle, TAB_DBL_8_CB_DBL8_RPT_A,&state_A ); 
	GetCtrlVal(TabPanelHandle, TAB_DBL_8_CB_DBL8_RPT_B,&state_B ); 
	

	if((state_A == 0) && (state_B == 0))		         //��û��ѡ��
	{
		MessagePopup ("�̼�ʧ��", "����ȷѡ��̼���Ȧ��");
		SendMsgToLog("����ȷѡ��̼���Ȧ���̼�ֹͣ��");  
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 
		return FALSE;
	}
	
    else if((state_A == 1) && (state_B == 0))			//ѡ����A
	{
	   	GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_PWR_A,&power_A ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_FQC_A,&frequency_A ); 
	   	GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TN_A,&train_num_A ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TT_A,&train_time_A ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TITV_A,&train_interval_A ); 
		//ÿ�������ٴ̼�һ��
		if( frequency_A * train_time_A < 1 )  
		{
			MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
			SendMsgToLog("�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡�̼�ֹͣ��");  
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;  
		}
		//�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��	
		if(frequency_A > pStimPara_DBL8_A[power_A-1].frequency )   
		{
			MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
			SendMsgToLog("�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡�̼�ֹͣ��");  
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
		//������������ܳ���6000
		if(( frequency_A * train_time_A * train_num_A ) > 6000 )    
		{
			MessagePopup ("�̼�ʧ��", "�������������6000��");
			SendMsgToLog("�������������6000���̼�ֹͣ��"); 
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
		
		/* ���β��� */
	
		stim_cycle_A = (int)(1000.0/frequency_A); 
	
		nByte_A += stim_cycle_A * train_num_A * (int)(frequency_A * train_time_A );
		nByte_A += (int)(train_interval_A * 1000 ) * (train_num_A -1 );
		
		//���δ̼�����
		if((pACircle = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*2)) == NULL )
		{
			free( pACircle );
			pACircle = NULL;
			MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
		
		//�����̼�����
		if((pWave = (uInt8 *)malloc( sizeof(uInt8) * nByte_A * 4)) == NULL )
		{
			free( pWave );
			pWave = NULL;
			MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
		//�����ڴ����Ϊ0
		memset( pACircle, 0, stim_cycle_A*2 );
		memset( pWave, 0, nByte_A*4 ); 
  		nByte = nByte_A;
		//����ź����ã����4λΪ0��
		for( i=0;i<stim_cycle_A-4;i++ )
		{
			pACircle[i] = 1;
		}
		//�ŵ��ź����ã����2λΪ1��  
		pACircle[stim_cycle_A*2-2] = 1;
		pACircle[stim_cycle_A*2-1] = 1;

		// �������ŵ��ź� 
		for(i=0;i<train_num_A;i++)	   //����
		{
			for(j=0;j<(int)(frequency_A * train_time_A );j++)   //ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle_A;k++)						//	  ÿ�δ̼���������λ
				{
					 pWave[(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
						 j*stim_cycle_A+k] = pACircle[k];
					 pWave[nByte_A+(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
					 	j*stim_cycle_A+k] = pACircle[stim_cycle_A+k];
				}
			}
		}

		/* �̼���ѹ */
		volt[0] = pStimPara_DBL8_A[power_A-1].volt;		 
		volt[1] = 0.8;
		
	}
	else if((state_A == 0) && (state_B == 1))         //ѡ����B
	{
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_PWR_B,&power_B ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_FQC_B,&frequency_B ); 
	   	GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TN_B,&train_num_B ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TT_B,&train_time_B ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TITV_B,&train_interval_B ); 
		
		if( frequency_B * train_time_B < 1 )  //ÿ�������ٴ̼�һ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;  
		}
			
		if(frequency_B >= pStimPara_DBL8_B[power_B-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
		{
			MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
	
		if(( frequency_B * train_time_B * train_num_B ) > 6000 )   //������������ܳ���6000 
		{
			MessagePopup ("��������", "�������������6000��");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
		
		/* ���β��� */
	   	stim_cycle_B = (int)(1000.0/frequency_B); 
	
		nByte_B += stim_cycle_B * train_num_B * (int)(frequency_B * train_time_B );
		nByte_B += (int)(train_interval_B * 1000 ) * (train_num_B -1 );
		
		//���δ̼�����
		if((pBCircle = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_B*2)) == NULL )
		{
			free( pBCircle );
			pBCircle = NULL;
			MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
		
		//�����̼�����
		if((pWave = (uInt8 *)malloc( sizeof(uInt8) * nByte_B * 4)) == NULL )
		{
			free( pWave );
			pWave = NULL;
			MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
		//�����ڴ����Ϊ0
		memset( pBCircle, 0, stim_cycle_B*2 );
		memset( pWave, 0, nByte_B*4 ); 
  		nByte = nByte_B; 
		//����ź����ã����4λΪ0��
		for( i=0;i<stim_cycle_B-4;i++ )
		{
			pBCircle[i] = 1;
		}
		//�ŵ��ź����ã����2λΪ1��  
		pBCircle[stim_cycle_B*2-2] = 1;
		pBCircle[stim_cycle_B*2-1] = 1;

		// �������ŵ��ź� 
		for(i=0;i<train_num_B;i++)	   //����
		{
			for(j=0;j<(int)(frequency_B * train_time_B );j++)   //ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle_B;k++)						//	  ÿ�δ̼���������λ
				{
					 pWave[(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*i+
						 j*stim_cycle_B+k] = pBCircle[k];
					 pWave[nByte_B+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*i+
					 	j*stim_cycle_B+k] = pBCircle[stim_cycle_B+k];
				}
			}
		}

		/* �̼���ѹ */
		volt[0] = pStimPara_DBL8_B[power_B-1].volt;		 
		volt[1] = 0.8;

	}
	else if((state_A == 1) && (state_B == 1))                                                 //ѡ����A��B 
	{
		//��ȡ��ȦA����
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_PWR_A,&power_A ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_FQC_A,&frequency_A ); 
	   	GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TN_A,&train_num_A ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TT_A,&train_time_A ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TITV_A,&train_interval_A ); 
		//������֤
		if( frequency_A * train_time_A < 1 )  //ÿ�������ٴ̼�һ��
		{
			MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;  
		}
			
		if(frequency_A > pStimPara_DBL8_A[power_A-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
		{
			MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
			
			
		if(( frequency_A * train_time_A * train_num_A ) > 6000 )   //������������ܳ���6000 
		{
			MessagePopup ("��������", "�������������6000��");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
		
		//��ȡ��ȦB����
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_PWR_B,&power_B ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_FQC_B,&frequency_B ); 
	   	GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TN_B,&train_num_B ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TT_B,&train_time_B ); 
		GetCtrlVal(TabPanelHandle, TAB_DBL_8_DBL8_RPT_TITV_B,&train_interval_B ); 
		
		//������֤
		if( frequency_B * train_time_B < 1 )  //ÿ�������ٴ̼�һ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;  
		}
			
		if(frequency_B > pStimPara_DBL8_B[power_B-1].frequency )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
			
			
		if(( frequency_B * train_time_B * train_num_B ) > 6000 )   //������������ܳ���6000 
		{
			MessagePopup ("�̼�ʧ��", "�������������6000��");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
		
		stim_cycle_A = (int)(1000.0/frequency_A);
		stim_cycle_B = (int)(1000.0/frequency_B);
		
		nByte_A += stim_cycle_A * train_num_A * (int)(frequency_A * train_time_A);
		nByte_A += (int)(train_interval_A*1000) * (train_num_A -1 );
		
		nByte_B += stim_cycle_B * train_num_B * (int)(frequency_B * train_time_B);
		nByte_B += (int)(train_interval_B*1000) * (train_num_B -1 );
		
		if((pACircle = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_A*2)) == NULL )
		{
			MessagePopup ( "ϵͳ����", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
			/* �̼���ť���ã�ֹͣ��ť������ */
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
		memset( pACircle,0,stim_cycle_A*2 );
		for( i=0;i<stim_cycle_A-4;i++ )
		{
			pACircle[i] = 1;
		}
	
		/* �ŵ��źŵ�����1�͵�2Ϊ�� */
		pACircle[stim_cycle_A*2-2] = 1;
		pACircle[stim_cycle_A*2-1] = 1;
		
		if((pBCircle = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle_B*2)) == NULL )
		{
			MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
			SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
			/* �̼���ť���ã�ֹͣ��ť������ */
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE; 
		}
		memset( pBCircle,0,stim_cycle_B*2 );
	
		for( i=0;i<stim_cycle_B-4;i++ )
		{
			pBCircle[i] = 1;
		}
	
		/* �ŵ��źŵ�����1�͵�2Ϊ�� */
		pBCircle[stim_cycle_B*2-2] = 1;
		pBCircle[stim_cycle_B*2-1] = 1;
		
		if(nByte_A>=nByte_B)
		{
			nByte = nByte_A; 
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*nByte_A*4)) == NULL )
			{
				MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
				SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
				/* �̼���ť���ã�ֹͣ��ť������ */
				SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
				SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
				return FALSE; 
			}
			
			//A  ���ŵ��ź�	
			for(i=0;i<train_num_A-1;i++)	   //����
			{
				
				for(j=0;j<(int)(frequency_A * train_time_A);j++)   //ÿ�����еĴ̼��� 
				{
					for(k=0;k<stim_cycle_A;k++)						//	  ÿ�δ̼���������λ
					{
						 pWave[(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
							 j*stim_cycle_A+k] = pACircle[k];
						 pWave[nByte_A+(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
							 j*stim_cycle_A+k] = pACircle[stim_cycle_A+k];
					}
				}

				for(j=0;j<(int)(train_interval_A*1000);j++)
				{
					pWave[(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
						(stim_cycle_A*(int)(frequency_A * train_time_A))+j] = 0;  
					pWave[nByte_A+(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
						(stim_cycle_A*(int)(frequency_A * train_time_A))+j] = 0; 
				}
			}
			
			for(i=0;i<(int)(frequency_A * train_time_A);i++)
				{
					for(j=0;j<stim_cycle_A;j++)
					{
						 pWave[(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*(train_num_A-1)+
							 i*stim_cycle_A+j] = pACircle[j];
						 pWave[nByte_A+(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*(train_num_A-1)+
							 i*stim_cycle_A+j] = pACircle[stim_cycle_A+j];
					}
				}
			
			//B  ��硢�ŵ��ź�	
			for(i=0;i<train_num_B-1;i++)	   //����
			{
				
				for(j=0;j<(int)(frequency_B * train_time_B);j++)   //ÿ�����еĴ̼��� 
				{
					for(k=0;k<stim_cycle_B;k++)						//	  ÿ�δ̼���������λ
					{
						 pWave[nByte_A*2+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B * 1000))*i+
							 j*stim_cycle_B+k] = pBCircle[k];
						 pWave[nByte_A*3+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*i+
							 j*stim_cycle_B+k] = pBCircle[stim_cycle_B+k];
					}
				}

				for(j=0;j<(int)(train_interval_B*1000);j++)
				{
					pWave[nByte_A*2+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*i+
						(stim_cycle_B*(int)(frequency_B * train_time_B))+j] = 0;  
					pWave[nByte_A*3+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*i+
						(stim_cycle_B*(int)(frequency_B * train_time_B))+j] = 0; 
				}
			}
			
			for(i=0;i<(int)(frequency_B * train_time_B);i++)
				{
					for(j=0;j<stim_cycle_B;j++)
					{
						 pWave[nByte_A*2+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*(train_num_B-1)+
							 i*stim_cycle_B+j] = pBCircle[j];
						 pWave[nByte_A*3+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*(train_num_B-1)+
							 i*stim_cycle_B+j] = pBCircle[stim_cycle_B+j];
					}
				}
		
			for(i=nByte_B;i<nByte_A;i++)
			{
				pWave[nByte_A*2 + i] = 0;	
				pWave[nByte_A*3 + i] = 0;	 
			}
			
	
		}
		else
		{
			nByte = nByte_B; 
			if((pWave = (uInt8 *)malloc(sizeof(uInt8)*nByte_B*4)) == NULL )
			{
				MessagePopup ( "ϵͳ����", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
				SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
				/* �̼���ť���ã�ֹͣ��ť������ */
				SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
				SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
				return FALSE; 
			}
			
			//A  ���ŵ��ź�	
			for(i=0;i<train_num_A-1;i++)	   //����
			{
				
				for(j=0;j<(int)(frequency_A * train_time_A);j++)   //ÿ�����еĴ̼��� 
				{
					for(k=0;k<stim_cycle_A;k++)						//	  ÿ�δ̼���������λ
					{
						 pWave[(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
							 j*stim_cycle_A+k] = pACircle[k];
						 pWave[nByte_B+(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
							 j*stim_cycle_A+k] = pACircle[stim_cycle_A+k];
					}
				}

				for(j=0;j<(int)(train_interval_A*1000);j++)
				{
					pWave[(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
						(stim_cycle_A*(int)(frequency_A * train_time_A))+j] = 0;  
					pWave[nByte_B+(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*i+
						(stim_cycle_A*(int)(frequency_A * train_time_A))+j] = 0; 
				}
			}
			
			for(i=0;i<(int)(frequency_A * train_time_A);i++)
				{
					for(j=0;j<stim_cycle_A;j++)
					{
						 pWave[(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*(train_num_A-1)+
							 i*stim_cycle_A+j] = pACircle[j];
						 pWave[nByte_B+(stim_cycle_A*(int)(frequency_A * train_time_A)+(int)(train_interval_A*1000))*(train_num_A-1)+
							 i*stim_cycle_A+j] = pACircle[stim_cycle_A+j];
					}
				}
			
			for(i=nByte_A;i<nByte_B;i++)
			{
				pWave[nByte_B*0 + i] = 0;	
				pWave[nByte_B*1 + i] = 0;	 
			}
			
	
			//B  ��硢�ŵ��ź�	
			for(i=0;i<train_num_B-1;i++)	   //����
			{
				
				for(j=0;j<(int)(frequency_B * train_time_B);j++)   //ÿ�����еĴ̼��� 
				{
					for(k=0;k<stim_cycle_B;k++)						//	  ÿ�δ̼���������λ
					{
						 pWave[nByte_B*2+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B * 1000))*i+
							 j*stim_cycle_B+k] = pBCircle[k];
						 pWave[nByte_B*3+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*i+
							 j*stim_cycle_B+k] = pBCircle[stim_cycle_B+k];
					}
				}

				for(j=0;j<(int)(train_interval_B*1000);j++)
				{
					pWave[nByte_B*2+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*i+
						(stim_cycle_B*(int)(frequency_B * train_time_B))+j] = 0;  
					pWave[nByte_B*3+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*i+
						(stim_cycle_B*(int)(frequency_B * train_time_B))+j] = 0; 
				}
			}
			
			for(i=0;i<(int)(frequency_B * train_time_B);i++)
				{
					for(j=0;j<stim_cycle_B;j++)
					{
						 pWave[nByte_B*2+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*(train_num_B-1)+
							 i*stim_cycle_B+j] = pBCircle[j];
						 pWave[nByte_B*3+(stim_cycle_B*(int)(frequency_B * train_time_B)+(int)(train_interval_B*1000))*(train_num_B-1)+
							 i*stim_cycle_B+j] = pBCircle[stim_cycle_B+j];
					}
				}
		
	
		}
		
		volt[0] = pStimPara_DBL8_A[power_A-1].volt;		 
		volt[1] = pStimPara_DBL8_B[power_B-1].volt;
	}	
	
	/* ���ʹ̼����� */
	if( Send_Stim_Volt_Command( volt ) == FALSE )
	{
		MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
		SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		
		//�ͷ��ڴ�
		if(pACircle != NULL)
		{
			free(pACircle);
			pACircle = NULL;
		}
		//�ͷ��ڴ�
		if(pBCircle != NULL)
		{
			free(pBCircle);
			pBCircle = NULL;
		}
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		
		return FALSE; 
	}

	
	
	/* ���������� */  	
	ShowStimSlide( nByte/1000 );
	/* ���ʹ̼����� */  		
	if( Send_CHRG_DisCHRG_Command( nByte,1,1 ) == FALSE )
	{
		 //�رս����� 
		if(g_StimTimerId != 0)	  
		{
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
		}
		//�ͷ��ڴ�
		if(pACircle != NULL)
		{
			free(pACircle);
			pACircle = NULL;
		}
		//�ͷ��ڴ�
		if(pBCircle != NULL)
		{
			free(pBCircle);
			pBCircle = NULL;
		}
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}

		MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
		SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE;
	}
	
	//�ͷ��ڴ�
	if(pACircle != NULL)
	{
		free(pACircle);
		pACircle = NULL;
	}
	
	//�ͷ��ڴ�
	if(pBCircle != NULL)
	{
		free(pBCircle);
		pBCircle = NULL;
	}	
	//�ͷ��ڴ�
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}

	/* �̼���ť���ã�ֹͣ��ť������ */
	SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
	SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	return TRUE;
}

int Dbl8_Sqc_Stim( )
{
	int       power = 0;
	int       stim_cycle = 0;
	double    frequency = 0.0;
	double    train_time = 0.0;
	double    train_interval = 0.0;
	int       train_num = 0;
	int       nPluse = 0;
	double    Stim_Time = 0;
	int       bChrgState = 0; 
	int       bVoltState = 0;
	int       numberOfRows = 0;
	int       i = 0;
	int       j = 0;
	char      coil[2]; 
	

	//��ť���
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE); 
			
	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
	GetNumTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, &numberOfRows);
		
	if(numberOfRows <1)
	{
	    SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);
		return FALSE; 
	}
			
	//��֤������Ч��
	 for(i=1;i<=numberOfRows;i++ )
	{
		/* ��ȡ���� */
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (1, i) ,coil );   
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (2, i) ,&power );
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (3, i) ,&frequency );
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, i) ,&train_time );
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (5, i) ,&train_interval );
		
		
		if((coil[0]>'B')||(coil[0]<'A'))
		{
			MessagePopup ("�̼�ʧ��", "��Ȧѡ�����");
			SendMsgToLog("��Ȧѡ����󣡴̼���ֹ��");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;
		}
		//ǿ�Ⱥ�Ƶ��Ҫƥ��
		if( frequency * train_time < 1 )  //ÿ�������ٴ̼�һ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
			SendMsgToLog("�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡�̼���ֹ��"); 
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;
		}
			
		if((coil[0] = 'A')&&(frequency >= pStimPara_DBL8_A[power-1].frequency) ||(coil[0] = 'B')&&(frequency >= pStimPara_DBL8_B[power-1].frequency)  )   //�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
			SendMsgToLog("�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡�̼���ֹ��"); 
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return -1;	
		}
				
		nPluse += (int)( frequency*train_time );
	
	}
			
	if( nPluse > 6000 )   //������������ܳ���6000 
		
	{
		MessagePopup ("��������", "�������������6000��");
		SendMsgToLog("�������������6000���̼���ֹ��");            
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return -1;	
	}
	
	for(i=1;i<=numberOfRows;i++ )
	{
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, i) ,&train_time );
		Stim_Time += train_time;
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (5, i) ,&train_interval );
		if(i< numberOfRows)
		{
			Stim_Time += train_interval; 	
		}
	}

	/* ���������� */
	ShowStimSlide( Stim_Time );

	/*�̼���ʼ*/
	for( i=1; i <= numberOfRows; i++ )
	{
		/* ��ȡ���� */
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (1, i) ,coil ); 
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (2, i) ,&power );
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (3, i) ,&frequency );
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (4, i) ,&train_time );
		GetTableCellVal (TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC,MakePoint (5, i) ,&train_interval );
				
		stim_cycle = (int)(1000.0/(float64)frequency);  
		
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4))==NULL)
		{
			MessagePopup ("ϵͳ����", "�����ڴ����");
			SendMsgToLog("�����ڴ���󣡴̼���ֹ��"); 
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);
			return FALSE;    
		}
		memset(pWave,0,stim_cycle*4);
		
		if( coil[0] == 'A' )		 //��ȦA����
		{
			for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[j] = 1;
			}
		
			/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
			pWave[stim_cycle*2-2] = 1;
			pWave[stim_cycle*2-1] = 1;
			
			volt[0] = pStimPara_DBL8_A[power-1].volt;		 
			volt[1] = 0.8;

	 	}
		else if( coil[0] == 'B' )	   //��Ȧ B ���� 
		{
			 for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[stim_cycle*2+j] = 1;
			}

			/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
			pWave[stim_cycle*4-2] = 1;
			pWave[stim_cycle*4-1] = 1;
		
			volt[0] = 0.8;		 
			volt[1] = pStimPara_DBL8_B[power-1].volt;
	 	}

		/* ���ʹ̼���ѹ*/
		if( Send_Stim_Volt_Command( volt ) == FALSE )
		{
			MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
			SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			//�ͷ��ڴ�
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}
			return FALSE; 
		}
		
		/* ���ʹ̼����� */  		
		if( Send_CHRG_DisCHRG_Command( stim_cycle,train_time,frequency ) == FALSE )
		{
		 	//�رս����� 
			if(g_StimTimerId != 0)	  
			{
				DiscardAsyncTimer ( g_StimTimerId );
				SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
			}
	
			//�ͷ��ڴ�
			if(pWave != NULL)
			{
				free(pWave);
				pWave = NULL;
			}

			MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
			SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			return FALSE;
		}
		//�ͷ��ڴ�
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		//��������һ�Σ����ٵȺ�
		if( i < numberOfRows )
		{
			DelayTime( train_interval );
		}
		
		//���ֹͣ�̼������˳�ѭ��
		if( bStim_Quit == 1 )
		{   
			goto bQuit;
		}
	}
				
bQuit:	 

	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}

	//�ָ��̼���ť
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );    
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	   

	return 0;
}


int Cc4_Sgl_Stim( )
{
	int       power = 0;
	int       stim_cycle = 0;
	int       i = 0;

	if((nSelFcsNum > FCS_L_VTC )||(nSelFcsNum < FCS_4_TLBR ))
	{
		 MessagePopup ("�̼�ʧ��", "����ȷѡ�񽹵㣡");
		 SendMsgToLog("ѡ�񽹵���󣡴̼���ֹ��");  
		 return FALSE;
	}
	
	//��ť���
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE); 
	
	/* �̼��������� */
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
	GetCtrlVal( TabPanelHandle,TAB_CC_4_CC4_SGL_PWR, &power );
	
	stim_cycle = (int)( 1000.0/pStimPara_CC4[power-1].frequency );   

	if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4))==NULL)
	{
		MessagePopup ("�̼�ʧ��", "�����ڴ�ʧ�ܣ�");
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);
		return FALSE;    
	}
	
	memset( pWave,0,stim_cycle*4 );
	
	if( nSelFcsNum == FCS_4_TLBR )		 //���� A ���鶼����
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[stim_cycle*0+i] = 1;
			pWave[stim_cycle*2+i] = 1;
		}
		
		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
				
		pWave[stim_cycle*4-2] = 1;
		pWave[stim_cycle*4-1] = 1;
		
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = pStimPara_CC4[power-1].volt;
		
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1 )
			goto bQuit2;
		
		Send_FCS_SEL_Command(FCS_4_TLBR);
	 }
	 else if( nSelFcsNum == FCS_1_TOP )	   //���� B ��1�鵥������ 
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[i] = 1;
		}

		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
	
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = 0.8;
				
		DisCharge( DISCHRGTIME ); 
		if( bStim_Quit == 1 )
			goto bQuit2;
		
		Send_FCS_SEL_Command( FCS_1_TOP );
	}
	else if( nSelFcsNum == FCS_1_LFT )		 //���� C ��2�鵥������
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[stim_cycle*2+i] = 1;
		}
		/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
		pWave[stim_cycle*4-2] = 1;
		pWave[stim_cycle*4-1] = 1;
	
		volt[0] = 0.8;		 
		volt[1] = pStimPara_CC4[power-1].volt;
				
		DisCharge( DISCHRGTIME ); 
		if( bStim_Quit == 1 )
			goto bQuit2;
		
		Send_FCS_SEL_Command( FCS_1_LFT );
	 }
	else if( nSelFcsNum == FCS_1_BTM )		 //���� D ��2�鵥������
	 {
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[stim_cycle*2+i] = 1;
		}
		
		pWave[stim_cycle*4-2] = 1;
		pWave[stim_cycle*4-1] = 1;
				
		volt[0] = 0.8;		 
		volt[1] = pStimPara_CC4[power-1].volt;
				
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1 )
			goto bQuit2;
		
		Send_FCS_SEL_Command( FCS_1_BTM );
		
	 }
	else if( nSelFcsNum == FCS_1_RT )		 //���� E ��1�鵥������
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[i] = 1;
		}

		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
				
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = 0.8;
			
		DisCharge( DISCHRGTIME ); 
		if( bStim_Quit == 1 )
			goto bQuit2;
		
		Send_FCS_SEL_Command( FCS_1_RT );
	 }
	else if( nSelFcsNum == FCS_L_HZ )		 //���� F ����ͬʱ����
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[stim_cycle*0+i] = 1;
			pWave[stim_cycle*2+i] = 1;
		}

		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
				
		pWave[stim_cycle*4-2] = 1;
		pWave[stim_cycle*4-1] = 1;
		
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = pStimPara_CC4[power-1].volt;
		
		DisCharge( DISCHRGTIME ); 
		if( bStim_Quit == 1 )
			goto bQuit2;
		
		Send_FCS_SEL_Command( FCS_L_HZ );
	 }
	else if( nSelFcsNum == FCS_L_VTC )		 //���� G ����ͬʱ����
	 {
		for( i=0;i<stim_cycle-4;i++ )
		{
			pWave[stim_cycle*0+i] = 1;
			pWave[stim_cycle*2+i] = 1;
		}
	
		pWave[stim_cycle*2-2] = 1;
		pWave[stim_cycle*2-1] = 1;
		
		pWave[stim_cycle*4-2] = 1;
		pWave[stim_cycle*4-1] = 1;

		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = pStimPara_CC4[power-1].volt;	
		
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1 )
			goto bQuit2;
		
		Send_FCS_SEL_Command( FCS_L_VTC );
	 }
	
	//���ʹ̼���ѹ
	if( Send_Stim_Volt_Command( volt ) == FALSE )
	{
		MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
		SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		
		goto bQuit1; 
	}

	//����������
	ShowStimSlide( (double)stim_cycle / 1000.00 ); 
	
	//���ʹ̼�����  		
	if( Send_CHRG_DisCHRG_Command( stim_cycle,1,1 ) == FALSE )
	{
		 //�رս����� 
		if(g_StimTimerId != 0)	  
		{
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
		}
	
		MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
		SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
	}
	
bQuit1:
	DisCharge( DISCHRGTIME );
bQuit2: 	
	Send_FCS_SEL_Command( FCS_NO  );

	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}
	//�ָ��̼���ť
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );    
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE );    
	return TRUE;
}

int Cc4_Rpt_Stim( )
{
	int     i              = 0;
	int     j              = 0;
	int     k              = 0; 
	int     power          = 0;
	int     train_num      = 0;
	int     stim_cycle	   = 0;
	double  frequency      = 0;
	double  train_time     = 0;
	double  train_interval = 0;
	int     nByte          = 0;

	//����У��	
	if((nSelFcsNum > FCS_L_VTC )||(nSelFcsNum < FCS_4_TLBR ))
	{
		 MessagePopup ("�̼�ʧ��", "����ȷѡ�񽹵㣡");
		 SendMsgToLog("ѡ�񽹵���󣡴̼���ֹ��");  
		 return FALSE;
	}
	
	//��ť���
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE); 
			 
	//�̼�������ȡ
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
	GetCtrlVal( TabPanelHandle,TAB_CC_4_CC4_RPT_PWR, &power );
	GetCtrlVal( TabPanelHandle,TAB_CC_4_CC4_RPT_FQC, &frequency ); 
	GetCtrlVal( TabPanelHandle,TAB_CC_4_CC4_RPT_TT, &train_time ); 
	GetCtrlVal( TabPanelHandle,TAB_CC_4_CC4_RPT_TN, &train_num ); 
	GetCtrlVal( TabPanelHandle,TAB_CC_4_CC4_RPT_TITV, &train_interval ); 
		
	//�̼�Ƶ�ʺʹ�ʱ��Ҫƥ��
	//ÿ�������ٴ̼�һ��
	if(frequency * train_time < 1)  
	{
		MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
		SendMsgToLog("�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡�̼���ֹ��");  
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);
		return FALSE;
	}
	
	//�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��		
	if(frequency >= pStimPara_CC4[power-1].frequency )   
	{
		MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		SendMsgToLog("�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡�̼���ֹ��"); 
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);
		return FALSE;	
	}
	
	//������������ܳ���6000
	if((frequency*train_time*train_num) > 6000 )    
	{
		MessagePopup ("�̼�ʧ��", "�������������6000��");
		SendMsgToLog("�������������6000���̼���ֹ��"); 
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);
		return FALSE;	
	}

	stim_cycle = (int)(1000.0/frequency);
	nByte += stim_cycle * train_num * (int)( frequency * train_time );
	nByte += (int)( train_interval * 1000 ) * ( train_num -1 );		
	
	//���δ̼�����
	if((pACircle = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4)) == NULL )
	{
		free( pACircle );
		pACircle = NULL;
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	//�����̼�����
	if((pWave = (uInt8 *)malloc( sizeof(uInt8) * nByte * 4)) == NULL )
	{
		free( pWave );
		pWave = NULL;
		
		if( pACircle != NULL )
		{
			free(pACircle);
			pACircle == NULL;
		}
		
		MessagePopup ( "�̼�ʧ��", "�����ڴ�ʧ�ܣ��̼���ֹ��" );
		SendMsgToLog("�����ڴ�ʧ�ܣ��̼���ֹ��");
		
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		return FALSE; 
	}
	//�����ڴ����Ϊ0
	memset( pACircle, 0, stim_cycle*4 );
	memset( pWave, 0, nByte*4 ); 
	
	if( nSelFcsNum == FCS_4_TLBR )		 //���� A ���鶼����
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pACircle[stim_cycle*0+i] = 1;
			pACircle[stim_cycle*2+i] = 1;
		}
	
		pACircle[stim_cycle*2-2] = 1;
		pACircle[stim_cycle*2-1] = 1;
				
		pACircle[stim_cycle*4-2] = 1;
		pACircle[stim_cycle*4-1] = 1;
	
		// �������ŵ��ź� 
		for(i=0;i<train_num;i++)	   									//����
		{
			for(j=0;j<(int)(frequency * train_time);j++)   				//ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle;k++)								//ÿ�δ̼���������λ
				{
					 pWave[(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[k];
				 	pWave[nByte+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle+k];
					 pWave[nByte*2+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*2+k];
				 	pWave[nByte*3+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*3+k];
				}
			}
		}
	 
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = pStimPara_CC4[power-1].volt;
				
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1)
			goto  bQuit2;
		Send_FCS_SEL_Command( FCS_4_TLBR );
				
	 }
	else if( nSelFcsNum == FCS_1_TOP )	   //���� B ��1�鵥������ 
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pACircle[i] = 1;
		}
		
		pACircle[stim_cycle*2-2] = 1;
		pACircle[stim_cycle*2-1] = 1;

		// �������ŵ��ź� 
		for(i=0;i<train_num;i++)	  									//����
		{
			for(j=0;j<(int)(frequency * train_time);j++)   				//ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle;k++)								//ÿ�δ̼���������λ
				{
					 pWave[(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[k];
				 	pWave[nByte+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle+k];
					
				}
			}
		}
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = 0.8;
		
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1)
			goto  bQuit2;
		Send_FCS_SEL_Command( FCS_1_TOP );
			
	 }
	
	else if( nSelFcsNum == FCS_1_LFT )		 //���� C ��2�鵥������
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pACircle[stim_cycle*2+i] = 1;
		}
	
		pACircle[stim_cycle*4-2] = 1;
		pACircle[stim_cycle*4-1] = 1;
		
		// �������ŵ��ź� 
		for(i=0;i<train_num;i++)	   								//����
		{
			for(j=0;j<(int)(frequency * train_time);j++)   			//ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle;k++)							//ÿ�δ̼���������λ
				{
					pWave[nByte*2+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*2+k];
				 	pWave[nByte*3+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*3+k];
				}
			}
		}
				
		volt[0] = 0.8;		 
		volt[1] = pStimPara_CC4[power-1].volt;
				
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1)
			goto  bQuit2;
		Send_FCS_SEL_Command( FCS_1_LFT );
	 }
	else if( nSelFcsNum == FCS_1_BTM )		 //���� D ��2�鵥������
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pACircle[stim_cycle*2+i] = 1;
		}
	
		pACircle[stim_cycle*4-2] = 1;
		pACircle[stim_cycle*4-1] = 1;
		// �������ŵ��ź� 
		for(i=0;i<train_num;i++)	  								//����
		{
			for(j=0;j<(int)(frequency * train_time);j++)  	 		//ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle;k++)							//ÿ�δ̼���������λ
				{
					pWave[nByte*2+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*2+k];
				 	pWave[nByte*3+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*3+k];
				}
			}
		}
				
		volt[0] = 0.8;		 
		volt[1] = pStimPara_CC4[power-1].volt;
				
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1)
			goto  bQuit2;
		Send_FCS_SEL_Command( FCS_1_BTM );
				
	 }
	else if( nSelFcsNum == FCS_1_RT )		 //���� E ��1�鵥������
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pACircle[i] = 1;
		}
	
		pACircle[stim_cycle*2-2] = 1;
		pACircle[stim_cycle*2-1] = 1;

		// �������ŵ��ź� 
		for(i=0;i<train_num;i++)	   							//����
		{
			for(j=0;j<(int)(frequency * train_time);j++)   		//ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle;k++)						//ÿ�δ̼���������λ
				{
					 pWave[(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[k];
				 	pWave[nByte+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle+k];
					
				}
			}
		}
				
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = 0.8;
				
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1)
			goto  bQuit2;
		Send_FCS_SEL_Command( FCS_1_RT );
				
	}
	else if( nSelFcsNum == FCS_L_HZ )		 //���� F ����ͬʱ����
	{
		for( i=0;i<stim_cycle-4;i++ )
		{
			pACircle[stim_cycle*0+i] = 1;
			pACircle[stim_cycle*2+i] = 1;
		}
	
		pACircle[stim_cycle*2-2] = 1;
		pACircle[stim_cycle*2-1] = 1;
				
		pACircle[stim_cycle*4-2] = 1;
		pACircle[stim_cycle*4-1] = 1;
		// �������ŵ��ź� 
		for(i=0;i<train_num;i++)	   								//����
		{
			for(j=0;j<(int)(frequency * train_time);j++)   			//ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle;k++)							//ÿ�δ̼���������λ
				{
					 pWave[(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[k];
				 	pWave[nByte+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle+k];
					 pWave[nByte*2+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*2+k];
				 	pWave[nByte*3+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*3+k];
				}
			}
		}
				
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = pStimPara_CC4[power-1].volt;
				
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1)
			goto  bQuit2;
		Send_FCS_SEL_Command( FCS_L_HZ );
				
	}
	else if( nSelFcsNum == FCS_L_VTC )		 //���� G ����ͬʱ����
	 {
		for( i=0;i<stim_cycle-4;i++ )
		{
			pACircle[stim_cycle*0+i] = 1;
			pACircle[stim_cycle*2+i] = 1;
		}

		pACircle[stim_cycle*2-2] = 1;
		pACircle[stim_cycle*2-1] = 1;
				
		pACircle[stim_cycle*4-2] = 1;
		pACircle[stim_cycle*4-1] = 1;
		// �������ŵ��ź� 
		for(i=0;i<train_num;i++)	   							//����
		{
			for(j=0;j<(int)(frequency * train_time);j++)   		//ÿ�����еĴ̼��� 
			{
				for(k=0;k<stim_cycle;k++)						//ÿ�δ̼���������λ
				{
					 pWave[(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[k];
				 	pWave[nByte+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle+k];
					 pWave[nByte*2+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*2+k];
				 	pWave[nByte*3+(stim_cycle*(int)(frequency * train_time)+(int)(train_interval*1000))*i+
					 	j*stim_cycle+k] = pACircle[stim_cycle*3+k];
				}
			}
		}
				
		volt[0] = pStimPara_CC4[power-1].volt;		 
		volt[1] = pStimPara_CC4[power-1].volt;
				
		DisCharge( DISCHRGTIME );
		if( bStim_Quit == 1)
			goto  bQuit2;
		Send_FCS_SEL_Command( FCS_L_VTC );
	}
			
	if( Send_Stim_Volt_Command( volt ) == FALSE )
	{
		MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
		SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
		goto bQuit1;
	}
	/* ���������� */  	
	ShowStimSlide( nByte/1000 );

	/* ���ʹ̼����� */  		
	if( Send_CHRG_DisCHRG_Command( nByte,1,1 ) == FALSE )
	{
		 //�رս����� 
		if(g_StimTimerId != 0)	  
		{
			DiscardAsyncTimer ( g_StimTimerId );
			SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
		}
	
		MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
		SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
		SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
		SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	

	}
	
bQuit1:	
	DisCharge( DISCHRGTIME );
bQuit2:
	Send_FCS_SEL_Command( FCS_NO );
 
	if(pACircle != NULL)
	{
		free(pACircle);
		pACircle = NULL;
	}
	
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;
	}
	//�ָ��̼���ť
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );    
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	   

	return TRUE;
}

int Cc4_Sqc_Stim( )
{
	int       power = 0;
	int       stim_cycle = 0;
	double    frequency = 0.0;
	double    train_time = 0.0;
	double    train_interval = 0.0;
	int       train_num = 0;
	int       nPluse = 0;
	double    Stim_Time = 0;
	int       numberOfRows = 0;
	int       i = 0;
	int       j = 0;
	char      focus[2]; 
	

	//��ť���
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,TRUE);
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,FALSE); 
			
	GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle);
	GetNumTableRows ( TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC, &numberOfRows);
		
	if(numberOfRows <1)
	{
	    MessagePopup ("�̼�ʧ��", "û������̼�������"); 
		SendMsgToLog("û������̼��������̼���ֹ��");
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);
		return FALSE; 
	}
			
	//��֤������Ч��
	 for(i=1;i<= numberOfRows;i++ )
	{
		//��ȡ���� 
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (1, i) ,focus );   
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (2, i) ,&power );
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (3, i) ,&frequency );
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (4, i) ,&train_time );
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (5, i) ,&train_interval );
		
		//����У��
		if((focus[0]>'G')||(focus[0]<'A'))
		{
			MessagePopup ("�̼�ʧ��", "�������");
			SendMsgToLog("������󣡴̼���ֹ��");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;
		}
		
		//ǿ�Ⱥ�Ƶ��Ҫƥ��
		if( frequency * train_time < 1 )  //ÿ�������ٴ̼�һ��
		{
			MessagePopup ("�̼�ʧ��", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
			SendMsgToLog("�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡�̼���ֹ��");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;
		}
		
		//�̼�ǿ�Ⱥʹ̼�Ƶ��Ҫƥ��	
		if(frequency >= pStimPara_CC4[power-1].frequency )   
		{
			MessagePopup ("�̼�ʧ��", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
			SendMsgToLog("�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡�̼���ֹ��");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			return FALSE;	
		}
		nPluse += (int)( frequency*train_time );
	
	}
			
	 //������������ܳ���6000
	if( nPluse > 6000 )    
	{
		MessagePopup ("��������", "�������������6000��");
		SendMsgToLog("�������������6000���̼���ֹ��");  
		SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
		SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
		return FALSE;	
	}
	for(i=1;i<=numberOfRows;i++ )
	{
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (4, i) ,&train_time );
		Stim_Time += train_time;
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (5, i) ,&train_interval );
		if( i<numberOfRows )
		{
			Stim_Time += train_interval; 
		}
	}
			
	/* ���������� */
	ShowStimSlide( Stim_Time );

	/*�̼���ʼ*/
	for( i=1; i <= numberOfRows; i++ )
	{
		if( bStim_Quit == 1 )
		{
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE); 
			goto bQuit1;
		}
		//��ȡ����
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (1, i) ,focus ); 
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (2, i) ,&power );
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (3, i) ,&frequency );
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (4, i) ,&train_time );
		GetTableCellVal (TabPanelHandle, TAB_CC_4_TABLE_CC4_SQC,MakePoint (5, i) ,&train_interval );
				
		stim_cycle = (int)(1000.0/(float64)frequency);  
				
		if((pWave = (uInt8 *)malloc(sizeof(uInt8)*stim_cycle*4))==NULL)
		{
			MessagePopup ("ϵͳ����", "�����ڴ����");
			SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE);
			SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE);
			return FALSE;    
		}
		memset(pWave,0,stim_cycle*4);		
	
		if( focus[0] == 'A' )		 //���� A ���鶼����
		{
			for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[stim_cycle*0+j] = 1;
				pWave[stim_cycle*2+j] = 1;
			}
		
			pWave[stim_cycle*2-2] = 1;
			pWave[stim_cycle*2-1] = 1;
				
			pWave[stim_cycle*4-2] = 1;
			pWave[stim_cycle*4-1] = 1;
				
			volt[0] = pStimPara_CC4[power-1].volt;		 
			volt[1] = pStimPara_CC4[power-1].volt;
				
			DisCharge( DISCHRGTIME ) ;
			if(bStim_Quit == 1)	
				goto bQuit2; 		
			Send_FCS_SEL_Command( FCS_4_TLBR );

		}
		else if( focus[0] == 'B' )	   //���� B ��1�鵥������ 
		{
			for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[j] = 1;
			}

			/* �ŵ��źŵ����ڶ��͵���Ϊ�� */
			pWave[stim_cycle*2-2] = 1;
			pWave[stim_cycle*2-1] = 1;
		
			volt[0] = pStimPara_CC4[power-1].volt;		 
			volt[1] = 0.8;
			DisCharge( DISCHRGTIME ) ;
			if(bStim_Quit == 1)	
				goto bQuit2;				
			Send_FCS_SEL_Command( FCS_1_TOP );
		}
		else if( focus[0] == 'C' )		 //���� C ��2�鵥������
		{
			for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[stim_cycle*2+j] = 1;
			}
			
			pWave[stim_cycle*4-2] = 1;
			pWave[stim_cycle*4-1] = 1;
				
			volt[0] = 0.8;		 
			volt[1] = pStimPara_CC4[power-1].volt;
				
			DisCharge( DISCHRGTIME );
			if(bStim_Quit == 1)	
				goto bQuit2;				
			Send_FCS_SEL_Command( FCS_1_LFT );
		}
		else if( focus[0] == 'D' )		 //���� D ��2�鵥������
		{
			for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[stim_cycle*2+j] = 1;
			}
	
			pWave[stim_cycle*4-2] = 1;
			pWave[stim_cycle*4-1] = 1;
				
			volt[0] = 0.8;		 
			volt[1] = pStimPara_CC4[power-1].volt;
			
			DisCharge( DISCHRGTIME );
			if(bStim_Quit == 1)	
				goto bQuit2;
			Send_FCS_SEL_Command( FCS_1_BTM );
		}
		else if( focus[0] == 'E' )		 //���� E ��1�鵥������
		{
			 for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[stim_cycle*0+j] = 1;
			}

			pWave[stim_cycle*2-2] = 1;
			pWave[stim_cycle*2-1] = 1;
				
			volt[0] = pStimPara_CC4[power-1].volt;		 
			volt[1] = 0.8;
				
			DisCharge( DISCHRGTIME );
			if(bStim_Quit == 1)	
				goto bQuit2; 
			Send_FCS_SEL_Command( FCS_1_RT );
		}
			
		else if( focus[0] == 'F' )		 //���� F ����ͬʱ����
		{
			for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[stim_cycle*0+j] = 1;
				pWave[stim_cycle*2+j] = 1;
			}

			pWave[stim_cycle*2-2] = 1;
			pWave[stim_cycle*2-1] = 1;
				
			pWave[stim_cycle*4-2] = 1;
			pWave[stim_cycle*4-1] = 1;
				
			volt[0] = pStimPara_CC4[power-1].volt;		 
			volt[1] = pStimPara_CC4[power-1].volt;
				
			DisCharge( DISCHRGTIME );
			if(bStim_Quit == 1)	
				goto bQuit2;				
			Send_FCS_SEL_Command( FCS_L_HZ );
				
		}
		else if( focus[0] == 'G' )		 //���� G ����ͬʱ����
		{
		 	for( j=0;j<stim_cycle-4;j++ )
			{
				pWave[stim_cycle*0+j] = 1;
				pWave[stim_cycle*2+j] = 1;
			}

			pWave[stim_cycle*2-2] = 1;
			pWave[stim_cycle*2-1] = 1;
				
			pWave[stim_cycle*4-2] = 1;
			pWave[stim_cycle*4-1] = 1;
				
			volt[0] = pStimPara_CC4[power-1].volt;		 
			volt[1] = pStimPara_CC4[power-1].volt;
				
			DisCharge( DISCHRGTIME );
			if(bStim_Quit == 1)	
				goto bQuit2;				
			Send_FCS_SEL_Command( FCS_L_VTC );
				
		 }
		
		if( Send_Stim_Volt_Command( volt ) == FALSE )
		{
			MessagePopup ("�̼�ʧ��", "���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��");
			SendMsgToLog("���ʹ̼���ѹʧ�ܣ��̼�ֹͣ��"); 
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			goto bQuit2;
		}
		
		if( Send_CHRG_DisCHRG_Command( stim_cycle,train_time,frequency ) == FALSE )
		{
			 //�رս����� 
			if(g_StimTimerId != 0)	  
			{
				DiscardAsyncTimer ( g_StimTimerId );
				SetCtrlVal(panelHandle,PANEL_SYS_STATE_STIM,0 ); 
			}
			
			MessagePopup ("�̼�ʧ��", "���ʹ̼����δ��󣡴̼���ֹ��");
			SendMsgToLog("���ʹ̼����δ��󣡴̼���ֹ��");
			SetCtrlAttribute( panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );
			SetCtrlAttribute( panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	
			goto bQuit1; 
		}
	
		if(bStim_Quit == 1)	
			goto bQuit1;
		
		if(pWave != NULL)
		{
			free(pWave);
			pWave = NULL;
		}
		
		if( i<numberOfRows )
		{
			DelayTime( train_interval-0.2 );
		}
	}
	
bQuit1:			
	DisCharge( DISCHRGTIME );
bQuit2:	
	Send_FCS_SEL_Command( FCS_NO );
	
	if(pWave != NULL)
	{
		free(pWave);
		pWave = NULL;		  
	}
	
	//�ָ��̼���ť
	SetCtrlAttribute(panelHandle,PANEL_CMD_START_STIM,ATTR_DIMMED,FALSE );    
	SetCtrlAttribute(panelHandle,PANEL_CMD_STOP_STIM,ATTR_DIMMED,TRUE ); 	   

	return 0;
}


/* ʱ�Ӵ����� */
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
}


int Send_Stim_Volt_Command( float64 volt[] )
{
	int          error=0;
	float64      min = 0.8;
	float64      max = 8.0; 
	char         errBuff[2048]={'\0'};

	DAQmxErrChk (DAQmxCreateTask("",&gStimVolttaskHandle));
	DAQmxErrChk (DAQmxCreateAOVoltageChan(gStimVolttaskHandle,"Dev1/ao0:1","",min,max,DAQmx_Val_Volts,""));
	DAQmxErrChk (DAQmxWriteAnalogF64(gStimVolttaskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,volt,NULL,NULL));
	DAQmxWaitUntilTaskDone (gStimVolttaskHandle, 1.0);
	DAQmxStopTask(gStimVolttaskHandle);
	DAQmxClearTask(gStimVolttaskHandle);
	gStimVolttaskHandle = 0;

Error:
	if( DAQmxFailed(error) ) 
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		if( gStimVolttaskHandle != 0 ) 
		{
			DAQmxStopTask(gStimVolttaskHandle);
			DAQmxClearTask(gStimVolttaskHandle);
			gStimVolttaskHandle = 0;
		}
		MessagePopup("DAQmx Error",errBuff);   
		return FALSE; 
	}

	return TRUE;
}


int Send_CHRG_DisCHRG_Command( int stim_cycle,double stim_time,double stim_freq )
{
	int         error=0;
	char        errBuff[2048]={'\0'};
	int         bEnd = -1;
	uInt8       data0[4] = {0,0,0,0};
	TaskHandle	taskHandle = 0; 

	DAQmxErrChk (DAQmxCreateTask("",&gChrgDisChrgtaskHandle));
	DAQmxErrChk (DAQmxCreateDOChan(gChrgDisChrgtaskHandle,"Dev1/port0/line2,Dev1/port0/line0,Dev1/port0/line6,Dev1/port0/line3","",DAQmx_Val_ChanPerLine));
	DAQmxErrChk (DAQmxCfgSampClkTiming(gChrgDisChrgtaskHandle,"/Dev1/PFI12",1000,DAQmx_Val_Rising,DAQmx_Val_ContSamps,stim_cycle));
	DAQmxErrChk (DAQmxWriteDigitalLines(gChrgDisChrgtaskHandle,stim_cycle,1,10.0,DAQmx_Val_GroupByChannel,pWave,NULL,NULL));

	Send_Ctr0_Command(stim_cycle*((int)(stim_time*stim_freq))); 
	DAQmxGetTaskAttribute (gChrgDisChrgtaskHandle, DAQmx_Task_Complete, &bEnd );

	while((bStim_Quit == 0)&&(bEnd == 0))
	{
		DAQmxGetTaskAttribute (gChrgDisChrgtaskHandle, DAQmx_Task_Complete, &bEnd ); 
	}

	DAQmxClearTask(gChrgDisChrgtaskHandle);
	gChrgDisChrgtaskHandle = 0;
	
	/*�ѳ�ŵ�������Ϊ��Ч*/
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateDOChan(taskHandle,"Dev1/port0/line2,Dev1/port0/line0,Dev1/port0/line6,Dev1/port0/line3","",DAQmx_Val_ChanPerLine ));
	DAQmxErrChk (DAQmxStartTask(taskHandle));
	DAQmxErrChk (DAQmxWriteDigitalLines(taskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,data0,NULL,NULL));
	DAQmxErrChk(DAQmxStopTask(taskHandle));
	DAQmxErrChk(DAQmxClearTask(taskHandle));
	taskHandle = 0;

Error:
	if( DAQmxFailed(error) ) 
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		if( gChrgDisChrgtaskHandle != 0 ) 
		{
			DAQmxStopTask(gChrgDisChrgtaskHandle);
			DAQmxClearTask(gChrgDisChrgtaskHandle);
			gChrgDisChrgtaskHandle = 0;
		}
		if( taskHandle!=0 ) 
		{
			DAQmxStopTask(taskHandle);
			DAQmxClearTask(taskHandle);
		}
		MessagePopup("DAQmx Error",errBuff);
		return FALSE;  
	}
	
	return TRUE;
}

void Send_Ctr0_Command (int clock_num )
{
	int         error = 0;
	char        errBuff[2048] = {'\0'};
	int         bEnd  = -1;
	DAQmxErrChk (DAQmxCreateTask("",&gCtr0taskHandle));
	DAQmxErrChk (DAQmxCreateCOPulseChanFreq(gCtr0taskHandle,"Dev1/ctr0","",DAQmx_Val_Hz,DAQmx_Val_Low ,0.0,1000,0.5));
	DAQmxErrChk (DAQmxCfgImplicitTiming(gCtr0taskHandle,DAQmx_Val_FiniteSamps,clock_num));
	DAQmxErrChk (DAQmxStartTask(gCtr0taskHandle));
	DAQmxGetTaskAttribute (gCtr0taskHandle, DAQmx_Task_Complete, &bEnd );  

	while((bStim_Quit == 0)&&(bEnd == 0))
	{
		DAQmxGetTaskAttribute ( gCtr0taskHandle, DAQmx_Task_Complete, &bEnd );
	}
	
	DAQmxStopTask(gCtr0taskHandle);
	DAQmxClearTask( gCtr0taskHandle );
	gCtr0taskHandle = 0; 

	if(gChrgDisChrgtaskHandle != 0 )
	{
		DAQmxStopTask(gChrgDisChrgtaskHandle); 
	}
   
Error:
	if( DAQmxFailed(error) ) 
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		if( gCtr0taskHandle != 0 ) 
		{
			DAQmxStopTask(gCtr0taskHandle);
			DAQmxClearTask(gCtr0taskHandle);
			gCtr0taskHandle = 0;
		}
		if(gChrgDisChrgtaskHandle != 0 )
		{
			DAQmxStopTask(gChrgDisChrgtaskHandle); 
		}
		MessagePopup("DAQmx Error",errBuff);
	}
	
}


int CVICALLBACK Cmd_Cc1_Sqc_Stim_Add (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int    Stim_Power         = 0;
    double Stim_Frequency     = 0;
    double Train_Time     	  = 0;
    double Train_Interval     = 0;
	int    numberOfRows       = 0;
	int    rowIndex           = 0;
	
	if(event == EVENT_COMMIT )
	{
		GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_1, &TabPanelHandle);
		GetCtrlVal(TabPanelHandle, TAB_CC_1_CC1_SQC_PWR,&Stim_Power );
		GetCtrlVal(TabPanelHandle, TAB_CC_1_CC1_SQC_FQC,&Stim_Frequency );
		GetCtrlVal(TabPanelHandle, TAB_CC_1_CC1_SQC_TT,&Train_Time );
		GetCtrlVal(TabPanelHandle, TAB_CC_1_CC1_SQC_TITV,&Train_Interval );
		/* ������Ч����֤ */
		 if( Stim_Frequency > pStimPara_CC1[Stim_Power-1].frequency )
		 {
			MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		 	return FALSE;
		 }
		 
		 if( Stim_Frequency*Train_Time <1 )
		 {
			MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
		 	return FALSE;
		 }
		
		GetNumTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, &numberOfRows);
		InsertTableRows ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, -1, 1, VAL_CELL_NUMERIC );
		SetTableRowAttribute ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, numberOfRows+1, ATTR_LABEL_POINT_SIZE, 20 ); 
	
		SetTableCellVal ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, MakePoint (1, numberOfRows+1), Stim_Power);
    	SetTableCellVal ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, MakePoint (2, numberOfRows+1), Stim_Frequency);
    	SetTableCellVal ( TabPanelHandle, TAB_CC_1_TABLE_CC1_SQC, MakePoint (3, numberOfRows+1), Train_Time);
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
		 if( Stim_Frequency > pStimPara_SGL8[Stim_Power-1].frequency)
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
		if(coil[0] == 'A')
		{
			if( Stim_Frequency > pStimPara_DBL8_A[Stim_Power-1].frequency)
		 	{
				MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		 		return FALSE;
			 }
		}
		else if( coil[0] == 'B' )
		{
			if( Stim_Frequency > pStimPara_DBL8_B[Stim_Power-1].frequency)
		 	{
				MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		 		return FALSE;
			 }
		}
		else
		{
			MessagePopup ("��������", "��Ȧ��д����");
		 	return FALSE;	
		}
		
		if( Stim_Frequency*Train_Duration <1 )
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
			GetNumTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, &numberOfRows ); 
			if( numberOfRows>0 )
			{
			   DeleteTableRows ( TabPanelHandle, TAB_DBL_8_TABLE_DBL8_SQC, numberOfRows, 1 );     
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
			{
				 return 0; 
			}
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
      

	switch( nChnlNum )
	{
		case 0:
			data[3] = 1;
			data[2] = 0;
			data[1] = 0;
   			data[0] = 0; 
			
			break;  
			
		case 1:
			data[3] = 0;
			data[2] = 1;
			data[1] = 1;
   			data[0] = 1; 
			
			break;
		case 2:
			data[3] = 0;
			data[2] = 1;
			data[1] = 1;
   			data[0] = 0; 
 
			break;				
		case 3:
			data[3] = 0;
			data[2] = 1;
			data[1] = 0;
   			data[0] = 1;  
 
			break;			
		case 4:
			data[3] = 0;
			data[2] = 1;
			data[1] = 0;
   			data[0] = 0; 
 
			break;
		case 5:
			data[3] = 0;
			data[2] = 0;
			data[1] = 1;
   			data[0] = 1; 

			break;
		case 6:
			data[3] = 0;
			data[2] = 0;
			data[1] = 1;
   			data[0] = 0;  

			break;
		case 7:
			data[3] = 0;
			data[2] = 0;
			data[1] = 0;
   			data[0] = 1;  
 
			break;			
		
		
		default:
			data[3] = 1;
			data[2] = 0;
			data[1] = 0;
   			data[0] = 0; 

			break;

	}
		DAQmxErrChk (DAQmxCreateTask("",&gFcsSeltaskHandle));
		DAQmxErrChk (DAQmxCreateDOChan(gFcsSeltaskHandle,"Dev1/port1/line0:3","",DAQmx_Val_ChanForAllLines));
		DAQmxErrChk (DAQmxStartTask(gFcsSeltaskHandle));
		DAQmxErrChk (DAQmxWriteDigitalLines(gFcsSeltaskHandle,1,1,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL));

Error:

	if( DAQmxFailed(error) )
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048); 
		MessagePopup("DAQmx Error",errBuff); 
	}

	if( gFcsSeltaskHandle!=0 ) 
	{
		DAQmxStopTask(gFcsSeltaskHandle);
		DAQmxClearTask(gFcsSeltaskHandle);
		gFcsSeltaskHandle = 0;
	}
}

int CVICALLBACK Cc4_Sqc_Fcs (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char fcs[2];
	
	switch (event)
	{
		case EVENT_LOST_FOCUS:
			GetPanelHandleFromTabPage ( panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle );
			GetCtrlVal( TabPanelHandle, TAB_CC_4_CC4_SQC_FCS,fcs ); 
		
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
		if( fcs[0] < 'A'||fcs[0] > 'G')
		 {
			MessagePopup ("��������", "���㽹��ѡ�����");
		 	return FALSE;
		 } 
		
		if( Stim_Frequency > pStimPara_CC4[Stim_Power-1].frequency)
		 {
			MessagePopup ("��������", "�̼�ǿ�Ⱥʹ̼�Ƶ�ʲ�ƥ�䣡");
		 	return FALSE;
		 }
		 
		 if((int)(Stim_Frequency*Train_Duration) <1 )
		 {
			MessagePopup ("��������", "�̼�Ƶ�ʺʹ�ʱ�䲻ƥ�䣡");
		 	return FALSE;
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

void ShowSysTime()
{
	int year,month,day,hour,mimute,second;
	char systime[100];
	GetSystemDate (&month,&day ,&year );
	GetSystemTime ( &hour, &mimute ,&second ); 
	sprintf(systime,"%4d-%02d-%02d %02d:%02d:%02d  ",year,month,day,hour,mimute,second );
	SetCtrlVal(panelHandle,PANEL_TXT_SYS_TIME,systime);
}

int CVICALLBACK Cmd_ShutDown_Sys (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    
	if(event == EVENT_LEFT_CLICK )
	{
	    
	} 
	
	return 0;
}

int CVICALLBACK Cb_Dbl8_Sgl_A (int panel, int control, int event,
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
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SGL_A, &bState );
			if ( bState == TRUE )
			{
				//�������ѡ��
				
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
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_STIM, TRUE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE );

				
				nSelStimNum = DBL8_SGL_STIM ;
				
			}
			else
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
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_STIM, TRUE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE ); 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Dbl8_Sgl_B (int panel, int control, int event,
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
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_SGL_B, &bState );
			if ( bState == TRUE )
			{
				//�������ѡ��
				
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
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_STIM, TRUE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE );

				
				nSelStimNum = DBL8_SGL_STIM ;
				
			}
			else
			{
			//�������ѡ��
				
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
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_STIM, TRUE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE ); 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Dbl8_Rpt_A (int panel, int control, int event,
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
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_A, &bState );
			if ( bState == TRUE )
			{
				//�������ѡ��
				
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
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, TRUE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE );

				
				nSelStimNum = DBL8_RPT_STIM ;
				
			}
			else
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
		   //	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE ); 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Dbl8_Rpt_B (int panel, int control, int event,
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
				
				return FALSE;
			}
			
			GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_DBL_8, &TabPanelHandle);
			GetCtrlVal( TabPanelHandle,TAB_DBL_8_CB_DBL8_RPT_B, &bState );
			if ( bState == TRUE )
			{
				//�������ѡ��
				
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
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, TRUE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE );

				
				nSelStimNum = DBL8_RPT_STIM ;
				
			}
			else
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
		   //	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SQC_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_A, FALSE ); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_SGL_B, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_A, FALSE ); 
			//	SetCtrlVal( TabPanelHandle_Temp,TAB_DBL_8_CB_DBL8_RPT_B, FALSE ); 
				
				/* ���ĸ�ҳ�� */
				GetPanelHandleFromTabPage (panelHandle, PANEL_TAB_STIM_MODE, PAGE_CC_4, &TabPanelHandle_Temp); 
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SGL_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_RPT_STIM, FALSE );
				SetCtrlVal( TabPanelHandle_Temp,TAB_CC_4_CB_CC4_SQC_STIM, FALSE ); 
			}
	//		printf("��Ȧ��%d �̼�ģʽ��%d\n",nSelCoilNum,nSelStimNum);
			
		
			break;
	}
	return 0;
}

