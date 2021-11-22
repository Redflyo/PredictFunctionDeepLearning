#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include "neuron.h"
#include <list>

class NeuralNetwork
{
public:
    std::vector<neuron*> network;
    NeuralNetwork(int layers[],int numLayersInNetwork,int numInputByNeuron);
    std::vector<float> propagation(std::vector<std::vector<float>> inputs);
    void deleteNetwork();
    void trainNetwork(std::vector<float> error, float learningRate);
private:
    int numLayers;
    void initDelta(std::vector<float> error);
    void changeWeights(float learningRate);
};


#endif // NEURALNETWORK_H
