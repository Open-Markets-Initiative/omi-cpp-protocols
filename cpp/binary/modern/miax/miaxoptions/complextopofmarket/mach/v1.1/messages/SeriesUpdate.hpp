#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/CallOrPut.hpp"
#include "../types/OpeningTime.hpp"
#include "../types/ClosingTime.hpp"
#include "../types/RestrictedOption.hpp"
#include "../types/LongTermOption.hpp"
#include "../types/ActiveOnMiax.hpp"
#include "../types/MiaxBboPostingIncrementIndicator.hpp"
#include "../types/LiquidityAcceptanceIncrementIndicator.hpp"
#include "../types/OpeningUnderlyingMarketCode.hpp"
#include "../types/PriorityQuoteWidth.hpp"
#include "../types/Reserved8.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate all Option series traded on MIAX for the current session. The product ID sent in this message is what will be disseminated in Top of Market BBO and Last Sale messages.
struct SeriesUpdate {

    Nanoseconds nanoseconds;
    ProductId product_id;
    UnderlyingSymbol underlying_symbol;
    SecuritySymbol security_symbol;
    ExpirationDate expiration_date;
    StrikePrice strike_price;
    CallOrPut call_or_put;
    OpeningTime opening_time;
    ClosingTime closing_time;
    RestrictedOption restricted_option;
    LongTermOption long_term_option;
    ActiveOnMiax active_on_miax;
    MiaxBboPostingIncrementIndicator miax_bbo_posting_increment_indicator;
    LiquidityAcceptanceIncrementIndicator liquidity_acceptance_increment_indicator;
    OpeningUnderlyingMarketCode opening_underlying_market_code;
    PriorityQuoteWidth priority_quote_width;
    Reserved8 reserved_8;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'P';

    // parse method
    static SeriesUpdate* parse(std::byte* buffer) {
        return reinterpret_cast<SeriesUpdate*>(buffer);
    }

    // parse method const
    static const SeriesUpdate* parse(const std::byte* buffer) {
        return reinterpret_cast<const SeriesUpdate*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SeriesUpdate* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SeriesUpdate*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
