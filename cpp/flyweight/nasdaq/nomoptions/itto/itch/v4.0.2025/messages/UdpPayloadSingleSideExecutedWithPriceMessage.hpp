#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Printable.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// These executions may be marked as non-printable. If the execution is marked as non-printed,
// it means that the contracts will be included into a later bulk print (e.g., in the case of
// auction executions). If a firm is looking to use the ITTO data in time-and-sales displays or
// volume calculations, NASDAQ recommends that firms ignore messages marked as non-printable to
// prevent double counting.
class UdpPayloadSingleSideExecutedWithPriceMessage {
  public:
    static constexpr const char* name = "UdpPayloadSingleSideExecutedWithPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPayloadSingleSideExecutedWithPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPayloadSingleSideExecutedWithPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 33;
    static constexpr std::size_t fixed_size = 33;
    std::size_t encoded_size() const { return 33; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t reference_number() const { return wire::read_u64_be(at(8)); }

    std::uint32_t cross_number() const { return wire::read_u32_be(at(16)); }

    std::uint32_t match_number() const { return wire::read_u32_be(at(20)); }

    Printable printable() const { return static_cast<Printable>(wire::read_char(at(24))); }

    Decimal price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(25))), -4); }

    std::uint32_t volume_long() const { return wire::read_u32_be(at(29)); }

    void print(std::ostream& out) const {
        out << "UdpPayloadSingleSideExecutedWithPriceMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", reference_number=";
        out << reference_number();
        out << ", cross_number=";
        out << cross_number();
        out << ", match_number=";
        out << match_number();
        out << ", printable=";
        out << printable();
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

inline std::ostream& operator<<(std::ostream& out, const UdpPayloadSingleSideExecutedWithPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
