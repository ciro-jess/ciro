#include "ciro_SERIALSICURITY.h"


// costruttore di default, inizia la classe senza parametri 
ciro_SERIALSICURITY::ciro_SERIALSICURITY() {     //costruttore 1 
  _pinDHT22= -1;   //inizializza a -1 il pin e indica che non è
  _temperatureThreshold = 40.0;// soglia di temperatura bne precisa 
}
// costruttore con i parametri del DHT22
ciro_SERIALSICURITY::ciro_SERIALSICURITY(int8_t pinDHT22) {
  _pinDHT22 = pinDHT22;    //costruttore ch3e consente di inizializzare il pin specifico dove è collegato il sensore
  _temperatureThreshold = 40.0;
}

void ciro_SERIALSICURITY::setupBLE(const char* deviceName, const char* UUID, const char* characteristicUUID){
  BLEDevice::init("Security System in azione");
  bleServer =BLEDevice::createServer();
  bleService =bleServer->createService(SERVICE_UUID);

  bleCharacteristic = bleService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
);

bleService->start();
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->start();

}
void ciro_SERIALSICURITY::receiveBLEMessage(){
  message = bleCharacteristic->getValue(); // legge il valore dal ble 

  if(message == "ATTIVA ALLARME"){
    Serial.println("allarme attivato ! blocco motore inserito");
    digitalWrite(_relayPompaCarbu, HIGH);
    digitalWrite(_buzzerPin,HIGH);
    delay(500);
    digitalWrite(_buzzerPin, LOW);

  }else if( message==" DISATTIVA ALLARME "){
    Serial.println("allarme disattivato ! blocco motore disattivato");
     digitalWrite(_relayPompaCarbu, LOW);
  
    
  }
}
void ciro_SERIALSICURITY::setMotionSensor(int motionPin) {
  _motionPin =motionPin;
  pinMode(_motionPin, INPUT);
}
//configurazione del blocco motore
void ciro_SERIALSICURITY::setMotor(int relayMotor){
  _relayMotor = relayMotor;
  pinMode(_relayMotor, OUTPUT);
  digitalWrite(_relayMotor, LOW);
}
void ciro_SERIALSICURITY::setTemperatureThreshold(float threshold) {
  _temperatureThreshold = threshold;
}
void ciro_SERIALSICURITY::setTemperatureAndAlert(int _relayVentoARD){
  if (_temperatureDeg > _temperatureThreshold) {
    Serial.println(" ATTENZIONE!!! TEMPERATURA ELEVATA!");
    digitalWrite(_relayVentoARD, HIGH);
  }else {
    Serial.println("temperatura OK");
    digitalWrite(_relayVentoARD, LOW);
  }
}
// controllo il sensore di inclinazione e ATTIVA IL BUZZER 
void ciro_SERIALSICURITY::setTildAndBuzzer(int _relaySirena) {
   if  (message == "ATTIVA ALLARME") {
    Serial.println("allarme attivo");
    digitalWrite(_relayPompaCarbu, LOW);
    digitalWrite(_relayMotor, LOW);
    digitalWrite(_buzzerPin, HIGH);
    delay(1000);
    digitalWrite(_buzzerPin, LOW);
    if (digitalRead(_tiltPin)== HIGH) {
    Serial.println("movimento rilveto ");
    digitalWrite(_relaySirena, HIGH);
    digitalWrite(_buzzerPin, HIGH); 
    digitalWrite(_relayPompaCarbu, LOW);
    digitalWrite(_relayMotor, LOW); 
  }else if (message == "RESET ALLARME"){
    Serial.println("allarme disattivato e movimento resettato");
    digitalWrite(_relayPompaCarbu, HIGH);
    digitalWrite(_buzzerPin, LOW);
    digitalWrite(_relaySirena,LOW);

  } else {
    Serial.println(" comando non riconosciuto ")
  }

   }
}
void ciro_SERIALSICURITY::checkMotionAndAlarm(){
  if (message == " ATTIVA ALLARME"){
  Serial.println("allarme attivo");
  digitalWrite(_relayPompaCarbu, LOW);
    digitalWrite(_relayMotor, LOW);
    digitalWrite(_buzzerPin, HIGH);
    delay(1000);
    digitalWrite(_buzzerPin, LOW);
  
  if (digitalRead(_motionPin) == HIGH) {
    Serial.println(" movimento rilevato !!!");
    digitalWrite(_buzzerPin, HIGH);
    digitalWrite(_relayPompaCarbu, LOW);
    digitalWrite(_relaySirena, HIGH);

    if(message == " RESET ALLARME"){
     digitalWrite(_buzzerPin, LOW);
    digitalWrite(_relayPompaCarbu, HIGH);
    digitalWrite(_relaySirena, LOW);
    }
  }else {
    Serial.println(" MESSAGGIO NON DECIFRATO ");
  }
}
}

void ciro_DHT22::setupBLE(const char* deviceName,  const char* serviceUUID, const char* characteristicUUID ){
  //iizializza il BLE
  BLEDevice::init(deviceName);  //inizializza il BLE
  bleServer =BLEDevice::createServer(); // crea il Server BLE 
  bleService = bleServer->createService(serviceUUID); // crea il servizio BLE 
  
   // crea le caratteristica BLE 
   bleCharacteristic = bleService->createCharacteristic(
    characteristicUUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
   );
 
   bleService->start(); // avvia il servizio 
   BLEAdvertising * advertising = BLEDevice::getAdvertising();
 // configurazione adversiting BLE 
   advertising->start(); // sono dei pacchetti BLE per farlo funzionare 
}

void ciro_DHT22::sendBLEData(){
  // convertiamo i dati sensore in una stringa
  String dataString = String("Temperatura: ")+ _temperatureDeg + "C, "+ "Umindità: "+ _humidity + " %";

  // inposta il varole nella caratteristica BLE
  bleCharacteristic->setValue(dataString.c_str());
  bleCharacteristic->notify(); //notifica del dispositivo remoto

}
void ciro_DHT22::setBuzzer(int8_t tiltPinPin, int8_t buzzerPin){
  _inclinPin = _tiltPin;  // imposta il pin del sensore di inclinazione
  _buzzerPin = buzzerPin;  // imposta il pin del buzzer
  pinMode(_tiltPin, INPUT); // configura il pin inclinazione come input 
  pinMode(_buzzerPin, OUTPUT); // configura il pin del buzzer oome output
  digitalWrite( _buzzerPin, LOW);// spegne il buzzer  inizialmente 
}

void ciro_DHT22::checkTildAndBuzzer(){
  if (message == " ATTIVA ALLARME"){
  Serial.println("allarme attivo");
  digitalWrite(_relayPompaCarbu, LOW);
    digitalWrite(_relayMotor, LOW);
    digitalWrite(_buzzerPin, HIGH);
    delay(1000);
    digitalWrite(_buzzerPin, LOW);
  if (digitalRead(_tiltPin)==HIGH) {
     Serial.println(" inclinazione rilevata !!!");
    digitalWrite(_buzzerPin, HIGH);
    digitalWrite(_relayPompaCarbu, LOW);
    digitalWrite(_relaySirena, HIGH);

    if(message == " RESET ALLARME"){
     digitalWrite(_buzzerPin, LOW);
    digitalWrite(_relayPompaCarbu, HIGH);
    digitalWrite(_relaySirena, LOW);
    }
  }else  {
    Serial.println(" MESSAGGIO NON DECIFRATO ");
  }
}
  }
