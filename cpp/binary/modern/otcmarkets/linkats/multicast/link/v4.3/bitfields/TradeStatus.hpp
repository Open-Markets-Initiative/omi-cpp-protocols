// OtcMarkets.LinkAts.Multicast.Link.v4.3: bitfields/TradeStatus.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Trade Status Information
struct TradeStatus {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Trade Status";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Irregular = 0x01;
    };

    // default constructor
    constexpr TradeStatus()
     : value{ 0 } {}

    // Indicates an irregular trade
    [[nodiscard]] constexpr bool Irregular() const {
        return value & mask::Irregular;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
