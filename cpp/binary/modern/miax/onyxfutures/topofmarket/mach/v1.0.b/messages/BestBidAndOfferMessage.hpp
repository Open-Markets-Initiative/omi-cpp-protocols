#pragma once

#include "../types/Timestamp.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/MbbPrice.hpp"
#include "../types/MbbSize.hpp"
#include "../types/MboPrice.hpp"
#include "../types/MboSize.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

#pragma pack(push, 1)

// used to publish MIAX Futures Onyx Best Bid and Offer (MBBO) of a Simple Instrument or Complex Instrument
struct BestBidAndOfferMessage {

    Timestamp timestamp;
    InstrumentId instrument_id;
    MbbPrice mbb_price;
    MbbSize mbb_size;
    MboPrice mbo_price;
    MboSize mbo_size;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 15;

    // parse method
    static BestBidAndOfferMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BestBidAndOfferMessage*>(buffer);
    }

    // parse method const
    static const BestBidAndOfferMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BestBidAndOfferMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const BestBidAndOfferMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const BestBidAndOfferMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
