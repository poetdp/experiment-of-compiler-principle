#ifndef LEXANA_H
#define LEXANA_H

#include <fstream>
#include <QString>
#include <QChar>

using namespace std;

//Token 表
typedef enum TOKEN {
    ENDOFFILE = -3,		//文件结束符
    ERRORINFO,			//错误信息
    COMMENT,			//注释
    OTHER,				//其他
    PRECOMPILE,   		//预编译符--#,include,define,ifdef,else,endif
    IDENTIFIER,   		//标识符，非关键字--[a-z][A-Z][0-9]
    KEYWORD,	  		//关键字32个
    CHARACTOR,    		//字符--单引号包含的,
    STRING,       		//字符串--双引号包含的
    NUMBER,       		//数字--1234,012
    OPERATOR,     		//运算符表
    BOUNDWORD 			//界符
} TOKEN;

//Token 名称表
const QString TokenName[] = {
    "其他","预编译符","标识符","关键字","字符","字符串","数字","运算符","界符"
};

//关键字表
const QString KEYWORDS[] = {
    "void","char","int","float","double",                   //5个基本数据类型
    "short","long","signed","unsigned",                     //4个类型修饰关键字
    "struct","union","enum","typedef","sizeof",             //5个复杂类型关键字
    "auto","static","register","extern","const","volatile", //6个存储级别关键字
    "return","continue","break","goto",                     //4个跳转结构
    "if","else","switch","case","default",                  //5个分支结构
    "for","do","while"                                      //3个循环结构
};
const int KEYWORDS_NUM = 32;

//运算符表
const QString OPERATORS[] = {
    "+","-","*","/","%","++","--",
    "=","<",">","!","==","<=",">=",
    "&","|","^","&&","||"

};
const int OPERATORS_NUM = 19;

//限界符表
const QString BOUNDWORDS[] = {
    ",",".",";",":","?",
    "(",")","[","]","{","}"
};
const int BOUNDWORDS_NUM = 11;

class LexicalAnalysis
{
public:
    LexicalAnalysis(QString src);
    int readChar(QChar &ch);
    int putBackChar(QChar ch);
    QString qcharToQstring(QChar ch);
    bool isStringInArray(QString str, const QString *arr, int n);
    void writeErrorInfo(QString& str, const QString err);
    int getToken(QString& qs, TOKEN& token);
    void lexAna(QString &dest, QString &msg);

private:
    int cur_line, cur_col; //当前坐标（行、列）
    int error_num;		   //错误数量

    int index;             //src 索引

    QString src;           //暂存源代码
    QString words;           //暂存单词
};

#endif // LEXANA_H
