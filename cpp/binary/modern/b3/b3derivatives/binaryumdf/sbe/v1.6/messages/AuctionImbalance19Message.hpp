#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../bitfields/ImbalanceCondition.hpp"
#include "../types/MdEntrySizeQuantityOptional.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

#pragma pack(push, 1)

// AuctionImbalance_19Message
struct AuctionImbalance19Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    MdUpdateAction md_update_action;
    ImbalanceCondition imbalance_condition;
    MdEntrySizeQuantityOptional md_entry_size_quantity_optional;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static AuctionImbalance19Message* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionImbalance19Message*>(buffer);
    }

    // parse method const
    static const AuctionImbalance19Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionImbalance19Message*>(buffer);
    }
};

#pragma pack(pop)
}
