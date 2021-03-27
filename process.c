#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"assn5.h"

int betting(int firstmoney, int *currentmoney, int *betmoney)
{
	while (1)
	{
		if (*currentmoney >= (firstmoney * 100))	//소지금이 초기 금액의 100배 이상의 경우 프로그램 종료
		{
			printf("당신은 돈을 너무 많이 벌어 카지노 업체가 당신을 쫓아냈습니다.");
			printf("카지노에서 $%d으로 무려 $%d를 벌었습니다!!!\n", firstmoney, *currentmoney);
			return 0;
		}
		if (*currentmoney == 0)		//소지금이 0원이 되면 프로그램 종료
		{
			printf("재산이 없어서 카지노에서 쫓겨났습니다...\n");
			printf("역시 올인은 하면 안돼요...\n");
			return 0;
		}

		printf("[현재 소지금 : $%d] 배팅 금액을 설정하세요! <0 for Exit> ", *currentmoney);
		fflush(stdin);
		scanf("%d", betmoney);		//배팅할 금액 입력
		system("cls");
		if (*betmoney == 0)		//0을 입력하면 프로그램 종료
		{
			printf("당신은 $%d을 들고가서 $%d를 남겨왔습니다.\n", firstmoney, *currentmoney);
			return 0;
		}
		printf("\n");
		if (*betmoney < 0 || *betmoney>*currentmoney)
		{
			printf("유효한 배팅 금액을 설정해주세요!\n");
			continue;
		}

		*currentmoney -= *betmoney;
		break;
	}
}

int shuffle(DECK *deck)
{
	CARD *temp;

	if (deck->count >= 26)	//26장 이상이면 shuffle을 생략한다.
		return 0;

	printf("카드를 새롭게 섞습니다...\n");
	while (deck->count != 52)		//deck의 개수가 52개가 되기 전까지 반복한다.
	{
		temp = (CARD*)malloc(sizeof(CARD));
		temp->shape = rand() % 4;			//shape에 0~3의 숫자를 랜덤 배정
		temp->number = rand() % 13 + 1;		//number에 1~13의 숫자를 랜덤 배정

		if (deck->head == NULL)		//NULL일 경우 head에 temp값 저장
			deck->head = temp;		//deck의 head에 현재 temp를 입력
		else
		{
			if (check(deck, temp) == 0)	//현재의 temp와 deck을 check해서 이미 deck에 있는 카드면 다시 temp의 정보를 만든다.
				continue;
			deck->tail->next = temp;	//tail의 next 자리에 temp의 정보를 넣는다.
		}
		deck->tail = temp;		//tail을 temp의 자리로 옮긴다.
		deck->tail->next = NULL;
		
		deck->count++;		//정상적인 처리가 되면 deck의 카드 개수가 한장 증가한다.
	}
}

void divide(DECK *deck, DECK *player, DECK *dealer)
{
	int i = 0;
	player->count = 0;
	player->head = NULL;
	player->tail = NULL;
	dealer->count = 0;
	dealer->head = NULL;
	dealer->tail = NULL;

	while (i < 4)
	{
		if (i % 2 == 0)
		{
			if (player->head == NULL)
				player->head = deck->head;			//NULL일 경우 player카드에 deck의 가장 위에 카드 저장
			else
				player->tail->next = deck->head;	//tail의 next 자리에 deck->head의 정보를 넣는다.
			player->tail = deck->head;
			deck->head = deck->head->next;		//deck의 head를 다음으로 바꿔준다.
			player->tail->next = NULL;
			player->count++;
		}
		else
		{
			if (dealer->head == NULL)		//NULL일 경우 head에 temp값 저장
				dealer->head = deck->head;		//deck의 head에 현재 temp를 입력
			else
				dealer->tail->next = deck->head;	//tail의 next 자리에 deck->head의 정보를 넣는다.
			dealer->tail = deck->head;
			deck->head = deck->head->next;		//deck의 head를 다음으로 바꿔준다.
			dealer->tail->next = NULL;
			dealer->count++;
		}
		deck->count--;	//deck의 개수가 한장씩 감소한다.
		i++;
	}
}

int playerturn(int *currentmoney, int *betmoney, DECK *deck, DECK *player, DECK *dealer, int *playersum, int *dealersum)
{
	char input[20];

	do {
		if (*playersum == 21)	//blackjack 나오면 더이상 안한다.
			return 0;
		if (*playersum > 21)	//21보다 크면 자동으로 딜러 단계로 넘어간다.
		{
			system("cls");
			return 0;
		}

		printf("Hit or Stay? ");
		gets(input);	//명령어를 문자열로 받는다.
		fflush(stdin);	//buffer 제거

		if (strlen(input) != 3 && strlen(input) != 4)	//문자열이 3개도 아니고 4개도 아닐 경우 
			printf("유효한 명령어를 입력해주세요.\n");
		else
		{
			strupr(input);	//input의 문자열을 모두 대문자로 바꿔준다.
			if (input[0] == 'S' && input[1] == 'T' && input[2] == 'A' && input[3] == 'Y')	//stay일 경우
			{
				system("cls");
				return 0;
			}
			else if (input[0] == 'H' && input[1] == 'I' && input[2] == 'T')	//hit일 경우
			{
				system("cls");
				player->tail->next = deck->head;	//다음칸에 현재 카드를 넣는다.
				player->tail = deck->head;			//tail의 위치 이동
				deck->head = deck->head->next;		//deck의 head를 다음으로 바꿔준다.
				player->tail->next = NULL;
				player->count++;	//player의 카드 개수 1증가
				deck->count--;		//deck의 카드 개수 1감소

				playerturnprint(currentmoney, betmoney, player, dealer, playersum, dealersum);	//현재 상화 출력
			}
			else
				printf("유효한 명령어를 입력해주세요.\n");	//다른 입력에 대해 다시 입력을 받는다.
		}
	} while (1);
}

int dealerturn(int *currentmoney, int *betmoney, DECK *deck, DECK *player, DECK *dealer, int *playersum, int *dealersum)	//dealer단계에서 현재 상황을 출력하는 함수
{
	if (*playersum == 21)	//blackjack이면 dealer단계 생략
		return 0;
	dealerturnprint(currentmoney, betmoney, player, dealer, playersum, dealersum);	//현재 상황 출력
	while (*dealersum <= 16)	//*dealersum이 17이상이면 자동 stay
	{
		printf("딜러가 Hit합니다...");
		getchar();		//Enter입력
		system("cls");

		dealer->tail->next = deck->head;	//다음칸에 현재 카드를 넣는다.
		dealer->tail = deck->head;			//tail의 위치 이동
		deck->head = deck->head->next;		//deck의 head를 다음으로 바꿔준다.
		dealer->tail->next = NULL;
		dealer->count++;		//dealer의 카드 개수 1증가
		deck->count--;			//deck의 카드 개수 1감소

		dealerturnprint(currentmoney, betmoney, player, dealer, playersum, dealersum);	//현재 상황 출력
	}
	printf("딜러가 Stay합니다.\n");
	printf("------------------------------------\n");
	return 0;
}

int winner(int *currentmoney, int *betmoney, int *playersum, int *dealersum)
{
	if (*playersum == 21)	//blackjack이면 3배의 금액과 베팅한 금액을 받는다.
	{
		printf("★B★L★A★C★K★J★A★C★K★\n");
		printf("배팅한 금액의 3배에 해당하는 $%d를 획득했습니다!\n", ((*betmoney) * 3));
		*currentmoney += ((*betmoney) * 4);
	}
	else if (*playersum > 21)	//금액의 변화가 없다
		printf("버스트! 플레이어가 졌습니다. 배팅한 돈을 잃었습니다.\n");
	else if (*dealersum == 21)	//금액의 변화가 없다
	{
		printf("딜러가 ★B★L★A★C★K★J★A★C★K★\n");
		printf("배팅한 돈을 잃었습니다.\n");
	}
	else if (*dealersum > 21)	//베팅한 금액을 추가로 받는다
	{
		printf("플레이어가 이겼습니다! $%d를 획득했습니다.\n", *betmoney);
		*currentmoney += ((*betmoney) * 2);
	}
	else if (*dealersum <= *playersum)	//배팅한 금액의 2배를 추가로 받는다
	{
		printf("플레이어가 이겼습니다! $%d를 획득했습니다.\n", ((*betmoney) * 2));
		*currentmoney += ((*betmoney) * 3);
	}
	else if (*dealersum > *playersum)	//금액의 변화가 없다
		printf("플레이어가 졌습니다. 배팅한 돈을 잃었습니다.\n");
	
	*betmoney = 0;
	return 0;
}