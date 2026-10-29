#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqQuotes.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqquotes::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 23;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqQuotes.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqquotes_v4_3 {

    // Layout: Time|Exchange|Symbol|Bid_Price|Bid_Size|Offer_Price|Offer_Size|Quote_Condition|Sequence_Number|National_BBO_Ind|FINRA_BBO_Indicator|FINRA_ADF_MPID_Indicator|Quote_Cancel_Correction|Source_Of_Quote|Retail_Interest_Indicator|Short_Sale_Restriction_Indicator|LULD_BBO_Indicator|SIP_Generated_Message_Identifier|National_BBO_LULD_Indicator|Participant_Timestamp|FINRA_ADF_Timestamp|FINRA_ADF_Market_Participant_Quote_Indicator|Security_Status_Indicator
    constexpr std::array<std::string_view, 23> layout{ "Time", "Exchange", "Symbol", "Bid_Price", "Bid_Size", "Offer_Price", "Offer_Size", "Quote_Condition", "Sequence_Number", "National_BBO_Ind", "FINRA_BBO_Indicator", "FINRA_ADF_MPID_Indicator", "Quote_Cancel_Correction", "Source_Of_Quote", "Retail_Interest_Indicator", "Short_Sale_Restriction_Indicator", "LULD_BBO_Indicator", "SIP_Generated_Message_Identifier", "National_BBO_LULD_Indicator", "Participant_Timestamp", "FINRA_ADF_Timestamp", "FINRA_ADF_Market_Participant_Quote_Indicator", "Security_Status_Indicator" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Quote: a line of 23 fields, onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 23, "Quote");
        row.time.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[0], 9, "Time")));  // Time
        row.exchange.set(fields[1]);  // Exchange
        row.symbol.set(fields[2]);  // Symbol
        row.bid_price.data = ::scaled::delimited::decimal(fields[3], 6, "Bid_Price");  // Bid_Price
        row.bid_size.set(::scaled::delimited::integer<std::int64_t>(fields[4], "Bid_Size"));  // Bid_Size
        row.offer_price.data = ::scaled::delimited::decimal(fields[5], 6, "Offer_Price");  // Offer_Price
        row.offer_size.set(::scaled::delimited::integer<std::int64_t>(fields[6], "Offer_Size"));  // Offer_Size
        row.quote_condition.set(fields[7]);  // Quote_Condition
        row.sequence_number.set(::scaled::delimited::integer<std::int64_t>(fields[8], "Sequence_Number"));  // Sequence_Number
        row.national_bbo_ind.set(fields[9]);  // National_BBO_Ind
        if (!fields[10].empty()) {  // FINRA_BBO_Indicator
            row.finra_bbo_indicator.set(fields[10]);
        }
        if (!fields[11].empty()) {  // FINRA_ADF_MPID_Indicator
            row.finra_adf_mpid_indicator.set(::scaled::delimited::integer<std::int64_t>(fields[11], "FINRA_ADF_MPID_Indicator"));
        }
        if (!fields[12].empty()) {  // Quote_Cancel_Correction
            row.quote_cancel_correction.set(fields[12]);
        }
        row.source_of_quote.set(fields[13]);  // Source_Of_Quote
        if (!fields[14].empty()) {  // Retail_Interest_Indicator
            row.retail_interest_indicator.set(fields[14]);
        }
        if (!fields[15].empty()) {  // Short_Sale_Restriction_Indicator
            row.short_sale_restriction_indicator.set(fields[15]);
        }
        if (!fields[16].empty()) {  // LULD_BBO_Indicator
            row.luld_bbo_indicator.set(fields[16]);
        }
        if (!fields[17].empty()) {  // SIP_Generated_Message_Identifier
            row.sip_generated_message_identifier.set(fields[17]);
        }
        if (!fields[18].empty()) {  // National_BBO_LULD_Indicator
            row.national_bbo_luld_indicator.set(fields[18]);
        }
        row.participant_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[19], 9, "Participant_Timestamp")));  // Participant_Timestamp
        if (!fields[20].empty()) {  // FINRA_ADF_Timestamp
            row.finra_adf_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[20], 9, "FINRA_ADF_Timestamp")));
        }
        if (!fields[21].empty()) {  // FINRA_ADF_Market_Participant_Quote_Indicator
            row.finra_adf_market_participant_quote_indicator.set(fields[21]);
        }
        if (!fields[22].empty()) {  // Security_Status_Indicator
            row.security_status_indicator.set(fields[22]);
        }
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqQuotes.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqquotes_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqQuotes.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqquotes_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}