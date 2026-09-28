#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// uRLLink data struct
class UrlLink {
  public:

    UrlLink() = default;
    UrlLink(std::uint16_t url_link_length, const std::string& url_link_data);

    // Url Link Length: Length of a string, in bytes. For instance, the string 'Ação',
    // converted to UTF-8, has 6 bytes, so length = 6.
    std::uint16_t url_link_length() const;
    void set_url_link_length(std::uint16_t value);

    // Url Link Data: Bytes of the string, encoded in UTF-8.
    const std::string& url_link_data() const;
    std::string& url_link_data();
    void set_url_link_data(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const UrlLink& other) const;
    bool operator!=(const UrlLink& other) const;

  private:
    std::uint16_t url_link_length_{};
    std::string url_link_data_{};
};

std::ostream& operator<<(std::ostream& out, const UrlLink& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
