#include "lexana.h"

//构造函数
LexicalAnalysis::LexicalAnalysis(QString src)
{
    //变量初始化
    cur_line = 1;
    cur_col = 0;
    error_num = 0;
    index = 0;

    this->src = src;
}

//读取一个字符
int LexicalAnalysis::readChar(QChar& ch)
{
    if (index >= src.length())
    {
        return -1;
    }
    ch = src[index++];
    //坐标变化
    if (ch == '\t')
    {
        cur_col += 4;
    }
    else
    {
        cur_col++;
    }
    if (ch == '\n')
    {
        cur_line++;
        cur_col = 0;
    }
    return 0;
}

//放回一个字符
int LexicalAnalysis::putBackChar(QChar ch)
{
    index--;
    //坐标变化
    if (ch == '\t')
    {
        cur_col -= 4;
    }
    else
    {
        cur_col--;
    }
    if (ch == '\n')
    {
        cur_line--;
    }
    return 0;
}

//将 QChar 转为 QString
QString LexicalAnalysis::qcharToQstring(QChar ch)
{
    QString qs;
    qs.append(ch);
    return qs;
}

//字符串 str 是否在数组 arr 中
bool LexicalAnalysis::isStringInArray(QString str, const QString* arr, int n)
{
    for (int i = 0; i<n; i++)
    {
        if (str == arr[i])
        {
            return true;
        }
    }
    return false;
}

//向 str 写入报错信息
void LexicalAnalysis::writeErrorInfo(QString& str, const QString err)
{
    str += err;
}

//得到一个单词及其类型
int LexicalAnalysis::getToken(QString& qs, TOKEN& token)
{
    QChar ch;
    //读取字符，遇到空白符则跳过
    do
    {
        if(readChar(ch) == -1)
        {
            return -1;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n');

    words.clear();    //清空 words

    if (ch == EOF)
    {
        token = ENDOFFILE;
    }
    else if (isStringInArray(qcharToQstring(ch), BOUNDWORDS, BOUNDWORDS_NUM))
    { //ch 是界符
        words.append(ch);
        token = BOUNDWORD;
    }
    else if (isStringInArray(qcharToQstring(ch), OPERATORS, OPERATORS_NUM))
    { //ch 是单符号运算符 --> 单、双运算符？注释？
        words.append(ch);
        token = OPERATOR;
        //考虑双字符
        QChar t;
        readChar(t);
        words.append(t);
        if (words == "//")
        { //单行注释
            token = COMMENT;
            while (readChar(t), t != '\n') ; //处理注释
        }
        else if (words == "/*")
        { //多行注释
            token = COMMENT;
            QChar t1, t2;
            readChar(t1);
            readChar(t2);
            while (!(t1 == '*' && t2 == '/')) //处理注释
            {
                t1 = t2;
                readChar(t2);
            }
        }
        else if (isStringInArray(words, OPERATORS, OPERATORS_NUM))
        { //双符号运算符
            token = OPERATOR;
        }
        else
        {
            putBackChar(words[words.length() - 1]);
            words.chop(1);
        }
    }
    else if (ch.isLetter() || ch == '_')
    { //ch 是字母或'_' --> 标识符？关键字？
        words.append(ch);
        QChar t;
        while (readChar(t), t.isDigit() || t.isLetter() || t == '_')
        {
            words.append(t);
        } //tmp中存放了标识符
        putBackChar(t); //多读了一个字符
        if (isStringInArray(words, KEYWORDS, KEYWORDS_NUM))
        { //是关键字
            token = KEYWORD;
        }
        else
        { //是标识符
            token = IDENTIFIER;
        }
    }
    else if (ch.isDigit())
    { //ch 是数字 --> 数字
        words.append(ch);
        QChar t;
        while (readChar(t), t.isDigit())
        {
            words.append(t);
        }
        putBackChar(t);
        token = NUMBER;
    }
    else if (ch == '\"')
    { //ch 是 \" --> 字符串
        QChar t;
        while (readChar(t), t != '\"')
        {
            words.append(t);
        }
        token = STRING;
    }
    else if (ch == '\'')
    { //ch 是 \' --> 字符
        QChar t;
        while (readChar(t), t != '\'')
        {
            words.append(t);
        }
        token = CHARACTOR;
        if (words.length() > 2)
        {
            writeErrorInfo(words, "不是字符");
            token = ERRORINFO;
        }
    }
    else
    {
        words.append(ch);
        token = OTHER;
    }

    qs = words;
    return 0;
}

//词法分析
void LexicalAnalysis::lexAna(QString &dest, QString &msg)
{
    index = 0;
    //逐字符处理
    int first = 1;
    while (index < src.length()) {
        TOKEN tk = OTHER;
        QString t = "";
        getToken(t, tk);

        if (tk >= 0)
        {
            dest += "(" + t + "," + TokenName[tk] + ")\n";
        }
        else if(tk == ERRORINFO)
        {
            error_num++;
            if (first)
            {
                msg += " ";
                first = 0;
            }
            else
            {
                msg += "\n         ";
            }
            msg += "Error: Line " + QString::number(cur_line) + ", " + t;
        }
    }

    if (error_num <= 0)
    {
        msg += " ";
    }
    else
    {
        msg += "\n\n         ";
    }
    msg += "词法分析完成! - ";
    msg += QString::number(error_num);
    msg += " error(s)";
}
