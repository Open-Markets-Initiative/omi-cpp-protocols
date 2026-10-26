#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Symbol.hpp"
#include "../types/LongName.hpp"
#include "../types/Isin.hpp"
#include "../types/FinancialProduct.hpp"
#include "../types/TradingCurrency.hpp"
#include "../types/DecimalsInPrice.hpp"
#include "../types/DecimalsInNominalValue.hpp"
#include "../types/OddLotSize.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/BlockLotSize.hpp"
#include "../types/NominalValue.hpp"
#include "../types/NumberOfLegs.hpp"
#include "../types/UnderlyingOrderbookId.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/DecimalsInStrikePrice.hpp"
#include "../types/PutOrCall.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Disseminated for all active securities at start of day or intra-day.
struct OrderBookDirectory {

    Nanoseconds nanoseconds;
    OrderBookId order_book_id;
    Symbol symbol;
    LongName long_name;
    Isin isin;
    FinancialProduct financial_product;
    TradingCurrency trading_currency;
    DecimalsInPrice decimals_in_price;
    DecimalsInNominalValue decimals_in_nominal_value;
    OddLotSize odd_lot_size;
    RoundLotSize round_lot_size;
    BlockLotSize block_lot_size;
    NominalValue nominal_value;
    NumberOfLegs number_of_legs;
    UnderlyingOrderbookId underlying_orderbook_id;
    StrikePrice strike_price;
    ExpirationDate expiration_date;
    DecimalsInStrikePrice decimals_in_strike_price;
    PutOrCall put_or_call;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static OrderBookDirectory* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookDirectory*>(buffer);
    }

    // parse method const
    static const OrderBookDirectory* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookDirectory*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderBookDirectory* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderBookDirectory*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
