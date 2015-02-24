#include <cstdlib>
#include <iostream>
#include <string>

#define INFINITY 2000000000

using namespace std;

class Vertex {
	private:
		int dist_to_source;
		bool assigned;
	
	public:
		int name;
		
		int get_dist() {
			return dist_to_source;
		}
		bool get_assigned() {
			return assigned;
		}
		
		void set_dist(int param) {
			dist_to_source = param;
		}
		
		void set_assigned(bool param) {
			assigned = param;
		}
		
		Vertex() {
			dist_to_source = INFINITY;
			assigned = false;
		}
};

class Edge {
	private:
		int weight;
		
	public:
		Vertex A;
		Vertex B;
		
		int get_weight() {
			return weight;
		}
		
		void set_weight(int param) {
			weight = param;
		}

};

void make_heap(Vertex * A, int size);
void adjusting_down(int node, Vertex * A, int size);
int find_path(Vertex * ver, Edge * edg, int source, int dest, int num_of_edges);
void swap_ver(Vertex * A, int node1, int node2);

void make_heap(Vertex * A, int size) {

	for (int i = size / 2; i > 0; i--) {
		adjusting_down(i, A, size);
	}
}

void adjusting_down(int node, Vertex * A, int size) {

	int index_of_smaller_child = 0;
	int temp = 0;
	int temp2 = 0;

	if (node <= size / 2) {
		index_of_smaller_child = node * 2;
		if ((index_of_smaller_child + 1 <= size) && (A[index_of_smaller_child].get_dist() > A[index_of_smaller_child + 1].get_dist())) {
			index_of_smaller_child++;
		}
		if (A[node].get_dist() > A[index_of_smaller_child].get_dist()) {
			swap_ver(A, node, index_of_smaller_child);
			adjusting_down(index_of_smaller_child, A, size);
		}
	}
}

void move_up_heap(Edge * A, int node) {
	int temp = 0;
	int temp2 = 0;
	
	while (A[node].get_weight() < A[node / 2].get_weight()) {
			temp = A[node].get_weight();
			temp2 = A[node / 2].get_weight();
			A[node].set_weight(temp2);
			A[node / 2].set_weight(temp);
			node = node / 2;
	}
}

void swap_ver(Vertex * A, int node1, int node2) {
	int temp = 0;
	int temp2 = 0;
	
	temp = A[node1].name;
	temp2 = A[node2].name;
	A[node1].name = temp2;
	A[node2].name = temp;
	
	temp = A[node1].get_dist();
	temp2 = A[node2].get_dist();
	A[node1].set_dist(temp2);
	A[node2].set_dist(temp);
			
	bool hold = false;
	hold = A[node1].get_assigned();
	
	if (A[node2].get_assigned()) {
		A[node1].set_assigned(true);
	}
	else
		A[node1].set_assigned(false);
	
	if (hold) {
		A[node2].set_assigned(true);
	}
	else
		A[node2].set_assigned(false);
}

int find_path(Vertex * ver, Edge * edg, int source, int dest, int num_of_comps) {
	
	ver[source + 1].set_dist(0);
	make_heap(ver, num_of_comps);
	swap_ver(ver, 1, num_of_comps);
	make_heap(ver, num_of_comps - 1);
	return 0;
}

int main() {
	Vertex * V;
	Edge * E;
	
	int num_of_cases = 0;
	
	int num_of_comps = 0;
	int num_of_cables = 0;
	int source_comp = 0;
	int dest_comp = 0;
	
	int ver_A = 0;
	int ver_B = 0;
	int weight = 0;
	
	cin >> num_of_cases;
	cin.ignore();
	
	while (num_of_cases-- != 0) {
		cin >> num_of_comps;
		cin.ignore();
		
		V = new Vertex[num_of_comps + 1];
		
		for (int i = 1; i <= num_of_comps; i++) {
			V[i].name = i;
		}
		
		cin >> num_of_cables;
		cin.ignore();
		
		E = new Edge[num_of_cables + 1];
		
		cin >> source_comp;
		cin.ignore();
		
		cin >> dest_comp;
		cin.ignore();
		
		int counter = num_of_cables;
		
		while (counter != 0) {
			cin >> ver_A;
			cin.ignore();
			cin >> ver_B;
			cin.ignore();
			cin >> weight;
			cin.ignore();
			
			E[counter].A.name = ver_A;
			E[counter].B.name = ver_B;
			E[counter].set_weight(weight);
			
			counter--;
		}
		
		make_heap(V, num_of_comps);
//		for (int j = 1; j <= num_of_comps; j++) {
//			cout << "V[" << j << "]: " << V[j].name << endl;
//		}
		find_path(V, E, source_comp, dest_comp, num_of_comps);
		
//		for (int j = 1; j <= num_of_comps; j++) {
//			cout << "V[" << j << "]: " << V[j].name << endl;
//		}
		
		delete[] V;
		delete[] E;
		
	}
	
	
	
	return 0;
}