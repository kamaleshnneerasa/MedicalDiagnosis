#include "Network.h"

// The whole network represted as a list of nodes
int Network::addNode(Graph_Node node)
{
	Pres_Graph.push_back(node);
	return 0;
}
    
    
int Network::netSize()
{
	return Pres_Graph.size();
}

    // get the index of node with a given name
int Network::get_index(string val_name)
{
    list<Graph_Node>::iterator listIt;
    int count=0;
    for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
    {
        if(listIt->get_name().compare(val_name)==0)
            return count;
        count++;
    }
    return -1;
}

// get the node at nth index
list<Graph_Node>::iterator Network::get_nth_node(int n)
{
    list<Graph_Node>::iterator listIt;
    int count=0;
    for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
    {
        if(count==n)
            return listIt;
        count++;
    }
    return listIt; 
}

//get the iterator of a node with a given name
list<Graph_Node>::iterator Network::search_node(string val_name)
{
    list<Graph_Node>::iterator listIt;
    for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
    {
        if(listIt->get_name().compare(val_name)==0)
            return listIt;
    }
    
    cout<<"node not found\n";
    return listIt;
}

Network Network::read_network()
{
    Network Alarm;
    string line;
    int find=0;
    ifstream myfile("alarm.bif"); 
    string temp;
    string name;
    vector<string> values;
    
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            stringstream ss;
            getline (myfile,line);
            
            ss.str(line);
            ss>>temp;
            
            if(temp.compare("variable")==0)
            {                 
                    ss>>name;
                    getline (myfile,line);
                   
                    stringstream ss2;
                    ss2.str(line);
                    for(int i=0;i<4;i++)
                    {                       
                        ss2>>temp;                      
                    }
                    values.clear();
                    while(temp.compare("};")!=0)
                    {
                        values.push_back(temp);
                        
                        ss2>>temp;
                    }
                    Graph_Node new_node(name,values.size(),values);
                    int pos=Alarm.addNode(new_node);
                    
            }
            else if(temp.compare("probability")==0)
            {                    
                    ss>>temp;
                    ss>>temp;
                    
                    list<Graph_Node>::iterator listIt;
                    list<Graph_Node>::iterator listIt1;
                    listIt=Alarm.search_node(temp);
                    int index=Alarm.get_index(temp);
                    ss>>temp;
                    values.clear();
                    while(temp.compare(")")!=0)
                    {
                        listIt1=Alarm.search_node(temp);
                        listIt1->add_child(index);
                        values.push_back(temp);
                        
                        ss>>temp;

                    }
                    listIt->set_Parents(values);
                    getline (myfile,line);
                    stringstream ss2;
                    
                    ss2.str(line);
                    ss2>> temp;
                    
                    ss2>> temp;
                    
                    vector<float> curr_CPT;
                    string::size_type sz;
                    while(temp.compare(";")!=0)
                    {
                        
                        curr_CPT.push_back(atof(temp.c_str()));
                        
                        ss2>>temp;
                    }
                    
                    listIt->set_CPT(curr_CPT);
            }
            else
            {}          
    }
        
        if(find==1)
        myfile.close();
    }
    
    return Alarm;
}