#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v8 {

// md_req_id_status
struct md_req_id_status {

    enum class enum_type : std::uint8_t {
        full_ack = 0,
        partial_ack = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Full Ack", enum_type::full_ack},
        {"Partial Ack", enum_type::partial_ack}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::full_ack: return "Full Ack";
            case enum_type::partial_ack: return "Partial Ack";
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

    static constexpr const char* name = "md_req_id_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_req_id_status::enum_type>;
    using storage_type = result_type;

    constexpr md_req_id_status()
     : value{ enum_type{} } {}

    constexpr md_req_id_status(enum_type v)
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
            set(enum_type::partial_ack);
    }

  protected:
    enum_type value;
};
}
