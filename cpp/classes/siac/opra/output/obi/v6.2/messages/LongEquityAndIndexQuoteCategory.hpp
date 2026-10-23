#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/LongEquityAndIndexQuoteMessageType.hpp"
#include "../messages/LongEquityAndIndexQuoteMessagePayload.hpp"
#include "../messages/Message.hpp"

namespace siac::opra::output::obi::v6_2 {

class Visitor;
class LongEquityAndIndexQuoteMessagePayloadVisitor;

// Long Equity And Index Quote Message
class LongEquityAndIndexQuoteCategory : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::LongEquityAndIndexQuote;

    LongEquityAndIndexQuoteCategory() = default;
    LongEquityAndIndexQuoteCategory(const LongEquityAndIndexQuoteCategory& other);
    LongEquityAndIndexQuoteCategory& operator=(const LongEquityAndIndexQuoteCategory& other);
    LongEquityAndIndexQuoteCategory(LongEquityAndIndexQuoteCategory&& other) noexcept = default;
    LongEquityAndIndexQuoteCategory& operator=(LongEquityAndIndexQuoteCategory&& other) noexcept = default;
    ~LongEquityAndIndexQuoteCategory() = default;

    // Long Equity And Index Quote Message Type: Long Equity and Index Quote Message Type
    LongEquityAndIndexQuoteMessageType long_equity_and_index_quote_message_type() const;
    void set_long_equity_and_index_quote_message_type(LongEquityAndIndexQuoteMessageType value);

    // Long Equity And Index Quote Message Payload: Branch
    const LongEquityAndIndexQuoteMessagePayload* long_equity_and_index_quote_message_payload() const;
    LongEquityAndIndexQuoteMessagePayload* long_equity_and_index_quote_message_payload();
    void set_long_equity_and_index_quote_message_payload(std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> value);

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

    bool operator==(const LongEquityAndIndexQuoteCategory& other) const;
    bool operator!=(const LongEquityAndIndexQuoteCategory& other) const;

  private:
    LongEquityAndIndexQuoteMessageType long_equity_and_index_quote_message_type_{};
    std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> long_equity_and_index_quote_message_payload_{};
};

} // namespace siac::opra::output::obi::v6_2
