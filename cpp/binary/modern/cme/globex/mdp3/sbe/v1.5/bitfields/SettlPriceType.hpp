#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {

// SettlPriceType bit set
struct SettlPriceType {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Settl Price Type";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Final = 0x01;
        static const type Actual = 0x02;
        static const type Rounded = 0x04;
        static const type Intraday = 0x08;
        static const type ReservedBits = 0x10;
        static const type UnusedSettlPriceType5 = 0x20;
        static const type UnusedSettlPriceType6 = 0x40;
        static const type NullValue = 0x80;
    };

    // default constructor
    constexpr SettlPriceType()
     : value{ 0 } {}

    // Final
    [[nodiscard]] constexpr bool Final() const {
        return value & mask::Final;
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

    // ReservedBits
    [[nodiscard]] constexpr bool ReservedBits() const {
        return value & mask::ReservedBits;
    }

    // Unused SettlPriceType 5
    [[nodiscard]] constexpr bool UnusedSettlPriceType5() const {
        return value & mask::UnusedSettlPriceType5;
    }

    // Unused SettlPriceType 6
    [[nodiscard]] constexpr bool UnusedSettlPriceType6() const {
        return value & mask::UnusedSettlPriceType6;
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
