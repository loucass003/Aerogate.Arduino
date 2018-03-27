#include <VirtualWire.h>

void setup()
{
    Serial.begin(9600);    // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(7);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(128);  // Bits per sec
}

void loop()
{
    const uint8_t msg[] = { 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send(msg, sizeof(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    delay(100);
}
