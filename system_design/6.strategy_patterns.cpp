// DESIGN PATTERNS - STRATEGY PATTERN
// ================================================================================

// Strategy ⟶ Interface
// ↓            ↑
// A  B  C ← Implementations
// ↓
// Context (holds Strategy)
// ↓
// Runtime change


// "The solution to inheritance is not more inheritance"

// PROBLEM WITH INHERITANCE:
// - Using inheritance in system design costs more resources
// - Requires hierarchical structure that continuously updates itself
// - Leads to breaking DRY (Don't Repeat Yourself) principle
// - Creates tight coupling between parent and child classes
// - Changes in parent class affect all child classes (fragile base class)
// - Cannot change behavior at runtime
// - Difficult to maintain and extend

// SOLUTION: STRATEGY DESIGN PATTERN
// - Define the algorithm rather than whole methods
// - Favor composition over inheritance
// - Encapsulate behaviors/algorithms into separate classes

// ================================================================================

// STRATEGY PATTERN EXPLAINED
// ================================================================================

// 1. WHAT IS STRATEGY PATTERN?
//    - Behavioral design pattern
//    - Defines a family of algorithms
//    - Encapsulates each algorithm
//    - Makes them interchangeable
//    - Lets algorithm vary independently from clients that use it

// 2. KEY PRINCIPLES:
//    - "Program to an interface, not an implementation"
//    - "Favor composition over inheritance"
//    - Separate what changes from what stays the same

// 3. COMPONENTS:
//    A. Strategy Interface: Defines common interface for all algorithms
//    B. Concrete Strategies: Implement different variations of algorithm
//    C. Context: Maintains reference to Strategy object and delegates to it

// ================================================================================

// CLASSIC EXAMPLE: DUCK SIMULATION
// ================================================================================

// PROBLEM WITH INHERITANCE APPROACH:

// class Duck {
//     quack() { }
//     swim() { }
//     fly() { }  // Problem: Not all ducks fly!
// }

// class MallardDuck extends Duck { }
// class RubberDuck extends Duck {
//     fly() { /* Cannot fly! */ }  // Must override
//     quack() { /* Squeaks instead */ }  // Must override
// }
// class WoodenDuck extends Duck {
//     fly() { /* Cannot fly! */ }  // Duplicate code
//     quack() { /* No sound! */ }  // Duplicate code
// }

// Issues:
// - Code duplication in overrides
// - Adding new behavior affects all subclasses
// - Runtime behavior changes impossible
// - Violates Open/Closed Principle

// SOLUTION WITH STRATEGY PATTERN:

// Step 1: Define Strategy Interfaces

// interface FlyBehavior {
//     fly();
// }

// interface QuackBehavior {
//     quack();
// }

// Step 2: Create Concrete Strategy Classes

// // Flying Strategies
// class FlyWithWings implements FlyBehavior {
//     fly() { 
//         print("Flying with wings!") 
//     }
// }

// class FlyNoWay implements FlyBehavior {
//     fly() { 
//         print("Cannot fly") 
//     }
// }

// class FlyRocketPowered implements FlyBehavior {
//     fly() { 
//         print("Flying with rocket!") 
//     }
// }

// // Quacking Strategies
// class Quack implements QuackBehavior {
//     quack() { 
//         print("Quack quack!") 
//     }
// }

// class Squeak implements QuackBehavior {
//     quack() { 
//         print("Squeak!") 
//     }
// }

// class MuteQuack implements QuackBehavior {
//     quack() { 
//         print("< Silence >") 
//     }
// }

// Step 3: Modify Duck Class to Use Composition

// class Duck {
//     FlyBehavior flyBehavior;      // Has-a relationship
//     QuackBehavior quackBehavior;  // Has-a relationship
    
//     performFly() {
//         flyBehavior.fly();  // Delegate to strategy
//     }
    
//     performQuack() {
//         quackBehavior.quack();  // Delegate to strategy
//     }
    
//     // Allow runtime behavior change
//     setFlyBehavior(FlyBehavior fb) {
//         this.flyBehavior = fb;
//     }
    
//     setQuackBehavior(QuackBehavior qb) {
//         this.quackBehavior = qb;
//     }
    
//     swim() {
//         print("All ducks swim!");
//     }
// }

// Step 4: Create Specific Duck Types

// class MallardDuck extends Duck {
//     constructor() {
//         flyBehavior = new FlyWithWings();
//         quackBehavior = new Quack();
//     }
// }

// class RubberDuck extends Duck {
//     constructor() {
//         flyBehavior = new FlyNoWay();
//         quackBehavior = new Squeak();
//     }
// }

// class WoodenDuck extends Duck {
//     constructor() {
//         flyBehavior = new FlyNoWay();
//         quackBehavior = new MuteQuack();
//     }
// }

// Step 5: Usage

// Duck mallard = new MallardDuck();
// mallard.performQuack();  // Output: Quack quack!
// mallard.performFly();    // Output: Flying with wings!

// // Runtime behavior change!
// mallard.setFlyBehavior(new FlyRocketPowered());
// mallard.performFly();    // Output: Flying with rocket!

// ================================================================================

// REAL-WORLD EXAMPLES
// ================================================================================

// 1. PAYMENT PROCESSING SYSTEM:

// interface PaymentStrategy {
//     pay(amount);
// }

// class CreditCardPayment implements PaymentStrategy {
//     pay(amount) { /* Process credit card */ }
// }

// class PayPalPayment implements PaymentStrategy {
//     pay(amount) { /* Process PayPal */ }
// }

// class CryptoPayment implements PaymentStrategy {
//     pay(amount) { /* Process cryptocurrency */ }
// }

// class ShoppingCart {
//     PaymentStrategy paymentStrategy;
    
//     checkout(amount) {
//         paymentStrategy.pay(amount);  // Flexible payment method
//     }
// }

// 2. COMPRESSION ALGORITHMS:

// interface CompressionStrategy {
//     compress(file);
// }

// class ZipCompression implements CompressionStrategy { }
// class RarCompression implements CompressionStrategy { }
// class GzipCompression implements CompressionStrategy { }

// class FileCompressor {
//     CompressionStrategy strategy;
    
//     compressFile(file) {
//         strategy.compress(file);
//     }
// }

// 3. SORTING ALGORITHMS:

// interface SortStrategy {
//     sort(data);
// }

// class QuickSort implements SortStrategy { }
// class MergeSort implements SortStrategy { }
// class BubbleSort implements SortStrategy { }

// class DataSorter {
//     SortStrategy strategy;
    
//     sortData(data) {
//         strategy.sort(data);
//     }
// }

// 4. NAVIGATION SYSTEMS:

// interface RouteStrategy {
//     buildRoute(start, end);
// }

// class CarRoute implements RouteStrategy { }
// class WalkingRoute implements RouteStrategy { }
// class PublicTransportRoute implements RouteStrategy { }
// class BikeRoute implements RouteStrategy { }

// 5. LOGGING SYSTEMS:

// interface LogStrategy {
//     log(message);
// }

// class FileLogger implements LogStrategy { }
// class DatabaseLogger implements LogStrategy { }
// class ConsoleLogger implements LogStrategy { }
// class CloudLogger implements LogStrategy { }

// ================================================================================

// ADVANTAGES OF STRATEGY PATTERN
// ================================================================================

// 1. FLEXIBILITY:
//    - Switch algorithms at runtime
//    - Easy to add new strategies without modifying existing code

// 2. MAINTAINABILITY:
//    - Each strategy is independent
//    - Changes to one strategy don't affect others
//    - Easier to test individual strategies

// 3. REDUCES CONDITIONAL STATEMENTS:
//    - Eliminates complex if-else or switch statements
//    - Each strategy encapsulates its own logic

// 4. FOLLOWS SOLID PRINCIPLES:
//    - Single Responsibility: Each strategy does one thing
//    - Open/Closed: Open for extension, closed for modification
//    - Dependency Inversion: Depend on abstractions

// 5. CODE REUSABILITY:
//    - Strategies can be reused across different contexts
//    - Mix and match behaviors as needed

// 6. CLEAN CODE:
//    - Separates concerns clearly
//    - More readable and understandable
//    - Reduces code duplication

// ================================================================================

// DISADVANTAGES OF STRATEGY PATTERN
// ================================================================================

// 1. INCREASED NUMBER OF CLASSES:
//    - More classes to manage
//    - Can be overkill for simple scenarios

// 2. CLIENT AWARENESS:
//    - Client must be aware of different strategies
//    - Must understand which strategy to use when

// 3. COMMUNICATION OVERHEAD:
//    - Context and strategies must communicate
//    - May pass unnecessary data

// 4. COMPLEXITY:
//    - Adds abstraction layers
//    - May be harder for beginners to understand

// ================================================================================

// WHEN TO USE STRATEGY PATTERN
// ================================================================================

// ✓ Use When:
// - Many related classes differ only in behavior
// - Need different variants of an algorithm
// - Algorithm uses data client shouldn't know about
// - Class has multiple behaviors with conditional statements
// - Want to change behavior at runtime

// ✗ Don't Use When:
// - Only have one or two algorithms
// - Algorithms don't change
// - Simple if-else is sufficient
// - Overhead of pattern exceeds benefits

// ================================================================================

// STRATEGY VS OTHER PATTERNS
// ================================================================================

// STRATEGY vs STATE PATTERN:
// - Strategy: Client chooses strategy explicitly
// - State: Context changes state automatically based on internal state

// STRATEGY vs Template Method:
// - Strategy: Uses composition (has-a)
// - Template: Uses inheritance (is-a)
// - Strategy: Can switch at runtime
// - Template: Fixed at compile time

// STRATEGY vs Factory:
// - Strategy: About behavior/algorithms
// - Factory: About object creation
// - Can be used together

// ================================================================================

// IMPLEMENTATION CHECKLIST
// ================================================================================

// 1. ☐ Identify the algorithm/behavior that varies
// 2. ☐ Create strategy interface with common method
// 3. ☐ Implement concrete strategy classes
// 4. ☐ Modify context class to use composition
// 5. ☐ Add method to change strategy at runtime (optional)
// 6. ☐ Initialize context with default strategy
// 7. ☐ Test each strategy independently
// 8. ☐ Test runtime strategy switching

// ================================================================================

// KEY TAKEAWAYS
// ================================================================================

// 1. "The solution to inheritance is not more inheritance"
// 2. Define algorithms/behaviors, not whole monolithic methods
// 3. Favor composition over inheritance
// 4. Program to interfaces, not implementations
// 5. Encapsulate what varies
// 6. Makes code flexible, maintainable, and testable
// 7. Enables runtime behavior changes
// 8. Follows Open/Closed Principle
// 9. Essential for scalable system design

// ================================================================================


#include <iostream>
using namespace std;

// --- Strategy Interface for Walk ---
class WalkableRobot {
public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {}
};

// --- Concrete Strategies for walk ---
class NormalWalk : public WalkableRobot {
public:
    void walk() override { 
        cout << "Walking normally..." << endl; 
    }
};

class NoWalk : public WalkableRobot {
public:
    void walk() override { 
        cout << "Cannot walk." << endl; 
    }
};


// --- Strategy Interface for Talk ---
class TalkableRobot {
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {}
};

// --- Concrete Strategies for Talk ---
class NormalTalk : public TalkableRobot {
public:
    void talk() override { 
        cout << "Talking normally..." << endl; 
    }
};

class NoTalk : public TalkableRobot {
public:
    void talk() override { 
        cout << "Cannot talk." << endl; 
    }
};

// --- Strategy Interface for Fly ---
class FlyableRobot {
public:
    virtual void fly() = 0;
    virtual ~FlyableRobot() {}
};

class NormalFly : public FlyableRobot {
public:
    void fly() override { 
        cout << "Flying normally..." << endl; 
    }
};

class NoFly : public FlyableRobot {
public:
    void fly() override { 
        cout << "Cannot fly." << endl; 
    }
};

// --- Robot Base Class ---
class Robot {
protected:
    WalkableRobot* walkBehavior;
    TalkableRobot* talkBehavior;
    FlyableRobot* flyBehavior;

public:
    Robot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f) {
        this->walkBehavior = w;
        this->talkBehavior = t;
        this->flyBehavior = f;
    }
       
    void walk() { 
        walkBehavior->walk(); 
    }
    void talk() { 
        talkBehavior->talk(); 
    }
    void fly() { 
        flyBehavior->fly(); 
    }

    virtual void projection() = 0; // Abstract method for subclasses
};

// --- Concrete Robot Types ---
class CompanionRobot : public Robot {
public:
    CompanionRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f)
        : Robot(w, t, f) {}

    void projection() override {
        cout << "Displaying friendly companion features..." << endl;
    }
};

class WorkerRobot : public Robot {
public:
    WorkerRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f)
        : Robot(w, t, f) {}

    void projection() override {
        cout << "Displaying worker efficiency stats..." << endl;
    }
};

// --- Main Function ---
int main() {
    Robot *robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();

    cout << "--------------------" << endl;

    Robot *robot2 = new WorkerRobot(new NoWalk(), new NoTalk(), new NormalFly());
    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->projection();

    return 0;
}
