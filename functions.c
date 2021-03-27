#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"assn5.h"

int check(DECK *deck, CARD *card)		//현재의 card에 대해 deck에 일치하는 게 있는지 학인
{
	CARD *temp;
	temp = deck->head;	//temp를 deck->head로 맞춰줬다.

	while (temp != NULL)	//NULL일 때까지
	{
		if (temp->shape == card->shape&&temp->number == card->number)	//비교해서 같으면 0리턴
			return 0;
		if (temp->next == NULL)	//temp의 다음값이 NULL이면 멈춘다.
			break;
		temp = temp->next;	//temp이동
	}
	return 1;		//없으면 1리턴
}

void cardshape(int random, char *shape)		//0~3의 숫자를 해당하는 카드 문양으로 바꿔주는 함수
{
	if (random == 0)
		strcpy(shape, "♠");	//문양이 2byte이기 때문에 문자 한개로 받지 못하여 문자열에 복사하는 방식을 사용한다.
	if (random == 1)
		strcpy(shape, "♥");
	if (random == 2)
		strcpy(shape, "◆");
	if (random == 3)
		strcpy(shape, "♣");
}

void cardnumber(int random, char *number)	//1~13의 숫자를 해당하는 카드 숫자로 바꿔주는 함수
{
	if (random == 1)
		strcpy(number, "A");	//해당하는 번호를 문자열을 복사한다.
	if (random == 2)
		strcpy(number, "2");
	if (random == 3)
		strcpy(number, "3");
	if (random == 4)
		strcpy(number, "4");
	if (random == 5)
		strcpy(number, "5");
	if (random == 6)
		strcpy(number, "6");
	if (random == 7)
		strcpy(number, "7");
	if (random == 8)
		strcpy(number, "8");
	if (random == 9)
		strcpy(number, "9");
	if (random == 10)
		strcpy(number, "10");
	if (random == 11)
		strcpy(number, "J");
	if (random == 12)
		strcpy(number, "Q");
	if (random == 13)
		strcpy(number, "K");
}

void sumcard(CARD *card, int *sum, int *countA)		//입력받은 card에 대해 정보를 sum에 더해준다.
{
	int i;
	if (card->number == 1)	
	{
		*sum += 11;		//일단 11을 더하고 상황에 따라 10을 빼준다.
		*countA += 1;		//A의 개수를 하나 늘린다.
	}
	else if (card->number == 11)	//J, Q, K는 10으로 처리한다.
		*sum += 10;
	else if (card->number == 12)
		*sum += 10;
	else if (card->number == 13)
		*sum += 10;
	else
		*sum += card->number;
	for (i = *countA; i > 0; i--)
	{
		if (*sum > 21)	//sum값이 21보다 크면 21보다 작아질 때까지만 A의 개수만큼 10을 빼준다.
		{
			*sum -= 10;
			*countA -= 1;
		}
	}
}

int playerturnprint(int *currentmoney, int *betmoney, DECK *player, DECK *dealer, int *playersum, int *dealersum)
{
	CARD *temp;
	char tempshape[3], tempnumber[3];
	int i = dealer->count;
	int cA = 0;
	int *countA;	//A의 개수만 따로 센다
	countA = &cA;	//*countA 초기화

	*playersum = 0;		//playersum, dealersum 초기화
	*dealersum = 0;

	printf("[소지금 : %d] [배팅금액 : %d]\n", *currentmoney, *betmoney);	//소지금 배팅금앱 출력
	printf("------------------------------------\n");

	//Dealer 부분 출력
	printf("<Dealer> ");
	for (temp = dealer->head; temp != NULL; temp = temp->next)
	{
		if (i == dealer->count)		//첫 번째 카드에 대해서만 ????로 출력한다.
			printf("[????] ");
		else
		{
			sumcard(temp, dealersum, countA);		//dealersum에 합이 더해지진다.
			cardshape(temp->shape, tempshape);		//tempshape에 문자열로 문양을 넣는다.
			cardnumber(temp->number, tempnumber);	//tempnumber에 문자열로 숫자를 넣는다.
			printf("[%s%s] ", tempshape, tempnumber);	//문자열 출력
		}	
		i--;
	}
	printf(", Sum = %d\n", *dealersum);

	//Player 부분 출력
	*countA = 0;	//*countA를 0으로 초기화
	printf("<Player> ");
	for (temp = player->head; temp != NULL; temp = temp->next)
	{
		sumcard(temp, playersum, countA);			//platersum에 합이 더해진다.
		cardshape(temp->shape, tempshape);			//tempshape에 문자열로 문양을 넣는다.
		cardnumber(temp->number, tempnumber);		//tempnumber에 문자열로 숫자를 넣는다.
		printf("[%s%s] ", tempshape, tempnumber);	//문자열 출력
	}
	printf(", Sum = %d\n", *playersum);
	printf("\n");
}

int dealerturnprint(int *currentmoney, int *betmoney, DECK *player, DECK *dealer, int *playersum, int *dealersum)
{
	CARD *temp;
	char tempshape[3], tempnumber[3];
	int cA = 0;
	int *countA;	//A의 개수만 따로 센다
	countA = &cA;	//*countA 초기화
	*playersum = 0;
	*dealersum = 0;

	printf("[소지금 : %d] [배팅금액 : %d]\n", *currentmoney, *betmoney);
	printf("------------------------------------\n");

	printf("<Dealer> ");
	for (temp = dealer->head; temp != NULL; temp = temp->next)
	{
		sumcard(temp, dealersum, countA);			//dealersum에 합이 더해진다.
		cardshape(temp->shape, tempshape);			//tempshape에 문자열로 문양을 넣는다.
		cardnumber(temp->number, tempnumber);		//tempnumber에 문자열로 숫자를 넣는다.
		printf("[%s%s] ", tempshape, tempnumber);	//문자열 출력
	}
	printf(", Sum = %d\n", *dealersum);

	*countA = 0;	//dealer의 countA를 초기화
	printf("<Player> ");
	for (temp = player->head; temp != NULL; temp = temp->next)
	{
		sumcard(temp, playersum, countA);			//playersum에 합이 더해진다.
		cardshape(temp->shape, tempshape);			//tempshape에 문자열로 문양을 넣는다.
		cardnumber(temp->number, tempnumber);		//tempnumber에 문자열로 숫자를 넣는다.
		printf("[%s%s] ", tempshape, tempnumber);	//문자열 출력
	}
	printf(", Sum = %d\n", *playersum);
	printf("\n");
}

int initialize(DECK *deck)
{
	CARD *temp1;
	temp1 = deck->head;		//temp1을 deck의 head로 고정한다

	while (temp1 != NULL)
	{
		temp1 = temp1->next;	//temp1을 다음으로 바꿔준다.
		free(deck->head);		//deck의 head를 free한다
		deck->head = temp1;		//deck의 head를 temp1위치로 옮긴다.
		if (temp1->next == NULL)	//다음이 NULL이면 그 위치에서 free하고 break해서 벗어난다.
		{
			free(deck->head);
			break;
		}
	}
	deck->count = 0;
}