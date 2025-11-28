
/*
╔═══════════════════════════════════════════════════════════════════════════╗
║                        SOLID PRINCIPLES - COMPLETE GUIDE                  ║
║                  Memory Trick: "SOLID" = 5 Key Principles                 ║
╚═══════════════════════════════════════════════════════════════════════════╝

SOLID is an acronym for 5 design principles that make software designs more:
    - Understandable
    - Flexible
    - Maintainable

S - Single Responsibility Principle (SRP)
O - Open/Closed Principle (OCP)
L - Liskov Substitution Principle (LSP)
I - Interface Segregation Principle (ISP)
D - Dependency Inversion Principle (DIP)
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

/*
═══════════════════════════════════════════════════════════════════════════
    1. SINGLE RESPONSIBILITY PRINCIPLE (SRP)
═══════════════════════════════════════════════════════════════════════════

DEFINITION: A class should have only ONE reason to change.
            Each class should have only ONE job/responsibility.

TRICK: "One Class, One Job" - If you can describe a class with "AND", 
       it's doing too much!

WHY?: 
    - Easier to understand
    - Easier to test
    - Less coupling
    - Easier to maintain
*/

// ❌ BAD EXAMPLE: Multiple Responsibilities
class UserBad {
public:
    string name;
    string email;
    
    // Responsibility 1: User data management
    void setName(string n) { name = n; }
    
    // Responsibility 2: Database operations
    void saveToDatabase() {
        cout << "Saving " << name << " to database..." << endl;
    }
    
    // Responsibility 3: Email operations
    void sendEmail(string message) {
        cout << "Sending email to " << email << ": " << message << endl;
    }
    
    // Responsibility 4: Logging
    void log(string action) {
        cout << "LOG: User " << name << " performed " << action << endl;
    }
};

// ✅ GOOD EXAMPLE: Single Responsibility for each class
class User {
private:
    string name;
    string email;
    
public:
    User(string n, string e) : name(n), email(e) {}
    string getName() const { return name; }
    string getEmail() const { return email; }
    void setName(string n) { name = n; }
};

class UserRepository {
public:
    void save(const User& user) {
        cout << "Saving " << user.getName() << " to database..." << endl;
    }
};

class EmailService {
public:
    void sendEmail(const User& user, string message) {
        cout << "Sending email to " << user.getEmail() << ": " << message << endl;
    }
};

class Logger {
public:
    void log(string message) {
        cout << "LOG: " << message << endl;
    }
};

/*
═══════════════════════════════════════════════════════════════════════════
    2. OPEN/CLOSED PRINCIPLE (OCP)
═══════════════════════════════════════════════════════════════════════════

DEFINITION: Software entities should be OPEN for extension but CLOSED for modification.
            You should be able to add new functionality without changing existing code.

TRICK: "Extend, Don't Edit" - Use inheritance/polymorphism instead of modifying code

WHY?: 
    - Prevents breaking existing functionality
    - Promotes code reusability
    - Easier to add new features
*/

// ❌ BAD EXAMPLE: Need to modify class for new shape types
class AreaCalculatorBad {
public:
    double calculateArea(string shapeType, double dimension1, double dimension2 = 0) {
        if (shapeType == "circle") {
            return 3.14 * dimension1 * dimension1;
        } else if (shapeType == "rectangle") {
            return dimension1 * dimension2;
        } else if (shapeType == "triangle") {  // Need to modify for each new shape!
            return 0.5 * dimension1 * dimension2;
        }
        return 0;
    }
};

// ✅ GOOD EXAMPLE: Open for extension, closed for modification
class Shape {
public:
    virtual double calculateArea() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double calculateArea() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double calculateArea() const override {
        return width * height;
    }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double calculateArea() const override {
        return 0.5 * base * height;
    }
};

// Can add new shapes without modifying existing code!
class AreaCalculator {
public:
    double calculate(const Shape& shape) {
        return shape.calculateArea();
    }
};

/*
═══════════════════════════════════════════════════════════════════════════
    3. LISKOV SUBSTITUTION PRINCIPLE (LSP)
═══════════════════════════════════════════════════════════════════════════

DEFINITION: Objects of a superclass should be replaceable with objects of its 
            subclasses without breaking the application.

TRICK: "Child Should Act Like Parent" - If it quacks like a duck but needs 
       batteries, it's probably breaking LSP!

WHY?: 
    - Ensures proper inheritance
    - Prevents unexpected behavior
    - Makes code more reliable
*/

// ❌ BAD EXAMPLE: Square violates LSP (Rectangle's behavior)
class RectangleBad {
protected:
    int width, height;
public:
    virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }
    int getArea() const { return width * height; }
};

class SquareBad : public RectangleBad {
public:
    void setWidth(int w) override {
        width = height = w;  // Changes both! Unexpected behavior
    }
    void setHeight(int h) override {
        width = height = h;  // Changes both! Unexpected behavior
    }
};

// This breaks: Expected area = 50, but Square gives 25!
// RectangleBad* r = new SquareBad();
// r->setWidth(5);
// r->setHeight(10);
// r->getArea(); // Expected 50, but gets 100 for square!

// ✅ GOOD EXAMPLE: Proper abstraction
class ShapeBase {
public:
    virtual int getArea() const = 0;
    virtual ~ShapeBase() = default;
};

class RectangleGood : public ShapeBase {
protected:
    int width, height;
public:
    RectangleGood(int w, int h) : width(w), height(h) {}
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    int getArea() const override { return width * height; }
};

class SquareGood : public ShapeBase {
private:
    int side;
public:
    SquareGood(int s) : side(s) {}
    void setSide(int s) { side = s; }
    int getArea() const override { return side * side; }
};

/*
═══════════════════════════════════════════════════════════════════════════
    4. INTERFACE SEGREGATION PRINCIPLE (ISP)
═══════════════════════════════════════════════════════════════════════════

DEFINITION: No client should be forced to depend on methods it does not use.
            Many specific interfaces are better than one general-purpose interface.

TRICK: "Small Focused Interfaces" - Don't force clients to implement what they don't need!

WHY?: 
    - Reduces unnecessary dependencies
    - More flexible design
    - Easier to understand and implement
*/

// ❌ BAD EXAMPLE: Fat interface forces unnecessary implementations
class WorkerBad {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
    virtual ~WorkerBad() = default;
};

class HumanWorker : public WorkerBad {
public:
    void work() override { cout << "Human working..." << endl; }
    void eat() override { cout << "Human eating..." << endl; }
    void sleep() override { cout << "Human sleeping..." << endl; }
};

class RobotWorker : public WorkerBad {
public:
    void work() override { cout << "Robot working..." << endl; }
    void eat() override { /* Robot doesn't eat! Forced to implement */ }
    void sleep() override { /* Robot doesn't sleep! Forced to implement */ }
};

// ✅ GOOD EXAMPLE: Segregated interfaces
class Workable {
public:
    virtual void work() = 0;
    virtual ~Workable() = default;
};

class Eatable {
public:
    virtual void eat() = 0;
    virtual ~Eatable() = default;
};

class Sleepable {
public:
    virtual void sleep() = 0;
    virtual ~Sleepable() = default;
};

class HumanWorkerGood : public Workable, public Eatable, public Sleepable {
public:
    void work() override { cout << "Human working..." << endl; }
    void eat() override { cout << "Human eating..." << endl; }
    void sleep() override { cout << "Human sleeping..." << endl; }
};

class RobotWorkerGood : public Workable {
public:
    void work() override { cout << "Robot working 24/7..." << endl; }
    // Robot only implements what it needs!
};

/*
═══════════════════════════════════════════════════════════════════════════
    5. DEPENDENCY INVERSION PRINCIPLE (DIP)
═══════════════════════════════════════════════════════════════════════════

DEFINITION: 
    A. High-level modules should not depend on low-level modules. 
       Both should depend on abstractions.
    B. Abstractions should not depend on details. 
       Details should depend on abstractions.

TRICK: "Depend on Abstractions, Not Concretions" - Use interfaces/abstract classes!

WHY?: 
    - Reduces coupling
    - Makes code more flexible
    - Easier to test (can mock dependencies)
    - Easier to swap implementations
*/

// ❌ BAD EXAMPLE: High-level class depends on concrete low-level class
class MySQLDatabase {
public:
    void connect() { cout << "Connected to MySQL" << endl; }
    void save(string data) { cout << "Saving to MySQL: " << data << endl; }
};

class UserServiceBad {
private:
    MySQLDatabase db;  // Tightly coupled to MySQL!
public:
    void saveUser(string userData) {
        db.connect();
        db.save(userData);
    }
    // If we want to switch to PostgreSQL, we need to modify this class!
};

// ✅ GOOD EXAMPLE: Both depend on abstraction
class Database {
public:
    virtual void connect() = 0;
    virtual void save(string data) = 0;
    virtual ~Database() = default;
};

class MySQLDatabaseGood : public Database {
public:
    void connect() override { cout << "Connected to MySQL" << endl; }
    void save(string data) override { cout << "Saving to MySQL: " << data << endl; }
};

class PostgreSQLDatabase : public Database {
public:
    void connect() override { cout << "Connected to PostgreSQL" << endl; }
    void save(string data) override { cout << "Saving to PostgreSQL: " << data << endl; }
};

class MongoDatabase : public Database {
public:
    void connect() override { cout << "Connected to MongoDB" << endl; }
    void save(string data) override { cout << "Saving to MongoDB: " << data << endl; }
};

class UserServiceGood {
private:
    Database* db;  // Depends on abstraction!
public:
    UserServiceGood(Database* database) : db(database) {}
    
    void saveUser(string userData) {
        db->connect();
        db->save(userData);
    }
    // Can easily switch database without modifying this class!
};

/*
═══════════════════════════════════════════════════════════════════════════
    DEMONSTRATION & TESTING
═══════════════════════════════════════════════════════════════════════════
*/

int main() {
    cout << "\n" << string(75, '=') << endl;
    cout << "SOLID PRINCIPLES DEMONSTRATION" << endl;
    cout << string(75, '=') << endl;
    
    // 1. SRP Demo
    cout << "\n1. SINGLE RESPONSIBILITY PRINCIPLE:" << endl;
    cout << string(50, '-') << endl;
    User user("Alice", "alice@example.com");
    UserRepository repo;
    EmailService emailSvc;
    Logger logger;
    
    repo.save(user);
    emailSvc.sendEmail(user, "Welcome!");
    logger.log("User created: " + user.getName());
    
    // 2. OCP Demo
    cout << "\n2. OPEN/CLOSED PRINCIPLE:" << endl;
    cout << string(50, '-') << endl;
    Circle circle(5);
    Rectangle rect(4, 6);
    Triangle tri(3, 4);
    AreaCalculator calc;
    
    cout << "Circle area: " << calc.calculate(circle) << endl;
    cout << "Rectangle area: " << calc.calculate(rect) << endl;
    cout << "Triangle area: " << calc.calculate(tri) << endl;
    
    // 3. LSP Demo
    cout << "\n3. LISKOV SUBSTITUTION PRINCIPLE:" << endl;
    cout << string(50, '-') << endl;
    RectangleGood rectLSP(5, 10);
    SquareGood sqLSP(5);
    cout << "Rectangle area: " << rectLSP.getArea() << endl;
    cout << "Square area: " << sqLSP.getArea() << endl;
    
    // 4. ISP Demo
    cout << "\n4. INTERFACE SEGREGATION PRINCIPLE:" << endl;
    cout << string(50, '-') << endl;
    HumanWorkerGood human;
    RobotWorkerGood robot;
    human.work();
    human.eat();
    robot.work();
    
    // 5. DIP Demo
    cout << "\n5. DEPENDENCY INVERSION PRINCIPLE:" << endl;
    cout << string(50, '-') << endl;
    MySQLDatabaseGood mysql;
    PostgreSQLDatabase postgres;
    MongoDatabase mongo;
    
    UserServiceGood service1(&mysql);
    service1.saveUser("User1");
    
    UserServiceGood service2(&postgres);
    service2.saveUser("User2");
    
    UserServiceGood service3(&mongo);
    service3.saveUser("User3");
    
    cout << "\n" << string(75, '=') << endl;
    cout << "SUMMARY - Remember: SOLID" << endl;
    cout << string(75, '=') << endl;
    cout << "S - One Class, One Job" << endl;
    cout << "O - Extend, Don't Edit" << endl;
    cout << "L - Child Should Act Like Parent" << endl;
    cout << "I - Small Focused Interfaces" << endl;
    cout << "D - Depend on Abstractions, Not Concretions" << endl;
    cout << string(75, '=') << endl;
    
    return 0;
}
