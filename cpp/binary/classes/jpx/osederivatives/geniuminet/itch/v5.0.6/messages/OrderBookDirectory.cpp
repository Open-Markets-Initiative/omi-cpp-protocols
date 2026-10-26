#include "OrderBookDirectory.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

OrderBookDirectory::OrderBookDirectory(std::chrono::nanoseconds nanoseconds, std::uint32_t order_book_id, const std::string& symbol, const std::string& long_name, const std::string& isin, FinancialProduct financial_product, const std::string& trading_currency, std::uint16_t decimals_in_price, std::uint16_t decimals_in_nominal_value, std::uint32_t odd_lot_size, std::uint32_t round_lot_size, std::uint32_t block_lot_size, std::uint64_t nominal_value, std::uint8_t number_of_legs, std::uint32_t underlying_orderbook_id, std::int32_t strike_price, std::uint32_t expiration_date, std::uint16_t decimals_in_strike_price, PutOrCall put_or_call)
  : nanoseconds_(nanoseconds), order_book_id_(order_book_id), symbol_(symbol), long_name_(long_name), isin_(isin), financial_product_(financial_product), trading_currency_(trading_currency), decimals_in_price_(decimals_in_price), decimals_in_nominal_value_(decimals_in_nominal_value), odd_lot_size_(odd_lot_size), round_lot_size_(round_lot_size), block_lot_size_(block_lot_size), nominal_value_(nominal_value), number_of_legs_(number_of_legs), underlying_orderbook_id_(underlying_orderbook_id), strike_price_(strike_price), expiration_date_(expiration_date), decimals_in_strike_price_(decimals_in_strike_price), put_or_call_(put_or_call) {}

std::chrono::nanoseconds OrderBookDirectory::nanoseconds() const { return nanoseconds_; }
void OrderBookDirectory::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t OrderBookDirectory::order_book_id() const { return order_book_id_; }
void OrderBookDirectory::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

const std::string& OrderBookDirectory::symbol() const { return symbol_; }
std::string& OrderBookDirectory::symbol() { return symbol_; }
void OrderBookDirectory::set_symbol(const std::string& value) { symbol_ = value; }

const std::string& OrderBookDirectory::long_name() const { return long_name_; }
std::string& OrderBookDirectory::long_name() { return long_name_; }
void OrderBookDirectory::set_long_name(const std::string& value) { long_name_ = value; }

const std::string& OrderBookDirectory::isin() const { return isin_; }
std::string& OrderBookDirectory::isin() { return isin_; }
void OrderBookDirectory::set_isin(const std::string& value) { isin_ = value; }

FinancialProduct OrderBookDirectory::financial_product() const { return financial_product_; }
void OrderBookDirectory::set_financial_product(FinancialProduct value) { financial_product_ = value; }

const std::string& OrderBookDirectory::trading_currency() const { return trading_currency_; }
std::string& OrderBookDirectory::trading_currency() { return trading_currency_; }
void OrderBookDirectory::set_trading_currency(const std::string& value) { trading_currency_ = value; }

std::uint16_t OrderBookDirectory::decimals_in_price() const { return decimals_in_price_; }
void OrderBookDirectory::set_decimals_in_price(std::uint16_t value) { decimals_in_price_ = value; }

std::uint16_t OrderBookDirectory::decimals_in_nominal_value() const { return decimals_in_nominal_value_; }
void OrderBookDirectory::set_decimals_in_nominal_value(std::uint16_t value) { decimals_in_nominal_value_ = value; }

std::uint32_t OrderBookDirectory::odd_lot_size() const { return odd_lot_size_; }
void OrderBookDirectory::set_odd_lot_size(std::uint32_t value) { odd_lot_size_ = value; }

std::uint32_t OrderBookDirectory::round_lot_size() const { return round_lot_size_; }
void OrderBookDirectory::set_round_lot_size(std::uint32_t value) { round_lot_size_ = value; }

std::uint32_t OrderBookDirectory::block_lot_size() const { return block_lot_size_; }
void OrderBookDirectory::set_block_lot_size(std::uint32_t value) { block_lot_size_ = value; }

std::uint64_t OrderBookDirectory::nominal_value() const { return nominal_value_; }
void OrderBookDirectory::set_nominal_value(std::uint64_t value) { nominal_value_ = value; }

std::uint8_t OrderBookDirectory::number_of_legs() const { return number_of_legs_; }
void OrderBookDirectory::set_number_of_legs(std::uint8_t value) { number_of_legs_ = value; }

std::uint32_t OrderBookDirectory::underlying_orderbook_id() const { return underlying_orderbook_id_; }
void OrderBookDirectory::set_underlying_orderbook_id(std::uint32_t value) { underlying_orderbook_id_ = value; }

std::int32_t OrderBookDirectory::strike_price() const { return strike_price_; }
void OrderBookDirectory::set_strike_price(std::int32_t value) { strike_price_ = value; }

std::uint32_t OrderBookDirectory::expiration_date() const { return expiration_date_; }
void OrderBookDirectory::set_expiration_date(std::uint32_t value) { expiration_date_ = value; }

std::uint16_t OrderBookDirectory::decimals_in_strike_price() const { return decimals_in_strike_price_; }
void OrderBookDirectory::set_decimals_in_strike_price(std::uint16_t value) { decimals_in_strike_price_ = value; }

PutOrCall OrderBookDirectory::put_or_call() const { return put_or_call_; }
void OrderBookDirectory::set_put_or_call(PutOrCall value) { put_or_call_ = value; }

MessageCode OrderBookDirectory::type() const { return message_type; }

std::string_view OrderBookDirectory::name() const { return "Order Book Directory"; }

std::size_t OrderBookDirectory::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookDirectory", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_book_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    symbol_ = wire::read_text(data + offset, 32, ' ');
    offset += 32;

    long_name_ = wire::read_text(data + offset, 32, ' ');
    offset += 32;

    isin_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    financial_product_ = static_cast<FinancialProduct>(wire::read_u8(data + offset));
    offset += 1;

    trading_currency_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    decimals_in_price_ = wire::read_u16_be(data + offset);
    offset += 2;

    decimals_in_nominal_value_ = wire::read_u16_be(data + offset);
    offset += 2;

    odd_lot_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    round_lot_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    block_lot_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    nominal_value_ = wire::read_u64_be(data + offset);
    offset += 8;

    number_of_legs_ = wire::read_u8(data + offset);
    offset += 1;

    underlying_orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    strike_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    expiration_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    decimals_in_strike_price_ = wire::read_u16_be(data + offset);
    offset += 2;

    put_or_call_ = static_cast<PutOrCall>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderBookDirectory::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookDirectory", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_id_));
    offset += 4;

    wire::write_text(data + offset, 32, ' ', symbol_);
    offset += 32;

    wire::write_text(data + offset, 32, ' ', long_name_);
    offset += 32;

    wire::write_text(data + offset, 12, ' ', isin_);
    offset += 12;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(financial_product_));
    offset += 1;

    wire::write_text(data + offset, 3, ' ', trading_currency_);
    offset += 3;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(decimals_in_price_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(decimals_in_nominal_value_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(odd_lot_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(round_lot_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(block_lot_size_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(nominal_value_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_legs_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(underlying_orderbook_id_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(strike_price_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(expiration_date_));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(decimals_in_strike_price_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(put_or_call_));
    offset += 1;

    return offset;
}

std::size_t OrderBookDirectory::encoded_size() const {
    return wire_size;
}

void OrderBookDirectory::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookDirectory::clone() const {
    return std::make_unique<OrderBookDirectory>(*this);
}

void OrderBookDirectory::print(std::ostream& out) const {
    out << "OrderBookDirectory{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_book_id=";
    out << order_book_id_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", long_name=";
    print::text(out, long_name_);
    out << ", isin=";
    print::text(out, isin_);
    out << ", financial_product=";
    out << financial_product_;
    out << ", trading_currency=";
    print::text(out, trading_currency_);
    out << ", decimals_in_price=";
    out << decimals_in_price_;
    out << ", decimals_in_nominal_value=";
    out << decimals_in_nominal_value_;
    out << ", odd_lot_size=";
    out << odd_lot_size_;
    out << ", round_lot_size=";
    out << round_lot_size_;
    out << ", block_lot_size=";
    out << block_lot_size_;
    out << ", nominal_value=";
    out << nominal_value_;
    out << ", number_of_legs=";
    out << static_cast<int>(number_of_legs_);
    out << ", underlying_orderbook_id=";
    out << underlying_orderbook_id_;
    out << ", strike_price=";
    out << strike_price_;
    out << ", expiration_date=";
    out << expiration_date_;
    out << ", decimals_in_strike_price=";
    out << decimals_in_strike_price_;
    out << ", put_or_call=";
    out << put_or_call_;
    out << '}';
}

bool OrderBookDirectory::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookDirectory*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookDirectory::operator==(const OrderBookDirectory& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_book_id_ == other.order_book_id_
        && symbol_ == other.symbol_
        && long_name_ == other.long_name_
        && isin_ == other.isin_
        && financial_product_ == other.financial_product_
        && trading_currency_ == other.trading_currency_
        && decimals_in_price_ == other.decimals_in_price_
        && decimals_in_nominal_value_ == other.decimals_in_nominal_value_
        && odd_lot_size_ == other.odd_lot_size_
        && round_lot_size_ == other.round_lot_size_
        && block_lot_size_ == other.block_lot_size_
        && nominal_value_ == other.nominal_value_
        && number_of_legs_ == other.number_of_legs_
        && underlying_orderbook_id_ == other.underlying_orderbook_id_
        && strike_price_ == other.strike_price_
        && expiration_date_ == other.expiration_date_
        && decimals_in_strike_price_ == other.decimals_in_strike_price_
        && put_or_call_ == other.put_or_call_;
}

bool OrderBookDirectory::operator!=(const OrderBookDirectory& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
