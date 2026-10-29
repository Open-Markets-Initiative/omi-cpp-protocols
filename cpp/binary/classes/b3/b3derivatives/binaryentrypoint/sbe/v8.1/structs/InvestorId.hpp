#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// SimpleNewOrderMessage
class InvestorId {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    InvestorId() = default;
    InvestorId(std::uint16_t prefix, const std::array<std::byte, 2>& offset_2_padding_2, std::uint32_t document);

    // Prefix: prefix
    std::uint16_t prefix() const;
    void set_prefix(std::uint16_t value);

    // Offset 2 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_2_padding_2() const;
    std::array<std::byte, 2>& offset_2_padding_2();
    void set_offset_2_padding_2(const std::array<std::byte, 2>& value);

    // Document: document
    std::uint32_t document() const;
    void set_document(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InvestorId& other) const;
    bool operator!=(const InvestorId& other) const;

  private:
    std::uint16_t prefix_{};
    std::array<std::byte, 2> offset_2_padding_2_{};
    std::uint32_t document_{};
};

std::ostream& operator<<(std::ostream& out, const InvestorId& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
