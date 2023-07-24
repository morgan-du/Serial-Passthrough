#include "mbed.h"

#define PC_BAUDRATE     115200
#define DEV_BAUDRATE    115200

UnbufferedSerial  pc(USBTX, USBRX);
UnbufferedSerial  dev(D1, D0);

// Low active Reset for RYLR998
DigitalOut dev_rst(D2, 1);

DigitalOut led1(LED1);
DigitalOut led2(LED2);

void dev_recv()
{
    char c;

    led1 = !led1;
    while(dev.readable()) {
        dev.read(&c, 1);
        pc.write(&c, 1);
    }
}

void pc_recv()
{
    char c;

    led2 = !led2;
    while(pc.readable()) {
        pc.read(&c, 1);
        dev.write(&c, 1);
    }
}

int main()
{
    pc.baud(PC_BAUDRATE);
    dev.baud(DEV_BAUDRATE);

    printf("Starting pass-through firmware...\r\n");
    pc.attach(&pc_recv, SerialBase::RxIrq);
    dev.attach(&dev_recv, SerialBase::RxIrq);

    while(1)
        sleep();
}
