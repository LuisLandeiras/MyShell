#include "shell.h"

int isjpeg(int fileDescriptor){
    unsigned char b[4];
    read(fileDescriptor, b, 4);
    lseek(fileDescriptor, 0, SEEK_SET);
    close(fileDescriptor);
    if(b[0] == 0xff || b[1] == 0xd8 || b[2] == 0xff || b[3] == 0xe1){
        return 1;
    }
    return 0;
}
