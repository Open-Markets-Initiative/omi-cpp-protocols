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

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// This message is sent whenever a quote on the book is replaced. The replaced quote has new
// sequence numbers on both sides. These new sequence numbers replace the prior sequence
// numbers on the quote.
class QuoteReplaceMessageShortForm {
  public:
    static constexpr const char* name = "QuoteReplaceMessageShortForm";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteReplaceMessageShortForm(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteReplaceMessageShortForm has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t original_bid_reference_number() const { return wire::read_u64_be(at(8)); }

    std::uint64_t bid_reference_number() const { return wire::read_u64_be(at(16)); }

    std::uint64_t original_ask_reference_number() const { return wire::read_u64_be(at(24)); }

    std::uint64_t ask_reference_number() const { return wire::read_u64_be(at(32)); }

    Decimal bid_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(40))), -4); }

    std::uint16_t bid_size_short() const { return wire::read_u16_be(at(42)); }

    Decimal ask_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(44))), -4); }

    std::uint16_t ask_size_short() const { return wire::read_u16_be(at(46)); }

    void print(std::ostream& out) const {
        out << "QuoteReplaceMessageShortForm{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", original_bid_reference_number=";
        out << original_bid_reference_number();
        out << ", bid_reference_number=";
        out << bid_reference_number();
        out << ", original_ask_reference_number=";
        out << original_ask_reference_number();
        out << ", ask_reference_number=";
        out << ask_reference_number();
        out << ", bid_price_short=";
        out << bid_price_short();
        out << ", bid_size_short=";
        out << bid_size_short();
        out << ", ask_price_short=";
        out << ask_price_short();
        out << ", ask_size_short=";
        out << ask_size_short();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteReplaceMessageShortForm& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
