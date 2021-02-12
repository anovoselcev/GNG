#pragma once
#include <QString>

namespace GNG {

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

}
