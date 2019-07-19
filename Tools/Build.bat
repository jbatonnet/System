@echo off
cd ..

:: Copy files
Tools\VMware\VDDK\VMware-mount Z: VMware\Disk.vmdk
xcopy /E /Y Root\* Z:\
Tools\VMware\VDDK\VMware-mount /d /f Z: