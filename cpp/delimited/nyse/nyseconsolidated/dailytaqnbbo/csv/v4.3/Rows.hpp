#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqNbbo.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqnbbo::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 30;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqNbbo.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqnbbo_v4_3 {

    // Layout: Time|Exchange|Symbol|Bid_Price|Bid_Size|Offer_Price|Offer_Size|Quote_Condition|Sequence_Number|National_BBO_Ind|FINRA_BBO_Indicator|FINRA_ADF_MPID_Indicator|Quote_Cancel_Correction|Source_Of_Quote|Best Bid Quote Condition|Best_Bid_Exchange|Best_Bid_Price|Best_Bid_Size|Best_Bid_FINRA_Market_Maker_ID|Best_Offer_Quote_Condition|Best_Offer_Exchange|Best_Offer_Price|Best_Offer_Size|Best_Offer_FINRA_Market_Maker_ID|LULD_Indicator|LULD_NBBO_Indicator|SIP_Generated_Message_Identifier|Participant_Timestamp|FINRA_ADF_Timestamp|Security_Status_Indicator
    constexpr std::array<std::string_view, 30> layout{ "Time", "Exchange", "Symbol", "Bid_Price", "Bid_Size", "Offer_Price", "Offer_Size", "Quote_Condition", "Sequence_Number", "National_BBO_Ind", "FINRA_BBO_Indicator", "FINRA_ADF_MPID_Indicator", "Quote_Cancel_Correction", "Source_Of_Quote", "Best Bid Quote Condition", "Best_Bid_Exchange", "Best_Bid_Price", "Best_Bid_Size", "Best_Bid_FINRA_Market_Maker_ID", "Best_Offer_Quote_Condition", "Best_Offer_Exchange", "Best_Offer_Price", "Best_Offer_Size", "Best_Offer_FINRA_Market_Maker_ID", "LULD_Indicator", "LULD_NBBO_Indicator", "SIP_Generated_Message_Identifier", "Participant_Timestamp", "FINRA_ADF_Timestamp", "Security_Status_Indicator" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Nbbo: a line of 30 fields, onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 30, "Nbbo");
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
        if (!fields[14].empty()) {  // Best Bid Quote Condition
            row.best_bid_quote_condition.set(fields[14]);
        }
        if (!fields[15].empty()) {  // Best_Bid_Exchange
            row.best_bid_exchange.set(fields[15]);
        }
        row.best_bid_price.data = ::scaled::delimited::decimal(fields[16], 6, "Best_Bid_Price");  // Best_Bid_Price
        row.best_bid_size.set(::scaled::delimited::integer<std::int64_t>(fields[17], "Best_Bid_Size"));  // Best_Bid_Size
        if (!fields[18].empty()) {  // Best_Bid_FINRA_Market_Maker_ID
            row.best_bid_finra_market_maker_id.set(fields[18]);
        }
        if (!fields[19].empty()) {  // Best_Offer_Quote_Condition
            row.best_offer_quote_condition.set(fields[19]);
        }
        if (!fields[20].empty()) {  // Best_Offer_Exchange
            row.best_offer_exchange.set(fields[20]);
        }
        row.best_offer_price.data = ::scaled::delimited::decimal(fields[21], 6, "Best_Offer_Price");  // Best_Offer_Price
        row.best_offer_size.set(::scaled::delimited::integer<std::int64_t>(fields[22], "Best_Offer_Size"));  // Best_Offer_Size
        if (!fields[23].empty()) {  // Best_Offer_FINRA_Market_Maker_ID
            row.best_offer_finra_market_maker_id.set(fields[23]);
        }
        if (!fields[24].empty()) {  // LULD_Indicator
            row.luld_indicator.set(fields[24]);
        }
        if (!fields[25].empty()) {  // LULD_NBBO_Indicator
            row.luld_nbbo_indicator.set(fields[25]);
        }
        if (!fields[26].empty()) {  // SIP_Generated_Message_Identifier
            row.sip_generated_message_identifier.set(fields[26]);
        }
        row.participant_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[27], 9, "Participant_Timestamp")));  // Participant_Timestamp
        if (!fields[28].empty()) {  // FINRA_ADF_Timestamp
            row.finra_adf_timestamp.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[28], 9, "FINRA_ADF_Timestamp")));
        }
        if (!fields[29].empty()) {  // Security_Status_Indicator
            row.security_status_indicator.set(fields[29]);
        }
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqNbbo.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqnbbo_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqNbbo.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqnbbo_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}