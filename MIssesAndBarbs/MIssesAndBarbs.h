#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define MISSIONARIES_MAX 3
#define BARBARIAN_MAX 3
#define SAILWAY_MAX 5
#define LEFT_BANK 1
#define RIGHT_BANK 0
#define STEP_MAX 100

extern int step[STEP_MAX];
extern int g_step_number;
extern int g_sail_way_max;
extern int g_crossing_history[3][STEP_MAX];

struct MyLeftBank
{
	int missionaries;	//传教士
	int barbarians;		//野蛮人
	int boat_state;	//1 means boat on left bank,0 boat on right bank;
};
/**
* Name		:InitSailWay
* Function	:According to the input boat number,the function generates all the sailing ways,
*			 stores in the two-dimensional array and return the number of sailing way.  
* Parameter	:int sailWay[2][STEP_MAX]	--Storing all the sailing ways.
*			 int& sailWayMax			--Storing the number of sailing way.
*			 const int boatNumber		--Inputing boat number
* Return	:The result of generation 
**/
int InitSailWay(int sailWay[2][STEP_MAX], int& sailWayMax, const int boatNumber);
/**
* Name		:BoatGoOppositeBank
* Function	:According to the sailing way and boat state,altering the missionaries,barbarians and boat state.
*			 After altering miss,barb and boat states,
*			 if their numbers are illegal(greater than input miss and barb),sailing failure return 0.sail way add one.
*			 else sailing rightful,return 1.
* Parameter	:MyLeftBank& this_			--now left bank missionaries,barbarians and boat state.
*			 int& sail_way				--sailing way,taking from global value(g_sail_way[2][STEP_MAX])
*			 const int input_miss		--input missionaries.
*			 const int input_barb		--input barbarians.
* Return	:The result of sailing. 1 means:success,0 means:fail
**/
int BoatGoOppositeBank(MyLeftBank& this_, int& sail_way, const int input_miss, const int input_barb);

/**
* Name		:JudgeBothBankState
* Function	:According to the parameter const MyLeftBank this_,judge two bank states of missionaries,barbrians.
*			 if missionaries Greater than or equal to barbrian on both banks,the sailing is successful.
*			 Updating sail way to zero.Return 1.
*			 else failing sail.Return 0.
* Parameter	:const MyLeftBank this_		 -- Judging the state of left bank and right bank.
*			 int& sail_way				 -- Sailing success,altering sail way = 0.
*			 const int input_miss,		 -- Input missionaries.	
*			 const int input_barb		 -- Input barbrians.
* Return	:The result of judging. 1 means:success,0 means:fail
**/
int JudgeBothBankState(const MyLeftBank this_, int& sail_way, const int input_miss, const int input_barb);

/**
* Name		:ReturnAvailableState
* Function	:If the the result of judging is fail.Return to last available state.
* Parameter	:const MyLeftBank this_		 -- Judging the state of left bank and right bank.
*			 int& sail_way				 -- Sailing success,altering sail way = 0.
*			 const int sail_way_max		 -- The number of total sailing way.
* Return	:1 means :success,0 means :the search is end.
**/
int ReturnAvailableState(MyLeftBank& this_, int& sail_way,const int sail_way_max);

/**
* Name		:PrintingSailWay
* Function	:Printing the way from start state to destination state.
* Parameter	:const int successWay  --the times of printing way.
* Return	:void
**/
void PrintingSailWay(const int successWay);

/**
* Name		:CrossRiver
* Function	:The total function.
* Parameter	:MyLeftBank & leftbank			--Input missionaries,barbrians and boat carrying number.
			 const int inputMissionaries	--Input missionaries
			 const int inputBarbarians		--Input barbrians
			 const int inputBoatnumber		--Input boat carrying number
* Return	:void
**/
void CrossRiver(MyLeftBank & leftbank, const int inputMissionaries, const int inputBarbarians,const int inputBoatnumber);
