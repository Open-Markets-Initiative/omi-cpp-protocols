#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// quote_status_response_to
struct quote_status_response_to {

    enum class enum_type : char {
        quote = '0',
        quote_request = '1',
        quote_cancel = '2',
        quote_request_reject = '3',
        no_value = '\0'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"No Value", enum_type::no_value},
        {"Quote", enum_type::quote},
        {"Quote Cancel", enum_type::quote_cancel},
        {"Quote Request", enum_type::quote_request},
        {"Quote Request Reject", enum_type::quote_request_reject}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::quote: return "Quote";
            case enum_type::quote_request: return "Quote Request";
            case enum_type::quote_cancel: return "Quote Cancel";
            case enum_type::quote_request_reject: return "Quote Request Reject";
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

    static constexpr const char* name = "quote_status_response_to";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<quote_status_response_to::enum_type>;
    using storage_type = result_type;

    constexpr quote_status_response_to()
     : value{ enum_type{} } {}

    constexpr quote_status_response_to(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
