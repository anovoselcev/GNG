#pragma once

#include <QNetworkAccessManager>
#include "GNG/rest_domain.hpp"

namespace GNG {

class RestClient : public QNetworkAccessManager{

public:

    RestClient() = default;

    RestClient(const QString& token,
               const QString& apiURL = RestApiURL) noexcept;

    QString InstrumentByFIGI(const QString& FIGI);

    std::vector<Account> Accounts() noexcept;

protected:

    QString                 _token;
    QString                 _apiURL;

    const inline static QString RestApiURL = "https://api-invest.tinkoff.ru/openapi";
};

}
