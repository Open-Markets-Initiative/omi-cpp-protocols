// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/TradeTimeStamp.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// trade_time_stamp
struct trade_time_stamp {

    static constexpr const char* name = "trade_time_stamp";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr std::uint32_t null_value = 0;

    using result_type = std::optional<std::uint32_t>;
    using storage_type = result_type;

    constexpr trade_time_stamp()
     : value{ null_value } {}

    constexpr trade_time_stamp(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        value = null_value;
    }

  protected:
    std::uint32_t value;
};
}
