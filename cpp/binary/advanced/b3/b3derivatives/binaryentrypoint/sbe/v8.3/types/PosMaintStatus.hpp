#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// pos_maint_status
struct pos_maint_status {

    enum class enum_type : char {
        accepted = '0',
        rejected = '2',
        completed = '3',
        not_executed = '9'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Accepted", enum_type::accepted},
        {"Completed", enum_type::completed},
        {"Not Executed", enum_type::not_executed},
        {"Rejected", enum_type::rejected}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::accepted: return "Accepted";
            case enum_type::rejected: return "Rejected";
            case enum_type::completed: return "Completed";
            case enum_type::not_executed: return "Not Executed";
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

    static constexpr const char* name = "pos_maint_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<pos_maint_status::enum_type>;
    using storage_type = result_type;

    constexpr pos_maint_status()
     : value{ enum_type{} } {}

    constexpr pos_maint_status(enum_type v)
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
            set(enum_type::not_executed);
    }

  protected:
    enum_type value;
};
}
