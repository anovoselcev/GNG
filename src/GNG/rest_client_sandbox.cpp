#include "GNG/rest_client_sandbox.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>


namespace GNG {

    RestClientSandBox::RestClientSandBox(const QString& token,
                           const QString& api) noexcept:
                           _token(token),
                           _apiURL(api){}


    bool RestClientSandBox::Autorization(){
        QUrl path = _apiURL + "/sandbox/register";
        QNetworkRequest req;
        req.setUrl(path);

        req.setRawHeader(QByteArray("Authorization"),
                         QByteArray("Bearer ") + _token.toUtf8());

        reply = post(req, QJsonDocument().toJson());
        connect(reply, &QNetworkReply::errorOccurred, this, &RestClientSandBox::SomeError);
        connect(reply, &QNetworkReply::finished, this, &RestClientSandBox::FinishedAuthorization);

        return reply->isOpen();
    }

    void RestClientSandBox::FinishedAuthorization(){
        reply->disconnect(SIGNAL(finished()));
        data = QJsonDocument::fromJson(reply->readAll());

        account.Type = data.object().take("payload").toObject().take("brokerAccountType").toString();
        account.ID = data.object().take("payload").toObject().take("brokerAccountId").toString();
        SetCurrencyBalance(Currency::RUB, 10000);
    }

    void RestClientSandBox::SomeError(QNetworkReply::NetworkError e){
        qDebug() << e;
    }

    void RestClientSandBox::SetCurrencyBalance(const QString& currency, double balance){
        QUrl url = _apiURL + "/sandbox/currencies/balance";
        QNetworkRequest req;
        req.setUrl(url);
        QJsonObject body;

        body.insert("currency", currency);
        body.insert("balance", balance);
        body.insert("brokerAccountId,omitempty", account.ID);

        req.setRawHeader(QByteArray("Authorization"),
                         QByteArray("Bearer ") + _token.toUtf8());

        reply = post(req, QJsonDocument(body).toJson());
        connect(reply, &QNetworkReply::finished, this, &RestClientSandBox::FinishedSetCurrencyBalance);
    }

    void RestClientSandBox::FinishedSetCurrencyBalance(){
        reply->disconnect(SIGNAL(finished()));
        qDebug() << reply->readAll();
        GetCurrences();
    }

    void RestClientSandBox::GetCurrences(){
        QUrl url = _apiURL + "/portfolio/currencies" + "?brokerAccountId=" + account.ID;

        QNetworkRequest req;
        req.setUrl(url);

        req.setRawHeader(QByteArray("Authorization"),
                         QByteArray("Bearer ") + _token.toUtf8());

        reply = get(req);
        connect(reply, &QNetworkReply::finished, this, &RestClientSandBox::FinishedGetCurrences);
    }

    void RestClientSandBox::FinishedGetCurrences(){
        reply->disconnect(SIGNAL(finished()));
        qDebug() << reply->readAll();
    }


    QString RestClientSandBox::InstrumentByFIGI(const QString& FIGI){
        QUrl path = _apiURL + "/market/search/by-figi?figi=" + FIGI;
        QNetworkRequest req;
        req.setUrl(path);
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QJsonDocument data;
        QNetworkReply* reply = post(req, data.toJson());
        return "";
    }

    std::vector<Account> RestClientSandBox::Accounts() noexcept{
        QUrl path = _apiURL + "/user/accounts";
        return {};
    }

}
