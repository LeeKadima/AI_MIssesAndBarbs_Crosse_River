#include "MissesAndBarbs.h"
int main()
{
	int input_missionaries;
	int input_barbarians;
	int intput_boat_number;
	cout << "Please enter the missionaries number:_\b";
	cin >> input_missionaries;
	
	cout << "Please enter the barbarians number:_\b";
	cin >> input_barbarians;

	cout << "Please enter the boat carrying number:_\b";
	cin >> intput_boat_number;

	MyLeftBank left_bank;
	left_bank.missionaries = input_missionaries;
	left_bank.barbarians = input_barbarians;
	left_bank.boat_state = LEFT_BANK;

	memset(step, -1, STEP_MAX * sizeof(int));	//Init step[STEP_MAX] to -1(unsail state)

	//Recording all bank state
	g_crossing_history[0][g_step_number] = input_missionaries;
	g_crossing_history[1][g_step_number] = input_barbarians;
	g_crossing_history[2][g_step_number] = LEFT_BANK;
	step[g_step_number] = 0;

	g_step_number++;	//Init sail.
	CrossRiver(left_bank, input_missionaries, input_barbarians, intput_boat_number);
}

