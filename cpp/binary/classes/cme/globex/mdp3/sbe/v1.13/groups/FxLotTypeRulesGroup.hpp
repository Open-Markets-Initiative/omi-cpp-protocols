#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of LotTypeRules entries
class FxLotTypeRulesGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 9;

    FxLotTypeRulesGroup() = default;
    FxLotTypeRulesGroup(std::int8_t lot_type, std::uint64_t min_lot_size_u_int_64);

    // Lot Type: This tag is required to interpret the value in tag 1231-MinLotSize
    std::int8_t lot_type() const;
    void set_lot_type(std::int8_t value);

    // Min Lot Size u Int 64: For FX instruments in the repeating group with Tag
    // 1093-LotType=2, Tag 1231-MinLotSize provides a Regular Amount - a default order size on
    // the Workstation screen. With tag 1093-LotType= 5, Tag 1231-MinLotSize value represents
    // standard min order qty increment. With tag 1093-LotType=6 tag 1231-MinLotSize contains
    // SizePriorityQty for instruments trading with Match Algorithm = P (Size Priority)
    std::uint64_t min_lot_size_u_int_64() const;
    void set_min_lot_size_u_int_64(std::uint64_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FxLotTypeRulesGroup& other) const;
    bool operator!=(const FxLotTypeRulesGroup& other) const;

  private:
    std::int8_t lot_type_{};
    std::uint64_t min_lot_size_u_int_64_{};
};

std::ostream& operator<<(std::ostream& out, const FxLotTypeRulesGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
