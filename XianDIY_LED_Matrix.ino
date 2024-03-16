#include <Wire.h>

const int i2c_addr = 0x70;

uint8_t buf[8];
String input_data;

String cmds[32];

String X = "0,96,1,12,2,0,3,0,4,128,5,2,6,0,7,1,8,0,9,0,10,128,11,2,12,0,13,0,14,64,15,4";
String I = "0,192,1,1,2,128,3,0,4,128,5,0,6,128,7,0,8,128,9,0,10,128,11,0,12,128,13,0,14,192,15,1";
String A = "0,64,1,2,2,64,3,2,4,64,5,2,6,64,7,2,8,192,9,3,10,64,11,2,12,0,13,0,14,128,15,1";
String N = "0,32,1,2,2,32,3,2,4,32,5,3,6,32,7,2,8,160,9,2,10,32,11,2,12,96,13,2,14,32,15,2";
String D = "0,96,1,0,2,160,3,0,4,32,5,0,6,32,7,1,8,32,9,1,10,32,11,1,12,160,13,0,14,96,15,0,";
String Y = "0,128,1,0,2,128,3,0,4,128,5,0,6,128,7,0,8,128,9,0,10,64,11,1,12,0,13,0,14,32,15,2";
String H = "0,64,1,4,2,64,3,4,4,64,5,4,6,64,7,4,8,192,9,7,10,64,11,4,12,64,13,4,14,64,15,4";
String E = "0,192,1,3,2,64,3,0,4,64,5,0,6,64,7,0,8,192,9,3,10,64,11,0,12,64,13,0,14,192,15,3";
String L = "0,192,1,3,2,64,3,0,4,64,5,0,6,64,7,0,8,64,9,0,10,64,11,0,12,64,13,0,14,64,15,0";
String O = "0,192,1,3,2,64,3,2,4,64,5,2,6,64,7,2,8,64,9,2,10,64,11,2,12,64,13,2,14,192,15,3";
String W = "0,128,1,2,2,128,3,2,4,0,5,1,6,64,7,5,8,64,9,4,10,0,11,0,12,32,13,8,14,32,15,8";
String R = "0,64,1,4,2,64,3,4,4,64,5,4,6,64,7,4,8,192,9,7,10,64,11,2,12,64,13,2,14,192,15,3";

void system_setup() {
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x21);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(10);
}

void display_setup() {
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x81);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(10);
}

void row_int_set() {
  Wire.beginTransmission(i2c_addr);
  Wire.write(0xA0);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(10);
}

void dimming_set() {

  Wire.beginTransmission(i2c_addr);
  Wire.write(0xE1);
  Wire.write(0x01);
  Wire.endTransmission();
}

void led_update_all(int addr_poi) {
  Wire.beginTransmission(i2c_addr);
  Wire.write(addr_poi);
  for(int i=0; i<8; i++) {
    Wire.write(buf[i]);
    Wire.write(0);
  }
  Wire.endTransmission();
}

void led_update(int addr_poi, int bu) {
  Wire.beginTransmission(i2c_addr);
  Wire.write(addr_poi);
  Wire.write(bu);
  Wire.endTransmission();
  //Serial.print(addr_poi);
  //Serial.print("//");
  //Serial.println(bu);
}


void buffer_clear() {

  for(int i=0; i<8; i++) {
    buf[i] = 0x00;
  }
  led_update_all(0x00);
}

int split(String data, char delimiter, String *dst) {
  int index = 0;
  int datalength = data.length();

  for(int i=0; i< datalength; i++){
    
    index = 0;
    int datalength = data.length();

    for(int i=0; i<datalength; i++) {
      char tmp = data.charAt(i);
      if(tmp == delimiter) {
        index++;
      } else {
        dst[index] += tmp;
      }
    }
    return (index +1);
  }
  return 0;
}


void demo1() {
  buffer_clear();
  int led_addr[8] = {1,3,15,31,63,127,255};

  for (int i=0; i<16; i++){
    for (int j=0; j<8; j++) {
      led_update(i,led_addr[j]);
      delay(100);
    }
  }
}

void demo2() {
  buffer_clear();
  int led_addr[8] = {1,3,15,31,63,127,255};

  for (int j=0; j<8; j++){
    for (int i=0; i<16; i++) {
      led_update(i,led_addr[j]);
    }
    delay(100);
  }

}


void demo3() {
  buffer_clear();
  int led_addr[8] = {1,2,4,8,16,32,64,128};

  for (int j=0; j<8; j++){
    for (int i=0; i<16; i++) {
      led_update(i,led_addr[j]);
    }
    delay(100);
  }

}

void demo4() {
  buffer_clear();
  int led_addr[8] = {1,2,4,8,16,32,64,128};

  for (int j=0; j<8; j++){
    for (int i=0; i<8; i++) {
      led_update(i*2,led_addr[j]);
    }
    delay(100);
  }
}

void XIAN_DIY() {
  led_matrix_update(X);
  delay(1000);
  led_matrix_update(I);
  delay(1000);
  led_matrix_update(A);
  delay(1000);
  led_matrix_update(N);
  delay(1000);
  led_matrix_update(D);
  delay(1000);
  led_matrix_update(I);
  delay(1000);
  led_matrix_update(Y);
  delay(1000);
}

void hello_world() {
  led_matrix_update(H);
  delay(1000);
  led_matrix_update(E);
  delay(1000);
  led_matrix_update(L);
  delay(1000);
  led_matrix_update(L);
  delay(1000);
  led_matrix_update(O);
  delay(1000);
  led_matrix_update(W);
  delay(1000);
  led_matrix_update(O);
  delay(1000);
  led_matrix_update(R);
  delay(1000);
  led_matrix_update(L);
  delay(1000);
  led_matrix_update(D);
  delay(1000);
}

void led_matrix_update(String buff) {

  buff.trim();
  split(buff,',',cmds);
  
  for (int i=0; i<16; i++) {
      led_update(cmds[i*2].toInt(),cmds[i*2+1].toInt());      
    }
    
  for(int i=0; i<32; i++) {
      cmds[i] = "";
    
    }
}



void led_serial_update() {
  if(Serial.available() > 0) {
    input_data = Serial.readString();
    led_matrix_update(input_data);
  } 
}


void setup() {
  Wire.begin();
  Serial.begin(9600);
 
  system_setup();
  display_setup();
  row_int_set();
  dimming_set();
  buffer_clear();
  delay(1000);
  XIAN_DIY();
  hello_world();
  buffer_clear();
  Serial.println("demo1");
  demo1();
  Serial.println("demo2");
  demo2();
  Serial.println("demo3");
  demo3();
  Serial.println("demo4");
  demo4();
  buffer_clear();
}

void loop() {

  led_serial_update();
  
}
