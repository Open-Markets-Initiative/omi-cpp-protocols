#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/MarketCode.hpp"
#include "../enums/OperationalHaltAction.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class Visitor;

// The Exchange uses this message to indicate the current Operational Status of a security to
// the trading community.
class OperationalHaltMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OperationalHaltMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 18;

    OperationalHaltMessage() = default;
    OperationalHaltMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, const std::string& stock, MarketCode market_code, OperationalHaltAction operational_halt_action);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Time Stamp: Timestamp
    std::chrono::nanoseconds time_stamp() const;
    void set_time_stamp(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in the execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Market Code: Identifies the applicable Nasdaq market center
    MarketCode market_code() const;
    void set_market_code(MarketCode value);

    // Operational Halt Action: Denotes the operational halt action
    OperationalHaltAction operational_halt_action() const;
    void set_operational_halt_action(OperationalHaltAction value);

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

    bool operator==(const OperationalHaltMessage& other) const;
    bool operator!=(const OperationalHaltMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds time_stamp_{};
    std::string stock_{};
    MarketCode market_code_{};
    OperationalHaltAction operational_halt_action_{};
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
