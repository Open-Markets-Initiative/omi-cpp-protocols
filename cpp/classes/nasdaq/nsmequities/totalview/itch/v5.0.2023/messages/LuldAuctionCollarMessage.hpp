#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// Indicates the auction collar thresholds within which a paused security can reopen following
// a LULD trading pause
class LuldAuctionCollarMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::LuldAuctionCollarMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    LuldAuctionCollarMessage() = default;
    LuldAuctionCollarMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, Decimal auction_collar_reference_price, Decimal upper_auction_collar_price, Decimal lower_auction_collar_price, std::uint32_t auction_collar_extension);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Auction Collar Reference Price: Reference price used to set the auction collars
    Decimal auction_collar_reference_price() const;
    void set_auction_collar_reference_price(Decimal value);

    // Upper Auction Collar Price: Indicates the price of the upper auction collar threshold
    Decimal upper_auction_collar_price() const;
    void set_upper_auction_collar_price(Decimal value);

    // Lower Auction Collar Price: Indicates the price of the lower auction collar threshold
    Decimal lower_auction_collar_price() const;
    void set_lower_auction_collar_price(Decimal value);

    // Auction Collar Extension: Indicates the number of extensions to the Reopening Auction
    std::uint32_t auction_collar_extension() const;
    void set_auction_collar_extension(std::uint32_t value);

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

    bool operator==(const LuldAuctionCollarMessage& other) const;
    bool operator!=(const LuldAuctionCollarMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::string stock_{};
    Decimal auction_collar_reference_price_{ 0, -4 };
    Decimal upper_auction_collar_price_{ 0, -4 };
    Decimal lower_auction_collar_price_{ 0, -4 };
    std::uint32_t auction_collar_extension_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
