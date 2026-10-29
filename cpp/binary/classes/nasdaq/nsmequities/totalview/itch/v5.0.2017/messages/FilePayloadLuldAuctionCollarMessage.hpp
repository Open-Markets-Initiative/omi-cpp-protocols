#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../messages/FileMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

class FileMessageVisitor;

// Indicates the auction collar thresholds within which a paused security can reopen following
// a LULD Trading Pause
class FilePayloadLuldAuctionCollarMessage : public FileMessage {
  public:
    // The code that selects this message
    static constexpr FileMessageCode message_type = MessageType::LuldAuctionCollarMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    FilePayloadLuldAuctionCollarMessage() = default;
    FilePayloadLuldAuctionCollarMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, Decimal auction_collar_reference_price, Decimal upper_auction_collar_price, Decimal lower_auction_collar_price, std::uint32_t auction_collar_extension);

    // Stock Locate: Always 0
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: NASDAQ OMX internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Auction Collar Reference Price: Reference price used to set the Auction Collars
    Decimal auction_collar_reference_price() const;
    void set_auction_collar_reference_price(Decimal value);

    // Upper Auction Collar Price: Indicates the price of the Upper Auction Collar Threshold
    Decimal upper_auction_collar_price() const;
    void set_upper_auction_collar_price(Decimal value);

    // Lower Auction Collar Price: Indicates the price of the Lower Auction Collar Threshold
    Decimal lower_auction_collar_price() const;
    void set_lower_auction_collar_price(Decimal value);

    // Auction Collar Extension: Indicates the number of the extensions to the Reopening
    // Auction
    std::uint32_t auction_collar_extension() const;
    void set_auction_collar_extension(std::uint32_t value);

    // FileMessage
    FileMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(FileMessageVisitor& visitor) const override;
    std::unique_ptr<FileMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const FileMessage& other) const override;

    bool operator==(const FilePayloadLuldAuctionCollarMessage& other) const;
    bool operator!=(const FilePayloadLuldAuctionCollarMessage& other) const;

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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
