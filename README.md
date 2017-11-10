# cppcourse-brunel

This program simulates a neuron network and is based on the Nicolas Brunel’s paper entitled “Dynamics of sparsely connected networks of excitatory and inhibitory spiking neurons”.



A. Description :

This program simulates a network composed of 12500 interconnected neurons. 
Among the 12500 neurons of the network, 80% (ie NE=10000) are excitatory and 20% (ie NI=2500) are inhibitory. 
The excitatory ones transmit a positive amplitude to their connections when they spike and consequently increase the membrane potential of their post-synaptic connections.
Unlike the excitatory neurons, the inhibitory ones transmit a negative amplitude to their connections when they spike and thus decrease the membrane potential of their post-synaptic connections.
All neurons receive a connection from 10% of the total network. 
More exactly, each of them receives randomly (uniform integer distribution) CE=1000 excitatory connections and CI=250 inhibitory connections.
In addition, each of them receives randomly 1000 connections from outside the network (poisson distribution).



B. Parameters of the simulation :

The simulation depends on :

-g = JI/JE : JI is the weight of the inhibitory connections and JE is the weight of the excitatory connections for the post-synaptic neurons

-eta = nu_ext/nu_thr : nu_ext is the rate of firing from the neurons outside the network and nu_thr is the rate needed to reach threshold in absence of feedback



C. Compilation :

To compile the project, it is necessary to be in the “build” folder.

In the right folder, on the terminal :

cmake ..
make



D. Execution :

To execute the program after its compilation, on the terminal :   ./Neurons
To execute the tests after the compilation of the program, on the terminal :   ./UnitTests



E. Utilisation :

At the execution of Neurons, the program will ask you for a positive simulation time in ms, and for strictly positive values for g and eta.
In order to recreating the Fig.8 of the Brunel’s paper, you can choose :

A : g=3 and eta=2

B : g=6 and eta=4

C: g=5 and eta=2

D: g=4.5 and eta=0.9



Note that in the file named “constants.hpp” and located in the “src” folder, it is possible to modify other parameters for the simulation, like the refractory time, the time delay,…

The documentation of the program is disponible in the file named "files.html" located in "html" in the "build" folder.



F. Results :

The spike times of all neurons of the network and their identification number are stored in a file named “spikes.txt” and located in the “build” folder.
You can use it to create a graph of the simulation on the website : https://cs116-plot.antoinealb.net/



Marie Anselmet
SCIPER : 271430
Projects for SV 2017
