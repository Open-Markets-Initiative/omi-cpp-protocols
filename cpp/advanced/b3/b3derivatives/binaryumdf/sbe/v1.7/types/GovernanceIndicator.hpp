#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// governance_indicator
struct governance_indicator {

    enum class enum_type : std::uint8_t {
        no = 0,
        n_1 = 1,
        n_2 = 2,
        nm = 4,
        ma = 5,
        mb = 6,
        m_2 = 7,
        no_value = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"M 2", enum_type::m_2},
        {"Ma", enum_type::ma},
        {"Mb", enum_type::mb},
        {"N 1", enum_type::n_1},
        {"N 2", enum_type::n_2},
        {"Nm", enum_type::nm},
        {"No", enum_type::no},
        {"No Value", enum_type::no_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no: return "No";
            case enum_type::n_1: return "N 1";
            case enum_type::n_2: return "N 2";
            case enum_type::nm: return "Nm";
            case enum_type::ma: return "Ma";
            case enum_type::mb: return "Mb";
            case enum_type::m_2: return "M 2";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "governance_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<governance_indicator::enum_type>;
    using storage_type = result_type;

    constexpr governance_indicator()
     : value{ enum_type::no } {}

    constexpr governance_indicator(enum_type v)
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
