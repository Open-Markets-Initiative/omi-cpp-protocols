#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Mpv.hpp"
#include "../enums/OptionClosingType.hpp"
#include "../enums/OptionType.hpp"
#include "../enums/Tradable.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

class PacketMessageVisitor;

// At the start of each trading day, the options system disseminates directory messages for all
// symbols eligible for the auction process in the options system.
class PayloadOptionsDirectoryMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OptionsDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    PayloadOptionsDirectoryMessage() = default;
    PayloadOptionsDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, const std::string& security_symbol, std::uint8_t expiration_year, std::uint8_t expiration_month, std::uint8_t expiration_day, Decimal strike_price, OptionType option_type, std::uint8_t source, const std::string& underlying_symbol, OptionClosingType option_closing_type, Tradable tradable, Mpv mpv);

    // Nanoseconds: The sub-second portion of the time, in nanoseconds (0-999999999). The
    // second portion of the time is obtained from the most recent timestamp message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Option Id: Option ID for this option, assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Security Symbol: Denotes the option symbol (security symbol)
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Expiration Year: Last two digits of the year of the option expiration
    std::uint8_t expiration_year() const;
    void set_expiration_year(std::uint8_t value);

    // Expiration Month: Expiration Month of the option (1-12)
    std::uint8_t expiration_month() const;
    void set_expiration_month(std::uint8_t value);

    // Expiration Day: Day of the Month of expiration (1-31)
    std::uint8_t expiration_day() const;
    void set_expiration_day(std::uint8_t value);

    // Strike Price: Explicit strike price. Refer to Data Types for field processing notes.
    Decimal strike_price() const;
    void set_strike_price(Decimal value);

    // Option Type: Option Type value
    OptionType option_type() const;
    void set_option_type(OptionType value);

    // Source: Identifies the source of the option, valid for the trading day.
    std::uint8_t source() const;
    void set_source(std::uint8_t value);

    // Underlying Symbol: Denotes the unique symbol assigned to the underlying security within
    // the Exchange System.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Option Closing Type: Denotes which System Event is used to determine when trading ceases
    // in this symbol.
    OptionClosingType option_closing_type() const;
    void set_option_closing_type(OptionClosingType value);

    // Tradable: Denotes whether or not this option is tradable at the exchange:
    Tradable tradable() const;
    void set_tradable(Tradable value);

    // Mpv: Minimum Price Variation for this option
    Mpv mpv() const;
    void set_mpv(Mpv value);

    // PacketMessage
    PacketMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PacketMessageVisitor& visitor) const override;
    std::unique_ptr<PacketMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PacketMessage& other) const override;

    bool operator==(const PayloadOptionsDirectoryMessage& other) const;
    bool operator!=(const PayloadOptionsDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t option_id_{};
    std::string security_symbol_{};
    std::uint8_t expiration_year_{};
    std::uint8_t expiration_month_{};
    std::uint8_t expiration_day_{};
    Decimal strike_price_{ 0, -4 };
    OptionType option_type_{};
    std::uint8_t source_{};
    std::string underlying_symbol_{};
    OptionClosingType option_closing_type_{};
    Tradable tradable_{};
    Mpv mpv_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
