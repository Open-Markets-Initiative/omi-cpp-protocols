#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// md_stream_id
struct md_stream_id {

    enum class enum_type : std::uint8_t {
        no_value = 255,
        market_place_assistant = 0,
        globex = 1,
        refinitiv = 2,
        icap = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Globex", enum_type::globex},
        {"Icap", enum_type::icap},
        {"Market Place Assistant", enum_type::market_place_assistant},
        {"No Value", enum_type::no_value},
        {"Refinitiv", enum_type::refinitiv}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_value: return "No Value";
            case enum_type::market_place_assistant: return "Market Place Assistant";
            case enum_type::globex: return "Globex";
            case enum_type::refinitiv: return "Refinitiv";
            case enum_type::icap: return "Icap";
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

    static constexpr const char* name = "md_stream_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_stream_id::enum_type>;
    using storage_type = result_type;

    constexpr md_stream_id()
     : value{ enum_type{} } {}

    constexpr md_stream_id(enum_type v)
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
            set(static_cast<enum_type>(255));
    }

  protected:
    enum_type value;
};
}
