// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: types/MarketSegmentIdOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// market_segment_id_optional
struct market_segment_id_optional {

    static constexpr const char* name = "market_segment_id_optional";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr std::uint8_t null_value = 0;

    using result_type = std::optional<std::uint8_t>;
    using storage_type = result_type;

    constexpr market_segment_id_optional()
     : value{ null_value } {}

    constexpr market_segment_id_optional(std::uint8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint8_t v) {
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
    std::uint8_t value;
};
}
