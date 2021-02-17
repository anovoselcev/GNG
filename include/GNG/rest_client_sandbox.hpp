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


    QString GetInstrumentByFIGI(const QString& FIGI) override;

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

    //! Получение валютных активов клиента
    void GetCurrencies() override;

    std::vector<Account> Accounts() noexcept;

};

}
