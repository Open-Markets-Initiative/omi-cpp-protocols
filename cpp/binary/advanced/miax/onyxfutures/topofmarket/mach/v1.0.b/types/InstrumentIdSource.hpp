// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/InstrumentIdSource.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// instrument_id_source
struct instrument_id_source {

    enum class enum_type : char {
        exchange = 'E'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 1> from_string_map = {{
        {"Exchange", enum_type::exchange}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::exchange: return "Exchange";
            default: return "unknown";
        }
    }

    static constexpr std::optional<enum_type> from_string(std::string_view str) {
        auto it = std::lower_bound(
            from_string_map.begin(),
            from_string_map.end(),
            str,
            [](const auto& pair, std::string_view s) { return pair.first < s; }
        );
        if (it != from_string_map.end() && it->first == str) {
            return it->second;
        }
        return std::nullopt;
    }

    static constexpr const char* name = "instrument_id_source";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<instrument_id_source::enum_type>;
    using storage_type = result_type;

    constexpr instrument_id_source()
     : value{ enum_type{} } {}

    constexpr instrument_id_source(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(enum_type::exchange);
    }

  protected:
    enum_type value;
};
}
