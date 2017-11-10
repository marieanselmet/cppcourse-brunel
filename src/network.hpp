//! Network class
/*!To model neuron networks
 */
#ifndef NETWORK_H 
#define NETWORK_H
#include "neuron.hpp"
#include <iostream>
#include <vector>
#include <cmath>


class Network {
	
	public :
	
	//!Constructor
	/*!
	 *\param nbr_excitatory the number of excitatory neurons in the network
	 *\param nbr_inhibitory the number of inhibitory neurons in the network
	 *\param eta_ the value of the ratio Nu_ext/Nu_thr
	 *\param JI_ the weight of inhibitory connections
	*/
	Network(unsigned int long nbr_excitatory, unsigned int long nbr_inhibitory, double Nu_ext_, double JI_);
	
	
	//!Destructor
	~Network();
	
	
	//!Getter for the local clock of the neuron
	/*!
	 *\return the value of the attribute clock of the network
	*/
	unsigned int long getClock() const;
	
	
	//!Getter for the number of neurons in the network
	/*!
	 *\return the value of the attribute nbrNeurons, the number of neurons in the network
	*/
	unsigned int long getNbrNeurons() const;
	
	
	//!Getter for the neurons of the network
	/*!
	 *\return a vector of neurons that contains the neurons of the network
	*/
	std::vector<Neuron> getNeurons() const;
	
	
	//!Test method used in the unitTests to know the number of excitatory connections that receives the neuron 'neuronNumber'
	/*!
	 *\param neuronNumber the number of the corresponding neuron in neurons
	 *\return the number of excitatory connections that receives the neuron 'neuronNumber'
	*/
	unsigned int long ExcitatoryConnectionsTest(unsigned int long neuronNumber) const;
	
	
	//!Test method used in the unitTests to know the number of inhibitory connections that receives the neuron 'neuronNumber'
	/*!
	 *\param neuronNumber the number of the corresponding neuron in neurons
	 *\return the number of inhibitory connections that receives the neuron 'neuronNumber'
	*/
	unsigned int long InhibitoryConnectionsTest(unsigned int long neuronNumber) const;
	
	//!Setter for the total number of neurons in the network
	/*!
	 *\param nbr the total number of neurons in the network
	*/
	 void setNbrNeurons(unsigned int long nbr);
	
	
	//!Method that updates the network at each time step of the simulation
	/*!
	 * updates each neuron of the network
	 * updates the neuron connections of the network
	 * updates the local clock
	 *\param external_current the external current (0.0 mV in our simulation)
	 *\param output_file the file where to write times of the neuron spikes
	*/
	void update(double external_current, std::ofstream& output_file);
	
	
	//!Method that updates the local clock of the network
	/*!
	 * increment the local clock of the network at each simulation step
	*/
	void updateClock();
	
	
	
	private :
	
	unsigned int long clock;	//!Local clock of the network (current time)
	double JI;	//!Weight of inhibitory connections
	double Nu_ext;	//!Background rate
	unsigned int long nbrNeurons;	//!Total number of neurons in the network
	unsigned int long nbrExcitatory;	//!Number of excitatory neurons of the network
	unsigned int long nbrInhibitory;	//!Number of inhibitory neurons of the network
	std::vector<Neuron> neurons;	//!Vector of the neurons of the network
	
	
};

#endif
