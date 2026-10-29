#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ProductComplex.hpp"
#include "../enums/ImpliedMarketIndicator.hpp"
#include "../groups/InstrmtLegGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class AddComplexInstrument {
  public:
    static constexpr const char* name = "AddComplexInstrument";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddComplexInstrument(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddComplexInstrument has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 504;
    static constexpr std::size_t fixed_size = 504;
    std::size_t encoded_size() const { return 504; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::int32_t> security_sub_type() const { return wire::nullable(wire::read_i32_le(at(16)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<ProductComplex> product_complex() const { return wire::nullable_enum<ProductComplex>(wire::read_u8(at(20)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<ImpliedMarketIndicator> implied_market_indicator() const { return wire::nullable_enum<ImpliedMarketIndicator>(wire::read_u8(at(21)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<std::uint8_t> no_legs() const { return wire::nullable(wire::read_u8(at(22)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 1> pad1() const { return bytes_.subspan(23).template first<1>(); }

    view::entries<InstrmtLegGrpComp> instrmt_leg_grp_comp() const { return view::entries<InstrmtLegGrpComp>{ bytes_.subspan(24), 20 }; }

    void print(std::ostream& out) const {
        out << "AddComplexInstrument{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", security_sub_type=";
        print::optional(out, security_sub_type());
        out << ", product_complex=";
        print::optional(out, product_complex());
        out << ", implied_market_indicator=";
        print::optional(out, implied_market_indicator());
        out << ", no_legs=";
        print::optional(out, no_legs());
        out << ", pad1=";
        print::hex(out, pad1().data(), pad1().size());
        out << ", instrmt_leg_grp_comp=";
        print::sequence(out, instrmt_leg_grp_comp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddComplexInstrument& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v6_0
