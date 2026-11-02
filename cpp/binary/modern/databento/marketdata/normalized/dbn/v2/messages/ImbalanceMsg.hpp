#pragma once

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

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// An auction imbalance message; the record of the imbalance schema
struct ImbalanceMsg {

    TsRecv ts_recv;
    RefPrice ref_price;
    AuctionTime auction_time;
    ContBookClrPrice cont_book_clr_price;
    AuctInterestClrPrice auct_interest_clr_price;
    SsrFillingPrice ssr_filling_price;
    IndMatchPrice ind_match_price;
    UpperCollar upper_collar;
    LowerCollar lower_collar;
    PairedQty paired_qty;
    TotalImbalanceQty total_imbalance_qty;
    MarketImbalanceQty market_imbalance_qty;
    UnpairedQty unpaired_qty;
    AuctionType auction_type;
    Side side;
    AuctionStatus auction_status;
    FreezeStatus freeze_status;
    NumExtensions num_extensions;
    UnpairedSide unpaired_side;
    SignificantImbalance significant_imbalance;
    Reserved1 reserved_1;

    // parse method
    static ImbalanceMsg* parse(std::byte* buffer) {
        return reinterpret_cast<ImbalanceMsg*>(buffer);
    }

    // parse method const
    static const ImbalanceMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const ImbalanceMsg*>(buffer);
    }
};

#pragma pack(pop)
}
