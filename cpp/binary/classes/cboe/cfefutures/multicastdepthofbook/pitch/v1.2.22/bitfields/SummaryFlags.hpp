#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Summary Flags bitfields
class SummaryFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    SummaryFlags() = default;
    explicit SummaryFlags(std::uint8_t raw);

    // High Price Valid: Set if High Price is a valid value
    bool high_price_valid() const;
    void set_high_price_valid(bool value);

    // High Price Is Bid: Set if High Price was set by the highest bid (rather than a trade)
    bool high_price_is_bid() const;
    void set_high_price_is_bid(bool value);

    // Low Price Valid: Set if Low Price is a valid value
    bool low_price_valid() const;
    void set_low_price_valid(bool value);

    // Low Price Is Offer: Set if Low Price was set by the lowest offer (rather than a trade)
    bool low_price_is_offer() const;
    void set_low_price_is_offer(bool value);

    // Open Close Valid: Set if both Open Price and Close Price fields contain valid values
    bool open_close_valid() const;
    void set_open_close_valid(bool value);

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

    bool operator==(const SummaryFlags& other) const;
    bool operator!=(const SummaryFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const SummaryFlags& value);

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
