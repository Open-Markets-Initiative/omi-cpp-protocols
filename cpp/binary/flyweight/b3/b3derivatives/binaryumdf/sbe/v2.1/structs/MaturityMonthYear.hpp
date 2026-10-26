#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// SecurityDefinition_12Message
class MaturityMonthYear {
  public:
    static constexpr const char* name = "MaturityMonthYear";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MaturityMonthYear(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MaturityMonthYear has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    std::uint16_t year() const { return wire::read_u16_le(at(0)); }

    std::uint8_t month() const { return wire::read_u8(at(2)); }

    std::uint8_t day() const { return wire::read_u8(at(3)); }

    std::uint8_t week() const { return wire::read_u8(at(4)); }

    void print(std::ostream& out) const {
        out << "MaturityMonthYear{";
        out << "year=";
        out << year();
        out << ", month=";
        out << static_cast<int>(month());
        out << ", day=";
        out << static_cast<int>(day());
        out << ", week=";
        out << static_cast<int>(week());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MaturityMonthYear& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
