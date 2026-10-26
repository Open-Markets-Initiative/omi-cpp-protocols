#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/EquityAndIndexLastSaleMessageType.hpp"
#include "../messages/EquityAndIndexLastSaleMessagePayload.hpp"
#include "../messages/Message.hpp"

namespace siac::opra::output::obi::v6_2 {

class Visitor;
class EquityAndIndexLastSaleMessagePayloadVisitor;

// Equity And Index Last Sale Message
class EquityAndIndexLastSaleCategory : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::EquityAndIndexLastSale;

    EquityAndIndexLastSaleCategory() = default;
    EquityAndIndexLastSaleCategory(const EquityAndIndexLastSaleCategory& other);
    EquityAndIndexLastSaleCategory& operator=(const EquityAndIndexLastSaleCategory& other);
    EquityAndIndexLastSaleCategory(EquityAndIndexLastSaleCategory&& other) noexcept = default;
    EquityAndIndexLastSaleCategory& operator=(EquityAndIndexLastSaleCategory&& other) noexcept = default;
    ~EquityAndIndexLastSaleCategory() = default;

    // Equity And Index Last Sale Message Type: Message type
    EquityAndIndexLastSaleMessageType equity_and_index_last_sale_message_type() const;
    void set_equity_and_index_last_sale_message_type(EquityAndIndexLastSaleMessageType value);

    // Equity And Index Last Sale Message Payload: Branch
    const EquityAndIndexLastSaleMessagePayload* equity_and_index_last_sale_message_payload() const;
    EquityAndIndexLastSaleMessagePayload* equity_and_index_last_sale_message_payload();
    void set_equity_and_index_last_sale_message_payload(std::unique_ptr<EquityAndIndexLastSaleMessagePayload> value);

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

    bool operator==(const EquityAndIndexLastSaleCategory& other) const;
    bool operator!=(const EquityAndIndexLastSaleCategory& other) const;

  private:
    EquityAndIndexLastSaleMessageType equity_and_index_last_sale_message_type_{};
    std::unique_ptr<EquityAndIndexLastSaleMessagePayload> equity_and_index_last_sale_message_payload_{};
};

} // namespace siac::opra::output::obi::v6_2
