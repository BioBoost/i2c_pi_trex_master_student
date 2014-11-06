#include "MyI2C.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>          //O_RDWR
#include <stdio.h>          //perror

namespace TRexLib{
    
    /*
     * Pointer to write function used for i2c communication.
     * Also see http://linux.die.net/man/2/write
     */
    ssize_t (* pi_i2c_write)(int, const void *, size_t) = write;
    
    /*
     * Pointer to read function used for i2c communication.
     * Also see http://linux.die.net/man/2/read
     */
    ssize_t (* pi_i2c_read)(int, void *, size_t) = read;
}