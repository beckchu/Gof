#include<string>
#include<atomic>
#include <mutex>
/*
构造函数，拷贝构造函数，拷贝赋值，必须是private
对象创建的线程安全问题
是否支持延时加载
getinstance性能是否高（是否加锁），获得instance后，程序要保证共享资源的多线程性
*/

using namespace std;

//===========解决资源冲突===========
class Logger{

public:
    ~Logger(){
        fclose(pfile);
    }

    void log(string message){
        char* buffer=(char*)malloc(message.size());
        //fwrite 是线程安全的
        fwrite(buffer,sizeof(char),sizeof(buffer),pfile);
    }
    //访问静态成员函数和成员
    static Logger* getInstance(){//饿汉模式不用加锁
        return instance;
    }

private:
    Logger(){
        pfile=fopen("./log.txt","w");
    }

    Logger(const Logger&){}
    Logger& operator=(const Logger&){}

private:
    FILE* pfile;
    static Logger* instance;
};

Logger* Logger::instance=new Logger();

//举例使用
class UserController{
public:
    void login(string username,string password){
        Logger.getInstance()->log(username+"logined!");
    }
};

class OrderControler{
private:
    //Logger* logger=new Logger();构造函数是私有的

void create(string order){
    Logger.getInstance()->log("Create a order: "+order);
}

};

//===========解决唯一标识===========
class IdGenerator0{

public:
    long getId(){
        long idL=id++;
        return idL;
    }

    static IdGenerator0* getInstance(){//饿汉模式不用加锁
        return instance;
    }

private:
    IdGenerator0(){}

private:
    static IdGenerator0* instance;
    atomic<int> id=0;
};

IdGenerator0* IdGenerator0::instance=new IdGenerator0();

//使用举例
long id=IdGenerator0::getInstance()->getId();


//==============饿汉模式：多线程安全，不用加锁，执行效率高，浪费内存=================
class IdGenerator1{
public:
    long getId(){
        return id++;
    }

private:
    static IdGenerator1* getInstance(){
        return instance;
    }

private:
    atomic<long> id=0;
    static IdGenerator1* instance;
    IdGenerator1(){}
};
//不支持延时加载，在创建初始化耗时很长的对象时，会影响到性能，最好的办法是用到再初始化
IdGenerator1* IdGenerator1::instance=new IdGenerator1();



//================懒汉模式，线程不安全，必须加锁才能保证单例===============
class IdGenerator2{
public:
    long getId(){
        return id++;
    }

private:
    static IdGenerator2* getInstance(){//必须加锁
        if(instance==NULL){
            instance=new IdGenerator2();
        }
        return instance;
    }

private:
    atomic<long> id=0;
    static IdGenerator2* instance;
    IdGenerator2(){}
};

//双重检测
//线程安全的单例：懒汉式（双检锁 DCL 机制）
class singleton{
public:
    static singleton* getInstance(){
        if(m_pSingleton==NULL){
            std::lock_guard<std::mutex> lock(m_mutex);//双检锁在c++中并不安全
            if(m_pSingleton==NULL){
                m_pSingleton=new singleton();
            }
        }
        return m_pSingleton;
    }

private:
    singleton(){}

private:
    static singleton* m_pSingleton;
    static mutex m_mutex;
};

singleton* m_pSingleton=NULL;

//内部静态类
//c++不适用，Java的友好实现



//以上都太简单了，没有考虑单例对象的构造和析构,拷贝构造问题,c++通用方法是使用Memory Barrier和饿汉模式
//参考陈硕的Linux实现


//=============单例有很多的问题，反模式================

