#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>
#include<QApplication>

//#include <QTest>

int main(int argc, char *argv[])

{

    QApplication app(argc, argv);



    testing::InitGoogleTest(&argc, argv);



    return RUN_ALL_TESTS();

}