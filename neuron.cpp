#include "neuron.h"
#include <iostream>
#include <math.h>

neuron::neuron(int lId, int nIdL,typeActivation activationFunction)
{
    this->activation = activationFunction;
    layerID = lId;
    neuronIdLayer = nIdL;
}

void neuron::setInputs(std::vector<float> newInputs)
{
    if(weights.size() == newInputs.size())
    {
        inputs = newInputs;
    }
    else
    {
        std::cout << "Error newInputs is not at the size than weights"<< std::endl;
    }

}

float neuron::getWeightWithIndex(int index)
{
    return weights[index];
}

std::vector<float> neuron::getInputs() const
{
    return inputs;
}

typeActivation neuron::getActivation() const
{
    return activation;
}

float neuron::sigmoid(float x)
{
    return 1/(1+exp(-x));
}

float neuron::relu(float x)
{
    return x > 0 ? x : 0;
}

void neuron::emptyInputsOutput()
{
    inputs.clear();
    output = 0;

}

void neuron::learn(float learningRate)
{
    for(int i = 0 ; i<(int)weights.size();i++)
    {
        weights[i] = weights[i] -  learningRate * delta;
    }
    bias -= learningRate * delta;
}

float neuron::preActivation()
{
    float sum = 0;
   for(int i = 0; i < (int)inputs.size() ; i++)
   {
       sum += weights[i] * inputs[i];
   }
   return sum+bias;
}
float neuron::propagate()
{
    if(activation == SIGMOID)
    {
        output = sigmoid(preActivation());
    }
    else if(activation == RELU)
    {
        output = relu(preActivation());
    }

    return output;
}

void neuron::defineWeight(int numberInput)
{
    weights.clear();
    for(int i = 0 ; i < numberInput; i++)
    {

        weights.push_back( (float)(( std::rand()%2 )*2-1)/2 );
    }
}


