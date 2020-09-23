//和面向对象的“组合关系”没关系
//主要用来处理树形结构数据，所以不常用

//这个设计模式感觉有点扯淡,更像算法实现

#include <string>
#include <list>

using namespace std;

class FileSystemNode{
protected:
    string path;
public:
    FileSystemNode(string path){
        this->path=path;
    }
    virtual int countNumOfFiles()=0;
    virtual long countSizeOfFiles()=0;

    string getPath(){
        return path;
    }
};

class File: public FileSystemNode{
public:
    File(string path):FileSystemNode(path){

    }

    int countNumOfFiles() override{
        return 1;
    }

    long countSizeOfFiles() override{
        if(!access(path,0)){
            return 0;
        }
        return ;
    }
};

class Directory: public FileSystemNode{
private:
    list<FileSystemNode*> subNodes;

public:
    Directory(string path):FileSystemNode(path){

    }

    int countNumOfFiles() override{
        int numOfFile=0;
        for(FileSystemNode* fileOrDir : subNodes){
            numOfFile +=fileOrDir->countNumOfFiles();//根据多态自动切换
        }
        return numOfFile;
    }

    long countSizeOfFiles() override{
        long sizeofFiles=0;
        for(FileSystemNode* fileOrDir : subNodes){
            sizeofFiles +=fileOrDir->countSizeOfFiles();
        }
        return sizeofFiles;
    }

    void addSubNode(FileSystemNode* fileOrDir){
        subNodes.push_back(fileOrDir);
    }
};





















