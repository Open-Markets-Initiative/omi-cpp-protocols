#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace iex::iexequities::deep::iextp::v1_06 {

// Sale Condition Flags
class SaleConditionFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    SaleConditionFlags() = default;
    explicit SaleConditionFlags(std::uint8_t raw);

    // Singleprice Cross Trade: Trade resulting from a single-price cross
    bool singleprice_cross_trade() const;
    void set_singleprice_cross_trade(bool value);

    // Trade Through Exempt: Trade is not subject to Rule 611
    bool trade_through_exempt() const;
    void set_trade_through_exempt(bool value);

    // Odd Lot: Odd Lot
    bool odd_lot() const;
    void set_odd_lot(bool value);

    // Extended Hours: Extended Hours Trade
    bool extended_hours() const;
    void set_extended_hours(bool value);

    // Intermarket Sweep: Intermarket Sweep Order
    bool intermarket_sweep() const;
    void set_intermarket_sweep(bool value);

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

    bool operator==(const SaleConditionFlags& other) const;
    bool operator!=(const SaleConditionFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const SaleConditionFlags& value);

} // namespace iex::iexequities::deep::iextp::v1_06
