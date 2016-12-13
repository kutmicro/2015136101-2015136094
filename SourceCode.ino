#include <MSGEQ7.h>
#include <Adafruit_NeoPixel.h>
#define MIN_K_value 100
#define MAX_K_value 200
int K_value = 100;
MSGEQ7 eq;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(40, 6, NEO_GRB + NEO_KHZ800);
//네오픽셀LED의 개수, 네오픽셀이 연결된 아두이노의 핀 번호, 네오픽셀의 타입에 따라 바뀌는 flag

uint32_t color_map[40] =
{ //위치별 픽셀 색상설정. 
   0x00ff5040,0x00ff50ff,0x000050ee,0x0000ff80,0x0020ff20,0x00efef00,0x00ff5000,0x00ff0000,
  0x00ff5040,0x00ff50ff,0x000050ee,0x0000ff80,0x0020ff20,0x00efef00,0x00ff5000,0x00ff0000,
  0x00ff5040,0x00ff50ff,0x000050ee,0x0000ff80,0x0020ff20,0x00efef00,0x00ff5000,0x00ff0000,
  0x00ff5040,0x00ff50ff,0x000050ee,0x0000ff80,0x0020ff20,0x00efef00,0x00ff5000,0x00ff0000,
  0x00ff5040,0x00ff50ff,0x000050ee,0x0000ff80,0x0020ff20,0x00efef00,0x00ff5000,0x00ff0000
};

void setup() {
  eq.init();//이퀄라이저를 사용하기 시작
  pixels.begin();//네오픽셀을 초기화 하기위해 모든 LED를 OFF 시킴(모든 명령이나 제어문 제거)
  pixels.clear();//네오픽셀 초기화
}

void on_pixel(int index) {
  pixels.setPixelColor(index, color_map[index]); //index위치에 색상을 설정
}

void loop() {
  eq.poll(); //digitalWrite함수를 이용하여 다중입출력을 제어하는 poll함수
  //소리 입력 받음
  int max_v = 0;
  pixels.clear(); //네오픽셀 초기화
  for (int i = 0; i < 7; i++) { //입력받은 신호에 따라 네오픽셀을 제어             
    int p = eq.getValue(i); //i번째의 spectrumvalues 값
    max_v = (p>max_v ?  p: max_v); //p와 max_v중 큰값을 max_v에 저장
    for (int j = 0; j < 5; j++) { //네오픽셀의 5번째 행까지 반복
      if (p > K_value*(5 - j)) { //p값이 K_value*(5-j)보다 크면
        on_pixel(i + (8 * j));
        //i+(8*j)번째 픽셀을 color_map에 지정된 색으로 설정
      }
    }
       }
  //마지막 열은 최대 음량을 출력
  for (int j = 0; j < 5; j++) {
    if (max_v > K_value*(5 - j)) { //저장한 max_v값이 K_value*(5-j)값보다 크면
      on_pixel(7 + (8 * j));
      //7+(8*j)번째 픽셀을 color_map[7+(8*j)]색으로 설정
    }
  }
  K_value = constrain(max_v / 5, MIN_K_value, MAX_K_value);
  // max_v/5의 값을 ( MIN_K_value ~ MAX_K_value ) 사이의 값으로 한정
  //5등분 분할의 기준을 음악의 최대값의 크기에 맞게 조절
  pixels.show(); //코드에서 작성한 명령을 NeoPixel로 넘겨 실제로 LED를 켜고 끄는 명령을 하게 하는 함수
  delay(100); // 0.1 초 딜레이를 준다.
}
