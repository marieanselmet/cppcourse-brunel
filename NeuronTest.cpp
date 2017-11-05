#include <iostream>
#include "neuron.hpp"
#include "gtest/gtest.h"

TEST (NeuronTest, SpikeTimes) {
	
	Neuron neuron;
	double Iext(1.01);
	
	
	neuron.update(924, Iext);
	EXPECT_EQ(0, neuron.getNbrSpikes());
	
	neuron.update(1, Iext);
	EXPECT_EQ(1, neuron.getNbrSpikes());
	EXPECT_EQ(0.0, neuron.getPotential());
	
	
	neuron.update(943, Iext);
	EXPECT_EQ(1, neuron.getNbrSpikes());
	neuron.update(1, Iext);
	EXPECT_EQ(2, neuron.getNbrSpikes());



}

TEST (NeuronTest, PositiveInput) {
	Neuron neuron;
	double Iext(1.0);
	
	///First update test
	neuron.update(1, Iext);
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0)), neuron.getPotential());
	
	///Test after a lot of updates
	neuron.update(10000, Iext);
	EXPECT_EQ(0, neuron.getNbrSpikes());
	EXPECT_GT(1E-3, (19.999-neuron.getPotential())); 
	
}
	

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
