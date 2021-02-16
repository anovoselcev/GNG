#include "GNG/rest_client_sandbox.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>


namespace GNG {

RestClientSandBox::RestClientSandBox(const QString& token,
                                     const QString& api) noexcept
    :   IRestClient(token, api){}

bool RestClientSandBox::Authorization()
{
    QUrl url = _apiURL + "/sandbox/register";

    auto reply = SendPostRequest(url, QJsonObject());

    auto data = QJsonDocument::fromJson(reply->readAll());

    account.Type = data.object().take("payload").toObject().take("brokerAccountType").toString();
    account.ID = data.object().take("payload").toObject().take("brokerAccountId").toString();

    if(reply->error() != QNetworkReply::NoError) {
        log(reply->errorString());
    }

    return reply->error() == QNetworkReply::NoError;
}

void RestClientSandBox::SetCurrencyBalance(const QString& currency, double balance){
    QUrl url = _apiURL + "/sandbox/currencies/balance";

    QJsonObject body;
    body.insert("currency", currency);
    body.insert("balance", balance);
    body.insert("brokerAccountId,omitempty", account.ID);

    auto reply = SendPostRequest(url, body);

    if(reply->error() != QNetworkReply::NoError) {
        log(reply->errorString());
    }

    qDebug() << "SetCurrencyBalance Reply:";
    log(reply->readAll());
}

void RestClientSandBox::GetCurrencies(){
    QUrl url = _apiURL + "/portfolio/currencies" + "?brokerAccountId=" + account.ID;

    auto reply = SendGetRequest(url);

    if(reply->error() != QNetworkReply::NoError) {
        log(reply->errorString());
    }

    qDebug() << "GetCurrences Reply:";
    log(reply->readAll());
}


QString RestClientSandBox::GetInstrumentByFIGI(const QString& FIGI){
    QUrl url = _apiURL + "/market/search/by-figi?figi=" + FIGI;
//    QNetworkRequest req;
//    req.setUrl(path);
//    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    QJsonDocument data;
    auto reply = SendGetRequest(url);

    if(reply->error() != QNetworkReply::NoError) {
        log(reply->errorString());
    }

    //Можно передавать что-то более удобное
    return reply->readAll();
}

std::vector<Account> RestClientSandBox::Accounts() noexcept{
    QUrl path = _apiURL + "/user/accounts";
    return {};
}

}
