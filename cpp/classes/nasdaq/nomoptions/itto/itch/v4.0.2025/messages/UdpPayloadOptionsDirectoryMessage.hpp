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
#include "../enums/OptionType.hpp"
#include "../enums/OptionsClosingType.hpp"
#include "../enums/Tradable.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// At the start of each trading day, NASDAQ disseminates options symbol directory messages for
// all active options symbols in the NASDAQ option system.
class UdpPayloadOptionsDirectoryMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OptionsDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 43;

    UdpPayloadOptionsDirectoryMessage() = default;
    UdpPayloadOptionsDirectoryMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t option_id, const std::string& security_symbol, std::uint8_t expiration_year, std::uint8_t expiration_month, std::uint8_t expiration_date, Decimal explicit_strike_price, OptionType option_type, std::uint8_t source, const std::string& underlying_symbol, OptionsClosingType options_closing_type, Tradable tradable, Mpv mpv);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Security Symbol: Denotes the security symbol.
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Expiration Year: Last two digits of the year of the option expiration
    std::uint8_t expiration_year() const;
    void set_expiration_year(std::uint8_t value);

    // Expiration Month: Expiration Month (1-12)
    std::uint8_t expiration_month() const;
    void set_expiration_month(std::uint8_t value);

    // Expiration Date: Day of the Month of expiration (1-31)
    std::uint8_t expiration_date() const;
    void set_expiration_date(std::uint8_t value);

    // Explicit Strike Price: Explicit strike price. Refer to Data Types for field processing
    // notes.
    Decimal explicit_strike_price() const;
    void set_explicit_strike_price(Decimal value);

    // Option Type:
    OptionType option_type() const;
    void set_option_type(OptionType value);

    // Source: Identifies the source of the Option, valid for the trading day
    std::uint8_t source() const;
    void set_source(std::uint8_t value);

    // Underlying Symbol: Denotes the unique symbol assigned to the underlying security within
    // exchange.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Options Closing Type: Denotes which System Event is used to trigger the option closing
    // process.
    OptionsClosingType options_closing_type() const;
    void set_options_closing_type(OptionsClosingType value);

    // Tradable: Denotes whether or not this option is tradable at the exchange. The allowable
    // values are:
    Tradable tradable() const;
    void set_tradable(Tradable value);

    // Mpv: Minimum Price Variation for this option. See Notes below for further explanation:
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

    bool operator==(const UdpPayloadOptionsDirectoryMessage& other) const;
    bool operator!=(const UdpPayloadOptionsDirectoryMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t option_id_{};
    std::string security_symbol_{};
    std::uint8_t expiration_year_{};
    std::uint8_t expiration_month_{};
    std::uint8_t expiration_date_{};
    Decimal explicit_strike_price_{ 0, -4 };
    OptionType option_type_{};
    std::uint8_t source_{};
    std::string underlying_symbol_{};
    OptionsClosingType options_closing_type_{};
    Tradable tradable_{};
    Mpv mpv_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
