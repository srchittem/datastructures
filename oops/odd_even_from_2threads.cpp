#include <iostream>
#include<thread>
#include <mutex>
#include <condition_variable>

using namespace std;


int counter = 1;
mutex cv_m;
condition_variable cv;


void even(){
	while(1) {
		unique_lock<mutex> lk(cv_m);

		if(counter % 2){
			cv.wait(lk);
		}

		cout << counter <<endl;
		counter++;
		cv.notify_one();
		if(counter>10)
			break;
	}
}



void odd() {
	while(1) {
		unique_lock<mutex> lk(cv_m);
		if(counter % 2 == 0){
			cv.wait(lk);
		}

		cout << counter <<endl;
		counter ++;
		cv.notify_one();
		if(counter>=10)
			break;
	
	}

}

int main() {
	
	thread t1(even);
	thread t2(odd);

	t1.join();
	t2.join();

}


