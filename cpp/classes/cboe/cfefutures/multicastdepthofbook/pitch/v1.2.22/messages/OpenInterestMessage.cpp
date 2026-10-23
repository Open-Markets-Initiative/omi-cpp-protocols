#include "OpenInterestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

OpenInterestMessage::OpenInterestMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint32_t trade_date, std::uint32_t open_interest)
  : time_offset_(time_offset), symbol_(symbol), trade_date_(trade_date), open_interest_(open_interest) {}

std::chrono::nanoseconds OpenInterestMessage::time_offset() const { return time_offset_; }
void OpenInterestMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& OpenInterestMessage::symbol() const { return symbol_; }
std::string& OpenInterestMessage::symbol() { return symbol_; }
void OpenInterestMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t OpenInterestMessage::trade_date() const { return trade_date_; }
void OpenInterestMessage::set_trade_date(std::uint32_t value) { trade_date_ = value; }

std::uint32_t OpenInterestMessage::open_interest() const { return open_interest_; }
void OpenInterestMessage::set_open_interest(std::uint32_t value) { open_interest_ = value; }

MessageCode OpenInterestMessage::type() const { return message_type; }

std::string_view OpenInterestMessage::name() const { return "Open Interest Message"; }

std::size_t OpenInterestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OpenInterestMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    trade_date_ = wire::read_u32_le(data + offset);
    offset += 4;

    open_interest_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t OpenInterestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OpenInterestMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_date_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(open_interest_));
    offset += 4;

    return offset;
}

std::size_t OpenInterestMessage::encoded_size() const {
    return wire_size;
}

void OpenInterestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OpenInterestMessage::clone() const {
    return std::make_unique<OpenInterestMessage>(*this);
}

void OpenInterestMessage::print(std::ostream& out) const {
    out << "OpenInterestMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", open_interest=";
    out << open_interest_;
    out << '}';
}

bool OpenInterestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OpenInterestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OpenInterestMessage::operator==(const OpenInterestMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_ == other.symbol_
        && trade_date_ == other.trade_date_
        && open_interest_ == other.open_interest_;
}

bool OpenInterestMessage::operator!=(const OpenInterestMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
