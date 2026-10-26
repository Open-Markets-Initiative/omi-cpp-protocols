#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/MarketSide.hpp"
#include "../types/OptionId.hpp"
#include "../types/PriceShort.hpp"
#include "../types/VolumeShort.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// For bandwidth efficiency reasons, this message can be published in either short or long format.
struct AddOrderMessageShortMessageForm {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    OrderReferenceNumber order_reference_number;
    MarketSide market_side;
    OptionId option_id;
    PriceShort price_short;
    VolumeShort volume_short;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'a';

    // parse method
    static AddOrderMessageShortMessageForm* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMessageShortMessageForm*>(buffer);
    }

    // parse method const
    static const AddOrderMessageShortMessageForm* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMessageShortMessageForm*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMessageShortMessageForm* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderMessageShortMessageForm*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
