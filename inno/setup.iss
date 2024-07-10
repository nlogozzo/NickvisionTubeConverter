; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Nickvision Parabolic"
#define MyAppShortName "Parabolic"
#define MyAppVersion "2024.7.0"
#define MyAppPublisher "Nickvision"
#define MyAppURL "https://nickvision.org"
#define MyAppExeName "org.nickvision.tubeconverter.winui.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{F0AE5CF5-E5D8-45DA-BE26-292D04C2591B}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
UsePreviousAppDir=no
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile=..\COPYING
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=..\inno
OutputBaseFilename=NickvisionParabolicSetup
SetupIconFile=..\resources\org.nickvision.tubeconverter.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern
PrivilegesRequired=admin
DirExistsWarning=no
CloseApplications=yes
ChangesEnvironment=yes

[Code]
procedure SetupVC();
var
  ResultCode: Integer;
begin
  if not Exec(ExpandConstant('{app}\deps\vc_redist.x64.exe'), '/install /quiet /norestart', '', SW_HIDE, ewWaitUntilTerminated, ResultCode)
  then
    MsgBox('Unable to install VC . Please try again', mbError, MB_OK);
end;

procedure SetupWinAppSDK();
var
  ResultCode: Integer;
begin
  if not Exec(ExpandConstant('{app}\deps\windowsappruntimeinstall-x64.exe'), '--quiet', '', SW_HIDE, ewWaitUntilTerminated, ResultCode)
  then
    MsgBox('Unable to install Windows App SDK. Please try again', mbError, MB_OK);
end;

procedure Cleanup();
begin
  DelTree(ExpandConstant('{app}\deps'), True, True, True);
end;

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\vc_redist.x64.exe"; DestDir: "{app}\deps"; AfterInstall: SetupVC  
Source: "..\windowsappruntimeinstall-x64.exe"; DestDir: "{app}\deps"; AfterInstall: SetupWinAppSDK  
Source: "..\yt-dlp.exe"; DestDir: "{app}\Release"; Flags: ignoreversion
Source: "..\ffmpeg.exe"; DestDir: "{app}\Release"; Flags: ignoreversion
Source: "..\ffplay.exe"; DestDir: "{app}\Release"; Flags: ignoreversion
Source: "..\ffprobe.exe"; DestDir: "{app}\Release"; Flags: ignoreversion
Source: "..\aria2c.exe"; DestDir: "{app}\Release"; Flags: ignoreversion
Source: "..\build\org.nickvision.tubeconverter.winui\Release\{#MyAppExeName}"; DestDir: "{app}\Release"; Flags: ignoreversion 
Source: "..\build\org.nickvision.tubeconverter.winui\Release\*"; DestDir: "{app}\Release"; Flags: ignoreversion recursesubdirs createallsubdirs; AfterInstall: Cleanup
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppShortName}"; Filename: "{app}\Release\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppShortName}"; Filename: "{app}\Release\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\Release\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

