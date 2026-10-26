#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ExpirationMonth.hpp"

namespace siac::opra::output::obi::v6_2 {

// Expiration Block
class ExpirationBlock {
  public:
    static constexpr const char* name = "ExpirationBlock";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExpirationBlock(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExpirationBlock has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    ExpirationMonth expiration_month() const { return static_cast<ExpirationMonth>(wire::read_char(at(0))); }

    std::uint8_t expiration_day() const { return wire::read_u8(at(1)); }

    std::uint8_t expiration_year() const { return wire::read_u8(at(2)); }

    void print(std::ostream& out) const {
        out << "ExpirationBlock{";
        out << "expiration_month=";
        out << expiration_month();
        out << ", expiration_day=";
        out << static_cast<int>(expiration_day());
        out << ", expiration_year=";
        out << static_cast<int>(expiration_year());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExpirationBlock& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
