#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/ShortEquityAndIndexQuoteMessageType.hpp"
#include "../messages/Message.hpp"
#include "../messages/ShortEquityAndIndexQuoteMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class Visitor;
class ShortEquityAndIndexQuoteMessagePayloadVisitor;

// Short Equity And Index Quote Message
class ShortEquityAndIndexQuoteCategory : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::ShortEquityAndIndexQuote;

    ShortEquityAndIndexQuoteCategory() = default;
    ShortEquityAndIndexQuoteCategory(const ShortEquityAndIndexQuoteCategory& other);
    ShortEquityAndIndexQuoteCategory& operator=(const ShortEquityAndIndexQuoteCategory& other);
    ShortEquityAndIndexQuoteCategory(ShortEquityAndIndexQuoteCategory&& other) noexcept = default;
    ShortEquityAndIndexQuoteCategory& operator=(ShortEquityAndIndexQuoteCategory&& other) noexcept = default;
    ~ShortEquityAndIndexQuoteCategory() = default;

    // Short Equity And Index Quote Message Type: Short Equity and Index Quote Message Type
    ShortEquityAndIndexQuoteMessageType short_equity_and_index_quote_message_type() const;
    void set_short_equity_and_index_quote_message_type(ShortEquityAndIndexQuoteMessageType value);

    // Short Equity And Index Quote Message Payload: Branch
    const ShortEquityAndIndexQuoteMessagePayload* short_equity_and_index_quote_message_payload() const;
    ShortEquityAndIndexQuoteMessagePayload* short_equity_and_index_quote_message_payload();
    void set_short_equity_and_index_quote_message_payload(std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> value);

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

    bool operator==(const ShortEquityAndIndexQuoteCategory& other) const;
    bool operator!=(const ShortEquityAndIndexQuoteCategory& other) const;

  private:
    ShortEquityAndIndexQuoteMessageType short_equity_and_index_quote_message_type_{};
    std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> short_equity_and_index_quote_message_payload_{};
};

} // namespace siac::opra::output::obi::v6_2
