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

// The following message is used in the event that an options trade transaction is broken on
// the same business day that it is reported.
class BrokenTradeReportMessage {
  public:
    static constexpr const char* name = "BrokenTradeReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BrokenTradeReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BrokenTradeReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(4)); }

    std::uint32_t original_cross_id() const { return wire::read_u32_be(at(8)); }

    Decimal original_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(12))), -4); }

    std::uint32_t original_volume() const { return wire::read_u32_be(at(16)); }

    void print(std::ostream& out) const {
        out << "BrokenTradeReportMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", option_id=";
        out << option_id();
        out << ", original_cross_id=";
        out << original_cross_id();
        out << ", original_price=";
        out << original_price();
        out << ", original_volume=";
        out << original_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BrokenTradeReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
