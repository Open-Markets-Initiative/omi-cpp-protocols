#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Symbol.hpp"
#include "../types/SymbolSfx.hpp"
#include "../types/RoundLot.hpp"
#include "../types/Reserved.hpp"
#include "../types/IsTestSymbol.hpp"
#include "../types/Mpv.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Instrument Directory Message
struct instrument_directory_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::security_id security_id;
        sbe_memoirdepthfeed::symbol symbol;
        sbe_memoirdepthfeed::symbol_sfx symbol_sfx;
        sbe_memoirdepthfeed::round_lot round_lot;
        sbe_memoirdepthfeed::reserved reserved;
        sbe_memoirdepthfeed::is_test_symbol is_test_symbol;
        sbe_memoirdepthfeed::mpv mpv;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::instrument_directory_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static instrument_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_directory_message*>(buffer);
    }

    // parse method const
    static const instrument_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_directory_message::fields_type, timestamp) == 0, "unexpected offset of instrument_directory_message::fields_type::timestamp");
static_assert(offsetof(instrument_directory_message::fields_type, security_id) == 8, "unexpected offset of instrument_directory_message::fields_type::security_id");
static_assert(offsetof(instrument_directory_message::fields_type, symbol) == 10, "unexpected offset of instrument_directory_message::fields_type::symbol");
static_assert(offsetof(instrument_directory_message::fields_type, symbol_sfx) == 16, "unexpected offset of instrument_directory_message::fields_type::symbol_sfx");
static_assert(offsetof(instrument_directory_message::fields_type, round_lot) == 22, "unexpected offset of instrument_directory_message::fields_type::round_lot");
static_assert(offsetof(instrument_directory_message::fields_type, reserved) == 26, "unexpected offset of instrument_directory_message::fields_type::reserved");
static_assert(offsetof(instrument_directory_message::fields_type, is_test_symbol) == 27, "unexpected offset of instrument_directory_message::fields_type::is_test_symbol");
static_assert(offsetof(instrument_directory_message::fields_type, mpv) == 28, "unexpected offset of instrument_directory_message::fields_type::mpv");
static_assert(sizeof(instrument_directory_message::fields_type) == 36, "unexpected sizeof instrument_directory_message::fields_type");
static_assert(sizeof(instrument_directory_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 36, "unexpected sizeof instrument_directory_message");

#pragma pack(pop)
}
