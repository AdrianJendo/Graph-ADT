
#include <iostream>
#include "lab4_GraphADT.hpp"
#include <queue>
#include <fstream>
#include <iomanip>

using namespace std;

//Constructors
ContactTracingGraph::ContactTracingGraph(): size(0){}
ContactTracingGraph::ContactTracingGraph(int new_size, vector<PersonNode*> new_vctr) : size(new_size), vctr(new_vctr){}


// PURPOSE: Explicit destructor of the class
void ContactTracingGraph::clean_up(PersonNode* cur) {
	EdgeNode* ptr = cur->adjacency_list_head;
	while (ptr) {
		ptr = ptr->next;
		delete cur->adjacency_list_head;
		cur->adjacency_list_head = ptr;
	}
	delete cur;
}

ContactTracingGraph::~ContactTracingGraph() {
	while (vctr.size()) {
		clean_up(vctr.back());
		vctr.pop_back();
	}
	size = 0;
}

//checks if cur node is in the vector container (which represents all the visited nodes)
bool ContactTracingGraph::is_visited(PersonNode* cur, const vector<PersonNode*>& container) const{
	for (int i = 0; i < container.size(); ++i) {
		if (cur->id == container[i]->id) {
			return true;
		}
	}
	return false;
}

void ContactTracingGraph::update_visited(EdgeNode*& cur, queue<PersonNode*>& cluster, vector<PersonNode*>& visited) const{
	if (!is_visited(cur->pNode, visited)) { //if current node is not yet visited, add to cluster and make visited
		cluster.push(cur->pNode);
		visited.push_back(cur->pNode);
	}
	cur = cur->next;
}

int ContactTracingGraph::count_virus_positive_contacts(string id) const{
	int count = 0;
	vector<PersonNode*> visited;
	PersonNode* start = nullptr;
	for (int i = 0; i < vctr.size(); ++i) {
		if (vctr[i]->id == id) {
			start = vctr[i];
			visited.push_back(start); //push start into visited nodes to not count them if they are sick
		}
	}

	//if id exists in vctr
	if (start) {
		queue<PersonNode*> contacts; //queue of unvisited people with direct or indirect contact with start person
		EdgeNode* cur = start->adjacency_list_head;

		while (cur) {
			//push all the nodes adjacent to start node into queue and update visited nodes list
			update_visited(cur, contacts, visited);

			/*
			//since we don't acctually need to check the visited vector here, this is probably faster than using update_visited:
			//1) push the nodes adjacent to start node into queue
			contacts.push(cur->pNode); 
			//2) push the nodes adjacent to start node into visited nodes list
			visited.push_back(cur->pNode);
			cur = cur->next;
			*/
		}

		//loop until all adjacency nodes are visited
		while (contacts.size()) {
			//check if current person has virus
			if (contacts.front()->has_virus)
				++count;

			//loop through all the adjacent nodes in current adjacent list and add to containers if appropriate
			cur = contacts.front()->adjacency_list_head;
			while (cur)
				update_visited(cur, contacts, visited);
			
			contacts.pop();
		}
	}
	return count;
}

//1 count how many people are connected to starting individual
//2 count if at least 2 people are sick
int ContactTracingGraph::find_largest_cluster_with_two_positive() const{
	int max_count = -1;
	int cur_count = 0;
	int sick_count = 0;
	queue <PersonNode*> cluster;
	vector<PersonNode*> visited;

	//loop through each node in the graph
	for (int i = 0; i < vctr.size(); ++i) {
		//check if current node has already been visited
		if (!is_visited(vctr[i], visited)) { 
			//vctr[i] is pushed into queue and changed to visited
			cluster.push(vctr[i]);	
			visited.push_back(vctr[i]);

			//loop to look for all unvisited adjacent nodes
			EdgeNode* cur = vctr[i]->adjacency_list_head;
			while (cur || cluster.size()) { //while (adjacent nodes or nodes to be processed)
				//push all the nodes in the adjacency list into the cluster
				if (cur) 
					update_visited(cur, cluster, visited); // update the cluster and visited containers and also increment cur
				else { //!cur -> start to analyze the cluster and see if any more adjacent nodes need to be added to the cluster
					//analyze front of cluster
					cur_count++;
					if (cluster.front()->has_virus)
						sick_count++;
					cluster.pop();

					//analyze next adjacency list to see if there are any more adjacent nodes
					if (cluster.size())
						cur = cluster.front()->adjacency_list_head;
				}
			}

			//update max count if cluster with more than 1 sick person is found and size is greater than current max
			if (sick_count > 1 && cur_count>max_count)
				max_count = cur_count;

			//reset counts
			sick_count = 0;
			cur_count = 0;
		}
	}
	return max_count;
}

//Adds a new person node to the graph
bool ContactTracingGraph::add_person(PersonNode* new_person) {
	if (!new_person)
		return false;

	vctr.push_back(new_person);
	++size;

	return true;
}

//creates an edge between two nodes
bool ContactTracingGraph::add_edge(PersonNode* person_1, PersonNode* person_2, unsigned int days_since_contact, string contact_location) {
	if (!(person_1 && person_2))
		return false;

	EdgeNode* cur1 = person_1->adjacency_list_head;
	EdgeNode* cur2 = person_2->adjacency_list_head;

	//adds the new connection to the start of the adjacency node list and pushes the other adjacent nodes back
	person_1->adjacency_list_head = new EdgeNode(person_2, cur1, days_since_contact, contact_location);
	person_2->adjacency_list_head = new EdgeNode(person_1, cur2, days_since_contact, contact_location);

	return true;
}

bool ContactTracingGraph::load_graph(string file_name) {

	ifstream fin(file_name);
	if (!fin)
		return false;

	//Id name last_test_date has_virus contacts days_since_contact contact_location <- format
	string temp = "";
	
	while (temp != "Contact_Location" && fin >> temp) {}

	if (temp != "Contact_Location")
		return false;
	else {
		string id, first_name, last_test_date, contact_name, contact_location;
		bool has_virus;
		int days_since_contact;

		cout << setw(6) << "ID" << setw(16) << "Name" << setw(20) << "Last_Test_Date" << setw(14) << "Has_Virus" << setw(16) << "Contacts" <<
			setw(20) << "Days_Since_Contact" << setw(30) << "Contact_Location" << " " << endl;
		while (fin >> id) {
			if (id.substr(0, 1) == "0") { //all ID's start with 0 <- allows to easily process multiple contacts in else
				fin >> first_name;
				fin >> last_test_date;
				fin >> has_virus;
				fin >> contact_name;
				fin >> days_since_contact;
				fin >> contact_location;

				cout << setw(6) << id << setw(16) << first_name << setw(20) << last_test_date << setw(14) << has_virus << setw(16);
			}
			else {
				contact_name = id;
				fin >> days_since_contact;
				fin >> contact_location;	
			}
			cout << contact_name << setw(20) << days_since_contact << setw(30) << contact_location;
			cout << endl << setw(72);
			cout << endl;
		}
	}
	cout << "" << endl;
	fin.close();
	return true;
}

bool ContactTracingGraph::store_graph(string file_name) {

	ofstream fout(file_name);
	if (!fout)
		return false;

	fout << setw(6) << "ID" << setw(16) << "Name" << setw(20) << "Last_Test_Date" << setw(14) << "Has_Virus" << setw(16) << "Contacts" <<
		setw(20) << "Days_Since_Contact" << setw(30) << "Contact_Location" << " " << endl;

	for (int i = 0; i < vctr.size(); i++) {
		fout << setw(6) << vctr[i]->id << setw(16) << vctr[i]->first_name << setw(20) << vctr[i]->last_test_date << setw(14) << vctr[i]->has_virus << setw(16);

		EdgeNode* cur = vctr[i]->adjacency_list_head;
		if (!cur) {
			fout << "NULL" << setw(20) << -1 << setw(30) << "NULL";
			fout << endl << setw(72);
		}
		else do{
			fout << cur->pNode->first_name << setw(20) << cur->days_since_contact << setw(30) << cur->contact_location;
			fout << endl << setw(72);
			cur = cur->next;
		} while (cur);
		//fout << endl;
	}

	fout.close();
	return true;
}



