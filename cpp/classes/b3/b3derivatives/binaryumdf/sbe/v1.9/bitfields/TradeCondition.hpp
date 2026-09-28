#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// TradeCondition bit set
class TradeCondition {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 2;

    TradeCondition() = default;
    explicit TradeCondition(std::uint16_t raw);

    // Opening Price: OpeningPrice
    bool opening_price() const;
    void set_opening_price(bool value);

    // Crossed: Crossed
    bool crossed() const;
    void set_crossed(bool value);

    // Last Trade At The Same Price: LastTradeAtTheSamePrice
    bool last_trade_at_the_same_price() const;
    void set_last_trade_at_the_same_price(bool value);

    // Out Of Sequence: OutOfSequence
    bool out_of_sequence() const;
    void set_out_of_sequence(bool value);

    // Unused Trade Condition 4: Unused TradeCondition 4
    bool unused_trade_condition_4() const;
    void set_unused_trade_condition_4(bool value);

    // Unused Trade Condition 5: Unused TradeCondition 5
    bool unused_trade_condition_5() const;
    void set_unused_trade_condition_5(bool value);

    // Trade On Behalf: TradeOnBehalf
    bool trade_on_behalf() const;
    void set_trade_on_behalf(bool value);

    // Unused Trade Condition 7: Unused TradeCondition 7
    bool unused_trade_condition_7() const;
    void set_unused_trade_condition_7(bool value);

    // Unused Trade Condition 8: Unused TradeCondition 8
    bool unused_trade_condition_8() const;
    void set_unused_trade_condition_8(bool value);

    // Unused Trade Condition 9: Unused TradeCondition 9
    bool unused_trade_condition_9() const;
    void set_unused_trade_condition_9(bool value);

    // Unused Trade Condition 10: Unused TradeCondition 10
    bool unused_trade_condition_10() const;
    void set_unused_trade_condition_10(bool value);

    // Unused Trade Condition 11: Unused TradeCondition 11
    bool unused_trade_condition_11() const;
    void set_unused_trade_condition_11(bool value);

    // Unused Trade Condition 12: Unused TradeCondition 12
    bool unused_trade_condition_12() const;
    void set_unused_trade_condition_12(bool value);

    // Regular Trade: RegularTrade
    bool regular_trade() const;
    void set_regular_trade(bool value);

    // Block Trade: BlockTrade
    bool block_trade() const;
    void set_block_trade(bool value);

    // Unused Trade Condition 15: Unused TradeCondition 15
    bool unused_trade_condition_15() const;
    void set_unused_trade_condition_15(bool value);

    // The whole bitfield as its wire integer
    std::uint16_t raw() const;
    void set_raw(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const TradeCondition& other) const;
    bool operator!=(const TradeCondition& other) const;

  private:
    std::uint16_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const TradeCondition& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
