// #include <bits/stdc++.h>
// using namespace std;

// class paymentstrategy{
//     public:
//     virtual void pay(double amount)=0;
//     // void ~paymentstrategy(){}
// };

// class upi:public paymentstrategy{
//     public:
//     void pay(double amount)override{
//         cout<<"payment done by UPI:"<<amount<<endl;
//     }
// };
// class wallet:public paymentstrategy{
//     public:
//     void pay(double amount)override{
//         cout<<"payment done by wallet:"<<amount<<endl;
//     }
// };
// class card:public paymentstrategy{
//     public:
//     void pay(double amount)override{
//         cout<<"payment done by card:"<<amount<<endl;
//     }
// };
// class paymentcontext{
//     paymentstrategy& pay;
//     public:
//     paymentcontext(paymentstrategy& p):pay(p){}
//     void exceute(double amount){
//         pay.pay(amount);
//     }
// };

// int main(){
    
//     // paymentstrategy pay(upi);
//     upi upi2;
//     paymentcontext context(upi2);
//     context.exceute(100);
//     card card;
//     paymentcontext context1(card);
//     context1.exceute(100);
//     return 0;
// }

// #include <bits/stdc++.h>
// using namespace std;

// class paymentservice{
//     public:
//     virtual void pay(double amount)=0;
// };
// class upi:public paymentservice{
//     public:
//     void pay(double amount) override{
//         cout<<"the payment is done throgh UPI of amount:"<<amount<<endl;
//     }
// };
// class card:public paymentservice{
//     public:
//     void pay(double amount) override{
//         cout<<"the payment is done throgh card of amount:"<<amount<<endl;
//     }
// };

// class paymentcontext{
//     paymentservice& pay;
//     public:
//     paymentcontext(paymentservice& p):pay(p){}
//     void payment(double amount){
//         pay.pay(amount);
//     }
// };

// int main(){
//     upi upi;
//     card card;
//     paymentcontext payment(upi);
//     paymentcontext payment1(card);
//     payment.payment(100);
//     payment1.payment(100);

//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

// class walking{
//     public:
//     virtual void move()=0;
// };
// class walk:public walking{
//     public:
//     void move() override{
//         cout<<"walking the robot man!\n";
//     }
// };
// class roll:public walking{
//     public:
//     void move() override{
//         cout<<"rolling the robot man!\n";
//     }
// };
// class robot{
//     walking* walk;
//     public:
//     robot(walking* w):walk(w){}
//     void move(){
//         walk->move();
//     }
// };


// class attackstragety{
//     public:
//     virtual void attack()=0;
// };
// class punchattack:public attackstragety{
//     public:
//     void attack() override{
//         cout<<"i will attack with the punch\n";
//     }
// };
// class lasserattack:public attackstragety{
//     public:
//     void attack() override{
//         cout<<"i will attack with the laser\n";
//     }
// };
// class fighterrobot{
//     attackstragety* attack;
//     public:
//     fighterrobot(attackstragety* a):attack(a){}
//     void fight(){
//         attack->attack();
//     }
//     void setattacker(attackstragety* a){
//         delete attack;
//         attack=a;
//     }
// };
// class jumpstrategy{
//     public:
//     virtual void jump()=0;
//     virtual ~jumpstrategy(){}
// };
// class highjump:public jumpstrategy{
//     public:
//     void jump()override{
//         cout<<"high jump here man\n";
//     }
// };
// class lowjump:public jumpstrategy{
//     public:
//     void jump()override{
//         cout<<"low jump here man\n";
//     }
// };
// class runstrategy{
//     public:
//     virtual void run()=0;
//     virtual ~runstrategy(){}
// };
// class fastrun:public runstrategy{
//     public:
//     void run()override{
//         cout<<"fast run here man\n";
//     }
// };
// class slowrun:public runstrategy{
//     public:
//     void run()override{
//         cout<<"slow run here man\n";
//     }
// };
// class gamecharacter{
//     runstrategy* run;
//     jumpstrategy* jump;
//     public:
//     gamecharacter(runstrategy* r,jumpstrategy* j):run(r),jump(j){}
//     virtual ~gamecharacter(){
//         delete run;
//         delete jump;
//     }
//     void performjump(){
//         jump->jump();
//     }
//     void performrun(){
//         run->run();
//     }
//     virtual void display()=0;
// };
// class animal:public gamecharacter{
//     public:
//     animal():gamecharacter(new fastrun(),new highjump()){}
//     void display() override{
//         cout<<"i am a animal\n";
//     }
// };
// class tank:public gamecharacter{
//     public:
//     tank():
//         gamecharacter(new slowrun(),new lowjump()){}
//     void display() override{
//         cout<<"i am a tank\n";
//     }
    
// };


class movestrategy{
    public:
    virtual void move()=0;
    virtual ~movestrategy(){}
};
class walkable:public movestrategy{
    public:
    void move() override{
        cout<<"i am walking!!\n";
    }
};
class nommove:public movestrategy{
    public:
    void move() override{
        cout<<"i am not able to walk!!\n";
    }
};
class thinktrategy{
    public:
    virtual void think()=0;
    virtual ~thinktrategy(){}
};
class chatgpt:public thinktrategy{
    public:
    void think() override{
        cout<<"i am thinking using the chatgpt!!\n";
    }
};
class notthink:public thinktrategy{
    public:
    void think() override{
        cout<<"i am not able to think using the chatgpt!!\n";
    }
};
class robot{
    thinktrategy* think;
    movestrategy* move;
    public:
    robot(movestrategy* m,thinktrategy* t):move(m),think(t){}
    virtual ~robot(){
        delete move;
        delete think;
    }
    void moving(){
        move->move();
    }
    void thinking(){
        think->think();
    }
    void setmoving(movestrategy* m){
        delete move;
        move=m;
    }
    virtual void display()=0;
};
class tesla:public robot{
    public:
    tesla():robot(new walkable(),new notthink()){}
    void display(){
        cout<<"see i can walk bbut i dont have brain yet\n";
    }
};
class claude:public robot{
    public:
    claude():robot(new nommove(),new chatgpt()){}
    void display(){
        cout<<"see i can think bbut i dont have legs yet\n";
    }
};
int main(){
    // robot r1(new walk());
    // robot r2(new roll());
    // r1.move();
    // r2.move();

    // fighterrobot fight(new lasserattack());
    // fighterrobot fight1(new punchattack());
    // fight.fight();
    // fight1.fight();
    // fight.setattacker(new punchattack());
    // fight.fight();

    // gamecharacter* a=new animal;
    // a->performjump();
    // a->performrun();
    // a->display();
    // delete a;

    // tank t;
    // t.performjump();
    // t.performrun();
    // t.display();

    robot* b=new tesla;
    robot* c=new claude;
    b->thinking();
    b->moving();
    b->display();
    b->setmoving(new nommove());
    b->moving();
    c->thinking();
    c->moving();
    c->display();
    delete b;
    delete c;

    return 0;
}