// Cme.Globex.Mdp3.Sbe.v1.9: bitfields/SettlPriceType.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// SettlPriceType bit set
struct SettlPriceType {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Settl Price Type";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type FinalDaily = 0x01;
        static const type Actual = 0x02;
        static const type Rounded = 0x04;
        static const type Intraday = 0x08;
        static const type NullValue = 0x80;
    };

    // default constructor
    constexpr SettlPriceType()
     : value{ 0 } {}

    // FinalDaily
    [[nodiscard]] constexpr bool FinalDaily() const {
        return value & mask::FinalDaily;
    }

    // Actual
    [[nodiscard]] constexpr bool Actual() const {
        return value & mask::Actual;
    }

    // Rounded
    [[nodiscard]] constexpr bool Rounded() const {
        return value & mask::Rounded;
    }

    // Intraday
    [[nodiscard]] constexpr bool Intraday() const {
        return value & mask::Intraday;
    }

    // NullValue
    [[nodiscard]] constexpr bool NullValue() const {
        return value & mask::NullValue;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
