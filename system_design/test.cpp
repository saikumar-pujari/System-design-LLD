#include <bits/stdc++.h>
using namespace std;

class paymentsystem{
    public:
    virtual void pay()=0;
    virtual ~paymentsystem(){}
};

class UPI:public paymentsystem{
    public:
    void pay() override{
        cout<<"pay using UPI\n";
    }
};

class CARD:public paymentsystem{
    public:
    void pay() override{
        cout<<"pay using card\n";
    }
};

class paymentthrogh{
    public:
    void process(paymentsystem& pay){
        pay.pay();
    }
};

class shape{
    public:
    virtual void area()=0;
    virtual ~shape(){}
};

class circle:public shape{
    public:
    void area() override{
        cout<<10<<endl;
    }
};

class triangle:public shape{
    public:
    void area() override{
        cout<<30<<endl;
    }
};

class square:public shape{
    public:
    void area() override{
        cout<<40<<endl;
    }
};
class area{
    public:
    void areacalculate(shape& s){
        s.area();
    }
};

class MySQLDatabase {
public:
    void connect() {
        cout << "Connected to MySQL\n";
    }
};

class UserService {
    MySQLDatabase db;   // ❌ concrete dependency
public:
    void run() {
        db.connect();
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    paymentthrogh what;
    UPI upi;
    CARD card;
    what.process(upi);
    what.process(card);


    area a;
    circle c;
    triangle t;
    square s;
    a.areacalculate(c);
    a.areacalculate(t);
    a.areacalculate(s);

    UserService service;
    service.run();
    return 0;
}