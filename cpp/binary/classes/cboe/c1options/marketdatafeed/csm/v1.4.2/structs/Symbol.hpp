#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Symbol
class Symbol {
  public:

    Symbol() = default;
    Symbol(std::uint8_t symbol_length, const std::string& symbol_text);

    // Symbol Length: Symbol of the class
    std::uint8_t symbol_length() const;
    void set_symbol_length(std::uint8_t value);

    // Symbol Text: Symbol of the class
    const std::string& symbol_text() const;
    std::string& symbol_text();
    void set_symbol_text(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Symbol& other) const;
    bool operator!=(const Symbol& other) const;

  private:
    std::uint8_t symbol_length_{};
    std::string symbol_text_{};
};

std::ostream& operator<<(std::ostream& out, const Symbol& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
