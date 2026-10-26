#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// TradeCondition bit set
class TradeCondition {
  public:
    static constexpr const char* name = "TradeCondition";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCondition(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 2;
    static constexpr std::size_t fixed_size = 2;
    std::size_t encoded_size() const { return 2; }

    std::uint16_t raw() const { return wire::read_u16_le(bytes_.data()); }

    bool opening_price() const { return (raw() & static_cast<std::uint16_t>(0x1)) != 0; }

    bool crossed() const { return (raw() & static_cast<std::uint16_t>(0x2)) != 0; }

    bool last_trade_at_the_same_price() const { return (raw() & static_cast<std::uint16_t>(0x4)) != 0; }

    bool out_of_sequence() const { return (raw() & static_cast<std::uint16_t>(0x8)) != 0; }

    bool unused_trade_condition_4() const { return (raw() & static_cast<std::uint16_t>(0x10)) != 0; }

    bool unused_trade_condition_5() const { return (raw() & static_cast<std::uint16_t>(0x20)) != 0; }

    bool trade_on_behalf() const { return (raw() & static_cast<std::uint16_t>(0x40)) != 0; }

    bool unused_trade_condition_7() const { return (raw() & static_cast<std::uint16_t>(0x80)) != 0; }

    bool unused_trade_condition_8() const { return (raw() & static_cast<std::uint16_t>(0x100)) != 0; }

    bool unused_trade_condition_9() const { return (raw() & static_cast<std::uint16_t>(0x200)) != 0; }

    bool unused_trade_condition_10() const { return (raw() & static_cast<std::uint16_t>(0x400)) != 0; }

    bool unused_trade_condition_11() const { return (raw() & static_cast<std::uint16_t>(0x800)) != 0; }

    bool unused_trade_condition_12() const { return (raw() & static_cast<std::uint16_t>(0x1000)) != 0; }

    bool regular_trade() const { return (raw() & static_cast<std::uint16_t>(0x2000)) != 0; }

    bool block_trade() const { return (raw() & static_cast<std::uint16_t>(0x4000)) != 0; }

    bool unused_trade_condition_15() const { return (raw() & static_cast<std::uint16_t>(0x8000)) != 0; }

    void print(std::ostream& out) const {
        out << "TradeCondition{";
        out << "opening_price=";
        out << (opening_price() ? "true" : "false");
        out << ", crossed=";
        out << (crossed() ? "true" : "false");
        out << ", last_trade_at_the_same_price=";
        out << (last_trade_at_the_same_price() ? "true" : "false");
        out << ", out_of_sequence=";
        out << (out_of_sequence() ? "true" : "false");
        out << ", unused_trade_condition_4=";
        out << (unused_trade_condition_4() ? "true" : "false");
        out << ", unused_trade_condition_5=";
        out << (unused_trade_condition_5() ? "true" : "false");
        out << ", trade_on_behalf=";
        out << (trade_on_behalf() ? "true" : "false");
        out << ", unused_trade_condition_7=";
        out << (unused_trade_condition_7() ? "true" : "false");
        out << ", unused_trade_condition_8=";
        out << (unused_trade_condition_8() ? "true" : "false");
        out << ", unused_trade_condition_9=";
        out << (unused_trade_condition_9() ? "true" : "false");
        out << ", unused_trade_condition_10=";
        out << (unused_trade_condition_10() ? "true" : "false");
        out << ", unused_trade_condition_11=";
        out << (unused_trade_condition_11() ? "true" : "false");
        out << ", unused_trade_condition_12=";
        out << (unused_trade_condition_12() ? "true" : "false");
        out << ", regular_trade=";
        out << (regular_trade() ? "true" : "false");
        out << ", block_trade=";
        out << (block_trade() ? "true" : "false");
        out << ", unused_trade_condition_15=";
        out << (unused_trade_condition_15() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCondition& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
