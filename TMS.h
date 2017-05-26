/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_DECORATION_3               2       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_4               3       /* control type: deco, callback function: (none) */
#define  PANEL_CMD_SYS_CONFIG             4       /* control type: command, callback function: Cmd_Sys_Config */
#define  PANEL_CMD_EXIT_SW                5       /* control type: command, callback function: Cmd_Exit_Sw */
#define  PANEL_CMD_STOP_STIM              6       /* control type: command, callback function: Cmd_Stop_Stim */
#define  PANEL_TXT_CURRENT_STATE          7       /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_POWER                  8       /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_COIL                   9       /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_SYS_TIME               10      /* control type: textMsg, callback function: (none) */
#define  PANEL_CMD_PT_CONFIG              11      /* control type: command, callback function: Cmd_Pt_Config */
#define  PANEL_CMD_START_STIM             12      /* control type: command, callback function: Cmd_Start_Stim */
#define  PANEL_TXT_STATE_STIM             13      /* control type: textMsg, callback function: (none) */
#define  PANEL_SYS_STATE_STIM             14      /* control type: scale, callback function: (none) */
#define  PANEL_SYS_STATE_TEMP_2           15      /* control type: scale, callback function: (none) */
#define  PANEL_SYS_STATE_TEMP             16      /* control type: scale, callback function: (none) */
#define  PANEL_TXT_STATE_TEMP             17      /* control type: textMsg, callback function: (none) */
#define  PANEL_SYS_STATE_COIL             18      /* control type: LED, callback function: (none) */
#define  PANEL_SYS_STATE_POWER            19      /* control type: LED, callback function: (none) */
#define  PANEL_TXT_STATE_COIL             20      /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_STATE_CONN             21      /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_STATE_POWER            22      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_30                 23      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_31                 24      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_32                 25      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_23                 26      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_22                 27      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_21                 28      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_20                 29      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_9                  30      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_6               31      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_11              32      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_2               33      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_12              34      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_13              35      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_33                 36      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_15              37      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_27                 38      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_26                 39      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_25                 40      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_16              41      /* control type: deco, callback function: (none) */
#define  PANEL_COIL_CC_1                  42      /* control type: picture, callback function: (none) */
#define  PANEL_COIL_DBL_8                 43      /* control type: picture, callback function: (none) */
#define  PANEL_COIL_SGL_8                 44      /* control type: picture, callback function: (none) */
#define  PANEL_COIL_CC_4                  45      /* control type: picture, callback function: (none) */
#define  PANEL_TEXTMSG_37                 46      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_19              47      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_17              48      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_24                 49      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_34                 50      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_35                 51      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_36                 52      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_11                 53      /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_BAR1                   54      /* control type: textMsg, callback function: (none) */
#define  PANEL_TAB_STIM_MODE              55      /* control type: tab, callback function: Tab_Stim_Mode */
#define  PANEL_TXT_FOCUS                  56      /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_BAR2                   57      /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_STIM_MODE              58      /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_BAR3                   59      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_41                 60      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_10                 61      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_38                 62      /* control type: textMsg, callback function: (none) */
#define  PANEL_TXT_BAR4                   63      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_18              64      /* control type: deco, callback function: (none) */
#define  PANEL_STR_AGE                    65      /* control type: string, callback function: (none) */
#define  PANEL_STR_SEX                    66      /* control type: string, callback function: (none) */
#define  PANEL_STR_NAME                   67      /* control type: string, callback function: (none) */
#define  PANEL_STR_SYMPTOM                68      /* control type: string, callback function: (none) */
#define  PANEL_STR_ID                     69      /* control type: string, callback function: (none) */
#define  PANEL_CONNECT_STATE              70      /* control type: LED, callback function: (none) */
#define  PANEL_DECORATION_10              71      /* control type: deco, callback function: (none) */
#define  PANEL_SPLITTER_3                 72      /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER_2                 73      /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER                   74      /* control type: splitter, callback function: (none) */

#define  PANEL_PT                         2
#define  PANEL_PT_TABLE_PATIENT           2       /* control type: table, callback function: Table_Patient */
#define  PANEL_PT_CMD_PATIENT_SEL         3       /* control type: command, callback function: Cmd_Patient_Sel */
#define  PANEL_PT_CMD_PATIENT_DEL         4       /* control type: command, callback function: Cmd_Patient_Del */
#define  PANEL_PT_CMD_PATIENT_SAVE        5       /* control type: command, callback function: Cmd_Patient_Save */
#define  PANEL_PT_CMD_PATIENT_ADD         6       /* control type: command, callback function: Cmd_Patient_Add */
#define  PANEL_PT_CMD_PATIENT_CANCEL      7       /* control type: command, callback function: Cmd_Patient_Cancel */
#define  PANEL_PT_PATIENT_SYMPTOM         8       /* control type: string, callback function: (none) */
#define  PANEL_PT_PATIENT_AGE             9       /* control type: string, callback function: (none) */
#define  PANEL_PT_PATIENT_SEX             10      /* control type: string, callback function: (none) */
#define  PANEL_PT_PATIENT_NAME            11      /* control type: string, callback function: (none) */
#define  PANEL_PT_PATIENT_ID              12      /* control type: string, callback function: (none) */

#define  PANEL_SYS                        3       /* callback function: Panel_Sys */
#define  PANEL_SYS_TAB_SYS_CONFIG         2       /* control type: tab, callback function: Tab_Sys_Config */
#define  PANEL_SYS_CMD_SYS_CONFIG_CANCEL  3       /* control type: command, callback function: Cmd_Sys_Config_Cancel */
#define  PANEL_SYS_CMD_SYS_CONFIG_OK      4       /* control type: command, callback function: Cmd_Sys_Config_Ok */

     /* tab page panel controls */
#define  TAB_CC_1_TEXTMSG_13              2       /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TABLE_CC1_SQC           3       /* control type: table, callback function: (none) */
#define  TAB_CC_1_CB_CC1_RPT_STIM         4       /* control type: radioButton, callback function: Cb_Cc1_Rpt_Stim */
#define  TAB_CC_1_CB_CC1_SGL_STIM         5       /* control type: radioButton, callback function: Cb_Cc1_Sgl_Stim */
#define  TAB_CC_1_CB_CC1_SQC_STIM         6       /* control type: radioButton, callback function: Cb_Cc1_Sqc_Stim */
#define  TAB_CC_1_DECORATION_8            7       /* control type: deco, callback function: (none) */
#define  TAB_CC_1_DECORATION_7            8       /* control type: deco, callback function: (none) */
#define  TAB_CC_1_PULSE_SQC               9       /* control type: picture, callback function: (none) */
#define  TAB_CC_1_PULSE_SGL               10      /* control type: picture, callback function: (none) */
#define  TAB_CC_1_CMD_CC1_SQC_STIM_CLC    11      /* control type: command, callback function: Cmd_Cc1_Sqc_Stim_Clc */
#define  TAB_CC_1_CMD_CC1_SQC_STIM_DEL    12      /* control type: command, callback function: Cmd_Cc1_Sqc_Stim_Del */
#define  TAB_CC_1_CMD_CC1_SQC_STIM_ADD    13      /* control type: command, callback function: Cmd_Cc1_Sqc_Stim_Add */
#define  TAB_CC_1_CC1_SQC_FQC             14      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_CC1_SQC_TT              15      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_CC1_SQC_TITV            16      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_CC1_RPT_TT              17      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_CC1_SQC_PWR             18      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_CC1_RPT_FQC             19      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_CC1_RPT_TITV            20      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_CC1_RPT_TN              21      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_60              22      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_41              23      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_61              24      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_PULSE_RPT               25      /* control type: picture, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_62              26      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_44              27      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_63              28      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_59              29      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_64              30      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_45              31      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_65              32      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_58              33      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_66              34      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_46              35      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_55              36      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_43              37      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_CC1_SGL_PWR             38      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_42              39      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_CC1_RPT_PWR             40      /* control type: numeric, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_40              41      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_56              42      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_1_TEXTMSG_57              43      /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TAB_CC_4_DECORATION_19           2       /* control type: deco, callback function: (none) */
#define  TAB_CC_4_TABLE_CC4_SQC           3       /* control type: table, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_13              4       /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_10              5       /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_CB_CC4_RPT_STIM         6       /* control type: radioButton, callback function: Cb_Cc4_Rpt_Stim */
#define  TAB_CC_4_CB_CC4_SGL_STIM         7       /* control type: radioButton, callback function: Cb_Cc4_Sgl_Stim */
#define  TAB_CC_4_CB_CC4_SQC_STIM         8       /* control type: radioButton, callback function: Cb_Cc4_Sqc_Stim */
#define  TAB_CC_4_DECORATION_8            9       /* control type: deco, callback function: (none) */
#define  TAB_CC_4_DECORATION_7            10      /* control type: deco, callback function: (none) */
#define  TAB_CC_4_CMD_CC4_SQC_STIM_CLC    11      /* control type: command, callback function: Cmd_Cc4_Sqc_Stim_Clc */
#define  TAB_CC_4_CMD_CC4_SQC_STIM_DEL    12      /* control type: command, callback function: Cmd_Cc4_Sqc_Stim_Del */
#define  TAB_CC_4_CMD_CC4_SQC_STIM_ADD    13      /* control type: command, callback function: Cmd_Cc4_Sqc_Stim_Add */
#define  TAB_CC_4_PULSE_SQC               14      /* control type: picture, callback function: (none) */
#define  TAB_CC_4_PULSE_SGL               15      /* control type: picture, callback function: (none) */
#define  TAB_CC_4_CC4_RPT_TT              16      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_CC4_RPT_FQC             17      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_CC4_RPT_TITV            18      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_CC4_RPT_TN              19      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_60              20      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_41              21      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_61              22      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_CC4_SQC_FQC             23      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_PULSE_RPT               24      /* control type: picture, callback function: (none) */
#define  TAB_CC_4_CC4_SQC_TT              25      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_CC4_SQC_TITV            26      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_62              27      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_CC4_SQC_INT             28      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_44              29      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_63              30      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_59              31      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_64              32      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_45              33      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_65              34      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_DECORATION_11           35      /* control type: deco, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_58              36      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_66              37      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_46              38      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_55              39      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_43              40      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_CC4_SGL_PWR             41      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_42              42      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_CC4_RPT_PWR             43      /* control type: numeric, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_40              44      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_56              45      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_TEXTMSG_57              46      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_FCS_L_VTC               47      /* control type: picture, callback function: Fcs_L_Vtc */
#define  TAB_CC_4_FCS_L_HZ                48      /* control type: picture, callback function: Fcs_L_Hz */
#define  TAB_CC_4_FCS_1_RT                49      /* control type: picture, callback function: Fcs_1_Rt */
#define  TAB_CC_4_FCS_1_BTM               50      /* control type: picture, callback function: Fcs_1_Btm */
#define  TAB_CC_4_FCS_1_LFT               51      /* control type: picture, callback function: Fcs_1_Lft */
#define  TAB_CC_4_FCS_1_TOP               52      /* control type: picture, callback function: Fcs_1_Top */
#define  TAB_CC_4_FCS_4_TBLR              53      /* control type: picture, callback function: Fcs_4_Tblr */
#define  TAB_CC_4_CC4_SQC_FCS             54      /* control type: string, callback function: Cc4_Sqc_Fcs */
#define  TAB_CC_4_A                       55      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_B                       56      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_C                       57      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_D                       58      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_E                       59      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_F                       60      /* control type: textMsg, callback function: (none) */
#define  TAB_CC_4_G                       61      /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TAB_COIL_TABLE_COIL              2       /* control type: table, callback function: Table_Coil */
#define  TAB_COIL_RDB_CC4                 3       /* control type: radioButton, callback function: Rdb_Cc4 */
#define  TAB_COIL_RDB_DBL8_B              4       /* control type: radioButton, callback function: Rdb_Dbl8_B */
#define  TAB_COIL_RDB_DBL8_A              5       /* control type: radioButton, callback function: Rdb_Dbl8_A */
#define  TAB_COIL_RDB_SGL8                6       /* control type: radioButton, callback function: Rdb_Sgl8 */
#define  TAB_COIL_RDB_CC1                 7       /* control type: radioButton, callback function: Rdb_Cc1 */
#define  TAB_COIL_TEXTMSG                 8       /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TAB_DBL_8_TEXTMSG_13             2       /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TABLE_DBL8_SQC         3       /* control type: table, callback function: (none) */
#define  TAB_DBL_8_CB_DBL8_RPT_STIM       4       /* control type: radioButton, callback function: Cb_Dbl8_Rpt_Stim */
#define  TAB_DBL_8_CB_DBL8_SGL_STIM       5       /* control type: radioButton, callback function: Cb_Dbl8_Sgl_Stim */
#define  TAB_DBL_8_CB_DBL8_SQC_STIM       6       /* control type: radioButton, callback function: Cb_Dbl8_Sqc_Stim */
#define  TAB_DBL_8_DECORATION_8           7       /* control type: deco, callback function: (none) */
#define  TAB_DBL_8_DECORATION_7           8       /* control type: deco, callback function: (none) */
#define  TAB_DBL_8_PULSE_SQC              9       /* control type: picture, callback function: (none) */
#define  TAB_DBL_8_PULSE_SGL              10      /* control type: picture, callback function: (none) */
#define  TAB_DBL_8_CMD_DBL8_SQC_STIM_CLC  11      /* control type: command, callback function: Cmd_Dbl8_Sqc_Stim_Clc */
#define  TAB_DBL_8_CMD_DBL8_SQC_STIM_DEL  12      /* control type: command, callback function: Cmd_Dbl8_Sqc_Stim_Del */
#define  TAB_DBL_8_CMD_DBL8_SQC_STIM_ADD  13      /* control type: command, callback function: Cmd_Dbl8_Sqc_Stim_Add */
#define  TAB_DBL_8_DBL8_RPT_TITV_B        14      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_TT_B          15      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_TN_B          16      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_TITV_A        17      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_SGL_PWR_A         18      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_SGL_PWR_B         19      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_TT_A          20      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_TN_A          21      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_FQC_B         22      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_SQC_FQC           23      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_PWR_B         24      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_SQC_TT            25      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_SQC_TITV          26      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_FQC_A         27      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_SQC_INT           28      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_DBL8_RPT_PWR_A         29      /* control type: numeric, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_60             30      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_41             31      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_61             32      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_PULSE_RPT              33      /* control type: picture, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_62             34      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_44             35      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_63             36      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_59             37      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_64             38      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_45             39      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_CB_DBL8_SGL_A          40      /* control type: radioButton, callback function: Cb_Dbl8_Sgl_A */
#define  TAB_DBL_8_TEXTMSG_65             41      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_CB_DBL8_SGL_B          42      /* control type: radioButton, callback function: Cb_Dbl8_Sgl_B */
#define  TAB_DBL_8_TEXTMSG_58             43      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_66             44      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_46             45      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_55             46      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_DECORATION_11          47      /* control type: deco, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_43             48      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_CB_DBL8_RPT_B          49      /* control type: radioButton, callback function: Cb_Dbl8_Rpt_B */
#define  TAB_DBL_8_DECORATION_10          50      /* control type: deco, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_42             51      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_40             52      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_DECORATION             53      /* control type: deco, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_57             54      /* control type: textMsg, callback function: (none) */
#define  TAB_DBL_8_CB_DBL8_RPT_A          55      /* control type: radioButton, callback function: Cb_Dbl8_Rpt_A */
#define  TAB_DBL_8_DBL8_SQC_COIL          56      /* control type: string, callback function: Dbl8_Sqc_Coil */
#define  TAB_DBL_8_DECORATION_9           57      /* control type: deco, callback function: (none) */
#define  TAB_DBL_8_TEXTMSG_56             58      /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TAB_OTHER_DISCHRG_TIME           2       /* control type: numeric, callback function: DisChrg_Time */
#define  TAB_OTHER_COILTEMP_MAX           3       /* control type: numeric, callback function: CoilTemp_Max */

     /* tab page panel controls */
#define  TAB_SGL_8_TEXTMSG_13             2       /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TABLE_SGL8_SQC         3       /* control type: table, callback function: (none) */
#define  TAB_SGL_8_CB_SGL8_RPT_STIM       4       /* control type: radioButton, callback function: Cb_Sgl8_Rpt_Stim */
#define  TAB_SGL_8_CB_SGL8_SGL_STIM       5       /* control type: radioButton, callback function: Cb_Sgl8_Sgl_Stim */
#define  TAB_SGL_8_CB_SGL8_SQC_STIM       6       /* control type: radioButton, callback function: Cb_Sgl8_Sqc_Stim */
#define  TAB_SGL_8_DECORATION_8           7       /* control type: deco, callback function: (none) */
#define  TAB_SGL_8_DECORATION_7           8       /* control type: deco, callback function: (none) */
#define  TAB_SGL_8_PULSE_SQC              9       /* control type: picture, callback function: (none) */
#define  TAB_SGL_8_PULSE_SGL              10      /* control type: picture, callback function: (none) */
#define  TAB_SGL_8_CMD_SGL8_SQC_STIM_CLC  11      /* control type: command, callback function: Cmd_Sgl8_Sqc_Stim_Clc */
#define  TAB_SGL_8_CMD_SGL8_SQC_STIM_DEL  12      /* control type: command, callback function: Cmd_Sgl8_Sqc_Stim_Del */
#define  TAB_SGL_8_CMD_SGL8_SQC_STIM_ADD  13      /* control type: command, callback function: Cmd_Sgl8_Sqc_Stim_Add */
#define  TAB_SGL_8_SGL8_RPT_TT            14      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_SGL8_RPT_FQC           15      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_SGL8_RPT_TITV          16      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_SGL8_SQC_FQC           17      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_SGL8_SQC_TT            18      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_SGL8_SQC_TITV          19      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_SGL8_RPT_TN            20      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_SGL8_SQC_INT           21      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_60             22      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_41             23      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_61             24      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_PULSE_RPT              25      /* control type: picture, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_62             26      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_44             27      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_63             28      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_59             29      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_64             30      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_45             31      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_65             32      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_58             33      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_66             34      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_46             35      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_55             36      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_43             37      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_SGL8_RPT_PWR           38      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_42             39      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_40             40      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_SGL8_SGL_PWR           41      /* control type: numeric, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_56             42      /* control type: textMsg, callback function: (none) */
#define  TAB_SGL_8_TEXTMSG_57             43      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Cb_Cc1_Rpt_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Cc1_Sgl_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Cc1_Sqc_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Cc4_Rpt_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Cc4_Sgl_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Cc4_Sqc_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Dbl8_Rpt_A(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Dbl8_Rpt_B(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Dbl8_Rpt_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Dbl8_Sgl_A(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Dbl8_Sgl_B(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Dbl8_Sgl_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Dbl8_Sqc_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Sgl8_Rpt_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Sgl8_Sgl_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Sgl8_Sqc_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cc4_Sqc_Fcs(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Cc1_Sqc_Stim_Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Cc1_Sqc_Stim_Clc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Cc1_Sqc_Stim_Del(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Cc4_Sqc_Stim_Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Cc4_Sqc_Stim_Clc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Cc4_Sqc_Stim_Del(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Dbl8_Sqc_Stim_Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Dbl8_Sqc_Stim_Clc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Dbl8_Sqc_Stim_Del(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Exit_Sw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Patient_Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Patient_Cancel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Patient_Del(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Patient_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Patient_Sel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Pt_Config(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Sgl8_Sqc_Stim_Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Sgl8_Sqc_Stim_Clc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Sgl8_Sqc_Stim_Del(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Start_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Stop_Stim(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Sys_Config(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Sys_Config_Cancel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cmd_Sys_Config_Ok(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CoilTemp_Max(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Dbl8_Sqc_Coil(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisChrg_Time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fcs_1_Btm(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fcs_1_Lft(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fcs_1_Rt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fcs_1_Top(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fcs_4_Tblr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fcs_L_Hz(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fcs_L_Vtc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Panel_Sys(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rdb_Cc1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rdb_Cc4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rdb_Dbl8_A(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rdb_Dbl8_B(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rdb_Sgl8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tab_Stim_Mode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tab_Sys_Config(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Table_Coil(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Table_Patient(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
