#include "ComplexStrategyAuctionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

ComplexStrategyAuctionMessage::ComplexStrategyAuctionMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, std::uint32_t auction_id, OrderType order_type, Side side, Decimal price, std::uint32_t size, ExecFlag exec_flag, OrderCapacity order_capacity, Scope scope, const std::string& owner_id, const std::string& giveup, const std::string& cmta, AuctionEvent auction_event, AuctionType auction_type, std::uint8_t number_of_responses, const std::vector<AuctionResponse>& auction_response)
  : timestamp_(timestamp), strategy_id_(strategy_id), auction_id_(auction_id), order_type_(order_type), side_(side), price_(price), size_(size), exec_flag_(exec_flag), order_capacity_(order_capacity), scope_(scope), owner_id_(owner_id), giveup_(giveup), cmta_(cmta), auction_event_(auction_event), auction_type_(auction_type), number_of_responses_(number_of_responses), auction_response_(auction_response) {}

std::chrono::nanoseconds ComplexStrategyAuctionMessage::timestamp() const { return timestamp_; }
void ComplexStrategyAuctionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t ComplexStrategyAuctionMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t ComplexStrategyAuctionMessage::strategy_id() const { return strategy_id_; }
void ComplexStrategyAuctionMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

std::uint32_t ComplexStrategyAuctionMessage::auction_id() const { return auction_id_; }
void ComplexStrategyAuctionMessage::set_auction_id(std::uint32_t value) { auction_id_ = value; }

OrderType ComplexStrategyAuctionMessage::order_type() const { return order_type_; }
void ComplexStrategyAuctionMessage::set_order_type(OrderType value) { order_type_ = value; }

Side ComplexStrategyAuctionMessage::side() const { return side_; }
void ComplexStrategyAuctionMessage::set_side(Side value) { side_ = value; }

Decimal ComplexStrategyAuctionMessage::price() const { return price_; }
void ComplexStrategyAuctionMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t ComplexStrategyAuctionMessage::size() const { return size_; }
void ComplexStrategyAuctionMessage::set_size(std::uint32_t value) { size_ = value; }

ExecFlag ComplexStrategyAuctionMessage::exec_flag() const { return exec_flag_; }
void ComplexStrategyAuctionMessage::set_exec_flag(ExecFlag value) { exec_flag_ = value; }

OrderCapacity ComplexStrategyAuctionMessage::order_capacity() const { return order_capacity_; }
void ComplexStrategyAuctionMessage::set_order_capacity(OrderCapacity value) { order_capacity_ = value; }

Scope ComplexStrategyAuctionMessage::scope() const { return scope_; }
void ComplexStrategyAuctionMessage::set_scope(Scope value) { scope_ = value; }

const std::string& ComplexStrategyAuctionMessage::owner_id() const { return owner_id_; }
std::string& ComplexStrategyAuctionMessage::owner_id() { return owner_id_; }
void ComplexStrategyAuctionMessage::set_owner_id(const std::string& value) { owner_id_ = value; }

const std::string& ComplexStrategyAuctionMessage::giveup() const { return giveup_; }
std::string& ComplexStrategyAuctionMessage::giveup() { return giveup_; }
void ComplexStrategyAuctionMessage::set_giveup(const std::string& value) { giveup_ = value; }

const std::string& ComplexStrategyAuctionMessage::cmta() const { return cmta_; }
std::string& ComplexStrategyAuctionMessage::cmta() { return cmta_; }
void ComplexStrategyAuctionMessage::set_cmta(const std::string& value) { cmta_ = value; }

AuctionEvent ComplexStrategyAuctionMessage::auction_event() const { return auction_event_; }
void ComplexStrategyAuctionMessage::set_auction_event(AuctionEvent value) { auction_event_ = value; }

AuctionType ComplexStrategyAuctionMessage::auction_type() const { return auction_type_; }
void ComplexStrategyAuctionMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

std::uint8_t ComplexStrategyAuctionMessage::number_of_responses() const { return number_of_responses_; }
void ComplexStrategyAuctionMessage::set_number_of_responses(std::uint8_t value) { number_of_responses_ = value; }

const std::vector<AuctionResponse>& ComplexStrategyAuctionMessage::auction_response() const { return auction_response_; }
std::vector<AuctionResponse>& ComplexStrategyAuctionMessage::auction_response() { return auction_response_; }
void ComplexStrategyAuctionMessage::set_auction_response(const std::vector<AuctionResponse>& value) { auction_response_ = value; }

MessageCode ComplexStrategyAuctionMessage::type() const { return message_type; }

std::string_view ComplexStrategyAuctionMessage::name() const { return "Complex Strategy Auction Message"; }

std::size_t ComplexStrategyAuctionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ComplexStrategyAuctionMessage", offset + 6, length);
    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    wire::require("ComplexStrategyAuctionMessage", offset + 4, length);
    strategy_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ComplexStrategyAuctionMessage", offset + 4, length);
    auction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ComplexStrategyAuctionMessage", offset + 1, length);
    order_type_ = static_cast<OrderType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyAuctionMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyAuctionMessage", offset + 4, length);
    price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    wire::require("ComplexStrategyAuctionMessage", offset + 4, length);
    size_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ComplexStrategyAuctionMessage", offset + 1, length);
    exec_flag_ = static_cast<ExecFlag>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyAuctionMessage", offset + 1, length);
    order_capacity_ = static_cast<OrderCapacity>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyAuctionMessage", offset + 1, length);
    scope_ = static_cast<Scope>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyAuctionMessage", offset + 6, length);
    owner_id_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::require("ComplexStrategyAuctionMessage", offset + 6, length);
    giveup_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::require("ComplexStrategyAuctionMessage", offset + 6, length);
    cmta_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::require("ComplexStrategyAuctionMessage", offset + 1, length);
    auction_event_ = static_cast<AuctionEvent>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyAuctionMessage", offset + 1, length);
    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyAuctionMessage", offset + 1, length);
    number_of_responses_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(number_of_responses_);
        auction_response_.clear();
        auction_response_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            AuctionResponse entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            auction_response_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t ComplexStrategyAuctionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexStrategyAuctionMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto number_of_responses = number_of_responses_;
    number_of_responses = static_cast<std::uint8_t>(auction_response_.size());

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(auction_id_));
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

    wire::write_char(data + offset, static_cast<char>(auction_event_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_responses));
    offset += 1;

    for (const auto& entry : auction_response_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t ComplexStrategyAuctionMessage::encoded_size() const {
    return 6 + 4 + 4 + 1 + 1 + 4 + 4 + 1 + 1 + 1 + 6 + 6 + 6 + 1 + 1 + 1 + wire::encoded_size_of(auction_response_);
}

void ComplexStrategyAuctionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexStrategyAuctionMessage::clone() const {
    return std::make_unique<ComplexStrategyAuctionMessage>(*this);
}

void ComplexStrategyAuctionMessage::print(std::ostream& out) const {
    out << "ComplexStrategyAuctionMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", auction_id=";
    out << auction_id_;
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
    out << ", auction_event=";
    out << auction_event_;
    out << ", auction_type=";
    out << auction_type_;
    out << ", number_of_responses=";
    out << static_cast<int>(number_of_responses_);
    out << ", auction_response=";
    print::sequence(out, auction_response_);
    out << '}';
}

bool ComplexStrategyAuctionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexStrategyAuctionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexStrategyAuctionMessage::operator==(const ComplexStrategyAuctionMessage& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && auction_id_ == other.auction_id_
        && order_type_ == other.order_type_
        && side_ == other.side_
        && price_ == other.price_
        && size_ == other.size_
        && exec_flag_ == other.exec_flag_
        && order_capacity_ == other.order_capacity_
        && scope_ == other.scope_
        && owner_id_ == other.owner_id_
        && giveup_ == other.giveup_
        && cmta_ == other.cmta_
        && auction_event_ == other.auction_event_
        && auction_type_ == other.auction_type_
        && number_of_responses_ == other.number_of_responses_
        && auction_response_ == other.auction_response_;
}

bool ComplexStrategyAuctionMessage::operator!=(const ComplexStrategyAuctionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
