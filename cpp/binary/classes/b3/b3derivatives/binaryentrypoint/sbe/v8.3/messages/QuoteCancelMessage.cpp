#include "QuoteCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

QuoteCancelMessage::QuoteCancelMessage(const BidirectionalBusinessHeader& bidirectional_business_header, std::uint64_t security_id, std::optional<std::uint64_t> quote_req_id_optional, std::optional<std::uint64_t> quote_id_optional, std::optional<std::uint32_t> account, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader, const DeskId& desk_id, const Memo& memo)
  : bidirectional_business_header_(bidirectional_business_header), security_id_(security_id), quote_req_id_optional_(quote_req_id_optional), quote_id_optional_(quote_id_optional), account_(account), sender_location_(sender_location), entering_trader_(entering_trader), executing_trader_(executing_trader), desk_id_(desk_id), memo_(memo) {}

const BidirectionalBusinessHeader& QuoteCancelMessage::bidirectional_business_header() const { return bidirectional_business_header_; }
BidirectionalBusinessHeader& QuoteCancelMessage::bidirectional_business_header() { return bidirectional_business_header_; }
void QuoteCancelMessage::set_bidirectional_business_header(const BidirectionalBusinessHeader& value) { bidirectional_business_header_ = value; }

std::uint64_t QuoteCancelMessage::security_id() const { return security_id_; }
void QuoteCancelMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::optional<std::uint64_t> QuoteCancelMessage::quote_req_id_optional() const { return quote_req_id_optional_; }
void QuoteCancelMessage::set_quote_req_id_optional(std::optional<std::uint64_t> value) { quote_req_id_optional_ = value; }

std::optional<std::uint64_t> QuoteCancelMessage::quote_id_optional() const { return quote_id_optional_; }
void QuoteCancelMessage::set_quote_id_optional(std::optional<std::uint64_t> value) { quote_id_optional_ = value; }

std::optional<std::uint32_t> QuoteCancelMessage::account() const { return account_; }
void QuoteCancelMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

const std::string& QuoteCancelMessage::sender_location() const { return sender_location_; }
std::string& QuoteCancelMessage::sender_location() { return sender_location_; }
void QuoteCancelMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& QuoteCancelMessage::entering_trader() const { return entering_trader_; }
std::string& QuoteCancelMessage::entering_trader() { return entering_trader_; }
void QuoteCancelMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

const std::string& QuoteCancelMessage::executing_trader() const { return executing_trader_; }
std::string& QuoteCancelMessage::executing_trader() { return executing_trader_; }
void QuoteCancelMessage::set_executing_trader(const std::string& value) { executing_trader_ = value; }

const DeskId& QuoteCancelMessage::desk_id() const { return desk_id_; }
DeskId& QuoteCancelMessage::desk_id() { return desk_id_; }
void QuoteCancelMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& QuoteCancelMessage::memo() const { return memo_; }
Memo& QuoteCancelMessage::memo() { return memo_; }
void QuoteCancelMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode QuoteCancelMessage::type() const { return message_type; }

std::string_view QuoteCancelMessage::name() const { return "Quote Cancel Message"; }

std::size_t QuoteCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += bidirectional_business_header_.decode(data + offset, length - offset);

    wire::require("QuoteCancelMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteCancelMessage", offset + 8, length);
    quote_req_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("QuoteCancelMessage", offset + 8, length);
    quote_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("QuoteCancelMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("QuoteCancelMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("QuoteCancelMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("QuoteCancelMessage", offset + 5, length);
    executing_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t QuoteCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteCancelMessage", encoded_size(), capacity);

    offset += bidirectional_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, quote_req_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, quote_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_text(data + offset, 5, '\0', executing_trader_);
    offset += 5;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t QuoteCancelMessage::encoded_size() const {
    return bidirectional_business_header_.encoded_size() + 8 + 8 + 8 + 4 + 10 + 5 + 5 + desk_id_.encoded_size() + memo_.encoded_size();
}

void QuoteCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteCancelMessage::clone() const {
    return std::make_unique<QuoteCancelMessage>(*this);
}

void QuoteCancelMessage::print(std::ostream& out) const {
    out << "QuoteCancelMessage{";
    out << "bidirectional_business_header=";
    bidirectional_business_header_.print(out);
    out << ", security_id=";
    out << security_id_;
    out << ", quote_req_id_optional=";
    print::optional(out, quote_req_id_optional_);
    out << ", quote_id_optional=";
    print::optional(out, quote_id_optional_);
    out << ", account=";
    print::optional(out, account_);
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", executing_trader=";
    print::text(out, executing_trader_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool QuoteCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteCancelMessage::operator==(const QuoteCancelMessage& other) const {
    return bidirectional_business_header_ == other.bidirectional_business_header_
        && security_id_ == other.security_id_
        && quote_req_id_optional_ == other.quote_req_id_optional_
        && quote_id_optional_ == other.quote_id_optional_
        && account_ == other.account_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && executing_trader_ == other.executing_trader_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool QuoteCancelMessage::operator!=(const QuoteCancelMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
