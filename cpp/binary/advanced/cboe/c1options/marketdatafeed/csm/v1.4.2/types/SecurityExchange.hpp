#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// security_exchange
struct security_exchange {

    enum class enum_type : char {
        cboe = 'C',
        one_chicago_not_supported = 'O',
        cbsx_not_supported = 'W',
        cfecof = 'F',
        cboe_2_options = '2'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Cboe", enum_type::cboe},
        {"Cboe 2 Options", enum_type::cboe_2_options},
        {"Cbsx Not Supported", enum_type::cbsx_not_supported},
        {"Cfecof", enum_type::cfecof},
        {"One Chicago Not Supported", enum_type::one_chicago_not_supported}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cboe: return "Cboe";
            case enum_type::one_chicago_not_supported: return "One Chicago Not Supported";
            case enum_type::cbsx_not_supported: return "Cbsx Not Supported";
            case enum_type::cfecof: return "Cfecof";
            case enum_type::cboe_2_options: return "Cboe 2 Options";
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

    static constexpr const char* name = "security_exchange";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_exchange::enum_type>;
    using storage_type = result_type;

    constexpr security_exchange()
     : value{ enum_type{} } {}

    constexpr security_exchange(enum_type v)
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
            set(enum_type::cboe_2_options);
    }

  protected:
    enum_type value;
};
}
