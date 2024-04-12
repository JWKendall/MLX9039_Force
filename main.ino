
#include <Wire.h> // For I2C Comms
#include <MLX90393.h> // From https://github.com/tedyapo/arduino-MLX90393 by Theodore Yapo

// For TFT Screen:
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

MLX90393 mlx;
MLX90393::txyz data; //Create a structure, called data, for sensor 1, of four floats (t, x, y, and z)
MLX90393::txyz data2; //Create a structure, called data2, for sensor 2, of four floats (t, x, y, and z)

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST); // Config of TFT Screen

void setup()
{
  Serial.begin(9600);
  
  Wire.begin(); // Join I2C Bus as controller

  // TFT
  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

}

void loop()
{
  // Sensor 1
  mlx.begin(1,0); //Sets A1 to VCC, A0 to GND. No DRDY pin used.
  mlx.readData(data); //Read the values from the sensor 1

  // Sensor 2
  mlx.begin(0,0); //Sets A1 to GND, A0 to GND. No DRDY pin used.
  mlx.readData(data2); //Read the values from the sensor 2

  // mlx.setOverSampling(0);
  // mlx.setDigitalFiltering(0);

  // Data from sensor 1 to Serial Plotter
  Serial.print("1X:");
  Serial.print(data.x);
  Serial.print(",");
  Serial.print("1Y:");
  Serial.print(data.y);
  Serial.print(",");
  Serial.print("1Z:");
  Serial.print(data.z);
  Serial.print(",");

  // Data from sensor 2 to Serial Plotter
  Serial.print("2X:");
  Serial.print(data2.x);
  Serial.print(",");
  Serial.print("2Y:");
  Serial.print(data2.y);
  Serial.print(",");
  Serial.print("2Z:");
  Serial.print(data2.z);

  Serial.println();

  // tft clear screen
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);

  // Print data on TFT:
  
  // Sensor 1
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("Sensor 1:");
  // X:
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("X:");
  // Value
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println(data.x, 4);
  // Y:
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("Y:");
  // Value
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println(data.y, 4);
  // Z:
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("Z:");
  // Value
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println(data.z, 4);

  // Sensor 2
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("Sensor 2:");
  // X:
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("X:");
  // Value
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println(data2.x, 4);
  // Y:
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("Y:");
  // Value
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println(data2.y, 4);
  // Z:
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("Z:");
  // Value
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println(data2.z, 4);

  delay(10);
}
