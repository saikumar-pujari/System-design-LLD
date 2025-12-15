
/*
 * ============================================================================
 * FACTORY DESIGN PATTERN - Complete Guide
 * ============================================================================
 * 
 * WHAT IS FACTORY PATTERN?
 * - A Creational Design Pattern that provides an interface for creating objects
 * - Delegates object creation to factory classes instead of using 'new' directly
 * - Client code doesn't need to know which exact class to instantiate
 * 
 * WHY USE FACTORY PATTERN?
 * - Encapsulates object creation logic
 * - Makes code more flexible and maintainable
 * - Follows SOLID principles (Open/Closed, Single Responsibility)
 * - Easy to add new product types without modifying existing code
 * 
 * ============================================================================
 * THREE TYPES OF FACTORY PATTERNS:
 * ============================================================================
 * 
 * 1. SIMPLE FACTORY (Factory Pattern)
 * ------------------------------------
 * - NOT an official GoF design pattern, but widely used
 * - A single factory class with a method that creates objects based on parameters
 * - Factory has all creation logic in one place
 * 
 * Structure:
 *   Client → Factory (static method) → creates → Product A/B/C
 * 
 * Pros:
 *   + Simple to implement
 *   + Centralizes object creation
 *   + Client code is clean
 * 
 * Cons:
 *   - Violates Open/Closed Principle (need to modify factory for new types)
 *   - Factory class can become large with many if-else statements
 *   - Not very flexible for complex scenarios
 * 
 * Example: Current implementation below (VehicleFactory class)
 * 
 * 
 * 2. FACTORY METHOD PATTERN
 * ---------------------------
 * - Official GoF design pattern
 * - Defines an interface for creating objects, but lets SUBCLASSES decide which class to instantiate
 * - Uses inheritance: factory method is overridden in subclasses
 * - Each concrete factory creates ONE specific product
 * 
 * Structure:
 *   Client → Creator (abstract) ← ConcreteCreatorA/B (override factory method)
 *                     ↓
 *            Product (abstract) ← ConcreteProductA/B
 * 
 * Pros:
 *   + Follows Open/Closed Principle (add new types by creating new subclasses)
 *   + Single Responsibility (each factory creates one type)
 *   + More flexible than Simple Factory
 * 
 * Cons:
 *   - More complex (more classes needed)
 *   - Can lead to class explosion
 * 
 * When to use:
 *   - When you don't know beforehand the exact types of objects
 *   - When you want to provide a library with extension points
 *   - When you want to delegate instantiation to subclasses
 * 
 * Example Use Case:
 *   class VehicleFactory {
 *       virtual Vehicle* createVehicle() = 0;  // Factory Method
 *   };
 *   class CarFactory : public VehicleFactory {
 *       Vehicle* createVehicle() { return new Car(); }
 *   };
 * 
 * 
 * 3. ABSTRACT FACTORY PATTERN
 * -----------------------------
 * - Official GoF design pattern
 * - Provides an interface for creating FAMILIES of related objects
 * - Creates multiple products that work together
 * - Like a "factory of factories"
 * 
 * Structure:
 *   Client → AbstractFactory ← ConcreteFactory1/2
 *                 ↓                    ↓
 *            creates ProductA    creates ProductB
 * 
 * Pros:
 *   + Ensures products from same family work together
 *   + Isolates concrete classes
 *   + Easy to swap entire product families
 *   + Follows Open/Closed Principle
 * 
 * Cons:
 *   - Very complex to implement
 *   - Adding new product types requires changing all factories
 * 
 * When to use:
 *   - When system needs to work with multiple families of products
 *   - When you want to ensure products from same family are used together
 *   - When you want to provide a library of products
 * 
 * Example Use Case:
 *   class VehicleFactory {
 *       virtual Engine* createEngine() = 0;
 *       virtual Tire* createTire() = 0;
 *   };
 *   class LuxuryVehicleFactory : public VehicleFactory {
 *       Engine* createEngine() { return new V8Engine(); }
 *       Tire* createTire() { return new PerformanceTire(); }
 *   };
 * 
 * ============================================================================
 * COMPARISON SUMMARY:
 * ============================================================================
 * 
 * Simple Factory:        One factory → Creates different products
 * Factory Method:        Multiple factories → Each creates one product type
 * Abstract Factory:      Multiple factories → Each creates family of related products
 * 
 * Complexity:    Simple Factory < Factory Method < Abstract Factory
 * Flexibility:   Simple Factory < Factory Method < Abstract Factory
 * 
 * ============================================================================
 * IMPLEMENTATION BELOW: SIMPLE FACTORY PATTERN
 * ============================================================================
 */

#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Abstract Product - Base class for all vehicles
class Vehicle {
public:
    virtual void drive() = 0;
    virtual string getType() = 0;
    virtual ~Vehicle() = default;
};

// Concrete Product 1 - Car
class Car : public Vehicle {
public:
    void drive() override {
        cout << "Driving a car on the road!" << endl;
    }
    
    string getType() override {
        return "Car";
    }
};

// Concrete Product 2 - Bike
class Bike : public Vehicle {
public:
    void drive() override {
        cout << "Riding a bike on the road!" << endl;
    }
    
    string getType() override {
        return "Bike";
    }
};

// Concrete Product 3 - Truck
class Truck : public Vehicle {
public:
    void drive() override {
        cout << "Driving a heavy truck!" << endl;
    }
    
    string getType() override {
        return "Truck";
    }
};

// Factory Class - Creates objects based on input
class VehicleFactory {
public:
    // Factory Method
    static unique_ptr<Vehicle> createVehicle(const string& type) {
        if (type == "Car") {
            return make_unique<Car>();
        }
        else if (type == "Bike") {
            return make_unique<Bike>();
        }
        else if (type == "Truck") {
            return make_unique<Truck>();
        }
        else {
            cout << "Invalid vehicle type!" << endl;
            return nullptr;
        }
    }
};

// Client Code
int main() {

    // auto bike = VehicleFactory::createVehicle("Bike");
    // see man this a typical example for the code ok! here the clinet will request the factory
    //clinets wants a bike-->bike* xyz(name) which is bike* b
    //factory is vehinclefactory::createvehicle('bike') here the factory will createvehicle of bike as requested
    //factory will revice the request as burgerfactory::createburger('type') here the type is any inout of burger

    cout << "=== Factory Design Pattern Demo ===" << endl << endl;
    
    // Create different vehicles using factory
    auto car = VehicleFactory::createVehicle("Car");
    if (car) {
        cout << "Created: " << car->getType() << endl;
        car->drive();
        cout << endl;
    }
    
    auto bike = VehicleFactory::createVehicle("Bike");
    if (bike) {
        cout << "Created: " << bike->getType() << endl;
        bike->drive();
        cout << endl;
    }
    
    auto truck = VehicleFactory::createVehicle("Truck");
    if (truck) {
        cout << "Created: " << truck->getType() << endl;
        truck->drive();
        cout << endl;
    }
    
    // Try invalid type
    auto invalid = VehicleFactory::createVehicle("Plane");
    
    cout << "\n=== Key Advantages ===" << endl;
    cout << "1. Client doesn't need to know concrete classes" << endl;
    cout << "2. Easy to add new vehicle types" << endl;
    cout << "3. Centralized object creation" << endl;
    cout << "4. Follows Open/Closed Principle" << endl;
    
    return 0;
}
