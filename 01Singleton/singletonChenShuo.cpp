
#include<boost/noncopyable.hpp>
#include<pthread.h>
#include<stdlib.h>

namespace mudo{

//Linux的多线程安全单例
template<typename T>
class Singleton:boost::noncopyable{
public:
    static T& instance(){//返回是引用
        pthread_once(&ponce_,&Singleton::init);
        return *value_;
    }

private:
    Singleton();
    ~Singleton();

    static void init(){
        value_=new T();
        ::atexit(destory);
    }

    static void destory(){
        delete value_;
    }

private:
    static pthread_once_t ponce_;
    static T* value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_=PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_=NULL;

}
