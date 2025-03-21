/*
Emmett Stavnitzky 400410510
Luke Tory 400368090
Devan Assi 400388918
Fech Agbassi 400380887
*/
#include "field_device.h"

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n------------------------\n"
    + group_name + " : " + device_name + "\n------------------------\n\n"); 
  
  Wire.begin();
  Wire.beginTransmission(ADDR);
  Wire.endTransmission();
  delay(300);

  light_sensor.begin(a_gain, a_time);

  Serial.println("Ready for LoRa connection!");
  
  Serial_0.begin(9600, SERIAL_8N1, 16, 17);
  Transceiver.init();
  Transceiver.SetAddressH(1);
  Transceiver.SetAddressL(1);
  Transceiver.SetAirDataRate(ADR_9600);
  Transceiver.SetChannel(TRANSCEIVER_CHANNEL);
  Transceiver.SetMode(EBYTE_MODE_NORMAL);
  Transceiver.SetTransmitPower(OPT_TP20);
  Transceiver.SaveParameters(PERMANENT);
  Transceiver.PrintParameters();
  
 //  Initializing IO port for MCP23017 IO expansion bus
  mcp.init();
  mcp.portMode(MCP23017Port::A, 0); // Configuring port A as OUTPUT
  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);  //Resetting port A 
}



void loop() {

  if(millis() - start_time > POLLING_PERIOD){
    
    //Temp sensor
    Wire.beginTransmission(ADDR);
    Wire.write(TMP_CMD);
    Wire.endTransmission();
    delay(100);

    Wire.requestFrom(ADDR, 2);

    char data[2];
    if(Wire.available() == 2){
      data[0] = Wire.read();
      data[1] = Wire.read();
    }

    temp = ((data[0] * 256.0) + data[1]);
    temp_c = ((175.72 * temp) / 65536.0) - 46.85;
    
    //Sample light sensor
    AsyncAPDS9306Data light_data = light_sensor.syncLuminosityMeasurement();
  
    //Calculate luminosity
    lux = light_data.calculateLux();

    //Format data as a JSON string
    String formatted_data = "{ \"" + group_name + "\": { \"" + device_name + "\": { \"Temp\": \"" 
        + String(temp_c) + "\", \"Luminosity\": \"" + String(lux) + "\" } } }" + '\n';
      
    Serial.println("Prepared LoRa message: " + formatted_data); 
    Serial2.println(formatted_data);
    Serial.println("LoRa sent!");
    
    start_time = millis();
  }

}
