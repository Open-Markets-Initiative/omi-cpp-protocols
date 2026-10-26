#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/MarketSide.hpp"
#include "../types/OptionId.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// For bandwidth efficiency reasons, this message can be published in either short or long format.
struct AddOrderMessageLongFormMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    OrderReferenceNumber order_reference_number;
    MarketSide market_side;
    OptionId option_id;
    PriceLong price_long;
    VolumeLong volume_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static AddOrderMessageLongFormMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMessageLongFormMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMessageLongFormMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMessageLongFormMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMessageLongFormMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderMessageLongFormMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
