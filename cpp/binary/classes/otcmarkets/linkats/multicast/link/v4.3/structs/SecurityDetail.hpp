#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// SecurityDetail
class SecurityDetail {
  public:

    SecurityDetail() = default;
    SecurityDetail(std::uint8_t security_detail_size, const std::string& security_detail_name);

    // Security Detail Size: Size of the SecurityDetail field. If zero, SecurityDetail is not
    // present.
    std::uint8_t security_detail_size() const;
    void set_security_detail_size(std::uint8_t value);

    // Security Detail Name: Security detail name
    const std::string& security_detail_name() const;
    std::string& security_detail_name();
    void set_security_detail_name(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecurityDetail& other) const;
    bool operator!=(const SecurityDetail& other) const;

  private:
    std::uint8_t security_detail_size_{};
    std::string security_detail_name_{};
};

std::ostream& operator<<(std::ostream& out, const SecurityDetail& value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
