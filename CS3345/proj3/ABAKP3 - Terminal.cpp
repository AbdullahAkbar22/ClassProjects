#include <bits/stdc++.h>

using namespace std;

struct Edge;

struct Node{
	int val;
	vector<Edge *> connections;
	Node * from;
	int shortestD;
	
};

struct Edge{
	Node * from;
	Node * to;
	bool visited = false;
	int weight;
	
};

struct MSTEdge{
	int vOne;
	int vTwo;
};

struct edgeCmp{
    bool operator()(Edge* a, Edge* b)
    {
        return a->weight > b->weight;
    }
};

struct mstCMP{
	bool operator()(MSTEdge a, MSTEdge b)
    {
		if(a.vOne == b.vOne)
			return a.vTwo > b.vTwo;
        return a.vOne > b.vOne;
    }
};


priority_queue<Edge*, vector<Edge*>, edgeCmp> edgeList;
priority_queue<MSTEdge, vector<MSTEdge>, mstCMP> mstEdges;

vector<Node *> nodeList;
queue<Edge *> edgesOn;

int* parents;



int find(int passed){
	if(parents[passed] == -1){
		return passed;
	}
	
	return find(parents[passed]);
}

int unionElements(int one, int two){
	int parentTwo = find(two);
	
	int parentOne = find(one);
	
	if(parentOne == parentTwo)
		return -1;
	
	parents[parentTwo] = one;
	return 1;
}

int main(){
	int numberNodes, source;
	cin >> numberNodes >> source;
	parents = new int[numberNodes + 1];
	fill(parents, parents + numberNodes + 1, -1);
	Node * src;
	for(int i = 1; i <= numberNodes; i++){
		Node * newN = new Node();
		newN->val = i;
		if(i == source){
			newN->shortestD = 0;
			src = newN;
		}
		else{
			newN->shortestD = INT_MAX;
		}
		nodeList.push_back(newN);
	}
	
	int vFrom, vTo, edgeWeight;
	cin >> vFrom >> vTo >> edgeWeight;
	while(vFrom != 0 && vTo != 0 && edgeWeight != 0){
		Edge * newE = new Edge();
		newE->from = nodeList[vFrom - 1];
		newE->to = nodeList[vTo - 1];
		newE->weight = edgeWeight;
		
		nodeList[vFrom - 1]->connections.push_back(newE);
		nodeList[vTo - 1]->connections.push_back(newE);
		edgeList.push(newE);
		cin >> vFrom >> vTo >> edgeWeight;
	}
	
	for(Edge * connected : src->connections){
		edgesOn.push(connected);
	}
	
	while(!edgesOn.empty()){
		Edge * currentEdge = edgesOn.front();
		edgesOn.pop();
		if(!currentEdge->visited){
			Node * nodeTo = currentEdge->to;
			Node * nodeFrom = currentEdge->from;
			if((nodeFrom->shortestD + currentEdge->weight) < nodeTo->shortestD && (nodeFrom->shortestD + currentEdge->weight) >= 0){
				nodeTo->shortestD = (nodeFrom->shortestD + currentEdge->weight);
				nodeTo->from = nodeFrom;
			}
			if((nodeTo->shortestD + currentEdge->weight) < nodeFrom->shortestD && (nodeTo->shortestD + currentEdge->weight) >= 0){
				nodeFrom->shortestD = (nodeTo->shortestD + currentEdge->weight);
				nodeFrom->from = nodeTo;
			}
			currentEdge->visited = true;
			for(Edge * edgeToGo : nodeTo->connections){
				edgesOn.push(edgeToGo);
			}
		}
		
	}
	
	for(Node * nodeOn : nodeList){
		if(nodeOn == src){
			cout << nodeOn->val << " " << nodeOn->val << " " << 0 << endl;
		}
		else{
			vector<int> path;
			Node * traverse = nodeOn;
			while(traverse != src){
				path.push_back(traverse->val);
				traverse = traverse->from;
			}
			path.push_back(src->val);
			for(int x = path.size() - 1; x > -1; x--){
				cout << path[x] << " ";
			}
			cout << nodeOn->shortestD << endl;
		}
	}
	
	cout << endl;
	int edgesAdded = 0;
	int mstSum = 0;
	while(edgesAdded < numberNodes && !edgeList.empty()){
		Edge * KEOn = edgeList.top();
		edgeList.pop();
		if(!(unionElements(KEOn->from->val, KEOn->to->val) == -1)){
			edgesAdded++;
			mstSum += KEOn->weight;
			MSTEdge M = MSTEdge();
			M.vOne = min(KEOn->from->val, KEOn->to->val);
			M.vTwo = max(KEOn->from->val, KEOn->to->val);
			mstEdges.push(M);
		}
		
	}
	
	while(!mstEdges.empty()){
		MSTEdge M = mstEdges.top();
		mstEdges.pop();
		cout << M.vOne << " " << M.vTwo << endl;
	}
	cout << "Minimal spanning tree length = " << mstSum << endl;
}