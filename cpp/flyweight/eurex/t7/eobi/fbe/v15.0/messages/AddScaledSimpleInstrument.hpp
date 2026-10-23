#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityType.hpp"
#include "../structs/RelatedInstrumentGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class AddScaledSimpleInstrument {
  public:
    static constexpr const char* name = "AddScaledSimpleInstrument";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddScaledSimpleInstrument(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddScaledSimpleInstrument has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 72;
    static constexpr std::size_t fixed_size = 72;
    std::size_t encoded_size() const { return 72; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::string_view security_desc() const { return view::text(at(16), 40, ' '); }

    std::optional<SecurityType> security_type() const { return wire::nullable_enum<SecurityType>(wire::read_u8(at(56)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 1> pad1() const { return bytes_.subspan(57).template first<1>(); }

    std::optional<std::uint16_t> quantity_scaling_factor() const { return wire::nullable(wire::read_u16_le(at(58)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::span<const std::byte, 4> pad4() const { return bytes_.subspan(60).template first<4>(); }

    RelatedInstrumentGrpComp related_instrument_grp_comp() const { return RelatedInstrumentGrpComp{ bytes_.subspan(64) }; }

    void print(std::ostream& out) const {
        out << "AddScaledSimpleInstrument{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", security_desc=";
        print::text(out, security_desc());
        out << ", security_type=";
        print::optional(out, security_type());
        out << ", pad1=";
        print::hex(out, pad1().data(), pad1().size());
        out << ", quantity_scaling_factor=";
        print::optional(out, quantity_scaling_factor());
        out << ", pad4=";
        print::hex(out, pad4().data(), pad4().size());
        out << ", related_instrument_grp_comp=";
        related_instrument_grp_comp().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddScaledSimpleInstrument& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
