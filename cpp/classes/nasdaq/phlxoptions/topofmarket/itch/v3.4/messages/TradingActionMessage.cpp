#include "TradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

TradingActionMessage::TradingActionMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, CurrentTradingState current_trading_state)
  : nanoseconds_(nanoseconds), option_id_(option_id), current_trading_state_(current_trading_state) {}

std::chrono::nanoseconds TradingActionMessage::nanoseconds() const { return nanoseconds_; }
void TradingActionMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t TradingActionMessage::option_id() const { return option_id_; }
void TradingActionMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

CurrentTradingState TradingActionMessage::current_trading_state() const { return current_trading_state_; }
void TradingActionMessage::set_current_trading_state(CurrentTradingState value) { current_trading_state_ = value; }

SequencedMessageCode TradingActionMessage::type() const { return message_type; }

std::string_view TradingActionMessage::name() const { return "Trading Action Message"; }

std::size_t TradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingActionMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    current_trading_state_ = static_cast<CurrentTradingState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingActionMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(current_trading_state_));
    offset += 1;

    return offset;
}

std::size_t TradingActionMessage::encoded_size() const {
    return wire_size;
}

void TradingActionMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> TradingActionMessage::clone() const {
    return std::make_unique<TradingActionMessage>(*this);
}

void TradingActionMessage::print(std::ostream& out) const {
    out << "TradingActionMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", current_trading_state=";
    out << current_trading_state_;
    out << '}';
}

bool TradingActionMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const TradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingActionMessage::operator==(const TradingActionMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && current_trading_state_ == other.current_trading_state_;
}

bool TradingActionMessage::operator!=(const TradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
