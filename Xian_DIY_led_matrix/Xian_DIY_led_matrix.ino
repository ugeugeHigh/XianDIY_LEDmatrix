#include <Wire.h>

const int i2c_addr = 0x70;

uint8_t buf[8];
String input_data;

String cmds[32];

int X[16] = {96,12,0,0,128,2,0,1,0,0,128,2,0,0,64,4};
int I[16] = {192,1,128,0,128,0,128,0,128,0,128,0,128,0,192,1};
int A[16] = {64,2,64,2,64,2,64,2,192,3,64,2,0,0,128,1};
int N[16] = {32,2,32,2,32,3,32,2,160,2,32,2,96,2,32,2};
int D[16] = {96,0,160,0,32,0,32,1,32,1,32,1,160,0,96,0};
int Y[16] = {128,0,128,0,128,0,128,0,128,0,64,1,0,0,32,2};

int H[16] = {64,4,64,4,64,4,64,4,192,7,64,4,64,4,64,4};
int E[16] = {192,3,64,0,64,0,64,0,192,3,64,0,64,0,192,3};
int L[16] = {192,3,64,0,64,0,64,0,64,0,64,0,64,0,64,0};
int O[16] = {192,3,64,2,64,2,64,2,64,2,64,2,64,2,192,3};
int W[16] = {128,2,128,2,0,1,64,5,64,4,0,0,32,8,32,8};
int R[16] = {64,4,64,4,64,4,64,4,192,7,64,2,64,2,192,3};



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
  Serial.print(addr_poi);
  Serial.print("//");
  Serial.println(bu);
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

String arrayToString(int *d) {
   String tmp="";
   for(int i=0; i<16; i++) {
      tmp += String(i)+","+String(d[i]);
      if(i != 15) {
        tmp += ",";
      }
   }
   Serial.println(tmp);
   return tmp;
}

void XIAN_DIY() {
  
  led_matrix_update(arrayToString(X));
  delay(1000);
  led_matrix_update(arrayToString(I));
  delay(1000);
  led_matrix_update(arrayToString(A));
  delay(1000);
  led_matrix_update(arrayToString(N));
  delay(1000);
  led_matrix_update(arrayToString(D));
  delay(1000);
  led_matrix_update(arrayToString(I));
  delay(1000);
  led_matrix_update(arrayToString(Y));
  delay(1000);
}

void hello_world() {
  led_matrix_update(arrayToString(H));
  delay(1000);
  led_matrix_update(arrayToString(E));
  delay(1000);
  led_matrix_update(arrayToString(L));
  delay(1000);
  led_matrix_update(arrayToString(L));
  delay(1000);
  led_matrix_update(arrayToString(O));
  delay(1000);
  led_matrix_update(arrayToString(W));
  delay(1000);
  led_matrix_update(arrayToString(O));
  delay(1000);
  led_matrix_update(arrayToString(R));
  delay(1000);
  led_matrix_update(arrayToString(L));
  delay(1000);
  led_matrix_update(arrayToString(D));
  delay(1000);
}

void led_matrix_update(String buff) {

  buff.trim();
  split(buff,',',cmds);
  
  for (int i=0; i<16; i++) {
    if(cmds[i*2] != "") {
      led_update(cmds[i*2].toInt(),cmds[i*2+1].toInt());
    }
       
        
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
  buffer_clear();
  XIAN_DIY();
  hello_world();
  
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
