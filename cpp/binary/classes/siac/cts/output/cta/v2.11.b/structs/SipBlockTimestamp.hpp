#pragma once

#include <chrono>
#include <cstddef>
#include <ostream>

namespace siac::cts::output::cta::v2_11_b {

// Cta packet timestamp
class SipBlockTimestamp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    SipBlockTimestamp() = default;
    SipBlockTimestamp(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds);

    // Seconds: Contains The Number Seconds From Epoch 111970000000 Utc
    std::chrono::seconds seconds() const;
    void set_seconds(std::chrono::seconds value);

    // Nanoseconds: The Nanosecond Portion Of The Time Currently Rounded To The Nearest
    // Microsecond
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SipBlockTimestamp& other) const;
    bool operator!=(const SipBlockTimestamp& other) const;

  private:
    std::chrono::seconds seconds_{};
    std::chrono::nanoseconds nanoseconds_{};
};

std::ostream& operator<<(std::ostream& out, const SipBlockTimestamp& value);

} // namespace siac::cts::output::cta::v2_11_b
