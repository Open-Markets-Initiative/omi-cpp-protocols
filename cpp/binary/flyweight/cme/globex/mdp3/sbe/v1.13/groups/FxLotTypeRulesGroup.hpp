#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of LotTypeRules entries
class FxLotTypeRulesGroup {
  public:
    static constexpr const char* name = "FxLotTypeRulesGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FxLotTypeRulesGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FxLotTypeRulesGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::int8_t lot_type() const { return wire::read_i8(at(0)); }

    std::uint64_t min_lot_size_u_int_64() const { return wire::read_u64_le(at(1)); }

    void print(std::ostream& out) const {
        out << "FxLotTypeRulesGroup{";
        out << "lot_type=";
        out << static_cast<int>(lot_type());
        out << ", min_lot_size_u_int_64=";
        out << min_lot_size_u_int_64();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FxLotTypeRulesGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
