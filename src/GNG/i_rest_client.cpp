#include "GNG/i_rest_client.hpp"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>

namespace GNG {

IRestClient::IRestClient(const QString &token,
                         const QString &apiURL) noexcept
                         : _manager(std::make_unique<QNetworkAccessManager>()),
                           _token(token),
                           _apiURL(apiURL){}

QNetworkReply *IRestClient::SendPostRequest(const QUrl &path,
                                            const QJsonObject &json){
    QNetworkRequest req;
    req.setUrl(path);
    req.setRawHeader(QByteArray("Authorization"),
                     QByteArray("Bearer ") + _token.toUtf8());

    auto reply = _manager->post(req, json.isEmpty() ? QByteArray() : QJsonDocument(json).toJson());

    //Блочим?
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply;
}

QNetworkReply* IRestClient::SendGetRequest(const QUrl &path) const{
    QNetworkRequest req;
    req.setUrl(path);
    req.setRawHeader(QByteArray("Authorization"),
                     QByteArray("Bearer ") + _token.toUtf8());
    auto reply = _manager->get(req);

    //Блочим?
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply;
}

bool IRestClient::isReplyValid(QNetworkReply* reply) const noexcept{
    if(reply->error() != QNetworkReply::NoError) {
        log(reply->errorString());
        log(reply->readAll());
        return false;
    }
    return true;
}

QByteArray IRestClient::Get(const QUrl& url) const{
    auto reply = SendGetRequest(url);

    if(!isReplyValid(reply))
        return QByteArray();

    qDebug() << "Get Reply:";
    log(reply->readAll());
    return reply->readAll();
}


QString IRestClient::modifyDateForURL(const QString& date) const noexcept{
    QString result(40, ' ');
//    size_t size = date.size();
//    date.resize(40);

//    for(uint8_t i = 31, j = 39; i >= 0; i--){
//        if(date[i] != ':' && date[i] != '+')
//            date[j--] = date[i];
//        else if(date[i] == ':'){
//            date[j--] = 'A';
//            date[j--] = '3';
//            date[j--] = '%';
//        }
//        else{
//            date[j--] = 'B';
//            date[j--] = '2';
//            date[j--] = '%';
//        }
//    }

    for(uint8_t i = 0, j = 0; i < date.size(); i++){
        if(date[i] != ':' && date[i] != '+')
            result[j++] = date[i];
        else if(date[i] == ':'){
            result[j++] = '%';
            result[j++] = '3';
            result[j++] = 'A';

        }
        else{
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = 'B';
        }
    }
    return result;
}

QByteArray IRestClient::GetOrders() const{
    QUrl url = _apiURL + "/orders" + "?brokerAccountId=" + account.ID;
    return Get(url);
}

QByteArray IRestClient::GetPortfolio() const{
    QUrl url = _apiURL + "/portfolio" + "?brokerAccountId=" + account.ID;
    return Get(url);
}

QByteArray IRestClient::GetCurrencies() const{
    QUrl url = _apiURL + "/portfolio/currencies" + "?brokerAccountId=" + account.ID;
    return Get(url);
}

QByteArray IRestClient::GetStocks() const{
    QUrl url = _apiURL + "/market/stocks" + "?brokerAccountId=" + account.ID;
    return Get(url);
}

QByteArray IRestClient::GetBonds() const{
    QUrl url = _apiURL + "/market/bonds" + "?brokerAccountId=" + account.ID;
    return Get(url);
}

QByteArray IRestClient::GetETF() const{
    QUrl url = _apiURL + "/market/etfs" + "?brokerAccountId=" + account.ID;
    return Get(url);
}

QByteArray IRestClient::GetCurrenciesPair() const{
    QUrl url = _apiURL + "/market/currencies" + "?brokerAccountId=" + account.ID;
    return Get(url);
}

QByteArray IRestClient::GetAccounts() const{
    QUrl url = _apiURL + "/user/accounts";
    return Get(url);
}

QByteArray IRestClient::GetInstrumentByTicker(const QString &ticker) const{
    QUrl url = _apiURL + "/market/search/by-ticker?ticker=" + ticker;
    return Get(url);
}

QByteArray IRestClient::GetInstrumentByFIGI(const QString &FIGI) const{
    QUrl url = _apiURL + "/market/search/by-figi?figi=" + FIGI;
    return Get(url);
}

QByteArray IRestClient::GetOrderBookByFIGI(const QString &FIGI,
                                           uint32_t depth) const{
    QUrl url = _apiURL + "/market/orderbook?depth="
                       + QString::number(depth)
                       + "&figi=" + FIGI;
    return Get(url);
}

QByteArray IRestClient::GetCandlesByFIGI(const QString &FIGI,
                                         const QString &from,
                                         const QString &to,
                                         const QString &interval) const{
    QUrl url = _apiURL + "/market/candles?"
                       + "figi=" + FIGI
                       + "&from=" + modifyDateForURL(from)
                       + "&to="   + modifyDateForURL(to)
                       + "&interval=" + interval;
    return Get(url);
}


}
