// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/BestBidAndOfferMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/MbbPrice.hpp"
#include "../types/MbbSize.hpp"
#include "../types/MboPrice.hpp"
#include "../types/MboSize.hpp"
#include "../types/MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

#pragma pack(push, 1)

// Best Bid And Offer Message
struct best_bid_and_offer_message {

    struct fields_type {
        mach_topofmarket::timestamp timestamp;
        mach_topofmarket::instrument_id instrument_id;
        mach_topofmarket::mbb_price mbb_price;
        mach_topofmarket::mbb_size mbb_size;
        mach_topofmarket::mbo_price mbo_price;
        mach_topofmarket::mbo_size mbo_size;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::best_bid_and_offer_message;

    fields_type fields;

    // parse method
    static best_bid_and_offer_message* parse(std::byte* buffer) {
        return reinterpret_cast<best_bid_and_offer_message*>(buffer);
    }

    // parse method const
    static const best_bid_and_offer_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const best_bid_and_offer_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(best_bid_and_offer_message::fields_type, timestamp) == 0, "unexpected offset of best_bid_and_offer_message::fields_type::timestamp");
static_assert(offsetof(best_bid_and_offer_message::fields_type, instrument_id) == 8, "unexpected offset of best_bid_and_offer_message::fields_type::instrument_id");
static_assert(offsetof(best_bid_and_offer_message::fields_type, mbb_price) == 12, "unexpected offset of best_bid_and_offer_message::fields_type::mbb_price");
static_assert(offsetof(best_bid_and_offer_message::fields_type, mbb_size) == 20, "unexpected offset of best_bid_and_offer_message::fields_type::mbb_size");
static_assert(offsetof(best_bid_and_offer_message::fields_type, mbo_price) == 24, "unexpected offset of best_bid_and_offer_message::fields_type::mbo_price");
static_assert(offsetof(best_bid_and_offer_message::fields_type, mbo_size) == 32, "unexpected offset of best_bid_and_offer_message::fields_type::mbo_size");
static_assert(sizeof(best_bid_and_offer_message::fields_type) == 36, "unexpected sizeof best_bid_and_offer_message::fields_type");
static_assert(sizeof(best_bid_and_offer_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 36, "unexpected sizeof best_bid_and_offer_message");

#pragma pack(pop)
}
