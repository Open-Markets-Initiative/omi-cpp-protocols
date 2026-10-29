#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Currency Code
class CurrencyCode {
  public:

    CurrencyCode() = default;
    CurrencyCode(std::uint8_t currency_code_length, const std::string& currency_code_text);

    // Currency Code Length: Not used
    std::uint8_t currency_code_length() const;
    void set_currency_code_length(std::uint8_t value);

    // Currency Code Text: Not used
    const std::string& currency_code_text() const;
    std::string& currency_code_text();
    void set_currency_code_text(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CurrencyCode& other) const;
    bool operator!=(const CurrencyCode& other) const;

  private:
    std::uint8_t currency_code_length_{};
    std::string currency_code_text_{};
};

std::ostream& operator<<(std::ostream& out, const CurrencyCode& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
