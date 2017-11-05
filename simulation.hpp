#ifndef SIMULATION_H 
#define SIMULATION_H
//! Simulation class
/*!To model simulations
 */
#include "network.hpp"
#include <iostream>
#include <vector>
#include <cmath>


class Simulation {
	
	public :
	
	//!Constructor
	Simulation();
	
	//!Destructor
	~Simulation();
	
	
	//!For the entry of the simulation time
	void simtimeEntry();
	
	//!For the entry of the eta value
	/*!
	 *\return the value of eta=Nu_ext/Nu_thr
	*/
	double etaEntry();
	
	
	//!For the entry of the g value
	/*!
	 *\return the value of g=JE/JI
	*/
	double gEntry();
	
	
	//!Method for the entry of the number of excitatory neurons in the simulation
	/*!
	 *\return the number of excitatory neurons for the simulation
	*/
	unsigned int long nbrExcitNeuronsEntry() const;
	
	
	//!Method for the entry of the number of inhibitory neurons in the simulation
	/*!
	 *\return the number of inhibitory neurons for the simulation
	*/
	unsigned int long nbrInhibNeuronsEntry() const;
	
	
	//!Getter for the value of the global clock of the simulation
	/*!
	 *\return the value of the attribute clock of the simulation
	*/
	unsigned int long getClock() const;
	
	
	//!Getter for the simulation time
	/*!
	 *\return the simulation time
	*/
	unsigned int long getSimtime() const;
	
	
	//!Method that updates the global clock at each simulation step
	void updateClock();
	
	
	//!Method that runs the simulation at each simulation step
	/*!
	 *\param file the file where to write times of the neuron spikes
	*/
	void run(std::ofstream& file);
	
	
	
	private :
	
	unsigned int long clock;	//!Global clock of the simulation
	unsigned int long simtime;	//!Simulation time
	double eta;	//!Value of the ratio Nu_ext/Nu_thr
	double JI;	//!Value of the ratio g/JE -> weight of inhibitory connections
	
	
	
	
};

#endif	

