#include <iostream>
#include <string>
#include"Homework02.h"
#include "Utils.h"
using namespace std;


string Suites[4] = { "♦",  "♣", "♥", "♠" };
string CardNames[] = { "2",  "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
enum CardValue { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10, ACE = 11 };

enum GameStatus { DEFAULT, STANDED, BUSTED };

struct Card
{
	string suite; // 카드 슈트 : 
	string name; // 카드 이름 : 2~10, J, Q, K, A
	int value = 0;  // 카드 값 : 1~11
};

struct CardPiles
{
	Card* Cards = nullptr; // 덱
	int Size = 0;
};
struct Participant
{
	string name; // 참가자 이름
	CardPiles Hand; // 참가자 패
	int Points = 0;
};

//초기덱(52장) 만들기		/리턴값 CardPiles.Cards 동적할당
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
			//cout << Deck[index].suite << Deck[index].name << " " << Deck[index].value << endl;
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
	for (int i = (Deck.Size - 1); i > 0; i--)
	{
		Card temp = (Deck.Cards)[i];
		int RandomIndex = GetRandomRange(0, i);
		Deck.Cards[i] = Deck.Cards[RandomIndex];
		Deck.Cards[RandomIndex] = temp;
		//cout << Deck.Cards[i].suite << Deck.Cards[i].name << " " << Deck.Cards[i].value << endl;

	}
}

// 드로우
void AddCard(const CardPiles& DrawnCards, Participant& Player)
{
	int temp = Player.Hand.Size;
	Card* OldHand = Player.Hand.Cards;
	Card* NewHand = new Card[temp + DrawnCards.Size];
	for (int i = 0; i < temp; i++)
	{
		NewHand[i] = OldHand[i];
	}
	for (int i = 0; i < DrawnCards.Size; i++)
	{
		NewHand[temp + i] = DrawnCards.Cards[i];
	}
	Player.Hand.Cards = NewHand;
	delete[] OldHand;
	Player.Hand.Size += DrawnCards.Size;
}

void Draw(Participant& Player, CardPiles& Deck, int HowMany = 1)
{
	if (HowMany > Deck.Size)
	{
		HowMany = Deck.Size;
	}

	CardPiles DrawnCards;
	DrawnCards.Cards = new Card[HowMany];
	for (int i = 0; i < HowMany; i++)
	{
		DrawnCards.Cards[i] = Deck.Cards[i];

	}
	for (int i = 0; i < Deck.Size - HowMany; i++)
	{
		Deck.Cards[i] = Deck.Cards[HowMany + i];
	}
	Deck.Size -= HowMany;
	DrawnCards.Size = HowMany;
	AddCard(DrawnCards, Player);
	delete[] DrawnCards.Cards;
}



// 카드 보여주기
void ShowCards(const CardPiles& Deck, bool hide = false)
{
	for (int i = 0; i < Deck.Size; i++)
	{
		if (hide == true && i == 0)
		{
			cout << "[??]" << endl;
			i++;
		}
		cout << "[" << Deck.Cards[i].suite << Deck.Cards[i].name << "]" << endl;
	}
}

//점수 계산
int CalculatePoints(Participant& Player)
{
	int Points = 0;
	int AceCount = 0;
	for (int i = 0; i < Player.Hand.Size; i++)
	{
		Points += Player.Hand.Cards[i].value;
		if (Player.Hand.Cards[i].value == ACE)
			AceCount++;
	}
	while (AceCount > 0 && Points > 21)
	{
		Points -= 10; // ACE의 값을 11에서 1로 변경
		AceCount--;
	}
	if (Points > 21)
	{
		Points = 0;
	}
	if (Points == 21 && Player.Hand.Size == 2)
	{
		Points = 100; // 블랙잭
	}

	Player.Points = Points;
	return Points;
}

// 히트/스탠드
GameStatus HitOrStand(Participant& Player, CardPiles& Deck, bool IsPlayer = false)
{
	GameStatus Result = DEFAULT;
	if (Player.Points == 0)
	{
		cout << (IsPlayer ? "플레이어가 버스트되었습니다.\n"
			: "딜러가 버스트되었습니다.\n")
			<< endl;
		return Result = BUSTED;
	}
	else
	{
		if (IsPlayer)
		{
			cout << "히트하시겠습니까? (y/n): ";

			char Choice;
			cin >> Choice;

			if (Choice == 'y' || Choice == 'Y')
			{
				Draw(Player, Deck);
				Player.Points = CalculatePoints(Player);
			}
			else
			{

				cout << "플레이어가 스탠드했습니다.\n" << endl;
				Result = STANDED;

			}
		}
		else
		{
			if (Player.Points < 17)
			{
				cout << "딜러가 히트합니다.\n" << endl;
				Draw(Player, Deck);
				Player.Points = CalculatePoints(Player);
			}
			else
			{
				cout << "딜러가 스탠드했습니다.\n" << endl;
				Result = STANDED;

			}
		}
	}
	return Result;
}
// UI
void ShowUI(Participant& Dealer, Participant& Player, bool hide = true)
{
	cout << "--딜러의 패--" << endl;
	ShowCards(Dealer.Hand, hide);
	CalculatePoints(Dealer);
	cout << "--플레이어의 패--" << endl;
	ShowCards(Player.Hand);
	CalculatePoints(Player);
	int Points = Player.Points;
	cout << "----------------" << endl;
	printf("현재 점수: %s\n", (Points == 100 ? "BLACK JACK!" : (to_string(Points)).c_str()));
}

void Homework02_Run()
{
	//플레이어, 딜러 인스턴스 생성
	srand((unsigned int)time(0));
	bool ContinueGame = true;
	while (ContinueGame)
	{
		Participant Dealer;
		Participant Player;
		CardPiles PlayingDeck = CreateDeck();

		ShuffleDeck(PlayingDeck);


		// 참가자에게 각각 카드를 덱에서 2장씩 나눠줌
		Draw(Dealer, PlayingDeck, 2);
		Draw(Player, PlayingDeck, 2);

		//ShowCards(PlayingDeck);
		GameStatus Game = DEFAULT;
		while (Game == DEFAULT)
		{
			ShowUI(Dealer, Player);
			Game = HitOrStand(Player, PlayingDeck, true);

		}
		GameStatus Game2 = DEFAULT;
		while (Game2 == DEFAULT)
		{
			ShowUI(Dealer, Player, false);
			Game2 = HitOrStand(Dealer, PlayingDeck);
		}
		printf("딜러 점수: %s\t", (Dealer.Points == 100 ? "BLACK JACK!" : (to_string(Dealer.Points)).c_str()));
		printf("플레이어 점수: %s\n", (Player.Points == 100 ? "BLACK JACK!" : (to_string(Player.Points)).c_str()));
		if (Player.Points == Dealer.Points)
		{
			cout << "무승부입니다." << endl;
		}
		else if (Player.Points > Dealer.Points)
		{
			cout << "플레이어가 승리했습니다!" << endl;
		}
		else
		{
			cout << "딜러가 승리했습니다!" << endl;
		}
		delete[] Dealer.Hand.Cards;
		delete[] Player.Hand.Cards;
		delete[] PlayingDeck.Cards;
		char Choice;
		cout << "게임을 계속하시겠습니까? (y/n): ";
		cin >> Choice;
		if (Choice == 'n' || Choice == 'N')
		{
			ContinueGame = false;
			cout << "게임을 종료합니다." << endl;
		}
	}
}