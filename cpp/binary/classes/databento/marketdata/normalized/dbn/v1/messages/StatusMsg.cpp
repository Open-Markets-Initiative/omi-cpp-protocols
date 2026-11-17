// Databento.MarketData.Normalized.Dbn.v1: messages/StatusMsg.cpp
#include "StatusMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

StatusMsg::StatusMsg(std::optional<std::chrono::nanoseconds> ts_recv, StatusAction status_action, StatusReason status_reason, TradingEvent trading_event, IsTrading is_trading, IsQuoting is_quoting, IsShortSellRestricted is_short_sell_restricted, const std::array<std::byte, 7>& reserved_7)
  : ts_recv_(ts_recv), status_action_(status_action), status_reason_(status_reason), trading_event_(trading_event), is_trading_(is_trading), is_quoting_(is_quoting), is_short_sell_restricted_(is_short_sell_restricted), reserved_7_(reserved_7) {}

std::optional<std::chrono::nanoseconds> StatusMsg::ts_recv() const { return ts_recv_; }
void StatusMsg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

StatusAction StatusMsg::status_action() const { return status_action_; }
void StatusMsg::set_status_action(StatusAction value) { status_action_ = value; }

StatusReason StatusMsg::status_reason() const { return status_reason_; }
void StatusMsg::set_status_reason(StatusReason value) { status_reason_ = value; }

TradingEvent StatusMsg::trading_event() const { return trading_event_; }
void StatusMsg::set_trading_event(TradingEvent value) { trading_event_ = value; }

IsTrading StatusMsg::is_trading() const { return is_trading_; }
void StatusMsg::set_is_trading(IsTrading value) { is_trading_ = value; }

IsQuoting StatusMsg::is_quoting() const { return is_quoting_; }
void StatusMsg::set_is_quoting(IsQuoting value) { is_quoting_ = value; }

IsShortSellRestricted StatusMsg::is_short_sell_restricted() const { return is_short_sell_restricted_; }
void StatusMsg::set_is_short_sell_restricted(IsShortSellRestricted value) { is_short_sell_restricted_ = value; }

const std::array<std::byte, 7>& StatusMsg::reserved_7() const { return reserved_7_; }
std::array<std::byte, 7>& StatusMsg::reserved_7() { return reserved_7_; }
void StatusMsg::set_reserved_7(const std::array<std::byte, 7>& value) { reserved_7_ = value; }

MessageCode StatusMsg::type() const { return message_type; }

std::string_view StatusMsg::name() const { return "Status Msg"; }

std::size_t StatusMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StatusMsg", wire_size, length);

    ts_recv_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    status_action_ = static_cast<StatusAction>(wire::read_u16_le(data + offset));
    offset += 2;

    status_reason_ = static_cast<StatusReason>(wire::read_u16_le(data + offset));
    offset += 2;

    trading_event_ = static_cast<TradingEvent>(wire::read_u16_le(data + offset));
    offset += 2;

    is_trading_ = static_cast<IsTrading>(wire::read_char(data + offset));
    offset += 1;

    is_quoting_ = static_cast<IsQuoting>(wire::read_char(data + offset));
    offset += 1;

    is_short_sell_restricted_ = static_cast<IsShortSellRestricted>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t StatusMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StatusMsg", wire_size, capacity);

    wire::write_u64_le(data + offset, ts_recv_ ? static_cast<std::uint64_t>(ts_recv_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(status_action_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(status_reason_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trading_event_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(is_trading_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(is_quoting_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(is_short_sell_restricted_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t StatusMsg::encoded_size() const {
    return wire_size;
}

void StatusMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StatusMsg::clone() const {
    return std::make_unique<StatusMsg>(*this);
}

void StatusMsg::print(std::ostream& out) const {
    out << "StatusMsg{";
    out << "ts_recv=";
    print::optional_duration(out, ts_recv_);
    out << ", status_action=";
    out << status_action_;
    out << ", status_reason=";
    out << status_reason_;
    out << ", trading_event=";
    out << trading_event_;
    out << ", is_trading=";
    out << is_trading_;
    out << ", is_quoting=";
    out << is_quoting_;
    out << ", is_short_sell_restricted=";
    out << is_short_sell_restricted_;
    out << ", reserved_7=";
    print::hex(out, reserved_7_.data(), reserved_7_.size());
    out << '}';
}

bool StatusMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StatusMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool StatusMsg::operator==(const StatusMsg& other) const {
    return ts_recv_ == other.ts_recv_
        && status_action_ == other.status_action_
        && status_reason_ == other.status_reason_
        && trading_event_ == other.trading_event_
        && is_trading_ == other.is_trading_
        && is_quoting_ == other.is_quoting_
        && is_short_sell_restricted_ == other.is_short_sell_restricted_
        && reserved_7_ == other.reserved_7_;
}

bool StatusMsg::operator!=(const StatusMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v1
