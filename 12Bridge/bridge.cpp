
//在项目中应用并不多，了解就行了

//第一种理解：类存在两个（或者多个变化维度），通过组合，让这些维度可以独立变化扩展
//官方：将抽象和实现分离，抽象是指类库，两者通过对象的组合关系组合在一起，
//抽象的所有逻辑操作，最终都委托给实现执行，类似于组合优于继承

#include <string>
#include <list>

using namespace std;

class MsgSender{
public:
    virtual void send(string message)=0;
};

class TelephoneMsgSender: public MsgSender{
public:
    TelephoneMsgSender(list<string> telephones){
        this->telephones=telephones;
    }

    void send(string message) override{

    }

private:
    list<string> telephones;
};


class EmailMsgSender: public MsgSender{
public:
    EmailMsgSender(list<string> emails){
        this->emails=emails;
    }

    void send(string message) override{

    }

private:
    list<string> emails;
};

class WechartMsgSender: public MsgSender{
public:
    WechartMsgSender(list<string> names){
        this->names=names;
    }

    void send(string message) override{

    }

private:
    list<string> names;
};

class Notification{
public:
    Notification(MsgSender* msgSender){
        this->msgSender=msgSender;
    }

    virtual void notify(string message)=0;

protected:
    MsgSender* msgSender;
};

class ServerNotification : public Notification{
public:
    ServerNotification(MsgSender* msgSender):Notification(msgSender){
        
    }

    void notify(string message) override{
        msgSender->send(message);
    }
};

//变化维度：msgSender 和Notification
//抽象：要去干什么，实现：怎么去干
