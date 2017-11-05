#include "neuron.hpp"
#include "network.hpp"
#include "simulation.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>



int main () {
	
	//Creation of the oftream output_file and opening
	std::ofstream output_file;
	output_file.open("spikes.txt");
	
	//Instanciation of a simulation and running
	Simulation simulation;
	simulation.run(output_file); 
	
	std::cout<<"Simulation : done"<<std::endl;
	
	//Closing of the file
	output_file.close();
	
	return 0;
}
