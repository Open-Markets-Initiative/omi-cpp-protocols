#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/InterestFlag.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

class Visitor;

// Indicates price improving interest of the Bid, Ask or both the Bid and Ask for a security.
class RetailInterestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RetailInterestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 19;

    RetailInterestMessage() = default;
    RetailInterestMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, InterestFlag interest_flag);

    // Stock Locate: Always 0
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq Texas internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Stock: Denotes the security symbol for the issue in the Nasdaq Texas execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Interest Flag: Indicates the type of price improvement available
    InterestFlag interest_flag() const;
    void set_interest_flag(InterestFlag value);

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

    bool operator==(const RetailInterestMessage& other) const;
    bool operator!=(const RetailInterestMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::string stock_{};
    InterestFlag interest_flag_{};
};

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
