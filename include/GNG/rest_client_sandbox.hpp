#pragma once

#include <QNetworkAccessManager>
#include "GNG/rest_domain.hpp"
#include <QNetworkReply>
#include <QJsonDocument>

#include "i_rest_client.hpp"

namespace GNG {

class RestClientSandBox : public IRestClient{

public:
    RestClientSandBox(const QString& token,
                      const QString& apiURL = RestApiSandboxURL) noexcept;

    bool Authorization() override;


    //! [0] Sandbox

    //! Выставление баланса по валютным позициям
    void SetCurrencyBalance(const QString& currency, double balance);

    //! Выставление баланса по инструментным позициям
    void SetPositionBalance();

    //! Удаление счета
    void Remove();

    //! Удаление всех позиций
    void Clear();

    //! [0] Sandbox

    //! [1] Orders
    QByteArray CreateLimitOrder(const QString& figi,
                                const QString& operation,
                                size_t lots,
                                double price,
                                const QString& brokID) override;

    QByteArray CreateMarketOrder(const QString& figi,
                                 const QString& operation,
                                 size_t lots,
                                 const QString& brokID) override;

    QByteArray CancelOrder(const QString& orderID,
                           const QString& brokID) override;


    //! [1] Orders

    std::vector<Account> Accounts() noexcept;

};

}
