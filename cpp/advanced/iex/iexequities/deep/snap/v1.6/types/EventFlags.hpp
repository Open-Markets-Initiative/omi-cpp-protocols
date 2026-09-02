#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

// event_flags
struct event_flags {

    enum class enum_type : std::uint8_t {
        order_book_is_processing_an_event = 0,
        event_processing_complete = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Event Processing Complete", enum_type::event_processing_complete},
        {"Order Book Is Processing An Event", enum_type::order_book_is_processing_an_event}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::order_book_is_processing_an_event: return "Order Book Is Processing An Event";
            case enum_type::event_processing_complete: return "Event Processing Complete";
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

    static constexpr const char* name = "event_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<event_flags::enum_type>;
    using storage_type = result_type;

    constexpr event_flags()
     : value{ enum_type::order_book_is_processing_an_event } {}

    constexpr event_flags(enum_type v)
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
            set(enum_type::event_processing_complete);
    }

  protected:
    enum_type value;
};
}
