#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Trade Flags
class TradeFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    TradeFlags() = default;
    explicit TradeFlags(std::uint8_t raw);

    // Trade Cancellation: Trade Cancellation
    bool trade_cancellation() const;
    void set_trade_cancellation(bool value);

    // Trade Correction: Trade Correction
    bool trade_correction() const;
    void set_trade_correction(bool value);

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

} // namespace lseg::lse::level2mbo::gtp::v26_2
