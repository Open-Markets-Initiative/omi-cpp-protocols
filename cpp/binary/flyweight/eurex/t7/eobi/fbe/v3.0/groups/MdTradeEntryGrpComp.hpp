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
#include "../enums/MdEntryType.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

class MdTradeEntryGrpComp {
  public:
    static constexpr const char* name = "MdTradeEntryGrpComp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MdTradeEntryGrpComp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MdTradeEntryGrpComp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::optional<Decimal> md_entry_px() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<std::int32_t> md_entry_size() const { return wire::nullable(wire::read_i32_le(at(8)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<MdEntryType> md_entry_type() const { return wire::nullable_enum<MdEntryType>(wire::read_u8(at(12)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 3> pad3() const { return bytes_.subspan(13).template first<3>(); }

    void print(std::ostream& out) const {
        out << "MdTradeEntryGrpComp{";
        out << "md_entry_px=";
        print::optional(out, md_entry_px());
        out << ", md_entry_size=";
        print::optional(out, md_entry_size());
        out << ", md_entry_type=";
        print::optional(out, md_entry_type());
        out << ", pad3=";
        print::hex(out, pad3().data(), pad3().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MdTradeEntryGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v3_0
