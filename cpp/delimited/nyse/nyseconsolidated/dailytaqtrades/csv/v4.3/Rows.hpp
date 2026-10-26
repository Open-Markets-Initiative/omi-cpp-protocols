#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqTrades.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqtrades::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 15;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqTrades.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqtrades_v4_3 {

    // Layout: Time|Exchange|Symbol|Sale Condition|Trade Volume|Trade Price|Trade Stop Stock Indicator|Trade Correction Indicator|Sequence Number|Trade Id|Source of Trade|Trade Reporting Facility|Participant Timestamp|Trade Reporting Facility TRF Timestamp|Trade Through Exempt Indicator
    constexpr std::array<std::string_view, 15> layout{ "Time", "Exchange", "Symbol", "Sale Condition", "Trade Volume", "Trade Price", "Trade Stop Stock Indicator", "Trade Correction Indicator", "Sequence Number", "Trade Id", "Source of Trade", "Trade Reporting Facility", "Participant Timestamp", "Trade Reporting Facility TRF Timestamp", "Trade Through Exempt Indicator" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Trade: a line of 15 fields, onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 15, "Trade");
        row.time.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[0], 9, "Time")));  // Time
        row.exchange.set(fields[1]);  // Exchange
        row.symbol.set(fields[2]);  // Symbol
        if (!fields[3].empty()) {  // Sale Condition
            row.sale_condition.set(fields[3]);
        }
        row.trade_volume.data = ::scaled::delimited::decimal(fields[4], 6, "Trade Volume");  // Trade Volume
        row.trade_price.data = ::scaled::delimited::decimal(fields[5], 6, "Trade Price");  // Trade Price
        if (!fields[6].empty()) {  // Trade Stop Stock Indicator
            row.trade_stop_stock_indicator.set(fields[6]);
        }
        row.trade_correction_indicator.set(fields[7]);  // Trade Correction Indicator
        row.sequence_number.set(::scaled::delimited::integer<std::int64_t>(fields[8], "Sequence Number"));  // Sequence Number
        row.trade_id.set(fields[9]);  // Trade Id
        row.source_of_trade.set(fields[10]);  // Source of Trade
        if (!fields[11].empty()) {  // Trade Reporting Facility
            row.trade_reporting_facility.set(fields[11]);
        }
        row.participant_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[12], 9, "Participant Timestamp")));  // Participant Timestamp
        if (!fields[13].empty()) {  // Trade Reporting Facility TRF Timestamp
            row.trade_reporting_facility_trf_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[13], 9, "Trade Reporting Facility TRF Timestamp")));
        }
        row.trade_through_exempt_indicator.set(::scaled::delimited::integer<std::int64_t>(fields[14], "Trade Through Exempt Indicator"));  // Trade Through Exempt Indicator
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqTrades.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqtrades_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqTrades.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqtrades_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}