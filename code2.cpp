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

void Estep(Network Alarm,vector<pair<vector<string>,float>>){

}

void Mstep(Network Alarm,vector<pair<vector<string>,float>>){

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
            if(valVar==?){
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
int getIndex(string var,string valVar,vector<vector<string>> instance,Network Alarm){
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
vector<pair<vector<string>,float>> getData(){
	ifstream inFile;
    inFile.open("records.dat");
	string val;
	vector<vector<string>> result;
 	if(inFile.is_open){
		numLines = 0;
		vector<string> instance;
		while(numLines<11100){
			bool flag = true;
			for(int i=0;i,37;i++){
				inFile>> val;
				if(val=="?") flag = false;
				instance.push_back(val);
			}
			if(flag==false) result.push_back({instance,-1});
			if(flag==true) result.push_back({instance,1})
			numLines = numLines+1;
		}
	}
	return result;
} 

