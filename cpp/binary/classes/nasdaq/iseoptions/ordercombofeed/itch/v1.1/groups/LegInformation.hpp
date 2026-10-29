#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

#include "../common/Decimal.hpp"
#include "../enums/LegSide.hpp"
#include "../enums/OptionType.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Leg information
class LegInformation {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 28;

    LegInformation() = default;
    LegInformation(std::uint32_t option_id, const std::string& security_symbol, std::uint8_t leg_id, std::uint8_t expiration_year, std::uint8_t expiration_month, std::uint8_t expiration_day, Decimal explicit_strike_price, OptionType option_type, LegSide leg_side, std::uint32_t leg_ratio);

    // Option Id: ISE’s Option ID for this leg, valid for the trading day. The same ID as the
    // corresponding Option in the Options Directory Message. Zero (0) for Stock Leg.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Security Symbol: Denotes the option root symbol (security symbol)
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Leg Id: Leg identifier within this strategy. This is an exchange-assigned 0-based index.
    // E.g. Nth leg has LegId=N-1.
    std::uint8_t leg_id() const;
    void set_leg_id(std::uint8_t value);

    // Expiration Year: Last two digits of the year of the option expiration
    std::uint8_t expiration_year() const;
    void set_expiration_year(std::uint8_t value);

    // Expiration Month: Expiration Month of the option (1-12)
    std::uint8_t expiration_month() const;
    void set_expiration_month(std::uint8_t value);

    // Expiration Day: Day of the Month of expiration (1-31)
    std::uint8_t expiration_day() const;
    void set_expiration_day(std::uint8_t value);

    // Explicit Strike Price: Denotes the explicit strike price of the option. Refer to Data
    // Types for field processing notes.
    Decimal explicit_strike_price() const;
    void set_explicit_strike_price(Decimal value);

    // Option Type: Option Type:
    OptionType option_type() const;
    void set_option_type(OptionType value);

    // Leg Side: Indicates the side of the leg
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

    // Leg Ratio: Leg Ratio
    std::uint32_t leg_ratio() const;
    void set_leg_ratio(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const LegInformation& other) const;
    bool operator!=(const LegInformation& other) const;

  private:
    std::uint32_t option_id_{};
    std::string security_symbol_{};
    std::uint8_t leg_id_{};
    std::uint8_t expiration_year_{};
    std::uint8_t expiration_month_{};
    std::uint8_t expiration_day_{};
    Decimal explicit_strike_price_{ 0, -8 };
    OptionType option_type_{};
    LegSide leg_side_{};
    std::uint32_t leg_ratio_{};
};

std::ostream& operator<<(std::ostream& out, const LegInformation& value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
