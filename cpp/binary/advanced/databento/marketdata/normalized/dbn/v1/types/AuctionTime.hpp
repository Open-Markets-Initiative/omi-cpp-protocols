// Databento.MarketData.Normalized.Dbn.v1: types/AuctionTime.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// auction_time
struct auction_time {

    static constexpr const char* name = "auction_time";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 18446744073709551615ULL;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    constexpr auction_time()
     : value{ null_value } {}

    constexpr auction_time(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        value = null_value;
    }

  protected:
    std::uint64_t value;
};
}
