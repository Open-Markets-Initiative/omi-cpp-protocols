#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../types/UnderlyingSecurityAltId.hpp"
#include "../types/UnderlyingSecurityAltIdSource.hpp"
#include "../types/CollateralMarketPrice.hpp"
#include "../types/DirtyPrice.hpp"
#include "../types/UnderlyingInstrumentGuid.hpp"
#include "../types/MdStreamId.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct collateral_market_value_groups_entry {
    sbe_mdp3::underlying_security_alt_id underlying_security_alt_id;
    sbe_mdp3::underlying_security_alt_id_source underlying_security_alt_id_source;
    sbe_mdp3::collateral_market_price collateral_market_price;
    sbe_mdp3::dirty_price dirty_price;
    sbe_mdp3::underlying_instrument_guid underlying_instrument_guid;
    sbe_mdp3::md_stream_id md_stream_id;
    sbe_mdp3::padding_2 padding_2;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Collateral Market Value
struct collateral_market_value {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::padding_2 padding_2;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<collateral_market_value_groups_entry, group_size> collateral_market_value_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static collateral_market_value* parse(std::byte* buffer) {
        return reinterpret_cast<collateral_market_value*>(buffer);
    }

    // parse method const
    static const collateral_market_value* parse(const std::byte* buffer) {
        return reinterpret_cast<const collateral_market_value*>(buffer);
    }

};

// layout verification
static_assert(offsetof(collateral_market_value::fields_type, transact_time) == 0, "unexpected offset of collateral_market_value::fields_type::transact_time");
static_assert(offsetof(collateral_market_value::fields_type, match_event_indicator) == 8, "unexpected offset of collateral_market_value::fields_type::match_event_indicator");
static_assert(offsetof(collateral_market_value::fields_type, padding_2) == 9, "unexpected offset of collateral_market_value::fields_type::padding_2");
static_assert(sizeof(collateral_market_value::fields_type) == 11, "unexpected sizeof collateral_market_value::fields_type");

#pragma pack(pop)
}

#include "details/CollateralMarketValueWriter.hpp"
#include "details/CollateralMarketValueReader.hpp"
