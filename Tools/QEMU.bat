@echo off
::cd ..

set qemu="C:\Program Files\qemu\qemu-system-i386.exe"
set disk="D:\Projets\OS\System\VMware\Disk.vmdk"

%qemu% ^
    -m 1G ^
    -k en ^
    -name System ^
    -display gtk ^
    -vga vmware ^
    -soundhw ac97 ^
    -net nic ^
    -usb ^
    -no-reboot ^
    -snapshot ^
    %disk%

:: -gdb tcp::1234 ^
:: -S ^