// Potentiometer is connected to GPIO 33 and 32
const int potPin1 = 33;
const int potPin2 = 32;

//resistance of reference resistors
const int R1 = 174;//174k ohms
//const int R2 =;

// variable for storing the potentiometer value
int potValue1 = 0;
int potValue2 = 0;

// represent last value
float preRs1 = 0;

void setup(void) {
  Serial.begin(115200);
  //Serial.println("CLEARDATA"); //clears up any data left from previous projects
  //Serial.println("LABEL,Time,Timer,Read val, Constant"); //always write LABEL, so excel knows the next things will be the names of the columns (instead of Acolumn you could write Time for instance)
  //Serial.println("RESETTIMER"); //resets timer to 0
  delay(3000);
}

void loop(void) {
  // Reading potentiometer value
  potValue1 = analogRead(potPin1);//12bit read
  //potValue2 = analogRead(potPin2);

  //this part is used to test portvalue. Range:0-4095
  //Serial.println(potValue1);
  //Serial.print(",");
  //Serial.println(potValue2);
  
  float V1 = resolution(potValue1);//transfre to voltage
  //float V2 = resolution(potValue2);

  //this part is used to test voltage. Range:0-3.3
  //Serial.print(V1);
  //Serial.print(",");
  //Serial.println(V2);

  float Rs1 = votageToR(V1, R1);
  if(preRs1 == 0){
    preRs1 = Rs1;
  } else if(abs(Rs1 - preRs1)> 20) {
    Rs1 = preRs1;
  } else {
    preRs1 = Rs1;  
  }
  //float Rs2 = votageToR(V2, R2);

  //this part is used to test resistance
  Serial.println(Rs1);
  Serial.print(",");
  Serial.println(465);

  //Serial.print("DATA,TIME, TIMER,"); //writes the time in the first column A and the time since the measurements started in column B
  //Serial.print(newPotValue);
  //Serial.println("");
  delay(200);
}

// 12bit resolution, range 0-4095 => 0-3.3V
float resolution(int potValue) {
  return potValue*1.0/4095.0*3.3;
}

// transfer voltage value to resistance
float votageToR(float voltage, int res) {
  return voltage*res/(3.3-voltage);
}
