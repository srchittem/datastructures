#include <iostream>
using namespace std;



struct Resource{
	int val;
};


class Demo {

	public:	
	Demo():m_resource_p(new Resource) {}
	~Demo(){delete m_resource_p;}

	Demo(const Demo & other):m_resource_p(new Resource) {cout <<"Copy Constructor" <<endl;}
	Demo & operator=(const Demo &other) {
		cout <<"Assignment Constructor" <<endl;
		m_resource_p = new Resource;
	}

	Demo(Demo &&other):m_resource_p(other.m_resource_p) {other.m_resource_p = NULL;}
	Demo & operator=(Demo && other){
		m_resource_p = other.m_resource_p;
		other.m_resource_p = NULL; 
	}

	private:
		Resource *m_resource_p;
};

Demo test_function(Demo &d) {
	Demo local;
	return local;
}

int main() {
	Demo d1,d2;

	d2= test_function(d1);



	cout << "exit" <<endl;
}
