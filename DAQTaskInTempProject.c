//**************************************************************************
//* WARNING: This file was automatically generated.  Any changes you make  *
//*          to this file will be lost if you generate the file again.     *
//**************************************************************************
#include <ansi_c.h>
#include <NIDAQmx.h>

#define DAQmxErrChk(functionCall) if( (DAQmxError=(functionCall))<0 ) goto Error; else

//**************************************************************************
//* This generated function configures your DAQmx task.                    *
//*                                                                        *
//* Follow these steps to use this generated function:                     *
//*   1) Define a task handle variable in your program.                    *
//*   2) Call the generated function.                                      *
//*   3) Use the returned task handle as a parameter to other DAQmx        *
//*      functions.                                                        *
//*   4) Clear the task handle when you finish.                            *
//*                                                                        *
//*         TaskHandle task = 0;                                           *
//*         CreateDAQTask(&task);                                          *
//*         <use the DAQmx task handle>                                    *
//*         DAQmxClearTask(task);                                          *
//*                                                                        *
//**************************************************************************
int32 CreateDAQTaskInTempProject(TaskHandle *taskOut1)
{
	int32 DAQmxError = DAQmxSuccess;
    TaskHandle taskOut;

	DAQmxErrChk(DAQmxCreateTask("DAQTaskInTempProject", &taskOut));

	DAQmxErrChk(DAQmxCreateAIVoltageChan(taskOut, "Dev1/ai1", "µÁ—π_0",
		DAQmx_Val_Diff, 0, 10, DAQmx_Val_Volts, ""));	

	DAQmxErrChk(DAQmxCreateAIVoltageChan(taskOut, "Dev1/ai4", "µÁ—π_1",
		DAQmx_Val_Diff, 0, 10, DAQmx_Val_Volts, ""));	

	DAQmxErrChk(DAQmxCfgSampClkTiming(taskOut, "", 
		100000, DAQmx_Val_Rising, 
		DAQmx_Val_FiniteSamps, 100));

    *taskOut1 = taskOut;

Error:
	return DAQmxError;
}

