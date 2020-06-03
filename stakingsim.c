#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
//make the randomness RANDOM make pid, make poison,maybe tax?
typedef struct player{
	char name[25];
	int gp;
	int hp;
}player;

struct player* createPlayer(char* name);
void printOut(player* staker);
void startStake(player* p1,player* p2);
int stakeAmount();
int fight(player* p1,player* p2);
int hitRoll();
void deductHP(player* gotHit,int hit);
void spoils(int amount,player* winner);
void resetHP(player* p1,player* p2);

int main(void){
	int i,n;
	player* player1;
	player* player2;
	char Staker1[]="Staker 1";
	char Staker2[]="Staker 2";
	player1=createPlayer(Staker1);
	player2=createPlayer(Staker2);
	printf("How many stakes are we going for? \n");
	scanf("%d",&n);
	while(n>0){
	srand(time(0));
	startStake(player1,player2);
	wasteTime();
	n--;
	}
	printf("It is over. Here are the results.\n");
	printOut(player1);
	printOut(player2);
	return 0;
	
}

struct player* createPlayer(char* name){
	struct player* temp;
	temp = (struct player*)malloc(sizeof(struct player));
	temp->hp=99;
	strcpy(temp->name,name);
	temp->gp=1000000;
	return temp;
}

void printOut(player* staker){
	printf("%s has %d hp and %d gp\n",staker->name,staker->hp,staker->gp);
}

void startStake(player* p1,player* p2){
	int amount = stakeAmount();
	printf("This stake will be for %d making it a total of %d!\n",amount,amount*2);
	p1->gp=p1->gp-(amount);
	p2->gp=p2->gp-(amount);
	printf("%d has been deducted from %s: %d and %s: %d\nWe are now starting the stake!\n",amount,p1->name,p1->gp,p2->name,p2->gp);
	int victor=fight(p1,p2);
	if (victor==0){
		spoils(amount*2,p1);
		printf("%s has been awarded the %d gp. They now have %d gp.\n",p1->name,amount*2,p1->gp);
	}
	else{
		spoils(amount*2,p2);
		printf("%s has been awarded the %d gp. They now have %d gp.\n",p2->name,amount*2,p2->gp);
	}
	resetHP(p1,p2);
}

int stakeAmount(){
	int n=(rand()%100+1) *1000;
	return n;
}

int fight(player* p1,player* p2){
	int hit;
	while (p1->hp>0 && p2->hp>0){
	hit=hitRoll();
	deductHP(p2,hit);
	printf("%s hit a %d on player 2. Player 2 has %d hp left.\n",p1->name,hit,p2->hp);
	if (p2->hp == 0){
		break;
	}
	hit=hitRoll();
	deductHP(p1,hit);
	printf("%s hit a %d on player 1. Player 1 has %d hp left.\n",p2->name,hit,p1->hp);
	}
	if (p2->hp == 0){
		printf("%s is the winner!\n",p1->name);
		return 0;
	}
	else {
		printf("%s is the winner!\n",p2->name);
		return 1;
	}
}

int hitRoll(){
	int n=rand()%100+1;
	if (n<=10){
		return 0;
	}
	else return rand()%26;
}

void deductHP(player* gotHit,int hit){
	if (gotHit->hp-hit<=0){
		gotHit->hp=0;
	}
	else gotHit->hp=gotHit->hp-hit;
}

void spoils(int amount,player* winner){
	winner->gp=winner->gp+amount;
}

void resetHP(player* p1,player* p2){
	p1->hp=99;
	p2->hp=99;
}

