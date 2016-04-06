#include "Attacker.h"
#include <math.h>


Attacker::Attacker()
{
}

void Attacker::Input(double P, double D, Grap graph)
{
	Prob = P;
	Delta = D;
	A_graph = graph;
}


void Attacker::Attack()
{
	double ave_h = 0;
	for (size_t i = 0; i < A_graph.Num_Node(); i++)
	{
		ave_h += A_graph.Node(i)->ReturnChannelGain();
	}
	ave_h /= A_graph.Num_Node();


	N1 = (((A_graph.Es() * abs(ave_h)) / A_graph.SigmaSquar()) * A_graph.SigmaSquar() * A_graph.Num_Node()) / (2 * Prob*Delta);

	
	for (int i = 0; i < N1; i++)
	{
		A_graph.Node(i)->Value(A_graph.Node(i)->Data() + Delta);
	}
}

Grap Attacker::Output()
{
	return A_graph;
}

int Attacker::Number_BNodes()
{
	return N1;
}


Attacker::~Attacker()
{
}
