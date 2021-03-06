#include "Grap.h"
#include "Consensus.h"
#include "Attacker.h"


#include <iostream>
#include <fstream>

#define OUTFILE "OutPut2.txt"

void main() {
	int a;

	std::ofstream out(OUTFILE);

	int n = 30;
	
	for (int i = 0; i < n; i++)
	{
		Graph Torus;

		Torus.Torus(30, 30);
		Torus.Input(12, 5, 1);
		Consensus  consensus;

		Torus.ComVal();
		out << "Ave Value of Graph: " << Torus.Ave() << std::endl;

		consensus.Input(Torus);
		//consensus.Cal_W_EWeight(0.5);
		consensus.Cal_W_MetroHast();
		out << "Normal Consensus" << std::endl;
		consensus.Cal_A(out);
		out <<std::endl << "Random Neighbour\n";
		consensus.Cal_A_RandNegi(out);
		out << "\n-----------------------------------------------------\n";

	}
	out.close();
	/*
	Attacker Attack1;

	Attack1.Input(0.5, 4, Tour);
	Attack1.Attack();
	std::cout << Attack1.Number_BNodes() << std::endl;
	Grap A_Tour = Attack1.Output();
	*/
	//A_Tour.ComVal();
	//std::cout << A_Tour.Ave() << std::endl;
	//consensus.Input(A_Tour);
	
	/*
	Grap Ring;
	Ring.Ring(9); // create ring graph

	Tour.ComVal(); // calculate Ave value of the graph
	Tour.Cal_L(); // Create Laplacian graph
	std::cout << Tour.Ave() << std::endl;
	Consensus  consensus;
	consensus.Input(Tour); // input graph 
	consensus.Cal_W_MetroHast(); // choose Weight matrix for consensus (note: even nodes -> LDegree convergent: coool and only one node reach ave value )
	consensus.Cal_A(); // run consensus algorithm 

	std::cout << "End program, exit" << std::endl;
	*/
	system("pause");
}