#include <string>
#include <unordered_map>

using namespace std;

class RuleConfig{

};

class IRuleConfigParser{
public:
    virtual RuleConfig parse(string str)=0;
};

class JsonRuleConfigParser:public IRuleConfigParser{
public:
    RuleConfig parse(string str){
        return;
    }
};

class XmlRuleConfigParser:public IRuleConfigParser{
public:
    RuleConfig parse(string str){
        return;
    }
};

class YamlRuleConfigParser:public IRuleConfigParser{
public:
    RuleConfig parse(string str){
        return;
    }
};

//简单工厂,伪代码
class RuleConfigSource{
public:
    RuleConfig load(string ruleConfigFilePath){
        string realConfigFileExtension=getFileExtension(ruleConfigFilePath);
        IRuleConfigParser* pParser=RuleConfigParseFactory::createParser(realConfigFileExtension);
        if(pParser==NULL){
            throw ;
        }
        string configText="";
        RuleConfig ruleConfig=pParser->parse(configText);
        return ruleConfig;
    }

private:
    string getFileExtension(string filePath){
        return "json";
    }
};


class RuleConfigParseFactory{
public:
    //简单工厂的if语句也是可以消掉的,但是没必要
    static IRuleConfigParser* createParser(string configFormat){
        IRuleConfigParser* pParser=NULL;
        if("json"==configFormat){
            //这里写的不一定对，dynamic_cast要判空
            pParser=dynamic_cast<IRuleConfigParser*>(new JsonRuleConfigParser());
        }
        else if ("xml"==configFormat)
        {
            pParser=dynamic_cast<IRuleConfigParser*>(new XmlRuleConfigParser());
        } 
        else if ("yaml"==configFormat)
        {
            pParser=dynamic_cast<IRuleConfigParser*>(new YamlRuleConfigParser());
        }
        return pParser;
    }
};


//工厂方法,将对象的创建集中到自己工厂中，然后统一由一个大的工厂管理这些工厂
class IRuleConfigParserFactory{
public:
    virtual IRuleConfigParser* createParser()=0;
};

class JsonRuleConfigParserFactory:public IRuleConfigParserFactory{
public:
    IRuleConfigParser* createParser(){
        return;
    }
};

class XmlRuleConfigParserFactory:public IRuleConfigParserFactory{
public:
    IRuleConfigParser* createParser(){
        return;
    }
};

class YamlRuleConfigParserFactory:public IRuleConfigParserFactory{
public:
    IRuleConfigParser* createParser(){
        return;
    }
};

//创建对象比较复杂，不是简单的new一下，要组合其他对象，各种初始化，
//将创建问题分解到多个工厂（如果不拆分简单工厂会非常大），
//创建对象比较简单时，只需使用简单工厂
//一般用new创建对象就可以了

class RuleConfigParserFactoryMap{//工厂的工厂，返回工厂的单例，实现和单例的饿汉模式相似
public:
    typedef unordered_map<string,IRuleConfigParserFactory*> unMap;
    static IRuleConfigParserFactory* getParserFactory(string type){
        if(type.empty()){
            return NULL;
        }

        IRuleConfigParserFactory* parserFactory=cachedFactories[type];
        return parserFactory;
    }

    static unMap initMap(){
        //这里错了，应该new一个
        unMap tmp;
        tmp.insert(make_pair<string,IRuleConfigParserFactory*>("json",new JsonRuleConfigParserFactory()));
        tmp.insert(make_pair<string,IRuleConfigParserFactory*>("xml",new XmlRuleConfigParserFactory()));
        tmp.insert(make_pair<string,IRuleConfigParserFactory*>("yaml",new YamlRuleConfigParserFactory()));
        return tmp;
    }

private:
    static unordered_map<string,IRuleConfigParserFactory*> cachedFactories;
};

unordered_map<string,IRuleConfigParserFactory*> RuleConfigParserFactoryMap::cachedFactories=RuleConfigParserFactoryMap::initMap();

//unordered_map<long,IRuleConfigParserFactory*> RuleConfigParserFactoryMap::cachedFactories={{"json",new JsonRuleConfigParser()},
//                                                                                           {"xml",new XmlRuleConfigParser()},
//                                                                                           {"yaml",new YamlRuleConfigParser()}};

class RuleConfigSource1{
public:
    RuleConfig load(string ruleConfigFilePath){
        string ruleConfigFileExtension=getFileExtension(ruleConfigFilePath);
        IRuleConfigParserFactory* pParserFactory=RuleConfigParserFactoryMap::getParserFactory(ruleConfigFileExtension);
        if(pParserFactory==NULL){
            throw "...";
        }
        IRuleConfigParser* parser=pParserFactory->createParser();
        string configText="";
        RuleConfig ruleConfig=parser->parse(configText);
        return ruleConfig;
    }

private:
    string getFileExtension(string filePath){
        return "json";
    }
};




//抽象工厂（不常用）
//是应对多配置对象的创建,直接看:工厂模式（上）


//java的依赖注入框架需要反射机制，c++没有，只能呵呵



