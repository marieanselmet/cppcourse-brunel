#include <iostream>
#include "neuron.hpp"
#include "network.hpp"
#include <random>
#include "gtest/gtest.h"


TEST (NeuronTest, RefractoryTime) {
	
	Neuron neuron(false);
	
	neuron.updateTest(924, 1.01);	//The neuron should have its first spike at 92.4 ms
	EXPECT_EQ(0, neuron.getNbrSpikes());
	
	
	neuron.updateTest(1, 1.01);
	EXPECT_EQ(1, neuron.getNbrSpikes());	//The first spike have already occured
	EXPECT_EQ(0.0, neuron.getPotential());
	
	neuron.updateTest(19, 1.01);	//The neuron should be refractory
	EXPECT_EQ(0.0, neuron.getPotential());
	
	neuron.updateTest(1, 1.01);
	EXPECT_GT(neuron.getPotential(), 0.0);	//The neuron is no longer refractory 
	
}


TEST (NeuronTest, SpikeTimes) {
	//924, 1868, 2812, 3756
	Neuron neuron(true);
	double Iext(1.01); //1869
	
	//We should have spikes at 92.4 ms, 186.8 ms, 281.8 ms, 375,6. ms ...etc
	neuron.updateTest(924, Iext);	//No spike for the moment
	EXPECT_EQ(0, neuron.getNbrSpikes());
	neuron.updateTest(1, Iext);
	EXPECT_EQ(1, neuron.getNbrSpikes());	//The first spike of the neuron should occur at 92,4 ms
	EXPECT_EQ(0.0, neuron.getPotential());	//After the first spike and during the refractory time, the membrane potential must be 0.0 mV
	
	
	neuron.updateTest(943, Iext);	
	EXPECT_EQ(1, neuron.getNbrSpikes());	//No second spike yet
	neuron.updateTest(1, Iext);
	EXPECT_EQ(2, neuron.getNbrSpikes());	//The second spike should have occured
	
	neuron.updateTest(943, Iext);
	EXPECT_EQ(2, neuron.getNbrSpikes());	//No third spike yet
	neuron.updateTest(1, Iext);
	EXPECT_EQ(3, neuron.getNbrSpikes());	//The third spike should have occured
	
	neuron.updateTest(943, Iext);
	EXPECT_EQ(3, neuron.getNbrSpikes());	//No fourth spike yet
	neuron.updateTest(1, Iext);
	EXPECT_EQ(4, neuron.getNbrSpikes());	//The fourth spike should have occured

} 


TEST (NeuronTest, PositiveInput) {
	
	Neuron neuron(true);
	double Iext(1.0);
	
	//First update test
	neuron.updateTest(1, Iext);
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0)), neuron.getPotential());
	
	//Test after a lot of updates
	neuron.updateTest(10000, Iext);
	EXPECT_EQ(0, neuron.getNbrSpikes());	//The neuron should never spike
	EXPECT_GT(1E-3, (19.999-neuron.getPotential())); //The membrane potential of the neuron should tend to 20 mV without reach it
	
	//After a lot of updates, without input current
	neuron.updateTest(3000, 0.0);
	EXPECT_NEAR(0, neuron.getPotential(), 1e-3);	//The membrane potential should tend to 0.0 mV
}


TEST (NeuronTest, Delay) {

	Neuron neuron(false);
	
	//The neuron will receive an excitatory signal of weight JE in its buffer at time 10 + delays_steps
	neuron.receiveSpike(10+(delay_steps), JE);
	
	//The neuron buffer should have been incremented by +1 at the corresponding time
	EXPECT_EQ(1, neuron.getIncomingSpikes()[25%(delay_steps+1)]);
	
}


TEST (NeuronTest, SpikeWithTwoNeurons) {
	
	Neuron neuron1(true);	//Supposing that neuron1 is excitatory
	Neuron neuron2(false);
	
	size_t time_tot(925+delay_steps);
	
	for(size_t i(0); i<time_tot; ++i) {
		
		if(neuron1.updateTest(1, 1.01)) {	//If a spikes of the neuron1 occurs a time step i+1
			neuron2.receiveSpike(i+delay_steps, JE);		//The neuron2 receives the corresponding signal in its buffer
			EXPECT_EQ(0.0, neuron1.getPotential());		//The membrane potential of the neuron1 after a spikes must be 0.0
		}
		neuron2.updateTest(1, 0.0);	
	}
	
	EXPECT_EQ(0.1, neuron2.getPotential());		//At time 925+delay_steps, the membrane potential of the neuron2 should be 0.1

}	
	

TEST (NetworkTest, NbrExcitatory) {
	
	//Creation of a network with 72 excitatory neurons and 4 inhibitory neurons
	Network network1(72,4,2,5);
	
	unsigned int long nbr_excitatory(0);
	size_t nbr_tot(76);
	
	//Iteration on each neuron of the network
	for(size_t i(0); i<72+4; ++i) {
		if(network1.getNeurons()[i].isExcitatory()) {
			++nbr_excitatory;
		}
	}
	
	//We should have 72 excitatory neurons
	EXPECT_EQ(72, nbr_excitatory);
	
	
	//With more neurons...
	//Creation of a network with 100 excitatory neurons and 25 inhibitory neurons
	Network network2(100,25,2,5);
	
	nbr_excitatory=0;
	nbr_tot=125;
	
	//Iteration on each neuron of the network
	for(size_t i(0); i<nbr_tot; ++i) {
		if(network2.getNeurons()[i].isExcitatory()) {
			++nbr_excitatory;
		}
	}
	
	//We should have 100 excitatory neurons
	EXPECT_EQ(100, nbr_excitatory);
	
}

TEST (NetworkTest, NbrInhibitory) {
	
	//Creation of a network with 72 excitatory neurons and 4 inhibitory neurons
	Network network1(72,4,2,5);
	
	unsigned int long nbr_inhibitory(0);
	size_t nbr_tot(76);
	
	//Iteration on each neuron of the network
	for(size_t i(0); i<nbr_tot; ++i) {
		if(!(network1.getNeurons()[i].isExcitatory())) {
			++nbr_inhibitory;
		}
	}
	
	//We should have 72 excitatory neurons
	EXPECT_EQ(4, nbr_inhibitory);
	
	
	//With more neurons...
	//Creation of a network with 100 excitatory neurons and 25 inhibitory neurons
	Network network2(100,25,2,5);
	
	nbr_inhibitory=0;
	nbr_tot=125;
	
	//Iteration on each neuron of the network
	for(size_t i(0); i<nbr_tot; ++i) {
		if(!(network2.getNeurons()[i].isExcitatory())) {
			++nbr_inhibitory;
		}
	}
	
	//We should have 100 excitatory neurons
	EXPECT_EQ(25, nbr_inhibitory);
	
}

TEST (NetworkTest, ExcitatoryConnections) {
	
	//Creation of a network with 10000 excitatory neurons and 2500 inhibitory neurons
	Network network(10000,2500,2,5);
	
	/*
	 * For a random neuron of the network, we will verify 
		that its has CE excitatory connections
	*/
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<>d(0, 10000+2500);
	unsigned int long neuronNumber=d(gen);
	
	//The neuron 'neuronNumber' should have CE excitatory connections
	EXPECT_EQ(CE, network.ExcitatoryConnectionsTest(neuronNumber));		
	
}

TEST (NetworkTest, InhibitoryConnections) {
	
	//Creation of a network with 10000 excitatory neurons and 2500 inhibitory neurons
	Network network(10000,2500,2,5);
	
	/*
	 * For a random neuron of the network, we will verify 
		that its has CI inhibitory connections
	*/
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<>d(0, 10000+2500);
	unsigned int long neuronNumber=d(gen);
	
	//The neuron 'neuronNumber' should have CI inhibitory connections
	EXPECT_EQ(CI, network.InhibitoryConnectionsTest(neuronNumber));
	
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
} 
