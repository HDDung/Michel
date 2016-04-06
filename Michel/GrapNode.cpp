#include "GrapNode.h"





void GrapNode::Add(GrapNode* Node)
{
	neighbor.push_back(Node);
}

void GrapNode::AddNum(int numb)
{
	Node_number = numb;
}


void GrapNode::Value(double data)
{
	Node_value = data;
}

void GrapNode::AddChannelGain(double channel)
{
	channelGain = channel;
}

double GrapNode::Data()
{
	return Node_value;
}

int GrapNode::Numb_Neighbor()
{
	return neighbor.size();
}

bool GrapNode::Belong_Neighbor(int node_th)
{
	for (size_t i = 0; i < neighbor.size(); i++)
	{
		if (node_th == neighbor[i]->NodeNum())
		{
			return true;
		}
	}
	return false;
}

int GrapNode::NodeNum()
{
	return Node_number;
}

double GrapNode::ReturnChannelGain()
{
	return channelGain;
}

std::vector<GrapNode*> GrapNode::Neighbor()
{
	return neighbor;
}

