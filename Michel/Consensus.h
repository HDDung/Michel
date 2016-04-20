#pragma once
#include "Grap.h"
#include "GrapNode.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <iomanip>

class Consensus
{
public:
	
	
	// Input Grap need to consensus
	void Input(Graph);
	// (NOT YET)Calculate Best-constant edge weight 
	void Cal_W_BConst();
	// Calculate Local-degree weight 
	void Cal_W_LDegree();
	// Calculate Max-degree weight 
	void Cal_W_Max();
	// Calculate Metropilis-Hasting matrix
	void Cal_W_MetroHast();
	// Calculate Equal Weight
	void Cal_W_EWeight(long double e);
	// Consensus Algorithm 
	void Cal_A(std::ostream& stream);
	// Consensus Algorithm with random choosing neighbor
	void Cal_A_RandNegi(std::ostream& stream);

	//Defense solution 
	void Def_5();
	
private:
	unsigned long long maxLOOP = 1.0e+18;
	long double comVAL = 0;
	Graph graph;
	std::vector<std::vector<long double>> W;
	//long double W[100][100];
	int Ave;
	long double Speed;


	
};

