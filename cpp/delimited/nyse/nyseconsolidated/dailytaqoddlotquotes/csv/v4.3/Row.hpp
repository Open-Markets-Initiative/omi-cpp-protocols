#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Nyse.NyseConsolidated.DailyTaqOddLotQuotes.Csv.v4.3: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace nyse::nyseconsolidated::dailytaqoddlotquotes::csv::v4_3 {

// Odd Lot Quote: a data line of the model, its fields typed as the model states them
struct OddLotQuote {
    // Time: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> time;
    // Exchange: text
    ::scaled::delimited::values::Required<std::string_view> exchange;
    // Symbol: text
    ::scaled::delimited::values::Required<std::string_view> symbol;
    // Sequence Number: an integer
    ::scaled::delimited::values::Required<std::int64_t> sequence_number;
    // Participant Timestamp: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> participant_timestamp;
    // FINRA ADF Timestamp: nanoseconds since midnight, America/New_York; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::uint64_t> finra_adf_timestamp;
    // Source of Quote: text
    ::scaled::delimited::values::Required<std::string_view> source_of_quote;
    // BOLO Indicator: text
    ::scaled::delimited::values::Required<std::string_view> bolo_indicator;
    // Clear Prior Odd Lot Quotes: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> clear_prior_odd_lot_quotes;
    // Side: text
    ::scaled::delimited::values::Required<std::string_view> side;
    // Odd Lot Quote Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> odd_lot_quote_price;
    static constexpr int odd_lot_quote_price_places = 6;
    // Odd Lot Quote Size: an integer
    ::scaled::delimited::values::Required<std::int64_t> odd_lot_quote_size;
    // Odd Lot FINRA Market Maker ID: text
    ::scaled::delimited::values::Required<std::string_view> odd_lot_finra_market_maker_id;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        time.reset();
        exchange.reset();
        symbol.reset();
        sequence_number.reset();
        participant_timestamp.reset();
        finra_adf_timestamp.reset();
        source_of_quote.reset();
        bolo_indicator.reset();
        clear_prior_odd_lot_quotes.reset();
        side.reset();
        odd_lot_quote_price.reset();
        odd_lot_quote_size.reset();
        odd_lot_finra_market_maker_id.reset();
    }

    // Time on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t time_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time.value()));
    }

    // Participant Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t participant_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(participant_timestamp.value()));
    }

    // FINRA ADF Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds;
    // none where the line leaves it empty
    std::optional<std::int64_t> finra_adf_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        if (!finra_adf_timestamp.has_value()) {
            return std::nullopt;
        }
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(finra_adf_timestamp.value()));
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "OddLotQuote{";
        out << "time=";
        ::scaled::delimited::values::print(out, time, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", exchange=";
        ::scaled::delimited::values::print(out, exchange, ::scaled::delimited::values::text);
        out << ", symbol=";
        ::scaled::delimited::values::print(out, symbol, ::scaled::delimited::values::text);
        out << ", sequence_number=";
        ::scaled::delimited::values::print(out, sequence_number, ::scaled::delimited::values::integer);
        out << ", participant_timestamp=";
        ::scaled::delimited::values::print(out, participant_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", finra_adf_timestamp=";
        ::scaled::delimited::values::print(out, finra_adf_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", source_of_quote=";
        ::scaled::delimited::values::print(out, source_of_quote, ::scaled::delimited::values::text);
        out << ", bolo_indicator=";
        ::scaled::delimited::values::print(out, bolo_indicator, ::scaled::delimited::values::text);
        out << ", clear_prior_odd_lot_quotes=";
        ::scaled::delimited::values::print(out, clear_prior_odd_lot_quotes, ::scaled::delimited::values::text);
        out << ", side=";
        ::scaled::delimited::values::print(out, side, ::scaled::delimited::values::text);
        out << ", odd_lot_quote_price=";
        ::scaled::delimited::values::print(out, odd_lot_quote_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, odd_lot_quote_price_places); });
        out << ", odd_lot_quote_size=";
        ::scaled::delimited::values::print(out, odd_lot_quote_size, ::scaled::delimited::values::integer);
        out << ", odd_lot_finra_market_maker_id=";
        ::scaled::delimited::values::print(out, odd_lot_finra_market_maker_id, ::scaled::delimited::values::text);
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const OddLotQuote& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = OddLotQuote;

}