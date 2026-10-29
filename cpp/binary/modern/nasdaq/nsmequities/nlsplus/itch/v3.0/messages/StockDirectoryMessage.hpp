#pragma once

#include "../types/Stock.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/RoundLotsOnly.hpp"
#include "../types/IssueClassification.hpp"
#include "../types/IssueSubType.hpp"
#include "../types/Authenticity.hpp"
#include "../types/ShortSaleThresholdIndicator.hpp"
#include "../types/IpoFlag.hpp"
#include "../types/LuldReferencePriceTier.hpp"
#include "../types/EtpFlag.hpp"
#include "../types/EtpLeverageFactor.hpp"
#include "../types/InverseIndicator.hpp"
#include "../types/BloombergId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Identifies the securities eligible for the trading session, disseminated at the start of each day.
struct StockDirectoryMessage {

    Stock stock;
    MarketCategory market_category;
    FinancialStatusIndicator financial_status_indicator;
    RoundLotSize round_lot_size;
    RoundLotsOnly round_lots_only;
    IssueClassification issue_classification;
    IssueSubType issue_sub_type;
    Authenticity authenticity;
    ShortSaleThresholdIndicator short_sale_threshold_indicator;
    IpoFlag ipo_flag;
    LuldReferencePriceTier luld_reference_price_tier;
    EtpFlag etp_flag;
    EtpLeverageFactor etp_leverage_factor;
    InverseIndicator inverse_indicator;
    BloombergId bloomberg_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static StockDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StockDirectoryMessage*>(buffer);
    }

    // parse method const
    static const StockDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StockDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StockDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StockDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
