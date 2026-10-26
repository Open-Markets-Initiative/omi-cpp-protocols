#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Number of entries
class LotTypeRulesGroup {
  public:
    static constexpr const char* name = "LotTypeRulesGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LotTypeRulesGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LotTypeRulesGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    std::int8_t lot_type() const { return wire::read_i8(at(0)); }

    std::optional<Decimal> min_lot_size() const { return wire::nullable_decimal(wire::read_i32_le(at(1)), static_cast<std::int32_t>(2147483647LL), -4); }

    void print(std::ostream& out) const {
        out << "LotTypeRulesGroup{";
        out << "lot_type=";
        out << static_cast<int>(lot_type());
        out << ", min_lot_size=";
        print::optional(out, min_lot_size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LotTypeRulesGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
