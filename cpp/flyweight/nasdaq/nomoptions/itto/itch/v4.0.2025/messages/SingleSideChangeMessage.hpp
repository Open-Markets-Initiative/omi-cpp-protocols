#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ChangeReason.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// This message is sent whenever an order or a side of a quote is being updated for price and
// (or) contracts. The reference number associated with the order quote is unchanged.
class SingleSideChangeMessage {
  public:
    static constexpr const char* name = "SingleSideChangeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SingleSideChangeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SingleSideChangeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t reference_number() const { return wire::read_u64_be(at(8)); }

    ChangeReason change_reason() const { return static_cast<ChangeReason>(wire::read_char(at(16))); }

    Decimal price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(17))), -4); }

    std::uint32_t volume_long() const { return wire::read_u32_be(at(21)); }

    void print(std::ostream& out) const {
        out << "SingleSideChangeMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", reference_number=";
        out << reference_number();
        out << ", change_reason=";
        out << change_reason();
        out << ", price_long=";
        out << price_long();
        out << ", volume_long=";
        out << volume_long();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SingleSideChangeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
