#pragma once

#include "../types/SecurityId.hpp"
#include "../types/Offset8Padding2.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/Offset11Padding1.hpp"
#include "../types/LastPx.hpp"
#include "../types/FillQty.hpp"
#include "../types/TradedHiddenQty.hpp"
#include "../types/CxlQty.hpp"
#include "../types/AggressorTime.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TransactTime.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

#pragma pack(push, 1)

// ExecutionSummary_55Message
struct ExecutionSummary55Message {

    SecurityId security_id;
    Offset8Padding2 offset_8_padding_2;
    AggressorSide aggressor_side;
    Offset11Padding1 offset_11_padding_1;
    LastPx last_px;
    FillQty fill_qty;
    TradedHiddenQty traded_hidden_qty;
    CxlQty cxl_qty;
    AggressorTime aggressor_time;
    RptSeq rpt_seq;
    TransactTime transact_time;

    // parse method
    static ExecutionSummary55Message* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionSummary55Message*>(buffer);
    }

    // parse method const
    static const ExecutionSummary55Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionSummary55Message*>(buffer);
    }
};

#pragma pack(pop)
}
