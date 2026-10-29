#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// auction_event
struct auction_event {

    enum class enum_type : char {
        start = 'S',
        auction_update = 'U',
        end_of_auction = 'E'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Auction Update", enum_type::auction_update},
        {"End Of Auction", enum_type::end_of_auction},
        {"Start", enum_type::start}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start: return "Start";
            case enum_type::auction_update: return "Auction Update";
            case enum_type::end_of_auction: return "End Of Auction";
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

    static constexpr const char* name = "auction_event";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_event::enum_type>;
    using storage_type = result_type;

    constexpr auction_event()
     : value{ enum_type{} } {}

    constexpr auction_event(enum_type v)
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
            set(enum_type::end_of_auction);
    }

  protected:
    enum_type value;
};
}
