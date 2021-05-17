#ifndef IRESTCLIENT_H
#define IRESTCLIENT_H

#include "GNG/rest_domain.hpp"
#include <QNetworkAccessManager>

namespace GNG {

class IRestClient : public QObject{

Q_OBJECT

public:
    IRestClient() = default;

    IRestClient(const QString& token,
                const QString& apiURL) noexcept;

    //! Авторизация
    virtual bool Authorization() = 0;

    //! [0] Orders

    //! Получение списка активных заявок
    QByteArray GetOrders() const;

    //! Создание лимитной заявки
    virtual void CreateLimitOrder(){};

    //! Создание рыночной заявки
    virtual void CreateMarketOrder(){};

    //! Отмена заявки
    virtual void CancelOrder(){};

    //! [0] Orders


    //! [1] Portfolio

    //! Получение портфеля клиента
    QByteArray GetPortfolio() const;

    //! Получение валютных активов клиента
    QByteArray GetCurrencies() const;

    //! [1] Portfolio


    //! [2] Market

    //! Получение списка акций
    QByteArray GetStocks() const;

    //! Получение списка облигаций
    QByteArray GetBonds() const;

    //! Получение списка ETF
    QByteArray GetETF() const;

    //! Получение списка валютных пар
    QByteArray GetCurrenciesPair() const;

    //! Получение стакана по FIGI
    QByteArray GetOrderBookByFIGI(const QString& FIGI,
                                  uint32_t depth) const;

    //! Получение исторических свечей по FIGI
    //! Надо понять как создавать нужный формат времени
    //! https://github.com/TinkoffCreditSystems/invest-openapi-go-sdk/blob/master/rest_client.go
    //! строка 366
    QByteArray GetCandlesByFIGI(const QString& FIGI,
                                const QString& from,
                                const QString& to,
                                const QString& interval) const;

    //! Получение инструмента по FIGI
    QByteArray GetInstrumentByFIGI(const QString& FIGI) const;

    //! Получение инструмента по Ticker'у
    QByteArray GetInstrumentByTicker(const QString& tiker) const;

    //! [2] Market


    //! [3] Operations

    //! Получение списка операций
    //! Неверная сигнатура!!!!
    QByteArray GetOperations() const;

    //! [3] Operations


    //! [4] User

    //! Получение брокерских счетов клиента
    QByteArray GetAccounts() const;

    //! [4] User

protected:
    //! Отправляет POST запрос по url с данными json
    QNetworkReply* SendPostRequest(const QUrl& url,
                                   const QJsonObject& json);

    //! Отправляет GET запрос по url
    QNetworkReply* SendGetRequest(const QUrl& path) const;

    bool isReplyValid(QNetworkReply* reply) const noexcept;

    QByteArray Get(const QUrl& url) const;

    QString modifyDateForURL(const QString& date) const noexcept;


    mutable std::unique_ptr<QNetworkAccessManager> _manager;

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
