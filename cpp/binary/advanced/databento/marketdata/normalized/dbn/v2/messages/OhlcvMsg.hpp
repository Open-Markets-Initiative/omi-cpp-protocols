// Databento.MarketData.Normalized.Dbn.v2: messages/OhlcvMsg.hpp
#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/Open.hpp"
#include "../types/High.hpp"
#include "../types/Low.hpp"
#include "../types/Close.hpp"
#include "../types/Volume.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v2;

#pragma pack(push, 1)

// Ohlcv Msg
struct ohlcv_msg {

    struct fields_type {
        dbn_normalized::open open;
        dbn_normalized::high high;
        dbn_normalized::low low;
        dbn_normalized::close close;
        dbn_normalized::volume volume;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::ohlcv_deprecated, {}, {}, {}};

    fields_type fields;

    // parse method
    static ohlcv_msg* parse(std::byte* buffer) {
        return reinterpret_cast<ohlcv_msg*>(buffer);
    }

    // parse method const
    static const ohlcv_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const ohlcv_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(ohlcv_msg::fields_type, open) == 0, "unexpected offset of ohlcv_msg::fields_type::open");
static_assert(offsetof(ohlcv_msg::fields_type, high) == 8, "unexpected offset of ohlcv_msg::fields_type::high");
static_assert(offsetof(ohlcv_msg::fields_type, low) == 16, "unexpected offset of ohlcv_msg::fields_type::low");
static_assert(offsetof(ohlcv_msg::fields_type, close) == 24, "unexpected offset of ohlcv_msg::fields_type::close");
static_assert(offsetof(ohlcv_msg::fields_type, volume) == 32, "unexpected offset of ohlcv_msg::fields_type::volume");
static_assert(sizeof(ohlcv_msg::fields_type) == 40, "unexpected sizeof ohlcv_msg::fields_type");
static_assert(sizeof(ohlcv_msg) == sizeof(dbn_normalized::record_header) + 40, "unexpected sizeof ohlcv_msg");

#pragma pack(pop)
}
