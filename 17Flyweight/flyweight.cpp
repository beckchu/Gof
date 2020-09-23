//享元模式的意图是复用对象，节省内存，前提是享元对象（相似的对象）是不可变对象

//不可变指的是：构造函数创建后，没有set方法改变其状态

#include<string>
#include<unordered_map>
#include<list>

using namespace std;
//享元类
class ChessPieceUnit{
public:
    static enum Color{//static比较合适
        RED,BLACK
    };

private:
    int id;
    string text;
    Color color;

public:
    ChessPieceUnit(int id,string text,Color color){
        this->id=id;
        this->text=text;
        this->color=color;
    }

    //没有set方法
    //省略get方法和其他的方法
};
//饿汉模式
class ChessPieceUnitFactory{
private:
    typedef unordered_map<int,ChessPieceUnit*> MAP;//这里只是伪代码
    static MAP pieces;//在类外要进行初始化的；
public:
    static MAP initMap(){//这个函数只是更改静态变量；
        MAP tmp;
        tmp.insert(make_pair("1",new ChessPieceUnit(1,"马",ChessPieceUnit::Color.BLACK)));
        tmp.insert(make_pair("2",new ChessPieceUnit(2,"马",ChessPieceUnit::Color.BLACK)));
    }

    static ChessPieceUnit* getChessPiece(int chessPieceId){
        return pieces[chessPieceId];
    }
};

//unordered_map<int,ChessPieceUnit*> ChessPieceUnitFactory::pieces=ChessPieceUnitFactory::initMap();

unordered_map<int,ChessPieceUnit*> ChessPieceUnitFactory::pieces={{"1",new ChessPieceUnit(1,"马",ChessPieceUnit::Color.BLACK)},
                                                                  {"2",new ChessPieceUnit(2,"车",ChessPieceUnit::Color.BLACK)}};
//省略摆放其他棋子的代码

class ChessPiece{
private:
    ChessPieceUnit* chessPieceUnit;//享元类
    int positionX;
    int positionY;

public:
    ChessPiece(ChessPieceUnit* unit,int positionX,int positionY){
        this->chessPieceUnit=unit;
        this->positionX=positionX;
        this->positionY=positionY;
    }

    //省略getter和seter
};

class ChessBord{
private:
    unordered_map<int,ChessPiece*> chessPieces;

public:
    ChessBord(){
        init();
    }

    void move(int chessPieceId,int toPositionX,int toPositionY){

    }

private:
    void init(){
        chessPieces.insert(make_pair(1,new ChessPiece(ChessPieceUnitFactory::getChessPiece(1),0,0)));
        chessPieces.insert(make_pair(1,new ChessPiece(ChessPieceUnitFactory::getChessPiece(1),0,0)));
        //省略摆放其他棋子的代码
    }

};


//文本编辑器享元
class CharacterStyle{
private:
    int font;
    int size;
    int colorRGB;
public:
    CharacterStyle(int font,int size,int colorRGB){
        this->colorRGB=colorRGB;
        this->font=font;
        this->size=size;
    }
        bool operator==(const CharacterStyle& other){
            return other.font==this->font && other.size==this->size && other.colorRGB==this->colorRGB;
        }
};

class CharacterStyleFactory{
private:
    const static list<CharacterStyle*>* styles;
public:
    static CharacterStyle* getStyle(int font,int size,int colorRGB){
        CharacterStyle* newStyle=new CharacterStyle(font,size,colorRGB);
        for(CharacterStyle* style:styles){
            //没找到就重建
        }
        return newStyle;
    }
};

const list<CharacterStyle*>* CharacterStyleFactory:: styles=new list<CharacterStyle*>();

class Character{
private:
    char c;
    CharacterStyle* style;

public:
    Character(char c,CharacterStyle* style){
        this->c=c;
        this->style=style;
    }
};

class Editor{
private:
    list<Character*>* chars;
public:
    Editor(list<Character*> *character){
        chars=character;
    }

    void appendCharacter(char c,int font,int size,int colorRGB){
        Character* character=new Character(c,CharacterStyleFactory.getStyle(font,size,colorRGB));
        chars->push_back(character);
    }

}











