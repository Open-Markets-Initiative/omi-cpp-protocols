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
#include "../types/AuctionInterestClearingPrice.hpp"
#include "../types/SsrFilingPrice.hpp"
#include "../types/IndicativeMatchPrice.hpp"
#include "../types/UpperCollar.hpp"
#include "../types/LowerCollar.hpp"
#include "../types/AuctionStatus.hpp"
#include "../types/FreezeStatus.hpp"
#include "../types/NumExtensions.hpp"
#include "../types/UnpairedQty.hpp"
#include "../types/UnpairedSide.hpp"
#include "../types/Reserved1.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::texasequities::integratedfeed::pillar::v2_5_g;

#pragma pack(push, 1)

// Imbalance Message
struct imbalance_message {

    struct fields_type {
        pillar_integratedfeed::source_time source_time;
        pillar_integratedfeed::source_time_ns source_time_ns;
        pillar_integratedfeed::symbol_index symbol_index;
        pillar_integratedfeed::symbol_seq_num symbol_seq_num;
        pillar_integratedfeed::reference_price reference_price;
        pillar_integratedfeed::paired_qty paired_qty;
        pillar_integratedfeed::total_imbalance_qty total_imbalance_qty;
        pillar_integratedfeed::market_imbalance_qty market_imbalance_qty;
        pillar_integratedfeed::auction_time auction_time;
        pillar_integratedfeed::auction_type auction_type;
        pillar_integratedfeed::imbalance_side imbalance_side;
        pillar_integratedfeed::continuous_book_clearing_price continuous_book_clearing_price;
        pillar_integratedfeed::auction_interest_clearing_price auction_interest_clearing_price;
        pillar_integratedfeed::ssr_filing_price ssr_filing_price;
        pillar_integratedfeed::indicative_match_price indicative_match_price;
        pillar_integratedfeed::upper_collar upper_collar;
        pillar_integratedfeed::lower_collar lower_collar;
        pillar_integratedfeed::auction_status auction_status;
        pillar_integratedfeed::freeze_status freeze_status;
        pillar_integratedfeed::num_extensions num_extensions;
        pillar_integratedfeed::unpaired_qty unpaired_qty;
        pillar_integratedfeed::unpaired_side unpaired_side;
        pillar_integratedfeed::reserved_1 reserved_1;
    };

    pillar_integratedfeed::message_header header = {std::uint16_t(sizeof(pillar_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::imbalance_message};

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
static_assert(offsetof(imbalance_message::fields_type, auction_interest_clearing_price) == 40, "unexpected offset of imbalance_message::fields_type::auction_interest_clearing_price");
static_assert(offsetof(imbalance_message::fields_type, ssr_filing_price) == 44, "unexpected offset of imbalance_message::fields_type::ssr_filing_price");
static_assert(offsetof(imbalance_message::fields_type, indicative_match_price) == 48, "unexpected offset of imbalance_message::fields_type::indicative_match_price");
static_assert(offsetof(imbalance_message::fields_type, upper_collar) == 52, "unexpected offset of imbalance_message::fields_type::upper_collar");
static_assert(offsetof(imbalance_message::fields_type, lower_collar) == 56, "unexpected offset of imbalance_message::fields_type::lower_collar");
static_assert(offsetof(imbalance_message::fields_type, auction_status) == 60, "unexpected offset of imbalance_message::fields_type::auction_status");
static_assert(offsetof(imbalance_message::fields_type, freeze_status) == 61, "unexpected offset of imbalance_message::fields_type::freeze_status");
static_assert(offsetof(imbalance_message::fields_type, num_extensions) == 62, "unexpected offset of imbalance_message::fields_type::num_extensions");
static_assert(offsetof(imbalance_message::fields_type, unpaired_qty) == 63, "unexpected offset of imbalance_message::fields_type::unpaired_qty");
static_assert(offsetof(imbalance_message::fields_type, unpaired_side) == 67, "unexpected offset of imbalance_message::fields_type::unpaired_side");
static_assert(offsetof(imbalance_message::fields_type, reserved_1) == 68, "unexpected offset of imbalance_message::fields_type::reserved_1");
static_assert(sizeof(imbalance_message::fields_type) == 69, "unexpected sizeof imbalance_message::fields_type");
static_assert(sizeof(imbalance_message) == sizeof(pillar_integratedfeed::message_header) + 69, "unexpected sizeof imbalance_message");

#pragma pack(pop)
}
