# Outline
This is a fork of the original repo at: https://github.com/DFRobot/DFRobot_LedDisplayModule

Originally had issues compile errors trying to use it out of the box on an ESP32 so I decided to get that fixed up.

Note that this repo will only have support for the 4-digit module in order to reduce the library size, I may in the future add in 8-digit support or create another add-on repo to support that.

There have also been various changes such as additional character support, minimising library size and easier functions to interact with the displays.

I have got it working working to my liking, however I will try to cleanup and maintain the code a bit more.

# DFRobot_LedDisplayModule
This is a 4bits digital tube. It communicates with the host via IIC to show numbers from 0 to 9, letters A, B, C, D, E, F, G, H, I, J, L, N, O, P, Q, R, S, T, U and dash (-) and period (.). <br>
The IIC address of 4 bits digital tube in default is 0x48. <br>

## DFRobot_LedDisplayModule for Arduino
---------------------------------------------------------
Provide an Arduino library for the Led Display Module.
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary
This is an Arduino IDE library to help realize the communication between the 4bits/8bits digital tube and Arduino<br>
The library ease the control of display by IIC<br>

## Installation

To use this library, please download the library file first and paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
   /*!
   *  @brief Initialize the 4bits 
   *  @return Return 0 if initialization succeeds, otherwise return non-zero.
   */ 
  int begin4();

  /*!
   *  @brief Start display
   *  @param Command to start display
   */
  void displayOn();
  
  /*!
   *  @brief End display
   *  @param Command to end displaying
   */  
  void displayOff();

  /*!
   *  @brief Flash mode of the 8 bits digital tube, flash at 0.5Hz
   *  @param IIC flash command
   */
  void flashTwos();
  
  /*!
   *  @brief Flash mode of the 8 bits digital tube, flash at 1HZ
   *  @param IIC flash command
   */
  void flashOnes();
  
  /*!
   *  @brief Flash mode of the 8 bits digital tube, flash at 2HZ 
   *  @param IIC flash command
   */
  void flashHalfs();
  
  /*!
   *  @brief The 8 bits digital tube stops flash 
   *  @param IIC command to stop flash
   */
  void stopFlash();

  /*!
   *  @brief Set brightness of the 4 bits digital tube
   *  @param The brightness value can be set to numbers 1~8
   */
  void setBrightness4(int brightnessValue); 

  /*!
   *  @brief Display area of the 4bits digital tube 
   *  @param The display address of the first bit to fourth bit could be numbers 1~4
   */
  void setDisplayArea4(int areaData);
  void setDisplayArea4(int areaData1,int areaData2);
  void setDisplayArea4(int areaData1,int areaData2,int areaData3);
  void setDisplayArea4(int areaData1,int areaData2,int areaData3,int areaData4);

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
   *  @brief Print data of the 4 bits digital tube
   *  @param Displayed data of bit 1 to bit 4 could be the numbers 0 to 9, capital letters A, B, C, D, E, F, H, L, O, P, U and dash-. 
   *  @n and also could be decimal points, such as "0." "9." "A." "-."
   */
  void print4(const char buf1[], const char buf2[], const char buf3[], const char buf4[]);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |             |              |      √       | 
Mega2560        |             |              |       √      | 
Leonardo        |             |              |      √       | 
ESP32         |      √       |              |             | 
micro:bit        |             |              |     √        | 

## History

- Forked: 07-Mar-2021

## Credits

Originally written by(wenzheng.wang@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))
