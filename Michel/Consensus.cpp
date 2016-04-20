#include "Consensus.h"

#define threshold 1.0e-8



void Consensus::Input(Graph grap_input)
{
	graph = grap_input;
	W.resize(graph.Num_Node(), std::vector<long double>(graph.Num_Node(), 0));
}

void Consensus::Cal_W_LDegree()
{
	GrapNode* Node_pt1 = NULL;
	GrapNode* Node_pt2 = NULL;
	for (size_t i = 0; i < graph.Num_Node(); i++)
	{
		for (size_t j = 0; j < graph.Num_Node(); j++)
		{
			Node_pt1 = graph.Node(i);
			Node_pt2 = graph.Node(j);
			W[i][j] = 1.0/std::max(Node_pt1->Numb_Neighbor(), Node_pt2->Numb_Neighbor());
		}
	}
}

void Consensus::Cal_W_Max()
{
	GrapNode* Node_pt = NULL;
	int max = INT_MIN;
	for (size_t i = 0; i < graph.Num_Node(); i++)
	{
		Node_pt = graph.Node(i);
		max = (Node_pt->Numb_Neighbor() > max) ? Node_pt->Numb_Neighbor() : max;
	}
	for (size_t i = 0; i < graph.Num_Node(); i++)
	{
		for (size_t j = 0; j < graph.Num_Node(); j++)
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

	


	for (size_t i = 0; i < graph.Num_Node(); i++)
	{
		for (size_t j = 0; j < graph.Num_Node(); j++)
		{
			W[i][j] = 0;
		}
	}

	for (size_t i = 0; i < graph.Num_Node(); i++)
	{
		for (size_t j = 0; j < graph.Num_Node(); j++)
		{
			Node_pt1 = graph.Node(i);
			Node_pt2 = graph.Node(j);
			if (i != j && Node_pt1->Belong_Neighbor(j)) {
				W[i][j] = 1.0 / (1 + std::max(Node_pt1->Numb_Neighbor(), Node_pt2->Numb_Neighbor()));
			}
		}
	}

	for (size_t i = 0; i < graph.Num_Node(); i++)
	{
		s = 0;
		Node_pt1 = graph.Node(i);
		std::vector<GrapNode*> list = Node_pt1->Neighbor();
		for (size_t j = 0; j < list.size(); j++)
		{
			s += W[i][list[j]->NodeNum()];
		}
		W[i][i] = 1 - s;
	}
	

}

void Consensus::Cal_W_EWeight(long double e)
{
	for (size_t i = 0; i < graph.Num_Node(); i++)
	{
		for (size_t j = 0; j < graph.Num_Node(); j++)
		{
			W[i][j] = e / graph.Num_Node();
		}
	}
}

void Consensus::Cal_A(std::ostream& stream = std::cout)
{
	int i, j;
	
	/*
	long double at1[100];
	long double at2[100];
	*/
	unsigned long long loop = 0;
	bool stop = 0;
	
	int n = graph.Num_Node();
	GrapNode* Node_pt1 = NULL;

	std::vector<long double> at1(n, 0), at2(n, 0);
	// Initial value
	for (i = 0; i < n; i++) {
		Node_pt1 = graph.Node(i);
		at1[i] = Node_pt1->Data();
	}
	long double temp;


	do
	{
		loop++;
		for (i = 0; i < n;i++)
		{
			
			at2[i] = at1[i];
			Node_pt1 = graph.Node(i);
			std::vector<GrapNode*> list = Node_pt1->Neighbor();
			// taking value from neighbor 
			for (size_t k = 0; k < list.size(); k++)
			{
				j = list[k]->NodeNum();
				at2[i] += W[i][j] * (at1[j] - at1[i]);
			}

			
		
			
			temp = fabs(at2[i] - at1[i]);
			//temp = std::Vector::Subtract(at2, at1);
				//grap.Ave());
			if (temp < threshold)
			{
				stream << " --> Convergence at iteration " << loop << "; agent " << i << " reaches value = " << at2[i] << std::endl;
				stream << std::fixed << std::setprecision(8) << "previous value: " << at1[i] << std::endl;
				stream << std::fixed << std::setprecision(8) << "difference: " << temp << std::endl;
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

	stream << "The final value: " << std::endl << std::endl;
	for (int i = 0; i < at2.size(); i++)
	{
		if (i % 100 == 0) stream << std::endl;
		stream << at2[i] << " ";

	}
}

void Consensus::Cal_A_RandNegi(std::ostream& stream = std::cout)
{
	int i, j;
	/*
	long double at1[100];
	long double at2[100];
	*/
	unsigned long long loop = 0;
	bool stop = 0;

	int n = graph.Num_Node();
	GrapNode* Node_pt1 = NULL;

	std::vector<long double> at1(n, 0), at2(n, 0);

	for (i = 0; i < n; i++) {		Node_pt1 = graph.Node(i);		at1[i] = Node_pt1->Data();	}

	std::srand(time(NULL));
	long double temp;
	do
	{
		loop++;
		for (i = 0; i < n; i++)
		{

			at2[i] = at1[i];
			Node_pt1 = graph.Node(i);
			std::vector<GrapNode*> list = Node_pt1->Neighbor();
			// taking value from neighbor randomly
			int RandIndex = rand() % list.size();
			j = list[RandIndex]->NodeNum();
			at2[i] += W[i][j] * (at1[j] - at1[i]);

			temp = fabs(at2[i] - at1[i]);
			//grap.Ave());
			if (temp < threshold)
			{
				stream << " --> Convergence at iteration " << loop << "; agent " << i << " reaches value = " << at2[i] << std::endl;
				stream << "Neighbour node number: " << j << " Value: "<<  at1[j] << std::endl;
				stream << std::fixed << std::setprecision(8) << "difference: "<< temp << std::endl;
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


	stream << "The final value: " << std::endl << std::endl;
	for (int i = 0; i < at2.size(); i++)
	{
		if (i % 100 == 0) stream << std::endl;
		stream << at2[i] << " ";
		
	}

}

void Consensus::Def_5()
{

}

