main:
	g++ test/main.cpp brainz/brainz.cpp brainz/Neuron.cpp -o test/main && cd test && ./main && cd ../