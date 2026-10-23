#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Future Leg
class FutureLeg {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 10;

    FutureLeg() = default;
    FutureLeg(std::int32_t leg_ratio, const std::string& leg_symbol);

    // Leg Ratio: Leg ratio (positive for buy, negative for sell).
    std::int32_t leg_ratio() const;
    void set_leg_ratio(std::int32_t value);

    // Leg Symbol: Symbol of leg.
    const std::string& leg_symbol() const;
    std::string& leg_symbol();
    void set_leg_symbol(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FutureLeg& other) const;
    bool operator!=(const FutureLeg& other) const;

  private:
    std::int32_t leg_ratio_{};
    std::string leg_symbol_{};
};

std::ostream& operator<<(std::ostream& out, const FutureLeg& value);

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
