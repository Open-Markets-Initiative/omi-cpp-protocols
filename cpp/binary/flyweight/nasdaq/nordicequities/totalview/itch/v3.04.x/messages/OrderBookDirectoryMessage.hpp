#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/FinancialProduct.hpp"
#include "../bitfields/NoteCodesBitField1.hpp"
#include "../bitfields/NoteCodesBitField2.hpp"
#include "../bitfields/NoteCodesBitField3.hpp"
#include "../bitfields/NoteCodesBitField4.hpp"
#include "../bitfields/NoteCodesBitField5.hpp"
#include "../bitfields/NoteCodesBitField6.hpp"
#include "../bitfields/NoteCodesBitField7.hpp"
#include "../bitfields/NoteCodesBitField8.hpp"
#include "../common/Decimal.hpp"
#include "../enums/PriceNotation.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Disseminated for all active order books at the start of each trading day
class OrderBookDirectoryMessage {
  public:
    static constexpr const char* name = "OrderBookDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderBookDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderBookDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 100;
    static constexpr std::size_t fixed_size = 100;
    std::size_t encoded_size() const { return 100; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint32_t order_book() const { return wire::read_u32_be(at(10)); }

    std::string_view symbol() const { return view::text(at(14), 16, ' '); }

    std::string_view isin() const { return view::text(at(30), 12, ' '); }

    FinancialProduct financial_product() const { return static_cast<FinancialProduct>(wire::read_u8(at(42))); }

    std::string_view trading_currency() const { return view::text(at(43), 3, ' '); }

    std::string_view mic() const { return view::text(at(46), 4, ' '); }

    std::uint16_t market_segment_id() const { return wire::read_u16_be(at(50)); }

    NoteCodesBitField1 note_codes_bit_field_1() const { return NoteCodesBitField1{ bytes_.subspan(52) }; }

    NoteCodesBitField2 note_codes_bit_field_2() const { return NoteCodesBitField2{ bytes_.subspan(53) }; }

    NoteCodesBitField3 note_codes_bit_field_3() const { return NoteCodesBitField3{ bytes_.subspan(54) }; }

    NoteCodesBitField4 note_codes_bit_field_4() const { return NoteCodesBitField4{ bytes_.subspan(55) }; }

    NoteCodesBitField5 note_codes_bit_field_5() const { return NoteCodesBitField5{ bytes_.subspan(56) }; }

    NoteCodesBitField6 note_codes_bit_field_6() const { return NoteCodesBitField6{ bytes_.subspan(57) }; }

    NoteCodesBitField7 note_codes_bit_field_7() const { return NoteCodesBitField7{ bytes_.subspan(58) }; }

    NoteCodesBitField8 note_codes_bit_field_8() const { return NoteCodesBitField8{ bytes_.subspan(59) }; }

    std::uint32_t round_lot_size() const { return wire::read_u32_be(at(60)); }

    std::string_view nordic_mid_mic() const { return view::text(at(64), 4, ' '); }

    std::string_view aod_mic() const { return view::text(at(68), 4, ' '); }

    std::string_view notation_of_qty() const { return view::text(at(72), 4, ' '); }

    Decimal notional_amount() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(76))), -5); }

    std::string_view currency() const { return view::text(at(84), 3, ' '); }

    PriceNotation price_notation() const { return static_cast<PriceNotation>(wire::read_char(at(87))); }

    Decimal multiplier_for_calculating_quantity_in_measurement_unit() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(88))), -6); }

    std::string_view pure_stream_mic() const { return view::text(at(96), 4, ' '); }

    void print(std::ostream& out) const {
        out << "OrderBookDirectoryMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "UTC");
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_book=";
        out << order_book();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", isin=";
        print::text(out, isin());
        out << ", financial_product=";
        out << financial_product();
        out << ", trading_currency=";
        print::text(out, trading_currency());
        out << ", mic=";
        print::text(out, mic());
        out << ", market_segment_id=";
        out << market_segment_id();
        out << ", note_codes_bit_field_1=";
        note_codes_bit_field_1().print(out);
        out << ", note_codes_bit_field_2=";
        note_codes_bit_field_2().print(out);
        out << ", note_codes_bit_field_3=";
        note_codes_bit_field_3().print(out);
        out << ", note_codes_bit_field_4=";
        note_codes_bit_field_4().print(out);
        out << ", note_codes_bit_field_5=";
        note_codes_bit_field_5().print(out);
        out << ", note_codes_bit_field_6=";
        note_codes_bit_field_6().print(out);
        out << ", note_codes_bit_field_7=";
        note_codes_bit_field_7().print(out);
        out << ", note_codes_bit_field_8=";
        note_codes_bit_field_8().print(out);
        out << ", round_lot_size=";
        out << round_lot_size();
        out << ", nordic_mid_mic=";
        print::text(out, nordic_mid_mic());
        out << ", aod_mic=";
        print::text(out, aod_mic());
        out << ", notation_of_qty=";
        print::text(out, notation_of_qty());
        out << ", notional_amount=";
        out << notional_amount();
        out << ", currency=";
        print::text(out, currency());
        out << ", price_notation=";
        out << price_notation();
        out << ", multiplier_for_calculating_quantity_in_measurement_unit=";
        out << multiplier_for_calculating_quantity_in_measurement_unit();
        out << ", pure_stream_mic=";
        print::text(out, pure_stream_mic());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderBookDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
