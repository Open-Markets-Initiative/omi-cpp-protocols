#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighIndicationPriceUpperLimitPriceBand.hpp"
#include "../types/LowIndicationPriceLowerLimitPriceBand.hpp"
#include "../types/BuyVolume.hpp"
#include "../types/SellVolume.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltReason.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/LimitUpLimitDownIndicator.hpp"

namespace siac::cts::output::cta::v2_9 {

#pragma pack(push, 1)

// The Trading Status message is transmitted when a Participant in a Cta eligible security, Local Issue or a Bond elects to notify CTS of an Opening Delay, a Trading Halt, a Trading Resume, a Price Indication or a Market Imbalance.
struct TradingStatusMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    LastPrice last_price;
    HighIndicationPriceUpperLimitPriceBand high_indication_price_upper_limit_price_band;
    LowIndicationPriceLowerLimitPriceBand low_indication_price_lower_limit_price_band;
    BuyVolume buy_volume;
    SellVolume sell_volume;
    SecurityStatus security_status;
    HaltReason halt_reason;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    LimitUpLimitDownIndicator limit_up_limit_down_indicator;

    // parse method
    static TradingStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradingStatusMessage*>(buffer);
    }

    // parse method const
    static const TradingStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
