#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Quote Information
class QuoteFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    QuoteFlags() = default;
    explicit QuoteFlags(std::uint8_t raw);

    // Update Side: Ask or Bid
    bool update_side() const;
    void set_update_side(bool value);

    // State: Open or Closed
    bool state() const;
    void set_state(bool value);

    // Ask Unsolicited: Ask Unsolicited
    bool ask_unsolicited() const;
    void set_ask_unsolicited(bool value);

    // Ask Priced: Ask Priced
    bool ask_priced() const;
    void set_ask_priced(bool value);

    // Ask Bid Wanted: Ask Bid Wanted
    bool ask_bid_wanted() const;
    void set_ask_bid_wanted(bool value);

    // Bid Unsolicited: Bid Unsolicited
    bool bid_unsolicited() const;
    void set_bid_unsolicited(bool value);

    // Bid Priced: Bid Priced
    bool bid_priced() const;
    void set_bid_priced(bool value);

    // Bid Ask Wanted: Bid Ask Wanted
    bool bid_ask_wanted() const;
    void set_bid_ask_wanted(bool value);

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

    bool operator==(const QuoteFlags& other) const;
    bool operator!=(const QuoteFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const QuoteFlags& value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
