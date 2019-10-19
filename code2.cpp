#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include <iterator>
#include "Network.h"
#include "Graph_Node.h"

using namespace std;

int main(){
    network Alarm;
    Alarm=read_network();
    vector<pair<vector<string>,float>> data = getData();
    initialize(Alarm,data);
    numIter = 0;
    while(numIter<20){
        Estep(Alarm,data);
        Mstep(Alarm,data);
    }

}
//We are calculating the data given the marginal distribultion
void Estep(Network Alarm,vector<pair<vector<string>,float>> data,int size){
    for(vector<pair<vector<string>,float>>::iterator ptr = data.begin(); ptr != data.end(); ptr++){
        if(ptr->second >= 0)
            continue;

        int varPst = -1; 
        for(int i =0; i< ptr->first.size(); i++){
            if(ptr->first[i].compare("?") == 0){
                varPst = i;
                break;
            }
        }

        list<Graph_Node>::iterator node =  get_nth_node(varPst);
        int nValues = node->nValues();

        for(int i = 0; i< nValues; i++){
            int index = getIndex(node->get_name(), node->get_values()[i], ptr->first, Alarm);
            (ptr+i+1)->second = node->getCPT()[index];
        }
    }
}
//We are calculting the marginal distributions given the data
void Mstep(Network Alarm,vector<pair<vector<string>,float>> data,int size){
    list<Graph_Node> Pres_Graph = Alarm.Pres_Graph;
    list<Graph_Node>::Iterator listIt;
    int index = -1;
    counter = 0;
    for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++){
        string var = listIt->get_name();
        int nvalues = listIt->get_nvalues();
        vector<float> CPT = listIt->getCPT();
        bool missing[CPT.size()]; 
        for(int i=0;i<CPT.size();i++){
            bool missing[i] = false;
            CPT[i]=0;
        } 
        for(int i=0;i<data.size();i++){
            int valVar = (data[i].first)[counter];
            int weight = data[i].second;
            if(valVar!="?"){
                index = getIndex(var,valVar,data[i],Alarm);
                CPT[index] = CPT[index]+weight;
            }
        }
        for(int i=0;i<CPT.size();i++) CPT[i] = CPT[i]/size;
        listIt->setCPT(CPT);
        counter = counter+1;
    }
}

void initialize(Network Alarm,vector<pair<vector<string>,float>> data){
    list<Graph_Node> Pres_Graph = Alarm.Pres_Graph;
    list<Graph_Node>::Iterator listIt;
    int index = -1;
    counter = 0;
    for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++){
        string var = listIt->get_name();
        int nvalues = listIt->get_nvalues();
        vector<float> CPT = listIt->getCPT();
        bool missing[CPT.size()]; 
        for(int i=0;i<CPT.size();i++){
            bool missing[i] = false;
            CPT[i]=0;
        } 
        for(int i=0;i<data.size();i++){
            int valVar = data[i][counter]; 
            index = getIndex(var,valVar,data[i],Alarm);
            if(valVar=="?"){
                missing[index] = true; 
            }
            else{
                if(missing[index]==false) CPT[index] = CPT[index]+1;
            }
            for(int i=0;i<CPT.size();i++){
                if(missing[i]==true) CPT[i] = rand()
                else CPT[i] = CPT[i]/data.size();
            }
        }
        listIt->setCPT(CPT);
        counter = counter+1;
    } 
}
//It takes variable,Value_of_variable,data_instance and Alarm as input and returns the index in the CPT Table  
int getIndex(string var,string valVar,vector<string> instance,Network Alarm){
    int index = 0;
    list<Graph_Node>::Iterator listIt1 = Alarm.search_node(var);
    int nvalues = listIt1->get_nvalues();
    vector<string> values = listIt1->get_values();
    vector<string> parents = listIt1->get_Parents();
    int nparents = parents.size();
    vector<string> parentSize;
    for(int i=0;i<nParents;i++) parentSize.push_back(parent[i].size());
    int temp=1;
    for(int i=0;i<nParents;i++){
        int id = Alarm.get_index(parents[i])
        for(int j=0;j<parents[i].size();j++){
            if(values[j]==instance[id]){
                index = index + j*temp;
                break;
            }
        }
        temp = temp*parents[i].size();
    }
    for(int i=0;i<nvalues;i++){
        if(values[i]==valVar){
            index = index + i*temp;
            break;
        }
    }
    return index;
}

//Reads the data from the file and returns in a dataStructure
pair<vector<pair<vector<string>,float>>,int> getData(Network Alarm){
    ifstream inFile;
    inFile.open("records.dat");
    string val;
    vector<vector<string>> result;
    if(inFile.is_open){
        numLines = 0;
        vector<string> instance;
        while(numLines<11100){
            int flag = -1;
            for(int i=0;i,37;i++){
                inFile>> val;
                if(val=="?") flag = i; 
                instance.push_back(val);
            }
            if(flag>=0){
                result.push_back({instance,-1});
                list<Graph_Node>::Iterator listIt = Alarm.get_nth_node(i);
                vector<string> values = listIt->getValues();
                for(int i=0;i<values.size();i++){
                    vector<string> temp = instance;
                    temp[flag] = values[i];
                    result.push_back({temp,0});
                }
            }
            if(flag<0) result.push_back({instance,1})
            numLines = numLines+1;
        }
    }
    return {result,numLines};
} 