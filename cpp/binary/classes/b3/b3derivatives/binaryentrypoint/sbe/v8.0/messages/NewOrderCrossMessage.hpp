#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/CrossedIndicator.hpp"
#include "../messages/Message.hpp"
#include "../structs/CrossSidesGroups.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// NewOrderCrossMessage
class NewOrderCrossMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::NewOrderCrossMessage;

    NewOrderCrossMessage() = default;
    NewOrderCrossMessage(const InboundBusinessHeader& inbound_business_header, const std::array<std::byte, 2>& offset_18_padding_2, std::uint64_t crossid, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader_optional, std::uint64_t security_id, std::uint64_t order_qty, Decimal price, std::optional<CrossedIndicator> crossed_indicator, const CrossSidesGroups& cross_sides_groups, const DeskId& desk_id, const Memo& memo);

    // Inbound Business Header: InboundBusinessHeader
    const InboundBusinessHeader& inbound_business_header() const;
    InboundBusinessHeader& inbound_business_header();
    void set_inbound_business_header(const InboundBusinessHeader& value);

    // Offset 18 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_18_padding_2() const;
    std::array<std::byte, 2>& offset_18_padding_2();
    void set_offset_18_padding_2(const std::array<std::byte, 2>& value);

    // CrossId: crossID
    std::uint64_t crossid() const;
    void set_crossid(std::uint64_t value);

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

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Order Qty: orderQty
    std::uint64_t order_qty() const;
    void set_order_qty(std::uint64_t value);

    // Price: price
    Decimal price() const;
    void set_price(Decimal value);

    // Crossed Indicator: crossedIndicator
    std::optional<CrossedIndicator> crossed_indicator() const;
    void set_crossed_indicator(std::optional<CrossedIndicator> value);

    // Cross Sides Groups: noSides Block
    const CrossSidesGroups& cross_sides_groups() const;
    CrossSidesGroups& cross_sides_groups();
    void set_cross_sides_groups(const CrossSidesGroups& value);

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

    bool operator==(const NewOrderCrossMessage& other) const;
    bool operator!=(const NewOrderCrossMessage& other) const;

  private:
    InboundBusinessHeader inbound_business_header_{};
    std::array<std::byte, 2> offset_18_padding_2_{};
    std::uint64_t crossid_{};
    std::string sender_location_{};
    std::string entering_trader_{};
    std::string executing_trader_optional_{};
    std::uint64_t security_id_{};
    std::uint64_t order_qty_{};
    Decimal price_{ 0, -4 };
    std::optional<CrossedIndicator> crossed_indicator_{};
    CrossSidesGroups cross_sides_groups_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
