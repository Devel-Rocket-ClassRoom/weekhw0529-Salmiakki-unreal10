#include <iostream>
#include <string>
#include "Utils.h"
#include"Homework01.h"
#include"Homework02.h"
using namespace std;

int main()
{
	Homework01_Run();
	Homework02_Run();
}
//블랙잭

// 딜러 카드 1장은 공개
// 첫패가 블랙잭일경우 즉시 승리
// 플레이어 히트/스탠드 선택
// 21 초과시 버스트
// 딜러는 17 이상이 될 때까지 히트
// 딜러가 버스트되면 플레이어 승리

//카드 비교
// 21-점수가 더 작은 참가자가 승리


