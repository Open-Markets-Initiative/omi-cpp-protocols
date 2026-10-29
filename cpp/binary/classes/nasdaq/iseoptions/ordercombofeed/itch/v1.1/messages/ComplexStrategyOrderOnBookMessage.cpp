#include "ComplexStrategyOrderOnBookMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

ComplexStrategyOrderOnBookMessage::ComplexStrategyOrderOnBookMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, OrderType order_type, Side side, Decimal price, std::uint32_t size, ExecFlag exec_flag, OrderCapacity order_capacity, Scope scope, const std::string& owner_id, const std::string& giveup, const std::string& cmta)
  : timestamp_(timestamp), strategy_id_(strategy_id), order_type_(order_type), side_(side), price_(price), size_(size), exec_flag_(exec_flag), order_capacity_(order_capacity), scope_(scope), owner_id_(owner_id), giveup_(giveup), cmta_(cmta) {}

std::chrono::nanoseconds ComplexStrategyOrderOnBookMessage::timestamp() const { return timestamp_; }
void ComplexStrategyOrderOnBookMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t ComplexStrategyOrderOnBookMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t ComplexStrategyOrderOnBookMessage::strategy_id() const { return strategy_id_; }
void ComplexStrategyOrderOnBookMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

OrderType ComplexStrategyOrderOnBookMessage::order_type() const { return order_type_; }
void ComplexStrategyOrderOnBookMessage::set_order_type(OrderType value) { order_type_ = value; }

Side ComplexStrategyOrderOnBookMessage::side() const { return side_; }
void ComplexStrategyOrderOnBookMessage::set_side(Side value) { side_ = value; }

Decimal ComplexStrategyOrderOnBookMessage::price() const { return price_; }
void ComplexStrategyOrderOnBookMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t ComplexStrategyOrderOnBookMessage::size() const { return size_; }
void ComplexStrategyOrderOnBookMessage::set_size(std::uint32_t value) { size_ = value; }

ExecFlag ComplexStrategyOrderOnBookMessage::exec_flag() const { return exec_flag_; }
void ComplexStrategyOrderOnBookMessage::set_exec_flag(ExecFlag value) { exec_flag_ = value; }

OrderCapacity ComplexStrategyOrderOnBookMessage::order_capacity() const { return order_capacity_; }
void ComplexStrategyOrderOnBookMessage::set_order_capacity(OrderCapacity value) { order_capacity_ = value; }

Scope ComplexStrategyOrderOnBookMessage::scope() const { return scope_; }
void ComplexStrategyOrderOnBookMessage::set_scope(Scope value) { scope_ = value; }

const std::string& ComplexStrategyOrderOnBookMessage::owner_id() const { return owner_id_; }
std::string& ComplexStrategyOrderOnBookMessage::owner_id() { return owner_id_; }
void ComplexStrategyOrderOnBookMessage::set_owner_id(const std::string& value) { owner_id_ = value; }

const std::string& ComplexStrategyOrderOnBookMessage::giveup() const { return giveup_; }
std::string& ComplexStrategyOrderOnBookMessage::giveup() { return giveup_; }
void ComplexStrategyOrderOnBookMessage::set_giveup(const std::string& value) { giveup_ = value; }

const std::string& ComplexStrategyOrderOnBookMessage::cmta() const { return cmta_; }
std::string& ComplexStrategyOrderOnBookMessage::cmta() { return cmta_; }
void ComplexStrategyOrderOnBookMessage::set_cmta(const std::string& value) { cmta_ = value; }

MessageCode ComplexStrategyOrderOnBookMessage::type() const { return message_type; }

std::string_view ComplexStrategyOrderOnBookMessage::name() const { return "Complex Strategy Order On Book Message"; }

std::size_t ComplexStrategyOrderOnBookMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ComplexStrategyOrderOnBookMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    strategy_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_type_ = static_cast<OrderType>(wire::read_char(data + offset));
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    size_ = wire::read_u32_be(data + offset);
    offset += 4;

    exec_flag_ = static_cast<ExecFlag>(wire::read_char(data + offset));
    offset += 1;

    order_capacity_ = static_cast<OrderCapacity>(wire::read_char(data + offset));
    offset += 1;

    scope_ = static_cast<Scope>(wire::read_char(data + offset));
    offset += 1;

    owner_id_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    giveup_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    cmta_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    return offset;
}

std::size_t ComplexStrategyOrderOnBookMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexStrategyOrderOnBookMessage", wire_size, capacity);

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(order_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(exec_flag_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(order_capacity_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(scope_));
    offset += 1;

    wire::write_text(data + offset, 6, ' ', owner_id_);
    offset += 6;

    wire::write_text(data + offset, 6, ' ', giveup_);
    offset += 6;

    wire::write_text(data + offset, 6, ' ', cmta_);
    offset += 6;

    return offset;
}

std::size_t ComplexStrategyOrderOnBookMessage::encoded_size() const {
    return wire_size;
}

void ComplexStrategyOrderOnBookMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexStrategyOrderOnBookMessage::clone() const {
    return std::make_unique<ComplexStrategyOrderOnBookMessage>(*this);
}

void ComplexStrategyOrderOnBookMessage::print(std::ostream& out) const {
    out << "ComplexStrategyOrderOnBookMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", order_type=";
    out << order_type_;
    out << ", side=";
    out << side_;
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", exec_flag=";
    out << exec_flag_;
    out << ", order_capacity=";
    out << order_capacity_;
    out << ", scope=";
    out << scope_;
    out << ", owner_id=";
    print::text(out, owner_id_);
    out << ", giveup=";
    print::text(out, giveup_);
    out << ", cmta=";
    print::text(out, cmta_);
    out << '}';
}

bool ComplexStrategyOrderOnBookMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexStrategyOrderOnBookMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexStrategyOrderOnBookMessage::operator==(const ComplexStrategyOrderOnBookMessage& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && order_type_ == other.order_type_
        && side_ == other.side_
        && price_ == other.price_
        && size_ == other.size_
        && exec_flag_ == other.exec_flag_
        && order_capacity_ == other.order_capacity_
        && scope_ == other.scope_
        && owner_id_ == other.owner_id_
        && giveup_ == other.giveup_
        && cmta_ == other.cmta_;
}

bool ComplexStrategyOrderOnBookMessage::operator!=(const ComplexStrategyOrderOnBookMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
