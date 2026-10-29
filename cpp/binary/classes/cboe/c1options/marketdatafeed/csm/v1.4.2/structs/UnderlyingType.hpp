#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Underlying Type
class UnderlyingType {
  public:

    UnderlyingType() = default;
    UnderlyingType(std::uint8_t underlying_type_length, const std::string& underlying_type_text);

    // Underlying Type Length:
    std::uint8_t underlying_type_length() const;
    void set_underlying_type_length(std::uint8_t value);

    // Underlying Type Text:
    const std::string& underlying_type_text() const;
    std::string& underlying_type_text();
    void set_underlying_type_text(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const UnderlyingType& other) const;
    bool operator!=(const UnderlyingType& other) const;

  private:
    std::uint8_t underlying_type_length_{};
    std::string underlying_type_text_{};
};

std::ostream& operator<<(std::ostream& out, const UnderlyingType& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
