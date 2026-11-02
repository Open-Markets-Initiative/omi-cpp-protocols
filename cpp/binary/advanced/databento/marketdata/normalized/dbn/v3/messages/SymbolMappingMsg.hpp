#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/StypeIn.hpp"
#include "../types/StypeInSymbol.hpp"
#include "../types/StypeOut.hpp"
#include "../types/StypeOutSymbol.hpp"
#include "../types/StartTs.hpp"
#include "../types/EndTs.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

// Symbol Mapping Msg
struct symbol_mapping_msg {

    struct fields_type {
        dbn_normalized::stype_in stype_in;
        dbn_normalized::stype_in_symbol stype_in_symbol;
        dbn_normalized::stype_out stype_out;
        dbn_normalized::stype_out_symbol stype_out_symbol;
        dbn_normalized::start_ts start_ts;
        dbn_normalized::end_ts end_ts;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::symbol_mapping, {}, {}, {}};

    fields_type fields;

    // parse method
    static symbol_mapping_msg* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_mapping_msg*>(buffer);
    }

    // parse method const
    static const symbol_mapping_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_mapping_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_mapping_msg::fields_type, stype_in) == 0, "unexpected offset of symbol_mapping_msg::fields_type::stype_in");
static_assert(offsetof(symbol_mapping_msg::fields_type, stype_in_symbol) == 1, "unexpected offset of symbol_mapping_msg::fields_type::stype_in_symbol");
static_assert(offsetof(symbol_mapping_msg::fields_type, stype_out) == 72, "unexpected offset of symbol_mapping_msg::fields_type::stype_out");
static_assert(offsetof(symbol_mapping_msg::fields_type, stype_out_symbol) == 73, "unexpected offset of symbol_mapping_msg::fields_type::stype_out_symbol");
static_assert(offsetof(symbol_mapping_msg::fields_type, start_ts) == 144, "unexpected offset of symbol_mapping_msg::fields_type::start_ts");
static_assert(offsetof(symbol_mapping_msg::fields_type, end_ts) == 152, "unexpected offset of symbol_mapping_msg::fields_type::end_ts");
static_assert(sizeof(symbol_mapping_msg::fields_type) == 160, "unexpected sizeof symbol_mapping_msg::fields_type");
static_assert(sizeof(symbol_mapping_msg) == sizeof(dbn_normalized::record_header) + 160, "unexpected sizeof symbol_mapping_msg");

#pragma pack(pop)
}
