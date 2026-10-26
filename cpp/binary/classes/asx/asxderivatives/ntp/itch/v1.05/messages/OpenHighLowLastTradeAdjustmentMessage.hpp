#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// Market trade price adjustments are sent resulting from modifications of Open, High, Low,
// Last and volume statistics due to market operations, prior to the instrument moving to the
// next session within the trade date, or at the close of instrument
class OpenHighLowLastTradeAdjustmentMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OpenHighLowLastTradeAdjustmentMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 54;

    OpenHighLowLastTradeAdjustmentMessage() = default;
    OpenHighLowLastTradeAdjustmentMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Decimal opening_trade, Decimal highest_trade, Decimal lowest_trade, Decimal last_trade, std::uint32_t last_volume, std::uint64_t total_traded_volume);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Opening Trade: Opening Traded Price.
    Decimal opening_trade() const;
    void set_opening_trade(Decimal value);

    // Highest Trade: Highest Traded Price.
    Decimal highest_trade() const;
    void set_highest_trade(Decimal value);

    // Lowest Trade: Lowest Traded Price.
    Decimal lowest_trade() const;
    void set_lowest_trade(Decimal value);

    // Last Trade: Last Traded Price.
    Decimal last_trade() const;
    void set_last_trade(Decimal value);

    // Last Volume: Last Traded Volume.
    std::uint32_t last_volume() const;
    void set_last_volume(std::uint32_t value);

    // Total Traded Volume: Total Traded Volume.
    std::uint64_t total_traded_volume() const;
    void set_total_traded_volume(std::uint64_t value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const OpenHighLowLastTradeAdjustmentMessage& other) const;
    bool operator!=(const OpenHighLowLastTradeAdjustmentMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    Decimal opening_trade_{ 0, -2 };
    Decimal highest_trade_{ 0, -2 };
    Decimal lowest_trade_{ 0, -2 };
    Decimal last_trade_{ 0, -2 };
    std::uint32_t last_volume_{};
    std::uint64_t total_traded_volume_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
