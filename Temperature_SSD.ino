#define analogPin A0
const int anode1 = 6;
const int anode2 = 5;

const int A = 7; //Section 'A' of the digit
const int B = 8; //Section 'B' of the digit
const int C = 9; //Section 'C' of the digit
const int D = 10; //Section 'D' of the digit
const int E = 11; //Section 'E' of the digit
const int F = 12; //Section 'F' of the digit
const int G = 13; //Section 'G' of the digit
const int DP = 3; //Decimal point of the digit

void setup() {
  Serial.begin(9600);

  pinMode(analogPin,0);
  pinMode(anode1, OUTPUT);
  pinMode(anode2, OUTPUT);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);

  
  digitalWrite(A, 0);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 0);
  digitalWrite(E, 0);
  digitalWrite(F, 0);
  digitalWrite(G, 0);
  digitalWrite(DP, 0);
}


void decodeAndWrite(unsigned int value, unsigned int digit)
{

  switch (digit)
  {
    
    case 1:
      digitalWrite(anode1, 0);
      digitalWrite(anode2, 1);
     
      digitalWrite(DP, 0);
      break;

    case 2: //Turns “on” the decimal point
      digitalWrite(anode1, 1);
      digitalWrite(anode2, 0);
     
      digitalWrite(DP, 1);
      break;

   
    

    default:
      digitalWrite(anode1, 1);
      digitalWrite(anode2, 1);
     
      digitalWrite(DP, 0);
      break;

  }

  switch (value) {

    case 0:
      digitalWrite(A, 1);
      digitalWrite(F, 1);
      digitalWrite(E, 1);
      digitalWrite(D, 1);
      digitalWrite(C, 1);
      digitalWrite(B, 1);
      digitalWrite(G, 0);
      break;

    case 1:
      digitalWrite(C, 1);
      digitalWrite(B, 1);
      digitalWrite(A, 0);
      digitalWrite(D, 0);
      digitalWrite(E, 0);
      digitalWrite(F, 0);
      digitalWrite(G, 0);
      break;

    case 2:
      digitalWrite(A, 1);
      digitalWrite(G, 1);
      digitalWrite(E, 1);
      digitalWrite(D, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 0);
      digitalWrite(F, 0);
      break;

    case 3:
      digitalWrite(C, 1);
      digitalWrite(B, 1);
      digitalWrite(A, 1);
      digitalWrite(G, 1);
      digitalWrite(D, 1);
      digitalWrite(E, 0);
      digitalWrite(F, 0);
      break;

    case 4:
      digitalWrite(F, 1);
      digitalWrite(B, 1);
      digitalWrite(G, 1);
      digitalWrite(C, 1);
      digitalWrite(A, 0);
      digitalWrite(D, 0);
      digitalWrite(E, 0);
      break;

    case 5:
      digitalWrite(A, 1);
      digitalWrite(F, 1);
      digitalWrite(G, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      digitalWrite(B, 0);
      digitalWrite(E, 0);
      break;

    case 6:
      digitalWrite(C, 1);
      digitalWrite(G, 1);
      digitalWrite(E, 1);
      digitalWrite(D, 1);
      digitalWrite(F, 1);
      digitalWrite(A, 0);
      digitalWrite(B, 0);
      break;

    case 7:
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      digitalWrite(E, 0);
      digitalWrite(F, 0);
      digitalWrite(G, 0);
      break;

    case 8:
      digitalWrite(A, 1);
      digitalWrite(F, 1);
      digitalWrite(B, 1);
      digitalWrite(G, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      digitalWrite(E, 1);
      break;

    case 9:
      digitalWrite(A, 1);
      digitalWrite(F, 1);
      digitalWrite(B, 1);
      digitalWrite(G, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      digitalWrite(E, 0);
      break;



    default:

      break;
  }
}

void loop() {
  
    float r = 10000;
float logrt, rt, T, F;
float a = 0.9059557119e-03, b = 2.484884034e-04, c = 2.040119886e-07;
float adcVal, i, numSamples = 50;

   adcVal = 0;
  for (i = 0; i < numSamples; i++)
  {
    adcVal = adcVal + analogRead(analogPin);
  }
  adcVal = adcVal / 50;
  rt = r * (1023.0 / (float)adcVal - 1.0);
  logrt = log(rt);
  T = (1.0 / (a + b*logrt + c*logrt*logrt*logrt));
  T = T - 273.15;
  F = (T * 9.0)/ 5.0 + 32.0; 
                            // convert to Celsius
  Serial.println("Temperature in Celcius=" + String(T));
  int tensPlace = 0;
  int onesPlace = 0;
   int segment;

  //calculating the “place”
  tensPlace = T / 10;

  //stating the digit on the 7 segment
  segment = 2;

  //call to the function we defined eariler
  decodeAndWrite(round(tensPlace), segment);

  //a brief pause so that we can see the number
  delay(10);

  //removing the tens place
  T = T - tensPlace * 10;
  //repeating for the other “places”
  onesPlace = T;
  segment = 1;
  decodeAndWrite(round(onesPlace), segment);
  delay(10);
  

}
