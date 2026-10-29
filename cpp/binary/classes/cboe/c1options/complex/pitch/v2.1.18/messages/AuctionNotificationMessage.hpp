#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/CustomerIndicator.hpp"
#include "../enums/SideIndicator.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// Auction Notification messages are used to disseminate order details of a complex auction.
class AuctionNotificationMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionNotificationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 45;

    AuctionNotificationMessage() = default;
    AuctionNotificationMessage(std::chrono::nanoseconds time_offset, const std::string& complex_instrument_id, std::uint64_t auction_id, AuctionType auction_type, SideIndicator side_indicator, Decimal price, std::uint32_t quantity, CustomerIndicator customer_indicator, const std::string& participant_id, std::uint32_t auction_end_offset, const std::string& client_id);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Complex Instrument Id: Complex Instrument Id right padded with spaces.
    const std::string& complex_instrument_id() const;
    std::string& complex_instrument_id();
    void set_complex_instrument_id(const std::string& value);

    // Auction Id: Day specific identifier assigned to this auction.
    std::uint64_t auction_id() const;
    void set_auction_id(std::uint64_t value);

    // Auction Type: Auction Type
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Side Indicator: Order Side
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

    // Quantity: Instrument quantity added to the complex book (may be less than the number
    // entered).
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Customer Indicator: Customer Indicator
    CustomerIndicator customer_indicator() const;
    void set_customer_indicator(CustomerIndicator value);

    // Participant Id: Optionally specified. If specified the Executing Broker of firm
    // attributed to this quote.
    const std::string& participant_id() const;
    std::string& participant_id();
    void set_participant_id(const std::string& value);

    // Auction End Offset: Nanosecond offset from last timestamp.
    std::uint32_t auction_end_offset() const;
    void set_auction_end_offset(std::uint32_t value);

    // Client Id: Optional user specified value attributed to this quote. Space filled
    // otherwise.
    const std::string& client_id() const;
    std::string& client_id();
    void set_client_id(const std::string& value);

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

    bool operator==(const AuctionNotificationMessage& other) const;
    bool operator!=(const AuctionNotificationMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string complex_instrument_id_{};
    std::uint64_t auction_id_{};
    AuctionType auction_type_{};
    SideIndicator side_indicator_{};
    Decimal price_{ 0, -4 };
    std::uint32_t quantity_{};
    CustomerIndicator customer_indicator_{};
    std::string participant_id_{};
    std::uint32_t auction_end_offset_{};
    std::string client_id_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
