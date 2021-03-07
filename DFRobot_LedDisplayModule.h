/*!
 * @file DFRobot_LedDisplayModule.h
 * @brief Define the basic structure of class DFRobot_LedDisplayModule
 * @n This is a 4bits digital tube that controlled by IIC interface.
 * @n The main functions of the digital tube is as below:
 * @n Show 4bits numbers and decimal points
 * @n At present, it only supports showing the show numbers from 0 to 9, letters A, B, C, D, E, F, G, H, I, J, L, N, O, P, Q, R, S, T, U and dash (-) and period (.).
 * @n And you can also bring decimal points, such as "0." "9." "A." "-."
 *
 * @copyright   Portions Copyright (c) 2021 Luke Rep-Baihelfer
 * @copyright   Portions Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Actor](wenzheng.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-12-10
 * @https://github.com/DFRobot/DFRobot_LedDisplayModule
 */
#ifndef __DFRobot_LedDisplayModule_H__
#define __DFRobot_LedDisplayModule_H__

#include "Arduino.h"
#include <Wire.h>

//Define DBG, change 0 to 1 open the DBG, 1 to 0 to close
#if 0
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#if 0
#define DBGI(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBGI(...)
#endif

#define CMD_HT16K33_OSCOFF      0x20  /**< Turn OFF the clock */
#define CMD_HT16K33_OSCON       0x21  /**< Turn ON the clock */
#define CMD_HT16K33_DISPLAYOFF  0x80  /**< Turn OFF the display */
#define CMD_HT16K33_DISPLAYON   0x81  /**< Turn ON the display*/

class DFRobot_LedDisplayModule
{
public:
  #define ERR_OK             0      //ok
  #define ERR_ADDR          -1      //error in I2C address

public:
 /**
   * @brief Constructor
   * @param pWire I2C bus pointer object. When calling the function, you may transfer a parameter into it. Default as Wire
   * @param addr the IIC address of 4 bits digital tube in default is 0x48
   */
  DFRobot_LedDisplayModule(TwoWire &wire, uint8_t ledAddress);

  /*!
   *  @brief  the 4 bits digital tube
   *  @return Return 0 if the initialization is successful, otherwise return non-zero
   */
  int begin4();

  /*!
   *  @brief Turn ON the display
   *  @param IIC command to turn ON the display
   */
  void displayOn();

  /*!
   *  @brief Turn OFF the display
   *  @param IIC command to turn OFF the display
   */
  void displayOff();

  /*!
   *  @brief Set brightness of the 4 bits digital tube
   *  @param The brightness value can be set to numbers 1~8
   */
  void setBrightness4(int brightnessValue);

  /*!
   *  @brief Display area of the 4 bits digital tube
   *  @param Display area from the first bit to the fourth bit could be number 1~4.
   */
  void setDisplayArea4(int areaData1 = 82,int areaData2 = 82,int areaData3 = 82,int areaData4 = 82);

  /*!
   *  @brief Set the decimal points of the 4 bits.
   *  @param decimals byte value to indicate which bits to be on/off in LSB order.
   *  @n 0b00000000 would turn them all off.
   *  @n 0b00001111 would turn them all on.
   *  @n 0b00000001 would turn them the 1st digit's decimal on.
   *  @n 0b00001000 would turn them the 4th digit's decimal on.
  */
  void setDecimals(byte decimals = 0b00000000);

  /*!
   *  @brief
   *  @param buf const char array, should contain at least 4 characters.
   *  @n todo: add some safety in
  */
  void printString(const char buf[]);

  /*!
   *  @brief Print data of the 4 bits digital tube
   *  @param It could be both integer and decimal
   */
  void print4(double sensorData);

  /*!
   *  @brief 4Print data of the 4 bits digital tube
   *  @param
   *  @n Displayed data of bit 1 to bit 4 could be the numbers 0 to 9, capital letters A, B, C, D, E, F, H, L, O, P, U and dash-,
   *  @n and it also could be decimal points, such as "0." "9." "A." "-."
   */
  void print4(const char buf1[], const char buf2[], const char buf3[], const char buf4[]);

private:
  TwoWire *_pWire;
  uint8_t _ledAddress;  /**< IIC Address */
  byte displayAreaFlag;  /**< Display area flag */
  byte data1,data2,data3,data4;  /**< Display data buffer*/
  unsigned char ledData1,ledData11,ledData2,ledData22,ledData3,ledData33,ledData4,ledData44;  /**< Input data buffer */

  byte d11;
  byte d21,d22;
  byte d31,d32,d33;
  byte d41,d42,d43,d44; /**< Display area data buffer*/

  byte d1,d2,d3;
  byte a1,a2,a3;  /**< Display address data buffer*/

  const unsigned char TAB2[38] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  /**< 0~9 then :;<=>?@ */
                                0x77,0x7C,0x39,0x5E,0x79,0x71,  /**< A~F */
                                0x3D,
                                0x76,                /**< H */
                                0x30,0x1E,0x00,
                                0x38,                /**< L */
                                0x00,0x54,0x5C,      /**< O */
                                0x73,                /**< P */
                                0x67,0x50,0x6D,0x40, /**< - */ //?? t is used for the - ???? 0x40
                                0x3E};               /**< U */                                                                   /**< Display data */

// These are all 8 bits with the MSB being the decimal point for the . character
  const unsigned char TAB_Point2[38] = {0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                      0xF7,0xFC,0xB9,0xDE,0xF9,0xF1,
                                      0xBD,
                                      0xF6,
                                      0xB0,0x9E,0x00,
                                      0xB8,
                                      0x00,0xD4,0xDC,
                                      0xF3,
                                      0xE7,0xD0,0xED,0xC0,
                                      0xBE};                                                                                     /**< Display data, light up the decimal point*/

  /*!
   *  @brief Send IIC command
   *  @param IIC command
   */
  void i2cWriteCmd(uint8_t cmd);

  /*!
   *  @brief 4-bit digital tube to send IIC data
   *  @param Register address
   *  @param IIC data
   */
  void i2cWriteData4(uint8_t reg,uint8_t data);

 /*!
  *  @brief Reset the print buffer area
  */
  void printCacheReset();

  /*!
   *  @brief Get display date of bit 1 to bit 8 from the user input
   */
  void getDisplayData();

  /*!
   *  @brief The 4bits digital tube to get the display address
   */
  void getDisplayAddress41();
  void getDisplayAddress42();
  void getDisplayAddress43();

  /*!
   *  @brief The 4bits digital tube to get the display address(sensor data mode)
   */
  void sensorGetDisplayAddress4();

  /**
   * @brief I2C address detection
   * @param addr I2C address
   * @return Return 0 if IIC address is set correctly, otherwise return non-zero.
   */
  int i2cdetect(uint8_t _ledAddress);
};

#endif