#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include "Network.h"

// Format checker just assumes you have Alarm.bif and Solved_Alarm.bif (your file) in current directory
using namespace std;

float random();
Network Alarm;
vector<vector<string>> data;
vector<int> missingElement;
vector<vector<float>> dataProb;
       
int main()
{
    //Data data;
	Alarm = read_network();
       
    string line;
    string val;
    ifstream myfile("records.dat");
    vector<string> values;

    if(myfile.is_open())
    {
        //DataEntry* ptr = root;

        while(!myfile.eof())
        {
            stringstream ss;
            getline(myfile, line);
            ss.str(line);

            float a[rowSize];
            values.clear();
            int missingElementPst = -1;

            for(int i =0; i<rowSize; i++)
            {
                ss >> val;
                int size = val.size();
                values.push_back(val.substr(1, size-1));
                
                if(val.compare("?")==0)
                    missingElementPst = i;
            }

            data.push_back(values);
            missingElement.push_back(missingElementPst);
            dataProb.push_back(vector<float> v);
        }
    }
    else
    {
        cout << "Unable to open "records.dat"\n";
        return 0;
    }


// Example: to do something
	cout<<"Perfect! Hurrah! \n";
	
}

void assignRandomCFTs()
{
    int size = Alarm.netSize();
    for(int i =0; i < size; i++)
    {
        list<Graph_Node>::iterator ptr = Alarm.get_nth_node(i);
        int CPTsize = *ptr.get_CPT().size();
        int valuesCount = *ptr.get_values().size();
        int parentsValues = CPTsize/valuesCount;

        vector<float> CPTupdate(CPTsize);
        //float sum = 0.0;

        for(int j =0; j < parentsValues; j++)
        {
            vector<float> temp = randomList(valuesCount);
            for(int k = 0; k < valuesCount; k++)
            {
                CPTupdate[j*valuesCount + k] = temp[k];
            }
        }

        *ptr.set_CPT(CPTupdate);
    }
}

void assignCFTFromData()
{
    int size = Alarm.netSize();
    for(int i =0; i < size; i++)
    {
        list<Graph_Node>::iterator ptr = Alarm.get_nth_node(i);
        int CPTsize = *ptr.get_CPT().size();
        int valuesCount = *ptr.get_values().size();
        int parentsValues = CPTsize/valuesCount;

        vector<float> CPTupdate(CPTsize);
        //float sum = 0.0;

        for(int j =0; j < parentsValues; j++)
        {
            vector<float> temp = randomList(valuesCount);
            for(int k = 0; k < valuesCount; k++)
            {
                CPTupdate[j*valuesCount + k] = temp[k];
            }
        }

        *ptr.set_CPT(CPTupdate);
    }
}

float randomFloat()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,1000000); // distribution in range [1, 6]

    return (float)dist6(rng)/(float) 1000000 ;
}

vector<float> randomList (int n)
{
    vector<float> arr(n);
    float sum = 0;

    for(int i =0; i<(n-1); i++)
    {
        arr[i] = randomFloat();
        sum += arr[i];
    }

    if(sum <= 1)
    {
        arr[n-1] = 1 - sum;
        return arr;
    }

    float factor = (float)((int)sum + 1);
    sum = 0;

    for(int i =0; i<(n-1); i++)
    {
        arr[i] = arr[i]/factor;
        sum += arr[i];
    }

    arr[n-1] = 1 - sum;
    return arr;
}