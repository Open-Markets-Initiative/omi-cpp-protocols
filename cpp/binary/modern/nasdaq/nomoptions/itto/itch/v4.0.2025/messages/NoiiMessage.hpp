#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/AuctionId.hpp"
#include "../types/AuctionType.hpp"
#include "../types/PairedContracts.hpp"
#include "../types/ImbalanceDirection.hpp"
#include "../types/OptionId.hpp"
#include "../types/ImbalancePrice.hpp"
#include "../types/ImbalanceVolume.hpp"
#include "../types/CustomerFirmIndicator.hpp"
#include "../types/Reserved3.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// For the NASDAQ Opening Auction, NASDAQ will begin the dissemination of NOII messages for a put or a call option five minutes prior to the start of opening process event and two minutes prior to the halt resumption (reopening) process event.
struct NoiiMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    AuctionId auction_id;
    AuctionType auction_type;
    PairedContracts paired_contracts;
    ImbalanceDirection imbalance_direction;
    OptionId option_id;
    ImbalancePrice imbalance_price;
    ImbalanceVolume imbalance_volume;
    CustomerFirmIndicator customer_firm_indicator;
    Reserved3 reserved_3;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'I';

    // parse method
    static NoiiMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NoiiMessage*>(buffer);
    }

    // parse method const
    static const NoiiMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NoiiMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NoiiMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NoiiMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
