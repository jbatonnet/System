@echo off
cd ..

:: Stop virtual machine
Tools\VMware\vmrun -T player stop "VMware\System.vmx"

:: Copy files
Tools\VMware\VDDK\VMware-mount Z: VMware\Disk.vmdk
xcopy /E /Y Root\* Z:\
Tools\VMware\VDDK\VMware-mount /d /f Z:

:: Run virtual machine
Tools\VMware\vmrun -T player start "VMware\System.vmx"