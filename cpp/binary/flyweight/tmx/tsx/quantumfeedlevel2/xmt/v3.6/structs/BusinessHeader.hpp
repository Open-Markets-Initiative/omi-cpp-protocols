// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/BusinessHeader.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SourceId.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Xmt Business Header
class BusinessHeader {
  public:
    static constexpr const char* name = "BusinessHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BusinessHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BusinessHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::uint8_t msg_version() const { return wire::read_u8(at(0)); }

    SourceId source_id() const { return static_cast<SourceId>(wire::read_char(at(1))); }

    std::uint16_t stream_id() const { return wire::read_u16_le(at(2)); }

    std::uint8_t sequence_0() const { return wire::read_u8(at(4)); }

    std::uint32_t sequence_1() const { return wire::read_u32_le(at(5)); }

    void print(std::ostream& out) const {
        out << "BusinessHeader{";
        out << "msg_version=";
        out << static_cast<int>(msg_version());
        out << ", source_id=";
        out << source_id();
        out << ", stream_id=";
        out << stream_id();
        out << ", sequence_0=";
        out << static_cast<int>(sequence_0());
        out << ", sequence_1=";
        out << sequence_1();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BusinessHeader& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
