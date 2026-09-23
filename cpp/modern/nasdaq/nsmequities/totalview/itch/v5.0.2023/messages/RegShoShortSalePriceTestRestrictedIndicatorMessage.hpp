#pragma once

#include "../types/LocateCode.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/RegShoAction.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Nasaq processes orders based on the most Reg SHO Restriction status value
struct RegShoShortSalePriceTestRestrictedIndicatorMessage {

    LocateCode locate_code;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Stock stock;
    RegShoAction reg_sho_action;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Y';

    // parse method
    static RegShoShortSalePriceTestRestrictedIndicatorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RegShoShortSalePriceTestRestrictedIndicatorMessage*>(buffer);
    }

    // parse method const
    static const RegShoShortSalePriceTestRestrictedIndicatorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RegShoShortSalePriceTestRestrictedIndicatorMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RegShoShortSalePriceTestRestrictedIndicatorMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const RegShoShortSalePriceTestRestrictedIndicatorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
