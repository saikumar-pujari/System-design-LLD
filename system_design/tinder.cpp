// #include <iostream>
// #include <vector>
// #include <thread>
//  #include <chrono>
// using namespace std;

// void calculateSquare(int num) {
//     cout  << num * num << endl;
// }

// int main() {
//     vector<int> numbers = {1,2,3,4,5,6,7,8,9,10};
//     vector<thread> threads;

//     auto start_time=chrono::high_resolution_clock::now();
//     // Create a thread for each number
//     for(int num : numbers){
//         threads.push_back(thread(calculateSquare, num));
//     }

//     // Join threads (wait for them to finish)
//     for(auto &t : threads){
//         t.join();
//     }

//     auto end_time = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
//     cout << "Time: " << duration << " ms\n\n";
//     cout << "All threads completed!" << endl;
//     return 0;
// }

// #include <iostream>
// #include <queue>
// #include <thread>
// #include <mutex>
// #include <condition_variable>
// #include <vector>
// #include <string>
// #include <chrono>

// using namespace std;

// // ------------ Event Broker --------------
// class EventBroker {
// public:
//     queue<string> events;
//     mutex mtx;
//     condition_variable cv;

//     void publish(const string &event) {
//         lock_guard<mutex> lock(mtx);
//         events.push(event);
//         cv.notify_all();
//         cout << "[Broker] New Event Published: " << event << endl;
//     }

//     string consume() {
//         unique_lock<mutex> lock(mtx);
//         cv.wait(lock, [&]{ return !events.empty(); });
//         string event = events.front();
//         events.pop();
//         return event;
//     }
// };

// // ------------ Consumers (Subscribers) --------------

// void NotificationService(EventBroker &broker) {
//     while (true) {
//         string event = broker.consume();
//         cout << "[----Notification Service] Processing event: " << event << endl;
//         this_thread::sleep_for(1s);
//     }
// }

// void InventoryService(EventBroker &broker) {
//     while (true) {
//         string event = broker.consume();
//         cout << "[Inventory Service] Updating stock for event: " << event << endl;
//         this_thread::sleep_for(1500ms);
//     }
// }

// // ------------ Producer (Order Service) --------------

// void OrderProducer(EventBroker &broker) {
//     vector<string> sampleOrders = {
//         "OrderPlaced: Pizza",
//         "OrderPlaced: Burger",
//         "OrderPlaced: Fries",
//         "OrderPlaced: Coke",
//     };

//     for (auto &order : sampleOrders) {
//         this_thread::sleep_for(2s);
//         broker.publish(order);
//     }
// }

// // ------------ Main Program --------------

// int main() {
//     EventBroker broker;

//     thread consumer1(NotificationService, ref(broker));
//     thread consumer2(InventoryService, ref(broker));
//     thread producer(OrderProducer, ref(broker));

//     producer.join();
//     consumer1.detach();
//     consumer2.detach();

//     // Keep program alive
//     while (true) {
//         this_thread::sleep_for(1s);
//     }
// }
#include <bits/stdc++.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

// This is the "job" we want to run on a schedule
void sendReport() {
    auto now = system_clock::to_time_t(system_clock::now());
    cout << "[JOB] Running sendReport at " << std::ctime(&now);
}

int main() {
    cout << "Starting tiny schedule-driven demo (job every 5 seconds)...\n";

    // Run forever
    while (true) {
        auto start = steady_clock::now();

        // 1. Run the job
        sendReport();

        // 2. Sleep until 5 seconds have passed
        auto end   = steady_clock::now();
        auto spent = duration_cast<seconds>(end - start).count();

        long long waitSeconds = max(0LL, 10LL - spent);
        this_thread::sleep_for(seconds(waitSeconds));
    }

    return 0;
}
//schedule -driven 
#include <bits/stdc++.h>
#include <chrono>
#include <thread>
using namespace std;

int storedResult = -1; // This simulates DB/cache storage

// Scheduled job
void runJob() {
    int randomScore = rand() % 100;
    storedResult = randomScore; // Storing result like DB
    cout << "[Job] New score generated: " << randomScore << endl;
}

// API call simulation (returns stored output)
int getLatestScore() {
    return storedResult;
}

int main() {
    cout << "Schedule-driven system demo...\n";

    // Run job in background every 5 seconds
    thread scheduler([](){
        while(true){
            runJob();
            this_thread::sleep_for(chrono::seconds(5));
        }
    });

    // Simulating the user reading results
    for(int i = 0; i < 10; i++){
        cout << "User requested score -> " << getLatestScore() << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    scheduler.join();
    return 0;
}
