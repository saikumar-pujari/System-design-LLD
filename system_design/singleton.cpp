#include <bits/stdc++.h>
using namespace std;
class singleton{
    private:
    static singleton* instance;
    static mutex mtx;
    singleton(){
        cout<<"ya boi\n";
    }
    public:
    static singleton* getInstance(){
        lock_guard<mutex>lock(mtx);
        if(instance==nullptr){instance=new singleton();}
          return instance;
    }
};
singleton* singleton::instance=nullptr;
mutex singleton::mtx;
int main(){
  auto s1=singleton::getInstance(); 
  auto s2=singleton::getInstance(); 
  cout<<(s1==s2)<<endl;
    return 0;
}