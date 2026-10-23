#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/TradeId.hpp"
#include "../types/CorrectionNumber.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeSize.hpp"
#include "../types/TradeCondition.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate canceled Trades that are resulting from Trade cancellations or corrections on MIAX during the current trading session.
struct TradeCancelMessage {

    Nanoseconds nanoseconds;
    ProductId product_id;
    TradeId trade_id;
    CorrectionNumber correction_number;
    TradePrice trade_price;
    TradeSize trade_size;
    TradeCondition trade_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static TradeCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancelMessage*>(buffer);
    }

    // parse method const
    static const TradeCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeCancelMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const TradeCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
