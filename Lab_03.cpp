#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <locale>
#include <list>

using namespace std;

//split the string in vector of type string 
vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

vector< vector<char> > string_to_vector_of_char(string input_current_state){
	vector<string> states = split(input_current_state,';');
	vector<char> aux;
	vector< vector<char> > state;
	vector<string>::iterator it;
	//cycle to get the vector
	for (it=states.begin(); it<states.end(); it++)
	{
    	string aux_string = *it;

    	if (aux_string.compare(" ()") != 0  && aux_string.compare("()") != 0 )
    	{	
	    	for(int i = 0; i< aux_string.length(); i++)
	    	{
	    		if(isalpha(aux_string[i]))
	    		{
	    			 aux.push_back(aux_string[i]);
	    		}
	    	}
	    	//create the vector of vectors
	    	state.push_back(aux);
	    	//earse the content of the vector aux to get the next states right
	    	aux.erase(aux.begin(), aux.end());
    	}
    	else
    	{
    		aux.push_back(' ');
    		//create the vector of vectors
	    	state.push_back(aux);
	    	//earse the content of the vector aux to get the next states right
	    	aux.erase(aux.begin(), aux.end());
    	}
	}
	return state;
}

// State class to repepresent the conection of each state
class State{
	vector< vector<char> > state;
	int path_cost;
	pair<int, int> movement;
	int visited = 1;
	int h = 0;
	int g = 0;
public:
	State(vector<vector <char> > state);
	State(vector<vector <char> > state,int path_cost,pair<int,int> movement);
	vector<vector<char> > getState();
	int getVisit();
	int getPathCost();
	void setMovement(pair<int,int> movement);
	void setPathCost(int v);
	void setVisited(int v);
	void setState(vector< vector<char> > state);
	void DFS(State state);
};
vector<vector<char> > State::getState(){
	return this->state;
}
void State::setPathCost(int v){
	this->path_cost = v;
}
int State::getPathCost(){
	return this->path_cost;
}
void State::setVisited(int v){
	this->visited = v;
}
void State::setMovement(pair<int,int> movement){
	this->movement = movement;
}

void State::setState(vector< vector<char> > state){
	this->state = state;
}
int State::getVisit(){
	return this->visited;
}

State::State(vector<vector <char> > state){
	this->state = state;
	this->path_cost = 0;
	this->movement = {0,0};
}
State::State(vector<vector <char> > state,int path_cost,pair<int,int> movement){
	this->state = state;
	this->path_cost = path_cost;
	this->movement = movement;
	this->visited = 1;
}


stack< State >  GenerateEstates(State state){
	//variables
	stack< State > DFS_Stack;
	int i = 0;
	int j = 0;
	char aux;
	int size = state.getState().size() -1;
	vector<vector<char> > v = state.getState();
	for (i = 0;i < v.size(); i++)
	{
		if (v.at(i).back() != ' '){
			aux  = v.at(i).back();
			v.at(i).pop_back();
			
			for (j = 0; j < v.size(); j++)
			{
				if (i != size-j){
					vector<char> aux_vector;

					if(state.getState().at(size-j).back() == ' '){
						aux_vector.push_back(aux);
						State state_aux(v,(state.getPathCost() + 1 + abs(size-j)),{i,j});
						v.at(size-j).swap(aux_vector);
 					}
 					else{
 						v.at(size-j).push_back(aux);
						State state_aux(v,(state.getPathCost() + 1 + abs(size-j)),{i,j});
						DFS_Stack.push(state_aux);
						v.at(size-j).pop_back();
					}
				}
			}
			v.at(i).push_back(aux);
		}
	}
	return DFS_Stack;
}

void DFSUtil(State state){

}

void DFS(State state){
	stack< State > states = GenerateEstates(state);

	for (stack< State > dump = states; !dump.empty(); dump.pop()){
			cout<< "estado: \n";
			for (int i = 0; i < dump.top().getState().size();i++){
				for (int j = 0; j < dump.top().getState().at(i).size(); ++j)
				{
					cout<< dump.top().getState().at(i)[j];
				}
				cout << "\n";
			}
	}

	for (; !states.empty(); states.pop()){
		if(states.top().getVisit() != 0){
			// DFS(states.top());
		}else{

		}
	}
}

int main(){
	// variables
	int number_height;
	string input_current_state;
	string input_goal_state;
	vector< vector<char> > current_state;
	vector< vector<char> > goal_state;

	//read the height 
	scanf("%d \n", &number_height);
	printf("number of the height is: %d \n", number_height);
	//read current state
	getline(cin, input_current_state);
	//convert the string to vecor of vector of type char
	current_state = string_to_vector_of_char(input_current_state);
	// it works
	// cout << "succes: " << current_state.at(0)[0] << "_\n";
	
	//initialize state
	State state(current_state);
	DFS(state);

	// read el goal state
	getline(cin, input_goal_state);
	//convert the string to vecor of vector of type char
	goal_state = string_to_vector_of_char(input_goal_state);

	return 0;
}