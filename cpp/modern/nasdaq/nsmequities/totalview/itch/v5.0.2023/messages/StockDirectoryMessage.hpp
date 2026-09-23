#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
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
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Market data redistributors should process this message to populate the Financial Status Indicator (required display field) and the Market Category (recommended display field) for NASDAQ-listed issues.
struct StockDirectoryMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
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
    static const StockDirectoryMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const StockDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
