#include "mpu6050.h"

static void MPU_WriteReg(uint8_t reg, uint8_t d)
{
    uint8_t Data[] = {reg, d};
    I2C1_GenStart();
    I2C1_SendAddress(MPU_ADDRESS, 0);
    I2C1_MasterSendData(Data, 2);
    I2C1_GenStop();
}

uint8_t MPU_Whoami()
{
    uint8_t data = 0x75; // WHOAMI Register Address
    uint8_t check;
    I2C1_GenStart();
    I2C1_SendAddress(MPU_ADDRESS, 0);
    I2C1_MasterSendData(&data, sizeof(data));
    // I2C1_GenStop();
    I2C1_GenStart();
    I2C1_SendAddress(MPU_ADDRESS, 1);
    I2C1_MasterReceiveData(&check, sizeof(check));
    return check;
}

void MPU_Init()
{
    MPU_WriteReg(MPU_REG_PWR_MGMT_1, 0); // Setting all the bit to 0 so that sensor wakeup

    MPU_WriteReg(MPU_REG_SMPLRT_DIV, 0x7U); // Setting sampling rate to 7 to make sampling rate to 1KHz

    MPU_WriteReg(MPU_REG_ACCEL_CONFIG, 0x0U); // Setting Scale Range to 250degree/s

    MPU_WriteReg(MPU_REG_GYRO_CONFIG, 0x0U); // Setting Scale Range to 2g
}

void MPU_Read_Accel()
{
    uint8_t reg = MPU_REG_ACCEL_XOUT_H;
    uint8_t AccelData[6];

    I2C1_GenStart();
    I2C1_SendAddress(MPU_ADDRESS, 0);
    I2C1_MasterSendData(&reg, 1);
    I2C1_GenStart();
    I2C1_SendAddress(MPU_ADDRESS, 1);
    I2C1_MasterReceiveData(AccelData, 6);
}