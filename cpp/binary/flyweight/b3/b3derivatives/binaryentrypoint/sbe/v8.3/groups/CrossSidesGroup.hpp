#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// noSides
class CrossSidesGroup {
  public:
    static constexpr const char* name = "CrossSidesGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CrossSidesGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CrossSidesGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 22;
    static constexpr std::size_t fixed_size = 22;
    std::size_t encoded_size() const { return 22; }

    Side side() const { return static_cast<Side>(wire::read_char(at(0))); }

    std::span<const std::byte, 1> offset_1_padding_1() const { return bytes_.subspan(1).template first<1>(); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(2)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint32_t> entering_firm_optional() const { return wire::nullable(wire::read_u32_le(at(6)), static_cast<std::uint32_t>(0ULL)); }

    std::uint64_t clordid() const { return wire::read_u64_le(at(10)); }

    std::optional<std::uint32_t> trading_sub_account() const { return wire::nullable(wire::read_u32_le(at(18)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "CrossSidesGroup{";
        out << "side=";
        out << side();
        out << ", offset_1_padding_1=";
        print::hex(out, offset_1_padding_1().data(), offset_1_padding_1().size());
        out << ", account=";
        print::optional(out, account());
        out << ", entering_firm_optional=";
        print::optional(out, entering_firm_optional());
        out << ", clordid=";
        out << clordid();
        out << ", trading_sub_account=";
        print::optional(out, trading_sub_account());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CrossSidesGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
