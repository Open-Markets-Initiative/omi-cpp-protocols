#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/UnderlyingIndex.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/ChannelId.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/ExchangeCode.hpp"
#include "../types/PriceScaleCode.hpp"
#include "../types/SecurityType.hpp"
#include "../types/PriceResolution.hpp"
#include "../types/Reserved1.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

namespace xdp_deepfeed = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Underlying Index Mapping Message
struct underlying_index_mapping_message {

    struct fields_type {
        xdp_deepfeed::underlying_index underlying_index;
        xdp_deepfeed::underlying_symbol underlying_symbol;
        xdp_deepfeed::channel_id channel_id;
        xdp_deepfeed::market_id market_id;
        xdp_deepfeed::system_id system_id;
        xdp_deepfeed::exchange_code exchange_code;
        xdp_deepfeed::price_scale_code price_scale_code;
        xdp_deepfeed::security_type security_type;
        xdp_deepfeed::price_resolution price_resolution;
        xdp_deepfeed::reserved_1 reserved_1;
    };

    xdp_deepfeed::message_header header = {std::uint16_t(sizeof(xdp_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::underlying_index_mapping_message};

    fields_type fields;

    // parse method
    static underlying_index_mapping_message* parse(std::byte* buffer) {
        return reinterpret_cast<underlying_index_mapping_message*>(buffer);
    }

    // parse method const
    static const underlying_index_mapping_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const underlying_index_mapping_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(underlying_index_mapping_message::fields_type, underlying_index) == 0, "unexpected offset of underlying_index_mapping_message::fields_type::underlying_index");
static_assert(offsetof(underlying_index_mapping_message::fields_type, underlying_symbol) == 4, "unexpected offset of underlying_index_mapping_message::fields_type::underlying_symbol");
static_assert(offsetof(underlying_index_mapping_message::fields_type, channel_id) == 15, "unexpected offset of underlying_index_mapping_message::fields_type::channel_id");
static_assert(offsetof(underlying_index_mapping_message::fields_type, market_id) == 16, "unexpected offset of underlying_index_mapping_message::fields_type::market_id");
static_assert(offsetof(underlying_index_mapping_message::fields_type, system_id) == 18, "unexpected offset of underlying_index_mapping_message::fields_type::system_id");
static_assert(offsetof(underlying_index_mapping_message::fields_type, exchange_code) == 19, "unexpected offset of underlying_index_mapping_message::fields_type::exchange_code");
static_assert(offsetof(underlying_index_mapping_message::fields_type, price_scale_code) == 20, "unexpected offset of underlying_index_mapping_message::fields_type::price_scale_code");
static_assert(offsetof(underlying_index_mapping_message::fields_type, security_type) == 21, "unexpected offset of underlying_index_mapping_message::fields_type::security_type");
static_assert(offsetof(underlying_index_mapping_message::fields_type, price_resolution) == 22, "unexpected offset of underlying_index_mapping_message::fields_type::price_resolution");
static_assert(offsetof(underlying_index_mapping_message::fields_type, reserved_1) == 23, "unexpected offset of underlying_index_mapping_message::fields_type::reserved_1");
static_assert(sizeof(underlying_index_mapping_message::fields_type) == 24, "unexpected sizeof underlying_index_mapping_message::fields_type");
static_assert(sizeof(underlying_index_mapping_message) == sizeof(xdp_deepfeed::message_header) + 24, "unexpected sizeof underlying_index_mapping_message");

#pragma pack(pop)
}
