#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Order Execution flags. Bit 0 indicates SIP reportability; bit 1 indicates Traded Against
// Retail; bits 2-7 are reserved.
class OrderExecutionFlags {
  public:
    static constexpr const char* name = "OrderExecutionFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutionFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool sip_reporting() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool traded_against_retail() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    void print(std::ostream& out) const {
        out << "OrderExecutionFlags{";
        out << "sip_reporting=";
        out << (sip_reporting() ? "true" : "false");
        out << ", traded_against_retail=";
        out << (traded_against_retail() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutionFlags& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
