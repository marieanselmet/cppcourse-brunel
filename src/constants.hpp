#ifndef CONSTANTS_H
#define CONSTANTS_H


constexpr double h = 0.1;	//!Time step for the simulation 
constexpr double delay = 1.5;	//!Synaptic delay in ms
static int delay_steps(static_cast<unsigned long> (delay/h)); //!Synaptic delay in steps
constexpr double TAU = 20.0;		//!Membrane time constant
constexpr double RESISTANCE = 20;	//!Membrane resistance
constexpr double Tref= 2.0; 	//!Refractory time in ms
constexpr double V_thr = 20.0;	//!Spike threshold
constexpr double J = 0.1;	//!Rate of the background neurons
constexpr int JE = 1; //!Weight of excitatory synaptic stimulations
constexpr int N = 12500; //!Number of neurons
constexpr int NE = 0.8*N; //!Number of excitatory neurons
constexpr int NI = 0.2*N; //!Number of inhibitory neurons
constexpr double CE = 1000;		//!Number of excitatory connections per neuron.
constexpr double CI = 250;	//!Number of inhibitory connections per neuron
constexpr double Nu_thr=V_thr/(CE*J*TAU);  //!The external frequency needed for the mean input to reach threshold in absence of feedback


#endif
