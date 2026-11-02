#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// A price level consolidated from multiple venues
class ConsolidatedBidAskPair {
  public:
    static constexpr const char* name = "ConsolidatedBidAskPair";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ConsolidatedBidAskPair(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ConsolidatedBidAskPair has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::optional<Decimal> bid_px() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> ask_px() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::uint32_t bid_sz() const { return wire::read_u32_le(at(16)); }

    std::uint32_t ask_sz() const { return wire::read_u32_le(at(20)); }

    std::uint16_t bid_pb() const { return wire::read_u16_le(at(24)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(26).template first<2>(); }

    std::uint16_t ask_pb() const { return wire::read_u16_le(at(28)); }

    std::span<const std::byte, 2> second_reserved_2() const { return bytes_.subspan(30).template first<2>(); }

    void print(std::ostream& out) const {
        out << "ConsolidatedBidAskPair{";
        out << "bid_px=";
        print::optional(out, bid_px());
        out << ", ask_px=";
        print::optional(out, ask_px());
        out << ", bid_sz=";
        out << bid_sz();
        out << ", ask_sz=";
        out << ask_sz();
        out << ", bid_pb=";
        out << bid_pb();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << ", ask_pb=";
        out << ask_pb();
        out << ", second_reserved_2=";
        print::hex(out, second_reserved_2().data(), second_reserved_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ConsolidatedBidAskPair& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
