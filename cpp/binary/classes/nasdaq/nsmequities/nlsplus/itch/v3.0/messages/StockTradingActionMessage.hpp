#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/CurrentTradingState.hpp"
#include "../enums/SecurityClass.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Indicates the current trading status of a security to the trading community. Clients should
// initialize all securities as halted at the start of the session.
class StockTradingActionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StockTradingActionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 15;

    StockTradingActionMessage() = default;
    StockTradingActionMessage(char reserved, const std::string& issue_symbol, SecurityClass security_class, CurrentTradingState current_trading_state, const std::string& reason);

    // Reserved: Reserved for future use; space filled in the initial release
    char reserved() const;
    void set_reserved(char value);

    // Issue Symbol: Denotes the Nasdaq-assigned issue symbol of the security for which the
    // trade report is being generated
    const std::string& issue_symbol() const;
    std::string& issue_symbol();
    void set_issue_symbol(const std::string& value);

    // Security Class: Indicates the primary listing market for the issue
    SecurityClass security_class() const;
    void set_security_class(SecurityClass value);

    // Current Trading State: Reflects the current trading state for the issue
    CurrentTradingState current_trading_state() const;
    void set_current_trading_state(CurrentTradingState value);

    // Reason: Reflects the Market Ops or Market Watch code for the trading state change
    const std::string& reason() const;
    std::string& reason();
    void set_reason(const std::string& value);

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

    bool operator==(const StockTradingActionMessage& other) const;
    bool operator!=(const StockTradingActionMessage& other) const;

  private:
    char reserved_{};
    std::string issue_symbol_{};
    SecurityClass security_class_{};
    CurrentTradingState current_trading_state_{};
    std::string reason_{};
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
