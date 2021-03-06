//! Neuron class
/*!To model neurons
 */
#ifndef NEURON_H 
#define NEURON_H
#include "constants.hpp"
#include <iostream>
#include <vector>
#include <cmath>



class Neuron {
	
	public :
	
	//!Constructor
	/*!
	 *\param excitat true if the neuron is excitatory, else false
	*/
	Neuron(bool excitat);
	
	
	//!Destructor
	~Neuron();
	
	
	//!Getter for the attribute excitatory
	/*!
	 *\return true if this neuron is excitatory, else false
	*/
	bool isExcitatory() const;
	
	
	//!Getter for the potential of the neuron
	/*!
	 *\return the potential value
	*/
	double getPotential() const;
	
	
	//!Getter for the spike number 
	/*!
	 *\return the number of spikes that occured between the start 
		of the simulation and the current time
	*/
	unsigned int getNbrSpikes() const;
	
	
	//!Getter for the neuron buffer
	/*!
	 *\return the buffer of the neuron
	*/
	std::vector<int> getIncomingSpikes() const;
	
	
	//!Getter for the time of the last spike
	/*!
	 *\return the time at which the last mesured spike occured
	*/
	double getLastTime() const;
	
	
	//!Method that return if the attribute times is empty
	/*!
	 *\return true if time is empty, else false
	*/
	bool timesEmpty() const;
	
	
	//!Method used to know if the neuron is refractory
	/*!
	 *\return true if the neuron is refractory, else false
	*/
	bool isRefractory() const;
	
	
	//!Getter for the targets of the neuron
	/*!
	 *\return a vector of unsigned int long that corresponds to the targets of the neuron
	*/
	std::vector<unsigned int long> getTargets() const;

	
	//!Setter for the membrane potential value of the neuron
	/*!
	 *\param new_potential the new value for the potential of the neuron
	*/
	void setPotential(double new_potential);
	
	
	//!Method to add a new target in the attribute targets of the neuron
	/*!
	 *\param target the number of the target neuron in neurons (in network.hpp)
	*/
	void addTarget(unsigned int long target);
	
	
	//!Method used in unitTests to know the number of times the neuron 'neuronNumber' is present in targets
	/*!
	 *\param neuronNumber the number of the corresponding neuron
	 *\return the number of times the neuron 'neuronNumber' is present in targets
	*/
	unsigned int isTarget(unsigned int neuronNumber) const;
	
	
	//!Method that increments the number of spikes by 1
	void incrementNbrSpikes();
	
	
	//!Method that adds a time in the attribute times of the neuron
	/*!
	 *\param time the current time, only when a spike occurs
	*/
	void addTimes(unsigned int long time);
	
	
	//!Method for the calculation of the membrane potential
	/*!
	 *\param Iext the input current (0.0 mV in our simulation)
	 *\param random a number generated by the random poisson distribution
	*/
	void updatePotential(double Iext, unsigned int random);
	
	
	//!Method that update the local clock of the neuron
	/*!
	 * Increment the local clock of the neuron at each step of the simulation
	*/
	void updateClock();
	
	
	//!Method that updates the state of the neuron at each step of the simulation
	/*!
	 * updates the membrane potential of the neuron
	 * updates the neuron buffer (attribute incoming_spikes)
	 * updates the local clock of the neuron
	 * updates the attributes concerning the spikes of the neuron
	 *\param Iext the input current (0.0 mV in our simulation)
	 *\param random a number generated by the random poisson distribution
	 *\return true if a spike occured during this step of simulation, else false
	*/
	bool update(double Iext, unsigned int random);
	
	
	//!Test method that updates the neuron without the background noise
	/*!
	 * updates the neuron without the term corresponding to the poisson distribution
		in the calculation of the membrane potential of the neuron
	 * updates the neuron 'times' simulation steps
	 *\param time the number of simulation steps to update the neuron
	 *\param Iext the input current
	 *\return true if a spike occured during this step of simulation, else false
	*/
	bool updateTest(unsigned int long time, double Iext);
	
	
	//!Method that 'manages' when the neuron receives a spike
	/*!
	 * add a signal of a certain weight in the neuron buffer (attribute incoming_spikes)
	 *\param t the time when the membrane potential of the neuron 
		must increase due to the spike of one of its connections  
	 *\param weight the weight of the connection between the neuron and the other
		neuron of the connection that spiked
	*/
	void receiveSpike(unsigned long t, int weight);
	
	
	//!Method that resets the neuron buffer 
	/*!
	 * resets the attribute incoming_spikes at each step of the simulation
	*/
	void resetIncomingSpikes();
	
	
	//!Display method
	/*!
	 * displays on the terminal the potential of the neuron
	*/
	void display() const;
	
	
	
	private :
	
	bool excitatory;	//!True if the neuron is excitatory, else false
	long double potential;	//!Membrane potential of the neuron (updated at each step of the simulation)
	unsigned int long nbr_spikes;	//!Total number of spikes of the neuron until the current time
	std::vector<unsigned int long> times;	//!Times when neuron spikes occured until the current time
	unsigned int long clock;	//!Local clock of the neuron (current time)
	std::vector<int> incoming_spikes;	//!Neuron buffer that stores the incoming spike signals of connections
	std::vector<unsigned int long> targets;	//!Connections which to send signals when the neuron spikes
	
	
	
	
};

#endif
