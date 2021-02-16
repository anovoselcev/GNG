#include "GNG/i_rest_client.hpp"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QEventLoop>

namespace GNG {

IRestClient::IRestClient(const QString &token,
                         const QString &apiURL) noexcept
                         : _token(token),
                           _apiURL(apiURL){}

QNetworkReply *IRestClient::SendPostRequest(const QUrl &path,
                                            const QJsonObject &json){
    QNetworkRequest req;
    req.setUrl(path);
    req.setRawHeader(QByteArray("Authorization"),
                     QByteArray("Bearer ") + _token.toUtf8());

    auto reply = post(req, json.isEmpty() ? QByteArray() : QJsonDocument(json).toJson());

    //Блочим?
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply;
}

QNetworkReply* IRestClient::SendGetRequest(const QUrl &path){
    QNetworkRequest req;
    req.setUrl(path);
    req.setRawHeader(QByteArray("Authorization"),
                     QByteArray("Bearer ") + _token.toUtf8());
    auto reply = get(req);

    //Блочим?
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply;
}

}
