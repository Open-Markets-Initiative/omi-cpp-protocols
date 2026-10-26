#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// securityDesc data struct
class SecurityDesc {
  public:

    SecurityDesc() = default;
    SecurityDesc(std::uint8_t security_desc_length, const std::string& security_desc_data);

    // Security Desc Length: Length in bytes of the security description text
    std::uint8_t security_desc_length() const;
    void set_security_desc_length(std::uint8_t value);

    // Security Desc Data: textual description for the financial instrument
    const std::string& security_desc_data() const;
    std::string& security_desc_data();
    void set_security_desc_data(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecurityDesc& other) const;
    bool operator!=(const SecurityDesc& other) const;

  private:
    std::uint8_t security_desc_length_{};
    std::string security_desc_data_{};
};

std::ostream& operator<<(std::ostream& out, const SecurityDesc& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
