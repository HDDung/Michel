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
	void Input(double P, double D, Grap graph);

	/*
	Attacking process
	*/
	void Attack();

	/*
	Return graph has been attacked
	*/
	Grap Output();

	// Return number of Byzantines nodes
	int Number_BNodes();
	
	
	~Attacker();

private:
	Grap A_graph;
	double Prob;
	double Delta; 
	int N1;
};

