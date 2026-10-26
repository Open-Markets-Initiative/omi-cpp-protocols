#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace iex::iexequities::tops::iextp::v1_56 {

// Quote Update Flags
class QuoteUpdateFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    QuoteUpdateFlags() = default;
    explicit QuoteUpdateFlags(std::uint8_t raw);

    // Market Session: Market Session Flag
    bool market_session() const;
    void set_market_session(bool value);

    // Symbol Availability: Symbol is halted, paused, or otherwise not available for trading on
    // IEX
    bool symbol_availability() const;
    void set_symbol_availability(bool value);

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

    bool operator==(const QuoteUpdateFlags& other) const;
    bool operator!=(const QuoteUpdateFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const QuoteUpdateFlags& value);

} // namespace iex::iexequities::tops::iextp::v1_56
