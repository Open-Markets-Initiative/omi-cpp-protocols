#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// ImbalanceCondition bit set
struct ImbalanceCondition {

    // underlying type
    using type = std::uint16_t;

    static constexpr const char* name = "Imbalance Condition";
    static constexpr std::size_t size = 2;

    struct mask {
        static const type UnusedImbalanceCondition0 = 0x0001;
        static const type UnusedImbalanceCondition1 = 0x0002;
        static const type UnusedImbalanceCondition2 = 0x0004;
        static const type UnusedImbalanceCondition3 = 0x0008;
        static const type UnusedImbalanceCondition4 = 0x0010;
        static const type UnusedImbalanceCondition5 = 0x0020;
        static const type UnusedImbalanceCondition6 = 0x0040;
        static const type UnusedImbalanceCondition7 = 0x0080;
        static const type ImbalanceMoreBuyers = 0x0100;
        static const type ImbalanceMoreSellers = 0x0200;
        static const type Reserved6 = 0xFC00;
    };

    // default constructor
    constexpr ImbalanceCondition()
     : value{ 0 } {}

    // Unused ImbalanceCondition 0
    [[nodiscard]] constexpr bool UnusedImbalanceCondition0() const {
        return value & mask::UnusedImbalanceCondition0;
    }

    // Unused ImbalanceCondition 1
    [[nodiscard]] constexpr bool UnusedImbalanceCondition1() const {
        return value & mask::UnusedImbalanceCondition1;
    }

    // Unused ImbalanceCondition 2
    [[nodiscard]] constexpr bool UnusedImbalanceCondition2() const {
        return value & mask::UnusedImbalanceCondition2;
    }

    // Unused ImbalanceCondition 3
    [[nodiscard]] constexpr bool UnusedImbalanceCondition3() const {
        return value & mask::UnusedImbalanceCondition3;
    }

    // Unused ImbalanceCondition 4
    [[nodiscard]] constexpr bool UnusedImbalanceCondition4() const {
        return value & mask::UnusedImbalanceCondition4;
    }

    // Unused ImbalanceCondition 5
    [[nodiscard]] constexpr bool UnusedImbalanceCondition5() const {
        return value & mask::UnusedImbalanceCondition5;
    }

    // Unused ImbalanceCondition 6
    [[nodiscard]] constexpr bool UnusedImbalanceCondition6() const {
        return value & mask::UnusedImbalanceCondition6;
    }

    // Unused ImbalanceCondition 7
    [[nodiscard]] constexpr bool UnusedImbalanceCondition7() const {
        return value & mask::UnusedImbalanceCondition7;
    }

    // ImbalanceMoreBuyers
    [[nodiscard]] constexpr bool ImbalanceMoreBuyers() const {
        return value & mask::ImbalanceMoreBuyers;
    }

    // ImbalanceMoreSellers
    [[nodiscard]] constexpr bool ImbalanceMoreSellers() const {
        return value & mask::ImbalanceMoreSellers;
    }

    // 6 reserved bits
    [[nodiscard]] constexpr bool Reserved6() const {
        return value & mask::Reserved6;
    }

  protected:
    type value;
};
}
