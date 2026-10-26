#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/RfqSide.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message is disseminated for anonymous Request for Quotes (RFQs) from the market
class RequestForQuoteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RequestForQuoteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 15;

    RequestForQuoteMessage() = default;
    RequestForQuoteMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, RfqSide rfq_side, std::uint32_t quantity);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Rfq Side: Identifies side of the RFQ
    RfqSide rfq_side() const;
    void set_rfq_side(RfqSide value);

    // Quantity: Number of lots added to the book (all volume is visible).
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

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

    bool operator==(const RequestForQuoteMessage& other) const;
    bool operator!=(const RequestForQuoteMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    RfqSide rfq_side_{};
    std::uint32_t quantity_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
