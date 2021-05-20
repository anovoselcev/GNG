#include "GNG/rest_client_sandbox.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>


namespace GNG {

RestClientSandBox::RestClientSandBox(const QString& token,
                                     const QString& api) noexcept
                                    : IRestClient(token, api){}

bool RestClientSandBox::Authorization(){

    QUrl url = _apiURL + "/sandbox/register";

    auto reply = SendPostRequest(url, QJsonObject());

    if(!isReplyValid(reply))
        return false;

    auto data = QJsonDocument::fromJson(reply->readAll());

    account.Type = data.object().take("payload").toObject().take("brokerAccountType").toString();
    account.ID = data.object().take("payload").toObject().take("brokerAccountId").toString();

    // Should i do this: reply->deleteLater(); ?

    return true;
}

void RestClientSandBox::SetCurrencyBalance(const QString& currency,
                                           double balance){
    QUrl url = _apiURL + "/sandbox/currencies/balance";

    QJsonObject body;
    body.insert("currency", currency);
    body.insert("balance", balance);
    body.insert("brokerAccountId,omitempty", account.ID);

    auto reply = SendPostRequest(url, body);

    if(!isReplyValid(reply))
        return;

    qDebug() << "SetCurrencyBalance Reply:";
    log(reply->readAll());
}

QByteArray RestClientSandBox::CreateLimitOrder(const QString &figi,
                                               const QString &operation,
                                               size_t lots,
                                               double price,
                                               const QString &brokID){
    QUrl url = _apiURL
            + "/sandbox/orders/limit-order?figi="
            + figi
            + "&brokerAccountId=" + brokID;

    QJsonObject body;
    body.insert("lots", QString::number(lots));
    body.insert("operation", operation);
    body.insert("price", QString::number(price));

    auto reply = SendPostRequest(url, body);

    if(!isReplyValid(reply))
        return {};

    qDebug() << "CreateLimitOrder Reply:";
    auto data = reply->readAll();
    log(data);
    return data;
}

QByteArray RestClientSandBox::CreateMarketOrder(const QString &figi,
                                                const QString &operation,
                                                size_t lots,
                                                const QString &brokID){
    QUrl url = _apiURL
            + "/sandbox/orders/market-order?figi="
            + figi
            + "&brokerAccountId=" + brokID;

    QJsonObject body;
    body.insert("lots", QString::number(lots));
    body.insert("operation", operation);

    auto reply = SendPostRequest(url, body);

    if(!isReplyValid(reply))
        return {};

    qDebug() << "CreateMarketOrder Reply:";
    auto data = reply->readAll();
    log(data);
    return data;
}

QByteArray RestClientSandBox::CancelOrder(const QString &orderID,
                                          const QString &brokID){
    QUrl url = _apiURL
            + "/sandbox/orders/cancel?orderId="
            + orderID
            + "&brokerAccountId=" + brokID;

    QJsonObject body;

    auto reply = SendPostRequest(url, body);

    if(!isReplyValid(reply))
        return {};

    qDebug() << "CancelOrder Reply:";
    auto data = reply->readAll();
    log(data);
    return data;
}


std::vector<Account> RestClientSandBox::Accounts() noexcept{
    QUrl path = _apiURL + "/user/accounts";
    return {};
}

}
