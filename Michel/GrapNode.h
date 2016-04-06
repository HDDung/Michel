#pragma once

#include <vector>
class GrapNode
{
public:
	// add neighbor
	void Add(GrapNode*); 
	// add node_th ;
	void AddNum(int); 
	// remove node_th
	void Remove(GrapNode*);
	// add value of node
	void Value(double); 
	//add channel gain
	void AddChannelGain(double channel);

	// return value of node
	double Data(); 
	// return number of neighbor
	int Numb_Neighbor(); 
	//belong to neighborhood
	bool Belong_Neighbor(int);
	// return node_th
	int NodeNum(); 
	//return channel gain
	double ReturnChannelGain();

	// return list neighbor of node
	std::vector<GrapNode*> Neighbor();
	
private:
	std::vector<GrapNode*> neighbor;
	double Node_value;
	int Node_number;
	double channelGain;
};

