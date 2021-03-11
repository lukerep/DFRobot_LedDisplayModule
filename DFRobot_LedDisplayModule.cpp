/*!
 * @file DFRobot_LedDisplayModule.h
 * @brief Define the basic structure of class DFRobot_LedDisplayModule
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Actor](liang.li@dfrobot.com)
 * @version  V1.0
 * @date  2019-12-10
 * @https://github.com/DFRobot/DFRobot_LedDisplayModule
 */

#include <Arduino.h>

#include "DFRobot_LedDisplayModule.h"

DFRobot_LedDisplayModule::DFRobot_LedDisplayModule(TwoWire &wire, uint8_t ledAddress)
{
  _pWire = &wire;
  _ledAddress = ledAddress >> 1;
}

int DFRobot_LedDisplayModule::begin4()
{
  _pWire->begin();
  if(i2cdetect(_ledAddress) != 0){
      DBG("I2C ADDR ERROR!");
      return ERR_ADDR;
  }
  setBrightness4(0);
  displayOn();
  return 0;
}

void DFRobot_LedDisplayModule::displayOn()
{
  i2cWriteCmd(0x01);
  i2cWriteCmd(CMD_HT16K33_DISPLAYON);
}

void DFRobot_LedDisplayModule::displayOff()
{
  i2cWriteCmd(0x00);
  i2cWriteCmd(CMD_HT16K33_DISPLAYOFF);
}

void DFRobot_LedDisplayModule::setBrightness4(int brightnessValue)
{
  if(brightnessValue == 8) brightnessValue = 0;
  i2cWriteCmd((brightnessValue<<4)|0x01);
}

void DFRobot_LedDisplayModule::setDisplayArea4(int areaData1, int areaData2, int areaData3, int areaData4)
{
  if(areaData2==82 && areaData3==82 && areaData4==82)
  {
    displayAreaFlag = 1;
    d11 = areaData1;
  }
  else if(areaData3==82 && areaData4==82)
  {
    displayAreaFlag = 2;
    d21 = areaData1;
    d22 = areaData2;
  }
  else if(areaData4==82)
  {
    displayAreaFlag = 3;
    d31 = areaData1;
    d32 = areaData2;
    d33 = areaData3;
  }
  else
  {
    displayAreaFlag = 4;
    d41 = areaData1;
    d42 = areaData2;
    d43 = areaData3;
    d44 = areaData4;
  }
}

void DFRobot_LedDisplayModule::print4(double sensorData)
{
  char cacheBuf[10];
  char cacheData1='0',cacheData2='0',cacheData3='0',cacheData4='0',cacheData5='0'; // '0' is equal to 48
  double temp = sensorData;
  if(temp < 10)
  {
    dtostrf(temp,1,3,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB_Point2[cacheData1-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break; 
      case 2:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB_Point2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData3-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
      case 3:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB_Point2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData3-48]);i2cWriteData4(a3,TAB2[cacheData4-48]);i2cWriteData4(d1,0x00);break;
      case 4:i2cWriteData4(0,TAB_Point2[cacheData1-48]);i2cWriteData4(1,TAB2[cacheData3-48]);i2cWriteData4(2,TAB2[cacheData4-48]);i2cWriteData4(3,TAB2[cacheData5-48]);break;
    }
  }
  else if(temp>=10 && temp<100)
  {
    dtostrf(temp,2,2,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
      case 2:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB_Point2[cacheData2-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
      case 3:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB_Point2[cacheData2-48]);i2cWriteData4(a3,TAB2[cacheData4-48]);i2cWriteData4(d1,0x00);break;
      case 4:i2cWriteData4(0,TAB2[cacheData1-48]);i2cWriteData4(1,TAB_Point2[cacheData2-48]);i2cWriteData4(2,TAB2[cacheData4-48]);i2cWriteData4(3,TAB2[cacheData5-48]);break;
    }
  }
  else if(temp>=100 && temp<1000)
  {
    dtostrf(temp,3,1,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
      case 2:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData2-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
      case 3:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData2-48]);i2cWriteData4(a3,TAB_Point2[cacheData3-48]);i2cWriteData4(d1,0x00);break;
      case 4:i2cWriteData4(0,TAB2[cacheData1-48]);i2cWriteData4(1,TAB2[cacheData2-48]);i2cWriteData4(2,TAB_Point2[cacheData3-48]);i2cWriteData4(3,TAB2[cacheData5-48]);break;
    }
  }
  else if(temp>=1000)
  {
    dtostrf(temp,4,0,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
      case 2:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData2-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
      case 3:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData2-48]);i2cWriteData4(a3,TAB2[cacheData3-48]);i2cWriteData4(d1,0x00);break;
      case 4:i2cWriteData4(0,TAB2[cacheData1-48]);i2cWriteData4(1,TAB2[cacheData2-48]);i2cWriteData4(2,TAB2[cacheData3-48]);i2cWriteData4(3,TAB2[cacheData4-48]);break;
    }
  }
}

void DFRobot_LedDisplayModule::setDecimals(byte decs) {
  int decimals[4] = {10, 10, 10, 10};
  for (byte digit = 0; digit < 4; digit++) {

    // If the specified digit decimal place is meant to be turned on
    if(decs & (1<<(digit))) {
      decimals[digit] = 46;
    }

  }
  ledData11 = decimals[0];
  ledData22 = decimals[1];
  ledData33 = decimals[2];
  ledData44 = decimals[3];

  getDisplayData();
  switch(displayAreaFlag)
  {
    case 1:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
    case 2:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(a2,data2);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
    case 3:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(a2,data2);i2cWriteData4(a3,data3);i2cWriteData4(d1,0x00);break;
    case 4:i2cWriteData4(d41-1,data1);i2cWriteData4(d42-1,data2);i2cWriteData4(d43-1,data3);i2cWriteData4(d44-1,data4);break;
  }
  // Not resetting cache because we want to be able to change the decimals independent of what characters are being displayed
  // printCacheReset();
}

void DFRobot_LedDisplayModule::printString(const char buf[]) {
  // If the character passed in is a space, set it to the '?' char so it displays empty
  // The space character is no in the lookup table for TAB/TAB_POINT2 so decimals don't work with it
  ledData1 = buf[0] == ' ' ? '?' : buf[0];
  ledData2 = buf[1] == ' ' ? '?' : buf[1];
  ledData3 = buf[2] == ' ' ? '?' : buf[2];
  ledData4 = buf[3] == ' ' ? '?' : buf[3];

  getDisplayData();
  switch(displayAreaFlag)
  {
    case 1:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
    case 2:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(a2,data2);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
    case 3:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(a2,data2);i2cWriteData4(a3,data3);i2cWriteData4(d1,0x00);break;
    case 4:i2cWriteData4(d41-1,data1);i2cWriteData4(d42-1,data2);i2cWriteData4(d43-1,data3);i2cWriteData4(d44-1,data4);break;
  }
  // Not resetting cache because we want to be able to change the characters independent of what decimals are being displayed
  // printCacheReset();
}

void DFRobot_LedDisplayModule::print4(const char buf1[], const char buf2[], const char buf3[], const char buf4[])
{
  if (buf1[0] != NULL){
  ledData1 = buf1[0];
  ledData11 = buf1[1];
  }else{
    ledData1 = 10;
    ledData11 = 10;
  }
  if (buf2[0] != NULL){
  ledData2 = buf2[0];
  ledData22 = buf2[1];
  }else{
    ledData2 = 10;
    ledData22 = 10;
  }
  if (buf3[0] != NULL){
  ledData3 = buf3[0];
  ledData33 = buf3[1];
  }else{
    ledData3 = 10;
    ledData33 = 10;
  }
  if (buf4[0] != NULL){
  ledData4 = buf4[0];
  ledData44 = buf4[1];
  }else{
    ledData4 = 10;
    ledData44 = 10;
  }

  getDisplayData();
  switch(displayAreaFlag)
  {
    case 1:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
    case 2:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(a2,data2);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
    case 3:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(a2,data2);i2cWriteData4(a3,data3);i2cWriteData4(d1,0x00);break;
    case 4:i2cWriteData4(d41-1,data1);i2cWriteData4(d42-1,data2);i2cWriteData4(d43-1,data3);i2cWriteData4(d44-1,data4);break;
  }
  printCacheReset();
}

void DFRobot_LedDisplayModule::i2cWriteCmd(uint8_t cmd)
{
  _pWire->beginTransmission(_ledAddress);
  _pWire->write(cmd);
  _pWire->endTransmission();
}

void DFRobot_LedDisplayModule::i2cWriteData4(uint8_t reg ,uint8_t data)
{
  _pWire->beginTransmission((0x68+reg*2)>>1);
  _pWire->write(data);
  _pWire->endTransmission();
}

void DFRobot_LedDisplayModule::printCacheReset()
{
  ledData1='0';
  ledData11='0';
  ledData2='0';
  ledData22='0';
  ledData3='0';
  ledData33='0';
  ledData4='0';
  ledData44='0';
}

void  DFRobot_LedDisplayModule::getDisplayData()
{
  // 45 = -
  // 46 = .
  // ledDataXX is 2 characters for a specific digit to allow for . and -
  // ledData1 is the first character, ledData11 is the second
  // -2 would mean ledData1 = - and ledData11 = 2
  // 2. would mean ledData1 = 2 and ledData11 = .
  // 0x80 = 10000000 which is just the decimal place

  if(ledData1==46 || ledData11==46)
  {
    if(ledData1==46)
    {
     data1 = 0x80;
    }
    else
    {
      // If the character is a -, set the ledData1 value to 84
      // So that when we do ledData1-48 it is equal to 36 which is character T in TAB2
      // Which is why character T is used for the - character
      if(ledData1==45) ledData1 = 84;
      data1 = TAB_Point2[ledData1-48];
    }
  }
  else
  {
    if(ledData1==45) ledData1 = 84;
    data1 = TAB2[ledData1-48];
  }

  if(ledData2==46 || ledData22==46)
  {
    if(ledData2==46)
    {
      data2 = 0x80;
    }
    else
    {
      if(ledData2==45) ledData2 = 84;
      data2 = TAB_Point2[ledData2-48];
    }
  }
  else
  {
    if(ledData2==45) ledData2 = 84;
    data2 = TAB2[ledData2-48];
  }

  if(ledData3==46 || ledData33==46)
  {
    if(ledData3==46)
    {
      data3 = 0x80;
    }
    else
    {
      if(ledData3==45) ledData3 = 84;
      data3 = TAB_Point2[ledData3-48];
    }
  }
  else
  {
    if(ledData3==45) ledData3 = 84;
    data3 = TAB2[ledData3-48];
  }

  if(ledData4==46 || ledData44==46)
  {
    if(ledData4==46)
    {
      data4 = 0x80;
    }
    else
    {
      if(ledData4==45) ledData4 = 84;
      data4 = TAB_Point2[ledData4-48];
    }
  }
  else
  {
    if(ledData4==45) ledData4 = 84;
    data4 = TAB2[ledData4-48];
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress41()
{
  int DisplayAreaData[4] = {1,2,3,4};

  a1 = d11;
  a1--;
  DisplayAreaData[d11-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>3)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 2)
    {
      d3 = DisplayAreaData[a];
      d3--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }   
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress42()
{
  int DisplayAreaData[4] = {1,2,3,4};

  a1 = d21;
  a1--;
  DisplayAreaData[d21-1] = 0;
  a2 = d22;
  a2--;
  DisplayAreaData[d22-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>3)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }   
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress43()
{
  int DisplayAreaData[4] = {1,2,3,4};

  a1 = d31;
  a1--;
  DisplayAreaData[d31-1] = 0;
  a2 = d32;
  a2--;
  DisplayAreaData[d32-1] = 0;
  a3 = d33;
  a3--;
  DisplayAreaData[d33-1] = 0;
  int i = 0;  
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>3)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
      break;
    }   
  }
}

void DFRobot_LedDisplayModule::sensorGetDisplayAddress4()
{
  switch(displayAreaFlag)
  {
    case 1:getDisplayAddress41(); break;
    case 2:getDisplayAddress42(); break;
    case 3:getDisplayAddress43(); break;
  }
}

int DFRobot_LedDisplayModule::i2cdetect(uint8_t _ledAddress)
{
  _pWire->beginTransmission(_ledAddress);
  if(_pWire->endTransmission() == 0)
  {
      DBG("Addr ok!");
      return  ERR_OK;
  }
  return ERR_ADDR;
}