#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Reserved for future use
class StatisticsReserved {
  public:
    static constexpr const char* name = "StatisticsReserved";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StatisticsReserved(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    std::uint8_t unused_8() const { return static_cast<std::uint8_t>((raw() & static_cast<std::uint8_t>(0xFF)) >> 0); }

    void print(std::ostream& out) const {
        out << "StatisticsReserved{";
        out << "unused_8=";
        out << static_cast<unsigned long long>(unused_8());
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StatisticsReserved& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
