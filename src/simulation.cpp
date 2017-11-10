#include "simulation.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>


//!Constructor
Simulation::Simulation() {
	
	clock=0;
	simtimeEntry();	//!Entry of the simulation time
	double g=gEntry();
	JI=g/JE;
	eta=etaEntry();
}
	
	
//!Destructor
Simulation::~Simulation() {}
	
	
//!For the entry of the simulation time
void Simulation::simtimeEntry() {
	std::cout<<"Enter the simulation time in ms : ";
	double time;
	std::cin>>time;
	assert(time>=0); //Verifies that time is positive
	simtime=(static_cast<unsigned int long>(time*10))/(static_cast<unsigned long>(h*10)); //To avoid round errors
	std::cout<<std::endl;
}


//!For the entry of the eta value
double Simulation::etaEntry() {
	std::cout<<"Enter the value of Nu_ext/Nu_thr : ";
	double eta_;
	std::cin>>eta_;
	assert(eta_>0); //Verifies that eta_ is strictly positive
	return eta_;
}


//!For the entry of the g value
double Simulation::gEntry() {
	std::cout<<"Enter the value of g=JE/JI : ";
	double g_;
	std::cin>>g_;
	assert(g_>0); //Verifies that g_ is strictly positive
	return g_;
}


//!Getter for the value of the global clock of the simulation
unsigned int long Simulation::getClock() const {
	return clock;
}


//!Getter for the simulation time
unsigned int long Simulation::getSimtime() const {
	return simtime;
}
	

//!Method that updates the global clock at each simulation step
void Simulation::updateClock() {
	++clock;
}


//!Method that runs the simulation at each simulation step
void Simulation::run(std::ofstream& output_file) { 
	
	/*
	 * Creation of a network with nbrExcitNeuronsEntry() excitatory neurons 
		and nbrInhibNeuronsEntry() inhibitory neurons
	*/
	Network network (NE, NI, eta, JI);
	
	
	/*
	 * While the simulation time is not up, at each simulation step :
	 * update of the network 'network'
	 * update of the global clock
	*/
	while (getClock()<simtime) {
		
		network.update(0.0, output_file);  //External_current of 0.0
		
		updateClock();		

	}	
}
		
	
	
