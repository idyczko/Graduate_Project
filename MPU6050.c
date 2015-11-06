/*
 * MP6050.c
 *
 * Created: 2015-09-25 10:58:06
 *  Author: Igor
 */ 

#include "MPU6050.h"


void MPU_self_test(unsigned char mpuAdress){
		char buf[17]="                ";
		TWI_start();
		
		TWI_check_ack(mpuAdress);
		
		TWI_write_data(0x75);
		
		TWI_repeated_start();
		
		TWI_read_address(mpuAdress|0x01);
		
		char response = TWI_read_data();
		
		sprintf(buf,"Response:  %x",response);
		LCD_WriteText(buf);
		
		TWI_stop();
}

void MPU_read_adress(unsigned char mpuAdress, unsigned char registerAdress, unsigned char* variable){
	TWI_start();
	
	TWI_check_ack(mpuAdress);
	
	TWI_write_data(registerAdress);
	
	TWI_repeated_start();
	
	TWI_read_address(mpuAdress|0x01);
	
	*variable = TWI_read_data();
	TWI_stop();
	
	}
	
void MPU_write_adress(unsigned char mpuAdress, unsigned char registerAdress, unsigned char value){
	TWI_start();
	
	TWI_check_ack(mpuAdress);
	
	TWI_write_data(registerAdress);
	
	TWI_write_data(value);

	TWI_stop();
	
}

void Get_Accel_Values(unsigned char MPU6050_ADDRESS)
{
	MPU_read_adress(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, &ACCEL_XOUT_H);
	MPU_read_adress(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_L, &ACCEL_XOUT_L);
	MPU_read_adress(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_H, &ACCEL_YOUT_H);
	MPU_read_adress(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_L, &ACCEL_YOUT_L);
	MPU_read_adress(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_H, &ACCEL_ZOUT_H);
	MPU_read_adress(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_L, &ACCEL_ZOUT_L);
	
	ACCEL_XOUT = ((ACCEL_XOUT_H<<8)|ACCEL_XOUT_L);
	ACCEL_YOUT = ((ACCEL_YOUT_H<<8)|ACCEL_YOUT_L);
	ACCEL_ZOUT = ((ACCEL_ZOUT_H<<8)|ACCEL_ZOUT_L);
}
	
void Setup_MPU6050(unsigned char MPU6050_ADDRESS, unsigned char SCALE)
	{
		//Sets sample rate to 8000/1+7 = 1000Hz
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, 0x07);
		//Disable FSync, 256Hz DLPF
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_CONFIG, 0x00);
		//Disable gyro self tests, scale of 500 degrees/s
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 0b00001000);
		//Disable accel self tests, scale of +-2g, no DHPF
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, SCALE);
		//Freefall threshold of |0mg|
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_FF_THR, 0x00);
		//Freefall duration limit of 0
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_FF_DUR, 0x00);
		//Motion threshold of 0mg
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_MOT_THR, 0x00);
		//Motion duration of 0s
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, 0x00);
		//Zero motion threshold
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, 0x00);
		//Zero motion duration threshold
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, 0x00);
		//Disable sensor output to FIFO buffer
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, 0x00);
		
		//AUX I2C setup
		//Sets AUX I2C to single master control, plus other config
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, 0x00);
		//Setup AUX I2C slaves
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_ADDR, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_REG, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_CTRL, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_ADDR, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_REG, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_CTRL, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_ADDR, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_REG, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_CTRL, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_ADDR, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_REG, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DO, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DI, 0x00);
		
		//MPU6050_RA_I2C_MST_STATUS //Read-only
		//Setup INT pin and AUX I2C pass through
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, 0x00);
		//Enable data ready interrupt
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, 0x00);
		
		//MPU6050_RA_DMP_INT_STATUS        //Read-only
		//MPU6050_RA_INT_STATUS 3A        //Read-only
		//MPU6050_RA_ACCEL_XOUT_H         //Read-only
		//MPU6050_RA_ACCEL_XOUT_L         //Read-only
		//MPU6050_RA_ACCEL_YOUT_H         //Read-only
		//MPU6050_RA_ACCEL_YOUT_L         //Read-only
		//MPU6050_RA_ACCEL_ZOUT_H         //Read-only
		//MPU6050_RA_ACCEL_ZOUT_L         //Read-only
		//MPU6050_RA_TEMP_OUT_H         //Read-only
		//MPU6050_RA_TEMP_OUT_L         //Read-only
		//MPU6050_RA_GYRO_XOUT_H         //Read-only
		//MPU6050_RA_GYRO_XOUT_L         //Read-only
		//MPU6050_RA_GYRO_YOUT_H         //Read-only
		//MPU6050_RA_GYRO_YOUT_L         //Read-only
		//MPU6050_RA_GYRO_ZOUT_H         //Read-only
		//MPU6050_RA_GYRO_ZOUT_L         //Read-only
		//MPU6050_RA_EXT_SENS_DATA_00     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_01     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_02     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_03     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_04     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_05     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_06     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_07     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_08     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_09     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_10     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_11     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_12     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_13     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_14     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_15     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_16     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_17     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_18     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_19     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_20     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_21     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_22     //Read-only
		//MPU6050_RA_EXT_SENS_DATA_23     //Read-only
		//MPU6050_RA_MOT_DETECT_STATUS     //Read-only
		
		//Slave out, dont care
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_DO, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_DO, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_DO, 0x00);
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_DO, 0x00);
		//More slave config
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
		//Reset sensor signal paths
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
		//Motion detection control
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, 0x00);
		//Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, 0x00);
		//Sets clock source to gyro reference w/ PLL
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 0b00000010);
		//Controls frequency of wakeups in accel low power mode plus the sensor standby modes
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, 0x00);
		//MPU6050_RA_BANK_SEL            //Not in datasheet
		//MPU6050_RA_MEM_START_ADDR        //Not in datasheet
		//MPU6050_RA_MEM_R_W            //Not in datasheet
		//MPU6050_RA_DMP_CFG_1            //Not in datasheet
		//MPU6050_RA_DMP_CFG_2            //Not in datasheet
		//MPU6050_RA_FIFO_COUNTH        //Read-only
		//MPU6050_RA_FIFO_COUNTL        //Read-only
		//Data transfer to and from the FIFO buffer
		MPU_write_adress(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, 0x00);
		//MPU6050_RA_WHO_AM_I             //Read-only, I2C address
		
		//printf("\nMPU6050 Setup Complete");
	}
