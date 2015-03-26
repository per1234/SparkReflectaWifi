/*  ReflectaArduinoCore.cpp - Library for exposing the core Arduino library functions over Reflecta*/#include "EReader.h"#include "Reflecta.h"#include "application.h"//#include "SD.h"char * stringBuffer = (char *)malloc(21);using namespace reflecta;using namespace reflectaFunctions;namespace reflectaArduinoCore{  /* int freeRam ()   {    extern int __heap_start, *__brkval;     int v;     return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);     }*/  void pinMode(TCPClient& client)  {    //anbr    int a,b;    //reflectaFrames::sendMessage("anbr: arduino set pinMode ");    //::pinMode(a=pop(), b=pop());    a=pop(client);    b=pop(client);    PinMode mode = (PinMode)b;        ::pinMode(a,mode);    //reflectaFrames::sendMessage("anbr: arduino: pin arg 1 :" + String(a, DEC));    //reflectaFrames::sendMessage("anbr: arduino: pin arg 2 :" + String(b, DEC));    //String(sequence, HEX)reflectaFrames::sendMessage(b);      }    void digitalRead(TCPClient& client)  {    push(::digitalRead(pop(client)), client);  }    void digitalWrite(TCPClient& client)  {    //anbr    int a,b;    //reflectaFrames::sendMessage("anbr: arduino: digitalWrite ");    //::digitalWrite(a=pop(), b=pop());    a=pop(client);    b=pop(client);    ::digitalWrite(a,b);    //reflectaFrames::sendMessage("anbr: arduino: pin arg 1 :" + String(a, DEC));    //reflectaFrames::sendMessage("anbr: arduino: pin arg 2 :" + String(b, DEC));      }    void analogRead(TCPClient& client)  {    push16(::analogRead(pop(client)), client);  }    void analogWrite(TCPClient& client)  {    int a,b;    a=pop(client);    b=pop(client);    ::analogWrite(a, b);    //::analogWrite(pop(), pop());  }  //char * stringBuffer = (char *)malloc(20);  void displayWif(TCPClient& client)  {    Serial.println(F("ReflectaArduinoCoreWifi.cpp: displayWif"));      //char stringBuffer[20];      int8_t count = pop(client);            	for (int i = 0; i < count; i++)      {	stringBuffer[i] = pop(client);      }    stringBuffer[count] = '\0';    //reflectaFrames::sendMessage("Free RAM: ");    //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);    reflectaFrames::sendMessage(stringBuffer, client);    //ereader.wake();    ereader.display_wif(stringBuffer, 0, 0);    ereader.show();    //ereader.sleep(0.1);    ereader.EPD.end();        //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);	  } /*void displayWifSram(TCPClient& client)  {      //char stringBuffer[20];      int8_t count = pop(client);            	for (int i = 0; i < count; i++)      {	stringBuffer[i] = pop(client);      }    stringBuffer[count] = '\0';    //reflectaFrames::sendMessage("Free RAM: ");    //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);    reflectaFrames::sendMessage(stringBuffer, client);    ereader.wake();        ereader.display_wif_sram(stringBuffer, 0, 0);    ereader.show_sram();        ereader.sleep(0.1);    //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);	  }*/File sd_file;  void writeToFile(TCPClient& client){    //buffer[20];  int8_t count = pop(client);  int8_t data;    for (int i = 0; i < count; i++)    {      data = pop(client);      if(sd_file){	sd_file.write(data);      }      //reflectaFrames::sendMessage(String(data, DEC));    }  //buffer[count] = '\0';  }     void putAscii(TCPClient& client)  {        int16_t x = pop16(client);    int16_t y = pop16(client);    //int8_t x = pop();    //int8_t y = pop();    int8_t count = pop(client);    for (int i = 0; i < count; i++)      {	stringBuffer[i] = pop(client);      }    stringBuffer[count] = '\0';    //ereader.wake();    ereader.put_ascii(x, y, stringBuffer, true);    //ereader.show();    //ereader.EPD.end();    //ereader.sleep(1);    //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);  } /*void putAsciiSram(TCPClient& client)  {        int16_t x = pop16(client);    int16_t y = pop16(client);    //int8_t x = pop();    //int8_t y = pop();    int8_t count = pop(client);    for (int i = 0; i < count; i++)      {	stringBuffer[i] = pop(client);      }    stringBuffer[count] = '\0';    //ereader.wake();    //ereader.put_ascii_sram(x, y, stringBuffer, true);    //ereader.show();    //ereader.sleep(1);    //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);  }*/      void ereaderWake(TCPClient& client)  {       ereader.wake();  }   void ereaderShow(TCPClient& client)  {       ereader.show();  }   /*void ereaderShowSram(TCPClient& client)  {       ereader.show_sram();  } */  /*void ereaderCpyImage(TCPClient& client)  {    reflectaFrames::sendMessage("ereader_cpy_image!", client);    //ereader.cpy_image();        //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);  }*/    void ereaderShowPartial(TCPClient& client)  {       int16_t first_line_no = pop16(client);       int8_t line_count = pop(client);              ereader.showPartial(first_line_no, line_count);       reflectaFrames::sendMessage("reflectaframesArduinoCore: ereader show partial "+String(first_line_no, DEC)+" , "+           String(line_count, DEC) , client);  }    /* void ereaderShowPartialSram(TCPClient& client)  {    int16_t first_line_no = pop16(client);    int8_t line_count = pop(client);        //ereader.showPartial_sram(first_line_no, line_count);  } */  void ereaderSleep(TCPClient& client)  {    int8_t time = pop(client);    ereader.sleep(time);  }     //char * writeFileName = (char *)malloc(20);  void openFileWrite(TCPClient& client)  {     ereader.wake();    int8_t count = pop(client);    //char writeFileName[count+1];        for (int i = 0; i < count; i++)      {	stringBuffer[i] = pop(client);      }    stringBuffer[count] = '\0';        sd_file = SD.open(stringBuffer, FILE_WRITE);    if(!sd_file){      reflectaFrames::sendMessage("e!", client);      ereader.sleep(1);    }      else{      sd_file.seek(0);    }    //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);  }  void closeFile(TCPClient& client){  sd_file.close();  //reflectaFrames::sendMessage(String(getFreeRam(), DEC), client);}void openFile(TCPClient& client){  //char stringBuffer[20];  int8_t count = pop(client);  for (int i = 0; i < count; i++)  {    stringBuffer[i] = pop(client);  }  stringBuffer[count] = '\0';  sd_file = SD.open(stringBuffer);  if(!sd_file){    Serial.println(F("Could not open write file"));    //reflectaFrames::sendMessage("e: o.file read");    //reflectaFrames::sendMessage("Open write file failed: ");    //error(FILE_NOT_FOUND_CODE);  }   } void readFile(TCPClient& client)  {        //buffer[20];    int8_t count = pop(client);    reflectaFrames::sendMessage(String(count, DEC), client);    int8_t data;    for (int i = 0; i < count; i++)      {	if(sd_file){	  data=sd_file.read();	}	push(data,client);	reflectaFrames::sendMessage(String(data, DEC), client);      }    //buffer[count] = '\0';    //reflectaFrames::sendMessage(String(data, DEC));      }  /*void SPI_send() {    uint8_t cs_pin = pop();  uint16_t length = pop();  // CS low  ::digitalWrite(cs_pin, LOW);    int8_t count = pop();    byte size = count;    byte buffer[size];        for (int i = 0; i < count; i++)    {      int8_t value = pop();      buffer[i] = value;    }   // send all data  for (uint16_t i = 0; i < length; ++i) {    SPI.transfer(buffer[i]);  }  // CS high  ::digitalWrite(cs_pin, HIGH);  }  */  /*    void PWM_start() {  ::analogWrite(pop(), 128);  // 50% duty cycle  }  void PWM_stop() {  ::analogWrite(pop(), 0);  }  */    /*void wireBeginMaster()  {    Wire.begin();  }    void wireRequestFrom()  {    int a, b;    a=pop();    b=pop();    //Wire.requestFrom(pop(), pop());    Wire.requestFrom(a,b);      }      void wireRequestFromStart()  {    int a,b;    a=pop();    b=pop();    Wire.requestFrom(a,b, false);    //Wire.requestFrom(pop(), pop(), false);  }    void wireAvailable()  {    push(Wire.available());  }    void wireRead()  {    if (Wire.available())      push(Wire.read());    else      reflectaFrames::sendEvent(Error, WireNotAvailable);  }    void wireBeginTransmission()  {    Wire.beginTransmission(pop());  }    // TODO: Support variants write(string) and write(data, length)  void wireWrite()  {    Wire.write(pop());  }    void wireEndTransmission()  {    Wire.endTransmission();  }    Servo servos[MAX_SERVOS];  // TODO: Support variant attach(pin, min, max)  void servoAttach()  {      int8_t pin = pop();      servos[pin].attach(pin);  }  void servoDetach()  {      servos[pop()].detach();  }  void servoWrite()  {    int a,b;    a=pop();    b=pop();          servos[a].write(b);      //servos[pop()].write(pop());  }    void servoWriteMicroseconds()  {      servos[pop()].writeMicroseconds(pop16());  }    // TODO: Support variant pulseIn(pin, value, timeout)  void pulseIn()  {    int a,b;    a=pop();    b=pop();        // BUGBUG: Broken, returns a 32 bit result    //push(::pulseIn(pop(), pop()));    push(::pulseIn(a, b));    }  */    // Bind the Arduino core methods to the ardu1 interface  void setup()  {        reflectaFunctions::bind("ardu1", pinMode);    reflectaFunctions::bind("ardu1", digitalRead);    reflectaFunctions::bind("ardu1", digitalWrite);    reflectaFunctions::bind("ardu1", analogRead);    reflectaFunctions::bind("ardu1", analogWrite);    reflectaFunctions::bind("ardu1", displayWif);    reflectaFunctions::bind("ardu1", openFileWrite);    reflectaFunctions::bind("ardu1", closeFile);    reflectaFunctions::bind("ardu1", writeToFile);    reflectaFunctions::bind("ardu1", openFile);    reflectaFunctions::bind("ardu1", readFile);    reflectaFunctions::bind("ardu1", putAscii);    reflectaFunctions::bind("ardu1", ereaderWake);    reflectaFunctions::bind("ardu1", ereaderShow);    reflectaFunctions::bind("ardu1", ereaderSleep);    reflectaFunctions::bind("ardu1", ereaderShowPartial);    //reflectaFunctions::bind("ardu1", displayWifSram);    //reflectaFunctions::bind("ardu1", putAsciiSram);    //reflectaFunctions::bind("ardu1", ereaderShowSram);    //reflectaFunctions::bind("ardu1", ereaderShowPartialSram);    //reflectaFunctions::bind("ardu1", ereaderCpyImage);    /*    reflectaFunctions::bind("ardu1", wireBeginMaster);        reflectaFunctions::bind("ardu1", wireRequestFrom);    reflectaFunctions::bind("ardu1", wireRequestFromStart);    reflectaFunctions::bind("ardu1", wireAvailable);    reflectaFunctions::bind("ardu1", wireRead);       reflectaFunctions::bind("ardu1", wireBeginTransmission);    reflectaFunctions::bind("ardu1", wireWrite);    reflectaFunctions::bind("ardu1", wireEndTransmission);        reflectaFunctions::bind("ardu1", servoAttach);    reflectaFunctions::bind("ardu1", servoDetach);    reflectaFunctions::bind("ardu1", servoWrite);    reflectaFunctions::bind("ardu1", servoWriteMicroseconds);    reflectaFunctions::bind("ardu1", pulseIn);    */      }};