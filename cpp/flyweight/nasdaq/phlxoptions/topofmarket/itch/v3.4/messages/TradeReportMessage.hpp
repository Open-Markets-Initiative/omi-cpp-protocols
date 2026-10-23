#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// The Trade Report message will be used to relay execution system transactions that are
// reported during the current business day. The options system only reports one-side of a
// trade execution on the feed and other data feed products.
class TradeReportMessage {
  public:
    static constexpr const char* name = "TradeReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 21;
    static constexpr std::size_t fixed_size = 21;
    std::size_t encoded_size() const { return 21; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(4)); }

    std::uint32_t cross_id() const { return wire::read_u32_be(at(8)); }

    char trade_condition() const { return wire::read_char(at(12)); }

    Decimal price_4() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(13))), -4); }

    std::uint32_t volume() const { return wire::read_u32_be(at(17)); }

    void print(std::ostream& out) const {
        out << "TradeReportMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", option_id=";
        out << option_id();
        out << ", cross_id=";
        out << cross_id();
        out << ", trade_condition=";
        print::character(out, trade_condition());
        out << ", price_4=";
        out << price_4();
        out << ", volume=";
        out << volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
