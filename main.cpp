#include <iostream>
#include <string>
#include "lab4_GraphADT.hpp"

using namespace std;

class ContactTracingGraphTest {
public:
	void demo1() {
		std::cout << "Test Driver 1: " << endl;

		std::cout << "Test 0. Empty Cluster: " <<endl;

		ContactTracingGraph c1;
		cout << c1.find_largest_cluster_with_two_positive() <<endl; //(-1)

		// Two clusters of unequal size and some people sick
		std::cout << "Test 1: " << endl;

		ContactTracingGraph::PersonNode* p1 = new ContactTracingGraph::PersonNode("0001", "Andy", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p2 = new ContactTracingGraph::PersonNode("0002", "Kelsey", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p3 = new ContactTracingGraph::PersonNode("0003", "Darryl", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p4 = new ContactTracingGraph::PersonNode("0004", "Maria", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p5 = new ContactTracingGraph::PersonNode("0005", "Mike", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p6 = new ContactTracingGraph::PersonNode("0006", "Nate", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p7 = new ContactTracingGraph::PersonNode("0007", "Olivia", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p8 = new ContactTracingGraph::PersonNode("0008", "Jess", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p9 = new ContactTracingGraph::PersonNode("0009", "Shelley", "01/15/2020", false);

		c1.add_person(p1);
		c1.add_person(p2);
		c1.add_person(p3);
		c1.add_person(p4);
		c1.add_person(p5);
		c1.add_person(p6);
		c1.add_person(p7);
		c1.add_person(p8);
		c1.add_person(p9);

		//cluster 1
		c1.add_edge(p1, p2, 1, "University_of_Waterloo");
		c1.add_edge(p1, p3, 9, "University_of_Waterloo");
		c1.add_edge(p1, p5, 3, "University_of_Waterloo");
		c1.add_edge(p2, p4, 2, "University_of_Waterloo");
		c1.add_edge(p4, p3, 2, "University_of_Waterloo");
		c1.add_edge(p4, p5, 6, "University_of_Waterloo");

		//cluster 2
		c1.add_edge(p6, p7, 6, "University_of_Waterloo");
		c1.add_edge(p6, p8, 1, "University_of_Waterloo");
		c1.add_edge(p9, p7, 4, "University_of_Waterloo");
		c1.add_edge(p9, p8, 6, "University_of_Waterloo");
		c1.add_edge(p7, p8, 7, "University_of_Waterloo");

		std::cout << c1.count_virus_positive_contacts("0001") << endl; //call on sick person in 1st cluster
		std::cout << c1.count_virus_positive_contacts("0008") << endl; //call on not sick person in 2nd cluster
		std::cout << c1.count_virus_positive_contacts("0006") << endl; //call on sick person in 2nd cluster (should be 1 less than previous call)
		std::cout << c1.count_virus_positive_contacts("1000") << endl; //call on non-existant person

		std::cout << c1.find_largest_cluster_with_two_positive() << endl; //returns cluster 1

		//Two clusters of unequal size but the larger one has only 1 sick person
		std::cout << "Test 2: " << endl;
		ContactTracingGraph c2;

		ContactTracingGraph::PersonNode* p11 = new ContactTracingGraph::PersonNode("0001", "Andy", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p12 = new ContactTracingGraph::PersonNode("0002", "Kelsey", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p13 = new ContactTracingGraph::PersonNode("0003", "Darryl", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p14 = new ContactTracingGraph::PersonNode("0004", "Maria", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p15 = new ContactTracingGraph::PersonNode("0005", "Mike", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p16 = new ContactTracingGraph::PersonNode("0006", "Nate", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p17 = new ContactTracingGraph::PersonNode("0007", "Olivia", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p18 = new ContactTracingGraph::PersonNode("0008", "Jess", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p19 = new ContactTracingGraph::PersonNode("0009", "Shelley", "01/15/2020", false);

		c2.add_person(p11);
		c2.add_person(p12);
		c2.add_person(p13);
		c2.add_person(p14);
		c2.add_person(p15);
		c2.add_person(p16);
		c2.add_person(p17);
		c2.add_person(p18);
		c2.add_person(p19);

		//clustrer 1
		c2.add_edge(p11, p12, 1, "University_of_Waterloo");
		c2.add_edge(p11, p13, 9, "University_of_Waterloo");
		c2.add_edge(p11, p15, 3, "University_of_Waterloo");
		c2.add_edge(p12, p14, 2, "University_of_Waterloo");
		c2.add_edge(p14, p13, 2, "University_of_Waterloo");
		c2.add_edge(p14, p15, 6, "University_of_Waterloo");

		//cluster 2
		c2.add_edge(p16, p17, 6, "University_of_Waterloo");
		c2.add_edge(p16, p18, 1, "University_of_Waterloo");
		c2.add_edge(p19, p17, 4, "University_of_Waterloo");
		c2.add_edge(p19, p18, 6, "University_of_Waterloo");
		c2.add_edge(p17, p18, 7, "University_of_Waterloo");

		std::cout << c2.count_virus_positive_contacts("0001") << endl; //call on non-sick person in single-sick cluster
		std::cout << c2.count_virus_positive_contacts("0003") << endl; //call on sick person in single-sick cluster (1 less than prev)
		std::cout << c2.count_virus_positive_contacts("0008") << endl; //call on non-sick person in multi-sick cluster
		std::cout << c2.count_virus_positive_contacts("0006") << endl; //call on sick person in multi-sick cluster (1 less than prev)

		std::cout << c2.find_largest_cluster_with_two_positive() << endl; //should return size of smaller cluster (4)

		c1.store_graph("Demo1.txt");
		c1.load_graph("Demo1.txt");
	}
	void demo2() {
		std::cout << "Test Driver 2: " << endl;
		//Several Clusters of single people or double people ie: one or no connections between them

		ContactTracingGraph c1;

		ContactTracingGraph::PersonNode* p1 = new ContactTracingGraph::PersonNode("0001", "Andy", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p2 = new ContactTracingGraph::PersonNode("0002", "Kelsey", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p3 = new ContactTracingGraph::PersonNode("0003", "Darryl", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p4 = new ContactTracingGraph::PersonNode("0004", "Maria", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p5 = new ContactTracingGraph::PersonNode("0005", "Mike", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p6 = new ContactTracingGraph::PersonNode("0006", "Nate", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p7 = new ContactTracingGraph::PersonNode("0007", "Olivia", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p8 = new ContactTracingGraph::PersonNode("0008", "Jess", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p9 = new ContactTracingGraph::PersonNode("0009", "Shelley", "01/15/2020", false);

		c1.add_person(p1);
		c1.add_person(p2);
		c1.add_person(p3);
		c1.add_person(p4);
		c1.add_person(p5);
		c1.add_person(p6);
		c1.add_person(p7);
		c1.add_person(p8);
		c1.add_person(p9);

		c1.add_edge(p1, p3, 6, "University_of_Waterloo");

		std::cout << c1.count_virus_positive_contacts("0001") << endl; //returns 1 since has a partner that is sick
		std::cout << c1.count_virus_positive_contacts("0003") << endl; //All should return 0
		std::cout << c1.count_virus_positive_contacts("0007") << endl;
		std::cout << c1.count_virus_positive_contacts("1000") << endl;

		std::cout << c1.find_largest_cluster_with_two_positive() << endl; //-1 since no cluster of more than 1 sick person

		c1.store_graph("Demo2.txt");
		c1.load_graph("Demo2.txt");
	}

	void demo3() {
		std::cout << "Test Driver 3: " << endl;

		//Two clusters of equal size but only 1 sick person in entire graph
		std:cout << "Test 1: " << endl;

		ContactTracingGraph c1;

		ContactTracingGraph::PersonNode* p1 = new ContactTracingGraph::PersonNode("0001", "Andy", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p2 = new ContactTracingGraph::PersonNode("0002", "Kelsey", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p3 = new ContactTracingGraph::PersonNode("0003", "Darryl", "01/15/2020", true);
		ContactTracingGraph::PersonNode* p4 = new ContactTracingGraph::PersonNode("0004", "Maria", "01/15/2020", false);
		
		ContactTracingGraph::PersonNode* p6 = new ContactTracingGraph::PersonNode("0006", "Nate", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p7 = new ContactTracingGraph::PersonNode("0007", "Olivia", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p8 = new ContactTracingGraph::PersonNode("0008", "Jess", "01/15/2020", false);
		ContactTracingGraph::PersonNode* p9 = new ContactTracingGraph::PersonNode("0009", "Shelley", "01/15/2020", false);

		c1.add_person(p1);
		c1.add_person(p2);
		c1.add_person(p3);
		c1.add_person(p4);
		c1.add_person(p6);
		c1.add_person(p7);
		c1.add_person(p8);
		c1.add_person(p9);

		//cluster 1
		c1.add_edge(p1, p2, 1, "University_of_Waterloo");
		c1.add_edge(p1, p3, 9, "University_of_Waterloo");
		c1.add_edge(p2, p4, 2, "University_of_Waterloo");
		c1.add_edge(p4, p3, 2, "University_of_Waterloo");

		//cluster 2
		c1.add_edge(p6, p7, 6, "University_of_Waterloo");
		c1.add_edge(p6, p8, 1, "University_of_Waterloo");
		c1.add_edge(p9, p7, 4, "University_of_Waterloo");
		c1.add_edge(p9, p8, 6, "University_of_Waterloo");
		c1.add_edge(p7, p8, 7, "University_of_Waterloo");

		std::cout << c1.count_virus_positive_contacts("0001") << endl; //1 person  sick in this cluster
		std::cout << c1.count_virus_positive_contacts("0003") << endl; //this is only sick person in the cluster; therefore, return 0
		
		std::cout << c1.count_virus_positive_contacts("0007") << endl; //no sick person in this cluster

		std::cout << c1.find_largest_cluster_with_two_positive() << endl; //-1 since at most one sick person per cluster
		
		//Two clusters of equal size and 2 people sick per cluster
		std::cout << "Test 2: " << endl;
		ContactTracingGraph::PersonNode* p10 = new ContactTracingGraph::PersonNode("0010", "James", "01/15/2020", true);
		ContactTracingGraph::PersonNode * p11 = new ContactTracingGraph::PersonNode("0011", "Igor", "01/15/2020", false);
		ContactTracingGraph::PersonNode * p12 = new ContactTracingGraph::PersonNode("0012", "Michael", "01/15/2020", true);
		ContactTracingGraph::PersonNode * p13 = new ContactTracingGraph::PersonNode("0013", "Christiano", "01/15/2020", true);
		c1.add_person(p10);
		c1.add_person(p11);
		c1.add_person(p12);
		c1.add_person(p13);

		c1.add_edge(p1, p10, 1, "University_of_Waterloo");
		c1.add_edge(p1, p11, 4, "University_of_Waterloo");
		c1.add_edge(p6, p12, 8, "University_of_Waterloo");
		c1.add_edge(p6, p13, 36, "Toronto");

		std::cout << c1.count_virus_positive_contacts("0001") << endl; //2 people  sick in this cluster
		std::cout << c1.count_virus_positive_contacts("0003") << endl; //sick person in first cluster; therefore, return one less than previous
		
		std::cout << c1.count_virus_positive_contacts("0007") << endl; //2 sick people in this cluster

		std::cout << c1.find_largest_cluster_with_two_positive() << endl; //return size of each equal cluster (6) 

		c1.add_person(new ContactTracingGraph::PersonNode("0019", "Sad_Person", "02/14/2020", true));

		c1.store_graph("Demo3.txt");
		c1.load_graph("Demo3.txt");
	}
};


int main() {
	ContactTracingGraphTest T1;
	T1.demo1();
	T1.demo2();
	T1.demo3();
}