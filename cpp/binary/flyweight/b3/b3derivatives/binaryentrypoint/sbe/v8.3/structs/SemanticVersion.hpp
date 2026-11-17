// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: structs/SemanticVersion.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// NegotiateResponseMessage
class SemanticVersion {
  public:
    static constexpr const char* name = "SemanticVersion";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SemanticVersion(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SemanticVersion has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::optional<std::uint8_t> major_number() const { return wire::nullable(wire::read_u8(at(0)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> minor_number() const { return wire::nullable(wire::read_u8(at(1)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> patch_number() const { return wire::nullable(wire::read_u8(at(2)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> build_number() const { return wire::nullable(wire::read_u8(at(3)), static_cast<std::uint8_t>(255ULL)); }

    void print(std::ostream& out) const {
        out << "SemanticVersion{";
        out << "major_number=";
        print::optional(out, major_number());
        out << ", minor_number=";
        print::optional(out, minor_number());
        out << ", patch_number=";
        print::optional(out, patch_number());
        out << ", build_number=";
        print::optional(out, build_number());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SemanticVersion& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
