#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/AuctionCollarReferencePrice.hpp"
#include "../types/UpperAuctionCollarPrice.hpp"
#include "../types/LowerAuctionCollarPrice.hpp"
#include "../types/AuctionCollarExtension.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Luld Auction Collar Message
struct luld_auction_collar_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::stock stock;
        itch_totalview::auction_collar_reference_price auction_collar_reference_price;
        itch_totalview::upper_auction_collar_price upper_auction_collar_price;
        itch_totalview::lower_auction_collar_price lower_auction_collar_price;
        itch_totalview::auction_collar_extension auction_collar_extension;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::luld_auction_collar_message};

    fields_type fields;

    // parse method
    static luld_auction_collar_message* parse(std::byte* buffer) {
        return reinterpret_cast<luld_auction_collar_message*>(buffer);
    }

    // parse method const
    static const luld_auction_collar_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const luld_auction_collar_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(luld_auction_collar_message::fields_type, stock_locate) == 0, "unexpected offset of luld_auction_collar_message::fields_type::stock_locate");
static_assert(offsetof(luld_auction_collar_message::fields_type, tracking_number) == 2, "unexpected offset of luld_auction_collar_message::fields_type::tracking_number");
static_assert(offsetof(luld_auction_collar_message::fields_type, timestamp) == 4, "unexpected offset of luld_auction_collar_message::fields_type::timestamp");
static_assert(offsetof(luld_auction_collar_message::fields_type, stock) == 10, "unexpected offset of luld_auction_collar_message::fields_type::stock");
static_assert(offsetof(luld_auction_collar_message::fields_type, auction_collar_reference_price) == 18, "unexpected offset of luld_auction_collar_message::fields_type::auction_collar_reference_price");
static_assert(offsetof(luld_auction_collar_message::fields_type, upper_auction_collar_price) == 22, "unexpected offset of luld_auction_collar_message::fields_type::upper_auction_collar_price");
static_assert(offsetof(luld_auction_collar_message::fields_type, lower_auction_collar_price) == 26, "unexpected offset of luld_auction_collar_message::fields_type::lower_auction_collar_price");
static_assert(offsetof(luld_auction_collar_message::fields_type, auction_collar_extension) == 30, "unexpected offset of luld_auction_collar_message::fields_type::auction_collar_extension");
static_assert(sizeof(luld_auction_collar_message::fields_type) == 34, "unexpected sizeof luld_auction_collar_message::fields_type");
static_assert(sizeof(luld_auction_collar_message) == sizeof(message_header) + 34, "unexpected sizeof luld_auction_collar_message");

#pragma pack(pop)
}
