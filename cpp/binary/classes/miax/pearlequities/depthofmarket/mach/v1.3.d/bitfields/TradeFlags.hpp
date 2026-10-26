#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Trade flags. Bit 0 indicates SIP reportability; bit 1 indicates Retail Trade participation;
// bits 2-7 are reserved.
class TradeFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    TradeFlags() = default;
    explicit TradeFlags(std::uint8_t raw);

    // Sip Reporting: 0 - Not reportable to the SIP; 1 - Reportable to the SIP.
    bool sip_reporting() const;
    void set_sip_reporting(bool value);

    // Retail Trade Indicator: 0 - Neither side is Retail; 1 - At least one side is Retail.
    bool retail_trade_indicator() const;
    void set_retail_trade_indicator(bool value);

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

    bool operator==(const TradeFlags& other) const;
    bool operator!=(const TradeFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const TradeFlags& value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
