#include "AllocationReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

AllocationReportMessage::AllocationReportMessage(const OutboundBusinessHeader& outbound_business_header, std::uint64_t alloc_id, std::uint64_t security_id, std::uint64_t alloc_report_id, AllocTransType alloc_trans_type, AllocReportType alloc_report_type, AllocNoOrdersType alloc_no_orders_type, std::optional<std::uint32_t> alloc_rej_code, std::uint64_t quantity, AllocStatus alloc_status, std::optional<std::uint16_t> trade_date_optional, std::chrono::nanoseconds transact_time, Side side, const std::string& sender_location, const std::string& entering_trader)
  : outbound_business_header_(outbound_business_header), alloc_id_(alloc_id), security_id_(security_id), alloc_report_id_(alloc_report_id), alloc_trans_type_(alloc_trans_type), alloc_report_type_(alloc_report_type), alloc_no_orders_type_(alloc_no_orders_type), alloc_rej_code_(alloc_rej_code), quantity_(quantity), alloc_status_(alloc_status), trade_date_optional_(trade_date_optional), transact_time_(transact_time), side_(side), sender_location_(sender_location), entering_trader_(entering_trader) {}

const OutboundBusinessHeader& AllocationReportMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& AllocationReportMessage::outbound_business_header() { return outbound_business_header_; }
void AllocationReportMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

std::uint64_t AllocationReportMessage::alloc_id() const { return alloc_id_; }
void AllocationReportMessage::set_alloc_id(std::uint64_t value) { alloc_id_ = value; }

std::uint64_t AllocationReportMessage::security_id() const { return security_id_; }
void AllocationReportMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t AllocationReportMessage::alloc_report_id() const { return alloc_report_id_; }
void AllocationReportMessage::set_alloc_report_id(std::uint64_t value) { alloc_report_id_ = value; }

AllocTransType AllocationReportMessage::alloc_trans_type() const { return alloc_trans_type_; }
void AllocationReportMessage::set_alloc_trans_type(AllocTransType value) { alloc_trans_type_ = value; }

AllocReportType AllocationReportMessage::alloc_report_type() const { return alloc_report_type_; }
void AllocationReportMessage::set_alloc_report_type(AllocReportType value) { alloc_report_type_ = value; }

AllocNoOrdersType AllocationReportMessage::alloc_no_orders_type() const { return alloc_no_orders_type_; }
void AllocationReportMessage::set_alloc_no_orders_type(AllocNoOrdersType value) { alloc_no_orders_type_ = value; }

std::optional<std::uint32_t> AllocationReportMessage::alloc_rej_code() const { return alloc_rej_code_; }
void AllocationReportMessage::set_alloc_rej_code(std::optional<std::uint32_t> value) { alloc_rej_code_ = value; }

std::uint64_t AllocationReportMessage::quantity() const { return quantity_; }
void AllocationReportMessage::set_quantity(std::uint64_t value) { quantity_ = value; }

AllocStatus AllocationReportMessage::alloc_status() const { return alloc_status_; }
void AllocationReportMessage::set_alloc_status(AllocStatus value) { alloc_status_ = value; }

std::optional<std::uint16_t> AllocationReportMessage::trade_date_optional() const { return trade_date_optional_; }
void AllocationReportMessage::set_trade_date_optional(std::optional<std::uint16_t> value) { trade_date_optional_ = value; }

std::chrono::nanoseconds AllocationReportMessage::transact_time() const { return transact_time_; }
void AllocationReportMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

Side AllocationReportMessage::side() const { return side_; }
void AllocationReportMessage::set_side(Side value) { side_ = value; }

const std::string& AllocationReportMessage::sender_location() const { return sender_location_; }
std::string& AllocationReportMessage::sender_location() { return sender_location_; }
void AllocationReportMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& AllocationReportMessage::entering_trader() const { return entering_trader_; }
std::string& AllocationReportMessage::entering_trader() { return entering_trader_; }
void AllocationReportMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

MessageCode AllocationReportMessage::type() const { return message_type; }

std::string_view AllocationReportMessage::name() const { return "Allocation Report Message"; }

std::size_t AllocationReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AllocationReportMessage", wire_size, length);

    offset += outbound_business_header_.decode(data + offset, length - offset);

    alloc_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    alloc_report_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    alloc_trans_type_ = static_cast<AllocTransType>(wire::read_char(data + offset));
    offset += 1;

    alloc_report_type_ = static_cast<AllocReportType>(wire::read_char(data + offset));
    offset += 1;

    alloc_no_orders_type_ = static_cast<AllocNoOrdersType>(wire::read_char(data + offset));
    offset += 1;

    alloc_rej_code_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    quantity_ = wire::read_u64_le(data + offset);
    offset += 8;

    alloc_status_ = static_cast<AllocStatus>(wire::read_char(data + offset));
    offset += 1;

    trade_date_optional_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    return offset;
}

std::size_t AllocationReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AllocationReportMessage", wire_size, capacity);

    offset += outbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(alloc_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(alloc_report_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(alloc_trans_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(alloc_report_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(alloc_no_orders_type_));
    offset += 1;

    wire::write_u32_le(data + offset, alloc_rej_code_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quantity_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(alloc_status_));
    offset += 1;

    wire::write_u16_le(data + offset, trade_date_optional_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    return offset;
}

std::size_t AllocationReportMessage::encoded_size() const {
    return wire_size;
}

void AllocationReportMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AllocationReportMessage::clone() const {
    return std::make_unique<AllocationReportMessage>(*this);
}

void AllocationReportMessage::print(std::ostream& out) const {
    out << "AllocationReportMessage{";
    out << "outbound_business_header=";
    outbound_business_header_.print(out);
    out << ", alloc_id=";
    out << alloc_id_;
    out << ", security_id=";
    out << security_id_;
    out << ", alloc_report_id=";
    out << alloc_report_id_;
    out << ", alloc_trans_type=";
    out << alloc_trans_type_;
    out << ", alloc_report_type=";
    out << alloc_report_type_;
    out << ", alloc_no_orders_type=";
    out << alloc_no_orders_type_;
    out << ", alloc_rej_code=";
    print::optional(out, alloc_rej_code_);
    out << ", quantity=";
    out << quantity_;
    out << ", alloc_status=";
    out << alloc_status_;
    out << ", trade_date_optional=";
    print::optional(out, trade_date_optional_);
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", side=";
    out << side_;
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << '}';
}

bool AllocationReportMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AllocationReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AllocationReportMessage::operator==(const AllocationReportMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && alloc_id_ == other.alloc_id_
        && security_id_ == other.security_id_
        && alloc_report_id_ == other.alloc_report_id_
        && alloc_trans_type_ == other.alloc_trans_type_
        && alloc_report_type_ == other.alloc_report_type_
        && alloc_no_orders_type_ == other.alloc_no_orders_type_
        && alloc_rej_code_ == other.alloc_rej_code_
        && quantity_ == other.quantity_
        && alloc_status_ == other.alloc_status_
        && trade_date_optional_ == other.trade_date_optional_
        && transact_time_ == other.transact_time_
        && side_ == other.side_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_;
}

bool AllocationReportMessage::operator!=(const AllocationReportMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
