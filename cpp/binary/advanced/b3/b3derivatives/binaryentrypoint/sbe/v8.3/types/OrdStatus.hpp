#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// ord_status
struct ord_status {

    enum class enum_type : char {
        new_value = '0',
        partially_filled = '1',
        filled = '2',
        canceled = '4',
        replaced = '5',
        rejected = '8',
        expired = 'C',
        restated = 'R',
        previous_final_state = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Canceled", enum_type::canceled},
        {"Expired", enum_type::expired},
        {"Filled", enum_type::filled},
        {"New", enum_type::new_value},
        {"Partially Filled", enum_type::partially_filled},
        {"Previous Final State", enum_type::previous_final_state},
        {"Rejected", enum_type::rejected},
        {"Replaced", enum_type::replaced},
        {"Restated", enum_type::restated}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::new_value: return "New";
            case enum_type::partially_filled: return "Partially Filled";
            case enum_type::filled: return "Filled";
            case enum_type::canceled: return "Canceled";
            case enum_type::replaced: return "Replaced";
            case enum_type::rejected: return "Rejected";
            case enum_type::expired: return "Expired";
            case enum_type::restated: return "Restated";
            case enum_type::previous_final_state: return "Previous Final State";
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

    static constexpr const char* name = "ord_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<ord_status::enum_type>;
    using storage_type = result_type;

    constexpr ord_status()
     : value{ enum_type{} } {}

    constexpr ord_status(enum_type v)
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
            set(enum_type::previous_final_state);
    }

  protected:
    enum_type value;
};
}
