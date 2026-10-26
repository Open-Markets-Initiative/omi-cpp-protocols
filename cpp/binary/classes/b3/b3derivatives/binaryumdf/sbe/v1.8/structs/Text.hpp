#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// text data struct
class Text {
  public:

    Text() = default;
    Text(std::uint16_t text_length, const std::string& text_data);

    // Text Length: Length of a string, in bytes. For instance, the string 'Ação', converted to
    // UTF-8, has 6 bytes, so length = 6.
    std::uint16_t text_length() const;
    void set_text_length(std::uint16_t value);

    // Text Data: Bytes of the string, encoded in UTF-8.
    const std::string& text_data() const;
    std::string& text_data();
    void set_text_data(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Text& other) const;
    bool operator!=(const Text& other) const;

  private:
    std::uint16_t text_length_{};
    std::string text_data_{};
};

std::ostream& operator<<(std::ostream& out, const Text& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
