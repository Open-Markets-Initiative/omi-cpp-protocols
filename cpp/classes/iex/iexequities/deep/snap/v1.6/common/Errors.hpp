#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>

namespace iex::iexequities::deep::snap::v1_6 {

// Thrown when a buffer does not hold the bytes a decode needs. The message names
// the class that was decoding, how many bytes it needed and how many it had.
class DecodeError : public std::runtime_error {
  public:
    DecodeError(std::string_view what, std::size_t needed, std::size_t available)
      : std::runtime_error(std::string(what) + ": " + std::to_string(needed)
                           + " bytes needed, " + std::to_string(available) + " available"),
        needed_(needed), available_(available) {}

    std::size_t needed() const { return needed_; }
    std::size_t available() const { return available_; }

  private:
    std::size_t needed_;
    std::size_t available_;
};

// Thrown when a buffer cannot take the bytes an encode produces, or when a packet
// is asked to encode a frame that holds no message.
class EncodeError : public std::runtime_error {
  public:
    EncodeError(std::string_view what, std::size_t needed, std::size_t capacity)
      : std::runtime_error(std::string(what) + ": " + std::to_string(needed)
                           + " bytes needed, " + std::to_string(capacity) + " of capacity"),
        needed_(needed), capacity_(capacity) {}

    EncodeError(std::string_view what, std::string_view reason)
      : std::runtime_error(std::string(what) + ": " + std::string(reason)),
        needed_(0), capacity_(0) {}

    std::size_t needed() const { return needed_; }
    std::size_t capacity() const { return capacity_; }

  private:
    std::size_t needed_;
    std::size_t capacity_;
};

} // namespace iex::iexequities::deep::snap::v1_6
