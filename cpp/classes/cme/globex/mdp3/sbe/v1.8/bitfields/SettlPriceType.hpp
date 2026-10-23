#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_8 {

// SettlPriceType bit set
class SettlPriceType {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    SettlPriceType() = default;
    explicit SettlPriceType(std::uint8_t raw);

    // Final: Final
    bool final() const;
    void set_final(bool value);

    // Actual: Actual
    bool actual() const;
    void set_actual(bool value);

    // Rounded: Rounded
    bool rounded() const;
    void set_rounded(bool value);

    // Intraday: Intraday
    bool intraday() const;
    void set_intraday(bool value);

    // Reserved Bits: ReservedBits
    bool reserved_bits() const;
    void set_reserved_bits(bool value);

    // Unused Settl Price Type 5: Unused SettlPriceType 5
    bool unused_settl_price_type_5() const;
    void set_unused_settl_price_type_5(bool value);

    // Unused Settl Price Type 6: Unused SettlPriceType 6
    bool unused_settl_price_type_6() const;
    void set_unused_settl_price_type_6(bool value);

    // Null Value: NullValue
    bool null_value() const;
    void set_null_value(bool value);

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

    bool operator==(const SettlPriceType& other) const;
    bool operator!=(const SettlPriceType& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const SettlPriceType& value);

} // namespace cme::globex::mdp3::sbe::v1_8
