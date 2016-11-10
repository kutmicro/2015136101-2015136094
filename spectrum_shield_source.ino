//스펙트럼 쉴드 핀 선언

#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1


//Define LED connections on the Arduino/Shield

int LED[] = {7, 8, 9, 10, 11, 12, 13};


//스펙트럼 변수 정의

int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7]; 
int i;


//루프 설정

void setup() {
 for(i=0; i<7; i++){ // LED배열 초기화 설정
  
    pinMode(LED[i], OUTPUT);
    //pinMode(핀번호, 모드) (모드-> OUTPUT,INPUT,INPUT_PULLUP)
    digitalWrite(LED[i], LOW);
    //digitalWrite(핀번호, 신호) (신호-> HIGH,LOW)
  }

  
  //스펙트럼 쉴드 초기화 설정

  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  

  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);


  //스펙트럼 분석기 초기화 설정

  digitalWrite(STROBE, LOW);
  delay(1);

  digitalWrite(RESET, HIGH);
  delay(1);

  digitalWrite(STROBE, HIGH);
  delay(1);

  digitalWrite(STROBE, LOW);
  delay(1);

  digitalWrite(RESET, LOW);

}

/*************메인 루프 함수**************/
void loop() {
  
  Read_Frequencies();
  
  Graph_Frequencies();

  delay(50);
  
}

/*************스펙트럼 쉴드에서 주파수******************/
void Read_Frequencies(){  //각각의 밴드에서 주파수를 읽기
  
  for (freq_amp = 0; freq_amp<7; freq_amp++) {

    Frequencies_One[freq_amp] = analogRead(DC_One);
    //analogRead(pin)아날로그 신호를 디지털로 변환하여 수치 반한.
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 

    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);

  }
}

/**************주파수에 맞게 LED 켜기*****************/

void Graph_Frequencies(){

   for( i= 0; i<7; i++) {
     if(Frequencies_Two[i] > Frequencies_One[i]){

        digitalWrite(LED[i], HIGH);
        delay(Frequencies_Two[i]);
        digitalWrite(LED[i], LOW);

     }
     else{
     
        digitalWrite(LED[i], HIGH);
        delay(Frequencies_One[i]);
        digitalWrite(LED[i], LOW);

     }
   }
}
