// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: bitfields/ImbalanceCondition.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// ImbalanceCondition bit set
struct ImbalanceCondition {

    // underlying type
    using type = std::uint16_t;

    static constexpr const char* name = "Imbalance Condition";
    static constexpr std::size_t size = 2;

    struct mask {
        static const type ImbalanceMoreBuyers = 0x0100;
        static const type ImbalanceMoreSellers = 0x0200;
    };

    // default constructor
    constexpr ImbalanceCondition()
     : value{ 0 } {}

    // ImbalanceMoreBuyers
    [[nodiscard]] constexpr bool ImbalanceMoreBuyers() const {
        return value & mask::ImbalanceMoreBuyers;
    }

    // ImbalanceMoreSellers
    [[nodiscard]] constexpr bool ImbalanceMoreSellers() const {
        return value & mask::ImbalanceMoreSellers;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
