#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// noUnderlyings
class UnderlyingsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 28;

    UnderlyingsGroup() = default;
    UnderlyingsGroup(std::uint64_t underlying_security_id, const std::string& underlying_symbol);

    // Underlying Security Id: Underlying instrument's security ID.
    std::uint64_t underlying_security_id() const;
    void set_underlying_security_id(std::uint64_t value);

    // Underlying Symbol: Underlying instrument's ticker symbol.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const UnderlyingsGroup& other) const;
    bool operator!=(const UnderlyingsGroup& other) const;

  private:
    std::uint64_t underlying_security_id_{};
    std::string underlying_symbol_{};
};

std::ostream& operator<<(std::ostream& out, const UnderlyingsGroup& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
