; TeamRobot Installer Script

;--------------------------------

; The name of the installer
Name "TeamRobot Installer"

; The file to write
OutFile "teamrobot-install.exe"

; The default installation directory
InstallDir $PROGRAMFILES\TeamRobot

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\TeamRobot" "Install_Dir"

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "TeamRobot (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File teamrobot.exe 
  File /r images
  File /r sounds
  File /r levels
  File font.xml
  File resources.xml
  File gui.xml
  File icon1.ico

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\TeamRobot "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TeamRobot" "DisplayName" "TeamRobot"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TeamRobot" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TeamRobot" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TeamRobot" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\TeamRobot"
  CreateShortCut "$SMPROGRAMS\TeamRobot\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\TeamRobot\TeamRobot (TeamRobot).lnk" "$INSTDIR\teamrobot.exe" "" "$INSTDIR\teamrobot.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TeamRobot"
  DeleteRegKey HKLM SOFTWARE\TeamRobot

  ; Remove files and uninstaller
  Delete $INSTDIR\teamrobot.exe
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\TeamRobot\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\TeamRobot"
  RMDir "$INSTDIR"

SectionEnd
