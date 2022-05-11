#include "shell.h"

int isjpeg(int fileDescriptor){
    unsigned char b[4];
    read(fileDescriptor, b, 4);
    if(b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && b[3] == 0xe0){
        return 1;
    }
    return 0;
}