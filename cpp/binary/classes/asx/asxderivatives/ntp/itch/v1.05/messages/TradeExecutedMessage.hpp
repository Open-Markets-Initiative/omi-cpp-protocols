#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ParticipantIdBuyer.hpp"
#include "../enums/ParticipantIdSeller.hpp"
#include "../enums/TradeType.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// The Trade Message is designed to provide details for executions in combination order books.
// Trade Executed messages are reported in the same sequence as order execution messages are
// reported
class TradeExecutedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 45;

    TradeExecutedMessage() = default;
    TradeExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, TradeType trade_type, std::uint64_t trade_id, std::uint32_t executed_quantity, Decimal trade_price, std::uint64_t combination_trade_id, const std::string& participant_id_buyer, const std::string& participant_id_seller);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Trade Type: Nature of the match
    TradeType trade_type() const;
    void set_trade_type(TradeType value);

    // Trade Id: Public trade id of the trade.
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

    // Executed Quantity: Volume traded.
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Trade Price: Price of trade (may be negative for combination trades).
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Combination Trade Id: A non-zero value indicates that this trade is part of an execution
    // cycle for a combination trade.
    std::uint64_t combination_trade_id() const;
    void set_combination_trade_id(std::uint64_t value);

    // Participant Id Buyer: Participant identifier of the owner of the buying order. Blank for
    // anonymous instruments.
    const std::string& participant_id_buyer() const;
    std::string& participant_id_buyer();
    void set_participant_id_buyer(const std::string& value);

    // Participant Id Seller: Participant identifier of the owner of the selling order. Blank
    // for anonymous instruments.
    const std::string& participant_id_seller() const;
    std::string& participant_id_seller();
    void set_participant_id_seller(const std::string& value);

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

    bool operator==(const TradeExecutedMessage& other) const;
    bool operator!=(const TradeExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    TradeType trade_type_{};
    std::uint64_t trade_id_{};
    std::uint32_t executed_quantity_{};
    Decimal trade_price_{ 0, -2 };
    std::uint64_t combination_trade_id_{};
    std::string participant_id_buyer_{};
    std::string participant_id_seller_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
