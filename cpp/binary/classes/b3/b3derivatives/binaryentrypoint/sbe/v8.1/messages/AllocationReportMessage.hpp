#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/AllocNoOrdersType.hpp"
#include "../enums/AllocReportType.hpp"
#include "../enums/AllocStatus.hpp"
#include "../enums/AllocTransType.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"
#include "../structs/OutboundBusinessHeader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// AllocationReportMessage
class AllocationReportMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AllocationReportMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 84;

    AllocationReportMessage() = default;
    AllocationReportMessage(const OutboundBusinessHeader& outbound_business_header, std::uint64_t alloc_id, std::uint64_t security_id, std::uint64_t alloc_report_id, AllocTransType alloc_trans_type, AllocReportType alloc_report_type, AllocNoOrdersType alloc_no_orders_type, std::optional<std::uint32_t> alloc_rej_code, std::uint64_t quantity, AllocStatus alloc_status, std::optional<std::uint16_t> trade_date_optional, std::chrono::nanoseconds transact_time, Side side, const std::string& sender_location, const std::string& entering_trader);

    // Outbound Business Header: OutboundBusinessHeader
    const OutboundBusinessHeader& outbound_business_header() const;
    OutboundBusinessHeader& outbound_business_header();
    void set_outbound_business_header(const OutboundBusinessHeader& value);

    // Alloc Id: allocID
    std::uint64_t alloc_id() const;
    void set_alloc_id(std::uint64_t value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Alloc Report Id: allocReportID
    std::uint64_t alloc_report_id() const;
    void set_alloc_report_id(std::uint64_t value);

    // Alloc Trans Type: allocTransType
    AllocTransType alloc_trans_type() const;
    void set_alloc_trans_type(AllocTransType value);

    // Alloc Report Type: allocReportType
    AllocReportType alloc_report_type() const;
    void set_alloc_report_type(AllocReportType value);

    // Alloc No Orders Type: allocNoOrdersType
    AllocNoOrdersType alloc_no_orders_type() const;
    void set_alloc_no_orders_type(AllocNoOrdersType value);

    // Alloc Rej Code: allocRejCode
    std::optional<std::uint32_t> alloc_rej_code() const;
    void set_alloc_rej_code(std::optional<std::uint32_t> value);

    // Quantity: quantity
    std::uint64_t quantity() const;
    void set_quantity(std::uint64_t value);

    // Alloc Status: allocStatus
    AllocStatus alloc_status() const;
    void set_alloc_status(AllocStatus value);

    // Trade Date Optional: tradeDate
    std::optional<std::uint16_t> trade_date_optional() const;
    void set_trade_date_optional(std::optional<std::uint16_t> value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Side: side
    Side side() const;
    void set_side(Side value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

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

    bool operator==(const AllocationReportMessage& other) const;
    bool operator!=(const AllocationReportMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    std::uint64_t alloc_id_{};
    std::uint64_t security_id_{};
    std::uint64_t alloc_report_id_{};
    AllocTransType alloc_trans_type_{};
    AllocReportType alloc_report_type_{};
    AllocNoOrdersType alloc_no_orders_type_{};
    std::optional<std::uint32_t> alloc_rej_code_{};
    std::uint64_t quantity_{};
    AllocStatus alloc_status_{};
    std::optional<std::uint16_t> trade_date_optional_{};
    std::chrono::nanoseconds transact_time_{};
    Side side_{};
    std::string sender_location_{};
    std::string entering_trader_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
