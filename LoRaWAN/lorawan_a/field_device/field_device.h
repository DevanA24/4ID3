/*
Emmett Stavnitzky 400410510
Luke Torry 400368090
Devan Assi 400388918
Fech Agbassi 400380887
*/
// Libraries
#include <TheThingsNetwork.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//  Macros
#define DHTPIN 2
#define DHTTYPE DHT11
#define POLLING_PERIOD 2000
#define GROUP_NAME "Group5"
#define DEVICE_NAME "Device5"

DHT_Unified dht(DHTPIN, DHTTYPE);
#define lora_serial Serial1
#define debug_serial Serial

// Set your AppEUI and AppKey
#define FREQUENCY_PLAN TTN_FP_US915
const char *app_eui = "0000000000000000";
const char *app_key = "A0816468EF00CA5DF8361044B88AB574";
TheThingsNetwork ttn(lora_serial, debug_serial, FREQUENCY_PLAN);

unsigned long start_time = millis();
