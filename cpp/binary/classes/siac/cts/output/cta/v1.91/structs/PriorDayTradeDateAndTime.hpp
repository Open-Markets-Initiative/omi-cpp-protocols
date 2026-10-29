#pragma once

#include <chrono>
#include <cstddef>
#include <ostream>

namespace siac::cts::output::cta::v1_91 {

// Prior Day Trade Date and Time
class PriorDayTradeDateAndTime {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    PriorDayTradeDateAndTime() = default;
    PriorDayTradeDateAndTime(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds);

    // Seconds: contains the number of seconds from Epoch 1/1/1970, 00:00:00 UTC
    std::chrono::seconds seconds() const;
    void set_seconds(std::chrono::seconds value);

    // Nanoseconds: Nanosecond portion of the time
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PriorDayTradeDateAndTime& other) const;
    bool operator!=(const PriorDayTradeDateAndTime& other) const;

  private:
    std::chrono::seconds seconds_{};
    std::chrono::nanoseconds nanoseconds_{};
};

std::ostream& operator<<(std::ostream& out, const PriorDayTradeDateAndTime& value);

} // namespace siac::cts::output::cta::v1_91
