#ifndef CIRO_SERIALSICURITY_H
#define CIRO_SERIALSICURITY_H



#include<Arduino.h>
#include<BLEServer.h>
#include<BLECharacteristic.h>
#include<BLEDevice.h>
#include<DHT.h> 


class ciro_SERIALSICURITY {
    public:
    ciro_SERIALSICURITY();     // costruttore di default
    ciro_SERIALSICURYTY(int8_t pinDHT22);      //  costruttore con sensore di temperatura 
       // CONFIGURAZIONE DEL BLE per il controllo da remoto  
       void setupBLE(const char* deviceName, const char* UUID, const char* characteristicUUID);
       // CONFIGURAZIONI HARDWARE
      void SetTiltAndBuzzer(int8_t tiltPin, int8_t buzzerPin);
      void SetMotionSensor(int8_t motionPin);
      void setMotor(int8_t relayMotor);
      void setBuzzer();
      // protezione termica 

    void setTemperatureThreshold(float threshold);
    void checkTemperatureAndAlert(); // controlla la temperatura e da l'allarme 
    void checkTildAndBuzzer(); // controlla l'inclinazione e manda l'allarme 
    void ckeckMotionAndBuzzer();// controlla il movimento e manda l'allarme se è attivato 
    void blockEngineSefely(); // blocca la pompa motore in caso di guasto 
    void receiveBLEMessage();
    // comunicazione del BLE SERIAL
    void sendBLEData();


   
   private: 
      
      std::string message;
      int8_t _pinDHT22;  //PIN del sensore  dht22
      int8_t _tiltPin; // pin sensore di inclinazione 
      int8_t _buzzerPin  // pin del buzzer
      int8_t _motionPin; // sensore di movimento 
      int8_t _relayMotor; // rele pin motore 
      int8_t _relayVentoARD; // rele pin ventola arduino
      int8_t _relaySirena; // relay sirena
      int8_t _relayPompaCarbu;
      
      
      int _humidity; //for the dht22
      float _temperatureDeg; //for the dht22
      float _temperatureThreshold; //for the dht22
      
  
   // variabili per il BLE
   BLEServer *bleServer;
   BLEService *bleService;
   BLECharacteristic *bleCharacteristic;

};

#endif
