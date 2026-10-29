#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/SecurityClass.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Adjusted Closing Price carrying an eight byte price.
class LongFormAdjustedClosingPriceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::LongFormAdjustedClosingPriceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    LongFormAdjustedClosingPriceMessage() = default;
    LongFormAdjustedClosingPriceMessage(const std::string& issue_symbol, SecurityClass security_class, Decimal adjusted_closing_price_long);

    // Issue Symbol: Denotes the Nasdaq-assigned issue symbol of the security for which the
    // trade report is being generated
    const std::string& issue_symbol() const;
    std::string& issue_symbol();
    void set_issue_symbol(const std::string& value);

    // Security Class: Indicates the primary listing market for the issue
    SecurityClass security_class() const;
    void set_security_class(SecurityClass value);

    // Adjusted Closing Price Long: Denotes the adjusted previous close price for the issue
    Decimal adjusted_closing_price_long() const;
    void set_adjusted_closing_price_long(Decimal value);

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

    bool operator==(const LongFormAdjustedClosingPriceMessage& other) const;
    bool operator!=(const LongFormAdjustedClosingPriceMessage& other) const;

  private:
    std::string issue_symbol_{};
    SecurityClass security_class_{};
    Decimal adjusted_closing_price_long_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
