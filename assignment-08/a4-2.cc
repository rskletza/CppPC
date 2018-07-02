#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
using namespace std;

int main() {
    int c = 0;
    mutex queue_mutex;
    condition_variable cv;
    bool done = false; 
    queue<int> goods;

    thread producer([&]() {
        for (int i = 0; i < 500; ++i) {
            unique_lock<mutex> lk(queue_mutex);
//            cv.wait(queue_mutex, []{return done;});
            goods.push(i);
            c++;
 //           cout << "push ";
            lk.unlock();
//            cv.notify_all();
        }

        done = true;
    });

    thread consumer([&]() {
        while (!done) {
            while (!goods.empty()) {
                unique_lock<mutex> lk(queue_mutex);
 //               cv.wait(lk, done);
                goods.pop();
                c--;
//                cout << "pop ";
                lk.unlock();
            }
        }
    });

    producer.join();
    consumer.join();
    cout << "Net: " << c << endl;
}
