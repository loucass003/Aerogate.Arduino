#include <Servo.h>
#include <High_Temp.h>
#include <OneWire.h> //Librairie du bus OneWire
#include <DallasTemperature.h> //Librairie du capteur
//#include <VirtualWire.h>


OneWire oneWire(7); //Bus One Wire sur la pin 2 de l'arduino
DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie
HighTemp ht(A1, A0);
Servo s_clapet;

int s_clapet_angle = 0;
int p_temp = 10;
int e_temp = 0;
int i_temp = 0;

uint8_t message(int emitter, int command, int value) {  

  
}

int* toBinary(int num, int len) {
  int out[3];
  int   nb = 2;
  int   i = 31;

  while (i >= 0) {
    if ((nb >> i) & 1)
      out[i] = 1;
    else
      out[i] = 0;
    --i;
  }
  return out;
}

void setup(void){
 Serial.begin(9600); //Permet la communication en serial
 sensors.begin(); //Activation des capteurs
 sensors.getAddress(sensorDeviceAddress, 0); //Demande l'adresse du capteur à l'index 0 du bus
 sensors.setResolution(sensorDeviceAddress, 12); //Résolutions possibles: 9,10,11,12
 sensors.getAddress(sensorDeviceAddress, 1);
 sensors.setResolution(sensorDeviceAddress, 12);
 ht.begin();
 s_clapet.attach(6);
 s_clapet.write(s_clapet_angle);

 /*vw_set_tx_pin(2);
 vw_set_ptt_inverted(true);
 vw_setup(128);*/
}






void loop(void) {

 Serial.print("Temp poele: ");
 Serial.println(p_temp = ht.getThmc());
 
 sensors.requestTemperatures(); //Demande la température aux capteurs
 Serial.print("La température 1 est: ");
 Serial.print(e_temp = sensors.getTempCByIndex(0)); //Récupération de la température en celsius du capteur n°0
 Serial.println(" C°");

 Serial.print("La température 2 est: ");
 Serial.print(i_temp = sensors.getTempCByIndex(1)); //Récupération de la température en celsius du capteur n°0
 Serial.println(" C°");

 Serial.println("--------------------------------");

 if(p_temp > 100 && s_clapet_angle != 90) {
   s_clapet.attach(6);
   s_clapet.write(s_clapet_angle = 90);
   Serial.println("1");
 } else if(p_temp <= 100 && s_clapet_angle != 0) {
   s_clapet.attach(6);
   s_clapet.write(s_clapet_angle = 0);
   Serial.println("2");
 }
 s_clapet.detach();
 Serial.println(s_clapet_angle);


/* uint8_t buf[VW_MAX_MESSAGE_LEN];
 uint8_t buflen = VW_MAX_MESSAGE_LEN;
 const uint8_t msg[] = { 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


 delay(200);
 vw_send(msg, sizeof(msg));
 Serial.println("Send");
 vw_wait_tx();
 delay(200);*/
 int* t = toBinary(2, 2);
  Serial.print(t[0]);
  Serial.println(t[1]);
}
