
#include<string>
//代理模式：通过引入代理类给原始类添加功能，控制访问

using namespace std;

namespace demo{

class UserVo{
private:
    string telephone;
    string password;
};

class RequestInfo{
public:
    RequestInfo(string str,long responseTime,long startTimestamp){

    }
};

class MetricsController{
public:
    int recordRequest(RequestInfo*){
        return 1;
    }
};
//实现1
class IUserController{//接口
public:
    virtual UserVo* login(string telephone,string password)=0;
    virtual UserVo* Register(string telephone,string password)=0;//不能使用register，因为是编译器变量
};

//实现
class UserController:public IUserController{
public:
    UserVo* login(string telephone,string password) override{
        return new UserVo();
    }

    UserVo* Register(string telephone,string password) override{
        return new UserVo();
    }
};

//增强原有类的功能，组合的形式实现；
class UserControllerProxy:public IUserController{
private:
    MetricsController* metricsController;
    IUserController* userController;

public:
    //依赖注入
    UserControllerProxy(IUserController* userController){
        this->userController=userController;
        this->metricsController=new MetricsController();//增强功能
    }

    UserVo* login(string telephone,string password) override{
        long startTimestamp=10;

        UserVo* userVo =userController->login(telephone,password);

        long endTimeStamp=100;
        long responseTime=endTimeStamp-startTimestamp;
        RequestInfo* requestInfo=new RequestInfo("login",responseTime,startTimestamp);
        metricsController->recordRequest(requestInfo);

        return userVo;
    }

    UserVo* Register(string telephone,string password) override{
        long startTimestamp=10;

        UserVo* userVo =userController->Register(telephone,password);
        long endTimeStamp=100;
        long responseTime=endTimeStamp-startTimestamp;
        RequestInfo* requestInfo=new RequestInfo("register",responseTime,startTimestamp);
        metricsController->recordRequest(requestInfo);

        return userVo;
    }

};

//创建增强代理，原始类和代理类使用同样的接口，使代理类替换原始类更加简单
IUserController* userController=new UserControllerProxy(new UserController());


//实现2=================原始类不能重新定义接口，只能使用继承==================
class UserControllerProxy1: public UserController{
private:
    MetricsController* metricsController;

public:
    UserControllerProxy1(){
        this->metricsController=new MetricsController();
    }

    UserVo* login(string telephone,string password) {
        long startTimestamp=10;

        UserVo* userVo =UserController::login(telephone,password);

        long endTimeStamp=100;
        long responseTime=endTimeStamp-startTimestamp;
        RequestInfo* requestInfo=new RequestInfo("login",responseTime,startTimestamp);
        metricsController->recordRequest(requestInfo);

        return userVo;
    }

    UserVo* Register(string telephone,string password) {
        long startTimestamp=10;

        UserVo* userVo =UserController::Register(telephone,password);
        long endTimeStamp=100;
        long responseTime=endTimeStamp-startTimestamp;
        RequestInfo* requestInfo=new RequestInfo("register",responseTime,startTimestamp);
        metricsController->recordRequest(requestInfo);

        return userVo;
    }
};


//===========c++现在还不支持反射机制，不支持动态代理=================

}




























