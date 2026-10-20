#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

// Security Directory Flags
class SecurityDirectoryFlags {
  public:
    static constexpr const char* name = "SecurityDirectoryFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityDirectoryFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool etp() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool when_issued() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool test_security() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "SecurityDirectoryFlags{";
        out << "etp=";
        out << (etp() ? "true" : "false");
        out << ", when_issued=";
        out << (when_issued() ? "true" : "false");
        out << ", test_security=";
        out << (test_security() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityDirectoryFlags& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deepplus::iextp::v1_01
