#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/RegShoAction.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

#pragma pack(push, 1)

// Nasdaq introduced the Reg SHO Short Sale Price Test Restricted Indicator message format.
struct RegShoRestrictionMessage {

    TrackingNumber tracking_number;
    TimeStamp time_stamp;
    Stock stock;
    RegShoAction reg_sho_action;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Y';

    // parse method
    static RegShoRestrictionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RegShoRestrictionMessage*>(buffer);
    }

    // parse method const
    static const RegShoRestrictionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RegShoRestrictionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RegShoRestrictionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RegShoRestrictionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
