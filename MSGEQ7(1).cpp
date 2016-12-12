#include "MSGEQ7.h"

MSGEQ7::MSGEQ7()
{
	MSGEQ7::Pin = A0;
	MSGEQ7::strobePin = 4;
	MSGEQ7::resetPin = 5;
}

void MSGEQ7::init(int value, int strobePin, int resetPin)
{
	MSGEQ7::Pin = value; //입력한 값들 대입
	MSGEQ7::strobePin = strobePin;
	MSGEQ7::resetPin = resetPin;

	//- pinMode(pin, mode) : 특정 디지털용 pin을 입력용으로 할지 출력용으로 할지 설정
	pinMode(MSGEQ7::Pin, INPUT); // 입력 핀으로 설정
	pinMode(MSGEQ7::strobePin, OUTPUT); // 출력 핀으로 설정
	pinMode(MSGEQ7::resetPin, OUTPUT);
	analogReference(DEFAULT);
	// 아날로그 입력에 사용하는 기준전압을 사용하는 보드의 기준 전압으로 설정.
}

void MSGEQ7::init()
{
	pinMode(MSGEQ7::Pin, INPUT); //INPUT 입력핀으로 설정
	pinMode(MSGEQ7::strobePin, OUTPUT); //OUTPUT 출력핀으로 설정
	pinMode(MSGEQ7::resetPin, OUTPUT);
	analogReference(DEFAULT); //기준전압을 설정하는 함수
							  // DEFAULT = 사용하는 보드의 기준 전압을 아날로그 입력에 사용.
}

void MSGEQ7::poll() //다중입출력 함수
{
	digitalWrite(MSGEQ7::resetPin, HIGH); //전압 on
	digitalWrite(MSGEQ7::resetPin, LOW); //전압 off
										 //digitalWrite(핀, 모드) HIGH =1, LOW =0

	for (int i = 0; i < 7; i++) {
		digitalWrite(MSGEQ7::strobePin, LOW);
		//strobePin에 전압 0
		delayMicroseconds(30); //출력을 위해 30만분의1초 지연
		MSGEQ7::spectrumValues[i] = analogRead(MSGEQ7::Pin);
		//analogRead(pin) : pin에 연결된 아날로그 신호 선의 전압 값을 디지털 값으로 읽어 들이는 함수
		//Pin의 값을 Values배열에 차례대로 저장
		digitalWrite(MSGEQ7::strobePin, HIGH);
		//strobePin에 전압을 준다
	}

	digitalWrite(MSGEQ7::resetPin, LOW); //  확실히 하기 위해
	digitalWrite(MSGEQ7::strobePin, HIGH); //
	delay(10); //0.001초 딜레이
}

int MSGEQ7::getValue(int index)
{
	return MSGEQ7::spectrumValues[index];
	//왼쪽 값을 저장한 배열의 index위치에 저장된 값을 반환
}
