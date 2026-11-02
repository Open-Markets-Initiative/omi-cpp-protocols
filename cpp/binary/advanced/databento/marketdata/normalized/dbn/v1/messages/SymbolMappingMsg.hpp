#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/StypeInSymbol.hpp"
#include "../types/StypeOutSymbol.hpp"
#include "../types/Dummy4.hpp"
#include "../types/StartTs.hpp"
#include "../types/EndTs.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v1;

#pragma pack(push, 1)

// Symbol Mapping Msg
struct symbol_mapping_msg {

    struct fields_type {
        dbn_normalized::stype_in_symbol stype_in_symbol;
        dbn_normalized::stype_out_symbol stype_out_symbol;
        dbn_normalized::dummy_4 dummy_4;
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
static_assert(offsetof(symbol_mapping_msg::fields_type, stype_in_symbol) == 0, "unexpected offset of symbol_mapping_msg::fields_type::stype_in_symbol");
static_assert(offsetof(symbol_mapping_msg::fields_type, stype_out_symbol) == 22, "unexpected offset of symbol_mapping_msg::fields_type::stype_out_symbol");
static_assert(offsetof(symbol_mapping_msg::fields_type, dummy_4) == 44, "unexpected offset of symbol_mapping_msg::fields_type::dummy_4");
static_assert(offsetof(symbol_mapping_msg::fields_type, start_ts) == 48, "unexpected offset of symbol_mapping_msg::fields_type::start_ts");
static_assert(offsetof(symbol_mapping_msg::fields_type, end_ts) == 56, "unexpected offset of symbol_mapping_msg::fields_type::end_ts");
static_assert(sizeof(symbol_mapping_msg::fields_type) == 64, "unexpected sizeof symbol_mapping_msg::fields_type");
static_assert(sizeof(symbol_mapping_msg) == sizeof(dbn_normalized::record_header) + 64, "unexpected sizeof symbol_mapping_msg");

#pragma pack(pop)
}
