#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AuctionOpeningType.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// Auction Summary messages are used to disseminate the results of an auction of a complex
// instrument. An Opening or Re-Opening Auction Summary message for each complex instrument is
// sent at the conclusion of its Opening or Re-Opening auction and represents Cboe opening
// price.
class AuctionSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    AuctionSummaryMessage() = default;
    AuctionSummaryMessage(std::chrono::nanoseconds time_offset, const std::string& complex_instrument_id_8, AuctionOpeningType auction_opening_type, Decimal price, std::uint32_t quantity);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Complex Instrument Id 8: Complex Instrument Id right padded with spaces.
    const std::string& complex_instrument_id_8() const;
    std::string& complex_instrument_id_8();
    void set_complex_instrument_id_8(const std::string& value);

    // Auction Opening Type: Auction Opening Type
    AuctionOpeningType auction_opening_type() const;
    void set_auction_opening_type(AuctionOpeningType value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

    // Quantity: Instrument quantity added to the complex book (may be less than the number
    // entered).
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

    bool operator==(const AuctionSummaryMessage& other) const;
    bool operator!=(const AuctionSummaryMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string complex_instrument_id_8_{};
    AuctionOpeningType auction_opening_type_{};
    Decimal price_{ 0, -4 };
    std::uint32_t quantity_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
