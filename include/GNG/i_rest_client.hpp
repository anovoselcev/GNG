#ifndef IRESTCLIENT_H
#define IRESTCLIENT_H

#include "GNG/rest_domain.hpp"
#include <QNetworkAccessManager>

namespace GNG {

class IRestClient : public QNetworkAccessManager{

public:
    IRestClient() = default;

    IRestClient(const QString& token,
                const QString& apiURL) noexcept;

    //! Авторизация
    virtual bool Authorization() = 0;

    //! [0] Orders

    //! Получение списка активных заявок
    virtual void GetOrders(){};

    //! Создание лимитной заявки
    virtual void CreateLimitOrder(){};

    //! Создание рыночной заявки
    virtual void CreateMarketOrder(){};

    //! Отмена заявки
    virtual void CancelOrder(){};

    //! [0] Orders


    //! [1] Portfolio

    //! Получение портфеля клиента
    virtual void GetPortfolio(){};

    //! Получение валютных активов клиента
    virtual void GetCurrencies(){};

    //! [1] Portfolio


    //! [2] Market

    //! Получение списка акций
    virtual void GetStocks(){};

    //! Получение списка облигаций
    virtual void GetBonds(){};

    //! Получение списка ETF
    virtual void GetETF(){};

    //! Получение списка валютных пар
    virtual void GetCurrenciesPair(){};

    //! Получение стакана по FIGI
    virtual void GetOrderBookByFIGI(){};

    //! Получение исторических свечей по FIGI
    virtual void GetCandlesByFIGI(){};

    //! Получение инструмента по FIGI
    virtual QString GetInstrumentByFIGI(const QString& FIGI){return "";};

    //! Получение инструмента по Ticker'у
    virtual void GetInstrumentByTicker(){};

    //! [2] Market


    //! [3] Operations

    //! Получение списка операций
    virtual void GetOperations(){};

    //! [3] Operations


    //! [4] User

    //! Получение брокерских счетов клиента
    virtual void GetAccounts(){};

    //! [4] User

protected:
    //! Отправляет POST запрос по url с данными json
    QNetworkReply* SendPostRequest(const QUrl& url,
                                   const QJsonObject& json);

    //! Отправляет GET запрос по url
    QNetworkReply* SendGetRequest(const QUrl& path);

    //! Токен аутентификации
    QString                 _token;

    //! URL сервера-обработчика HTTP запросов
    QString                 _apiURL;

    //! Структура, хранящая json:"brokerAccountType" (Account::Type - тип аккаунта) и json:"brokerAccountId" (Account::ID - ID аккаунта)
    Account account;

    inline static const QString RestApiURL        = "https://api-invest.tinkoff.ru/openapi";
    inline static const QString RestApiSandboxURL = "https://api-invest.tinkoff.ru/openapi/sandbox";
};

}
#endif // IRESTCLIENT_H
