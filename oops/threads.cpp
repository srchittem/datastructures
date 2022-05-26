#include <iostream>
#include <thread>
#include <string>

using namespace std;


struct work{
	string m_data;

	work(string data):m_data(data) {};
	~work() {cout << "in work destructor" <<endl;}

	work (work && other):m_data(other.m_data) {/*other.m_data = "";*/}
	work &operator=(work && other) {};

	work (const work & other):m_data(other.m_data) {/*other.m_data = "";*/}
	work &operator=(const work & other) {};

	void operator()() {cout << "in work operator()";}

	const string& GetData() {return m_data;}
};

void thread_function1(int i) {
        while(i<10) {
                cout << i <<endl;
                i++;
        }
}

void thread_function2(int &i) {
        while(i<20) {
                cout << i <<endl;
                i++;
        }
}


void thread_function3(work w) {
        while(1) {
		w.m_data ="thread3";
		cout << w.GetData() << endl;
        	break;
	}
}


int main() { 
        int first_parameter = 0;
        int second_parameter = 10;
    
  	work  w("main");

        std::thread t1(thread_function1,first_parameter);
        std::thread t2(thread_function2, std::ref(second_parameter));
        std::thread t3(thread_function3,w);

        t1.join();
        t2.join();
        t3.join();


	
        cout << "Main thread exit" << first_parameter << " " << second_parameter  << " " << w.GetData()  << endl;

}   


