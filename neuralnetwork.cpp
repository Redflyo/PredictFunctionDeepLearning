#include "neuralnetwork.h"
#include <iostream>
NeuralNetwork::NeuralNetwork(int layers[],int numLayersInNetwork,int numInputByNeuron)
{
    numLayers = numLayersInNetwork;
    typeActivation currentTyp = RELU;
    std::cout << "nb size layers" << numLayers << std::endl;
    for (int currentLayer = 0 ; currentLayer < numLayers ; currentLayer++ )
    {
        for(int n = 0; n < layers[currentLayer] ; n++)
        {
            int numInputs;
            if(currentLayer == 0)
            {
                numInputs = numInputByNeuron;
            }
            else
            {
                numInputs = layers[currentLayer - 1];
            }
            currentTyp = RELU;
            if(currentLayer == numLayers-1)
            {
                //currentTyp = SIGMOID;
            }

            neuron* newNeuron = new neuron(currentLayer,n,currentTyp);
            newNeuron->defineWeight(numInputs); // define number of weight for the neurone

            network.push_back(newNeuron);
        }
    }
}

void NeuralNetwork::deleteNetwork()
{
    while(network.size() != 0)
    {

        delete network[0];
        network.erase(network.begin(),network.begin()+1);

    }
}

void NeuralNetwork::trainNetwork(std::vector<float> errors,float learningRate)
{
    initDelta(errors);
    changeWeights(learningRate);
}
void NeuralNetwork::initDelta(std::vector<float> errors)
{
    bool finnish;
    for(int i = 0;i < (int)errors.size();i++) // delta de la dernière couche
    {
        finnish = false;
        for( auto n = network.end()-1;n != network.begin() && !finnish; --n)
        {
            if((*n)->layerID == numLayers-1 && (*n)->neuronIdLayer == i) // si neurone voulu de la dernière couche
            {
                (*n)->delta = errors[i];
                finnish = true;
            }
        }
    }
    int currentLayer = numLayers - 2 ;
    // calcule gradient des couches cachés
    for(int i = network.size()-1; i> -1 ; i--)
    {
        if(network[i]->layerID == currentLayer)
        {
        // fait la somme des gradients de la couche supérieur
            float sumGradient = 0;
            for(int j = i+1; j < (int)network.size(); j++ )
            {
                if(network[j]->layerID == currentLayer+1)
                {
                   sumGradient+=network[j]->delta * network[j]->getWeightWithIndex(network[i]->neuronIdLayer) ;
                    //sumGradient+=network[j]->delta;
                }
            }
            network[i]->delta =  sumGradient;
        }
    }



}

void NeuralNetwork::changeWeights(float leaningRate)
{
    for(int i = 0; i < (int)network.size(); i++)
    {
        network[i]->learn(leaningRate);
    }
}
std::vector<float> NeuralNetwork::propagation(std::vector<std::vector<float>> inputs)
{
    for(neuron* n : network) // vide les inputs et outputs déjà existant
    {
        n->emptyInputsOutput();
    }

    int cpt = 0 ;
    std::list<float> lastLayer;
    std::list<float> newLayer;

    for(auto it= inputs.begin(); it != inputs.end(); ++it)
    {
        network[cpt]->setInputs(*it);
        network[cpt]->propagate();
        lastLayer.push_back(network[cpt]->output);
        if(network[cpt]->layerID != 0)
        {
            std::cerr << "Erreur propagationNetwork code 1 la valeur est : "
                      << network[cpt]->layerID
                      << std::endl;
        }

        cpt++;
    }
    int layerId = 1;
    while(cpt < (int)network.size())
    {
        if(network[cpt]->layerID != layerId)
        {
            if(layerId > network[cpt]->layerID)
            {
                std::cerr << "Erreur propagation code 2" << std::endl;
            } // try if error where neuron is not order

            layerId = network[cpt]->layerID;
            lastLayer = newLayer;
            newLayer.clear();
        }


        std::vector<float> result;
        for(auto it = lastLayer.begin();it != lastLayer.end();++it)
        {
            result.push_back(*it);
        }
        network[cpt]->setInputs(result);
        newLayer.push_back(network[cpt]->propagate()); // add neuron in the newLayer which be the lastLayer
        cpt++;
    }

    std::vector<float> resultLastLayer; // get output of last layer
    for(auto it = newLayer.begin();it != newLayer.end();++it)
    {
        resultLastLayer.push_back(*it);
    }

    return resultLastLayer;

}


