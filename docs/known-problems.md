## 'SCK' was not declared, 'MOSI' was not declared, ..., errors

M5Stamp S3 support was a bit flaky in early versions in early `arduino-esp32` library.
If you are seeing compilation errors similar to these blow, you probably are probably hit by <https://github.com/espressif/arduino-esp32/issues/8185>:

```
Compiling .pio\build\M5StampS3\liba52\BLE\BLECharacteristic.cpp.o
C:/users/test/.platformio/packages/framework-arduinoespressif32/libraries/SPI/src/SPI.cpp: In member function 'void SPIClass::begin(int8_t, int8_t, int8_t, int8_t)':
C:/users/test/.platformio/packages/framework-arduinoespressif32/libraries/SPI/src/SPI.cpp:87:37: error: 'SCK' was not declared in this scope
         _sck = (_spi_num == FSPI) ? SCK : -1;
                                     ^~~
C:/users/test/.platformio/packages/framework-arduinoespressif32/libraries/SPI/src/SPI.cpp:87:37: note: suggested alternative: 'SCL'
         _sck = (_spi_num == FSPI) ? SCK : -1;
                                     ^~~
                                     SCL
C:/users/test/.platformio/packages/framework-arduinoespressif32/libraries/SPI/src/SPI.cpp:88:38: error: 'MISO' was not declared in this scope
         _miso = (_spi_num == FSPI) ? MISO : -1;
                                      ^~~~
C:/users/test/.platformio/packages/framework-arduinoespressif32/libraries/SPI/src/SPI.cpp:89:38: error: 'MOSI' was not declared in this scope
         _mosi = (_spi_num == FSPI) ? MOSI : -1;
                                      ^~~~
C:/users/test/.platformio/packages/framework-arduinoespressif32/libraries/SPI/src/SPI.cpp:90:36: error: 'SS' was not declared in this scope
         _ss = (_spi_num == FSPI) ? SS : -1;
                                    ^~
C:/users/test/.platformio/packages/framework-arduinoespressif32/libraries/SPI/src/SPI.cpp:90:36: note: suggested alternative: 'PS'
         _ss = (_spi_num == FSPI) ? SS : -1;
                                    ^~
                                    PS
*** [.pio\build\M5StampS3\lib1db\SPI\SPI.cpp.o] Error 1
```


Make sure you have install/updated `Espressif 32` platform in your PlatformIO IDE. This project was tested with version 6.9.0.
