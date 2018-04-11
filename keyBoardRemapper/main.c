#include <stdio.h>
#include <windows.h>

//registry path HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Keyboard Layout

/*
 
 00000000 00000000 02000000 00003A00 00000000
 
 
    The first 16 zeros are just there to waste space.
    The “02” represents how many keys you are going to re-map plus 1. (It really represents the length of the data, but whatever)
    The  “0000” before the 3A000 is the key we actually want Windows to map TO, which in this case is nothing, or 0.
    The  “3A00” is the key we are mapping from, in this case the caps lock key.
    The next 8 zeros are there to waste space as the null terminator.
    You can map between multiple keys by incrementing the “02” and then adding another block after the 3rd byte. 
    ref: https://www.howtogeek.com/howto/windows-vista/disable-caps-lock-key-in-windows-vista/
 
    http://www.ee.bgu.ac.il/~microlab/MicroLab/Labs/ScanCodes.htm  	 
 */

int main() {
    HKEY hkey;
    BYTE * b[0x1];
    b[0] = 1;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Keyboard Layout", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &hkey);
    RegSetValueEx(hkey, L"test", 0, REG_BINARY, b, 0x1);
    return (0);
}
