#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/SymbolName.hpp"
#include "../types/LongName.hpp"
#include "../types/Isin.hpp"
#include "../types/Exchange.hpp"
#include "../types/Instrument.hpp"
#include "../types/CfiCode.hpp"
#include "../types/ExpiryYear.hpp"
#include "../types/ExpiryMonth.hpp"
#include "../types/OptionType.hpp"
#include "../types/Strike.hpp"
#include "../types/UnderlyingTradeableInstrumentId.hpp"
#include "../types/PriceDisplayDecimals.hpp"
#include "../types/PriceFractionalDenominator.hpp"
#include "../types/PriceMinimumTick.hpp"
#include "../types/StrikePriceDecimalPosition.hpp"
#include "../types/StrikePriceFractionalDenominator.hpp"
#include "../types/StrikePriceMinimumTick.hpp"
#include "../types/LastTradingDate.hpp"
#include "../types/PriorDaySettlement.hpp"
#include "../types/Volatility.hpp"
#include "../types/Currency.hpp"
#include "../types/LotSizeOrFaceValue.hpp"
#include "../types/MaturityValue.hpp"
#include "../types/CouponRate.hpp"
#include "../types/PaymentsPerYear.hpp"
#include "../types/BlockLotSize.hpp"
#include "../types/ExpiryDate.hpp"
#include "../types/BasisOfQuotation.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// The Options Symbol Directory message describes options and warrants contracts.
struct OptionsSymbolDirectoryMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    SymbolName symbol_name;
    LongName long_name;
    Isin isin;
    Exchange exchange;
    Instrument instrument;
    CfiCode cfi_code;
    ExpiryYear expiry_year;
    ExpiryMonth expiry_month;
    OptionType option_type;
    Strike strike;
    UnderlyingTradeableInstrumentId underlying_tradeable_instrument_id;
    PriceDisplayDecimals price_display_decimals;
    PriceFractionalDenominator price_fractional_denominator;
    PriceMinimumTick price_minimum_tick;
    StrikePriceDecimalPosition strike_price_decimal_position;
    StrikePriceFractionalDenominator strike_price_fractional_denominator;
    StrikePriceMinimumTick strike_price_minimum_tick;
    LastTradingDate last_trading_date;
    PriorDaySettlement prior_day_settlement;
    Volatility volatility;
    Currency currency;
    LotSizeOrFaceValue lot_size_or_face_value;
    MaturityValue maturity_value;
    CouponRate coupon_rate;
    PaymentsPerYear payments_per_year;
    BlockLotSize block_lot_size;
    ExpiryDate expiry_date;
    BasisOfQuotation basis_of_quotation;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'h';

    // parse method
    static OptionsSymbolDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsSymbolDirectoryMessage*>(buffer);
    }

    // parse method const
    static const OptionsSymbolDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsSymbolDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsSymbolDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsSymbolDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
