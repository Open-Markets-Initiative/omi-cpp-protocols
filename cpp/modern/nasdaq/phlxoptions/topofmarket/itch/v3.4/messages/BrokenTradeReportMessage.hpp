#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/OriginalCrossId.hpp"
#include "../types/OriginalPrice.hpp"
#include "../types/OriginalVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The following message is used in the event that an options trade transaction is broken on the same business day that it is reported.
struct BrokenTradeReportMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    OriginalCrossId original_cross_id;
    OriginalPrice original_price;
    OriginalVolume original_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static BrokenTradeReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BrokenTradeReportMessage*>(buffer);
    }

    // parse method const
    static const BrokenTradeReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BrokenTradeReportMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const BrokenTradeReportMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const BrokenTradeReportMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
