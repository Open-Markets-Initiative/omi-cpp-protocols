#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqUtpAdmin.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqutpadmin::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 23;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqUtpAdmin.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqutpadmin_v4_3 {

    // Layout: Timestamp|Symbol|Message Category|Message Type|Message Sequence Number|Market Center Originator ID|Sub Market Center Originator ID|Participant Timestamp|Financial Status|Short Sale Treshold Indicator|Short Sale Restriction Indicator|Trading Action Code|Trading Action Sequence Number|Trading Action Timestamp|Trading Action Reason|LULD Lower Limit Price Band|LULD Upper Limit Price Band|LULDPrice Band Indicator|Market Wide Circuit Breaker Decline Level 1|Market Wide Circuit Breaker Decline Level 2|Market Wide Circuit Breaker Decline Level 3|Market Wide Circuit Breaker Status|Message Text
    constexpr std::array<std::string_view, 23> layout{ "Timestamp", "Symbol", "Message Category", "Message Type", "Message Sequence Number", "Market Center Originator ID", "Sub Market Center Originator ID", "Participant Timestamp", "Financial Status", "Short Sale Treshold Indicator", "Short Sale Restriction Indicator", "Trading Action Code", "Trading Action Sequence Number", "Trading Action Timestamp", "Trading Action Reason", "LULD Lower Limit Price Band", "LULD Upper Limit Price Band", "LULDPrice Band Indicator", "Market Wide Circuit Breaker Decline Level 1", "Market Wide Circuit Breaker Decline Level 2", "Market Wide Circuit Breaker Decline Level 3", "Market Wide Circuit Breaker Status", "Message Text" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Utp Admin: a line of 23 fields, or as few as 6: its last 17 are optional, null where the line stops before them; onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 6, 23, "Utp Admin");
        row.timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[0], 9, "Timestamp")));  // Timestamp
        if (!fields[1].empty()) {  // Symbol
            row.symbol.set(fields[1]);
        }
        row.message_category.set(fields[2]);  // Message Category
        row.message_type.set(fields[3]);  // Message Type
        row.message_sequence_number.set(::scaled::delimited::integer<std::int64_t>(fields[4], "Message Sequence Number"));  // Message Sequence Number
        row.market_center_originator_id.set(fields[5]);  // Market Center Originator ID
        if (!::scaled::delimited::at(fields, 6).empty()) {  // Sub Market Center Originator ID
            row.sub_market_center_originator_id.set(::scaled::delimited::at(fields, 6));
        }
        if (!::scaled::delimited::at(fields, 7).empty()) {  // Participant Timestamp
            row.participant_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(::scaled::delimited::at(fields, 7), 9, "Participant Timestamp")));
        }
        if (!::scaled::delimited::at(fields, 8).empty()) {  // Financial Status
            row.financial_status.set(::scaled::delimited::at(fields, 8));
        }
        if (!::scaled::delimited::at(fields, 9).empty()) {  // Short Sale Treshold Indicator
            row.short_sale_treshold_indicator.set(::scaled::delimited::at(fields, 9));
        }
        if (!::scaled::delimited::at(fields, 10).empty()) {  // Short Sale Restriction Indicator
            row.short_sale_restriction_indicator.set(::scaled::delimited::integer<std::int64_t>(::scaled::delimited::at(fields, 10), "Short Sale Restriction Indicator"));
        }
        if (!::scaled::delimited::at(fields, 11).empty()) {  // Trading Action Code
            row.trading_action_code.set(::scaled::delimited::at(fields, 11));
        }
        if (!::scaled::delimited::at(fields, 12).empty()) {  // Trading Action Sequence Number
            row.trading_action_sequence_number.set(::scaled::delimited::integer<std::int64_t>(::scaled::delimited::at(fields, 12), "Trading Action Sequence Number"));
        }
        if (!::scaled::delimited::at(fields, 13).empty()) {  // Trading Action Timestamp
            row.trading_action_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(::scaled::delimited::at(fields, 13), 9, "Trading Action Timestamp")));
        }
        if (!::scaled::delimited::at(fields, 14).empty()) {  // Trading Action Reason
            row.trading_action_reason.set(::scaled::delimited::at(fields, 14));
        }
        if (!::scaled::delimited::at(fields, 15).empty()) {  // LULD Lower Limit Price Band
            row.luld_lower_limit_price_band.data = ::scaled::delimited::decimal(::scaled::delimited::at(fields, 15), 6, "LULD Lower Limit Price Band");
        }
        if (!::scaled::delimited::at(fields, 16).empty()) {  // LULD Upper Limit Price Band
            row.luld_upper_limit_price_band.data = ::scaled::delimited::decimal(::scaled::delimited::at(fields, 16), 6, "LULD Upper Limit Price Band");
        }
        if (!::scaled::delimited::at(fields, 17).empty()) {  // LULDPrice Band Indicator
            row.luldprice_band_indicator.set(::scaled::delimited::at(fields, 17));
        }
        if (!::scaled::delimited::at(fields, 18).empty()) {  // Market Wide Circuit Breaker Decline Level 1
            row.market_wide_circuit_breaker_decline_level_1.data = ::scaled::delimited::decimal(::scaled::delimited::at(fields, 18), 2, "Market Wide Circuit Breaker Decline Level 1");
        }
        if (!::scaled::delimited::at(fields, 19).empty()) {  // Market Wide Circuit Breaker Decline Level 2
            row.market_wide_circuit_breaker_decline_level_2.data = ::scaled::delimited::decimal(::scaled::delimited::at(fields, 19), 2, "Market Wide Circuit Breaker Decline Level 2");
        }
        if (!::scaled::delimited::at(fields, 20).empty()) {  // Market Wide Circuit Breaker Decline Level 3
            row.market_wide_circuit_breaker_decline_level_3.data = ::scaled::delimited::decimal(::scaled::delimited::at(fields, 20), 2, "Market Wide Circuit Breaker Decline Level 3");
        }
        if (!::scaled::delimited::at(fields, 21).empty()) {  // Market Wide Circuit Breaker Status
            row.market_wide_circuit_breaker_status.set(::scaled::delimited::integer<std::int64_t>(::scaled::delimited::at(fields, 21), "Market Wide Circuit Breaker Status"));
        }
        if (!::scaled::delimited::at(fields, 22).empty()) {  // Message Text
            row.message_text.set(::scaled::delimited::at(fields, 22));
        }
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqUtpAdmin.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqutpadmin_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqUtpAdmin.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqutpadmin_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}