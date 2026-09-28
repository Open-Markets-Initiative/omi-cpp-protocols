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
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class PacketMessageVisitor;

// An Operational Halt means that there has been an interruption of service on the identified
// security impacting only the designated Market Center
class PayloadOperationalHaltMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OperationalHaltMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    PayloadOperationalHaltMessage() = default;
    PayloadOperationalHaltMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, MarketCode market_code, OperationalHaltAction operational_halt_action);

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

    // Market Code: Market Code
    MarketCode market_code() const;
    void set_market_code(MarketCode value);

    // Operational Halt Action: Indicates the operational halt action for the security
    OperationalHaltAction operational_halt_action() const;
    void set_operational_halt_action(OperationalHaltAction value);

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

    bool operator==(const PayloadOperationalHaltMessage& other) const;
    bool operator!=(const PayloadOperationalHaltMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::string stock_{};
    MarketCode market_code_{};
    OperationalHaltAction operational_halt_action_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
