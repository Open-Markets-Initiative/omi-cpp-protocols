#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/NoteCodesBitField1.hpp"
#include "../bitfields/NoteCodesBitField2.hpp"
#include "../bitfields/NoteCodesBitField3.hpp"
#include "../bitfields/NoteCodesBitField4.hpp"
#include "../bitfields/NoteCodesBitField5.hpp"
#include "../bitfields/NoteCodesBitField6.hpp"
#include "../bitfields/NoteCodesBitField7.hpp"
#include "../bitfields/NoteCodesBitField8.hpp"
#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/FinancialProduct.hpp"
#include "../enums/PriceNotation.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// Disseminated for all active order books at the start of each trading day
class OrderBookDirectoryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderBookDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 100;

    OrderBookDirectoryMessage() = default;
    OrderBookDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t order_book, const std::string& symbol, const std::string& isin, FinancialProduct financial_product, const std::string& trading_currency, const std::string& mic, std::uint16_t market_segment_id, const NoteCodesBitField1& note_codes_bit_field_1, const NoteCodesBitField2& note_codes_bit_field_2, const NoteCodesBitField3& note_codes_bit_field_3, const NoteCodesBitField4& note_codes_bit_field_4, const NoteCodesBitField5& note_codes_bit_field_5, const NoteCodesBitField6& note_codes_bit_field_6, const NoteCodesBitField7& note_codes_bit_field_7, const NoteCodesBitField8& note_codes_bit_field_8, std::uint32_t round_lot_size, const std::string& nordic_mid_mic, const std::string& aod_mic, const std::string& notation_of_qty, Decimal notional_amount, const std::string& currency, PriceNotation price_notation, Decimal multiplier_for_calculating_quantity_in_measurement_unit, const std::string& pure_stream_mic);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Order Book: Order book id
    std::uint32_t order_book() const;
    void set_order_book(std::uint32_t value);

    // Symbol: Human readable name of the security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Isin: Isin code identifying security
    const std::string& isin() const;
    std::string& isin();
    void set_isin(const std::string& value);

    // Financial Product: Type of financial product
    FinancialProduct financial_product() const;
    void set_financial_product(FinancialProduct value);

    // Trading Currency: Trading currency
    const std::string& trading_currency() const;
    std::string& trading_currency();
    void set_trading_currency(const std::string& value);

    // Mic: Market identifier code
    const std::string& mic() const;
    std::string& mic();
    void set_mic(const std::string& value);

    // Market Segment Id: Market segment this order book belongs to
    std::uint16_t market_segment_id() const;
    void set_market_segment_id(std::uint16_t value);

    // Note Codes Bit Field 1: Note codes, logical Or is used to identify multiple note codes
    const NoteCodesBitField1& note_codes_bit_field_1() const;
    NoteCodesBitField1& note_codes_bit_field_1();
    void set_note_codes_bit_field_1(const NoteCodesBitField1& value);

    // Note Codes Bit Field 2: Note codes, logical Or is used to identify multiple note codes
    const NoteCodesBitField2& note_codes_bit_field_2() const;
    NoteCodesBitField2& note_codes_bit_field_2();
    void set_note_codes_bit_field_2(const NoteCodesBitField2& value);

    // Note Codes Bit Field 3: Note codes, logical Or is used to identify multiple note codes
    const NoteCodesBitField3& note_codes_bit_field_3() const;
    NoteCodesBitField3& note_codes_bit_field_3();
    void set_note_codes_bit_field_3(const NoteCodesBitField3& value);

    // Note Codes Bit Field 4: Note codes, logical Or is used to identify multiple note codes
    const NoteCodesBitField4& note_codes_bit_field_4() const;
    NoteCodesBitField4& note_codes_bit_field_4();
    void set_note_codes_bit_field_4(const NoteCodesBitField4& value);

    // Note Codes Bit Field 5: Note codes, logical Or is used to identify multiple note codes
    const NoteCodesBitField5& note_codes_bit_field_5() const;
    NoteCodesBitField5& note_codes_bit_field_5();
    void set_note_codes_bit_field_5(const NoteCodesBitField5& value);

    // Note Codes Bit Field 6: Note codes, logical Or is used to identify multiple note codes
    const NoteCodesBitField6& note_codes_bit_field_6() const;
    NoteCodesBitField6& note_codes_bit_field_6();
    void set_note_codes_bit_field_6(const NoteCodesBitField6& value);

    // Note Codes Bit Field 7: Note codes, logical Or is used to identify multiple note codes
    const NoteCodesBitField7& note_codes_bit_field_7() const;
    NoteCodesBitField7& note_codes_bit_field_7();
    void set_note_codes_bit_field_7(const NoteCodesBitField7& value);

    // Note Codes Bit Field 8: Note codes, logical Or is used to identify multiple note codes
    const NoteCodesBitField8& note_codes_bit_field_8() const;
    NoteCodesBitField8& note_codes_bit_field_8();
    void set_note_codes_bit_field_8(const NoteCodesBitField8& value);

    // Round Lot Size: Number of shares representing a round lot
    std::uint32_t round_lot_size() const;
    void set_round_lot_size(std::uint32_t value);

    // Nordic Mid Mic: Venue Mic if a Nordic At Mid order book applies
    const std::string& nordic_mid_mic() const;
    std::string& nordic_mid_mic();
    void set_nordic_mid_mic(const std::string& value);

    // Aod Mic: Venue Mic if an auction on demand order book applies
    const std::string& aod_mic() const;
    std::string& aod_mic();
    void set_aod_mic(const std::string& value);

    // Notation Of Qty: Measurement units the quantity is expressed in
    const std::string& notation_of_qty() const;
    std::string& notation_of_qty();
    void set_notation_of_qty(const std::string& value);

    // Notional Amount: Notional amount if specified
    Decimal notional_amount() const;
    void set_notional_amount(Decimal value);

    // Currency: Currency of the notional amount
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Price Notation: Populated with M if price is monetary value
    PriceNotation price_notation() const;
    void set_price_notation(PriceNotation value);

    // Multiplier For Calculating Quantity In Measurement Unit: Multiplier to calculate
    // quantity in measurement units
    Decimal multiplier_for_calculating_quantity_in_measurement_unit() const;
    void set_multiplier_for_calculating_quantity_in_measurement_unit(Decimal value);

    // Pure Stream Mic: Venue Mic if a PureStream order book applies
    const std::string& pure_stream_mic() const;
    std::string& pure_stream_mic();
    void set_pure_stream_mic(const std::string& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const OrderBookDirectoryMessage& other) const;
    bool operator!=(const OrderBookDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint32_t order_book_{};
    std::string symbol_{};
    std::string isin_{};
    FinancialProduct financial_product_{};
    std::string trading_currency_{};
    std::string mic_{};
    std::uint16_t market_segment_id_{};
    NoteCodesBitField1 note_codes_bit_field_1_{};
    NoteCodesBitField2 note_codes_bit_field_2_{};
    NoteCodesBitField3 note_codes_bit_field_3_{};
    NoteCodesBitField4 note_codes_bit_field_4_{};
    NoteCodesBitField5 note_codes_bit_field_5_{};
    NoteCodesBitField6 note_codes_bit_field_6_{};
    NoteCodesBitField7 note_codes_bit_field_7_{};
    NoteCodesBitField8 note_codes_bit_field_8_{};
    std::uint32_t round_lot_size_{};
    std::string nordic_mid_mic_{};
    std::string aod_mic_{};
    std::string notation_of_qty_{};
    Decimal notional_amount_{ 0, -5 };
    std::string currency_{};
    PriceNotation price_notation_{};
    Decimal multiplier_for_calculating_quantity_in_measurement_unit_{ 0, -6 };
    std::string pure_stream_mic_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
