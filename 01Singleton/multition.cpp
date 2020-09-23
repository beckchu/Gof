#include <unordered_map>
#include <thread>

using namespace std;
//普通单例是进程唯一的
//============线程唯一的单例=============
class IdGenerator{
public:
    long getId(){
        return id++;
    }

    static IdGenerator* getInstance(){
        long currentThreadId=this_thread::get_id();
        if(instance.find(currentThreadId)==instance.end()){
            instance[currentThreadId]=new IdGenerator();
        }
        return instance[currentThreadId];
    }

private:
    IdGenerator(){}

private:
    atomic<long> id=0;
    static unordered_map<long,IdGenerator*> instance;
};

//=================集群唯一的单例：进程间也是唯一================
//只需将对象序列化储存在外部，使用时从外部获取并反序列化（可序列化为json、xml、普通二进制文件）
//具体参考：单例（下）

//=====================多例模式，饿汉模式==================
class BackendServer{
public:
    BackendServer(long l,string str){
        this->serverNo=l;
        this->serverAddress=str;
    }

    BackendServer* getInstance(long serverNo){
        return serverInstances[serverNo];
    }
private:
    long serverNo;
    string serverAddress;
    static int SERVER_COUNT;
    static unordered_map<long,BackendServer*> serverInstances;
};

int BackendServer::SERVER_COUNT=3;
unordered_map<long,BackendServer*> BackendServer::serverInstances={{1,new BackendServer(1,"")},
                                                                   {2,new BackendServer(1,"")},
                                                                   {3,new BackendServer(1,"")}};

//===================多例模式，通过名称获取对象,懒汉模式======================
class logger{
public:
    static logger* getInstance(string loggerName){
        if(instances.find(loggerName)==instances.end()){
            instances[loggerName]=new logger();
        }
        return instances[loggerName];
    }

    void log(){}
    //静态函数只能访问静态成员变量，用来初始化，改变值，static createMap(logger* a)可以访问普通变量，但是是其他的类，不是this的，奇技淫巧
    static void createMap(logger* a){

    }
    static unordered_map<string,logger*> createMap(){//这样实现并不是懒汉模式；
        unordered_map<string,logger*> tmp;
        tmp.insert(make_pair<string,logger*>("1",new logger()));
        tmp.insert(make_pair<string,logger*>("2",new logger()));
        tmp.insert(make_pair<string,logger*>("3",new logger()));
        return tmp;
    }
private:
    logger(){}

    static unordered_map<string,logger*> instances;
};

unordered_map<string,logger*> logger::instances=logger::createMap();

//unordered_map<long,logger*> logger::instances={{1,new logger()},
//                                               {2,new logger()},
//                                               {3,new logger()}};
