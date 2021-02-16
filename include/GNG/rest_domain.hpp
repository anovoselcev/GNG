#pragma once
#include <QString>
#include <QtDebug>
#include <QDateTime>
#include <vector>

namespace GNG {

inline void log(const QString& str) {
    qDebug() << QDateTime::currentDateTimeUtc().toString() << ": " << str;
}

inline void log(QString&& str) {
    qDebug() << QDateTime::currentDateTimeUtc().toString() << ": " << str;
}

namespace Currency {
    const inline QString RUB = "RUB";
    const inline QString USD = "USD";
    const inline QString EUR = "EUR";
    const inline QString TRY = "TRY";
    const inline QString JPY = "JPY";
    const inline QString CNY = "CNY";
    const inline QString CHF = "CHF";
    const inline QString GBP = "GBP";
    const inline QString HKD = "HKD";
}

namespace OperationType {
    const inline QString BUY                = "Buy";
    const inline QString SELL               = "Sell";
    const inline QString BrokerCommission   = "BrokerCommission";
    const inline QString ExchangeCommission = "ExchangeCommission";
    const inline QString ServiceCommission  = "ServiceCommission";
    const inline QString MarginCommission   = "MarginCommission";
    const inline QString OtherCommission    = "OtherCommission";
    const inline QString PayIn              = "PayIn";
    const inline QString PayOut             = "PayOut";
    const inline QString Tax                = "Tax";
    const inline QString TaxLucre           = "TaxLucre";
    const inline QString TaxDividend        = "TaxDividend";
    const inline QString TaxCoupon          = "TaxCoupon";
    const inline QString TaxBack            = "TaxBack";
    const inline QString Repayment          = "Repayment";
    const inline QString PartRepayment      = "PartRepayment";
    const inline QString Coupon             = "Coupon";
    const inline QString Dividend           = "Dividend";
    const inline QString SecurityIn         = "SecurityIn";
    const inline QString SecurityOut        = "SecurityOut";
    const inline QString BuyCard            = "BuyCard";
}

namespace OrderStatus {
    const inline QString New            = "New";
    const inline QString PartiallyFill  = "PartiallyFill";
    const inline QString Fill           = "Fill";
    const inline QString Cancelled      = "Cancelled";
    const inline QString Replaced       = "Replaced";
    const inline QString PendingCancel  = "PendingCancel";
    const inline QString Rejected       = "Rejected";
    const inline QString PendingReplace = "PendingReplace";
    const inline QString PendingNew     = "PendingNew";

}

namespace OperationStatus {
    const inline QString Done     = "Done";
    const inline QString Decline  = "Decline";
    const inline QString Progress = "Progress";
}

namespace InstrumentType {
    const inline QString Stock    = "Stock";
    const inline QString Currency = "Currency";
    const inline QString Bond     = "Bond";
    const inline QString Etf      = "Etf";
}

namespace OrderType {
    const inline QString Limit  = "Limit";
    const inline QString Market = "Market";
}

namespace AccountType {
    const inline QString AccountTinkoff    = "Tinkoff";
    const inline QString AccountTinkoffIIS = "TinkoffIis";
}

struct Account{
    QString Type; //json:"brokerAccountType"
    QString ID;   //json:"brokerAccountId"
};

struct MoneyAmount{
    QString Currency;
    double  Value;
};

struct PlacedOrder{
    QString     ID;
    QString     Operation;
    QString     Status;
    QString     RejectReason;
    int32_t     RequestedLots;
    int32_t     ExecutedLots;
    MoneyAmount Commission;
    QString     Message;
};

struct Order{
    QString ID;             //json:"orderId"
    QString FIGI;           //json:"figi"
    QString Operation;      //json:"operation"
    QString Status;         //json:"status"
    int32_t RequestedLots;  //json:"requestedLots"
    int32_t ExecutedLots;   //json:"executedLots"
    QString Type;           //json:"type"
    double  Price;          //json:"price"
};

struct PositionBalance{
    QString     FIGI;                       //json:"figi"
    QString     Ticker;                     //json:"ticker"
    QString     ISIN;                       //json:"isin"
    QString     InstrumentType;             //json:"instrumentType"
    double      Balance;                    //json:"balance"
    double      Blocked;                    //json:"blocked"
    int32_t     Lots;                       //json:"lots"
    MoneyAmount ExpectedYield;              //json:"expectedYield"
    MoneyAmount AveragePositionPrice;       //json:"averagePositionPrice"
    MoneyAmount AveragePositionPriceNoNkd;  //json:"averagePositionPriceNoNkd"
    QString     Name;                       //json:"name"
};

struct CurrencyBalance{
    QString Currency; //json:"currency"
    double  Balance;  //json:"balance"
    double  Blocked;  //json:"blocked"
};

struct Portfolio{
    std::vector<PositionBalance> Positions;
    std::vector<CurrencyBalance> Currencies;
};

struct Instrument {
    QString FIGI;             //json:"figi"
    QString Ticker;           //json:"ticker"
    QString ISIN;             //json:"isin"
    QString Name;             //json:"name"
    double  MinPriceIncrement;//json:"minPriceIncrement"
    int32_t Lot;              //json:"lot"
    QString Currency;         //json:"currency"
    QString Type;             //json:"type"
};


struct Trade {
    QString ID;       //json:"tradeId"
    QString DateTime; //json:"date"
    double  Price;    //json:"price"
    int32_t Quantity; //json:"quantity"
};

struct Operation {
    QString             ID;                 //json:"id"
    QString             Status;             //json:"status"
    std::vector<Trade>  Trades;             //json:"trades"
    MoneyAmount         Commission;         //json:"commission"
    QString             Currency;           //json:"currency"
    double              Payment;            //json:"payment"
    double              Price;              //json:"price"
    int32_t             Quantity;           //json:"quantity"
    int32_t             QuantityExecuted;   //json:"quantityExecuted"
    QString             FIGI;               //json:"figi"
    QString             InstrumentType;     //json:"instrumentType"
    bool                IsMarginCall;       //json:"isMarginCall"
    QString             DateTime;           //json:"date"
    QString             OperationType;      //json:"operationType"
};

struct RestPriceQuantity {
    double Price;    //json:"price"
    double Quantity; //json:"quantity"
};

struct RestOrderBook {
    QString                        FIGI;                //json:"figi"
    int32_t                        Depth;               //json:"depth"
    std::vector<RestPriceQuantity> Bids;                //json:"bids"
    std::vector<RestPriceQuantity> Asks;                //json:"asks"
    QString                        TradeStatus;         //json:"tradeStatus"
    double                         MinPriceIncrement;   //json:"minPriceIncrement"
    double                         LastPrice;           //json:"lastPrice,omitempty"
    double                         ClosePrice;          //json:"closePrice,omitempty"
    double                         LimitUp;             //json:"limitUp,omitempty"
    double                         LimitDown;           //json:"limitDown,omitempty"
    double                         FaceValue;           //json:"faceValue,omitempty"
};

}
