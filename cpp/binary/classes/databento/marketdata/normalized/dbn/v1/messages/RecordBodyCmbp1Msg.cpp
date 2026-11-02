#include "RecordBodyCmbp1Msg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

RecordBodyCmbp1Msg::RecordBodyCmbp1Msg(std::optional<Decimal> price, std::uint32_t size, Action action, Side side, const Flags& flags, const std::array<std::byte, 1>& reserved_1, std::optional<std::chrono::nanoseconds> ts_recv, std::int32_t ts_in_delta, const std::array<std::byte, 4>& reserved_4, const ConsolidatedBidAskPair& consolidated_bid_ask_pair)
  : price_(price), size_(size), action_(action), side_(side), flags_(flags), reserved_1_(reserved_1), ts_recv_(ts_recv), ts_in_delta_(ts_in_delta), reserved_4_(reserved_4), consolidated_bid_ask_pair_(consolidated_bid_ask_pair) {}

std::optional<Decimal> RecordBodyCmbp1Msg::price() const { return price_; }
void RecordBodyCmbp1Msg::set_price(std::optional<Decimal> value) { price_ = value; }

std::uint32_t RecordBodyCmbp1Msg::size() const { return size_; }
void RecordBodyCmbp1Msg::set_size(std::uint32_t value) { size_ = value; }

Action RecordBodyCmbp1Msg::action() const { return action_; }
void RecordBodyCmbp1Msg::set_action(Action value) { action_ = value; }

Side RecordBodyCmbp1Msg::side() const { return side_; }
void RecordBodyCmbp1Msg::set_side(Side value) { side_ = value; }

const Flags& RecordBodyCmbp1Msg::flags() const { return flags_; }
Flags& RecordBodyCmbp1Msg::flags() { return flags_; }
void RecordBodyCmbp1Msg::set_flags(const Flags& value) { flags_ = value; }

const std::array<std::byte, 1>& RecordBodyCmbp1Msg::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& RecordBodyCmbp1Msg::reserved_1() { return reserved_1_; }
void RecordBodyCmbp1Msg::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

std::optional<std::chrono::nanoseconds> RecordBodyCmbp1Msg::ts_recv() const { return ts_recv_; }
void RecordBodyCmbp1Msg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

std::int32_t RecordBodyCmbp1Msg::ts_in_delta() const { return ts_in_delta_; }
void RecordBodyCmbp1Msg::set_ts_in_delta(std::int32_t value) { ts_in_delta_ = value; }

const std::array<std::byte, 4>& RecordBodyCmbp1Msg::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& RecordBodyCmbp1Msg::reserved_4() { return reserved_4_; }
void RecordBodyCmbp1Msg::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

const ConsolidatedBidAskPair& RecordBodyCmbp1Msg::consolidated_bid_ask_pair() const { return consolidated_bid_ask_pair_; }
ConsolidatedBidAskPair& RecordBodyCmbp1Msg::consolidated_bid_ask_pair() { return consolidated_bid_ask_pair_; }
void RecordBodyCmbp1Msg::set_consolidated_bid_ask_pair(const ConsolidatedBidAskPair& value) { consolidated_bid_ask_pair_ = value; }

GatewayMessageCode RecordBodyCmbp1Msg::type() const { return message_type; }

std::string_view RecordBodyCmbp1Msg::name() const { return "Cmbp 1 Msg"; }

std::size_t RecordBodyCmbp1Msg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RecordBodyCmbp1Msg", wire_size, length);

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    action_ = static_cast<Action>(wire::read_char(data + offset));
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    offset += flags_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    ts_recv_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    ts_in_delta_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    offset += consolidated_bid_ask_pair_.decode(data + offset, length - offset);

    return offset;
}

std::size_t RecordBodyCmbp1Msg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RecordBodyCmbp1Msg", wire_size, capacity);

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    offset += flags_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_u64_le(data + offset, ts_recv_ ? static_cast<std::uint64_t>(ts_recv_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(ts_in_delta_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    offset += consolidated_bid_ask_pair_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t RecordBodyCmbp1Msg::encoded_size() const {
    return wire_size;
}

void RecordBodyCmbp1Msg::accept(GatewayMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<GatewayMessage> RecordBodyCmbp1Msg::clone() const {
    return std::make_unique<RecordBodyCmbp1Msg>(*this);
}

void RecordBodyCmbp1Msg::print(std::ostream& out) const {
    out << "RecordBodyCmbp1Msg{";
    out << "price=";
    print::optional(out, price_);
    out << ", size=";
    out << size_;
    out << ", action=";
    out << action_;
    out << ", side=";
    out << side_;
    out << ", flags=";
    flags_.print(out);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", ts_recv=";
    print::optional_duration(out, ts_recv_);
    out << ", ts_in_delta=";
    out << ts_in_delta_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", consolidated_bid_ask_pair=";
    consolidated_bid_ask_pair_.print(out);
    out << '}';
}

bool RecordBodyCmbp1Msg::equals(const GatewayMessage& other) const {
    const auto* that = dynamic_cast<const RecordBodyCmbp1Msg*>(&other);
    return that != nullptr && *this == *that;
}

bool RecordBodyCmbp1Msg::operator==(const RecordBodyCmbp1Msg& other) const {
    return price_ == other.price_
        && size_ == other.size_
        && action_ == other.action_
        && side_ == other.side_
        && flags_ == other.flags_
        && reserved_1_ == other.reserved_1_
        && ts_recv_ == other.ts_recv_
        && ts_in_delta_ == other.ts_in_delta_
        && reserved_4_ == other.reserved_4_
        && consolidated_bid_ask_pair_ == other.consolidated_bid_ask_pair_;
}

bool RecordBodyCmbp1Msg::operator!=(const RecordBodyCmbp1Msg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v1
