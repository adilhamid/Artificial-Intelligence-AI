/*
 * State.cpp
 *
 *  Created on: Sep 20, 2017
 *      Author: adilhamidmalla
 */

#include "BlocksWorldProblem.h"

#include "ASearch.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <ctime>

using namespace std;

//Global Variables
int numStacks = 3;
int numBlocks = 5;
int maxSteps = 100;
int minSteps = 0;

BlocksWorldProblem SetGoalState() {
	BlocksWorldProblem goalState(numStacks, numBlocks);
	assert(numStacks >= 2 && numBlocks >= 1);
	// Putting the Goal State
	for (int counter = 0; counter < numBlocks; ++counter) {
		goalState.stackHolders[0].push_back('A' + counter);
	}
	return goalState;
}

void swap(char *a, char *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
// A function to generate a random permutation of arr[]
void randomize(vector<char> arr, int n) {
	srand(time(NULL));
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(arr[i], arr[j]);
	}
}

BlocksWorldProblem ProblemGenerator() {
	cout << "Initial State " << endl;
	BlocksWorldProblem initialState(numStacks, numBlocks);

//	initialState.stackHolders[0].push_back('B');
//	initialState.stackHolders[1].push_back('C');
//	initialState.stackHolders[1].push_back('E');
//	initialState.stackHolders[2].push_back('A');
//	initialState.stackHolders[2].push_back('D');
//	return initialState;

	int totalStacks = numStacks;
	vector<char> arrayList(numBlocks);
	for (int cnt = 0; cnt < numBlocks; ++cnt) {
		arrayList[cnt] = 'A' + cnt;
	}
	randomize(arrayList, numBlocks);
	totalStacks = numBlocks;
	// Multinomial Distribution of elements in
	for (int cntStack = 0; cntStack < numStacks; ++cntStack) {
		if (cntStack != numStacks - 1) {
			int randStack = rand() % (totalStacks + 1);
			for (int cntBlock = 0; cntBlock < randStack; ++cntBlock) {
				initialState.stackHolders[cntStack].push_back(arrayList.back());
				arrayList.pop_back();
			}
			totalStacks -= randStack;
		} else {
			for (int cntBlock = 0; cntBlock < totalStacks; ++cntBlock) {
				initialState.stackHolders[cntStack].push_back(arrayList.back());
				arrayList.pop_back();
			}

		}

	}
	initialState.PrintState();
	return initialState;
}

BlocksWorldProblem::BlocksWorldProblem() {
// TODO Auto-generated constructor stub
}

BlocksWorldProblem::BlocksWorldProblem(int pNumStacks, int pNumBlocks) {
	stackHolders = new std::vector<char>[pNumStacks];
	numBlocks = pNumBlocks;
	numStacks = pNumStacks;
}

bool BlocksWorldProblem::IsGoalNode(BlocksWorldProblem goalState) {

	for (int cntStack = 0; cntStack < this->numStacks; ++cntStack) {
		if (this->stackHolders[cntStack].size()
				!= goalState.stackHolders[cntStack].size()) {
			return false;
		}
		for (int cntBlocks = 0;
				cntBlocks < goalState.stackHolders[cntStack].size();
				++cntBlocks) {
			if (this->stackHolders[cntStack][cntBlocks]
					!= goalState.stackHolders[cntStack][cntBlocks]) {
				return false;
			}
		}
	}
	return true;
}
void DeepCopyState(BlocksWorldProblem sourceState,
		BlocksWorldProblem destState) {
	for (int cntStack = 0; cntStack < numStacks; ++cntStack) {
		for (int cntBlocks = 0;
				cntBlocks < sourceState.stackHolders[cntStack].size();
				++cntBlocks) {
			destState.stackHolders[cntStack].push_back(
					sourceState.stackHolders[cntStack][cntBlocks]);
		}
	}
	return;
}
std::vector<BlocksWorldProblem> BlocksWorldProblem::GenerateSuccessors(
		BlocksWorldProblem currentState) {

//	cout << "Generating the Successors" << endl;
	vector<BlocksWorldProblem> returnVal;
	for (int cntStack = 0; cntStack < numStacks; ++cntStack) {
		if (currentState.stackHolders[cntStack].size() > 0) {
			char topElement = currentState.stackHolders[cntStack].back();
			for (int innerCntStack = 0; innerCntStack < numStacks;
					++innerCntStack) {
				if (cntStack == innerCntStack)
					continue;

				// Add the State to the list of successors which is accessible from the current node.
				BlocksWorldProblem tempState(numStacks, numBlocks);
				//DeepCopy the State
				DeepCopyState(currentState, tempState);

				tempState.stackHolders[cntStack].pop_back();
				tempState.stackHolders[innerCntStack].push_back(topElement);

//				tempState.PrintState();
				returnVal.push_back(tempState);

			}
		}
	}
	return returnVal;
}

bool BlocksWorldProblem::IsIdenticalState(BlocksWorldProblem currentState) {

	for (int cntStack = 0; cntStack < this->numStacks; ++cntStack) {
		if (this->stackHolders[cntStack].size()
				!= currentState.stackHolders[cntStack].size()) {
			return false;
		}
		for (int cntBlocks = 0;
				cntBlocks < currentState.stackHolders[cntStack].size();
				++cntBlocks) {
			if (this->stackHolders[cntStack][cntBlocks]
					!= currentState.stackHolders[cntStack][cntBlocks]) {
				return false;
			}
		}
	}
	return true;
}

float BlocksWorldProblem::GetGCost(BlocksWorldProblem currentState) {
// Since the cost to each of the step is just one so the Cost is uniform for now
	return 1.0;
}

float BlocksWorldProblem::HeuristicsEstimateCost(BlocksWorldProblem goalState) {

// Use Different Heuristics for solving the problem
	//float h1 = HeuristicsOneCost(goalState);
	//float h2 = HeuristicsTwoCost(goalState);

	float h3 = HeuristicsThreeCost(goalState);
	return h3;
}

void BlocksWorldProblem::PrintState() {
	for (int stackCnt = 0; stackCnt < this->numStacks; stackCnt++) {
		cout << "Stack " << stackCnt << ": ";
		for (auto val : this->stackHolders[stackCnt]) {
			cout << val << " ";
		}
		cout << endl;
	}
	cout << endl;
}
// get the cost of misplaced blocks on the stacks
float BlocksWorldProblem::HeuristicsOneCost(BlocksWorldProblem goalState) {
	int h1Val = 0;
// Number of elements present in the First Stack + misplaced stacks
	h1Val += numBlocks - this->stackHolders[0].size();

	for (int cntBlocks = 0; cntBlocks < this->stackHolders[0].size();
			++cntBlocks) {
		if (this->stackHolders[0][cntBlocks] == 'A' + cntBlocks) {
			continue;
		} else {
			h1Val += this->stackHolders[0].size() - cntBlocks;
			return h1Val;
		}
	}
	return h1Val;
}

float BlocksWorldProblem::HeuristicsTwoCost(
		BlocksWorldProblem blocksWorldProblem) {
	int h2Cost = 0;
	// Check the goal stack value
	for (int i = 1; i < blocksWorldProblem.stackHolders[0].size(); i++) {
		if (blocksWorldProblem.stackHolders[0][i]
				!= blocksWorldProblem.stackHolders[0][i - 1] + 1) {
			h2Cost += 2;
		}
	}

	// For other stacks
	for (int cntStack = 1; cntStack < numStacks; cntStack++) {
		for (int cntBlock = 1;
				cntBlock < blocksWorldProblem.stackHolders[cntStack].size();
				cntBlock++) {
			if (blocksWorldProblem.stackHolders[cntStack][cntBlock]
					!= blocksWorldProblem.stackHolders[cntStack][cntBlock - 1]
							+ 1) {
				h2Cost += 2;
			}
		}
	}
	return h2Cost;
}

float BlocksWorldProblem::HeuristicsThreeCost(
		BlocksWorldProblem blocksWorldProblem) {
	int h3Cost = 0;

	int numBlocksOnce = 0;
	int numBlocksTwice = 0;

	for (int i = 1; i < blocksWorldProblem.stackHolders[0].size(); i++) {
		if (blocksWorldProblem.stackHolders[0][i]
				!= blocksWorldProblem.stackHolders[0][i - 1] -1) {
			numBlocksTwice += 1;
		}
	}
	// For other stacks
	for (int cntStack = 1; cntStack < numStacks; cntStack++) {
		for (int cntBlock = blocksWorldProblem.stackHolders[cntStack].size()
				- 1; cntBlock >= 1; cntBlock--) {

			char top = blocksWorldProblem.stackHolders[cntStack][cntBlock];
			char lower = blocksWorldProblem.stackHolders[cntStack][cntBlock-1];
			char checked = blocksWorldProblem.stackHolders[cntStack][cntBlock] - 1 ;

			cout << "Here " << top << " "<<  lower << " " << checked <<endl;

			if (blocksWorldProblem.stackHolders[cntStack][cntBlock]
					!= blocksWorldProblem.stackHolders[cntStack][cntBlock-1]
							+ 1) {
				numBlocksOnce += 1;
			} else if (blocksWorldProblem.stackHolders[cntStack][cntBlock]
					== blocksWorldProblem.stackHolders[cntStack][cntBlock-1]
							+ 1) {
				numBlocksTwice += 1;
			}
			else{
				numBlocksOnce ++;
			}

		}
	}
	cout <<numBlocksOnce << " " <<numBlocksTwice <<endl;
	h3Cost += (2*numBlocksOnce + 4*numBlocksTwice);
	return h3Cost ;
}

float BlocksWorldProblem::HeuristicsFourCost(
		BlocksWorldProblem blocksWorldProblem) {
	return 0.0;
}

float BlocksWorldProblem::HeuristicsFiveCost(
		BlocksWorldProblem blocksWorldProblem) {
	return 0.0;
}

BlocksWorldProblem::~BlocksWorldProblem() {
// TODO Auto-generated destructor stub
}

int main(int argc, char* argv[]) {

	cout << "Stacks and Blocks please" << endl;

	cin >> numStacks >> numBlocks;

	// Starting the initial state and goal state
	BlocksWorldProblem initialState = ProblemGenerator();
	BlocksWorldProblem goalState = SetGoalState();

	// Initialize the blocksworld A* Search
	ASearch<BlocksWorldProblem> blocksworld;

	blocksworld.InitProblemState(initialState, goalState);

	int totalGoalTests = 0;
	ASearcReturnVal resultVal;

	//Searching algorithm starts
	do {
		resultVal = blocksworld.ASearchExecute();
		totalGoalTests++;

	} while (resultVal.resultState
			== ASearch<BlocksWorldProblem>::STATE_SEARCHING);

	if (resultVal.resultState == ASearch<BlocksWorldProblem>::STATE_GOAL) {
		cout << "Goal State Found " << endl;
		cout << "Success!! depth = " << resultVal.depthOfGoalState
				<< ", Total Goal Tests = " << totalGoalTests
				<< ", Maximum Queue Size= " << resultVal.maxQueueSize
				<< ", Total Cost = " << blocksworld.GetTotalSolutionCost()
				<< endl;

		blocksworld.TracebackSolution();
	} else {
		cout << "Could not found the goal due to time out" << endl;
	}
	cout << "Done and dusted " << endl;
	return 0;

}