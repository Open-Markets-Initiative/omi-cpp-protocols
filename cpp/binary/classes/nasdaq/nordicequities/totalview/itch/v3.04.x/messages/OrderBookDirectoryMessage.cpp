#include "OrderBookDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

OrderBookDirectoryMessage::OrderBookDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t order_book, const std::string& symbol, const std::string& isin, FinancialProduct financial_product, const std::string& trading_currency, const std::string& mic, std::uint16_t market_segment_id, const NoteCodesBitField1& note_codes_bit_field_1, const NoteCodesBitField2& note_codes_bit_field_2, const NoteCodesBitField3& note_codes_bit_field_3, const NoteCodesBitField4& note_codes_bit_field_4, const NoteCodesBitField5& note_codes_bit_field_5, const NoteCodesBitField6& note_codes_bit_field_6, const NoteCodesBitField7& note_codes_bit_field_7, const NoteCodesBitField8& note_codes_bit_field_8, std::uint32_t round_lot_size, const std::string& nordic_mid_mic, const std::string& aod_mic, const std::string& notation_of_qty, Decimal notional_amount, const std::string& currency, PriceNotation price_notation, Decimal multiplier_for_calculating_quantity_in_measurement_unit, const std::string& pure_stream_mic)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_book_(order_book), symbol_(symbol), isin_(isin), financial_product_(financial_product), trading_currency_(trading_currency), mic_(mic), market_segment_id_(market_segment_id), note_codes_bit_field_1_(note_codes_bit_field_1), note_codes_bit_field_2_(note_codes_bit_field_2), note_codes_bit_field_3_(note_codes_bit_field_3), note_codes_bit_field_4_(note_codes_bit_field_4), note_codes_bit_field_5_(note_codes_bit_field_5), note_codes_bit_field_6_(note_codes_bit_field_6), note_codes_bit_field_7_(note_codes_bit_field_7), note_codes_bit_field_8_(note_codes_bit_field_8), round_lot_size_(round_lot_size), nordic_mid_mic_(nordic_mid_mic), aod_mic_(aod_mic), notation_of_qty_(notation_of_qty), notional_amount_(notional_amount), currency_(currency), price_notation_(price_notation), multiplier_for_calculating_quantity_in_measurement_unit_(multiplier_for_calculating_quantity_in_measurement_unit), pure_stream_mic_(pure_stream_mic) {}

std::chrono::nanoseconds OrderBookDirectoryMessage::timestamp() const { return timestamp_; }
void OrderBookDirectoryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderBookDirectoryMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint16_t OrderBookDirectoryMessage::tracking_number() const { return tracking_number_; }
void OrderBookDirectoryMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint32_t OrderBookDirectoryMessage::order_book() const { return order_book_; }
void OrderBookDirectoryMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

const std::string& OrderBookDirectoryMessage::symbol() const { return symbol_; }
std::string& OrderBookDirectoryMessage::symbol() { return symbol_; }
void OrderBookDirectoryMessage::set_symbol(const std::string& value) { symbol_ = value; }

const std::string& OrderBookDirectoryMessage::isin() const { return isin_; }
std::string& OrderBookDirectoryMessage::isin() { return isin_; }
void OrderBookDirectoryMessage::set_isin(const std::string& value) { isin_ = value; }

FinancialProduct OrderBookDirectoryMessage::financial_product() const { return financial_product_; }
void OrderBookDirectoryMessage::set_financial_product(FinancialProduct value) { financial_product_ = value; }

const std::string& OrderBookDirectoryMessage::trading_currency() const { return trading_currency_; }
std::string& OrderBookDirectoryMessage::trading_currency() { return trading_currency_; }
void OrderBookDirectoryMessage::set_trading_currency(const std::string& value) { trading_currency_ = value; }

const std::string& OrderBookDirectoryMessage::mic() const { return mic_; }
std::string& OrderBookDirectoryMessage::mic() { return mic_; }
void OrderBookDirectoryMessage::set_mic(const std::string& value) { mic_ = value; }

std::uint16_t OrderBookDirectoryMessage::market_segment_id() const { return market_segment_id_; }
void OrderBookDirectoryMessage::set_market_segment_id(std::uint16_t value) { market_segment_id_ = value; }

const NoteCodesBitField1& OrderBookDirectoryMessage::note_codes_bit_field_1() const { return note_codes_bit_field_1_; }
NoteCodesBitField1& OrderBookDirectoryMessage::note_codes_bit_field_1() { return note_codes_bit_field_1_; }
void OrderBookDirectoryMessage::set_note_codes_bit_field_1(const NoteCodesBitField1& value) { note_codes_bit_field_1_ = value; }

const NoteCodesBitField2& OrderBookDirectoryMessage::note_codes_bit_field_2() const { return note_codes_bit_field_2_; }
NoteCodesBitField2& OrderBookDirectoryMessage::note_codes_bit_field_2() { return note_codes_bit_field_2_; }
void OrderBookDirectoryMessage::set_note_codes_bit_field_2(const NoteCodesBitField2& value) { note_codes_bit_field_2_ = value; }

const NoteCodesBitField3& OrderBookDirectoryMessage::note_codes_bit_field_3() const { return note_codes_bit_field_3_; }
NoteCodesBitField3& OrderBookDirectoryMessage::note_codes_bit_field_3() { return note_codes_bit_field_3_; }
void OrderBookDirectoryMessage::set_note_codes_bit_field_3(const NoteCodesBitField3& value) { note_codes_bit_field_3_ = value; }

const NoteCodesBitField4& OrderBookDirectoryMessage::note_codes_bit_field_4() const { return note_codes_bit_field_4_; }
NoteCodesBitField4& OrderBookDirectoryMessage::note_codes_bit_field_4() { return note_codes_bit_field_4_; }
void OrderBookDirectoryMessage::set_note_codes_bit_field_4(const NoteCodesBitField4& value) { note_codes_bit_field_4_ = value; }

const NoteCodesBitField5& OrderBookDirectoryMessage::note_codes_bit_field_5() const { return note_codes_bit_field_5_; }
NoteCodesBitField5& OrderBookDirectoryMessage::note_codes_bit_field_5() { return note_codes_bit_field_5_; }
void OrderBookDirectoryMessage::set_note_codes_bit_field_5(const NoteCodesBitField5& value) { note_codes_bit_field_5_ = value; }

const NoteCodesBitField6& OrderBookDirectoryMessage::note_codes_bit_field_6() const { return note_codes_bit_field_6_; }
NoteCodesBitField6& OrderBookDirectoryMessage::note_codes_bit_field_6() { return note_codes_bit_field_6_; }
void OrderBookDirectoryMessage::set_note_codes_bit_field_6(const NoteCodesBitField6& value) { note_codes_bit_field_6_ = value; }

const NoteCodesBitField7& OrderBookDirectoryMessage::note_codes_bit_field_7() const { return note_codes_bit_field_7_; }
NoteCodesBitField7& OrderBookDirectoryMessage::note_codes_bit_field_7() { return note_codes_bit_field_7_; }
void OrderBookDirectoryMessage::set_note_codes_bit_field_7(const NoteCodesBitField7& value) { note_codes_bit_field_7_ = value; }

const NoteCodesBitField8& OrderBookDirectoryMessage::note_codes_bit_field_8() const { return note_codes_bit_field_8_; }
NoteCodesBitField8& OrderBookDirectoryMessage::note_codes_bit_field_8() { return note_codes_bit_field_8_; }
void OrderBookDirectoryMessage::set_note_codes_bit_field_8(const NoteCodesBitField8& value) { note_codes_bit_field_8_ = value; }

std::uint32_t OrderBookDirectoryMessage::round_lot_size() const { return round_lot_size_; }
void OrderBookDirectoryMessage::set_round_lot_size(std::uint32_t value) { round_lot_size_ = value; }

const std::string& OrderBookDirectoryMessage::nordic_mid_mic() const { return nordic_mid_mic_; }
std::string& OrderBookDirectoryMessage::nordic_mid_mic() { return nordic_mid_mic_; }
void OrderBookDirectoryMessage::set_nordic_mid_mic(const std::string& value) { nordic_mid_mic_ = value; }

const std::string& OrderBookDirectoryMessage::aod_mic() const { return aod_mic_; }
std::string& OrderBookDirectoryMessage::aod_mic() { return aod_mic_; }
void OrderBookDirectoryMessage::set_aod_mic(const std::string& value) { aod_mic_ = value; }

const std::string& OrderBookDirectoryMessage::notation_of_qty() const { return notation_of_qty_; }
std::string& OrderBookDirectoryMessage::notation_of_qty() { return notation_of_qty_; }
void OrderBookDirectoryMessage::set_notation_of_qty(const std::string& value) { notation_of_qty_ = value; }

Decimal OrderBookDirectoryMessage::notional_amount() const { return notional_amount_; }
void OrderBookDirectoryMessage::set_notional_amount(Decimal value) { notional_amount_ = value; }

const std::string& OrderBookDirectoryMessage::currency() const { return currency_; }
std::string& OrderBookDirectoryMessage::currency() { return currency_; }
void OrderBookDirectoryMessage::set_currency(const std::string& value) { currency_ = value; }

PriceNotation OrderBookDirectoryMessage::price_notation() const { return price_notation_; }
void OrderBookDirectoryMessage::set_price_notation(PriceNotation value) { price_notation_ = value; }

Decimal OrderBookDirectoryMessage::multiplier_for_calculating_quantity_in_measurement_unit() const { return multiplier_for_calculating_quantity_in_measurement_unit_; }
void OrderBookDirectoryMessage::set_multiplier_for_calculating_quantity_in_measurement_unit(Decimal value) { multiplier_for_calculating_quantity_in_measurement_unit_ = value; }

const std::string& OrderBookDirectoryMessage::pure_stream_mic() const { return pure_stream_mic_; }
std::string& OrderBookDirectoryMessage::pure_stream_mic() { return pure_stream_mic_; }
void OrderBookDirectoryMessage::set_pure_stream_mic(const std::string& value) { pure_stream_mic_ = value; }

MessageCode OrderBookDirectoryMessage::type() const { return message_type; }

std::string_view OrderBookDirectoryMessage::name() const { return "Order Book Directory Message"; }

std::size_t OrderBookDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookDirectoryMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    symbol_ = wire::read_text(data + offset, 16, ' ');
    offset += 16;

    isin_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    financial_product_ = static_cast<FinancialProduct>(wire::read_u8(data + offset));
    offset += 1;

    trading_currency_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    mic_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    market_segment_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    offset += note_codes_bit_field_1_.decode(data + offset, length - offset);

    offset += note_codes_bit_field_2_.decode(data + offset, length - offset);

    offset += note_codes_bit_field_3_.decode(data + offset, length - offset);

    offset += note_codes_bit_field_4_.decode(data + offset, length - offset);

    offset += note_codes_bit_field_5_.decode(data + offset, length - offset);

    offset += note_codes_bit_field_6_.decode(data + offset, length - offset);

    offset += note_codes_bit_field_7_.decode(data + offset, length - offset);

    offset += note_codes_bit_field_8_.decode(data + offset, length - offset);

    round_lot_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    nordic_mid_mic_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    aod_mic_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    notation_of_qty_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    notional_amount_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -5);
    offset += 8;

    currency_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    price_notation_ = static_cast<PriceNotation>(wire::read_char(data + offset));
    offset += 1;

    multiplier_for_calculating_quantity_in_measurement_unit_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    pure_stream_mic_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t OrderBookDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookDirectoryMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    wire::write_text(data + offset, 16, ' ', symbol_);
    offset += 16;

    wire::write_text(data + offset, 12, ' ', isin_);
    offset += 12;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(financial_product_));
    offset += 1;

    wire::write_text(data + offset, 3, ' ', trading_currency_);
    offset += 3;

    wire::write_text(data + offset, 4, ' ', mic_);
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(market_segment_id_));
    offset += 2;

    offset += note_codes_bit_field_1_.encode(data + offset, capacity - offset);

    offset += note_codes_bit_field_2_.encode(data + offset, capacity - offset);

    offset += note_codes_bit_field_3_.encode(data + offset, capacity - offset);

    offset += note_codes_bit_field_4_.encode(data + offset, capacity - offset);

    offset += note_codes_bit_field_5_.encode(data + offset, capacity - offset);

    offset += note_codes_bit_field_6_.encode(data + offset, capacity - offset);

    offset += note_codes_bit_field_7_.encode(data + offset, capacity - offset);

    offset += note_codes_bit_field_8_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(round_lot_size_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', nordic_mid_mic_);
    offset += 4;

    wire::write_text(data + offset, 4, ' ', aod_mic_);
    offset += 4;

    wire::write_text(data + offset, 4, ' ', notation_of_qty_);
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(notional_amount_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', currency_);
    offset += 3;

    wire::write_char(data + offset, static_cast<char>(price_notation_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(multiplier_for_calculating_quantity_in_measurement_unit_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 4, ' ', pure_stream_mic_);
    offset += 4;

    return offset;
}

std::size_t OrderBookDirectoryMessage::encoded_size() const {
    return wire_size;
}

void OrderBookDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookDirectoryMessage::clone() const {
    return std::make_unique<OrderBookDirectoryMessage>(*this);
}

void OrderBookDirectoryMessage::print(std::ostream& out) const {
    out << "OrderBookDirectoryMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "UTC");
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_book=";
    out << order_book_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", isin=";
    print::text(out, isin_);
    out << ", financial_product=";
    out << financial_product_;
    out << ", trading_currency=";
    print::text(out, trading_currency_);
    out << ", mic=";
    print::text(out, mic_);
    out << ", market_segment_id=";
    out << market_segment_id_;
    out << ", note_codes_bit_field_1=";
    note_codes_bit_field_1_.print(out);
    out << ", note_codes_bit_field_2=";
    note_codes_bit_field_2_.print(out);
    out << ", note_codes_bit_field_3=";
    note_codes_bit_field_3_.print(out);
    out << ", note_codes_bit_field_4=";
    note_codes_bit_field_4_.print(out);
    out << ", note_codes_bit_field_5=";
    note_codes_bit_field_5_.print(out);
    out << ", note_codes_bit_field_6=";
    note_codes_bit_field_6_.print(out);
    out << ", note_codes_bit_field_7=";
    note_codes_bit_field_7_.print(out);
    out << ", note_codes_bit_field_8=";
    note_codes_bit_field_8_.print(out);
    out << ", round_lot_size=";
    out << round_lot_size_;
    out << ", nordic_mid_mic=";
    print::text(out, nordic_mid_mic_);
    out << ", aod_mic=";
    print::text(out, aod_mic_);
    out << ", notation_of_qty=";
    print::text(out, notation_of_qty_);
    out << ", notional_amount=";
    out << notional_amount_;
    out << ", currency=";
    print::text(out, currency_);
    out << ", price_notation=";
    out << price_notation_;
    out << ", multiplier_for_calculating_quantity_in_measurement_unit=";
    out << multiplier_for_calculating_quantity_in_measurement_unit_;
    out << ", pure_stream_mic=";
    print::text(out, pure_stream_mic_);
    out << '}';
}

bool OrderBookDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookDirectoryMessage::operator==(const OrderBookDirectoryMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_book_ == other.order_book_
        && symbol_ == other.symbol_
        && isin_ == other.isin_
        && financial_product_ == other.financial_product_
        && trading_currency_ == other.trading_currency_
        && mic_ == other.mic_
        && market_segment_id_ == other.market_segment_id_
        && note_codes_bit_field_1_ == other.note_codes_bit_field_1_
        && note_codes_bit_field_2_ == other.note_codes_bit_field_2_
        && note_codes_bit_field_3_ == other.note_codes_bit_field_3_
        && note_codes_bit_field_4_ == other.note_codes_bit_field_4_
        && note_codes_bit_field_5_ == other.note_codes_bit_field_5_
        && note_codes_bit_field_6_ == other.note_codes_bit_field_6_
        && note_codes_bit_field_7_ == other.note_codes_bit_field_7_
        && note_codes_bit_field_8_ == other.note_codes_bit_field_8_
        && round_lot_size_ == other.round_lot_size_
        && nordic_mid_mic_ == other.nordic_mid_mic_
        && aod_mic_ == other.aod_mic_
        && notation_of_qty_ == other.notation_of_qty_
        && notional_amount_ == other.notional_amount_
        && currency_ == other.currency_
        && price_notation_ == other.price_notation_
        && multiplier_for_calculating_quantity_in_measurement_unit_ == other.multiplier_for_calculating_quantity_in_measurement_unit_
        && pure_stream_mic_ == other.pure_stream_mic_;
}

bool OrderBookDirectoryMessage::operator!=(const OrderBookDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
