// B3.B3Derivatives.BinaryUmdf.Sbe.v2.2: bitfields/TradeCondition.hpp
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
        static const type TradeOnBehalf = 0x0040;
        static const type RegularTrade = 0x2000;
        static const type BlockTrade = 0x4000;
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

    // TradeOnBehalf
    [[nodiscard]] constexpr bool TradeOnBehalf() const {
        return value & mask::TradeOnBehalf;
    }

    // RegularTrade
    [[nodiscard]] constexpr bool RegularTrade() const {
        return value & mask::RegularTrade;
    }

    // BlockTrade
    [[nodiscard]] constexpr bool BlockTrade() const {
        return value & mask::BlockTrade;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
