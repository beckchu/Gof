
#include<string>

using namespace std;

//建造者模式：构造函数的参数很多，参数间有依赖关系，避免对象之间的无效状态，创建同一种对象
//工厂模式：创建不同对象
//建造者和原类的代码有重复，逼不得已不需要使用
class ResourcePoolConfig{
private:
    string name;
    int maxTotal;
    int maxIdle;
    int minIdle;

public:
    static class Builder{//建造者
    public:
        ResourcePoolConfig* build(int maxIdle=DEFAULT_MAX_IDLE,int maxTotal=DEFAULT_MAX_TOTAL,int minIdle=DEFAULT_MIN_IDLE){
            //对参数的初始化和校验都可以放在这里
            if(name.size()==0){
                throw "";
            }
            if(maxIdle>maxTotal){
                throw "";
            }
            if (minIdle>maxTotal  || minIdle>maxIdle){
                throw "";
            }
            return new ResourcePoolConfig(this);
        }

        Builder& setName(string name){
            if(name.size()==0){
                throw "";
            }
            this->name=name;
            return *this;
        }

        Builder& setMaxTotal(int maxTotal){
            if(maxTotal<=0){
                throw "...";
            }
            this->maxTotal=maxTotal;
            return *this;
        }

        Builder& setMaxIdle(int maxIdle){
            if(maxIdle<0){
                throw "...";
            }
            this->maxIdle=maxIdle;
            return *this;
        }

        Builder& setMinIdle(int minIdle){
            if(minIdle<0){
                throw "...";
            }
            this->minIdle=minIdle;
            return *this;
        }

    private:
        static const int DEFAULT_MAX_TOTAL;
        static const int DEFAULT_MAX_IDLE;
        static const int DEFAULT_MIN_IDLE;
    public:
        string name;
        int maxTotal;
        int maxIdle;
        int minIdle;
    };
    const int Builder::DEFAULT_MAX_IDLE=8;
    const int Builder::DEFAULT_MAX_TOTAL=8;
    const int Builder::DEFAULT_MIN_IDLE=8;

private:
    ResourcePoolConfig(Builder* builder){
        this->name=builder->name;
        this->maxTotal=builder->maxTotal;
        this->maxIdle=builder->maxIdle;
        this->minIdle=builder->minIdle;
    }
};

ResourcePoolConfig* config= ResourcePoolConfig.Builder()//临时对象
        .setName("DBConnectionPoll")//返回的是引用
        .setMaxTotal(16)
        .setMaxIdle(10)
        .setMinIdle(12)
        .build();

//建造者和工厂模式的区别
//直接看：建造者模式，主要是看应用场景，总结的非常好





