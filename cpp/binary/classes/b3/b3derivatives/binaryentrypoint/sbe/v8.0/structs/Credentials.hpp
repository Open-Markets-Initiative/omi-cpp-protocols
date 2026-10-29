#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// credentials data struct
class Credentials {
  public:

    Credentials() = default;
    Credentials(std::uint8_t credentials_length, const std::string& credentials_data);

    // Credentials Length: Length of credentials data.
    std::uint8_t credentials_length() const;
    void set_credentials_length(std::uint8_t value);

    // Credentials Data: Credentials data in ASCII.
    const std::string& credentials_data() const;
    std::string& credentials_data();
    void set_credentials_data(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Credentials& other) const;
    bool operator!=(const Credentials& other) const;

  private:
    std::uint8_t credentials_length_{};
    std::string credentials_data_{};
};

std::ostream& operator<<(std::ostream& out, const Credentials& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
