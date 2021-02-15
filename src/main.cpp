#include "mainwindow.hpp"
#include <GNG/rest_client_sandbox.hpp>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    GNG::RestClientSandBox c("t.KR8nAVRVAw64pJ7rd_eau0q3Ra0XetjBtxhUoDGjxsQ4mUehXy67zdDgCT3qu-WuA-T9r8YFH73tIiRK3ITNCw",
                      "https://api-invest.tinkoff.ru/openapi/sandbox");
    qDebug() << c.Autorization();

    return a.exec();
}
