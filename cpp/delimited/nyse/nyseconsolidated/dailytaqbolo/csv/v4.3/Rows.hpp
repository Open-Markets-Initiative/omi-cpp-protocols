#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqBolo.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqbolo::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 14;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqBolo.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqbolo_v4_3 {

    // Layout: Time|Symbol|Sequence Number|Source of Quote|SIP-generated Message Identifier|BOLO Indicator|Odd Lot Best Bid Participant ID|Odd Lot Best Bid Quote Price|Odd Lot Best Bid Quote Size|Odd Lot FINRA Best Bid Market Maker ID|Odd Lot Best Offer Participant ID|Odd Lot Best Offer Quote Price|Odd Lot Best Offer Quote Size|Odd Lot FINRA Best Offer Market Maker ID
    constexpr std::array<std::string_view, 14> layout{ "Time", "Symbol", "Sequence Number", "Source of Quote", "SIP-generated Message Identifier", "BOLO Indicator", "Odd Lot Best Bid Participant ID", "Odd Lot Best Bid Quote Price", "Odd Lot Best Bid Quote Size", "Odd Lot FINRA Best Bid Market Maker ID", "Odd Lot Best Offer Participant ID", "Odd Lot Best Offer Quote Price", "Odd Lot Best Offer Quote Size", "Odd Lot FINRA Best Offer Market Maker ID" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Bolo: a line of 14 fields, onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 14, "Bolo");
        row.time.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[0], 9, "Time")));  // Time
        row.symbol.set(fields[1]);  // Symbol
        row.sequence_number.set(::scaled::delimited::integer<std::int64_t>(fields[2], "Sequence Number"));  // Sequence Number
        row.source_of_quote.set(fields[3]);  // Source of Quote
        if (!fields[4].empty()) {  // SIP-generated Message Identifier
            row.sip_generated_message_identifier.set(fields[4]);
        }
        if (!fields[5].empty()) {  // BOLO Indicator
            row.bolo_indicator.set(fields[5]);
        }
        row.odd_lot_best_bid_participant_id.set(fields[6]);  // Odd Lot Best Bid Participant ID
        row.odd_lot_best_bid_quote_price.data = ::scaled::delimited::decimal(fields[7], 6, "Odd Lot Best Bid Quote Price");  // Odd Lot Best Bid Quote Price
        row.odd_lot_best_bid_quote_size.set(::scaled::delimited::integer<std::int64_t>(fields[8], "Odd Lot Best Bid Quote Size"));  // Odd Lot Best Bid Quote Size
        row.odd_lot_finra_best_bid_market_maker_id.set(fields[9]);  // Odd Lot FINRA Best Bid Market Maker ID
        row.odd_lot_best_offer_participant_id.set(fields[10]);  // Odd Lot Best Offer Participant ID
        row.odd_lot_best_offer_quote_price.data = ::scaled::delimited::decimal(fields[11], 6, "Odd Lot Best Offer Quote Price");  // Odd Lot Best Offer Quote Price
        row.odd_lot_best_offer_quote_size.set(::scaled::delimited::integer<std::int64_t>(fields[12], "Odd Lot Best Offer Quote Size"));  // Odd Lot Best Offer Quote Size
        row.odd_lot_finra_best_offer_market_maker_id.set(fields[13]);  // Odd Lot FINRA Best Offer Market Maker ID
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqBolo.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqbolo_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqBolo.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqbolo_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}