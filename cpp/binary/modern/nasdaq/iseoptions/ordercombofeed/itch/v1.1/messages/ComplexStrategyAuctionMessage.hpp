#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/AuctionId.hpp"
#include "../types/OrderType.hpp"
#include "../types/Side.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/ExecFlag.hpp"
#include "../types/OrderCapacity.hpp"
#include "../types/Scope.hpp"
#include "../types/OwnerId.hpp"
#include "../types/Giveup.hpp"
#include "../types/Cmta.hpp"
#include "../types/AuctionEvent.hpp"
#include "../types/AuctionType.hpp"
#include "../types/NumberOfResponses.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

#pragma pack(push, 1)

// This message is used to announce strategy auctions. The start of auction is announced, followed by possible updates on the auction, and announcing the end of the auction.
struct ComplexStrategyAuctionMessage {

    Timestamp timestamp;
    StrategyId strategy_id;
    AuctionId auction_id;
    OrderType order_type;
    Side side;
    Price price;
    Size size;
    ExecFlag exec_flag;
    OrderCapacity order_capacity;
    Scope scope;
    OwnerId owner_id;
    Giveup giveup;
    Cmta cmta;
    AuctionEvent auction_event;
    AuctionType auction_type;
    NumberOfResponses number_of_responses;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'J';

    // parse method
    static ComplexStrategyAuctionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexStrategyAuctionMessage*>(buffer);
    }

    // parse method const
    static const ComplexStrategyAuctionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexStrategyAuctionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexStrategyAuctionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexStrategyAuctionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
