#pragma once

#include <cstdint>

#define PDO_5V          (uint8_t)5
#define PDO_9V          (uint8_t)9
#define PDO_12V         (uint8_t)12
#define PDO_15V         (uint8_t)15
#define PDO_18V         (uint8_t)18
#define PDO_20V         (uint8_t)20

#define PDO_500MA       (uint16_t)500
#define PDO_700MA       (uint16_t)700
#define PDO_1000MA      (uint16_t)1000
#define PDO_1A          PDO_1000MA
#define PDO_1250MA      (uint16_t)1250
#define PDO_1500MA      (uint16_t)1500
#define PDO_1750MA      (uint16_t)1750
#define PDO_2000MA      (uint16_t)2000
#define PDO_2A          PDO_2000MA
#define PDO_2250MA      (uint16_t)2250
#define PDO_2500MA      (uint16_t)2500
#define PDO_2750MA      (uint16_t)2750
#define PDO_3000MA      (uint16_t)3000
#define PDO_3A          PDO_3000MA
#define PDO_3250MA      (uint16_t)3250
#define PDO_3500MA      (uint16_t)3500
#define PDO_4000MA      (uint16_t)4000
#define PDO_4A          PDO_4000MA
#define PDO_4500MA      (uint16_t)4500
#define PDO_5000MA      (uint16_t)5000
#define PDO_5A          PDO_5000MA

struct PDO {
  uint8_t voltage;
  uint16_t current;
};
