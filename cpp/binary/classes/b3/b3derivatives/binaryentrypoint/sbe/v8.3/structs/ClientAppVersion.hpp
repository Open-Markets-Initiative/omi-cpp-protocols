#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// clientAppVersion data struct
class ClientAppVersion {
  public:

    ClientAppVersion() = default;
    ClientAppVersion(std::uint8_t client_app_version_length, const std::string& client_app_version_data);

    // Client App Version Length: Length of client system information.
    std::uint8_t client_app_version_length() const;
    void set_client_app_version_length(std::uint8_t value);

    // Client App Version Data: Client system information.
    const std::string& client_app_version_data() const;
    std::string& client_app_version_data();
    void set_client_app_version_data(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ClientAppVersion& other) const;
    bool operator!=(const ClientAppVersion& other) const;

  private:
    std::uint8_t client_app_version_length_{};
    std::string client_app_version_data_{};
};

std::ostream& operator<<(std::ostream& out, const ClientAppVersion& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
