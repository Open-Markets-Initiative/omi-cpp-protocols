#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/ReferenceNumber.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/Printable.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// These executions may be marked as non-printable. If the execution is marked as non-printed, it means that the contracts will be included into a later bulk print (e.g., in the case of auction executions). If a firm is looking to use the ITTO data in time-and-sales displays or volume calculations, NASDAQ recommends that firms ignore messages marked as non-printable to prevent double counting.
struct SingleSideExecutedWithPriceMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    ReferenceNumber reference_number;
    CrossNumber cross_number;
    MatchNumber match_number;
    Printable printable;
    PriceLong price_long;
    VolumeLong volume_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static SingleSideExecutedWithPriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SingleSideExecutedWithPriceMessage*>(buffer);
    }

    // parse method const
    static const SingleSideExecutedWithPriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SingleSideExecutedWithPriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SingleSideExecutedWithPriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SingleSideExecutedWithPriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
