#ifndef OTHER_FILE_H
#define OTHER_FILE_H

#include<iostream>
#include<time.h>
#include<vector>
#include<string>
#include<math.h>
#include<algorithm>
#include<cassert>
#include <string>

using namespace std;
/**
 * CONFIGURABLE ARTIFICIAL NEURAL NETWORK IN C++
 * *********************************************
 * -----------Configurable Parameters-----------
 * 1.   Number of Layers
 * 2.   Number of neurons in each Layer
 * 3.   Activation Function for each Layer (ReLU, Sigmoid, TanH, Softmax)
 * 4.   Network Architecture (Fully Connected / Partially Connected)
 * 5.   L2 Regularization Strength to Avoid Overfitting
**/

vector<float> multiply(vector<float>mat1,vector<vector<float>>mat2)
{
    /**Returns a row vector as product of the first parameter i.e a row vector and the second parameter i.e. matrix**/
    vector<float>res;
    for(unsigned int i=0;i<mat2[0].size();i++)
    {   
        float sum=0;
        for(unsigned int j=0;j<mat1.size();j++)
        {
            sum=sum+(mat1[j]*mat2[j][i]);
        }
        res.push_back(sum);
    }
    return res;
}

vector<float>  multiply2(vector<vector<float> > x, vector<float> y)
{
    /**
        Returns a vector with n elements which is actually a column vector of dimensions n*1 
        obtained by multiplying the first parameter i.e. a matrix of dimension n*m and second parameter i.e. a column vector of dimensions m*1.
    **/
    vector<float> ans;
    for(unsigned int i=0;i<x.size();i++)
     {
       float sum=0;
       for(unsigned int j=0;j<x[i].size();j++)
        {
            sum=sum+(x[i][j]*y[j]);
        }
        ans.push_back(sum);
     }
   return ans; 
}

vector<vector<float>> multiply3(vector<float> x, vector<float> y)
{   
    /**Returns a product matrix taking first vector as column vector and second vector as row vector.**/
    vector<vector<float>> ans;
    for(unsigned int i=0;i<x.size();i++)
    {   vector<float> temp;
        for(unsigned int j=0;j<y.size();j++)
        {
            temp.push_back(x[i]*y[j]);       
        }
        ans.push_back(temp);
    }
    return ans;
}

vector<float> addTwoVectors(vector<float>u,vector<float>v)
{
    /**Returns a sum vector of given two vectors u and v**/
    vector<float> res;
    int n = u.size();
    for(int i=0;i<n;i++)
    {
        res.push_back(u[i]+v[i]);
    }
    return res;
}

vector<vector<float>> generate_random_matrix(int x,int y)
{
    /**Returns a matrix of dimensions x and y and assigns random values between 0 and 1 to every element of the matrix.**/
    vector<vector<float>>temp;
    srand( (unsigned)time( NULL ) );
    for(int i=0;i<x;i++)
    {
        vector<float>temp1;
        for(int j=0;j<y;j++)
        {
            temp1.push_back(((float) rand() / (RAND_MAX)));
        }
        temp.push_back(temp1);
    }
    // for(int i=0;i<x;i++)
    // {
    //     for(int j=0;j<y;j++)
    //     {
    //         cout<<temp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    return temp;
}

vector<float> generate_random_array(int x)
{
    /**Returns a vector of length x and assigns random value between 0 and 1 to every element of the vector.**/
    srand( (unsigned)time( NULL ) );
    vector<float>temp1;
    for(int j=0;j<x;j++)
    {
        temp1.push_back(((float) rand() / (RAND_MAX)));
    }
    return temp1;
}
class NeuralNetwork{
    /** 
    Functions:
        softmax
        activate
        activate_derivative
        feed_forward
        backpropagate
        train
    Data Members:
        numoflayers: Number of layers in the network
        inputSize: Number of inputs expected
        outputSize: Number of possible classifications
        layerSizes: List containing number of neurons in every layer.
        layerWeights: List of matrices representing weights between layers
        layerBias: List of vectors representing bias before activation
        activationFunction: List of activation functions at each layer
        trainingMethod: string containing gradient descent approach
        learningRate: float representing learning rate in training
        L2regularizationStrength: float representing L2 regularization strength(lambda)
    **/
    private:
        vector<int>layerSizes;
        int inputSize;
        int outputSize;
        int numoflayers;
        float learningRate;
        float L2regularizationStrength;
        vector<string>activationFunction;
        vector<vector<vector<float>>>layerWeights;
        vector<vector<float>>layerBias;
        string trainingMethod;

    public:
        NeuralNetwork(vector<int>layerSizes1,float learningRate1,vector<string>activationFunction1,string trainingMethod1,float L2regularizationStrength1,bool drop_neurons)
        {
            /**
            Constructor
            Initializes NeuralNetwork object.
            Defines all the pertinent instance variables required to construct and
            manipulate a NeuralNetwork object.
            Parameters:
                layerSizes1: A list of ints representing the size of each layer.
                learningRate1: A float that defines the rate of gradient descent.
                activationFunction1: An optional string that defines the activation function used in each hidden layer.
                trainingMethod1: An optional string defining approach to gradient descent.
                L2regularizationStrength1: A float that defines the strength for L2 regularization
            **/
            numoflayers=layerSizes1.size();
            if(numoflayers!=0)
            {
                inputSize=layerSizes1[0];
                outputSize=layerSizes1[numoflayers-1];
            }
            for(int i=0;i<numoflayers;i++)
            {
                layerSizes.push_back(layerSizes1[i]);
                activationFunction.push_back(activationFunction1[i]);
            }
            for(int i=0;i<numoflayers-1;i++)
            {
                layerWeights.push_back(generate_random_matrix(layerSizes[i],layerSizes[i+1]));
                layerBias.push_back(generate_random_array(layerSizes[i+1]));
            }
            trainingMethod=trainingMethod1;
            learningRate=learningRate1;
            L2regularizationStrength=L2regularizationStrength1;
            if(drop_neurons==true)
            {
                for(int i=0;i<numoflayers-1;i++)
                {
                    for(int j=0;j<layerSizes[i+1];j++)
                    {
                        int x;
                        cout<<"Enter the number of neuron connections you want to drop from neurons in Layer "<<i+1<<"to neuron number "<<j+1<<" of Layer "<<i+2<<"\t=>";
                        cin>>x;
                        vector<int>temp;
                        for(int k=0;k<x;k++)
                        {
                            int y;
                            cout<<"Note: Enter values from 1 to "<<layerSizes[i]<<" as Layer "<<i+1<<"contains"<<layerSizes[i]<<"total neurons \n";
                            cout<<"Enter the neuron number of neurons in Layer "<<i+1<<" whose connection you want to break with neuron number "<<j+1<<" of Layer "<<i+2<<"\t=>";
                            cin>>y;
                            layerWeights[i][y-1][j] = 0.0;
                        }
                    }
                }
                // for(int i=0;i<numoflayers-1;i++)
                // {
                //     for(int j=0;j<layerWeights[i].size();j++)
                //     {
                //         for(int k=0;k<layerWeights[i][j].size();k++)
                //         {
                //             cout<<layerWeights[i][j][k]<<" ";
                //         }
                //         cout<<endl;
                //     }
                // }
            }
        }

        vector<float> softmax(vector<float>array)
        {
            /**
            Performs softmax on each value of a given array.
            A normalizing function that makes each value in array add to 1. Useful
            in classification for determining probability of each class. Used in
            the activate function when called on an array. Normally called on the
            last layer of the network.
            Parameters:
                array: An array to be used in the softmax function. Normally represents the output layer of a network.
            Returns:
            Softmax of array
            **/
            vector<float> temp;
            int n=array.size();
            float maxim=array[0];
            for(int i=1;i<n;i++)
            {
                if(array[i]>maxim)
                    maxim = array[i];
            }
            for(int i=0;i<n;i++)
            {
                temp.push_back(exp(array[i]-maxim));
            }
            float sum=0;
            for(int i=0;i<n;i++)
            {
                sum+=temp[i];
            }
            for(int i=0;i<n;i++)
            {
                temp[i]=temp[i]/sum;
            }
            return temp;
        }

        vector<float> activate(vector<float> value,string activationFunction)
        {
            /**
            Modifies a value using the given activation function
            Activates the value, provided as either an array or single input, using
            the user-inputted activation function.
            This activate function is then called in feed_forward and backpropagate.
            Parameters:
                value: Either an array or single float value representing value to be activated.
                activationFunction: A string representing the user-inputted function to be used on the given value.
            Returns:
            Activated value
            **/
            vector<float>res;
            if(activationFunction=="ReLU")
            {
                for(unsigned int i=0;i<value.size();i++)
                {
                    if(value[i]>0)
                        res.push_back(value[i]);
                    else
                        res.push_back(0);
                }
                return res;
            }
            else if(activationFunction=="Sigmoid")
            {
                for(unsigned int i=0;i<value.size();i++)
                {
                        res.push_back(1.0/(1.0 + exp(-1*value[i])));
                }
                return res;
            }
            else if(activationFunction=="TanH")
            {
                for(unsigned int i=0;i<value.size();i++)
                {
                    res.push_back(tanh(value[i]));
                }
                return res;
            }
            else if(activationFunction=="Softmax")
            {
                res = softmax(value); 
                return res;
            }
        }

        vector<float>activate_derivative(vector<float>value,string activationFunction)
        {
            /**
            Derivative of the activation function.
            Used in the backpropagate function to calculate error at each layer.
            Parameters:
                value: An array representing the values to be activated.
                activationFunction: A string representing the user-inputted function whose derivative is to be used on the given value.
            Returns:
                Vector containg Derivative of activated value vector.
            **/
            vector<float>res;
            int n=value.size();
            if(activationFunction=="Sigmoid")
            {
                res=activate(value,"Sigmoid");
                for(int i=0;i<n;i++)
                {
                    res[i]=res[i]*(1-res[i]);
                }
                return res;
            }
            else if(activationFunction=="ReLU")
            {
                for(int i=0;i<n;i++)
                {
                    if(value[i]>0)
                        res.push_back(1);
                    else
                        res.push_back(0);
                }
                return res;
            }
            else if(activationFunction=="TanH")
            {
                res=activate(value,"TanH");
                for(int i=0;i<n;i++)
                {
                    res[i] = 1.0 - res[i]*res[i];
                }
                return res;
            }
        }

        pair<vector<float>,vector<vector<float>>> feed_forward(vector<float>input,bool trainFlag = false)
        {
            /**
            Sends input through each layer of the network.
            Yields the set of outputs computed by a forward-pass through the neural
            network. Defines weighted inputs to be used in training if TrainFlag is
            turned on.
            Parameters:
                input: A list of ints representing the size of each layer.
                trainFlag: An optional boolean that determines if forward-pass is being used for training purposes.
            Returns:
                A pair containing the output values vector and weightedInputs matrix.
            **/
            int n=input.size();
            vector<vector<float>>weightedInputs;
            if(trainFlag)
            {
                vector<float>temp;
                for(int i=0;i<n;i++)
                {
                    temp.push_back(input[i]);
                }
                weightedInputs.push_back(temp);
            }
            assert( (int) input.size()==inputSize);

            vector<float>values = activate(input,activationFunction[0]);

            for(unsigned int weightIndex=0;weightIndex<layerWeights.size();weightIndex++)
            {
                vector<float>afterMatMul = multiply(values,layerWeights[weightIndex]);
                vector<float>afterBiasAddition = addTwoVectors(afterMatMul,layerBias[weightIndex]);
                if(trainFlag)
                {
                    vector<float>temp1;
                    for(unsigned int i=0;i<afterBiasAddition.size();i++)
                    {
                        temp1.push_back(afterBiasAddition[i]);
                    }
                    weightedInputs.push_back(temp1);
                }
                vector<float>afterActivation = activate(afterBiasAddition,activationFunction[weightIndex+1]);
                values = afterActivation;
            }
            pair<vector<float>,vector<vector<float>>>p;
            if(!trainFlag)
            {
                p.first=values;
                return p;
            }
            else
            {
                p.first=values;
                p.second=weightedInputs;
                return p;
            }    
        }

        vector<vector<float>> backpropagate(vector<float> actualOutput,vector<float> desiredOutput, vector<vector<float>> weightedInputs)
        {
            /**
            Performs a single iteration of backpropagation by calculating the
            error in each layer.
            Yields the set of errors in each layer based on an experimental output
            and desired output. These errors are then used to modify the weights
            and biases of the network according to the desired gradient descent
            method.
            Parameters:
                actualOutput: An array containing the values from a forward pass
                desiredOutput: An array containing the expected/desired values based on the corresponding input values
                weightedInputs: A list of arrays representing the value at each layer calculated during forward propagation before activation.
                    Passed as a parameter for the sake of convenience so the values don't have to be calculated multiple times.
            Returns:
                A list of arrays representing the error in each layer
            **/
            vector<vector<float>> errorValues;
            vector<float>err;
            int n=actualOutput.size();
            int w=weightedInputs.size();
            assert(w==numoflayers);
            for(int i=0;i<n;i++)
            {
                err.push_back(actualOutput[i]-desiredOutput[i]);
            }
            if(activationFunction[numoflayers-1] != "Softmax")
            {
                vector<float>backprop_derivative;
                backprop_derivative=activate_derivative(weightedInputs[w-1],activationFunction[w-1]);
                for(int i=0;i<n;i++)
                {
                    err[i] = err[i] * backprop_derivative[i];
                }
            }
            errorValues.push_back(err);
            for(int index=w-2;index>0;index--)
            {
                int errorValuesSize=errorValues.size();
                vector<float>backprop_derivative;
                vector<float>err_iter;
                if(errorValuesSize>0)
                {
                    vector<float>temp = multiply2(layerWeights[index],errorValues[errorValuesSize-1]);
                    backprop_derivative = activate_derivative(weightedInputs[index],activationFunction[index]);
                    int f=temp.size();
                    for(int i=0;i<f;i++)
                    {
                        err_iter.push_back(temp[i]*backprop_derivative[i]);
                    }
                    errorValues.push_back(err_iter);
                }
            }
            reverse(errorValues.begin(),errorValues.end());
            return errorValues;
        }

        void train(vector<vector<float>>inputs,vector<vector<float>>outputs,int epochs,bool L2regularizationFlag)
        {
            /**
            Trains network using supervised learning method approach.
            Yields a set of updated weights and biases that have improved accuracy
            in feed-forward inference.
            Parameters:
                inputs: A list of arrays representing each input data point. Input must be the same size as the first layer.
                outputs: A list of arrays representing each output data point. Each output array must have the same size as the number of classes.
                epochs: Optional integer that determines number of gradient descent iterations.
            Returns:
                None
            **/
            // cout<<"Starting training...\n\n";
            assert(inputs.size()==outputs.size());
            if(trainingMethod=="batchGradientDescent")
            {
                for(int iterations=0;iterations<epochs;iterations++)
                {
                    // cout<<"============ STARTING EPOCH"<<iterations<<"==========\n";
                    vector<vector<vector<float>>> weightUpdates;
                    vector<vector<float>> biasUpdates;
                    int inputlen=inputs.size();
                    for(int indexValue=0;indexValue<inputlen;indexValue++)
                    {
                        // cout<<"Input"<<indexValue<<" | Epoch "<<iterations<<"\n";
                        vector<float>input = inputs[indexValue];
                        pair<vector<float>,vector<vector<float>>>p = feed_forward(input,true);
                        vector<float>actualOutput = p.first;
                        vector<vector<float>>weightedInputs = p.second;
                        
                        vector<float>desiredOutput = outputs[indexValue];

                        vector<vector<float>>errorValues = backpropagate(actualOutput,desiredOutput,weightedInputs);

                        if(weightUpdates.size()==0 && biasUpdates.size()==0)
                        {
                            vector<float>errorInput;
                            vector<vector<float>>weightValue;
                            for(unsigned int index=0;index<errorValues.size();index++)
                            {
                                errorInput = errorValues[index]; 
                                weightValue = multiply3(weightedInputs[index],errorInput);
                                weightUpdates.push_back(weightValue);
                                biasUpdates.push_back(errorValues[index]);
                            }
                        }
                        else
                        {
                            vector<float>errorInput;
                            vector<vector<float>>weightValue;
                            for(unsigned int index=0;index<errorValues.size();index++)
                            {
                                errorInput = errorValues[index];
                                weightValue = multiply3(weightedInputs[index],errorInput);
                                for(unsigned int j=0;j<weightUpdates[index].size();j++)
                                {
                                    for(unsigned int k=0;k<weightUpdates[index][j].size();k++)
                                    {
                                        weightUpdates[index][j][k] = weightUpdates[index][j][k] + weightValue[j][k];
                                    }
                                }
                                for(unsigned int j=0;j<biasUpdates[index].size();j++)
                                {
                                    biasUpdates[index][j] = biasUpdates[index][j] + errorValues[index][j];
                                }
                            }
                        }  
                    }
                    for(unsigned int arrIndex=0;arrIndex<weightUpdates.size();arrIndex++)
                    {
                        
                        for(unsigned int j=0;j<weightUpdates[arrIndex].size();j++)
                        {
                            for(unsigned int k=0;k<weightUpdates[arrIndex][j].size();k++)
                            {
                                weightUpdates[arrIndex][j][k] = weightUpdates[arrIndex][j][k] / inputlen;
                            }
                        }
                        
                        for(unsigned int j=0;j<weightUpdates[arrIndex].size();j++)
                        {
                            for(unsigned int k=0;k<weightUpdates[arrIndex][j].size();k++)
                            {
                                weightUpdates[arrIndex][j][k] = weightUpdates[arrIndex][j][k] * learningRate ;
                            }
                        }
                        if(L2regularizationFlag == true)
                        {
                            for(unsigned int j=0;j<weightUpdates[arrIndex].size();j++)
                            {
                                for(unsigned int k=0;k<weightUpdates[arrIndex][j].size();k++)
                                {
                                    weightUpdates[arrIndex][j][k] = weightUpdates[arrIndex][j][k] + (L2regularizationStrength * layerWeights[arrIndex][j][k]);
                                }
                            }
                        }
                        assert(weightUpdates.size()==layerWeights.size());
                        assert(weightUpdates[arrIndex].size()==layerWeights[arrIndex].size());
                        assert(weightUpdates[arrIndex][2].size()==layerWeights[arrIndex][2].size());
                        for(unsigned int j=0;j<weightUpdates[arrIndex].size();j++)
                        {
                            for(unsigned int k=0;k<weightUpdates[arrIndex][j].size();k++)
                            {
                                layerWeights[arrIndex][j][k] = layerWeights[arrIndex][j][k] - weightUpdates[arrIndex][j][k];
                            }
                        }
                        
                    }
                    
                    for(unsigned int biasIndex=0;biasIndex<biasUpdates.size();biasIndex++)
                    {
                        for(unsigned int j=0;j<biasUpdates[biasIndex].size();j++)
                        {
                            biasUpdates[biasIndex][j] = biasUpdates[biasIndex][j]/inputlen;
                        }
                        for(unsigned int j=0;j<biasUpdates[biasIndex].size();j++)
                        {
                            biasUpdates[biasIndex][j] = biasUpdates[biasIndex][j]*learningRate;
                        }
                        for(unsigned int j=0;j<biasUpdates[biasIndex].size();j++)
                        {
                            layerBias[biasIndex][j] = layerBias[biasIndex][j] - biasUpdates[biasIndex][j];
                        }
                    }
                    // cout<<"EPOCH "<<iterations<<" ENDED\n";
                }
            }
            // cout<<"Completed Training...\n";
        }
};

double helper(double alpha, int nEpochs)
{
    float learningRate = alpha;
    float L2regularizationStrength = 0.01; 
    bool L2regularizationFlag = false;
    bool drop_neurons = false;
    string trainingMethod = "batchGradientDescent";

    vector<int>layerSizes;
    layerSizes.push_back(64);
    layerSizes.push_back(50);
    layerSizes.push_back(10);

    vector<string>activations;
    activations.push_back("ReLU");
    activations.push_back("ReLU");
    activations.push_back("Softmax");

    char regularization_flag = 'N';
    int net_arch = 1; // fully connected network

    NeuralNetwork* net = new NeuralNetwork(layerSizes,learningRate,activations,trainingMethod,L2regularizationStrength,drop_neurons);
    /**
     * DATASET :
     *      Optdigits Dataset - 32x32 bitmaps of handwritten digits were divided into nonoverlapping blocks of 4x4 and 
     *      the number of on pixels are counted in each block. This generates an input matrix of 8x8 where each element 
     *      is an integer in the range 0..16.All these 8*8=64 matrix elements are the feature of our dataset.
     *      
     *      Ref: https://archive.ics.uci.edu/ml/datasets/optical+recognition+of+handwritten+digits
     * 
     *      Number of Instances: 5620
     *      Dataset Characteristics: Multivariate
     *      Attribute Characteristics: Integer
     *      Missing Values: No
     * 
     * train_inputs:
     *      Resource File: train_features.txt
     *      Number of rows: Number of training samples = 3823.
     *      Number of columns: Number of features = 64.
     * 
     * test_inputs:
     *      Resource File: test_features.txt
     *      Number of rows: Number of training samples = 1797.
     *      Number of columns: Number of features = 64.
     * 
     * train_outputs:
     *      Resource File: train_classes.txt
     *      Number of rows: Number of training samples = 1797.
     *      Number of columns: Number of classes = 10.
     *      An entry is 1 if the sample belongs to that class else 0.
     * 
     * train_classes_outputs:
     *      Resource File: train_output.txt
     *      Number of rows: Number of training samples = 3823.
     *      Number of columns = 1 
     *      Class of the training sample.
     * 
     * test_classes_outputs:
     *      Resource File: test_output.txt
     *      Number of rows: Number of training samples = 1797.
     *      Number of columns = 1 
     *      Class of the training sample.
    **/
    vector<vector<float> >train_inputs;
    vector<vector<float> >train_outputs;
    vector<vector<float> >test_inputs;

    vector<int>train_classes_outputs;
    vector<int>test_classes_outputs;

    //Importing Dataset 
    FILE *archivo;
    archivo = fopen("train_features.txt","r");
    for(int i=0;i<3823;i++)
    {   vector<float> temp;
        for(int j=0;j<64;j++)
        { 
            if(j!=63)
            { int x;
              fscanf(archivo,"%d ",&x);
              float p=x;
              temp.push_back(p);
            }
           else
            { int x;
              fscanf(archivo,"%d\n",&x);
              float p=x;
              temp.push_back(p);
            }
         }
         train_inputs.push_back(temp);
    }
    fclose(archivo);

    FILE *archivo1;
    archivo1 = fopen("train_classes.txt","r");
    for(int i=0;i<3823;i++)
    {   vector<float> temp;
        for(int j=0;j<10;j++)
        { 
            if(j!=9)
            { int x;
              fscanf(archivo1,"%d ",&x);
              float p=x;
              temp.push_back(p);
            }
           else
            { int x;
              fscanf(archivo1,"%d\n",&x);
              float p=x;
              temp.push_back(p);
            }
         }
         train_outputs.push_back(temp);
    }
    fclose(archivo1);

    FILE*archivo2;
    archivo2 = fopen("train_output.txt","r");
    for(int i=0;i<3823;i++)
    {
        int x;
        fscanf(archivo2,"%d\n",&x);
        train_classes_outputs.push_back(x);
    }
    fclose(archivo2);

    FILE *archivo3;
    archivo3 = fopen("test_features.txt","r");
    for(int i=0;i<1797;i++)
    {   vector<float> temp;
        for(int j=0;j<64;j++)
        { 
            if(j!=63)
            { int x;
              fscanf(archivo3,"%d ",&x);
              float p=x;
              temp.push_back(p);
            }
           else
            { int x;
              fscanf(archivo3,"%d\n",&x);
              float p=x;
              temp.push_back(p);
            }
         }
         test_inputs.push_back(temp);
    }
    fclose(archivo3);

    FILE*archivo4;
    archivo4 = fopen("test_output.txt","r");
    for(int i=0;i<1797;i++)
    {
        int x;
        fscanf(archivo4,"%d\n",&x);
        test_classes_outputs.push_back(x);
    }
    fclose(archivo4);
    
    //Training
    int epochs = nEpochs;
    // cout<<"Enter the number of epochs you want to perform training\t=>";
    // cin>>epochs;
    net->train(train_inputs,train_outputs,epochs,L2regularizationFlag);

    //Testing
    int accurate_counter = 0;
    int total_counter = 0;

    /**
        STORING RESULTS
        Resource File:  predictions.txt
        For all test samples predicted value is printed and compared with the actual value.
    **/
    FILE* archivo5;
    archivo5 = fopen("predictions.txt","w");
    for(unsigned int i=0;i<test_inputs.size();i++)
    {
        vector<float>array;
        array=test_inputs[i];
        pair<vector<float>,vector<vector<float>>> pairoutput = net->feed_forward(array,false); 
        vector<float>output = pairoutput.first;
        
        // cout<<"\n";
        int predictedValue=0;
        float max_output=output[0];
        for(unsigned int j=1;j<output.size();j++)
        {
            if(output[j]>max_output)
            {
                max_output = output[j];
                predictedValue=j;
            }
        }
        // cout<<"Predicted Value:"<<predictedValue<<" \n";
        // fprintf(archivo5,"Predicted Value: %d \n",predictedValue);
        // cout<<"Actual Value:"<<test_classes_outputs[i]<<" \n";
        // fprintf(archivo5,"Actual Value: %d \n",test_classes_outputs[i]);
        if(predictedValue == test_classes_outputs[i])
        {
        //     cout<<"Correct Prediction\n";
        //     fprintf(archivo5,"Correct Prediction!\n");
                accurate_counter = accurate_counter + 1;
        }
        total_counter = total_counter + 1;
        // fprintf(archivo5,"\n");
    }

    //Computing Accuracy
    // cout<<"Accurate counter = "<<accurate_counter<<"\n";
    // fprintf(archivo5,"Accurate count: %d \n",accurate_counter);
    // cout<<"Total counter = "<<total_counter<<"\n";
    // fprintf(archivo5,"Total count: %d \n",total_counter);
    float acc=1.0*accurate_counter;
    float tot=1.0*total_counter;
    // cout<<"Your accuracy is: "<<acc/tot << "\n";
    // fprintf(archivo5,"Your accuracy is %f: \n",acc/tot);
    // fclose(archivo5);

    return acc/tot;
}

#endif
