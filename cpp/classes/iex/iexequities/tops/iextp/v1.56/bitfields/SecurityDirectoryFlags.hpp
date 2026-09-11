#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace iex::iexequities::tops::iextp::v1_56 {

// Security Directory Flags
class SecurityDirectoryFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    SecurityDirectoryFlags() = default;
    explicit SecurityDirectoryFlags(std::uint8_t raw);

    // Etp: Symbol is an ETP
    bool etp() const;
    void set_etp(bool value);

    // When Issued: Symbol is a when issued security
    bool when_issued() const;
    void set_when_issued(bool value);

    // Test Security: Symbol is a test security
    bool test_security() const;
    void set_test_security(bool value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecurityDirectoryFlags& other) const;
    bool operator!=(const SecurityDirectoryFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const SecurityDirectoryFlags& value);

} // namespace iex::iexequities::tops::iextp::v1_56
