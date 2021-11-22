#ifndef NEURON_H
#define NEURON_H
#include <vector>

enum typeActivation { SIGMOID, RELU };

class neuron
{

public:
    int layerID;
    int neuronIdLayer;
    float output;
    void setInputs(std::vector<float> newInputs);
    void learn(float learningRate);    // use delta and weights
    float propagate(); // get result
    void defineWeight(int numInputs);
    void emptyInputsOutput();
    neuron(int layerID,int layerId,typeActivation activationFunction);
    float getWeightWithIndex(int index);
    float delta=0;
    std::vector<float> getInputs() const;

    typeActivation getActivation() const;

private:
    float bias = 1;
    typeActivation activation;
    std::vector<float> inputs;
    std::vector<float> weights;
    float sigmoid(float x);
    float relu(float x);
    float preActivation();
};

#endif // NEURON_H
