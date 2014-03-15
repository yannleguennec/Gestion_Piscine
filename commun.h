#ifndef commun_h
#define commun_h

#define TITRE "Gestion Piscine"
#define VERSION "v2.00"

#define Log(x) { \
  Serial.print("// "); \
  Serial.print(millis()); \
  Serial.print(": "); \
  Serial.print(__FILE__); \
  Serial.print(":"); \
  Serial.print(__LINE__); \
  Serial.print(":"); \
  Serial.print(__FUNCTION__); \
  Serial.print("(): "); \
  Serial.println(x); \
}

struct
{
  float tempAir;
  float tempEau;
  float humidite;
  float pression;
  float tempAir2;
  float altitude;
} resultats;
#endif

