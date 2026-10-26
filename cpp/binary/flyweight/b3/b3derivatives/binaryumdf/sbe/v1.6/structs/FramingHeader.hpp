#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// B3 Sbe framing header
class FramingHeader {
  public:
    static constexpr const char* name = "FramingHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FramingHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FramingHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::uint16_t message_length() const { return wire::read_u16_le(at(0)); }

    std::uint16_t encoding_type() const { return wire::read_u16_le(at(2)); }

    void print(std::ostream& out) const {
        out << "FramingHeader{";
        out << "message_length=";
        out << message_length();
        out << ", encoding_type=";
        out << encoding_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FramingHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
