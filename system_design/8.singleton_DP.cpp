
/*
SINGLETON DESIGN PATTERN
========================

Definition:
-----------
Singleton is a creational design pattern that ensures a class has only ONE instance
and provides a global point of access to that instance.

Key Characteristics:
-------------------
1. Private constructor (prevents external instantiation)
2. Static instance variable
3. Static method to get the instance
4. Delete copy constructor and assignment operator (C++11)

Use Cases:
----------
- Database connections
- Logger classes
- Configuration managers
- Thread pools
- Cache systems
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>

using namespace std;

// ========================================================================
// 1. LAZY INITIALIZATION SINGLETON (Not Thread-Safe)
// ========================================================================
class LazyDatabaseConnection {
private:
    static LazyDatabaseConnection* instance;
    string connectionString;
    
    // Private constructor
    LazyDatabaseConnection() {
        connectionString = "Connected to Database";
        cout << "LazyDatabaseConnection created!" << endl;
    }
    
public:
    // Delete copy constructor and assignment operator
    LazyDatabaseConnection(const LazyDatabaseConnection&) = delete;
    LazyDatabaseConnection& operator=(const LazyDatabaseConnection&) = delete;
    
    // Static method to get instance
    static LazyDatabaseConnection* getInstance() {
        if (instance == nullptr) {
            instance = new LazyDatabaseConnection();
        }
        return instance;
    }
    
    void query(const string& sql) {
        cout << "Executing query: " << sql << endl;
    }
    
    string getConnection() {
        return connectionString;
    }
};

// Initialize static member
LazyDatabaseConnection* LazyDatabaseConnection::instance = nullptr;

// ========================================================================
// 2. EAGER INITIALIZATION SINGLETON (Thread-Safe by default)
// ========================================================================
class EagerLogger {
private:
    static EagerLogger* instance;
    
    // Private constructor
    EagerLogger() {
        cout << "EagerLogger created at program start!" << endl;
    }
    
public:
    // Delete copy constructor and assignment operator
    EagerLogger(const EagerLogger&) = delete;
    EagerLogger& operator=(const EagerLogger&) = delete;
    
    // Static method to get instance
    static EagerLogger* getInstance() {
        return instance;
    }
    
    void log(const string& message) {
        cout << "[LOG]: " << message << endl;
    }
};

// Eager initialization - created at program start
EagerLogger* EagerLogger::instance = new EagerLogger();

// ========================================================================
// 3. THREAD-SAFE SINGLETON with DOUBLE-CHECKED LOCKING
// ========================================================================
class ThreadSafeConfig {
private:
    static ThreadSafeConfig* instance;
    static mutex mtx;
    string configData;
    
    // Private constructor
    ThreadSafeConfig() {
        configData = "App Configuration Loaded";
        cout << "ThreadSafeConfig created by thread: " 
             << this_thread::get_id() << endl;
    }
    
public:
    // Delete copy constructor and assignment operator
    ThreadSafeConfig(const ThreadSafeConfig&) = delete;
    ThreadSafeConfig& operator=(const ThreadSafeConfig&) = delete;
    
    // Thread-safe getInstance with double-checked locking
    static ThreadSafeConfig* getInstance() {
        // First check without locking (performance optimization)
        if (instance == nullptr) {
            lock_guard<mutex> lock(mtx);  // Lock for thread safety
            // Second check with locking
            if (instance == nullptr) {
                instance = new ThreadSafeConfig();
            }
        }
        return instance;
    }
    
    void setConfig(const string& key, const string& value) {
        lock_guard<mutex> lock(mtx);
        cout << "Config set: " << key << " = " << value << endl;
    }
    
    string getConfig() {
        return configData;
    }
};

// Initialize static members
ThreadSafeConfig* ThreadSafeConfig::instance = nullptr;
mutex ThreadSafeConfig::mtx;

// ========================================================================
// 4. MEYER'S SINGLETON (C++11 Thread-Safe, Recommended)
// ========================================================================
class MeyersSingleton {
private:
    // Private constructor
    MeyersSingleton() {
        cout << "MeyersSingleton created!" << endl;
    }
    
public:
    // Delete copy constructor and assignment operator
    MeyersSingleton(const MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;
    
    // Thread-safe in C++11 and later
    static MeyersSingleton& getInstance() {
        static MeyersSingleton instance;  // Created only once, thread-safe
        return instance;
    }
    
    void doSomething() {
        cout << "MeyersSingleton is working!" << endl;
    }
};

// ========================================================================
// TESTING MULTITHREADING
// ========================================================================
void threadFunction(int threadId) {
    cout << "Thread " << threadId << " requesting instance..." << endl;
    ThreadSafeConfig* config = ThreadSafeConfig::getInstance();
    config->setConfig("Thread" + to_string(threadId), "Value" + to_string(threadId));
}

// ========================================================================
// MAIN FUNCTION - DEMONSTRATION
// ========================================================================
int main() {
    cout << "========== SINGLETON DESIGN PATTERN EXAMPLES ==========" << endl;
    cout << endl;
    
    // 1. Lazy Initialization Example
    cout << "1. LAZY INITIALIZATION:" << endl;
    cout << "Instance created only when first requested" << endl;
    LazyDatabaseConnection* db1 = LazyDatabaseConnection::getInstance();
    LazyDatabaseConnection* db2 = LazyDatabaseConnection::getInstance();
    cout << "db1 address: " << db1 << endl;
    cout << "db2 address: " << db2 << endl;
    cout << "Same instance? " << (db1 == db2 ? "YES" : "NO") << endl;
    db1->query("SELECT * FROM users");
    cout << endl;
    
    // 2. Eager Initialization Example
    cout << "2. EAGER INITIALIZATION:" << endl;
    cout << "Instance created at program start (before main)" << endl;
    EagerLogger* logger1 = EagerLogger::getInstance();
    EagerLogger* logger2 = EagerLogger::getInstance();
    cout << "logger1 address: " << logger1 << endl;
    cout << "logger2 address: " << logger2 << endl;
    cout << "Same instance? " << (logger1 == logger2 ? "YES" : "NO") << endl;
    logger1->log("Application started");
    cout << endl;
    
    // 3. Thread-Safe Singleton with Multithreading
    cout << "3. THREAD-SAFE SINGLETON (Double-Checked Locking):" << endl;
    vector<thread> threads;
    for (int i = 0; i < 5; i++) {
        threads.push_back(thread(threadFunction, i));
    }
    for (auto& th : threads) {
        th.join();
    }
    cout << endl;
    
    // 4. Meyer's Singleton Example
    cout << "4. MEYER'S SINGLETON (C++11 Recommended):" << endl;
    MeyersSingleton& ms1 = MeyersSingleton::getInstance();
    MeyersSingleton& ms2 = MeyersSingleton::getInstance();
    cout << "ms1 address: " << &ms1 << endl;
    cout << "ms2 address: " << &ms2 << endl;
    cout << "Same instance? " << (&ms1 == &ms2 ? "YES" : "NO") << endl;
    ms1.doSomething();
    cout << endl;
    
    cout << "========== COMPARISON ==========" << endl;
    cout << "Lazy: Created when first needed, not thread-safe" << endl;
    cout << "Eager: Created at program start, thread-safe" << endl;
    cout << "Thread-Safe: Lazy + mutex + double-checked locking" << endl;
    cout << "Meyer's: Best approach in C++11+, automatic thread-safety" << endl;
    
    return 0;
}