#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Unit Header
class UnitHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    UnitHeader() = default;
    UnitHeader(std::uint16_t length, std::uint8_t message_count, char market_data_group, std::uint32_t sequence_number);

    // Length: Length of the message block including the header and all payload messages
    std::uint16_t length() const;
    void set_length(std::uint16_t value);

    // Message Count: Number of payload messages that will follow the header
    std::uint8_t message_count() const;
    void set_message_count(std::uint8_t value);

    // Market Data Group: Identity of the market data group the payload messages relate to
    char market_data_group() const;
    void set_market_data_group(char value);

    // Sequence Number: Sequence number of the first payload message
    std::uint32_t sequence_number() const;
    void set_sequence_number(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const UnitHeader& other) const;
    bool operator!=(const UnitHeader& other) const;

  private:
    std::uint16_t length_{};
    std::uint8_t message_count_{};
    char market_data_group_{};
    std::uint32_t sequence_number_{};
};

std::ostream& operator<<(std::ostream& out, const UnitHeader& value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
