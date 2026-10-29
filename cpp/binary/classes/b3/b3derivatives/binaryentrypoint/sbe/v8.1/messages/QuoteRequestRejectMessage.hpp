#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/SettlTypeOptional.hpp"
#include "../messages/Message.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/SidesGroups.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// QuoteRequestRejectMessage
class QuoteRequestRejectMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::QuoteRequestRejectMessage;

    QuoteRequestRejectMessage() = default;
    QuoteRequestRejectMessage(const BidirectionalBusinessHeader& bidirectional_business_header, std::optional<std::uint32_t> quote_request_reject_reason, std::uint64_t security_id, std::uint64_t quote_req_id, std::optional<std::uint64_t> quote_id_optional, std::optional<std::uint32_t> trade_id_optional, std::uint32_t contra_broker, std::chrono::nanoseconds transact_time, const std::string& entering_trader, SettlTypeOptional settl_type_optional, std::optional<Decimal> price_8_optional, std::optional<std::uint64_t> order_qty_optional, const std::string& sender_location, const std::string& executing_trader, std::optional<Decimal> fixed_rate_percentage_8_optional, std::optional<std::uint16_t> days_to_settlement_optional, const SidesGroups& sides_groups, const DeskId& desk_id, const Memo& memo, const Text& text);

    // Bidirectional Business Header: BidirectionalBusinessHeader
    const BidirectionalBusinessHeader& bidirectional_business_header() const;
    BidirectionalBusinessHeader& bidirectional_business_header();
    void set_bidirectional_business_header(const BidirectionalBusinessHeader& value);

    // Quote Request Reject Reason: quoteRequestRejectReason
    std::optional<std::uint32_t> quote_request_reject_reason() const;
    void set_quote_request_reject_reason(std::optional<std::uint32_t> value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Quote Req Id: quoteReqID
    std::uint64_t quote_req_id() const;
    void set_quote_req_id(std::uint64_t value);

    // Quote Id Optional: quoteID
    std::optional<std::uint64_t> quote_id_optional() const;
    void set_quote_id_optional(std::optional<std::uint64_t> value);

    // Trade Id Optional: tradeID
    std::optional<std::uint32_t> trade_id_optional() const;
    void set_trade_id_optional(std::optional<std::uint32_t> value);

    // Contra Broker: contraBroker
    std::uint32_t contra_broker() const;
    void set_contra_broker(std::uint32_t value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

    // Settl Type Optional: settlType
    SettlTypeOptional settl_type_optional() const;
    void set_settl_type_optional(SettlTypeOptional value);

    // Price 8 Optional: price
    std::optional<Decimal> price_8_optional() const;
    void set_price_8_optional(std::optional<Decimal> value);

    // Order Qty Optional: orderQty
    std::optional<std::uint64_t> order_qty_optional() const;
    void set_order_qty_optional(std::optional<std::uint64_t> value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Executing Trader: executingTrader
    const std::string& executing_trader() const;
    std::string& executing_trader();
    void set_executing_trader(const std::string& value);

    // Fixed Rate Percentage 8 Optional: fixedRate
    std::optional<Decimal> fixed_rate_percentage_8_optional() const;
    void set_fixed_rate_percentage_8_optional(std::optional<Decimal> value);

    // Days To Settlement Optional: daysToSettlement
    std::optional<std::uint16_t> days_to_settlement_optional() const;
    void set_days_to_settlement_optional(std::optional<std::uint16_t> value);

    // Sides Groups: noSides Block
    const SidesGroups& sides_groups() const;
    SidesGroups& sides_groups();
    void set_sides_groups(const SidesGroups& value);

    // Desk Id: deskID data struct
    const DeskId& desk_id() const;
    DeskId& desk_id();
    void set_desk_id(const DeskId& value);

    // Memo: memo data struct
    const Memo& memo() const;
    Memo& memo();
    void set_memo(const Memo& value);

    // Text: text data struct
    const Text& text() const;
    Text& text();
    void set_text(const Text& value);

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

    bool operator==(const QuoteRequestRejectMessage& other) const;
    bool operator!=(const QuoteRequestRejectMessage& other) const;

  private:
    BidirectionalBusinessHeader bidirectional_business_header_{};
    std::optional<std::uint32_t> quote_request_reject_reason_{};
    std::uint64_t security_id_{};
    std::uint64_t quote_req_id_{};
    std::optional<std::uint64_t> quote_id_optional_{};
    std::optional<std::uint32_t> trade_id_optional_{};
    std::uint32_t contra_broker_{};
    std::chrono::nanoseconds transact_time_{};
    std::string entering_trader_{};
    SettlTypeOptional settl_type_optional_{};
    std::optional<Decimal> price_8_optional_{};
    std::optional<std::uint64_t> order_qty_optional_{};
    std::string sender_location_{};
    std::string executing_trader_{};
    std::optional<Decimal> fixed_rate_percentage_8_optional_{};
    std::optional<std::uint16_t> days_to_settlement_optional_{};
    SidesGroups sides_groups_{};
    DeskId desk_id_{};
    Memo memo_{};
    Text text_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
