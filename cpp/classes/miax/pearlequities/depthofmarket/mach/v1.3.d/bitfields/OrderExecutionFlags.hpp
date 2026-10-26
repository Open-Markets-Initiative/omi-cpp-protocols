#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Order Execution flags. Bit 0 indicates SIP reportability; bit 1 indicates Traded Against
// Retail; bits 2-7 are reserved.
class OrderExecutionFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    OrderExecutionFlags() = default;
    explicit OrderExecutionFlags(std::uint8_t raw);

    // Sip Reporting: 0 - Not reportable to the SIP; 1 - Reportable to the SIP.
    bool sip_reporting() const;
    void set_sip_reporting(bool value);

    // Traded Against Retail: 0 - Did not trade against Retail; 1 - Traded against Retail.
    bool traded_against_retail() const;
    void set_traded_against_retail(bool value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const OrderExecutionFlags& other) const;
    bool operator!=(const OrderExecutionFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const OrderExecutionFlags& value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
