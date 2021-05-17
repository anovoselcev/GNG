#include "mainwindow.hpp"
#include <GNG/rest_client_sandbox.hpp>

#include <QApplication>
#include "GNG/rest_domain.hpp"

//https://tinkoffcreditsystems.github.io/invest-openapi/swagger-ui/#/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    GNG::RestClientSandBox c("t.N4ex5PfKxkGnjNHN6zmbyuYc-18FeLsF4q2fWcGUG__mSy6FNNXSc1NgndR0-2pAShDdDzhsD0eB0LVLhLoxcg",
                             "https://api-invest.tinkoff.ru/openapi/sandbox");

    qDebug() << "Authorization completed successfuly = " << c.Authorization();

    c.SetCurrencyBalance(GNG::Currency::RUB, 10000);
    c.GetCurrencies();
    c.GetInstrumentByFIGI("BBG000BPH459");
    c.GetOrderBookByFIGI("BBG000BPH459", 2);
    auto last_date = GNG::DateTime::currentRFC3339();
    last_date[3] = '0';
    c.GetCandlesByFIGI("BBG000BPH459",
                      last_date,
                       GNG::DateTime::currentRFC3339(),
                       GNG::DateTime::MONTH);

    return a.exec();
}
