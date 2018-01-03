//------------------------------------------------------------------------------
// GY521: Contains the library useful to manage the Accelerometer.
//------------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>

#include "GY521.h"

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define	BUFFERSIZE		1000	//Amount of readings used to average, make it higher to get more precision but sketch will be slower  (default:1000)
#define ACC_DEADZONE	8     	//Acelerometer error allowed, make it lower to get more precision, but sketch may not converge  (default:8)
#define GY_DEADZONE		1     	//Giro error allowed, make it lower to get more precision, but sketch may not converge  (default:1)

#define GRAVITY       9.81

float	ACC_SENSITIVITY	= 16384;
float	GY_SENSITIVITY	= 131;

//------------------------------------------------------------------------------
// GY521: Constructors of the class
//------------------------------------------------------------------------------

GY521::GY521(const int mpu){
	MPU = mpu;
	acc_gy = MPU6050(MPU);
	state = 0;
}

//------------------------------------------------------------------------------
// ACC TO G:
//------------------------------------------------------------------------------

void GY521::acc2g() {
    acc_d.ax = acc.ax / ACC_SENSITIVITY;
    acc_d.ay = acc.ay / ACC_SENSITIVITY;
    acc_d.az = acc.az / ACC_SENSITIVITY;
}

//------------------------------------------------------------------------------
// GY TO G:
//------------------------------------------------------------------------------

void GY521::gy2g() {
    gy_d.gx = gy.gx / GY_SENSITIVITY;
    gy_d.gy = gy.gy / GY_SENSITIVITY;
    gy_d.gz = gy.gz / GY_SENSITIVITY;
}

//----------------------------------------------------------------------
// COMPUTE VELOCITY: Compute velocity from accelerometer data
//----------------------------------------------------------------------

float GY521::computeVelocity() {
	unsigned long current_t = millis();
	unsigned long delta = current_t - previous_t;
	previous_t = current_t;
  float dt = delta/1000.00;
	
	vx += acc_d.ax * GRAVITY * dt;
	vy += acc_d.ay * GRAVITY * dt;
	vz += (acc_d.az - 1) * GRAVITY * dt;
	
	return sqrt(pow(vx,2) + pow(vy,2) + pow(vz,2));
}

//------------------------------------------------------------------------------
// READ ALL: Read data from all the sensors
//------------------------------------------------------------------------------

void GY521::readAll() {
	Wire.beginTransmission(MPU);
	Wire.write(0x3B);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU, 14, true);
	
	acc.ax = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
	acc.ay = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	acc.az = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	tmp = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
	gy.gx = Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
	gy.gy = Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
	gy.gz = Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

//------------------------------------------------------------------------------
// READ ACC: Read data from accelerometer sensor
//------------------------------------------------------------------------------

void GY521::readAcc() {
	Wire.beginTransmission(MPU);
	Wire.write(0x3B);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU, 6, true);
	
	acc.ax = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
	acc.ay = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	acc.az = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
}

//------------------------------------------------------------------------------
// READ GY: Read data from gyroscope sensor
//------------------------------------------------------------------------------

void GY521::readGy() {
	Wire.beginTransmission(MPU);
	Wire.write(0x43);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU, 6, true);
	
	gy.gx = Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
	gy.gy = Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
	gy.gz = Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

//------------------------------------------------------------------------------
// READ TMP: Read data from temperature sensor
//------------------------------------------------------------------------------

void GY521::readTmp() {
	Wire.beginTransmission(MPU);
	Wire.write(0x41);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU, 2, true);
	
	tmp = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
}

//------------------------------------------------------------------------------
// MEAN SENSORS:
//------------------------------------------------------------------------------

void GY521::meansensors() {
	long i=0, buff_ax=0, buff_ay=0, buff_az=0, buff_gx=0, buff_gy=0, buff_gz=0;
	
	while (i<(BUFFERSIZE+101)){
		acc_gy.getMotion6(&acc.ax, &acc.ay, &acc.az, &gy.gx, &gy.gy, &gy.gz);
		
		if (i>100 && i<=(BUFFERSIZE+100)){
			buff_ax=buff_ax+acc.ax;
			buff_ay=buff_ay+acc.ay;
			buff_az=buff_az+acc.az;
			buff_gx=buff_gx+gy.gx;
			buff_gy=buff_gy+gy.gy;
			buff_gz=buff_gz+gy.gz;
		}
		
		if (i==(BUFFERSIZE+100)){
			mean_ax=buff_ax/BUFFERSIZE;
			mean_ay=buff_ay/BUFFERSIZE;
			mean_az=buff_az/BUFFERSIZE;
			mean_gx=buff_gx/BUFFERSIZE;
			mean_gy=buff_gy/BUFFERSIZE;
			mean_gz=buff_gz/BUFFERSIZE;
		}
		i++;
		delay(2); //Needed so we don't get repeated measures
	}
}

//------------------------------------------------------------------------------
// CALIBRATION:
//------------------------------------------------------------------------------

void GY521::calibration() {
	ax_offset=-mean_ax/8;
	ay_offset=-mean_ay/8;
	az_offset=(16384-mean_az)/8;
	
	gx_offset=-mean_gx/4;
	gy_offset=-mean_gy/4;
	gz_offset=-mean_gz/4;
	
	while (1){
		int ready=0;
		acc_gy.setXAccelOffset(ax_offset);
		acc_gy.setYAccelOffset(ay_offset);
		acc_gy.setZAccelOffset(az_offset);
		
		acc_gy.setXGyroOffset(gx_offset);
		acc_gy.setYGyroOffset(gy_offset);
		acc_gy.setZGyroOffset(gz_offset);
		
		meansensors();
		
		if (abs(mean_ax)<=ACC_DEADZONE)
			ready++;
		else
			ax_offset=ax_offset-mean_ax/ACC_DEADZONE;
		
		if (abs(mean_ay)<=ACC_DEADZONE)
			ready++;
		else
			ay_offset=ay_offset-mean_ay/ACC_DEADZONE;
		
		if (abs(16384-mean_az)<=ACC_DEADZONE)
			ready++;
		else
			az_offset=az_offset+(16384-mean_az)/ACC_DEADZONE;
		
		if (abs(mean_gx)<=GY_DEADZONE)
			ready++;
		else
			gx_offset=gx_offset-mean_gx/(GY_DEADZONE+1);
		
		if (abs(mean_gy)<=GY_DEADZONE)
			ready++;
		else
			gy_offset=gy_offset-mean_gy/(GY_DEADZONE+1);
		
		if (abs(mean_gz)<=GY_DEADZONE)
			ready++;
		else
			gz_offset=gz_offset-mean_gz/(GY_DEADZONE+1);
		
		if (ready==6)
			break;
	}
}

//------------------------------------------------------------------------------
// INIT: Initialize the connection with the sensor
//------------------------------------------------------------------------------

void GY521::init() {
	acc_gy.initialize();
}

//------------------------------------------------------------------------------
// CALIBRATE: 	Calibrate acceleromter and gyroscope
//------------------------------------------------------------------------------

void GY521::calibrate() {
  Serial.println(F("CALIBRATION STARTED"));
	delay(2000);
	acc_gy.setXAccelOffset(0);
	acc_gy.setYAccelOffset(0);
	acc_gy.setZAccelOffset(0);
	acc_gy.setXGyroOffset(0);
	acc_gy.setYGyroOffset(0);
	acc_gy.setZGyroOffset(0);
	
	if (state==0){
		meansensors();
		state++;
		delay(1000);
	}
	
	if (state==1) {
		calibration();
		state++;
		delay(1000);
	}
 Serial.println(F("CALIBRATION DONE"));
}

//------------------------------------------------------------------------------
// PRINT ALL: Print data from all the sensors
//------------------------------------------------------------------------------

void GY521::printAll() {
	//readAll();
	printAcc();
	printGy();
	Serial.println();
}

//------------------------------------------------------------------------------
// PRINT ACC: Print data from accelerometer sensor
//------------------------------------------------------------------------------

void GY521::printAcc() {
	Serial.print(F("Accelerometer:\t\t"));
	Serial.print(F("X = ")); 
	Serial.print(acc.ax);
	Serial.print(F("\t| Y = ")); 
	Serial.print(acc.ay);
	Serial.print(F("\t| Z = ")); 
	Serial.println(acc.az);
}

//------------------------------------------------------------------------------
// PRINT GY: Print data from accelerometer sensor
//------------------------------------------------------------------------------

void GY521::printGy() {
	Serial.print(F("Gyroscope:\t\t"));
	Serial.print(F("X = ")); 
	Serial.print(gy.gx);
	Serial.print(F("\t| Y = ")); 
	Serial.print(gy.gy);
	Serial.print(F("\t| Z = ")); 
	Serial.println(gy.gz);
}

//------------------------------------------------------------------------------
// PRINT TMP: Print data from accelerometer sensor
//------------------------------------------------------------------------------

void GY521::printTmp() {
	Serial.print(F("Temperature:\t\t")); 
	Serial.print(tmp / 340.00 + 36.53); 
	Serial.println(F(" C "));
}

//------------------------------------------------------------------------------
// PRINT ALL DOUBLE: Print data from all the sensors
//------------------------------------------------------------------------------

void GY521::printAllDouble(){
	//readAll();
  //acc2g();
  //gy2g();
	printAccDouble();
	printGyDouble();
	Serial.println();
}

//------------------------------------------------------------------------------
// PRINT ACC DOUBLE: Print data from accelerometer sensor
//------------------------------------------------------------------------------

void GY521::printAccDouble() {
	Serial.print(F("Accelerometer (g):\t"));
	Serial.print(F("X = "));
	Serial.print(acc_d.ax, 4);
	Serial.print(F("\t| Y = "));
	Serial.print(acc_d.ay, 4);
	Serial.print(F("\t| Z = "));
	Serial.println(acc_d.az, 4);
  Serial.print(F("Velocity :\t"));
  Serial.println(acc_d.v, 4);
}

//------------------------------------------------------------------------------
// PRINT GY DOUBLE: Print data from accelerometer sensor
//------------------------------------------------------------------------------

void GY521::printGyDouble() {
	Serial.print(F("Gyroscope (g):\t\t"));
	Serial.print(F("X = "));
	Serial.print(gy_d.gx, 4);
	Serial.print(F("\t| Y = "));
	Serial.print(gy_d.gy, 4);
	Serial.print(F("\t| Z = "));
	Serial.println(gy_d.gz, 4);
}

//------------------------------------------------------------------------------
// PRINT TMP DOUBLE: Print data from accelerometer sensor
//------------------------------------------------------------------------------

void GY521::printTmpDouble() {
	Serial.print(F("Temperature:\t\t"));
	Serial.print(tmp_d / 340.00 + 36.53,4);
	Serial.println(F(" C "));
}

//------------------------------------------------------------------------------
// GET ALL: Get data from all the sensors
//------------------------------------------------------------------------------

sensor_data_raw_t GY521::getAll() {
	readAll();
	all.ax = acc.ax;
	all.ay = acc.ax;
	all.az = acc.az;
	all.gx = gy.gx;
	all.gy = gy.gy;
	all.gz = gy.gz;
  
	return all;
}

//------------------------------------------------------------------------------
// GET ACC: Get data from accelerometer sensor
//------------------------------------------------------------------------------

acc_raw_t GY521::getAcc() {
	readAcc();
	return acc;
}

//------------------------------------------------------------------------------
// GET GY: Get data from accelerometer sensor
//------------------------------------------------------------------------------

gy_raw_t GY521::getGy() {
	readGy();
	return gy;
}

//------------------------------------------------------------------------------
// GET TMP: Get data from accelerometer sensor
//------------------------------------------------------------------------------

int16_t GY521::getTmp() {
	readTmp();
	return tmp;
}

//------------------------------------------------------------------------------
// GET ALL DOUBLE: Get data from all the sensors
//------------------------------------------------------------------------------

sensor_data_g_t GY521::getAllDouble() {
	readAll();
	acc2g();
	gy2g();
	all_d.ax = acc_d.ax;
	all_d.ay = acc_d.ax;
	all_d.az = acc_d.az;
	all_d.v = computeVelocity();
	all_d.gx = gy_d.gx;
	all_d.gy = gy_d.gy;
	all_d.gz = gy_d.gz;
  
	return all_d;
}

//------------------------------------------------------------------------------
// GET ACC DOUBLE: Get data from accelerometer sensor
//------------------------------------------------------------------------------

acc_g_t GY521::getAccDouble() {
	readAcc();
	acc2g();
	acc_d.v = computeVelocity();
	return acc_d;
}

//------------------------------------------------------------------------------
// GET GY DOUBLE: Get data from accelerometer sensor
//------------------------------------------------------------------------------

gy_g_t GY521::getGyDouble() {
	readGy();
	gy2g();
	return gy_d;
}

//------------------------------------------------------------------------------
// GET TMP DOUBLE: Get data from accelerometer sensor
//------------------------------------------------------------------------------

float GY521::getTmpDouble() {
	readTmp();
	tmp_d = (float) tmp;
	return tmp_d;
}
