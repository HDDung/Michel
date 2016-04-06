#include "Consensus.h"





void Consensus::Input(Grap grap_input)
{
	grap = grap_input;
	W.resize(grap.Num_Node(), std::vector<double>(grap.Num_Node(), 0));
}

void Consensus::Cal_W_LDegree()
{
	GrapNode* Node_pt1 = NULL;
	GrapNode* Node_pt2 = NULL;
	for (size_t i = 0; i < grap.Num_Node(); i++)
	{
		for (size_t j = 0; j < grap.Num_Node(); j++)
		{
			Node_pt1 = grap.Node(i);
			Node_pt2 = grap.Node(j);
			W[i][j] = 1/std::fmax(Node_pt1->Numb_Neighbor(), Node_pt2->Numb_Neighbor());
		}
	}
}

void Consensus::Cal_W_Max()
{
	GrapNode* Node_pt = NULL;
	int max = -1;
	for (size_t i = 0; i < grap.Num_Node(); i++)
	{
		Node_pt = grap.Node(i);
		max = (Node_pt->Numb_Neighbor() > max) ? Node_pt->Numb_Neighbor() : max;
	}
	for (size_t i = 0; i < grap.Num_Node(); i++)
	{
		for (size_t j = 0; j < grap.Num_Node(); j++)
		{
			W[i][j] = 1.0/max;
		}
	}
}


void Consensus::Cal_W_MetroHast()
{
	GrapNode* Node_pt1 = NULL;
	GrapNode* Node_pt2 = NULL;
	double s = 0;

	


	for (size_t i = 0; i < grap.Num_Node(); i++)
	{
		for (size_t j = 0; j < grap.Num_Node(); j++)
		{
			W[i][j] = 0;
		}
	}

	for (size_t i = 0; i < grap.Num_Node(); i++)
	{
		for (size_t j = 0; j < grap.Num_Node(); j++)
		{
			Node_pt1 = grap.Node(i);
			Node_pt2 = grap.Node(j);
			if (i != j && Node_pt1->Belong_Neighbor(j)) {
				W[i][j] = 1 / (1 + std::fmax(Node_pt1->Numb_Neighbor(), Node_pt2->Numb_Neighbor()));
			}
		}
	}

	for (size_t i = 0; i < grap.Num_Node(); i++)
	{
		s = 0;
		Node_pt1 = grap.Node(i);
		std::vector<GrapNode*> list = Node_pt1->Neighbor();
		for (size_t j = 0; j < list.size(); j++)
		{
			s += W[i][list[j]->NodeNum()];
		}
		W[i][i] = 1 - s;
	}
	

}

void Consensus::Cal_W_EWeight(double e)
{
	for (size_t i = 0; i < grap.Num_Node(); i++)
	{
		for (size_t j = 0; j < grap.Num_Node(); j++)
		{
			W[i][j] = e / grap.Num_Node();
		}
	}
}

void Consensus::Cal_A()
{
	int i, j;
	
	/*
	double at1[100];
	double at2[100];
	*/
	unsigned long long loop = 0;
	bool stop = 0;
	
	int n = grap.Num_Node();
	GrapNode* Node_pt1 = NULL;

	std::vector<double> at1(n, 0), at2(n, 0);
	// Initial value
	for (i = 0; i < n; i++) {
		Node_pt1 = grap.Node(i);
		at1[i] = Node_pt1->Data();
	}
	double temp;


	do
	{
		loop++;
		for (i = 0; i < n;i++)
		{
			
			at2[i] = at1[i];
			Node_pt1 = grap.Node(i);
			std::vector<GrapNode*> list = Node_pt1->Neighbor();
			// taking value from neighbor 
			for (size_t k = 0; k < list.size(); k++)
			{
				j = list[k]->NodeNum();
				at2[i] += W[i][j] * (at1[j] - at1[i]);
			}

			
		
			
			temp = fabs(at2[i] - at1[i]);
				//grap.Ave());
			if (temp < 1.0e-6 )
			{
				std::cout << " --> Convergence at iteration " << loop << "; agent " << i << " reaches value = " << at2[i] << std::endl;
				stop = 1;
				//system("pause");
			}
		}

		if (loop%1000 == 0) {
			for (i = 0; i < n;i++) std::cout << at2[i] << " ";
			std::cout << std::endl << loop << " " << std::endl ;

		}

		for (i = 0; i < n;i++) at1[i] = at2[i];
	} while (!stop && loop <= maxLOOP);
}

void Consensus::Cal_A_RandNegi()
{
	int i, j;
	/*
	double at1[100];
	double at2[100];
	*/
	unsigned long long loop = 0;
	bool stop = 0;

	int n = grap.Num_Node();
	GrapNode* Node_pt1 = NULL;

	std::vector<double> at1(n, 0), at2(n, 0);

	for (i = 0; i < n; i++) {
		Node_pt1 = grap.Node(i);
		at1[i] = Node_pt1->Data();
	}

	std::srand(time(NULL));
	double temp;
	do
	{
		loop++;
		for (i = 0; i < n; i++)
		{

			at2[i] = at1[i];
			Node_pt1 = grap.Node(i);
			std::vector<GrapNode*> list = Node_pt1->Neighbor();
			// taking value from neighbor randomly
			int RandIndex = rand() % list.size();
			j = list[RandIndex]->NodeNum();
			at2[i] += W[i][j] * (at1[j] - at1[i]);

			temp = fabs(at2[i] - at1[i]);
			//grap.Ave());
			if (temp < 1.0e-6 )
			{
				std::cout << " --> Convergence at iteration " << loop << "; agent " << i << " reaches value = " << at2[i] << std::endl;
				stop = 1;
				//system("pause");
			}
		}

		if (loop % 1000 == 0) {
			for (i = 0; i < n; i++) std::cout << at2[i] << " ";
			std::cout << std::endl << loop << " " << std::endl;

		}

		for (i = 0; i < n; i++) at1[i] = at2[i];
	} while (!stop && loop <= maxLOOP);
}

void Consensus::Def_5()
{

}

