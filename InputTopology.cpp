/*
 * LogicalTopology.cpp
 *
 *  Created on: 2013-08-06
 *      Author: ar3roy
 */

#include "InputTopology.h"

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stddef.h>

using namespace std;

InputTopology* InputTopology::inputTopology=NULL;


InputTopology* InputTopology:: getInputTopology()
{
	if(inputTopology == NULL)
		inputTopology = new InputTopology();

	return inputTopology;
}

unsigned long InputTopology::getNumberOfSwitches()
{
	return this->numberOfSwitches;
}

void InputTopology::populateTopology(string fileName) {


	ifstream fin(fileName.c_str());

	if(fin.is_open())
	{
		unsigned long numberOfEdges;
		fin >> this->numberOfSwitches;
		fin >> numberOfEdges;

		this->topology = new LinkProperty *[this->numberOfSwitches];

		for(unsigned long i = 0; i < this->numberOfSwitches; i++)
		{
			this->topology[i] = new LinkProperty [this->numberOfSwitches];
		}

		for(unsigned long i = 0; i < numberOfEdges; i++)
		{
			string source, destination;
			double bandwidth, delay;
			fin >> source >> destination >> bandwidth >> delay;

			this->topology[atol(source.substr(1).c_str())-1][atol(destination.substr(1).c_str())-1].bandwidth = bandwidth;
			this->topology[atol(destination.substr(1).c_str())-1][atol(source.substr(1).c_str())-1].bandwidth = bandwidth;
			this->topology[atol(source.substr(1).c_str())-1][atol(destination.substr(1).c_str())-1].delay = delay;
			this->topology[atol(destination.substr(1).c_str())-1][atol(source.substr(1).c_str())-1].delay = delay;

		}

		fin.close();

	}
	else
		cout << "Unable to open topology file: " << fileName << endl;

}

void InputTopology::populateTopologyBandwidth(double**& topologyBandwidth) {

	topologyBandwidth = new double* [this->numberOfSwitches];

	for(unsigned long i = 0; i < this->numberOfSwitches; i++)
	{
		topologyBandwidth[i] = new double[this->numberOfSwitches];

		for(unsigned long j = 0; j < this->numberOfSwitches; j++)
			topologyBandwidth[i][j] = this->topology[i][j].bandwidth;
 	}
}

void InputTopology::populateTopologyDelay(double**& topologyDelay) {

	topologyDelay = new double* [this->numberOfSwitches];

	for(unsigned long i = 0; i < this->numberOfSwitches; i++)
	{
		topologyDelay[i] = new double[this->numberOfSwitches];

		for(unsigned long j = 0; j < this->numberOfSwitches; j++)
			topologyDelay[i][j] = this->topology[i][j].delay;
 	}
}

InputTopology::InputTopology() {


}

double InputTopology::getLinkDelay(unsigned long switch1,
		unsigned long switch2) {

	return this->topology[switch1][switch2].delay;
}

double InputTopology::getLinkBandwidth(unsigned long switch1,
		unsigned long switch2) {

	return this->topology[switch1][switch2].bandwidth;
}

bool InputTopology::isNeighbor(unsigned long switch1, unsigned long switch2) {
	return this->topology[switch1][switch2].bandwidth != 0 || this->topology[switch2][switch1].bandwidth != 0;
}

InputTopology::~InputTopology() {

}

