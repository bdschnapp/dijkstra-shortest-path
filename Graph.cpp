#include <iostream>
#include <vector>
#include <fstream> 
#include <climits>
using namespace std;

struct Edge{
	string source, target;
	int weight;
};

class Graph
{
public:
	vector<vector<int>> data;
	vector<string> names;


	Graph(string fileName){
		//initializes a vector of edges and fills vector from file
		ifstream fin;
		fin.open(fileName);
		int edgesSize;
		vector<Edge> edges;
		fin>>edgesSize;
		edges.resize(edgesSize);
		for (int i = 0; i < edgesSize; i++){
			Edge temp;
			fin>>temp.source;
			fin>>temp.weight;
			fin>>temp.target;
			edges[i] = temp;
		}
		
		
		//sets the values in names to their appropriate names
		for(int i = 0; i < edges.size(); i++){
			bool found = false;
			bool tar;
			int j = 0;
			while( j < names.size() && !found){
				if(names[j] == edges[i].source || names[j] == edges[i].target){
					found = true;
				}
				j++;
			}
			if(!found){
				names.push_back(edges[i].source);	
			}
		}
		//resizes data and sets all values to infinity
		for(int i = 0; i < names.size(); i++){
		data.push_back(vector<int>());
			for(int j = 0; j < names.size(); j++){
				data[i].push_back(INT_MAX);
			}		
		}
		//sets all values to their appropriate weights
		for(int n = 0; n < edges.size(); n++){
			int s, t;
			for(int i = 0; i < names.size(); i++){
				if(edges[n].source == names[i]){
					s = i;
				}
				if(edges[n].target == names[i]){
					t = i;
				}
			}
			data[s][t] = data[t][s] = edges[n].weight;
		}
		for(int i = 0; i < names.size();i++){
			data[i][i] = 0;
		}
	}
	
	void print(){
		for(int i = 0; i < names.size(); i++){
			cout << names[i];
			for(int j = 0; j < names.size(); j++){
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	void dijkstra(){
		vector<bool> v;
		vector<int> d; 
		for(int i = 0; i < names.size(); i++){
			v.push_back(false);
			d.push_back(INT_MAX);
		}
		d[0] = 0;
		
		for(int i = 0; i < names.size() - 1 ; i++){
		
			int c;
			int min = INT_MAX; 

		   	for (int j = 0; j < names.size(); j++){
		   		if (v[j] == false && d[j] <= min){
    			 	min = d[j];
					c = j;
				}
			}
    		v[c] = true;
			
			for(int j = 0; j < names.size(); j++){
				if ((!v[j])&& (data[c][j]) && (d[c] != INT_MAX) && (d[c]+data[c][j] < d[j]))
					d[j] = d[c] + data[c][j];
			}	 	
		}
		
		for(int i = 1; i < names.size(); i++){
			cout << "Distance from " << names[0] << " to " << names[i] << " is " << d[i] << endl;
		}
	}
};

int main(){
	Graph graph1 = Graph("Givengraph.txt");
	graph1.print();
	graph1.dijkstra();
	return EXIT_SUCCESS;
}


