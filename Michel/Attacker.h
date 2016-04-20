#pragma once
#include "Grap.h"
#include <iostream>
#include <stdlib.h>


class Attacker
{
public:
	Attacker();
	/*
	Input the parameter P and D and the graph
	
	*/
	void Input(long double P, long double D, Graph graph);

	/*
	Attacking process
	*/
	void Attack();

	/*
	Return graph has been attacked
	*/
	Graph Output();

	// Return number of Byzantines nodes
	int Number_BNodes();
	
	
	~Attacker();

private:
	Graph A_graph;
	long double Prob;
	long double Delta; 
	int N1;
};

