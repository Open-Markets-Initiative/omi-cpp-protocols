#pragma once

#include "../types/LocateCode.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/RegShoAction.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

#pragma pack(push, 1)

// In February 2011, the Securities and Exchange Commission (SEC) implemented changes to Rule 201 of the Regulation SHO (Reg SHO).
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
    static const RegShoShortSalePriceTestRestrictedIndicatorMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RegShoShortSalePriceTestRestrictedIndicatorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
