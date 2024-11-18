#include <Arduino.h>
#include <openGLCD.h>
#include <WiFi.h>
#include <EEPROM.h>
#include <WebServer.h>
// chân nút bấm
int nutup = 34;
int nutdown = 35;
int nutenter = 12;
int nutforward = 13;

int output = 14;

// bộ đọc cho nút
int i;
int vitri = 1;
int lastvitri = 1;
unsigned long thoigiantruockhibamnut = 0;
const long thoigianbamnut = 80;
int enter = 0;
int len = 0;
int xuong = 0;
int back = 0;
int lastback = 0;
int lastenter = 0;
int chedo = 0;
int lastchedo = -1;
// Cảm biến
int sensorpin = 39;
float analogReadMax = 4095.0;
int giatrinhietdo =0 ;
float mV;
float nhietdo;
float lastnhietdo;
//
unsigned long thoigiantruockhidongbo = 0;
// EEPROM
int Thresholdmax ; 
int Thresholdmin;

int lastThresholdmax = -1;
int lastThresholmin = -1;

int mode=0;
int lastmode = 0;
