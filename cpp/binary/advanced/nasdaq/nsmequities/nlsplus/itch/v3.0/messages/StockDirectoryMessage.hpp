#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
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

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Stock Directory Message
struct stock_directory_message {

    struct fields_type {
        itch_nlsplus::stock stock;
        itch_nlsplus::market_category market_category;
        itch_nlsplus::financial_status_indicator financial_status_indicator;
        itch_nlsplus::round_lot_size round_lot_size;
        itch_nlsplus::round_lots_only round_lots_only;
        itch_nlsplus::issue_classification issue_classification;
        itch_nlsplus::issue_sub_type issue_sub_type;
        itch_nlsplus::authenticity authenticity;
        itch_nlsplus::short_sale_threshold_indicator short_sale_threshold_indicator;
        itch_nlsplus::ipo_flag ipo_flag;
        itch_nlsplus::luld_reference_price_tier luld_reference_price_tier;
        itch_nlsplus::etp_flag etp_flag;
        itch_nlsplus::etp_leverage_factor etp_leverage_factor;
        itch_nlsplus::inverse_indicator inverse_indicator;
        itch_nlsplus::bloomberg_id bloomberg_id;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::stock_directory_message};

    fields_type fields;

    // parse method
    static stock_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<stock_directory_message*>(buffer);
    }

    // parse method const
    static const stock_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const stock_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(stock_directory_message::fields_type, stock) == 0, "unexpected offset of stock_directory_message::fields_type::stock");
static_assert(offsetof(stock_directory_message::fields_type, market_category) == 8, "unexpected offset of stock_directory_message::fields_type::market_category");
static_assert(offsetof(stock_directory_message::fields_type, financial_status_indicator) == 9, "unexpected offset of stock_directory_message::fields_type::financial_status_indicator");
static_assert(offsetof(stock_directory_message::fields_type, round_lot_size) == 10, "unexpected offset of stock_directory_message::fields_type::round_lot_size");
static_assert(offsetof(stock_directory_message::fields_type, round_lots_only) == 14, "unexpected offset of stock_directory_message::fields_type::round_lots_only");
static_assert(offsetof(stock_directory_message::fields_type, issue_classification) == 15, "unexpected offset of stock_directory_message::fields_type::issue_classification");
static_assert(offsetof(stock_directory_message::fields_type, issue_sub_type) == 16, "unexpected offset of stock_directory_message::fields_type::issue_sub_type");
static_assert(offsetof(stock_directory_message::fields_type, authenticity) == 18, "unexpected offset of stock_directory_message::fields_type::authenticity");
static_assert(offsetof(stock_directory_message::fields_type, short_sale_threshold_indicator) == 19, "unexpected offset of stock_directory_message::fields_type::short_sale_threshold_indicator");
static_assert(offsetof(stock_directory_message::fields_type, ipo_flag) == 20, "unexpected offset of stock_directory_message::fields_type::ipo_flag");
static_assert(offsetof(stock_directory_message::fields_type, luld_reference_price_tier) == 21, "unexpected offset of stock_directory_message::fields_type::luld_reference_price_tier");
static_assert(offsetof(stock_directory_message::fields_type, etp_flag) == 22, "unexpected offset of stock_directory_message::fields_type::etp_flag");
static_assert(offsetof(stock_directory_message::fields_type, etp_leverage_factor) == 23, "unexpected offset of stock_directory_message::fields_type::etp_leverage_factor");
static_assert(offsetof(stock_directory_message::fields_type, inverse_indicator) == 27, "unexpected offset of stock_directory_message::fields_type::inverse_indicator");
static_assert(offsetof(stock_directory_message::fields_type, bloomberg_id) == 28, "unexpected offset of stock_directory_message::fields_type::bloomberg_id");
static_assert(sizeof(stock_directory_message::fields_type) == 40, "unexpected sizeof stock_directory_message::fields_type");
static_assert(sizeof(stock_directory_message) == sizeof(itch_nlsplus::message_header) + 40, "unexpected sizeof stock_directory_message");

#pragma pack(pop)
}
