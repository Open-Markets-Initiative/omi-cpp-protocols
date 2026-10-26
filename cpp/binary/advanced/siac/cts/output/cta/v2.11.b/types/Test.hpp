#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// test
struct test {

    enum class enum_type : char {
        not_a_test_symbol = '0',
        test_symbol = '1'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Not A Test Symbol", enum_type::not_a_test_symbol},
        {"Test Symbol", enum_type::test_symbol}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_a_test_symbol: return "Not A Test Symbol";
            case enum_type::test_symbol: return "Test Symbol";
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

    static constexpr const char* name = "test";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<test::enum_type>;
    using storage_type = result_type;

    constexpr test()
     : value{ enum_type{} } {}

    constexpr test(enum_type v)
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
            set(enum_type::test_symbol);
    }

  protected:
    enum_type value;
};
}
