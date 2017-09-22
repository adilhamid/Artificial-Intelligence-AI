/*
 * Node.h
 *
 *  Created on: Sep 20, 2017
 *      Author: adilhamidmalla
 */

#ifndef NODE_H_
#define NODE_H_

#include<vector>

class Node {

public:
	State currentState;
	Node* Parent;
	Node *child;
	Action act;   // Actions taken on the state
	float totalCost; // g(n) + h(n)
	float gCost; // g(n) --> Actual Path Cost
	float hCost; // h(n) --> Heuristics Functional Cost


	Node();
	virtual ~Node();
};

#endif /* NODE_H_ */
