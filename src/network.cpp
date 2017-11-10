#include "network.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <random>


//!Constructor
Network::Network(unsigned int long nbr_excitatory, unsigned int long nbr_inhibitory, double eta_, double JI_)
: clock(0), JI(JI_), nbrExcitatory(nbr_excitatory), nbrInhibitory(nbr_inhibitory)
{
	
	Nu_ext=eta_*V_thr*h/(J*TAU);

	unsigned int nbr_tot (nbr_excitatory);
	nbr_tot += nbr_inhibitory;
	setNbrNeurons(nbr_tot);
	
	
	//Constuction of nbr_excitatory excitatory neurons in the network
	if((nbr_excitatory!=0)) {
		for(size_t i(0); i<nbr_excitatory; ++i) { 
			neurons.push_back(Neuron (true));
		}
	}
	
	//Construction of nbr_inhibitory inhibitory neurons in the network
	if((nbr_inhibitory!=0)) {
		for(size_t i(0); i<nbr_inhibitory; ++i) {
			neurons.push_back(Neuron (false));
		}	
	}
	
	
	//Creation of 2 random uniform int distributions
	/* 
	 * d1 : uniform int distribution in the interval [0, nbr_excitatory-1]
	 * d2 : uniform int distribution in the interval [nbr_excitatory-1, nbr_tot-1]
	*/
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<>d1(0, nbr_excitatory-1);
	std::uniform_int_distribution<>d2(nbr_excitatory, nbr_tot-1);
	

	//Creation of neuron connections
	/*
	 * for each neuron of the total number of neurons of the network (nbr_tot) :
	 * -> creation of CE excitatory connections
	 * -> creation of CI inhibitory connections
	*/
	for(unsigned int long i(0); i<nbr_tot; ++i) {
		
		for(unsigned int long j(0); j<CE; ++j) {
			
			/*
			 * Addition of the index of the neuron i in the attribute neurons of the network 
			   to the attribute targets of a random excitatory neuron of the network
			*/
			neurons[d1(gen)].addTarget(i);  
		}
		
		for(unsigned int long j(0); j<CI; ++j) {
			/*
			 * Addition of the index of the neuron i in the attribute neurons of the network 
			   to the attribute targets of a random inhibitory neuron of the network
			*/
			neurons[d2(gen)].addTarget(i);
		}
			
	}
	
	std::cout<<"Connections : done"<<std::endl;
	
}
		
	
//!Destructor
Network::~Network() {
	
	setNbrNeurons(0);
		
	neurons.clear();	//Clearing of the vector that stores the neurons of the network
}


//!Getter for the local clock of the neuron
unsigned int long Network::getClock() const {
	return clock;
}


//!Getter for the number of neurons in the network
unsigned int long Network::getNbrNeurons() const {
	return nbrNeurons;
}


//!Getter for the neurons of the network
std::vector<Neuron> Network::getNeurons() const {
	return neurons;
}
	

//!Test method used in the unitTests to know the number of excitatory connections that receives the neuron 'neuronNumber'
unsigned int long Network::ExcitatoryConnectionsTest(unsigned int long neuronNumber) const {
	unsigned int nbr_excitatory_connections(0);
	for(size_t j(0); j<(nbrExcitatory); ++j) {			
		/*
		* We look for the presence of the neuron 'neuronNumber' of neurons 
		in targets of the j excitatory neurons of the network
		*/ 
		
		nbr_excitatory_connections+=neurons[j].isTarget(neuronNumber);
	}	
	
	return nbr_excitatory_connections;
} 


//!Test method used in the unitTests to know the number of inhibitory connections that receives the neuron 'neuronNumber'
unsigned int long Network::InhibitoryConnectionsTest(unsigned int long neuronNumber) const {
	unsigned int nbr_inhibitory_connections(0);
	for(size_t j(nbrExcitatory); j<nbrNeurons; ++j) {			
		/*
		* We look for the presence of the neuron 'neuronNumber' of neurons 
		in targets of the j excitatory neurons of the network
		*/ 
		
		nbr_inhibitory_connections+=neurons[j].isTarget(neuronNumber);
	}	
	
	return nbr_inhibitory_connections;
} 	
	
//!Setter for the total number of neurons in the network
void Network::setNbrNeurons(unsigned int long nbr) {
	nbrNeurons=nbr;
}


//!Method that updates the network at each time step of the simulation
void Network::update(double external_current, std::ofstream& output_file) {
	
	bool spike;
	
	//Creation of a random poisson distribution of parameter Vext
	static std::random_device rd;	
	static std::mt19937 gen(rd());
	std::poisson_distribution<> d(Nu_ext); 
	
	//For each neuron of the network 
	for(size_t i(0); i<neurons.size(); ++i) { 
		
		spike=neurons[i].update(external_current, d(gen));	//Update of each neuron 
		
		/*These 2 lines can be uncommented to have a display on the terminal */
		//std::cout<<"Neuron "<<i+1<<" : ";
		//neurons[i].display();	//Display of the potential value of each neuron on the terminal
		
		
		//If a spike for the neuron i of neurons occured
		if(spike) {
			
			//Writing of the time when the spike occured and the neuron number in output_file 
			output_file<<getClock()<<'\t'<<i+1<<'\n'; 
			
			
			//For each 'target' of the neuron i 
			for(auto target : neurons[i].getTargets()) { 
				
				if(neurons[i].isExcitatory()) { 
					
					/* If the neuron i is excitatory :
					 * the target j of the attribute targets of the neuron i will 
						receive a signal of weight WE in its buffer with a certain delay
					*/
					neurons[target].receiveSpike(clock+(delay_steps), JE); 
					
				} else {
					
					/* If the neuron i is inhibitory :
					 * the target j of the attribute targets of the neuron i will 
						receive a signal of weight WI in its buffer with a certain delay
					*/
					neurons[target].receiveSpike(clock+(delay_steps), -JI); 
					
				} 
			} 
		}
	}
		
	
	updateClock();	//Update of the local clock of the network at each simulation step

}
			

//!Method that updates the local clock of the network
void Network::updateClock() {
	++clock;
}	
