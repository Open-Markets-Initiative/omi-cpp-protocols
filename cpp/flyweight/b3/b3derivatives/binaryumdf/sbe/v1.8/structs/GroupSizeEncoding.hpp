#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// GroupSizeEncoding
class GroupSizeEncoding {
  public:
    static constexpr const char* name = "GroupSizeEncoding";

    // the bytes it reads, which it does not own: they must outlive it
    explicit GroupSizeEncoding(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every GroupSizeEncoding has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    std::uint16_t block_length() const { return wire::read_u16_le(at(0)); }

    std::uint8_t num_in_group() const { return wire::read_u8(at(2)); }

    void print(std::ostream& out) const {
        out << "GroupSizeEncoding{";
        out << "block_length=";
        out << block_length();
        out << ", num_in_group=";
        out << static_cast<int>(num_in_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const GroupSizeEncoding& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
