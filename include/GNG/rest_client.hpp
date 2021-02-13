#pragma once

#include <QNetworkAccessManager>

namespace GNG {

class RestClient{

public:

    RestClient() = default;

    RestClient(const QString& token,
               const QString& apiURL = RestApiURL) noexcept;

    RestClient(QString&& token,
               QString&& apiURL = "https://api-invest.tinkoff.ru/openapi") noexcept;

    ~RestClient();

protected:

    QNetworkAccessManager*  _client = nullptr;
    QString                 _token;
    QString                 _apiURL;

    const inline static QString RestApiURL = "https://api-invest.tinkoff.ru/openapi";
};

}
