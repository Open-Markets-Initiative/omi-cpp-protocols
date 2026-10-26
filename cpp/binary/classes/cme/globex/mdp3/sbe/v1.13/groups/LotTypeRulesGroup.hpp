#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries
class LotTypeRulesGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    LotTypeRulesGroup() = default;
    LotTypeRulesGroup(std::int8_t lot_type, std::optional<Decimal> min_lot_size_decimal_qty);

    // Lot Type: This tag is required to interpret the value in tag 1231-MinLotSize
    std::int8_t lot_type() const;
    void set_lot_type(std::int8_t value);

    // Min Lot Size Decimal Qty: Minimum quantity accepted for order entry. If tag
    // 1093-LotType=4, this value is the minimum quantity for order entry expressed in the
    // applicable units, specified in tag 996-UnitOfMeasure, e.g. megawatts
    std::optional<Decimal> min_lot_size_decimal_qty() const;
    void set_min_lot_size_decimal_qty(std::optional<Decimal> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const LotTypeRulesGroup& other) const;
    bool operator!=(const LotTypeRulesGroup& other) const;

  private:
    std::int8_t lot_type_{};
    std::optional<Decimal> min_lot_size_decimal_qty_{};
};

std::ostream& operator<<(std::ostream& out, const LotTypeRulesGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
