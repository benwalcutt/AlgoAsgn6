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
		int connector;
		
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
			int connector = 0;
		}
};

class Edge {
	private:
		int weight;
		
	public:
		Vertex A;
		Vertex B;
		bool used;
		
		int get_weight() {
			return weight;
		}
		
		void set_weight(int param) {
			weight = param;
		}

};

void make_heap(Vertex * A, int size);
void adjusting_down(int node, Vertex * A, int size);
int find_path(Vertex * ver, Edge * edg, Vertex * pri_q, int source, int dest, int num_of_edges);
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

int find_path(Vertex * ver, Edge * edg, Vertex * pri_q, int source, int dest, int num_of_comps, int num_of_edges) {
	int base_vertex = 0;
	int search_vertex = 0;
	int temp_dist = 0;	
	int temp_count = num_of_comps;
	
	// set source equal to 0 and assigned for vertex and pri_q
	ver[source].set_dist(0);
	ver[source].set_assigned(true);
	pri_q[source + 1].set_dist(0);
	pri_q[source + 1].set_assigned(true);
	
	// initialize base_vertex which will change
	base_vertex = source;
	
	// remove source from pri_q
	make_heap(pri_q, num_of_comps);
	swap_ver(pri_q, 1, num_of_comps);
	num_of_comps--;
	// loop while dest is not assigned
	while (!(ver[dest].get_assigned())) {
		// loop through edges to find one with base vertex as a vertex
		for (int i = 0; i < num_of_edges; i++) {
			if (edg[i].A.name == base_vertex && !(edg[i].B.get_assigned())) {
				//found an edge with a vertex that is the base
				// search through pri_q to find where the connecting vertex is located
				search_vertex = edg[i].B.name;
				for (int j = 1; j <= num_of_comps; j++) {
					if (pri_q[j].name == search_vertex) {
						// found the vertex in the pri_q by name
						// compare distance by distance already discovered
						temp_dist = edg[i].get_weight() + ver[base_vertex].get_dist();
						if (temp_dist < pri_q[j].get_dist()) {
							// newly discovered distance is shorter so update
							pri_q[j].set_dist(temp_dist);
							pri_q[j].connector = base_vertex;
						} // end temp_dist if
					} // end pri_q name and search_vertex if
				} // end search through pri_q
			} // end if a.name is base vertex
			
			else if (edg[i].B.name == base_vertex && !(edg[i].A.get_assigned())) {
				//found an edge with a vertex that is the base
				// search through pri_q to find where the connecting vertex is located
				search_vertex = edg[i].A.name;
				for (int j = 1; j <= num_of_comps; j++) {
					if (pri_q[j].name == search_vertex) {
						// found the vertex in the pri_q by name
						// compare distance by distance already discovered
						temp_dist = edg[i].get_weight() + ver[base_vertex].get_dist();
						if (temp_dist < pri_q[j].get_dist()) {
							// newly discovered distance is shorter so update
							pri_q[j].set_dist(temp_dist);
							pri_q[j].connector = base_vertex;
						} // end temp_dist if
						else {
						}
					} // end pri_q name and search_vertex if
				} // end search through pri_q
			} // end if b.name is base vertex
			
		} // end edge loop
		
		// found all the newly discovered paths so we need make heap again which will place the lowest distance at the top
		make_heap(pri_q, num_of_comps);
		

		// swap so lowest becomes the last
		swap_ver(pri_q, 1, num_of_comps);
		// update the Vertex table to show the distance and set assigned
		ver[pri_q[num_of_comps].name].set_dist(pri_q[num_of_comps].get_dist());
		ver[pri_q[num_of_comps].name].set_assigned(true);
		// remove the last element of the pri_q
		base_vertex = pri_q[num_of_comps].name;
		num_of_comps--;
	} // end while
	return ver[dest].get_dist();
}

int main() {
	Vertex * V;
	Edge * E;
	Vertex * Q;
	
	int num_of_cases = 0;
	int case_counter = 1;
	int result = 0;
	
	int num_of_comps = 0;
	int num_of_cables = 0;
	int source_comp = 0;
	int dest_comp = 0;
	
	int ver_A = 0;
	int ver_B = 0;
	int weight = 0;
	
	cin >> num_of_cases;
	cin.ignore();
	
	while (case_counter <= num_of_cases) {
		cin >> num_of_comps;
		cin.ignore();
		
		V = new Vertex[num_of_comps];
		Q = new Vertex[num_of_comps + 1];
		
		for (int i = 0; i < num_of_comps; i++) {
			V[i].name = i;
			Q[i+1].name = i;
		}
		
		cin >> num_of_cables;
		cin.ignore();
		
		E = new Edge[num_of_cables];
		
		cin >> source_comp;
		cin.ignore();
		
		cin >> dest_comp;
		cin.ignore();
		
		int counter = num_of_cables;
		
		while (counter != 0) {
			counter--;
			cin >> ver_A;
			cin.ignore();
			
			cin >> ver_B;
			cin.ignore();
			
			cin >> weight;
			cin.ignore();
			
			E[counter].A.name = ver_A;
			E[counter].B.name = ver_B;
			E[counter].set_weight(weight);
			E[counter].used = false;
			

		} // end little while

		result = find_path(V, E, Q, source_comp, dest_comp, num_of_comps, num_of_cables);
		
		if (result != INFINITY) {
			cout << "Case #" << case_counter << ": " << result << endl;
		}
		else {
			cout << "Case #" << case_counter << ": unreachable" << endl;
		}
		case_counter++;
		
		delete[] V;
		delete[] E;
		delete[] Q;
		
	} // end big while
	return 0;
}