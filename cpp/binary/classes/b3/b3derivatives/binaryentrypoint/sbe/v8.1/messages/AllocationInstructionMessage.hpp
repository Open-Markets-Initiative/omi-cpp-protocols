#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/AllocNoOrdersType.hpp"
#include "../enums/AllocTransType.hpp"
#include "../enums/AllocType.hpp"
#include "../messages/Message.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// AllocationInstructionMessage
class AllocationInstructionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AllocationInstructionMessage;

    AllocationInstructionMessage() = default;
    AllocationInstructionMessage(const InboundBusinessHeader& inbound_business_header, std::uint64_t alloc_id, std::uint64_t security_id, AllocTransType alloc_trans_type, AllocType alloc_type, AllocNoOrdersType alloc_no_orders_type, std::uint64_t quantity, const std::string& sender_location, const std::string& entering_trader, std::uint32_t trade_id, std::optional<std::uint16_t> trade_date_optional, std::uint64_t individual_alloc_id, std::uint32_t alloc_account, std::uint64_t alloc_qty, const DeskId& desk_id, const Memo& memo);

    // Inbound Business Header: InboundBusinessHeader
    const InboundBusinessHeader& inbound_business_header() const;
    InboundBusinessHeader& inbound_business_header();
    void set_inbound_business_header(const InboundBusinessHeader& value);

    // Alloc Id: allocID
    std::uint64_t alloc_id() const;
    void set_alloc_id(std::uint64_t value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Alloc Trans Type: allocTransType
    AllocTransType alloc_trans_type() const;
    void set_alloc_trans_type(AllocTransType value);

    // Alloc Type: allocType
    AllocType alloc_type() const;
    void set_alloc_type(AllocType value);

    // Alloc No Orders Type: allocNoOrdersType
    AllocNoOrdersType alloc_no_orders_type() const;
    void set_alloc_no_orders_type(AllocNoOrdersType value);

    // Quantity: quantity
    std::uint64_t quantity() const;
    void set_quantity(std::uint64_t value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

    // Trade Id: tradeID
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Trade Date Optional: tradeDate
    std::optional<std::uint16_t> trade_date_optional() const;
    void set_trade_date_optional(std::optional<std::uint16_t> value);

    // Individual Alloc Id: individualAllocID
    std::uint64_t individual_alloc_id() const;
    void set_individual_alloc_id(std::uint64_t value);

    // Alloc Account: allocAccount
    std::uint32_t alloc_account() const;
    void set_alloc_account(std::uint32_t value);

    // Alloc Qty: allocQty
    std::uint64_t alloc_qty() const;
    void set_alloc_qty(std::uint64_t value);

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

    bool operator==(const AllocationInstructionMessage& other) const;
    bool operator!=(const AllocationInstructionMessage& other) const;

  private:
    InboundBusinessHeader inbound_business_header_{};
    std::uint64_t alloc_id_{};
    std::uint64_t security_id_{};
    AllocTransType alloc_trans_type_{};
    AllocType alloc_type_{};
    AllocNoOrdersType alloc_no_orders_type_{};
    std::uint64_t quantity_{};
    std::string sender_location_{};
    std::string entering_trader_{};
    std::uint32_t trade_id_{};
    std::optional<std::uint16_t> trade_date_optional_{};
    std::uint64_t individual_alloc_id_{};
    std::uint32_t alloc_account_{};
    std::uint64_t alloc_qty_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
