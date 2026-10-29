#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Sent whenever an execution on CIX ATS is amended
class TradeCorrectMessage {
  public:
    static constexpr const char* name = "TradeCorrectMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCorrectMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCorrectMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 84;
    static constexpr std::size_t fixed_size = 84;
    std::size_t encoded_size() const { return 84; }

    std::uint16_t symbol_id() const { return wire::read_u16_le(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(2)))); }

    std::uint64_t reserved_8() const { return wire::read_u64_le(at(10)); }

    char reserved_1() const { return wire::read_char(at(18)); }

    std::string_view symbol() const { return view::text(at(19), 11, ' '); }

    std::uint64_t execution_id() const { return wire::read_u64_le(at(30)); }

    std::string_view broker() const { return view::text(at(38), 3, ' '); }

    std::string_view contra_broker() const { return view::text(at(41), 3, ' '); }

    std::uint64_t original_execution_id() const { return wire::read_u64_le(at(44)); }

    Decimal original_trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(52))), -6); }

    Decimal original_trade_quantity() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(60))), -6); }

    Decimal corrected_trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(68))), -6); }

    Decimal corrected_trade_quantity() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(76))), -6); }

    void print(std::ostream& out) const {
        out << "TradeCorrectMessage{";
        out << "symbol_id=";
        out << symbol_id();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", reserved_8=";
        out << reserved_8();
        out << ", reserved_1=";
        print::character(out, reserved_1());
        out << ", symbol=";
        print::text(out, symbol());
        out << ", execution_id=";
        out << execution_id();
        out << ", broker=";
        print::text(out, broker());
        out << ", contra_broker=";
        print::text(out, contra_broker());
        out << ", original_execution_id=";
        out << original_execution_id();
        out << ", original_trade_price=";
        out << original_trade_price();
        out << ", original_trade_quantity=";
        out << original_trade_quantity();
        out << ", corrected_trade_price=";
        out << corrected_trade_price();
        out << ", corrected_trade_quantity=";
        out << corrected_trade_quantity();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCorrectMessage& value) {
    value.print(out);
    return out;
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
