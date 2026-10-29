#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// deskID data struct
class DeskId {
  public:

    DeskId() = default;
    DeskId(std::uint8_t desk_id_length, const std::string& desk_id_data);

    // Desk Id Length: Length of trading desk identification.
    std::uint8_t desk_id_length() const;
    void set_desk_id_length(std::uint8_t value);

    // Desk Id Data: Trading desk identification in ASCII format.
    const std::string& desk_id_data() const;
    std::string& desk_id_data();
    void set_desk_id_data(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const DeskId& other) const;
    bool operator!=(const DeskId& other) const;

  private:
    std::uint8_t desk_id_length_{};
    std::string desk_id_data_{};
};

std::ostream& operator<<(std::ostream& out, const DeskId& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
