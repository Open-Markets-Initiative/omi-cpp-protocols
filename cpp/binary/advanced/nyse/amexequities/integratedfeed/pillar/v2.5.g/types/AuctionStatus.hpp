#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

// auction_status
struct auction_status {

    enum class enum_type : std::uint8_t {
        will_run_as_always_for_open_and_close = 0,
        will_run_interest_exists_inside_or_at_the_collars_or_is_fully_paired_off = 1,
        will_not_run_because_there_is_an_imbalance_through_the_collars = 2,
        will_not_run_will_transition_to_the_closing_auction_instead = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Will Not Run Because There Is An Imbalance Through The Collars", enum_type::will_not_run_because_there_is_an_imbalance_through_the_collars},
        {"Will Not Run Will Transition To The Closing Auction Instead", enum_type::will_not_run_will_transition_to_the_closing_auction_instead},
        {"Will Run As Always For Open And Close", enum_type::will_run_as_always_for_open_and_close},
        {"Will Run Interest Exists Inside Or At The Collars Or Is Fully Paired Off", enum_type::will_run_interest_exists_inside_or_at_the_collars_or_is_fully_paired_off}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::will_run_as_always_for_open_and_close: return "Will Run As Always For Open And Close";
            case enum_type::will_run_interest_exists_inside_or_at_the_collars_or_is_fully_paired_off: return "Will Run Interest Exists Inside Or At The Collars Or Is Fully Paired Off";
            case enum_type::will_not_run_because_there_is_an_imbalance_through_the_collars: return "Will Not Run Because There Is An Imbalance Through The Collars";
            case enum_type::will_not_run_will_transition_to_the_closing_auction_instead: return "Will Not Run Will Transition To The Closing Auction Instead";
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

    static constexpr const char* name = "auction_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_status::enum_type>;
    using storage_type = result_type;

    constexpr auction_status()
     : value{ enum_type{} } {}

    constexpr auction_status(enum_type v)
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
            set(enum_type::will_not_run_will_transition_to_the_closing_auction_instead);
    }

  protected:
    enum_type value;
};
}
