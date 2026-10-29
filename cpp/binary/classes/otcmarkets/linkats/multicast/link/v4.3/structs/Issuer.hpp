#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Issuer
class Issuer {
  public:

    Issuer() = default;
    Issuer(std::uint8_t issuer_size, const std::string& issuer_name);

    // Issuer Size: Size of the IssuerName field. If zero, IssuerName is not present.
    std::uint8_t issuer_size() const;
    void set_issuer_size(std::uint8_t value);

    // Issuer Name: Issuer name
    const std::string& issuer_name() const;
    std::string& issuer_name();
    void set_issuer_name(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Issuer& other) const;
    bool operator!=(const Issuer& other) const;

  private:
    std::uint8_t issuer_size_{};
    std::string issuer_name_{};
};

std::ostream& operator<<(std::ostream& out, const Issuer& value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
