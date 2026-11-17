// B3.B3Derivatives.BinaryUmdf.Sbe.v2.1: bitfields/MatchEventIndicator.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// MatchEventIndicator bit set
class MatchEventIndicator {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    MatchEventIndicator() = default;
    explicit MatchEventIndicator(std::uint8_t raw);

    // Implied: Implied
    bool implied() const;
    void set_implied(bool value);

    // Recovery Msg: RecoveryMsg
    bool recovery_msg() const;
    void set_recovery_msg(bool value);

    // End Of Event: EndOfEvent
    bool end_of_event() const;
    void set_end_of_event(bool value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MatchEventIndicator& other) const;
    bool operator!=(const MatchEventIndicator& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const MatchEventIndicator& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
