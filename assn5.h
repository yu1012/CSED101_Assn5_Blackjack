#ifndef ASSN5_H
#define ASSN5_H

typedef struct card
{
	int shape;		//카드의 문양
	int number;		//카드의 숫자
	struct card *next;
}CARD;

typedef struct deck
{
	int count;		//deck카드의 개수
	CARD *head;
	CARD *tail;
}DECK;

int betting(int firstmoney, int *currentmoney, int *betmoney);
int shuffle(DECK *deck);
void divide(DECK *deck, DECK *player, DECK *dealer);
int playerturn(int *currentmoney, int *betmoney, DECK *deck, DECK *player, DECK *dealer, int *playersum, int *dealersum);
int dealerturn(int *currentmoney, int *betmoney, DECK *deck, DECK *player, DECK *dealer, int *playersum, int *dealersum);
int winner(int *currentmoney, int *betmoney, int *playersum, int *dealersum);

int check(DECK *deck, CARD *card);
void cardshape(int random, char *shape);
void cardnumber(int random, char *number);
int playerturnprint(int *currentmoney, int *betmoney, DECK *player, DECK *dealer, int *playersum, int *dealersum);
int dealerturnprint(int *currentmoney, int *betmoney, DECK *player, DECK *dealer, int *playersum, int *dealersum);
void sumcard(CARD *card, int *sum, int *countA);
int initialize(DECK *deck);

#endif