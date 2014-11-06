#include "MyTRex.h"
#include "MyStatusDataPacket.h"
#include "MyI2C.h"
#include "wait.h"

using namespace TRexLib;

static const int REMOTE_ADDRESS = 0x07;
static const char * DEVICE = "/dev/i2c-1";

int main() {
    printf("Sizeof char: %d\r\n", sizeof(char));
    printf("Sizeof int: %d\r\n", sizeof(int));

    Serial pc;

    // We need to supply the device path
    MyI2C i2c(DEVICE, REMOTE_ADDRESS);
    
    MyTRex trex(&i2c, REMOTE_ADDRESS);

    // Read the status of the device
    MyStatusDataPacket status;
    if (trex.readStatus(&status)) {
        pc.printf("Startbyte: %#x\r\n", status.getStartByte());
        pc.printf("Errorflags: %#x\r\n", status.getErrorFlags());
        pc.printf("Battery Voltage: %.2fV\r\n", status.getBatteryVoltage());
        pc.printf("Left Motor Current: %.2fA\r\n", status.getMotorCurrent(LEFT));
        pc.printf("Right Motor Current: %.2fA\r\n", status.getMotorCurrent(RIGHT));
        pc.printf("Left Encoder Count: %d\r\n", status.getEncoderCount(LEFT));
        pc.printf("Right Encoder Count: %d\r\n", status.getEncoderCount(RIGHT));
        AcceleroMeter accel = status.getAcceleroMeter();
        pc.printf("AcceleroMeter [x, y, z]: [%d, %d, %d]\r\n", accel.x, accel.y, accel.z);
        Impact impact = status.getImpact();
        pc.printf("Impact [x, y, z]: [%d, %d, %d]\r\n", impact.x, impact.y, impact.z);
    } else {
        pc.printf("Could not read status\r\n");
    }
    
    pc.printf("Done\r\n");

    return 0;
}
