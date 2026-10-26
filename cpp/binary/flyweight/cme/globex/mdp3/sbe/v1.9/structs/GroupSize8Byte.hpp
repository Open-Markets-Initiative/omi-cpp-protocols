#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// 8 Byte aligned repeating group dimensions
class GroupSize8Byte {
  public:
    static constexpr const char* name = "GroupSize8Byte";

    // the bytes it reads, which it does not own: they must outlive it
    explicit GroupSize8Byte(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every GroupSize8Byte has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint16_t block_length() const { return wire::read_u16_le(at(0)); }

    std::span<const std::byte, 5> padding_5() const { return bytes_.subspan(2).template first<5>(); }

    std::uint8_t num_in_group() const { return wire::read_u8(at(7)); }

    void print(std::ostream& out) const {
        out << "GroupSize8Byte{";
        out << "block_length=";
        out << block_length();
        out << ", padding_5=";
        print::hex(out, padding_5().data(), padding_5().size());
        out << ", num_in_group=";
        out << static_cast<int>(num_in_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const GroupSize8Byte& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
