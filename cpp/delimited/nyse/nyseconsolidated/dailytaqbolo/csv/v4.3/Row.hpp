#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Nyse.NyseConsolidated.DailyTaqBolo.Csv.v4.3: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace nyse::nyseconsolidated::dailytaqbolo::csv::v4_3 {

// Bolo: a data line of the model, its fields typed as the model states them
struct Bolo {
    // Time: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> time;
    // Symbol: text
    ::scaled::delimited::values::Required<std::string_view> symbol;
    // Sequence Number: an integer
    ::scaled::delimited::values::Required<std::int64_t> sequence_number;
    // Source of Quote: text
    ::scaled::delimited::values::Required<std::string_view> source_of_quote;
    // SIP-generated Message Identifier: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> sip_generated_message_identifier;
    // BOLO Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> bolo_indicator;
    // Odd Lot Best Bid Participant ID: text
    ::scaled::delimited::values::Required<std::string_view> odd_lot_best_bid_participant_id;
    // Odd Lot Best Bid Quote Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> odd_lot_best_bid_quote_price;
    static constexpr int odd_lot_best_bid_quote_price_places = 6;
    // Odd Lot Best Bid Quote Size: an integer
    ::scaled::delimited::values::Required<std::int64_t> odd_lot_best_bid_quote_size;
    // Odd Lot FINRA Best Bid Market Maker ID: text
    ::scaled::delimited::values::Required<std::string_view> odd_lot_finra_best_bid_market_maker_id;
    // Odd Lot Best Offer Participant ID: text
    ::scaled::delimited::values::Required<std::string_view> odd_lot_best_offer_participant_id;
    // Odd Lot Best Offer Quote Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> odd_lot_best_offer_quote_price;
    static constexpr int odd_lot_best_offer_quote_price_places = 6;
    // Odd Lot Best Offer Quote Size: an integer
    ::scaled::delimited::values::Required<std::int64_t> odd_lot_best_offer_quote_size;
    // Odd Lot FINRA Best Offer Market Maker ID: text
    ::scaled::delimited::values::Required<std::string_view> odd_lot_finra_best_offer_market_maker_id;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        time.reset();
        symbol.reset();
        sequence_number.reset();
        source_of_quote.reset();
        sip_generated_message_identifier.reset();
        bolo_indicator.reset();
        odd_lot_best_bid_participant_id.reset();
        odd_lot_best_bid_quote_price.reset();
        odd_lot_best_bid_quote_size.reset();
        odd_lot_finra_best_bid_market_maker_id.reset();
        odd_lot_best_offer_participant_id.reset();
        odd_lot_best_offer_quote_price.reset();
        odd_lot_best_offer_quote_size.reset();
        odd_lot_finra_best_offer_market_maker_id.reset();
    }

    // Time on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t time_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time.value()));
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "Bolo{";
        out << "time=";
        ::scaled::delimited::values::print(out, time, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", symbol=";
        ::scaled::delimited::values::print(out, symbol, ::scaled::delimited::values::text);
        out << ", sequence_number=";
        ::scaled::delimited::values::print(out, sequence_number, ::scaled::delimited::values::integer);
        out << ", source_of_quote=";
        ::scaled::delimited::values::print(out, source_of_quote, ::scaled::delimited::values::text);
        out << ", sip_generated_message_identifier=";
        ::scaled::delimited::values::print(out, sip_generated_message_identifier, ::scaled::delimited::values::text);
        out << ", bolo_indicator=";
        ::scaled::delimited::values::print(out, bolo_indicator, ::scaled::delimited::values::text);
        out << ", odd_lot_best_bid_participant_id=";
        ::scaled::delimited::values::print(out, odd_lot_best_bid_participant_id, ::scaled::delimited::values::text);
        out << ", odd_lot_best_bid_quote_price=";
        ::scaled::delimited::values::print(out, odd_lot_best_bid_quote_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, odd_lot_best_bid_quote_price_places); });
        out << ", odd_lot_best_bid_quote_size=";
        ::scaled::delimited::values::print(out, odd_lot_best_bid_quote_size, ::scaled::delimited::values::integer);
        out << ", odd_lot_finra_best_bid_market_maker_id=";
        ::scaled::delimited::values::print(out, odd_lot_finra_best_bid_market_maker_id, ::scaled::delimited::values::text);
        out << ", odd_lot_best_offer_participant_id=";
        ::scaled::delimited::values::print(out, odd_lot_best_offer_participant_id, ::scaled::delimited::values::text);
        out << ", odd_lot_best_offer_quote_price=";
        ::scaled::delimited::values::print(out, odd_lot_best_offer_quote_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, odd_lot_best_offer_quote_price_places); });
        out << ", odd_lot_best_offer_quote_size=";
        ::scaled::delimited::values::print(out, odd_lot_best_offer_quote_size, ::scaled::delimited::values::integer);
        out << ", odd_lot_finra_best_offer_market_maker_id=";
        ::scaled::delimited::values::print(out, odd_lot_finra_best_offer_market_maker_id, ::scaled::delimited::values::text);
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const Bolo& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = Bolo;

}