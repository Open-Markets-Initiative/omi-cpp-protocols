#include "SecurityStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

SecurityStatusMessage::SecurityStatusMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, SecurityStatus security_status, HaltCondition halt_condition, const std::array<std::byte, 4>& reserved_4, std::uint32_t price_1, std::uint32_t price_2, SsrTriggeringExchangeId ssr_triggering_exchange_id, std::uint32_t ssr_triggering_volume, std::optional<std::uint32_t> time, char ssr_state, char market_state, char session_state)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), security_status_(security_status), halt_condition_(halt_condition), reserved_4_(reserved_4), price_1_(price_1), price_2_(price_2), ssr_triggering_exchange_id_(ssr_triggering_exchange_id), ssr_triggering_volume_(ssr_triggering_volume), time_(time), ssr_state_(ssr_state), market_state_(market_state), session_state_(session_state) {}

std::uint32_t SecurityStatusMessage::source_time() const { return source_time_; }
void SecurityStatusMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t SecurityStatusMessage::source_time_ns() const { return source_time_ns_; }
void SecurityStatusMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t SecurityStatusMessage::symbol_index() const { return symbol_index_; }
void SecurityStatusMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t SecurityStatusMessage::symbol_seq_num() const { return symbol_seq_num_; }
void SecurityStatusMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

SecurityStatus SecurityStatusMessage::security_status() const { return security_status_; }
void SecurityStatusMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

HaltCondition SecurityStatusMessage::halt_condition() const { return halt_condition_; }
void SecurityStatusMessage::set_halt_condition(HaltCondition value) { halt_condition_ = value; }

const std::array<std::byte, 4>& SecurityStatusMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& SecurityStatusMessage::reserved_4() { return reserved_4_; }
void SecurityStatusMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

std::uint32_t SecurityStatusMessage::price_1() const { return price_1_; }
void SecurityStatusMessage::set_price_1(std::uint32_t value) { price_1_ = value; }

std::uint32_t SecurityStatusMessage::price_2() const { return price_2_; }
void SecurityStatusMessage::set_price_2(std::uint32_t value) { price_2_ = value; }

SsrTriggeringExchangeId SecurityStatusMessage::ssr_triggering_exchange_id() const { return ssr_triggering_exchange_id_; }
void SecurityStatusMessage::set_ssr_triggering_exchange_id(SsrTriggeringExchangeId value) { ssr_triggering_exchange_id_ = value; }

std::uint32_t SecurityStatusMessage::ssr_triggering_volume() const { return ssr_triggering_volume_; }
void SecurityStatusMessage::set_ssr_triggering_volume(std::uint32_t value) { ssr_triggering_volume_ = value; }

std::optional<std::uint32_t> SecurityStatusMessage::time() const { return time_; }
void SecurityStatusMessage::set_time(std::optional<std::uint32_t> value) { time_ = value; }

char SecurityStatusMessage::ssr_state() const { return ssr_state_; }
void SecurityStatusMessage::set_ssr_state(char value) { ssr_state_ = value; }

char SecurityStatusMessage::market_state() const { return market_state_; }
void SecurityStatusMessage::set_market_state(char value) { market_state_ = value; }

char SecurityStatusMessage::session_state() const { return session_state_; }
void SecurityStatusMessage::set_session_state(char value) { session_state_ = value; }

MessageCode SecurityStatusMessage::type() const { return message_type; }

std::string_view SecurityStatusMessage::name() const { return "Security Status Message"; }

std::size_t SecurityStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityStatusMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    security_status_ = static_cast<SecurityStatus>(wire::read_char(data + offset));
    offset += 1;

    halt_condition_ = static_cast<HaltCondition>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    price_1_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_2_ = wire::read_u32_le(data + offset);
    offset += 4;

    ssr_triggering_exchange_id_ = static_cast<SsrTriggeringExchangeId>(wire::read_char(data + offset));
    offset += 1;

    ssr_triggering_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    time_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    ssr_state_ = wire::read_char(data + offset);
    offset += 1;

    market_state_ = wire::read_char(data + offset);
    offset += 1;

    session_state_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t SecurityStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(security_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(halt_condition_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(price_1_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(price_2_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(ssr_triggering_exchange_id_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ssr_triggering_volume_));
    offset += 4;

    wire::write_u32_le(data + offset, time_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_char(data + offset, ssr_state_);
    offset += 1;

    wire::write_char(data + offset, market_state_);
    offset += 1;

    wire::write_char(data + offset, session_state_);
    offset += 1;

    return offset;
}

std::size_t SecurityStatusMessage::encoded_size() const {
    return wire_size;
}

void SecurityStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityStatusMessage::clone() const {
    return std::make_unique<SecurityStatusMessage>(*this);
}

void SecurityStatusMessage::print(std::ostream& out) const {
    out << "SecurityStatusMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", security_status=";
    out << security_status_;
    out << ", halt_condition=";
    out << halt_condition_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", price_1=";
    out << price_1_;
    out << ", price_2=";
    out << price_2_;
    out << ", ssr_triggering_exchange_id=";
    out << ssr_triggering_exchange_id_;
    out << ", ssr_triggering_volume=";
    out << ssr_triggering_volume_;
    out << ", time=";
    print::optional(out, time_);
    out << ", ssr_state=";
    print::character(out, ssr_state_);
    out << ", market_state=";
    print::character(out, market_state_);
    out << ", session_state=";
    print::character(out, session_state_);
    out << '}';
}

bool SecurityStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityStatusMessage::operator==(const SecurityStatusMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && security_status_ == other.security_status_
        && halt_condition_ == other.halt_condition_
        && reserved_4_ == other.reserved_4_
        && price_1_ == other.price_1_
        && price_2_ == other.price_2_
        && ssr_triggering_exchange_id_ == other.ssr_triggering_exchange_id_
        && ssr_triggering_volume_ == other.ssr_triggering_volume_
        && time_ == other.time_
        && ssr_state_ == other.ssr_state_
        && market_state_ == other.market_state_
        && session_state_ == other.session_state_;
}

bool SecurityStatusMessage::operator!=(const SecurityStatusMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::bbo::pillar::v2_5_b
