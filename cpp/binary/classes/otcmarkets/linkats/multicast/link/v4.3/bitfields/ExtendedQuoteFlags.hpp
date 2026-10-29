#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Extended Quote Information
class ExtendedQuoteFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    ExtendedQuoteFlags() = default;
    explicit ExtendedQuoteFlags(std::uint8_t raw);

    // Quote Saturated: Quote should be considered for inside price
    bool quote_saturated() const;
    void set_quote_saturated(bool value);

    // Bid Auto Ex: Bid Auto Execution enabled
    bool bid_auto_ex() const;
    void set_bid_auto_ex(bool value);

    // Offer Auto Ex: Offer Auto Execution enabled
    bool offer_auto_ex() const;
    void set_offer_auto_ex(bool value);

    // Nms Conditional Quote: Displayed quote size is a round lot at least two times greater
    // than the minimum round lot size and cannot be partially filled.
    bool nms_conditional_quote() const;
    void set_nms_conditional_quote(bool value);

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

    bool operator==(const ExtendedQuoteFlags& other) const;
    bool operator!=(const ExtendedQuoteFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const ExtendedQuoteFlags& value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
