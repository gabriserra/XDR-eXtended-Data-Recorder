#ifndef __GY521_H__
#define __GY521_H__

#include "MPU6050.h"
#include "I2Cdev.h"

//------------------------------------------------------------------------------
// GLOBAL STRUCTURES
//------------------------------------------------------------------------------

typedef struct acc_raw {
	int16_t ax;
	int16_t ay;
	int16_t az;
} acc_raw_t;

typedef struct acc_g {
	float ax;
	float ay;
	float az;
	float v;
} acc_g_t;

typedef struct gy_raw {
	int16_t gx;
	int16_t gy;
	int16_t gz;
} gy_raw_t;

typedef struct gy_g {
	float gx;
	float gy;
	float gz;
} gy_g_t;

typedef struct sensor_data_raw {
	uint32_t seq_num;
	int16_t ax;
	int16_t ay;
	int16_t az;
	int16_t gx;
	int16_t gy;
	int16_t gz;
} sensor_data_raw_t;

typedef struct sensor_data_g {
	uint32_t seq_num;
	float ax;
	float ay;
	//float az;
	//float v;
	//float gx;
	//float gy;
	float gz;
} sensor_data_g_t;

//------------------------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------------------------

#define NUMBER_OF_AXIS			3
#define NUMBER_OF_VARIABLES		6

//------------------------------------------------------------------------------
// CLASS DEFINITION
//------------------------------------------------------------------------------

class GY521 {
	//--------------------------------------------------------------------------
	// PRIVATE MEMBERS AND FUNCTIONS
	//--------------------------------------------------------------------------
	private:
		//----------------------------------------------------------------------
		// PRIVATE MEMBERS
		//----------------------------------------------------------------------
	
		MPU6050 acc_gy;
		int MPU;
		int mean_ax, mean_ay, mean_az, mean_gx, mean_gy, mean_gz, state;
		int ax_offset, ay_offset, az_offset, gx_offset, gy_offset, gz_offset;
   
		sensor_data_raw_t all;
		sensor_data_g_t all_d;

		acc_raw_t acc;
		acc_g_t acc_d;

		gy_raw_t gy;
		gy_g_t gy_d;

		int16_t tmp;
		float tmp_d;
	
		float vx, vy, vz;
   
		//----------------------------------------------------------------------
		// PRIVATE FUNCTIONS
		//----------------------------------------------------------------------

    //----------------------------------------------------------------------
    // ACC TO G:
    //----------------------------------------------------------------------

    void raw2g(uint32_t);

		//----------------------------------------------------------------------
		// ACC TO G:
		//----------------------------------------------------------------------

		void acc2g();

		//----------------------------------------------------------------------
		// GY TO G:
		//----------------------------------------------------------------------

		void gy2g();
	
		//----------------------------------------------------------------------
		// COMPUTE VELOCITY: Compute velocity from accelerometer data
		//----------------------------------------------------------------------
	
		float computeVelocity();

		//----------------------------------------------------------------------
		// READ ALL: Read data from all the sensors
		//----------------------------------------------------------------------
	
		void readAll();
	
		//----------------------------------------------------------------------
		// READ ACC: Read data from accelerometer sensor
		//----------------------------------------------------------------------
	
		void readAcc();
	
		//----------------------------------------------------------------------
		// READ GY: Read data from gyroscope sensor
		//----------------------------------------------------------------------
	
		void readGy();
	
		//----------------------------------------------------------------------
		// READ TMP: Read data from temperature sensor
		//----------------------------------------------------------------------
	
		void readTmp();
	
		//----------------------------------------------------------------------
		// MEAN SENSORS:
		//----------------------------------------------------------------------
	
		void meansensors();
	
		//----------------------------------------------------------------------
		// CALIBRATION:
		//----------------------------------------------------------------------
	
		void calibration();
	
	//--------------------------------------------------------------------------
	// PUBLIC MEMBERS AND FUNCTIONS
	//--------------------------------------------------------------------------
	public:
    //----------------------------------------------------------------------
    // PUBLIC MEMBERS
    //----------------------------------------------------------------------
    
    unsigned long previous_t;

		//----------------------------------------------------------------------
		// PUBLIC FUNCTIONS
		//----------------------------------------------------------------------
	
		//----------------------------------------------------------------------
		// GY521: Constructor of the class
		//----------------------------------------------------------------------

		GY521(const int mpu);
	
		//----------------------------------------------------------------------
		// INIT: 	Initialize the connection with the sensor
		//----------------------------------------------------------------------
	
		void init();
	
		//----------------------------------------------------------------------
		// CALIBRATE: 	Calibrate acceleromter and gyroscope
		//----------------------------------------------------------------------
	
		void calibrate();
	
		//----------------------------------------------------------------------
		// PRINT ALL: Print data from all the sensors
		//----------------------------------------------------------------------
	
		void printAll();
	
		//----------------------------------------------------------------------
		// PRINT ACC: Print data from accelerometer sensor
		//----------------------------------------------------------------------
	
		void printAcc();
	
		//----------------------------------------------------------------------
		// PRINT GY: Print data from accelerometer sensor
		//----------------------------------------------------------------------
	
		void printGy();

		//----------------------------------------------------------------------
		// PRINT TMP: Print data from accelerometer sensor
		//----------------------------------------------------------------------
  
		void printTmp();

		//----------------------------------------------------------------------
		// PRINT ALL DOUBLE: Print data from all the sensors
		//----------------------------------------------------------------------

		void printAllDouble();

		//----------------------------------------------------------------------
		// PRINT ACC DOUBLE: Print data from accelerometer sensor
		//----------------------------------------------------------------------

		void printAccDouble();

		//----------------------------------------------------------------------
		// PRINT GY DOUBLE: Print data from accelerometer sensor
		//----------------------------------------------------------------------

		void printGyDouble();

		//----------------------------------------------------------------------
		// PRINT TMP DOUBLE: Print data from accelerometer sensor
		//----------------------------------------------------------------------

		void printTmpDouble();
	
		//----------------------------------------------------------------------
		// GET ALL: Get data from all the sensors
		//----------------------------------------------------------------------
	
		sensor_data_raw_t getAll();
	
		//----------------------------------------------------------------------
		// GET ACC: Get data from accelerometer sensor
		//----------------------------------------------------------------------
	
		acc_raw_t getAcc();
	
		//----------------------------------------------------------------------
		// GET GY: Get data from accelerometer sensor
		//----------------------------------------------------------------------
	
		gy_raw_t getGy();
	
		//----------------------------------------------------------------------
		// GET TMP: Get data from accelerometer sensor
		//----------------------------------------------------------------------
	
		int16_t getTmp();
	
		//----------------------------------------------------------------------
		// GET ALL DOUBLE: Get data from all the sensors
		//----------------------------------------------------------------------
	
		sensor_data_g_t GY521::getAllDouble(uint32_t seq_num);
	
		//----------------------------------------------------------------------
		// GET ACC DOUBLE: Get data from accelerometer sensor
		//----------------------------------------------------------------------
	
		acc_g_t GY521::getAccDouble();
	
		//----------------------------------------------------------------------
		// GET GY DOUBLE: Get data from accelerometer sensor
		//----------------------------------------------------------------------
	
		gy_g_t GY521::getGyDouble();

		//----------------------------------------------------------------------
		// GET TMP DOUBLE: Get data from accelerometer sensor
		//----------------------------------------------------------------------
	  
		float getTmpDouble();
};

#endif
