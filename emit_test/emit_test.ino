#include <VirtualWire.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");

  //vw_set_rx_pin(6);
  vw_set_tx_pin(2);
  vw_set_ptt_inverted(true);
  vw_setup(128);
  //vw_rx_start();
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  const uint8_t msg[] = { 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  delay(200);
  vw_send(msg, sizeof(msg));
  Serial.println("Send");
  vw_wait_tx();
 delay(200);
 /* vw_wait_rx_max(1000);
  delay(200);
  if (vw_get_message(buf, &buflen))
  {
    Serial.print("Got: ");

    for (int i = 0; i < buflen; i++)
    {
      Serial.print(buf[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }*/
}

