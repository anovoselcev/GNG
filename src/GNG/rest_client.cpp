#include "GNG/rest_client.hpp"
#include <QJsonDocument>


namespace GNG {

    RestClient::RestClient(const QString& token,
                           const QString& api) noexcept:
                           _token(token),
                           _apiURL(api){}


    QString RestClient::InstrumentByFIGI(const QString& FIGI){
        QUrl path = _apiURL + "/market/search/by-figi?figi=" + FIGI;
        QNetworkRequest req;
        req.setUrl(path);
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QJsonDocument data;
        QNetworkReply* reply = post(req, data.toJson());
    }

    std::vector<Account> RestClient::Accounts() noexcept{
        QUrl path = _apiURL + "/user/accounts";

    }

}
