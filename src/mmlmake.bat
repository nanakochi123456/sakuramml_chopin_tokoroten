rem @echo off

set GOW=E:\Program\Dev\Gow\bin
set CYGWIN=E:\Program\Dev\Cygwin64\bin
set GREP="%GOW%\grep.exe"
set BASE="%CYGWIN%\base64.exe"
set ZIP="%ProgramFiles%\7-zip\7z.exe"

if "%1"=="" goto noopt

echo. >> upload.mml
echo /////////////////////////////////////////////////////// >> upload.mml
echo // %1 >> upload.mml
echo /////////////////////////////////////////////////////// >> upload.mml
echo Key(KEY) >>upload.mml
IF "%2"=="" goto notime
echo #TM={Time(%2)} >> upload.mml

:notime
echo. >> upload.mml
%GREP% -v Include < %1 >> upload.mml
goto exit
:noopt

copy base.mml upload.mml
call mmlmake.bat tokoroten.h
call mmlmake.bat 001.mml
call mmlmake.bat 002.mml 48:1:1
call mmlmake.bat 003.mml 64:1:1
call mmlmake.bat 004.mml 116:1:1
call mmlmake.bat 005.mml 131:1:1
call mmlmake.bat 006.mml 178:1:1
call mmlmake.bat 007.mml 194:1:1
call mmlmake.bat 008.mml 246:1:1
call mmlmake.bat 009.mml 262:1:1
call mmlmake.bat 010.mml 274:1:1
call mmlmake.bat 011.mml 282:1:1
call mmlmake.bat 012.mml 295:1:1
call mmlmake.bat 013.mml 305:2:1
call mmlmake.bat 014.mml 330:1:1
call mmlmake.bat 015.mml 362:1:1
call mmlmake.bat 016.mml 375:1:1
call mmlmake.bat 017.mml 383:1:1
call mmlmake.bat 018.mml 396:1:1
call mmlmake.bat 019.mml 406:2:1
call mmlmake.bat 020.mml 431:1:1
call mmlmake.bat 021.mml 463:1:1
call mmlmake.bat 022.mml 471:1:1
call mmlmake.bat 023.mml 487:1:1
call mmlmake.bat 024.mml 511:1:1
call mmlmake.bat 025.mml 539:1:1
call mmlmake.bat 026.mml 579:1:1
call mmlmake.bat 027.mml 626:1:1
call mmlmake.bat 028.mml 642:1:1
call mmlmake.bat 029.mml 702:1:1
call mmlmake.bat 030.mml 710:1:1

echo End >> upload.mml
call mmlmake.bat tokoroten.cfg

echo. >> upload.mml
echo /////////////////////////////////////////////////////// >> upload.mml
echo // 7zip + base64 files (work files)>> upload.mml
echo /////////////////////////////////////////////////////// >> upload.mml

del tokoroten.b64
del tokoroten.7z
%ZIP% a tokoroten.7z 0*.mml tokoroten.mml tokoroten.cfg tokoroten.h *.bat *.pl *.txt
%BASE% <tokoroten.7z>tokoroten.b64
type tokoroten.b64 >> upload.mml

:exit
