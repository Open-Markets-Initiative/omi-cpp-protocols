#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/TsRecv.hpp"
#include "../types/RefPrice.hpp"
#include "../types/AuctionTime.hpp"
#include "../types/ContBookClrPrice.hpp"
#include "../types/AuctInterestClrPrice.hpp"
#include "../types/SsrFillingPrice.hpp"
#include "../types/IndMatchPrice.hpp"
#include "../types/UpperCollar.hpp"
#include "../types/LowerCollar.hpp"
#include "../types/PairedQty.hpp"
#include "../types/TotalImbalanceQty.hpp"
#include "../types/MarketImbalanceQty.hpp"
#include "../types/UnpairedQty.hpp"
#include "../types/AuctionType.hpp"
#include "../types/Side.hpp"
#include "../types/AuctionStatus.hpp"
#include "../types/FreezeStatus.hpp"
#include "../types/NumExtensions.hpp"
#include "../types/UnpairedSide.hpp"
#include "../types/SignificantImbalance.hpp"
#include "../types/Reserved1.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

// Imbalance Msg
struct imbalance_msg {

    struct fields_type {
        dbn_normalized::ts_recv ts_recv;
        dbn_normalized::ref_price ref_price;
        dbn_normalized::auction_time auction_time;
        dbn_normalized::cont_book_clr_price cont_book_clr_price;
        dbn_normalized::auct_interest_clr_price auct_interest_clr_price;
        dbn_normalized::ssr_filling_price ssr_filling_price;
        dbn_normalized::ind_match_price ind_match_price;
        dbn_normalized::upper_collar upper_collar;
        dbn_normalized::lower_collar lower_collar;
        dbn_normalized::paired_qty paired_qty;
        dbn_normalized::total_imbalance_qty total_imbalance_qty;
        dbn_normalized::market_imbalance_qty market_imbalance_qty;
        dbn_normalized::unpaired_qty unpaired_qty;
        dbn_normalized::auction_type auction_type;
        dbn_normalized::side side;
        dbn_normalized::auction_status auction_status;
        dbn_normalized::freeze_status freeze_status;
        dbn_normalized::num_extensions num_extensions;
        dbn_normalized::unpaired_side unpaired_side;
        dbn_normalized::significant_imbalance significant_imbalance;
        dbn_normalized::reserved_1 reserved_1;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::imbalance, {}, {}, {}};

    fields_type fields;

    // parse method
    static imbalance_msg* parse(std::byte* buffer) {
        return reinterpret_cast<imbalance_msg*>(buffer);
    }

    // parse method const
    static const imbalance_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const imbalance_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(imbalance_msg::fields_type, ts_recv) == 0, "unexpected offset of imbalance_msg::fields_type::ts_recv");
static_assert(offsetof(imbalance_msg::fields_type, ref_price) == 8, "unexpected offset of imbalance_msg::fields_type::ref_price");
static_assert(offsetof(imbalance_msg::fields_type, auction_time) == 16, "unexpected offset of imbalance_msg::fields_type::auction_time");
static_assert(offsetof(imbalance_msg::fields_type, cont_book_clr_price) == 24, "unexpected offset of imbalance_msg::fields_type::cont_book_clr_price");
static_assert(offsetof(imbalance_msg::fields_type, auct_interest_clr_price) == 32, "unexpected offset of imbalance_msg::fields_type::auct_interest_clr_price");
static_assert(offsetof(imbalance_msg::fields_type, ssr_filling_price) == 40, "unexpected offset of imbalance_msg::fields_type::ssr_filling_price");
static_assert(offsetof(imbalance_msg::fields_type, ind_match_price) == 48, "unexpected offset of imbalance_msg::fields_type::ind_match_price");
static_assert(offsetof(imbalance_msg::fields_type, upper_collar) == 56, "unexpected offset of imbalance_msg::fields_type::upper_collar");
static_assert(offsetof(imbalance_msg::fields_type, lower_collar) == 64, "unexpected offset of imbalance_msg::fields_type::lower_collar");
static_assert(offsetof(imbalance_msg::fields_type, paired_qty) == 72, "unexpected offset of imbalance_msg::fields_type::paired_qty");
static_assert(offsetof(imbalance_msg::fields_type, total_imbalance_qty) == 76, "unexpected offset of imbalance_msg::fields_type::total_imbalance_qty");
static_assert(offsetof(imbalance_msg::fields_type, market_imbalance_qty) == 80, "unexpected offset of imbalance_msg::fields_type::market_imbalance_qty");
static_assert(offsetof(imbalance_msg::fields_type, unpaired_qty) == 84, "unexpected offset of imbalance_msg::fields_type::unpaired_qty");
static_assert(offsetof(imbalance_msg::fields_type, auction_type) == 88, "unexpected offset of imbalance_msg::fields_type::auction_type");
static_assert(offsetof(imbalance_msg::fields_type, side) == 89, "unexpected offset of imbalance_msg::fields_type::side");
static_assert(offsetof(imbalance_msg::fields_type, auction_status) == 90, "unexpected offset of imbalance_msg::fields_type::auction_status");
static_assert(offsetof(imbalance_msg::fields_type, freeze_status) == 91, "unexpected offset of imbalance_msg::fields_type::freeze_status");
static_assert(offsetof(imbalance_msg::fields_type, num_extensions) == 92, "unexpected offset of imbalance_msg::fields_type::num_extensions");
static_assert(offsetof(imbalance_msg::fields_type, unpaired_side) == 93, "unexpected offset of imbalance_msg::fields_type::unpaired_side");
static_assert(offsetof(imbalance_msg::fields_type, significant_imbalance) == 94, "unexpected offset of imbalance_msg::fields_type::significant_imbalance");
static_assert(offsetof(imbalance_msg::fields_type, reserved_1) == 95, "unexpected offset of imbalance_msg::fields_type::reserved_1");
static_assert(sizeof(imbalance_msg::fields_type) == 96, "unexpected sizeof imbalance_msg::fields_type");
static_assert(sizeof(imbalance_msg) == sizeof(dbn_normalized::record_header) + 96, "unexpected sizeof imbalance_msg");

#pragma pack(pop)
}
