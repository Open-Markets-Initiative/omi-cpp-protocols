#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqCtaAdmin.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqctaadmin::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 26;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqCtaAdmin.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqctaadmin_v4_3 {

    // Layout: Timestamp|Symbol|Message Category|Message Type|Message Sequence Number|Participant Identifier|Participant Timestamp|Financial Status|Currency Indicator|Security Status|Halt Reason|Related Security Indicator|Common Indicator|Last Price|Status Indicator|High Indication Price/Upper Limit Price Band|Low Indication Price/LowerL imit Price Band|Buy Volume|Sell Volume|Short Sale Restriction Indicator|Limit Up/Limit Down Indicator|Market Wide Circuit Breaker Decline Level 1|Market Wide Circuit Breaker Decline Level 2|Market Wide Circuit Breaker Decline Level 3|Market Wide Circuit Breaker Status|Message Text
    constexpr std::array<std::string_view, 26> layout{ "Timestamp", "Symbol", "Message Category", "Message Type", "Message Sequence Number", "Participant Identifier", "Participant Timestamp", "Financial Status", "Currency Indicator", "Security Status", "Halt Reason", "Related Security Indicator", "Common Indicator", "Last Price", "Status Indicator", "High Indication Price/Upper Limit Price Band", "Low Indication Price/LowerL imit Price Band", "Buy Volume", "Sell Volume", "Short Sale Restriction Indicator", "Limit Up/Limit Down Indicator", "Market Wide Circuit Breaker Decline Level 1", "Market Wide Circuit Breaker Decline Level 2", "Market Wide Circuit Breaker Decline Level 3", "Market Wide Circuit Breaker Status", "Message Text" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Cta Admin: a line of 26 fields, onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 26, "Cta Admin");
        row.timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[0], 9, "Timestamp")));  // Timestamp
        if (!fields[1].empty()) {  // Symbol
            row.symbol.set(fields[1]);
        }
        row.message_category.set(fields[2]);  // Message Category
        row.message_type.set(fields[3]);  // Message Type
        row.message_sequence_number.set(::scaled::delimited::integer<std::int64_t>(fields[4], "Message Sequence Number"));  // Message Sequence Number
        row.participant_identifier.set(fields[5]);  // Participant Identifier
        row.participant_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[6], 9, "Participant Timestamp")));  // Participant Timestamp
        if (!fields[7].empty()) {  // Financial Status
            row.financial_status.set(fields[7]);
        }
        if (!fields[8].empty()) {  // Currency Indicator
            row.currency_indicator.set(fields[8]);
        }
        if (!fields[9].empty()) {  // Security Status
            row.security_status.set(fields[9]);
        }
        if (!fields[10].empty()) {  // Halt Reason
            row.halt_reason.set(fields[10]);
        }
        if (!fields[11].empty()) {  // Related Security Indicator
            row.related_security_indicator.set(fields[11]);
        }
        if (!fields[12].empty()) {  // Common Indicator
            row.common_indicator.set(fields[12]);
        }
        if (!fields[13].empty()) {  // Last Price
            row.last_price.data = ::scaled::delimited::decimal(fields[13], 6, "Last Price");
        }
        if (!fields[14].empty()) {  // Status Indicator
            row.status_indicator.set(fields[14]);
        }
        if (!fields[15].empty()) {  // High Indication Price/Upper Limit Price Band
            row.high_indication_price_upper_limit_price_band.data = ::scaled::delimited::decimal(fields[15], 6, "High Indication Price/Upper Limit Price Band");
        }
        if (!fields[16].empty()) {  // Low Indication Price/LowerL imit Price Band
            row.low_indication_price_lower_l_imit_price_band.data = ::scaled::delimited::decimal(fields[16], 6, "Low Indication Price/LowerL imit Price Band");
        }
        if (!fields[17].empty()) {  // Buy Volume
            row.buy_volume.set(::scaled::delimited::integer<std::int64_t>(fields[17], "Buy Volume"));
        }
        if (!fields[18].empty()) {  // Sell Volume
            row.sell_volume.set(::scaled::delimited::integer<std::int64_t>(fields[18], "Sell Volume"));
        }
        if (!fields[19].empty()) {  // Short Sale Restriction Indicator
            row.short_sale_restriction_indicator.set(fields[19]);
        }
        if (!fields[20].empty()) {  // Limit Up/Limit Down Indicator
            row.limit_up_limit_down_indicator.set(fields[20]);
        }
        if (!fields[21].empty()) {  // Market Wide Circuit Breaker Decline Level 1
            row.market_wide_circuit_breaker_decline_level_1.data = ::scaled::delimited::decimal(fields[21], 2, "Market Wide Circuit Breaker Decline Level 1");
        }
        if (!fields[22].empty()) {  // Market Wide Circuit Breaker Decline Level 2
            row.market_wide_circuit_breaker_decline_level_2.data = ::scaled::delimited::decimal(fields[22], 2, "Market Wide Circuit Breaker Decline Level 2");
        }
        if (!fields[23].empty()) {  // Market Wide Circuit Breaker Decline Level 3
            row.market_wide_circuit_breaker_decline_level_3.data = ::scaled::delimited::decimal(fields[23], 2, "Market Wide Circuit Breaker Decline Level 3");
        }
        if (!fields[24].empty()) {  // Market Wide Circuit Breaker Status
            row.market_wide_circuit_breaker_status.set(fields[24]);
        }
        if (!fields[25].empty()) {  // Message Text
            row.message_text.set(fields[25]);
        }
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqCtaAdmin.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqctaadmin_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqCtaAdmin.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqctaadmin_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}