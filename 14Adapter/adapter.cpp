//适配器模式是一种补偿模式，补救设计上的缺陷
//专栏上有应用举例


//类适配：接口实现
class ITarget{
public:
    virtual void f1()=0;
    virtual void f2()=0;
    virtual void fc()=0;
};

class Adaptee{
public:
    void fa(){};
    void fb(){};
    void fc(){};
};

class Adapter:public Adaptee,public ITarget{
public:
    void f1(){
        Adaptee::fa();
    }

    void f2(){
        //重新实现f2
    }
    //fc()直接复用Adaptee，这是和对象适配器最大的不同

};

//对象适配：组合实现
class Adapter:public ITarget{
private:
    Adaptee* adaptee;
public:
    Adapter(Adaptee* adaptee){
        this->adaptee=adaptee;
    }

    void f1(){
        adaptee->fa();
    }

    void f2(){
        //重新实现f2
    }

    void fc(){
        adaptee->fc();
    }
}

//两者之间的选择
//1、Adaptee接口不多，两者都可以
//2、Adaptee接口很多，Adaptee和ITarget接口定义大部分相同，使用类适配器，可以直接复用Adaptee的接口
//3、                                              不同，使用对象适配器，因为组合更加的灵活







