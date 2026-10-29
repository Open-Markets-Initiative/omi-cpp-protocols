#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/PairedQty.hpp"
#include "../types/TotalImbalanceQty.hpp"
#include "../types/MarketImbalanceQty.hpp"
#include "../types/AuctionTime.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ContinuousBookClearingPrice.hpp"
#include "../types/ClosingOnlyClearingPrice.hpp"
#include "../types/SsrFilingPrice.hpp"
#include "../types/IndicativeMatchPrice.hpp"
#include "../types/UpperCollar.hpp"
#include "../types/LowerCollar.hpp"
#include "../types/AuctionStatus.hpp"
#include "../types/FreezeStatus.hpp"
#include "../types/NumExtensions.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

namespace xdp_integratedfeed = ::nyse::amexequities::integratedfeed::xdp::v2_1_g;

#pragma pack(push, 1)

// Imbalance Message
struct imbalance_message {

    struct fields_type {
        xdp_integratedfeed::source_time source_time;
        xdp_integratedfeed::source_time_ns source_time_ns;
        xdp_integratedfeed::symbol_index symbol_index;
        xdp_integratedfeed::symbol_seq_num symbol_seq_num;
        xdp_integratedfeed::reference_price reference_price;
        xdp_integratedfeed::paired_qty paired_qty;
        xdp_integratedfeed::total_imbalance_qty total_imbalance_qty;
        xdp_integratedfeed::market_imbalance_qty market_imbalance_qty;
        xdp_integratedfeed::auction_time auction_time;
        xdp_integratedfeed::auction_type auction_type;
        xdp_integratedfeed::imbalance_side imbalance_side;
        xdp_integratedfeed::continuous_book_clearing_price continuous_book_clearing_price;
        xdp_integratedfeed::closing_only_clearing_price closing_only_clearing_price;
        xdp_integratedfeed::ssr_filing_price ssr_filing_price;
        xdp_integratedfeed::indicative_match_price indicative_match_price;
        xdp_integratedfeed::upper_collar upper_collar;
        xdp_integratedfeed::lower_collar lower_collar;
        xdp_integratedfeed::auction_status auction_status;
        xdp_integratedfeed::freeze_status freeze_status;
        xdp_integratedfeed::num_extensions num_extensions;
    };

    xdp_integratedfeed::message_header header = {std::uint16_t(sizeof(xdp_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::imbalance_message};

    fields_type fields;

    // parse method
    static imbalance_message* parse(std::byte* buffer) {
        return reinterpret_cast<imbalance_message*>(buffer);
    }

    // parse method const
    static const imbalance_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const imbalance_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(imbalance_message::fields_type, source_time) == 0, "unexpected offset of imbalance_message::fields_type::source_time");
static_assert(offsetof(imbalance_message::fields_type, source_time_ns) == 4, "unexpected offset of imbalance_message::fields_type::source_time_ns");
static_assert(offsetof(imbalance_message::fields_type, symbol_index) == 8, "unexpected offset of imbalance_message::fields_type::symbol_index");
static_assert(offsetof(imbalance_message::fields_type, symbol_seq_num) == 12, "unexpected offset of imbalance_message::fields_type::symbol_seq_num");
static_assert(offsetof(imbalance_message::fields_type, reference_price) == 16, "unexpected offset of imbalance_message::fields_type::reference_price");
static_assert(offsetof(imbalance_message::fields_type, paired_qty) == 20, "unexpected offset of imbalance_message::fields_type::paired_qty");
static_assert(offsetof(imbalance_message::fields_type, total_imbalance_qty) == 24, "unexpected offset of imbalance_message::fields_type::total_imbalance_qty");
static_assert(offsetof(imbalance_message::fields_type, market_imbalance_qty) == 28, "unexpected offset of imbalance_message::fields_type::market_imbalance_qty");
static_assert(offsetof(imbalance_message::fields_type, auction_time) == 32, "unexpected offset of imbalance_message::fields_type::auction_time");
static_assert(offsetof(imbalance_message::fields_type, auction_type) == 34, "unexpected offset of imbalance_message::fields_type::auction_type");
static_assert(offsetof(imbalance_message::fields_type, imbalance_side) == 35, "unexpected offset of imbalance_message::fields_type::imbalance_side");
static_assert(offsetof(imbalance_message::fields_type, continuous_book_clearing_price) == 36, "unexpected offset of imbalance_message::fields_type::continuous_book_clearing_price");
static_assert(offsetof(imbalance_message::fields_type, closing_only_clearing_price) == 40, "unexpected offset of imbalance_message::fields_type::closing_only_clearing_price");
static_assert(offsetof(imbalance_message::fields_type, ssr_filing_price) == 44, "unexpected offset of imbalance_message::fields_type::ssr_filing_price");
static_assert(offsetof(imbalance_message::fields_type, indicative_match_price) == 48, "unexpected offset of imbalance_message::fields_type::indicative_match_price");
static_assert(offsetof(imbalance_message::fields_type, upper_collar) == 52, "unexpected offset of imbalance_message::fields_type::upper_collar");
static_assert(offsetof(imbalance_message::fields_type, lower_collar) == 56, "unexpected offset of imbalance_message::fields_type::lower_collar");
static_assert(offsetof(imbalance_message::fields_type, auction_status) == 60, "unexpected offset of imbalance_message::fields_type::auction_status");
static_assert(offsetof(imbalance_message::fields_type, freeze_status) == 61, "unexpected offset of imbalance_message::fields_type::freeze_status");
static_assert(offsetof(imbalance_message::fields_type, num_extensions) == 62, "unexpected offset of imbalance_message::fields_type::num_extensions");
static_assert(sizeof(imbalance_message::fields_type) == 63, "unexpected sizeof imbalance_message::fields_type");
static_assert(sizeof(imbalance_message) == sizeof(xdp_integratedfeed::message_header) + 63, "unexpected sizeof imbalance_message");

#pragma pack(pop)
}
