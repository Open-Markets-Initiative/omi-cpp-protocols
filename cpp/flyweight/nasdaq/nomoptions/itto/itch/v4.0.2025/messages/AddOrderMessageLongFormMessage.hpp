#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketSide.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// For bandwidth efficiency reasons, this message can be published in either short or long
// format.
class AddOrderMessageLongFormMessage {
  public:
    static constexpr const char* name = "AddOrderMessageLongFormMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderMessageLongFormMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderMessageLongFormMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(8)); }

    MarketSide market_side() const { return static_cast<MarketSide>(wire::read_char(at(16))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(17)); }

    Decimal price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(21))), -4); }

    std::uint32_t volume_long() const { return wire::read_u32_be(at(25)); }

    void print(std::ostream& out) const {
        out << "AddOrderMessageLongFormMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", market_side=";
        out << market_side();
        out << ", option_id=";
        out << option_id();
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

inline std::ostream& operator<<(std::ostream& out, const AddOrderMessageLongFormMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
