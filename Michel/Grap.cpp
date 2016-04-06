#include "Grap.h"

#define RandomValue 8
#define RandomChannel 10


void Grap::Input(double time_bandwidth_product, double sensed_signal, double error)
{
	M_var = time_bandwidth_product;
	Es_var = sensed_signal;
	SigmaSquare_var = error;

}

void Grap::Ring(int NumbNode)
{
	
	srand(time(NULL));
	for (size_t i = 0; i < NumbNode; i++)
	{
		GrapNode node;
		node.AddNum(i);
		node.Value(rand() % RandomValue + 1);
		node.AddChannelGain((rand() % RandomChannel + 1) / 10.0);
		grap.push_back(node);
	}

	grap[0].Add(&grap[NumbNode - 1]);
	grap[0].Add(&grap[1]);
	for (size_t i = 1; i < NumbNode-1; i++)
	{
		grap[i].Add(&grap[i - 1]);
		grap[i].Add(&grap[i + 1]);
	}
	grap[NumbNode - 1].Add(&grap[NumbNode - 2]);
	grap[NumbNode - 1].Add(&grap[0]);
}

void Grap::Tour(int d1, int d2)
{
	//create all node
	srand(time(NULL));
	for (size_t i = 0; i < d1*d2; i++)
	{
		GrapNode node;
		node.AddNum(i);
		node.Value(rand() % RandomValue + 1);
		node.AddChannelGain((rand() % RandomChannel + 1)/10.0);
		grap.push_back(node);
	}
	// create link of each nodes in each rings 
	for (size_t j = 0; j < d2; j++)
	{
		grap[j*d1].Add(&grap[j*d1 + d1 - 1]);
		grap[j*d1].Add(&grap[j*d1+1]);
		for (size_t i = j*d1+1; i < j*d1 + d1 - 1; i++)
		{
			grap[i].Add(&grap[i - 1]);
			grap[i].Add(&grap[i + 1]);
		}
		grap[j*d1 + d1 - 1].Add(&grap[j*d1 + d1 - 2]);
		grap[j*d1 + d1 - 1].Add(&grap[j*d1]);
	}

	// link all rings together 

	for (size_t i = 1; i < d2; i++)
	{
		for (size_t j = 0; j < d1; j++)
		{
			grap[i*d1 + j].Add(&grap[d1*(i - 1) + j]);
		}
	}

	for (size_t i = 0; i < d1; i++)
	{
		grap[i].Add(&grap[d1*(d2 - 1) + i]);
	}
	

}

void Grap::Cal_L()
{
	for (size_t i = 0; i < grap.size(); i++)
	{
		for (size_t j = 0; j < grap.size(); j++)
		{
			if (grap[i].Belong_Neighbor(j)) {
				L[i][j] = -1;
			}
			else if ( i == j ) {
				L[i][j] = (double)grap[i].Numb_Neighbor();
			}
			else L[i][j] = 0;
		}
	}


}

void Grap::ComVal()
{
	AveValue = 0;
	for (size_t i = 0; i < grap.size(); i++)
	{
		AveValue += grap[i].Data();
	}
	AveValue = AveValue / grap.size();
}

GrapNode* Grap::Node(int i)
{
	return &grap[i];
}

double Grap::Ave()
{
	//ComVal();
	return AveValue;
}

int Grap::Num_Node()
{
	return grap.size();
}

double Grap::M()
{
	return M_var;
}

double Grap::Es()
{
	return Es_var;
}

double Grap::SigmaSquar()
{
	return SigmaSquare_var;
}
