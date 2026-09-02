#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/AuctionType.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/PairedShares.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/IndicativeClearingPrice.hpp"
#include "../types/ImbalanceShares.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ExtensionNumber.hpp"
#include "../types/ScheduledAuctionTime.hpp"
#include "../types/AuctionBookClearingPrice.hpp"
#include "../types/CollarReferencePrice.hpp"
#include "../types/LowerAuctionCollar.hpp"
#include "../types/UpperAuctionCollar.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

namespace iextp_tops = ::iex::iexequities::tops::iextp::v1_64;

#pragma pack(push, 1)

// Auction Information Message
struct auction_information_message {

    struct fields_type {
        iextp_tops::auction_type auction_type;
        iextp_tops::timestamp timestamp;
        iextp_tops::symbol symbol;
        iextp_tops::paired_shares paired_shares;
        iextp_tops::reference_price reference_price;
        iextp_tops::indicative_clearing_price indicative_clearing_price;
        iextp_tops::imbalance_shares imbalance_shares;
        iextp_tops::imbalance_side imbalance_side;
        iextp_tops::extension_number extension_number;
        iextp_tops::scheduled_auction_time scheduled_auction_time;
        iextp_tops::auction_book_clearing_price auction_book_clearing_price;
        iextp_tops::collar_reference_price collar_reference_price;
        iextp_tops::lower_auction_collar lower_auction_collar;
        iextp_tops::upper_auction_collar upper_auction_collar;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::auction_information_message};

    fields_type fields;

    // parse method
    static auction_information_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_information_message*>(buffer);
    }

    // parse method const
    static const auction_information_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_information_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_information_message::fields_type, auction_type) == 0, "unexpected offset of auction_information_message::fields_type::auction_type");
static_assert(offsetof(auction_information_message::fields_type, timestamp) == 1, "unexpected offset of auction_information_message::fields_type::timestamp");
static_assert(offsetof(auction_information_message::fields_type, symbol) == 9, "unexpected offset of auction_information_message::fields_type::symbol");
static_assert(offsetof(auction_information_message::fields_type, paired_shares) == 17, "unexpected offset of auction_information_message::fields_type::paired_shares");
static_assert(offsetof(auction_information_message::fields_type, reference_price) == 21, "unexpected offset of auction_information_message::fields_type::reference_price");
static_assert(offsetof(auction_information_message::fields_type, indicative_clearing_price) == 29, "unexpected offset of auction_information_message::fields_type::indicative_clearing_price");
static_assert(offsetof(auction_information_message::fields_type, imbalance_shares) == 37, "unexpected offset of auction_information_message::fields_type::imbalance_shares");
static_assert(offsetof(auction_information_message::fields_type, imbalance_side) == 41, "unexpected offset of auction_information_message::fields_type::imbalance_side");
static_assert(offsetof(auction_information_message::fields_type, extension_number) == 42, "unexpected offset of auction_information_message::fields_type::extension_number");
static_assert(offsetof(auction_information_message::fields_type, scheduled_auction_time) == 43, "unexpected offset of auction_information_message::fields_type::scheduled_auction_time");
static_assert(offsetof(auction_information_message::fields_type, auction_book_clearing_price) == 47, "unexpected offset of auction_information_message::fields_type::auction_book_clearing_price");
static_assert(offsetof(auction_information_message::fields_type, collar_reference_price) == 55, "unexpected offset of auction_information_message::fields_type::collar_reference_price");
static_assert(offsetof(auction_information_message::fields_type, lower_auction_collar) == 63, "unexpected offset of auction_information_message::fields_type::lower_auction_collar");
static_assert(offsetof(auction_information_message::fields_type, upper_auction_collar) == 71, "unexpected offset of auction_information_message::fields_type::upper_auction_collar");
static_assert(sizeof(auction_information_message::fields_type) == 79, "unexpected sizeof auction_information_message::fields_type");
static_assert(sizeof(auction_information_message) == sizeof(message_header) + 79, "unexpected sizeof auction_information_message");

#pragma pack(pop)
}
