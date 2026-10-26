#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
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

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Noii Message
struct noii_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::auction_id auction_id;
        itch_itto::auction_type auction_type;
        itch_itto::paired_contracts paired_contracts;
        itch_itto::imbalance_direction imbalance_direction;
        itch_itto::option_id option_id;
        itch_itto::imbalance_price imbalance_price;
        itch_itto::imbalance_volume imbalance_volume;
        itch_itto::customer_firm_indicator customer_firm_indicator;
        itch_itto::reserved_3 reserved_3;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::noii_message};

    fields_type fields;

    // parse method
    static noii_message* parse(std::byte* buffer) {
        return reinterpret_cast<noii_message*>(buffer);
    }

    // parse method const
    static const noii_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const noii_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(noii_message::fields_type, tracking_number) == 0, "unexpected offset of noii_message::fields_type::tracking_number");
static_assert(offsetof(noii_message::fields_type, timestamp) == 2, "unexpected offset of noii_message::fields_type::timestamp");
static_assert(offsetof(noii_message::fields_type, auction_id) == 8, "unexpected offset of noii_message::fields_type::auction_id");
static_assert(offsetof(noii_message::fields_type, auction_type) == 12, "unexpected offset of noii_message::fields_type::auction_type");
static_assert(offsetof(noii_message::fields_type, paired_contracts) == 13, "unexpected offset of noii_message::fields_type::paired_contracts");
static_assert(offsetof(noii_message::fields_type, imbalance_direction) == 17, "unexpected offset of noii_message::fields_type::imbalance_direction");
static_assert(offsetof(noii_message::fields_type, option_id) == 18, "unexpected offset of noii_message::fields_type::option_id");
static_assert(offsetof(noii_message::fields_type, imbalance_price) == 22, "unexpected offset of noii_message::fields_type::imbalance_price");
static_assert(offsetof(noii_message::fields_type, imbalance_volume) == 26, "unexpected offset of noii_message::fields_type::imbalance_volume");
static_assert(offsetof(noii_message::fields_type, customer_firm_indicator) == 30, "unexpected offset of noii_message::fields_type::customer_firm_indicator");
static_assert(offsetof(noii_message::fields_type, reserved_3) == 31, "unexpected offset of noii_message::fields_type::reserved_3");
static_assert(sizeof(noii_message::fields_type) == 34, "unexpected sizeof noii_message::fields_type");
static_assert(sizeof(noii_message) == sizeof(itch_itto::message_header) + 34, "unexpected sizeof noii_message");

#pragma pack(pop)
}
