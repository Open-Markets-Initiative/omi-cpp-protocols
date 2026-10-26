#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqOddLotQuotes.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqoddlotquotes::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 13;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqOddLotQuotes.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqoddlotquotes_v4_3 {

    // Layout: Time|Exchange|Symbol|Sequence Number|Participant Timestamp|FINRA ADF Timestamp|Source of Quote|BOLO Indicator|Clear Prior Odd Lot Quotes|Side|Odd Lot Quote Price|Odd Lot Quote Size|Odd Lot FINRA Market Maker ID
    constexpr std::array<std::string_view, 13> layout{ "Time", "Exchange", "Symbol", "Sequence Number", "Participant Timestamp", "FINRA ADF Timestamp", "Source of Quote", "BOLO Indicator", "Clear Prior Odd Lot Quotes", "Side", "Odd Lot Quote Price", "Odd Lot Quote Size", "Odd Lot FINRA Market Maker ID" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Odd Lot Quote: a line of 13 fields, onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 13, "Odd Lot Quote");
        row.time.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[0], 9, "Time")));  // Time
        row.exchange.set(fields[1]);  // Exchange
        row.symbol.set(fields[2]);  // Symbol
        row.sequence_number.set(::scaled::delimited::integer<std::int64_t>(fields[3], "Sequence Number"));  // Sequence Number
        row.participant_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[4], 9, "Participant Timestamp")));  // Participant Timestamp
        if (!fields[5].empty()) {  // FINRA ADF Timestamp
            row.finra_adf_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[5], 9, "FINRA ADF Timestamp")));
        }
        row.source_of_quote.set(fields[6]);  // Source of Quote
        row.bolo_indicator.set(fields[7]);  // BOLO Indicator
        if (!fields[8].empty()) {  // Clear Prior Odd Lot Quotes
            row.clear_prior_odd_lot_quotes.set(fields[8]);
        }
        row.side.set(fields[9]);  // Side
        row.odd_lot_quote_price.data = ::scaled::delimited::decimal(fields[10], 6, "Odd Lot Quote Price");  // Odd Lot Quote Price
        row.odd_lot_quote_size.set(::scaled::delimited::integer<std::int64_t>(fields[11], "Odd Lot Quote Size"));  // Odd Lot Quote Size
        row.odd_lot_finra_market_maker_id.set(fields[12]);  // Odd Lot FINRA Market Maker ID
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqOddLotQuotes.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqoddlotquotes_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqOddLotQuotes.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqoddlotquotes_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}