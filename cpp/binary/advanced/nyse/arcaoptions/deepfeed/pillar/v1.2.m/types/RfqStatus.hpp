#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// rfq_status
struct rfq_status {

    enum class enum_type : char {
        start_of_rfq_auction = 'O',
        end_of_rfq_auction = 'Q'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"End Of Rfq Auction", enum_type::end_of_rfq_auction},
        {"Start Of Rfq Auction", enum_type::start_of_rfq_auction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_rfq_auction: return "Start Of Rfq Auction";
            case enum_type::end_of_rfq_auction: return "End Of Rfq Auction";
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

    static constexpr const char* name = "rfq_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<rfq_status::enum_type>;
    using storage_type = result_type;

    constexpr rfq_status()
     : value{ enum_type{} } {}

    constexpr rfq_status(enum_type v)
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
            set(enum_type::end_of_rfq_auction);
    }

  protected:
    enum_type value;
};
}
