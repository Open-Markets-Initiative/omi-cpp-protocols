#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Side.hpp"
#include "../enums/SingleCancelRestatementReason.hpp"
#include "../messages/Message.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// OrderCancelRequestMessage
class OrderCancelRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OrderCancelRequestMessage;

    OrderCancelRequestMessage() = default;
    OrderCancelRequestMessage(const InboundBusinessHeader& inbound_business_header, const std::array<std::byte, 2>& offset_18_padding_2, std::uint64_t clordid, std::uint64_t security_id, std::optional<std::uint64_t> order_id_optional, std::optional<std::uint64_t> origclordid, Side side, std::optional<SingleCancelRestatementReason> single_cancel_restatement_reason, const std::array<std::byte, 2>& offset_54_padding_2, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader_optional, const DeskId& desk_id, const Memo& memo);

    // Inbound Business Header: InboundBusinessHeader
    const InboundBusinessHeader& inbound_business_header() const;
    InboundBusinessHeader& inbound_business_header();
    void set_inbound_business_header(const InboundBusinessHeader& value);

    // Offset 18 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_18_padding_2() const;
    std::array<std::byte, 2>& offset_18_padding_2();
    void set_offset_18_padding_2(const std::array<std::byte, 2>& value);

    // ClOrdId: clOrdID
    std::uint64_t clordid() const;
    void set_clordid(std::uint64_t value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Order Id Optional: orderID
    std::optional<std::uint64_t> order_id_optional() const;
    void set_order_id_optional(std::optional<std::uint64_t> value);

    // OrigClOrdId: origClOrdID
    std::optional<std::uint64_t> origclordid() const;
    void set_origclordid(std::optional<std::uint64_t> value);

    // Side: side
    Side side() const;
    void set_side(Side value);

    // Single Cancel Restatement Reason: execRestatementReason
    std::optional<SingleCancelRestatementReason> single_cancel_restatement_reason() const;
    void set_single_cancel_restatement_reason(std::optional<SingleCancelRestatementReason> value);

    // Offset 54 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_54_padding_2() const;
    std::array<std::byte, 2>& offset_54_padding_2();
    void set_offset_54_padding_2(const std::array<std::byte, 2>& value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

    // Executing Trader Optional: executingTrader
    const std::string& executing_trader_optional() const;
    std::string& executing_trader_optional();
    void set_executing_trader_optional(const std::string& value);

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

    bool operator==(const OrderCancelRequestMessage& other) const;
    bool operator!=(const OrderCancelRequestMessage& other) const;

  private:
    InboundBusinessHeader inbound_business_header_{};
    std::array<std::byte, 2> offset_18_padding_2_{};
    std::uint64_t clordid_{};
    std::uint64_t security_id_{};
    std::optional<std::uint64_t> order_id_optional_{};
    std::optional<std::uint64_t> origclordid_{};
    Side side_{};
    std::optional<SingleCancelRestatementReason> single_cancel_restatement_reason_{};
    std::array<std::byte, 2> offset_54_padding_2_{};
    std::string sender_location_{};
    std::string entering_trader_{};
    std::string executing_trader_optional_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
