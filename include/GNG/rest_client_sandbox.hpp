#pragma once

#include <QNetworkAccessManager>
#include "GNG/rest_domain.hpp"
#include <QNetworkReply>
#include <QJsonDocument>

namespace GNG {

class RestClientSandBox : public QNetworkAccessManager{

public:

    RestClientSandBox() = default;

    RestClientSandBox(const QString& token,
                      const QString& apiURL = RestApiURL) noexcept;

    bool Autorization();

    QString InstrumentByFIGI(const QString& FIGI);

    void SetCurrencyBalance(const QString& currency, double balance);

    void GetCurrences();

    std::vector<Account> Accounts() noexcept;

    public slots:

    void FinishedAuthorization();

    void FinishedSetCurrencyBalance();

    void FinishedGetCurrences();

    void SomeError(QNetworkReply::NetworkError);

protected:

    QString                 _token;
    QString                 _apiURL;

    QNetworkReply* reply = nullptr;

    Account account;

    QJsonDocument data;

    const inline static QString RestApiURL = "https://api-invest.tinkoff.ru/openapi/sandbox";
};

}
