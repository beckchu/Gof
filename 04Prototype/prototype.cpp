//就是将原有的复杂对象（创建成本比较大：数据从慢速IO获取）进行拷贝构造，或移动构造，深拷贝和浅拷贝
//对c++来说没啥用处

#include <stdio.h>


class Prototype{
public:
    Prototype(){}
    virtual ~Prototype(){}

    virtual Prototype* clone()=0;
};

class ConcretePrototype:public Prototype{
public:
    ConcretePrototype(){}
    ~ConcretePrototype(){}

    Prototype* clone(){
        return new ConcretePrototype(*this);
    }
private:
    ConcretePrototype(const ConcretePrototype&){
        fprintf(stderr,"ConcretePrototype copy construct!\n");
    }
};

