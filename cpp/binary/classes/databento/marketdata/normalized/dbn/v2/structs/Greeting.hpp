#pragma once

#include <cstddef>
#include <ostream>
#include <string>

namespace databento::marketdata::normalized::dbn::v2 {

// The message sent by the gateway immediately after a client connects (lsg_version: the live
// gateway version)
class Greeting {
  public:

    Greeting() = default;
    Greeting(const std::string& control_fields);

    // Control Fields: ASCII key=value pairs separated by the | character, terminated by a
    // newline character
    const std::string& control_fields() const;
    std::string& control_fields();
    void set_control_fields(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Greeting& other) const;
    bool operator!=(const Greeting& other) const;

  private:
    std::string control_fields_{};
};

std::ostream& operator<<(std::ostream& out, const Greeting& value);

} // namespace databento::marketdata::normalized::dbn::v2
