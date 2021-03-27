#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"assn5.h"

int main(int argc, char *argv[])
{
	DECK deck;		//전체 카드 덱
	DECK player;	//player 덱
	DECK dealer;	//dealer 덱
	int inputmoney;
	int firstmoney;
	int *posessmoney;
	int *betmoney;
	int *playersum;
	int *dealersum;
	int pmoney = 0;
	int bmoney = 0;
	int psum = 0;
	int dsum = 0;

	posessmoney = &pmoney;	//포인터 0으로 초기화
	betmoney = &bmoney;		//포인터 0으로 초기화
	playersum = &psum;		//초기화
	dealersum = &dsum;		//초기화

	srand(time(NULL));

	if (argv[1] == NULL)	//입력받은 값이 없으면 자동으로 5000원 처리한다.
		inputmoney = 5000;
	else
	{
		if (strlen(argv[1]) == 1)		//문자를 숫자로 변화한다.
			inputmoney = (argv[1][0] - '0');
		if (strlen(argv[1]) == 2)
			inputmoney = (argv[1][0] - '0') * 10 + (argv[1][1] - '0');
		if (strlen(argv[1]) == 3)
			inputmoney = (argv[1][0] - '0') * 100 + (argv[1][1] - '0') * 10 + (argv[1][2] - '0');
		if (strlen(argv[1]) == 4)
			inputmoney = (argv[1][0] - '0') * 1000 + (argv[1][1] - '0') * 100 + (argv[1][2] - '0') * 10 + (argv[1][3] - '0');
		if (strlen(argv[1]) == 5)
			inputmoney = (argv[1][0] - '0') * 10000 + (argv[1][1] - '0') * 1000 + (argv[1][2] - '0') * 100 + (argv[1][3] - '0') * 10 + (argv[1][4] - '0');
		if (strlen(argv[1]) == 6)
			inputmoney = (argv[1][0] - '0') * 100000 + (argv[1][1] - '0') * 10000 + (argv[1][2] - '0') * 1000 + (argv[1][3] - '0') * 100 + (argv[1][4] - '0') * 10 + (argv[1][5] - '0');
		if (strlen(argv[1]) == 7)
			inputmoney = 1000000;
	}
	
	firstmoney = inputmoney;		//처음 보유하고 있던 금액 기억
	*posessmoney = inputmoney;		//소유하고 있는 금액에 처음 보유하고 있는 금액을 넣어준다.

	while (1)
	{
		deck.count = 0;		//deck 초기화
		deck.head = NULL;	//deck 초기화
		deck.tail = NULL;	//deck 초기화

		*dealersum = 0;	//금액 초기화
		*playersum = 0;	//금액 초기화

		if (betting(firstmoney, posessmoney, betmoney) == 0)		//betting 함수 호출
			break;

		shuffle(&deck);		//성공적으로 betting이 되면 deck을 섞는다.
		divide(&deck, &player, &dealer);		//덱을 섞을 후 player 과 dealer한테 카드를 2장씩 배분한다.
		playerturnprint(posessmoney, betmoney, &player, &dealer, playersum, dealersum);		//현재 상황을 출력한다.
		
		getchar();		//buffer제거
		playerturn(posessmoney, betmoney, &deck, &player, &dealer, playersum, dealersum);	//player 차례
		dealerturn(posessmoney, betmoney, &deck, &player, &dealer, playersum, dealersum);	//dealer 차례
		winner(posessmoney, betmoney, playersum, dealersum);		//승자 판별
		initialize(&player);	//player deck을 초기화한다.
		initialize(&dealer);	//dealer deck을 초기화한다.
		if (deck.count <= 26)	//카드의 개수가 26개면 deck도 초기화한다.
			initialize(&deck);
	}
	return 0;
}