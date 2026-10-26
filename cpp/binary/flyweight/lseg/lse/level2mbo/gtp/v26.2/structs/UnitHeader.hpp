#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class UnitHeader {
  public:
    static constexpr const char* name = "UnitHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnitHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnitHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint16_t length() const { return wire::read_u16_le(at(0)); }

    std::uint8_t message_count() const { return wire::read_u8(at(2)); }

    char market_data_group() const { return wire::read_char(at(3)); }

    std::uint32_t sequence_number() const { return wire::read_u32_le(at(4)); }

    void print(std::ostream& out) const {
        out << "UnitHeader{";
        out << "length=";
        out << length();
        out << ", message_count=";
        out << static_cast<int>(message_count());
        out << ", market_data_group=";
        print::character(out, market_data_group());
        out << ", sequence_number=";
        out << sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnitHeader& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
