#pragma once
#include <iostream>
#include <string>
#include "Utils.h"
using namespace std;

//string Suites[4] = { "♦",  "♣", "♥", "♠" };
//string CardNames[] = { "2",  "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
//enum CardValue { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10, ACE = 11 };
//
//enum GameStatus { DEFAULT, STANDED, BUSTED };
//
//struct Card
//{
//	string suite; // 카드 슈트 : 
//	string name; // 카드 이름 : 2~10, J, Q, K, A
//	int value = 0;  // 카드 값 : 1~11
//};
//
//struct CardPiles
//{
//	Card* Cards = nullptr; // 덱
//	int Size = 0;
//};
//struct Participant
//{
//	string name; // 참가자 이름
//	CardPiles Hand; // 참가자 패
//	int Points = 0;
//};
//
////초기덱(52장) 만들기		/리턴값 CardPiles.Cards 동적할당
//CardPiles CreateDeck();
////셔플
//void ShuffleDeck(CardPiles& Deck);
//// 드로우
//void AddCard(const CardPiles& DrawnCards, Participant& Player);
//
//void Draw(Participant& Player, CardPiles& Deck, int HowMany = 1);
//
//
//// 카드 보여주기
//void ShowCards(const CardPiles& Deck, bool hide = false);
//
////점수 계산
//int CalculatePoints(Participant& Player);
//
//// 히트/스탠드
//GameStatus HitOrStand(Participant& Player, CardPiles& Deck, bool IsPlayer = false);
//
//// UI
//void ShowUI(Participant& Dealer, Participant& Player, bool hide = true);
//
//
void Homework02_Run();
