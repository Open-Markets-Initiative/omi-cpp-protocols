// B3.B3Derivatives.BinaryUmdf.Sbe.v1.9: bitfields/MatchEventIndicatorOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// MatchEventIndicator bit set
class MatchEventIndicatorOptional {
  public:
    static constexpr const char* name = "MatchEventIndicatorOptional";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MatchEventIndicatorOptional(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool implied() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool recovery_msg() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool end_of_event() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "MatchEventIndicatorOptional{";
        out << "implied=";
        out << (implied() ? "true" : "false");
        out << ", recovery_msg=";
        out << (recovery_msg() ? "true" : "false");
        out << ", end_of_event=";
        out << (end_of_event() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MatchEventIndicatorOptional& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
