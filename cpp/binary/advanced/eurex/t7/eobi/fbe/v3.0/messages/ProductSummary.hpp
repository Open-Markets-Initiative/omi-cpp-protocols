#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/TradSesStatus.hpp"
#include "../types/FastMarketIndicator.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Product Summary
struct product_summary {

    struct fields_type {
        fbe_eobi::last_msg_seq_num_processed last_msg_seq_num_processed;
        fbe_eobi::trading_session_id trading_session_id;
        fbe_eobi::trading_session_sub_id trading_session_sub_id;
        fbe_eobi::trad_ses_status trad_ses_status;
        fbe_eobi::fast_market_indicator fast_market_indicator;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::product_summary, {}};

    fields_type fields;

    // parse method
    static product_summary* parse(std::byte* buffer) {
        return reinterpret_cast<product_summary*>(buffer);
    }

    // parse method const
    static const product_summary* parse(const std::byte* buffer) {
        return reinterpret_cast<const product_summary*>(buffer);
    }

};

// layout verification
static_assert(offsetof(product_summary::fields_type, last_msg_seq_num_processed) == 0, "unexpected offset of product_summary::fields_type::last_msg_seq_num_processed");
static_assert(offsetof(product_summary::fields_type, trading_session_id) == 4, "unexpected offset of product_summary::fields_type::trading_session_id");
static_assert(offsetof(product_summary::fields_type, trading_session_sub_id) == 5, "unexpected offset of product_summary::fields_type::trading_session_sub_id");
static_assert(offsetof(product_summary::fields_type, trad_ses_status) == 6, "unexpected offset of product_summary::fields_type::trad_ses_status");
static_assert(offsetof(product_summary::fields_type, fast_market_indicator) == 7, "unexpected offset of product_summary::fields_type::fast_market_indicator");
static_assert(sizeof(product_summary::fields_type) == 8, "unexpected sizeof product_summary::fields_type");
static_assert(sizeof(product_summary) == sizeof(fbe_eobi::message_header_comp) + 8, "unexpected sizeof product_summary");

#pragma pack(pop)
}
