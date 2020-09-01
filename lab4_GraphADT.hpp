
#ifndef LAB4_GRAPH_ADT_HPP
#define LAB4_GRAPH_ADT_HPP

#include <string>
#include <vector>
#include <queue>

using namespace std;

//PURPOSE: Models an undirected Graph ADT
class ContactTracingGraph {

protected:
	struct PersonNode;

	//Linked list representation of all edges at a node
	struct EdgeNode {
		PersonNode* pNode; //Adjacent node
		EdgeNode* next; //next edge in linked list
		unsigned int days_since_contact;
		string contact_location;
		
		//must declare edgeNode with parametric constructor
		EdgeNode(PersonNode* new_pNode, EdgeNode* new_next, unsigned int new_days_since_contact, string new_contact_location) : 
			pNode(new_pNode), next(new_next), days_since_contact(new_days_since_contact), contact_location(new_contact_location) {}
	};

	//node declaration
	struct PersonNode {
		string id, first_name, last_test_date;
		bool has_virus;
		EdgeNode* adjacency_list_head;

		//must declare personNode with parametric constructor
		PersonNode(string new_id, string new_first_name, string new_last_test_date, bool new_has_virus, EdgeNode* new_adjacency_list_head) : 
			id(new_id), first_name(new_first_name), last_test_date(new_last_test_date), has_virus(new_has_virus), adjacency_list_head(new_adjacency_list_head) {}

		PersonNode(string new_id, string new_first_name, string new_last_test_date, bool new_has_virus) :
			id(new_id), first_name(new_first_name), last_test_date(new_last_test_date), has_virus(new_has_virus), adjacency_list_head(nullptr) {}
	};


	vector<PersonNode*> vctr; //array of all graph nodes
	int size; //probably can delete (but I have left this here for potential uses in the future)

	//private helper functions
	friend class ContactTracingGraphTest;
	void clean_up(PersonNode* cur);
	bool is_visited(PersonNode* cur, const vector<PersonNode*>& container) const;
	void update_visited(EdgeNode*& cur, queue<PersonNode*>& cluster, vector<PersonNode*>& visited) const;

public:
	// CONSTRUCTOR AND DESTRUCTOR
	// PURPOSE: Default/empty constructor
	ContactTracingGraph();

	//PURPOSE: Parametric constructor
	ContactTracingGraph(int new_size, vector<PersonNode*> new_vctr);

	// PURPOSE: Explicit destructor of the class ContactTracingGraph
	~ContactTracingGraph();

	//Returns the number of positive contacts in a cluster relative to starting person
	int count_virus_positive_contacts (string id) const;
	//Returns the size of the largest cluster (of at least size 2) with 2 positive cases
	int find_largest_cluster_with_two_positive() const;

	//Functions to add person and edge to graph
	bool add_person(PersonNode* new_person);
	bool add_edge(PersonNode* person_1, PersonNode* person_2, unsigned int days_since_contact,string contact_location);

	//File io
	bool store_graph(string file_name); //loads graph from text file and outputs to console
	bool load_graph(string file_name); //stores current graph as a text file
};

#endif