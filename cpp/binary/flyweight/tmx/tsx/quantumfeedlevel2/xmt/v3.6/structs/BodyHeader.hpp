// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/BodyHeader.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MsgType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Xmt Body Header
class BodyHeader {
  public:
    static constexpr const char* name = "BodyHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BodyHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BodyHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    std::uint16_t msg_length() const { return wire::read_u16_le(at(0)); }

    MsgType msg_type() const { return static_cast<MsgType>(wire::read_char(at(2))); }

    void print(std::ostream& out) const {
        out << "BodyHeader{";
        out << "msg_length=";
        out << msg_length();
        out << ", msg_type=";
        out << msg_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BodyHeader& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
