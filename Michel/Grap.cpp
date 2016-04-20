#include "Grap.h"

#define RandomValue 987
#define RandomDiffValue 80
#define RandomChannel 10


void Graph::Input(long double time_bandwidth_product, long double sensed_signal, long double error)
{
	M_var = time_bandwidth_product;
	Es_var = sensed_signal;
	SigmaSquare_var = error;

}

void Graph::Ring(int NumbNode)
{
	
	srand(time(NULL));
	for (size_t i = 0; i < NumbNode; i++)
	{
		GrapNode node;
		node.AddNum(i);
		node.Value(rand() % RandomValue + 1);
		node.AddChannelGain((rand() % RandomChannel + 1) / 10.0);
		graph.push_back(node);
	}

	graph[0].Add(&graph[NumbNode - 1]);
	graph[0].Add(&graph[1]);
	for (size_t i = 1; i < NumbNode-1; i++)
	{
		graph[i].Add(&graph[i - 1]);
		graph[i].Add(&graph[i + 1]);
	}
	graph[NumbNode - 1].Add(&graph[NumbNode - 2]);
	graph[NumbNode - 1].Add(&graph[0]);
}

void Graph::Torus(int d1, int d2)
{
	//create all node
	srand(time(NULL));
	for (int i = 0; i < d1*d2; i++)
	{
		GrapNode node;
		node.AddNum(i);
		node.Value(rand() % RandomValue + 1);
		node.AddChannelGain((rand() % RandomChannel + 1)/10.0);
		graph.push_back(node);
	}
	// create link of each nodes in each rings 
	for (int j = 0; j < d2; j++)
	{
		//graph[j*d1].Add(&graph[j*d1 + d1 - 1]);
		graph[j*d1].Add(&graph[j*d1+1]);
		for (int i = j*d1+1; i < j*d1 + d1 - 1; i++)
		{
			//graph[i].Add(&graph[i - 1]);
			graph[i].Add(&graph[i + 1]);
		}
		//graph[j*d1 + d1 - 1].Add(&graph[j*d1 + d1 - 2]);
		graph[j*d1 + d1 - 1].Add(&graph[j*d1]);
	}

	// link all rings together 

	for (int i = 1; i < d2; i++)
	{
		for (int j = 0; j < d1; j++)
		{
			graph[i*d1 + j].Add(&graph[d1*(i - 1) + j]);
		}
	}

	for (int i = 0; i < d1; i++)
	{
		graph[i].Add(&graph[d1*(d2 - 1) + i]);
	}


	// make the value of all nodes different
	for (int i = 0; i < graph.size(); i++)
	{
		std::vector<GrapNode*> list = graph[i].Neighbor();
		// taking value from neighbor 
		for (size_t k = 0; k < list.size(); k++)
		{
			int j = list[k]->NodeNum();
			if (graph[i].Data() == graph[j].Data())
			{
				graph[j].Value(graph[j].Data() + rand() % RandomDiffValue + 1);
			}
		}
	}
	

}

void Graph::Cal_L()
{
	for (size_t i = 0; i < graph.size(); i++)
	{
		for (size_t j = 0; j < graph.size(); j++)
		{
			if (graph[i].Belong_Neighbor(j)) {
				L[i][j] = -1;
			}
			else if ( i == j ) {
				L[i][j] = (long double)graph[i].Numb_Neighbor();
			}
			else L[i][j] = 0;
		}
	}


}

void Graph::ComVal()
{
	AveValue = 0;
	for (size_t i = 0; i < graph.size(); i++)
	{
		AveValue += graph[i].Data();
	}
	AveValue = AveValue / graph.size();
}

GrapNode* Graph::Node(int i)
{
	return &graph[i];
}

long double Graph::Ave()
{
	//ComVal();
	return AveValue;
}

int Graph::Num_Node()
{
	return graph.size();
}

long double Graph::M()
{
	return M_var;
}

long double Graph::Es()
{
	return Es_var;
}

long double Graph::SigmaSquar()
{
	return SigmaSquare_var;
}
