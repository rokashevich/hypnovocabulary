@echo off
cd %~dp0
set QTDIR=C:\Qt\5.6\mingw49_32
copy %QTDIR%\bin\Qt5Core.dll bundle\
copy %QTDIR%\bin\Qt5Gui.dll bundle\
copy %QTDIR%\bin\Qt5Widgets.dll bundle\
copy %QTDIR%\bin\libgcc_s_dw2-1.dll bundle\
copy %QTDIR%\bin\libwinpthread-1.dll bundle\
copy "%QTDIR%\bin\libstdc++-6.dll" bundle\
mkdir bundle\platforms
copy %QTDIR%\plugins\platforms\qminimal.dll bundle\platforms