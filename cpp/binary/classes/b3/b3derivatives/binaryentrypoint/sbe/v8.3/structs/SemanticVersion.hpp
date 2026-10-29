#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// NegotiateResponseMessage
class SemanticVersion {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    SemanticVersion() = default;
    SemanticVersion(std::uint8_t major_number, std::uint8_t minor_number, std::uint8_t patch_number, std::uint8_t build_number);

    // Major Number: majorNumber
    std::uint8_t major_number() const;
    void set_major_number(std::uint8_t value);

    // Minor Number: minorNumber
    std::uint8_t minor_number() const;
    void set_minor_number(std::uint8_t value);

    // Patch Number: patchNumber
    std::uint8_t patch_number() const;
    void set_patch_number(std::uint8_t value);

    // Build Number: buildNumber
    std::uint8_t build_number() const;
    void set_build_number(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SemanticVersion& other) const;
    bool operator!=(const SemanticVersion& other) const;

  private:
    std::uint8_t major_number_{};
    std::uint8_t minor_number_{};
    std::uint8_t patch_number_{};
    std::uint8_t build_number_{};
};

std::ostream& operator<<(std::ostream& out, const SemanticVersion& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
