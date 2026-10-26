#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// For bandwidth efficiency reasons, this message can be published in either short or long
// format.
class AddQuoteMessageShortFormMessage {
  public:
    static constexpr const char* name = "AddQuoteMessageShortFormMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddQuoteMessageShortFormMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddQuoteMessageShortFormMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint64_t bid_reference_number() const { return wire::read_u64_be(at(8)); }

    std::uint64_t ask_reference_number() const { return wire::read_u64_be(at(16)); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(24)); }

    Decimal bid_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(28))), -4); }

    std::uint16_t bid_size_short() const { return wire::read_u16_be(at(30)); }

    Decimal ask_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(32))), -4); }

    std::uint16_t ask_size_short() const { return wire::read_u16_be(at(34)); }

    void print(std::ostream& out) const {
        out << "AddQuoteMessageShortFormMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", bid_reference_number=";
        out << bid_reference_number();
        out << ", ask_reference_number=";
        out << ask_reference_number();
        out << ", option_id=";
        out << option_id();
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

inline std::ostream& operator<<(std::ostream& out, const AddQuoteMessageShortFormMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
