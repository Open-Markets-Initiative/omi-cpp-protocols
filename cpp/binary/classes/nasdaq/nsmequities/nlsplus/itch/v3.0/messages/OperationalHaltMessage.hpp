#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/MarketCode.hpp"
#include "../enums/OperationalHaltAction.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Indicates the current operational status of a security to the trading community. An
// operational halt is specific to the market centre for which it is declared and does not
// interrupt trading of the instrument on any other market place.
class OperationalHaltMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OperationalHaltMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 10;

    OperationalHaltMessage() = default;
    OperationalHaltMessage(const std::string& stock, MarketCode market_code, OperationalHaltAction operational_halt_action);

    // Stock: Denotes the security symbol for the issue in the Nasdaq execution system
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Market Code: Denotes the market centre for which the operational halt is declared
    MarketCode market_code() const;
    void set_market_code(MarketCode value);

    // Operational Halt Action: Denotes whether the issue is operationally halted on the
    // identified market or has resumed trading
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
    std::string stock_{};
    MarketCode market_code_{};
    OperationalHaltAction operational_halt_action_{};
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
