#include <SoftwareServo.h>
#include <High_Temp.h>
#include <OneWire.h> //Librairie du bus OneWire
#include <DallasTemperature.h> //Librairie du capteur
#include <VirtualWire.h>

#define MODULE_ID 0

OneWire oneWire(7); //Bus One Wire sur la pin 2 de l'arduino
DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie
HighTemp ht(A1, A0);
SoftwareServo s_clapet;

int s_clapet_angle = 0;
int p_temp = 0;
int e_temp = 0;
int i_temp = 0;

int start_time;

int log2(int x)
{
  int i = 31;
  while(i >= 0 && !(x >> i))
    --i;
  return i + 1;
}

void toBinary(uint8_t* out, int n, int len)
{
  for (uint8_t i = 0; i < len; ++i)
    out[len - 1 - i] = (n >> i) & 1;
}

int message(uint8_t* out, int id, int command, int value)
{
  int val_len = log2(value);
  toBinary(out, id, 2);
  toBinary(out + 2, command, 4);
  toBinary(out + 6, value, val_len);
  return 6 + val_len;
}

void setup() 
{
  Serial.begin(9600); //Permet la communication en serial
  sensors.begin(); //Activation des capteurs
  sensors.getAddress(sensorDeviceAddress, 0); //Demande l'adresse du capteur à l'index 0 du bus
  sensors.setResolution(sensorDeviceAddress, 12); //Résolutions possibles: 9,10,11,12
  sensors.getAddress(sensorDeviceAddress, 1);
  sensors.setResolution(sensorDeviceAddress, 12);
  ht.begin();
  s_clapet.attach(6);
  s_clapet.write(s_clapet_angle);

  vw_set_tx_pin(2);
  vw_set_ptt_inverted(true);
  vw_setup(128);

  start_time = millis();
}

void sendMessages() 
{
  uint8_t msg[38];
  memset(msg, 0, 38);
  int l = message(msg, MODULE_ID, 1, p_temp);
  vw_send(msg, l);
  vw_wait_tx();
  memset(msg, 0, 38);
  l = message(msg, MODULE_ID, 2, e_temp);
  vw_send(msg, l);
  vw_wait_tx();
  memset(msg, 0, 38);
  l = message(msg, MODULE_ID, 3, i_temp);
  vw_send(msg, l);
  vw_wait_tx();
  memset(msg, 0, 38);
  l = message(msg, MODULE_ID, 4, s_clapet_angle);
  vw_send(msg, l);
  vw_wait_tx();
}

void loop() 
{
  Serial.print("Temp poele: ");
  Serial.println(p_temp = ht.getThmc());

  sensors.requestTemperatures(); //Demande la température aux capteurs
  Serial.print("La température 1 est: ");
  Serial.print(e_temp = sensors.getTempCByIndex(0)); //Récupération de la température en celsius du capteur n°0
  Serial.println(" C°");

  Serial.print("La température 2 est: ");
  Serial.print(i_temp = sensors.getTempCByIndex(1)); //Récupération de la température en celsius du capteur n°0
  Serial.println(" C°");

  if(p_temp > 100 && s_clapet_angle != 90) {
    s_clapet.attach(6);
    s_clapet.write(s_clapet_angle = 90);
  } else if(p_temp <= 100 && s_clapet_angle != 0) {
    s_clapet.attach(6);
    s_clapet.write(s_clapet_angle = 0);
  }
  s_clapet.detach();
  sendMessages();

  if(millis() - start_time > 30000) {
    Serial.println("Send data");
    sendMessages();
  }
}
