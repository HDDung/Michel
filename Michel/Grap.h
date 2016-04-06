#pragma once
#include "GrapNode.h"
#include <vector>
#include <time.h>

class Grap
{
public:
	
	//Input value of Graph 
	void Input(double time_bandwidth_product, double sensed_signal, double error);
	// create Ring Graph
	void Ring(int);
	/* create Tour Graph
	number of nodes in a ring,  number of rings
	*/
	void Tour(int, int);
	// create Laplacian graph
	void Cal_L();
	// calculate average value to compare
	void ComVal();


	// Return the value of grap

	//retuun address of i node
	GrapNode* Node(int);
	// return Average number
	double Ave(); 
	// return number of node
	int Num_Node(); 
	//return value M (time_bandwidth_product)
	double M();
	//return value Es (sensed_signal)
	double Es();
	//return value SigmaSquare (error)
	double SigmaSquar();
	//Public value
	double L[100][100];

private:
	double AveValue = 0;
	std::vector<GrapNode> grap;
	
	double M_var = 0; 
	double Es_var = 0;
	double SigmaSquare_var = 0;

	std::vector<double> h;
	void IntialChannelGain();
};

