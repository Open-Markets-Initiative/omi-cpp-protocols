#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// memo data struct
class Memo {
  public:

    Memo() = default;
    Memo(std::uint8_t memo_length, const std::string& memo_data);

    // Memo Length: Length of free format text field defined by client.
    std::uint8_t memo_length() const;
    void set_memo_length(std::uint8_t value);

    // Memo Data: Free ASCII format text field defined by client.
    const std::string& memo_data() const;
    std::string& memo_data();
    void set_memo_data(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Memo& other) const;
    bool operator!=(const Memo& other) const;

  private:
    std::uint8_t memo_length_{};
    std::string memo_data_{};
};

std::ostream& operator<<(std::ostream& out, const Memo& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
