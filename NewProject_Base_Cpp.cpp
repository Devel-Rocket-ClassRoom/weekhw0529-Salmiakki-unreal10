#include <iostream>
#include <string>
#include "Utils.h"
using namespace std;


//char Suites[4] = { '♦',  '♣', '♥', '♠' };
char Suites[4] = { 'D',  'C', 'H', 'S' };
string CardNames[] = { "2",  "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
enum CardValue { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10, ACE = 11 };


struct Card
{
	char suite = 'D'; // 카드 슈트 : 
	string name; // 카드 이름 : 2~10, J, Q, K, A
	int value;  // 카드 값 : 1~11
};

struct CardPiles
{
	Card* Cards; // 덱
	int Size;
};
struct Participant
{
	char* name; // 참가자 이름
	Card* Hand; // 참가자 패
};

//초기덱(52장) 만들기		/리턴값.Cards 동적할당
CardPiles CreateDeck()
{
	CardPiles D;
	Card* Deck = new Card[52];
	int index = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			Deck[index].suite = Suites[i];
			Deck[index].name = CardNames[j];
			if (j < 9)
				Deck[index].value = j + 2;
			else if (j < 12)
				Deck[index].value = 10;
			else
				Deck[index].value = 11;
			cout << Deck[index].suite << Deck[index].name << " " << Deck[index].value << endl;
			index++;
		}
	}
	D.Cards = Deck;
	D.Size = index;
	return D;
}

//셔플
void ShuffleDeck(CardPiles& Deck)
{
	for (int i = (Deck.Size-1); i > 0; i--)
	{
		Card temp = (Deck.Cards)[i];
		int RandomIndex = GetRandomRange(0, i);
		Deck.Cards[i] = Deck.Cards[RandomIndex];
		Deck.Cards[RandomIndex] = temp;
		cout << Deck.Cards[i].suite << Deck.Cards[i].name << " " << Deck.Cards[i].value << endl;

	}
}

// 드로우
Card* DrawDeck(Card* Deck, int HowMany=1)		//리턴값 동적할당
{
	while (HowMany > 0)
	{
		Card* DrawnCards = new Card[HowMany];
		for (int i = 0; i < HowMany; i++)
		{
			DrawnCards[i] = Deck[i];
			Deck[i] = Deck[sizeof(*Deck) / sizeof(Card) - 1 - i];
		}
		return DrawnCards;
	}
}



int main()
{
//플레이어, 딜러 인스턴스 생성

	//Participant Dealer;
	//Participant Player;
	CardPiles PlayingDeck = CreateDeck();
	
	ShuffleDeck(PlayingDeck);
	
	/*for (Card c : PlayingDeck)
	{
		cout << c.suite << c.name << " ";
	}*/
	//cout << PlayingDeck[0].suite << PlayingDeck[0].name << " " << PlayingDeck[0].value << endl;
}

//블랙잭

// 참가자의 패를 가변 배열로 동적할당 
// 참가자에게 각각 카드를 덱에서 2장씨 가져옴
// 딜러 카드 1장은 공개
// 첫패가 블랙잭일경우 즉시 승리
// 플레이어 히트/스탠드 선택
// 21 초과시 버스트
// 딜러는 17 이상이 될 때까지 히트
// 딜러가 버스트되면 플레이어 승리

//카드 비교
// 21-점수가 더 작은 참가자가 승리


