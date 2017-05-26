<distribution version="15.0.0" name="TMS" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{A16BC070-2D97-49A1-9CBF-CFE19344ADFE}">
		<general appName="TMS" outputLocation="d:\TMS_Final\TMS_20160325\cvidistkit.TMS" relOutputLocation="cvidistkit.TMS" outputLocationWithVars="d:\TMS_Final\TMS_20160325\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="2" autoIncrement="true" version="1.0.5">
			<arp company="PKU" companyURL="www.pku.edu.cn" supportURL="" contact="李晓华" phone="13810832668" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="Chinese (Simplified)" showPaths="true" showRuntimeOnly="true" readMe="" license="">
			<dlgstrings welcomeTitle="TMS" welcomeText=""/></userinterface>
		<dirs appDirID="101">
			<installDir name="Pic" dirID="100" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="TMS" dirID="101" parentID="2" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Coil" dirID="102" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Log" dirID="103" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Patient" dirID="104" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="para" dirID="105" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="TMS" dirID="106" parentID="7" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Pulse" dirID="107" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Desktop]" dirID="0" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="Focus" dirID="108" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="d:\TMS_Final\TMS_20160325\cvibuild.TMS\Release\TMS.exe" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="D:\TMS_Final\TMS_20160325\Coil\COIL_CC_1.png" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="d:\TMS_Final\TMS_20160325\TMS.uir" relSourcePath="TMS.uir" relSourceBase="0" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="3" sourcePath="D:\TMS_Final\TMS_20160325\Pic\Logo_PKU.png" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="4" sourcePath="D:\TMS_Final\TMS_20160325\Patient\patient.txt" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="5" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160322.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="6" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160309.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="7" sourcePath="D:\TMS_Final\TMS_20160325\Pulse\PULSE_RPT.png" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="8" sourcePath="D:\TMS_Final\TMS_20160325\para\StimPara_DBL8_A.txt" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="9" sourcePath="D:\TMS_Final\TMS_20160325\Focus\Focus_2.png" targetDir="108" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="10" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160324.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="11" sourcePath="D:\TMS_Final\TMS_20160325\para\StimPara_CC4.txt" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="12" sourcePath="D:\TMS_Final\TMS_20160325\Pulse\PULSE_SQC.png" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="13" sourcePath="D:\TMS_Final\TMS_20160325\para\StimPara_CC1.txt" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="14" sourcePath="D:\TMS_Final\TMS_20160325\Focus\Focus_5.png" targetDir="108" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="15" sourcePath="D:\TMS_Final\TMS_20160325\Coil\COIL_CC_4.png" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="16" sourcePath="D:\TMS_Final\TMS_20160325\para\Others.ini" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="17" sourcePath="D:\TMS_Final\TMS_20160325\Pulse\PULSE_SGL.png" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="18" sourcePath="D:\TMS_Final\TMS_20160325\para\StimPara_DBL8_B.txt" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="19" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160314.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="20" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160315.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="21" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160329.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="22" sourcePath="D:\TMS_Final\TMS_20160325\para\StimPara_SGL8.txt" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="23" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160321.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="24" sourcePath="D:\TMS_Final\TMS_20160325\Coil\COIL_DBL_8.png" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="25" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160325.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="26" sourcePath="D:\TMS_Final\TMS_20160325\Focus\Focus_4.png" targetDir="108" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="27" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160323.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="28" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160310.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="29" sourcePath="D:\TMS_Final\TMS_20160325\Focus\Focus_1.png" targetDir="108" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="30" sourcePath="D:\TMS_Final\TMS_20160325\Coil\COIL_SGL_8.png" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="31" sourcePath="D:\TMS_Final\TMS_20160325\Focus\Focus_3.png" targetDir="108" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="32" sourcePath="D:\TMS_Final\TMS_20160325\Focus\Focus_6.png" targetDir="108" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="33" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160316.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="34" sourcePath="D:\TMS_Final\TMS_20160325\Focus\Focus_7.png" targetDir="108" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="35" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160331.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="36" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160318.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="37" sourcePath="D:\TMS_Final\TMS_20160325\Pic\Logo_XW.png" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="38" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160317.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="39" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160330.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="40" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160320.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="41" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160328.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="42" sourcePath="D:\TMS_Final\TMS_20160325\Log\TMS_LOG_20160311.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="43" sourcePath="D:\TMS_Final\TMS_20160325\Pic\TMS.ico" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="101" projectID="0">
				<fileID>0</fileID></projectOutput>
			<projectDependencies dirID="101" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="TMS" targetFileID="0" destDirID="106" cmdLineArgs="" description="" runStyle="NORMAL"/>
			<shortcut name="TMS" targetFileID="0" destDirID="0" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine installToAppDir="false" activeXsup="true" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="true">
			<hasSoftDeps/></runtimeEngine><sxsRuntimeEngine>
			<selected>false</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WIN7</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<baselineProducts>
			<product name="NI LabWindows/CVI Shared Runtime 2015" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{C123DBC1-8C63-4369-A052-EE7D3922EAC9}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="15.0.408">
				<dependencies>
					<productID>{024FAF36-B990-41BE-8B48-D850F5C8494C}</productID>
					<productID>{0416C950-A8C6-4CFE-B206-A8D28091A40B}</productID>
					<productID>{08505CC2-EA7F-4818-9C45-B74EDA7227F8}</productID>
					<productID>{108DA20D-E0DA-4F10-A7B6-96D2ACA38752}</productID>
					<productID>{10A1BCD4-CF1D-4198-B037-77FB1AEFF5FE}</productID>
					<productID>{20124E21-206B-485F-838F-14BB88161045}</productID>
					<productID>{21B81C08-8854-4C2D-99E2-6CECA2D468A8}</productID>
					<productID>{22F17C52-A282-4383-8E5C-5C38B41DD605}</productID>
					<productID>{37C0159A-E5E2-4688-9360-0435AE0E55C7}</productID>
					<productID>{3830A103-2D39-4801-927B-BD0C5BC78DC2}</productID>
					<productID>{511DCDDD-7001-4E8A-9B76-2973184602D3}</productID>
					<productID>{658224F9-1A2B-4E18-B00F-3F969C9EE080}</productID>
					<productID>{7F93F26A-E5F7-4AE1-840F-F88DFE2DE3A5}</productID>
					<productID>{87E698D6-02AC-485E-A6BA-9194C94CC547}</productID>
					<productID>{8FA5DFB9-33F5-4ADD-B0E2-350BAA0BABB5}</productID>
					<productID>{A27131D0-7F5F-4CB3-9A4B-1A2563D5821C}</productID>
					<productID>{A6EC0085-0C92-43C8-9EF5-82C3BFDAB3EE}</productID>
					<productID>{B3B56C15-80A8-4972-90CB-D80E64B3F39C}</productID>
					<productID>{C1F1FD0A-D051-4CA7-AAF0-2E9C0A881054}</productID>
					<productID>{C23121A8-AF17-4C1D-A2B4-A6DE7A156DCF}</productID>
					<productID>{C67371A2-E288-429E-A2B6-85D36B29BF8E}</productID>
					<productID>{CE1D0ABA-7672-4A48-ACD8-9AFB1EA33809}</productID>
					<productID>{DE29136A-18FD-4868-920D-455BAC406C29}</productID>
					<productID>{E37177D7-6E25-4A09-9B6B-A64707B4D563}</productID>
					<productID>{E42DC871-9F3D-4FCC-9722-4ABE047C63B1}</productID>
					<productID>{E84997A1-4D6F-4C0B-B60D-F85B360D2666}</productID>
					<productID>{ECB572E6-5CE3-4E9E-B1B3-16A00E02153A}</productID>
					<productID>{F2273FA7-117C-43D7-BD59-00B025535442}</productID></dependencies></product>
			<product name="NI-DAQmx Runtime 15.5" UC="{923C9CD5-A0D8-4147-9A8D-998780E30763}" productID="{282047BF-3150-4411-A7F9-4E84D59A0DE7}" path="(None)" flavorID="_full_" flavorName="Runtime" verRestr="false" coreVer="15.50.49152">
				<dependencies>
					<productID>{0254E88F-B754-4C89-9237-4DB51CAF6E6B}</productID>
					<productID>{0869FCA0-E7F7-45B4-8AA6-C7F38BDC999A}</productID>
					<productID>{0BEC53B4-1F11-4B5D-8823-7CD989A2AF18}</productID>
					<productID>{108DA20D-E0DA-4F10-A7B6-96D2ACA38752}</productID>
					<productID>{137571E8-8C31-4957-B6D8-0655D4352FAA}</productID>
					<productID>{140C2942-89C1-4CCB-8EF0-E3EFEE47BE9E}</productID>
					<productID>{180778D4-3CB5-41D1-9F16-F330A211340B}</productID>
					<productID>{1E31480B-C568-4CFE-81B1-9B2B041A91EB}</productID>
					<productID>{20124E21-206B-485F-838F-14BB88161045}</productID>
					<productID>{20D9F37F-8742-4F3F-811B-303A7BFC6E4C}</productID>
					<productID>{2F96C96B-1F8C-4E43-A68E-097198BB94DB}</productID>
					<productID>{32102491-7A91-4478-9F84-70D6DD325AF7}</productID>
					<productID>{3830A103-2D39-4801-927B-BD0C5BC78DC2}</productID>
					<productID>{3A0CBC02-CBC7-4F3B-94F1-7EFFAB05DE4C}</productID>
					<productID>{3D7A22BF-A10F-4F3D-8C5E-CE38E8EFD3F4}</productID>
					<productID>{415780C0-4A19-4567-AAAE-10CCB9832B13}</productID>
					<productID>{48E3422A-2764-4AC0-9027-D066001158C7}</productID>
					<productID>{511DCDDD-7001-4E8A-9B76-2973184602D3}</productID>
					<productID>{54FE2F95-81BF-4AC1-A303-263C7FD3CAB6}</productID>
					<productID>{620E2675-9EB4-47C9-A6A8-FFBFA5B5CAEE}</productID>
					<productID>{6454CE6A-2F1B-4548-B932-F9282CE22369}</productID>
					<productID>{658224F9-1A2B-4E18-B00F-3F969C9EE080}</productID>
					<productID>{6CED5B26-5F59-4586-9EC0-3E92B5ECF76E}</productID>
					<productID>{6EB5AE02-7B7F-4BBA-92D3-8E16EABD716A}</productID>
					<productID>{7C925FEF-175B-427F-98F6-517D90445561}</productID>
					<productID>{8FA5DFB9-33F5-4ADD-B0E2-350BAA0BABB5}</productID>
					<productID>{A626D491-9243-4079-BFED-F5994370FE5D}</productID>
					<productID>{A6B51336-E340-4F69-AD9A-35B4CE00FA29}</productID>
					<productID>{A6D3B721-E990-45D2-AE97-FFCD385C78DF}</productID>
					<productID>{A6EC0085-0C92-43C8-9EF5-82C3BFDAB3EE}</productID>
					<productID>{BC793079-C42A-42A5-A2FF-69F95EF253ED}</productID>
					<productID>{BF43E745-015C-422C-8CB9-9C4AF9E0147E}</productID>
					<productID>{C8D01979-121F-4EB3-AD6F-0C754C987909}</productID>
					<productID>{CE1D0ABA-7672-4A48-ACD8-9AFB1EA33809}</productID>
					<productID>{D84FB7E8-4AB8-4C2D-8457-01EC7C05BA2A}</productID>
					<productID>{DEC25D81-2317-47F6-8B26-D54A939DA1EE}</productID>
					<productID>{DFDF4CEF-9EAA-45A1-87C9-B2DF39C5DB6F}</productID>
					<productID>{E26D12B1-FC0E-4A96-B283-1B1CBC7DB896}</productID>
					<productID>{E37177D7-6E25-4A09-9B6B-A64707B4D563}</productID>
					<productID>{E84997A1-4D6F-4C0B-B60D-F85B360D2666}</productID>
					<productID>{E863186F-AEBE-4E1E-A8D6-E58D6AC15B14}</productID>
					<productID>{EB3180EC-A3C4-4128-B3E1-9CFA74B6AE28}</productID>
					<productID>{EB66D3AE-4EE2-485D-B875-0B73185D0223}</productID>
					<productID>{F3E66B88-C518-412C-BCA3-577951F3E991}</productID>
					<productID>{FE107E74-49F0-43F3-A0CA-5FAC52592F98}</productID></dependencies></product></baselineProducts>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="d:\TMS_Final\TMS_20160325\TMS.prj" ProjectRelativePath="TMS.prj"/></Projects>
		<buildData progressBarRate="0.593002760632251">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.357886742187500</ProductsAdded>
				<DPConfigured>1.062963062500000</DPConfigured>
				<DPMergeModulesAdded>2.157105281250000</DPMergeModulesAdded>
				<DPClosed>3.791089382812500</DPClosed>
				<DistributionsCopied>4.068202507812500</DistributionsCopied>
				<End>168.633279031250000</End></progressTimes></buildData>
	</msi>
</distribution>
