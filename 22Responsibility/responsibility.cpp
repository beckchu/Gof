#include <string>
#include<iostream>

using namespace std;


//模板设计模式：基于继承实现
class AbstractClass{
public:
    void templateMethod() final{//此方法禁用继承,感觉override和final在这个IDE中有问题 final
        //....
        method1();
        //....
        method2();
    }

protected:
    virtual void method1()=0;
    virtual void method2()=0;
};

class ConcreteClass1:public AbstractClass{
protected:
    void method1(){

    }
    void method2(){

    }
};

class ConcreteClass2:public AbstractClass{
protected:
    void method1(){

    }
    void method2(){

    }
};
//扩展：业务流程固定：eg：http解析，提供扩展点扩展，
//
//复用：算法骨架固定，利用继承实现代码的复用

//复用和扩展相差不大


class AbstractClass1{
public:
    void templateMethod1(){//final
        //...
        method1();
        //...
        method2();
    }

    void templateMethod2(){
        //
        method3();
        //
        method4();
    }

protected:
    virtual void method1()=0;
    virtual void method2()=0;
    virtual void method3()=0;
    virtual void method4()=0;

};

//如果按照模板设计模式来的话，模板方法只实用了部分函数，但是子类要把所有virtual方法实现一遍，相当徒劳

//使用adapter模式解决

class Adapter:public AbstractClass1{
protected:
    void method1(){
        cout<<"Adapter method1"<<endl;
    }

    void method2(){
        cout<<"Adapter method2"<<endl;
    }

    void method3(){
        cout<<"Adapter method3"<<endl;
    }

    void method4(){
        cout<<"Adapter method4"<<endl;
    }

};

class ConcreteClass12:public Adapter{
protected:
    void method1(){
        cout<<"ConcreteClass12 method1"<<endl;
    }

    void method2(){
        cout<<"ConcreteClass12 method2"<<endl;
    }
};

class ConcreteClass34:public Adapter{
protected:
    void method3(){
        cout<<"ConcreteClass34 method3"<<endl;
    }

    void method4(){
        cout<<"ConcreteClass34 method4"<<endl;
    }
};

int main(){
    ConcreteClass12 c;
    c.templateMethod1();
    c.templateMethod2();

    ConcreteClass34 c2;
    c2.templateMethod1();
    c2.templateMethod2();
    return 1;
}

