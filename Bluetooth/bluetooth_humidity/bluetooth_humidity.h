//Libraries
#include <Arduino.h>
#include <Wire.h>
#include <AsyncAPDS9306.h>
#include "BluetoothSerial.h"

//IIC Addresses for Temperature Sensor
#define ADDR (byte)(0x40)
#define TMP_CMD (byte)(0xF5)

//Sample frequency
#define DELAY_BETWEEN_SAMPLES_MS 5000

//Device information
String group_name = "Group5";
String device_name = "Device5";
BluetoothSerial bluetooth_serial;


//Instantiating sensor object and configuration
AsyncAPDS9306 light_sensor;
const APDS9306_ALS_GAIN_t apds_gain = APDS9306_ALS_GAIN_1;
const APDS9306_ALS_MEAS_RES_t apds_time = APDS9306_ALS_MEAS_RES_16BIT_25MS;
