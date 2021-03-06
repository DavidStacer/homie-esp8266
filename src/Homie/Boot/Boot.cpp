#include "Boot.hpp"

using namespace HomieInternals;

Boot::Boot(const char* name)
: _interface(nullptr)
, _name(name)
{
}

void Boot::attachInterface(Interface* interface) {
  _interface = interface;
}

void Boot::setup() {
  if (this->_interface->led.enabled) {
    pinMode(this->_interface->led.pin, OUTPUT);
    digitalWrite(this->_interface->led.pin, !this->_interface->led.on);
  }

  WiFi.persistent(false); // Don't persist data on EEPROM since this is handled by Homie
  WiFi.disconnect(); // Reset network state

  char hostname[MAX_WIFI_SSID_LENGTH];
  strcpy(hostname, this->_interface->brand);
  strcat_P(hostname, PSTR("-"));
  strcat(hostname, Helpers::getDeviceId());

  WiFi.hostname(hostname);

  Logger.log(F("** Booting into "));
  Logger.log(this->_name);
  Logger.logln(F(" mode **"));
}

void Boot::loop() {
}
