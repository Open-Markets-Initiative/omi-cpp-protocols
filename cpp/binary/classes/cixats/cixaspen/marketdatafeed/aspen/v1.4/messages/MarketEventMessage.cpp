#include "MarketEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

MarketEventMessage::MarketEventMessage(const std::string& reserved_2, std::chrono::nanoseconds timestamp, Event event)
  : reserved_2_(reserved_2), timestamp_(timestamp), event_(event) {}

const std::string& MarketEventMessage::reserved_2() const { return reserved_2_; }
std::string& MarketEventMessage::reserved_2() { return reserved_2_; }
void MarketEventMessage::set_reserved_2(const std::string& value) { reserved_2_ = value; }

std::chrono::nanoseconds MarketEventMessage::timestamp() const { return timestamp_; }
void MarketEventMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

Event MarketEventMessage::event() const { return event_; }
void MarketEventMessage::set_event(Event value) { event_ = value; }

MessageCode MarketEventMessage::type() const { return message_type; }

std::string_view MarketEventMessage::name() const { return "Market Event Message"; }

std::size_t MarketEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MarketEventMessage", wire_size, length);

    reserved_2_ = wire::read_text(data + offset, 2, ' ');
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    event_ = static_cast<Event>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MarketEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketEventMessage", wire_size, capacity);

    wire::write_text(data + offset, 2, ' ', reserved_2_);
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(event_));
    offset += 1;

    return offset;
}

std::size_t MarketEventMessage::encoded_size() const {
    return wire_size;
}

void MarketEventMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MarketEventMessage::clone() const {
    return std::make_unique<MarketEventMessage>(*this);
}

void MarketEventMessage::print(std::ostream& out) const {
    out << "MarketEventMessage{";
    out << "reserved_2=";
    print::text(out, reserved_2_);
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", event=";
    out << event_;
    out << '}';
}

bool MarketEventMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MarketEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketEventMessage::operator==(const MarketEventMessage& other) const {
    return reserved_2_ == other.reserved_2_
        && timestamp_ == other.timestamp_
        && event_ == other.event_;
}

bool MarketEventMessage::operator!=(const MarketEventMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
