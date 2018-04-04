#include "MissesAndBarbs.h"

int step[STEP_MAX];		//Recording every sail way
int g_step_number = 0;
int g_sail_way_max = 0;
int g_crossing_history[3][STEP_MAX];
int g_sail_way[2][STEP_MAX];

int InitSailWay(int sailWay[2][100], int& sailWayMax, const int boatNumber)
{
	int miss_number = 0, barb_number = 0;			//Initializing missionary and barbarian number. 
	sailWayMax = 0;									//Initializing sailing way number.
	//Setting sailing way.
	while (miss_number != boatNumber+1 || barb_number != 0)
	{
		barb_number++;
		if (miss_number + barb_number <= boatNumber)
		{
			sailWay[0][sailWayMax] = miss_number;
			sailWay[1][sailWayMax] = barb_number;
			sailWayMax++;
		}
		else
		{
			miss_number++;
			barb_number = 0;
			sailWay[0][sailWayMax] = miss_number;
			sailWay[1][sailWayMax] = barb_number;
			sailWayMax++;
		}
	}
	sailWayMax--;									//Subtracting the excess state
	sailWay[0][sailWayMax] = 0;
	sailWay[1][sailWayMax] = 0;

	return 1;
}
//start g_step_number = 1;
int BoatGoOppositeBank(MyLeftBank& this_,int& sail_way,const int input_miss,const int input_barb)
{
	if (LEFT_BANK == this_.boat_state)			//If the boat is on the left bank.
	{
		//If the boat can sail on this sailing way.
		if (this_.missionaries >= g_sail_way[0][sail_way] && this_.barbarians >= g_sail_way[1][sail_way])
		{
			this_.missionaries -= g_sail_way[0][sail_way];	//Altering the misses ,barbs and boat state. 
			this_.barbarians -= g_sail_way[1][sail_way];
			this_.boat_state = (g_step_number + 1) % 2;
			step[g_step_number] = sail_way;
			return 1;
		}
		sail_way++;
		return 0;
	}
	else if (RIGHT_BANK == this_.boat_state)	//If the boat is on the right bank.
	{
		int left_miss = this_.missionaries + g_sail_way[0][sail_way];
		int left_barb = this_.barbarians + g_sail_way[1][sail_way];
		if (left_miss <= input_miss && left_barb <= input_barb)
		{
			this_.missionaries = left_miss;					//Altering the misses ,barbs and boat state. 
			this_.barbarians = left_barb;
			this_.boat_state = (g_step_number + 1) % 2;
			return 1;
		}
		sail_way++;
		return 0;
	}
	else  //Boat state goes wrong.
	{
		cout << "\nBoat state goes wrong.\n";
		system("pause");
		return -1;
	}
}
int JudgeBothBankState(const MyLeftBank this_,int& sail_way ,const int input_miss, const int input_barb)
{
	for (int i = 0; i < g_step_number; i++)			//if the boat state is the same as any previous state,go sailing with next sailing way.
	{
		if (g_crossing_history[0][i] == this_.missionaries &&
			g_crossing_history[1][i] == this_.barbarians &&
			g_crossing_history[2][i] == this_.boat_state
			)
		{ 
			return 0;
		}
	}
	//Excluding special cases:barbarian's number is over zero and missionary is zero.
	//barb_number>miss_number,but the state is rightful.
	if ((this_.missionaries == 0 && (this_.barbarians <= input_barb)) ||
		(this_.missionaries == input_miss && (this_.barbarians <= input_barb)) ||
		(this_.missionaries == 0 && this_.barbarians == 0))
	{
		g_crossing_history[0][g_step_number] = this_.missionaries;
		g_crossing_history[1][g_step_number] = this_.barbarians;
		g_crossing_history[2][g_step_number] = this_.boat_state;
		step[g_step_number] = sail_way;

		sail_way = 0;
		g_step_number++;

		return 1;
	}
	//Checking two bank's state.
	int right_miss = input_miss - this_.missionaries;
	int right_barb = input_barb - this_.barbarians;
	if ((this_.missionaries >= this_.barbarians) && (right_miss >= right_barb))
	{
		g_crossing_history[0][g_step_number] = this_.missionaries;
		g_crossing_history[1][g_step_number] = this_.barbarians;
		g_crossing_history[2][g_step_number] = this_.boat_state;
		step[g_step_number] = sail_way;

		sail_way = 0;
		g_step_number++;

		return 1;
	}
	else
	{
		return 0;
	}
}
int ReturnAvailableState(MyLeftBank& this_, int& sail_way,const int sail_way_max)
{
	if ((0 == this_.boat_state) && (0 == this_.missionaries) && (0 == this_.barbarians)) //When the state is getting the destination
	{																	                 //return to available sailing way.			
		g_step_number -= 2;
		this_.missionaries = g_crossing_history[0][g_step_number - 1];
		this_.barbarians = g_crossing_history[1][g_step_number - 1];
		this_.boat_state = (g_step_number) % 2;

		sail_way = step[g_step_number];
		sail_way++;
		return 1;
	}
	if (++sail_way<sail_way_max)	//Recoverying three states.
	{
		this_.missionaries = g_crossing_history[0][g_step_number-1];
		this_.barbarians = g_crossing_history[1][g_step_number-1];
		this_.boat_state = (g_step_number) % 2;
	}	
	while (sail_way>=sail_way_max)	//Returing to last available sailing state.																											
	{
		if (g_step_number-- > 1)
		{
		this_.missionaries = g_crossing_history[0][g_step_number-1];
		this_.barbarians = g_crossing_history[1][g_step_number - 1];
		this_.boat_state = (g_step_number) % 2;
		sail_way = step[g_step_number];
		sail_way++;
		}
		else return 0;
	}
	return 1;
}
void PrintingSailWay(const int successWay)
{
	cout << "\nEventually,we search the " << successWay << " ways" << endl;
	for (int i = 0; i < g_step_number; i++)
	{
		cout << '(' << g_crossing_history[0][i] << "," << g_crossing_history[1][i] << "," << g_crossing_history[2][i] << ')' << endl;
	}

}
void CrossRiver(MyLeftBank & leftbank, const int inputMissionaries, const int inputBarbarians, const int inputBoatnumber)
{
	int sailWay = 0;
	int success_way = 0;
	InitSailWay(g_sail_way, g_sail_way_max, inputBoatnumber);
	while (!(g_step_number == 0 && sailWay >= g_sail_way_max))
	{
		while (!((0 == leftbank.boat_state) && (0 == leftbank.missionaries) && (0 == leftbank.barbarians)))
		{
			if (1 == BoatGoOppositeBank(leftbank, sailWay, inputMissionaries, inputBarbarians))
			{
				if (0 == JudgeBothBankState(leftbank, sailWay, inputMissionaries, inputBarbarians))
				if (0 == ReturnAvailableState(leftbank, sailWay, g_sail_way_max))
					break;
			}
			if (sailWay >= g_sail_way_max)
			{
				ReturnAvailableState(leftbank, sailWay, g_sail_way_max);
			}
		}
		if ((0 == leftbank.boat_state) && (0 == leftbank.missionaries) && (0 == leftbank.barbarians))
		{
			success_way++;
			PrintingSailWay(success_way);
			ReturnAvailableState(leftbank, sailWay, g_sail_way_max);
		}
	}
	if (success_way == 0)
	{
		cout << "\nSorry,we cann't find a way.\n\n";
	}
	system("pause");
	//else cout << "\nEventually,find " << success_way << " ways" << endl;
}