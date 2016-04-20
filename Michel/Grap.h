#pragma once
#include "GrapNode.h"
#include <vector>
#include <time.h>

class Graph
{
public:
	
	//Input value of Graph 
	void Input(long double time_bandwidth_product, long double sensed_signal, long double error);
	// create Ring Graph
	void Ring(int);
	/* create Tour Graph
	number of nodes in a ring,  number of rings
	*/
	void Torus(int, int);
	// create Laplacian graph
	void Cal_L();
	// calculate average value to compare
	void ComVal();


	// Return the value of grap

	//retuun address of i node
	GrapNode* Node(int);
	// return Average number
	long double Ave(); 
	// return number of node
	int Num_Node(); 
	//return value M (time_bandwidth_product)
	long double M();
	//return value Es (sensed_signal)
	long double Es();
	//return value SigmaSquare (error)
	long double SigmaSquar();
	//Public value
	long double L[100][100];

private:
	long double AveValue = 0;
	std::vector<GrapNode> graph;
	
	long double M_var = 0; 
	long double Es_var = 0;
	long double SigmaSquare_var = 0;

	std::vector<long double> h;
	void IntialChannelGain();
};

