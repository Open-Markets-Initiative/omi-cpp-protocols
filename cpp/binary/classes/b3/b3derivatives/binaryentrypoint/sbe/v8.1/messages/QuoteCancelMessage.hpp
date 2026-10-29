#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// QuoteCancelMessage
class QuoteCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::QuoteCancelMessage;

    QuoteCancelMessage() = default;
    QuoteCancelMessage(const BidirectionalBusinessHeader& bidirectional_business_header, std::uint64_t security_id, std::optional<std::uint64_t> quote_req_id_optional, std::optional<std::uint64_t> quote_id_optional, std::optional<std::uint32_t> account, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader, const DeskId& desk_id, const Memo& memo);

    // Bidirectional Business Header: BidirectionalBusinessHeader
    const BidirectionalBusinessHeader& bidirectional_business_header() const;
    BidirectionalBusinessHeader& bidirectional_business_header();
    void set_bidirectional_business_header(const BidirectionalBusinessHeader& value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Quote Req Id Optional: quoteReqID
    std::optional<std::uint64_t> quote_req_id_optional() const;
    void set_quote_req_id_optional(std::optional<std::uint64_t> value);

    // Quote Id Optional: quoteID
    std::optional<std::uint64_t> quote_id_optional() const;
    void set_quote_id_optional(std::optional<std::uint64_t> value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

    // Executing Trader: executingTrader
    const std::string& executing_trader() const;
    std::string& executing_trader();
    void set_executing_trader(const std::string& value);

    // Desk Id: deskID data struct
    const DeskId& desk_id() const;
    DeskId& desk_id();
    void set_desk_id(const DeskId& value);

    // Memo: memo data struct
    const Memo& memo() const;
    Memo& memo();
    void set_memo(const Memo& value);

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

    bool operator==(const QuoteCancelMessage& other) const;
    bool operator!=(const QuoteCancelMessage& other) const;

  private:
    BidirectionalBusinessHeader bidirectional_business_header_{};
    std::uint64_t security_id_{};
    std::optional<std::uint64_t> quote_req_id_optional_{};
    std::optional<std::uint64_t> quote_id_optional_{};
    std::optional<std::uint32_t> account_{};
    std::string sender_location_{};
    std::string entering_trader_{};
    std::string executing_trader_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
