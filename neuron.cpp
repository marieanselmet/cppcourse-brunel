#include "neuron.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <random>


//!Constructor
Neuron::Neuron(bool excitat) : incoming_spikes(delay_steps+1) { 
	setPotential(0.0);
	nbr_spikes=0;
	clock=0;
	excitatory=excitat;
	
	for(auto& value : incoming_spikes) {	//At the construction of the neuron, its buffer doesn't contain signals. 
		value=0;
	}
}


//!Destructor
Neuron::~Neuron() {

	setPotential(0.0);

	for(auto& value : incoming_spikes) {	//At the destruction of the neuron, its buffer doesn't contain signals
		value=0;
	}
	
	targets.clear();	//At the destruction, the neuron has no more targets	
}

	
//!Getter for the attribute excitatory
bool Neuron::isExcitatory() const {
	return excitatory;
}


//!Getter for the potential of the neuron
double Neuron::getPotential() const {
	return potential;
}


//!Getter for the spike number 
unsigned int Neuron::getNbrSpikes() const {
	return nbr_spikes;
}


//!Getter for the time of the last spike
double Neuron::getLastTime() const {
	return times.back();
}

//!Method that return if the attribute times is empty
bool Neuron::timesEmpty() const {
	return times.empty();
}


//!Getter for the local clock
unsigned int Neuron::getClock() const {
	return clock;
}


//!Method used to know if the neuron is refractory
bool Neuron::isRefractory() const {
	return ((clock-getLastTime())*h<Tref);  //The neuron is refractory if the time since its last spike is < Tref
}


//!Getter for the targets of the neuron
std::vector<unsigned int long> Neuron::getTargets() const {
	return targets;
}	


//!Setter for the membrane potential value of the neuron
void Neuron::setPotential(double new_potential) {
	potential=new_potential;
}


//!Method to add a new target in the attribute targets of the neuron
void Neuron::addTarget(unsigned int long target) {
	targets.push_back(target);
}


//!Method used in unitTests to know the number of times the neuron 'neuronNumber' is present in targets
unsigned int Neuron::isTarget(unsigned int neuronNumber) const {
	
	unsigned int nbr(0);
	for(size_t i(0); i<targets.size(); ++i) {
		if((targets[i])==neuronNumber) {
			++nbr;	//If the neuron 'neuronNumber' is present in targets, we increment nbr by +1
		}
	}

	return nbr;
}

	
//!Method that increments the number of spikes by 1
void Neuron::incrementNbrSpikes() {
	++nbr_spikes;
}


//!Method that adds a time in the attribute times of the neuron
void Neuron::addTimes(int time) {
	 times.push_back(time);
}


//!Method for the calculation of the membrane potential
void Neuron::updatePotential(double Iext, unsigned int random) {

	//Calculation of the membrane potential
	/*
	* the first and the second term of the calculation 
	* the third term of the calculation considers the buffer and thus the incoming spikes of the connections
		->it adds (J*nbr of spikes) of connections at time 'clock-D' to the calculation of potential
	* the fourth term corresponds to a random connection with outside (poisson law)
	*/
	potential=potential*exp(-(h)/TAU)+Iext*RESISTANCE*(1-exp(-(h)/TAU))+ J*(incoming_spikes[clock%(delay_steps+1)]) + J*random; 
}


//!Method that update the local clock of the neuron
void Neuron::updateClock() {
	++clock;
}


//!Method that updates the state of the neuron at each step of the simulation
bool Neuron::update(double Iext, unsigned int random) {
	  
	bool spike(false); //For de return type of the method
		
		
	//If neuron's potential exceeds V_thr -> spike. 
	if(getPotential()>V_thr) {	
		addTimes(getClock()); 	//Add he spike time to the attribute times of the neuron
		incrementNbrSpikes();	//Increment the total number of spikes of the neuron since the beginning of the simulation by +1
		setPotential(0.0);  //Set the membrane potential of the neuron to 0.0 afer a spike
		spike=true;		//For the return of the method
	}
		
	//If the neuron is refractory, keep its potential at 0.0, else udpate its membrane potential
	if((!(timesEmpty())) and (isRefractory())) {  
		setPotential(0.0);	 	
	} else {	
		updatePotential(Iext, random);
	}
		
		
	//Reset the number of signals of connections in the buffer corresponding to time 'clock' to 0
	resetIncomingSpikes(); 
	
	
	//Update of the local clock at each step of the simulation
	updateClock();  
		
		
	return spike;	
}
	


bool Neuron::updateTest(unsigned int long time, double Iext) {
	
	bool spike(false); //For de return type of the method
		
	for(size_t i(0); i<time; ++i) {		//time iterations for the update of the neuron
	
		spike=false;
		
		
		//If neuron's potential exceeds V_thr -> spike. 
		if(getPotential()>V_thr) {	
			addTimes(getClock()); 	//Add he spike time to the attribute times of the neuron
			incrementNbrSpikes();	//Increment the total number of spikes of the neuron since the beginning of the simulation by +1
			setPotential(0.0);  //Set the membrane potential of the neuron to 0.0 afer a spike
			spike=true;		//For the return of the method
		}
		
		
		//If the neuron is refractory, keep its potential at 0.0, else udpate its membrane potential
		if((!(timesEmpty())) and (isRefractory())) {  
			setPotential(0.0);	 	
		} else {
			//Calculation of the potential without the outside noise (ie without the poisson distribution)	
			potential=potential*exp(-(h)/TAU)+Iext*RESISTANCE*(1-exp(-(h)/TAU))+ J*(incoming_spikes[clock%(delay_steps+1)]); 
		}
		
		
		//Reset the number of signals of connections in the buffer corresponding to time 'clock' to 0
		resetIncomingSpikes(); 
	
	
		//Update of the local clock at each step of the simulation
		updateClock();  
		
	}
		
		
	return spike;
}
	
	
//!Method that 'manages' when the neuron receives a spike
void Neuron::receiveSpike(unsigned long t, int weight) {   
	
	const auto t_buff=t%(delay_steps+1);	// t_buff gives the index corresponding to time t in the neuron buffer
	assert(t_buff<incoming_spikes.size());	//Verification that t_buff really indexes an existing box of the neuron buffer
	incoming_spikes[t_buff]+=weight;	//Addition of the signal of weight 'weight' in the neuron buffer
}


//!Method that resets the neuron buffer 
void Neuron::resetIncomingSpikes() {
	incoming_spikes[clock%(delay_steps+1)]=0;
}


//!Display method
void Neuron::display() const {
	std::cout<<"V("<<clock*h<<")="<<getPotential()<<std::endl;
}
