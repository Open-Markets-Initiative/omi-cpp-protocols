// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: structs/InvestorId.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// SimpleNewOrderMessage
class InvestorId {
  public:
    static constexpr const char* name = "InvestorId";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InvestorId(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InvestorId has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::optional<std::uint16_t> prefix() const { return wire::nullable(wire::read_u16_le(at(0)), static_cast<std::uint16_t>(0ULL)); }

    std::span<const std::byte, 2> offset_2_padding_2() const { return bytes_.subspan(2).template first<2>(); }

    std::optional<std::uint32_t> document() const { return wire::nullable(wire::read_u32_le(at(4)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "InvestorId{";
        out << "prefix=";
        print::optional(out, prefix());
        out << ", offset_2_padding_2=";
        print::hex(out, offset_2_padding_2().data(), offset_2_padding_2().size());
        out << ", document=";
        print::optional(out, document());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InvestorId& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
