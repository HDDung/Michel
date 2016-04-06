#pragma once
#include "Grap.h"
#include "GrapNode.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <time.h>

class Consensus
{
public:
	
	
	// Input Grap need to consensus
	void Input(Grap);
	// (NOT YET)Calculate Best-constant edge weight 
	void Cal_W_BConst();
	// Calculate Local-degree weight 
	void Cal_W_LDegree();
	// Calculate Max-degree weight 
	void Cal_W_Max();
	// Calculate Metropilis-Hasting matrix
	void Cal_W_MetroHast();
	// Calculate Equal Weight
	void Cal_W_EWeight(double e);
	// Consensus Algorithm 
	void Cal_A();
	// Consensus Algorithm with random choosing neighbor
	void Cal_A_RandNegi();

	//Defense solution 
	void Def_5();
	
private:
	unsigned long long maxLOOP = 1.0e+18;
	double comVAL = 0;
	Grap grap;
	std::vector<std::vector<double>> W;
	//double W[100][100];
	int Ave;
	double Speed;


	
};

