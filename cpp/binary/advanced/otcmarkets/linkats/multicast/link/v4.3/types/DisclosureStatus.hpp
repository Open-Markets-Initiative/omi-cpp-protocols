// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/DisclosureStatus.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// disclosure_status
struct disclosure_status {

    enum class enum_type : std::uint8_t {
        no_disclosure = 0,
        current_information = 2,
        limited_information = 3,
        no_information = 4
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Current Information", enum_type::current_information},
        {"Limited Information", enum_type::limited_information},
        {"No Disclosure", enum_type::no_disclosure},
        {"No Information", enum_type::no_information}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_disclosure: return "No Disclosure";
            case enum_type::current_information: return "Current Information";
            case enum_type::limited_information: return "Limited Information";
            case enum_type::no_information: return "No Information";
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

    static constexpr const char* name = "disclosure_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<disclosure_status::enum_type>;
    using storage_type = result_type;

    constexpr disclosure_status()
     : value{ enum_type{} } {}

    constexpr disclosure_status(enum_type v)
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
            set(enum_type::no_information);
    }

  protected:
    enum_type value;
};
}
