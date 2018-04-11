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



int main(void) {
    HKEY hkey;
    char registryKeyValue[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    size_t size = sizeof (registryKeyValue); 
    LONG result_open, result_close, result_write;

    printf("Opening Key...\n");
    result_open = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            "SYSTEM\\CurrentControlSet\\Control\\Keyboard Layout",
            0, KEY_WRITE, &hkey);

    if (result_open != ERROR_SUCCESS) {
        if (result_open == ERROR_FILE_NOT_FOUND) {
            printf("Not found\n");
        } else {
            printf("Error Opening Key\n");
        }
    } else {
        printf("SUCCESS!!!\n");
    }

    printf("Writing Value named testval\n");
    result_write = RegSetValueEx(hkey, "bartolomew", 0, REG_BINARY, registryKeyValue, size);
    if (result_write != ERROR_SUCCESS) {
        printf("Error Writing Value\n");
    } else {
        printf("SUCCESS!!!\n");
    }
    printf("Closing Key...\n");
    result_close = RegCloseKey(hkey);
    if (result_close != ERROR_SUCCESS) {
        printf("Error Closing Key\n");
    } else {
        printf("SUCCESS!!!!\n");
    }

    return 0;
}