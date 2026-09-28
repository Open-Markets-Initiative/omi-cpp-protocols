#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// TradeCondition bit set
struct TradeCondition {

    // underlying type
    using type = std::uint16_t;

    static constexpr const char* name = "Trade Condition";
    static constexpr std::size_t size = 2;

    struct mask {
        static const type OpeningPrice = 0x0001;
        static const type Crossed = 0x0002;
        static const type LastTradeAtTheSamePrice = 0x0004;
        static const type OutOfSequence = 0x0008;
        static const type UnusedTradeCondition4 = 0x0010;
        static const type UnusedTradeCondition5 = 0x0020;
        static const type TradeOnBehalf = 0x0040;
        static const type UnusedTradeCondition7 = 0x0080;
        static const type UnusedTradeCondition8 = 0x0100;
        static const type UnusedTradeCondition9 = 0x0200;
        static const type UnusedTradeCondition10 = 0x0400;
        static const type UnusedTradeCondition11 = 0x0800;
        static const type UnusedTradeCondition12 = 0x1000;
        static const type RegularTrade = 0x2000;
        static const type BlockTrade = 0x4000;
        static const type UnusedTradeCondition15 = 0x8000;
    };

    // default constructor
    constexpr TradeCondition()
     : value{ 0 } {}

    // OpeningPrice
    [[nodiscard]] constexpr bool OpeningPrice() const {
        return value & mask::OpeningPrice;
    }

    // Crossed
    [[nodiscard]] constexpr bool Crossed() const {
        return value & mask::Crossed;
    }

    // LastTradeAtTheSamePrice
    [[nodiscard]] constexpr bool LastTradeAtTheSamePrice() const {
        return value & mask::LastTradeAtTheSamePrice;
    }

    // OutOfSequence
    [[nodiscard]] constexpr bool OutOfSequence() const {
        return value & mask::OutOfSequence;
    }

    // Unused TradeCondition 4
    [[nodiscard]] constexpr bool UnusedTradeCondition4() const {
        return value & mask::UnusedTradeCondition4;
    }

    // Unused TradeCondition 5
    [[nodiscard]] constexpr bool UnusedTradeCondition5() const {
        return value & mask::UnusedTradeCondition5;
    }

    // TradeOnBehalf
    [[nodiscard]] constexpr bool TradeOnBehalf() const {
        return value & mask::TradeOnBehalf;
    }

    // Unused TradeCondition 7
    [[nodiscard]] constexpr bool UnusedTradeCondition7() const {
        return value & mask::UnusedTradeCondition7;
    }

    // Unused TradeCondition 8
    [[nodiscard]] constexpr bool UnusedTradeCondition8() const {
        return value & mask::UnusedTradeCondition8;
    }

    // Unused TradeCondition 9
    [[nodiscard]] constexpr bool UnusedTradeCondition9() const {
        return value & mask::UnusedTradeCondition9;
    }

    // Unused TradeCondition 10
    [[nodiscard]] constexpr bool UnusedTradeCondition10() const {
        return value & mask::UnusedTradeCondition10;
    }

    // Unused TradeCondition 11
    [[nodiscard]] constexpr bool UnusedTradeCondition11() const {
        return value & mask::UnusedTradeCondition11;
    }

    // Unused TradeCondition 12
    [[nodiscard]] constexpr bool UnusedTradeCondition12() const {
        return value & mask::UnusedTradeCondition12;
    }

    // RegularTrade
    [[nodiscard]] constexpr bool RegularTrade() const {
        return value & mask::RegularTrade;
    }

    // BlockTrade
    [[nodiscard]] constexpr bool BlockTrade() const {
        return value & mask::BlockTrade;
    }

    // Unused TradeCondition 15
    [[nodiscard]] constexpr bool UnusedTradeCondition15() const {
        return value & mask::UnusedTradeCondition15;
    }

  protected:
    type value;
};
}
