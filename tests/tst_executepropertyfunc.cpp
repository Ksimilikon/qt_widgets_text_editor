#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <QString>
#include <QDebug>
#include "../io/saver.h"

using namespace testing;

TEST(ExecutePropertyFunc, Properly)
{
    QString testStr = "ss{text}";
    QString result = io::executeProps(testStr, "ss");
    qDebug() << "result test=" << result;
    EXPECT_TRUE(result == "text");
}
TEST(ExecutePropertyFunc, IndependentSpaces)
{
    QString testStr = "   ss    {_ tex t }   ";
    QString result = io::executeProps(testStr, "ss");
    qDebug() << "result test=" << result;
    EXPECT_TRUE(result == "_ tex t ");
}
TEST(ExecutePropertyFunc, NotFirst)
{
    QString testStr = "ref dsfa{dfadfa}\nss{text}";
    QString result = io::executeProps(testStr, "ss");
    qDebug() << "result test=" << result;
    EXPECT_TRUE(result == "text");
}
TEST(ExecutePropertyFunc, RealData1)
{
    QString testStr = "styles{\nподпись(\ncolorText=#111111\ncolorBg=#ffffff\nfontSize=10\nlineHeight=1\nfontName=Arial\naligmentH=right\n)\nобычный(\ncolorText=#000000\ncolorBg=#ffffff\nfontSize=14\nlineHeight=1.5\nfontName=Arial\naligmentH=justify\n)\n}\nvars{\nимя=кси\nвар=переменная\n}\ntext{тестовое %вар про\n!!подпись-от кого: %имя}";
    QString result = io::executeProps(testStr, "text");
    qDebug() << "result test=" << result;
    EXPECT_TRUE(result == "тестовое %вар про\n!!подпись-от кого: %имя");
}
TEST(ExecutePropertyFunc, RealData2)
{
    QString testStr = "styles{\nподпись(\ncolorText=#111111\ncolorBg=#ffffff\nfontSize=10\nlineHeight=1\nfontName=Arial\naligmentH=right\n)\nобычный(\ncolorText=#000000\ncolorBg=#ffffff\nfontSize=14\nlineHeight=1.5\nfontName=Arial\naligmentH=justify\n)\n}\nvars{\nимя=кси\nвар=переменная\n}\ntext{тестовое %вар про\n!!подпись-от кого: %имя}";
    QString result = io::executeProps(testStr, "styles");
    qDebug() << "result test=" << result;
    EXPECT_TRUE(result == "\nподпись(\ncolorText=#111111\ncolorBg=#ffffff\nfontSize=10\nlineHeight=1\nfontName=Arial\naligmentH=right\n)\nобычный(\ncolorText=#000000\ncolorBg=#ffffff\nfontSize=14\nlineHeight=1.5\nfontName=Arial\naligmentH=justify\n)\n");
}
TEST(ExecutePropertyFunc, RealData3)
{
    QString testStr = "styles{\nподпись(\ncolorText=#111111\ncolorBg=#ffffff\nfontSize=10\nlineHeight=1\nfontName=Arial\naligmentH=right\n)\nобычный(\ncolorText=#000000\ncolorBg=#ffffff\nfontSize=14\nlineHeight=1.5\nfontName=Arial\naligmentH=justify\n)\n}\nvars{\nимя=кси\nвар=переменная\n}\ntext{тестовое %вар про\n!!подпись-от кого: %имя}";
    QString result = io::executeProps(testStr, "vars");
    qDebug() << "result test=" << result;
    EXPECT_TRUE(result == "\nимя=кси\nвар=переменная\n");
}
