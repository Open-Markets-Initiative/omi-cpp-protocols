// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: types/AccountType.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// account_type
struct account_type {

    enum class enum_type : std::uint8_t {
        remove_account_information = 38,
        regular_account = 39,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"No Value", enum_type::no_value},
        {"Regular Account", enum_type::regular_account},
        {"Remove Account Information", enum_type::remove_account_information}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::remove_account_information: return "Remove Account Information";
            case enum_type::regular_account: return "Regular Account";
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

    static constexpr const char* name = "account_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr enum_type null_value = static_cast<enum_type>(0);

    using result_type = std::optional<account_type::enum_type>;
    using storage_type = result_type;

    constexpr account_type()
     : value{ static_cast<enum_type>(0) } {}

    constexpr account_type(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        const enum_type held = value;
        return held == null_value ? std::nullopt : result_type{held};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        set(null_value);
    }

  protected:
    enum_type value;
};
}
