#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/EquityAndIndexEndOfDaySummaryMessageType.hpp"
#include "../messages/EquityAndIndexEndOfDaySummaryMessagePayload.hpp"
#include "../messages/Message.hpp"

namespace siac::opra::output::obi::v6_2 {

class Visitor;
class EquityAndIndexEndOfDaySummaryMessagePayloadVisitor;

// Equity And Index End Of Day Summary Message
class EquityAndIndexEndOfDaySummaryCategory : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::EquityAndIndexEndOfDaySummary;

    EquityAndIndexEndOfDaySummaryCategory() = default;
    EquityAndIndexEndOfDaySummaryCategory(const EquityAndIndexEndOfDaySummaryCategory& other);
    EquityAndIndexEndOfDaySummaryCategory& operator=(const EquityAndIndexEndOfDaySummaryCategory& other);
    EquityAndIndexEndOfDaySummaryCategory(EquityAndIndexEndOfDaySummaryCategory&& other) noexcept = default;
    EquityAndIndexEndOfDaySummaryCategory& operator=(EquityAndIndexEndOfDaySummaryCategory&& other) noexcept = default;
    ~EquityAndIndexEndOfDaySummaryCategory() = default;

    // Equity And Index End Of Day Summary Message Type: Equity and Index End of Day Summary
    // Message Type
    EquityAndIndexEndOfDaySummaryMessageType equity_and_index_end_of_day_summary_message_type() const;
    void set_equity_and_index_end_of_day_summary_message_type(EquityAndIndexEndOfDaySummaryMessageType value);

    // Equity And Index End Of Day Summary Message Payload: Branch
    const EquityAndIndexEndOfDaySummaryMessagePayload* equity_and_index_end_of_day_summary_message_payload() const;
    EquityAndIndexEndOfDaySummaryMessagePayload* equity_and_index_end_of_day_summary_message_payload();
    void set_equity_and_index_end_of_day_summary_message_payload(std::unique_ptr<EquityAndIndexEndOfDaySummaryMessagePayload> value);

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

    bool operator==(const EquityAndIndexEndOfDaySummaryCategory& other) const;
    bool operator!=(const EquityAndIndexEndOfDaySummaryCategory& other) const;

  private:
    EquityAndIndexEndOfDaySummaryMessageType equity_and_index_end_of_day_summary_message_type_{};
    std::unique_ptr<EquityAndIndexEndOfDaySummaryMessagePayload> equity_and_index_end_of_day_summary_message_payload_{};
};

} // namespace siac::opra::output::obi::v6_2
