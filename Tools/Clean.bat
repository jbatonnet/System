@echo off

:: Clean temporary files
forfiles /s /p ..\Source /m *.tlog /c "cmd /c del /q @path"
forfiles /s /p ..\Source /m *.asm /c "cmd /c del /q @path"
forfiles /s /p ..\Source /m *.obj /c "cmd /c del /q @path"

:: Clean directories
forfiles /s /p ..\Source /m obj /c "cmd /c rmdir /q /s @path"
forfiles /s /p ..\Source /m bin /c "cmd /c rmdir /q /s @path"
forfiles /s /p ..\Source /m Debug /c "cmd /c del /q /s @path\*"
forfiles /s /p ..\Source /m Debug /c "cmd /c attrib -s -h @path"
forfiles /s /p ..\Source /m Debug /c "cmd /c attrib +s +h @path"
forfiles /s /p ..\Source /m Release /c "cmd /c del /q /s @path\*"
forfiles /s /p ..\Source /m Release /c "cmd /c attrib -s -h @path"
forfiles /s /p ..\Source /m Release /c "cmd /c attrib +s +h @path"
forfiles /s /p ..\Source /m x64 /c "cmd /c del /q /s @path\*"
forfiles /s /p ..\Source /m x64 /c "cmd /c attrib -s -h @path"
forfiles /s /p ..\Source /m x64 /c "cmd /c attrib +s +h @path"
forfiles /s /p ..\Source /m ARM /c "cmd /c del /q /s @path\*"
forfiles /s /p ..\Source /m ARM /c "cmd /c attrib -s -h @path"
forfiles /s /p ..\Source /m ARM /c "cmd /c attrib +s +h @path"

:: Clean VMware
del /q /s ..\VMware\*.log
del /q /s ..\VMware\*.dmp

:: Clean Visual Studio files
forfiles /s /p ..\Source /m *.sdf /c "cmd /c del /q @path"