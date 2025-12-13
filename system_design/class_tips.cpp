#include <bits/stdc++.h>
using namespace std;


class paymentservice{
    public:
    double calculate(){
        return 100.0;
    }
};

class savetoDB{
    public:
    void savetodbd(double price){
        cout<<"\nthe value saved in DB are:"<<price<<endl;
    }
};
class invoice{
    public:
    void printinvoice(double price){
        cout<<"the invoice prixe is:"<<price<<endl;
    }
};
class email{
    public:
    void sendmail(double price){
        cout<<"the email is sent of price:"<<price<<endl;
    }
};

class service{
    public:
    void work(){
        cout<<"there is nothing to work here man\n";
    }
};

//passing object to a function!
void dosomething(service& s){
    s.work();
}

class controller{
    public:
    void dosomething(service &s){
        cout<<"controller will handle the service\n";
        s.work();
    }
};
class control{
    service &S;
    public:
    control(service& s):S(s){}
    void handle(){
        cout<<"control will take care of it man\n";
        S.work();
    }
};

class check{
    public:
    int value=0;
};
class increment{
    check& Check;
    public:
    increment(check& c):Check(c){}
    void incrementing(){
        Check.value++;
        cout<<"the check value is:"<<Check.value<<endl;
    }
};

class engine{
    public:
    void start(){
        cout<<"the engine is started\n";
    }
};
class car{
    engine& E;
    public:
    car(engine& e):E(e){}
    void start(){
        cout<<"the car is ready press to start\n";
        E.start();
    }
};
class hummer{
    engine* E;
    public:
    hummer(engine* e):E(e){}
    void start(){
        cout<<"start the car which is hummer man!\n";
        if(E)E->start();
        else cout<<"the car doesnot have any engine man!\n";
    }
};

int main(){
    paymentservice p;
    savetoDB db;
    invoice in;
    email em;
    double price=p.calculate();
    cout<<price;
    db.savetodbd(price);
    in.printinvoice(price);
    em.sendmail(price);
    cout<<"---------------------\n";
    service s;
    dosomething(s);
    controller c;
    c.dosomething(s);
    control ctrl1(s);
    ctrl1.handle();
    cout<<"---------------------\n";
    
    check chk1;
    cout<<chk1.value<<endl;
    increment sa(chk1);
    sa.incrementing();
    sa.incrementing();
    sa.incrementing();
    cout<<"---------------------\n";

    engine e;
    car car1(e);
    car1.start();
    hummer h(&e);
    h.start();
    hummer h1(nullptr);
    h1.start();
    return 0;
}