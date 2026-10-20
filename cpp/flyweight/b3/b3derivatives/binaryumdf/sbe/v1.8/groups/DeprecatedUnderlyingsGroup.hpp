#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// noUnderlyings
class DeprecatedUnderlyingsGroup {
  public:
    static constexpr const char* name = "DeprecatedUnderlyingsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeprecatedUnderlyingsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeprecatedUnderlyingsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    std::uint64_t underlying_security_id() const { return wire::read_u64_le(at(0)); }

    std::optional<Decimal> index_pct() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0LL), -9); }

    std::optional<Decimal> index_theoretical_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::string_view underlying_symbol() const { return view::text(at(24), 20, '\0'); }

    void print(std::ostream& out) const {
        out << "DeprecatedUnderlyingsGroup{";
        out << "underlying_security_id=";
        out << underlying_security_id();
        out << ", index_pct=";
        print::optional(out, index_pct());
        out << ", index_theoretical_qty=";
        print::optional(out, index_theoretical_qty());
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeprecatedUnderlyingsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
