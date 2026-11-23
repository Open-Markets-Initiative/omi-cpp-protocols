// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/AckRequiredPossDup.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// ack_required_poss_dup
struct ack_required_poss_dup {

    enum class enum_type : char {
        unused = '0',
        ack_required = 'A',
        poss_dup = 'D'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Ack Required", enum_type::ack_required},
        {"Poss Dup", enum_type::poss_dup},
        {"Unused", enum_type::unused}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::unused: return "Unused";
            case enum_type::ack_required: return "Ack Required";
            case enum_type::poss_dup: return "Poss Dup";
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

    static constexpr const char* name = "ack_required_poss_dup";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<ack_required_poss_dup::enum_type>;
    using storage_type = result_type;

    constexpr ack_required_poss_dup()
     : value{ enum_type{} } {}

    constexpr ack_required_poss_dup(enum_type v)
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
            set(enum_type::poss_dup);
    }

  protected:
    enum_type value;
};
}
