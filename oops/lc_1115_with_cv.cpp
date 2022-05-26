#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;

class FooBar {
private:
    int n;
    mutex m;
    bool flag = false;
    condition_variable cv;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo() {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(m);
            if(flag)
                cv.wait(lk);
            
            flag = true;
	    cout << "foo";
            cv.notify_one();
        }
    }

    void bar() {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(m);
            if(!flag)
                cv.wait(lk);
            flag = false;
	    cout << "bar" <<endl;
	    cv.notify_one();
        }
    }
};

void thread_function1(FooBar &f) {
	f.foo();
}

void thread_function2(FooBar &f) {
	f.bar();
}



int main() {
	FooBar f(10);
	thread t1(thread_function1, std::ref(f));
	thread t2(thread_function2, std::ref(f));

	t1.join();
	t2.join();	

}
