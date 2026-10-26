#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Nyse.NyseConsolidated.DailyTaqNbbo.Csv.v4.3: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace nyse::nyseconsolidated::dailytaqnbbo::csv::v4_3 {

// Nbbo: a data line of the model, its fields typed as the model states them
struct Nbbo {
    // Time: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> time;
    // Exchange: text
    ::scaled::delimited::values::Required<std::string_view> exchange;
    // Symbol: text
    ::scaled::delimited::values::Required<std::string_view> symbol;
    // Bid_Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> bid_price;
    static constexpr int bid_price_places = 6;
    // Bid_Size: an integer
    ::scaled::delimited::values::Required<std::int64_t> bid_size;
    // Offer_Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> offer_price;
    static constexpr int offer_price_places = 6;
    // Offer_Size: an integer
    ::scaled::delimited::values::Required<std::int64_t> offer_size;
    // Quote_Condition: text
    ::scaled::delimited::values::Required<std::string_view> quote_condition;
    // Sequence_Number: an integer
    ::scaled::delimited::values::Required<std::int64_t> sequence_number;
    // National_BBO_Ind: text
    ::scaled::delimited::values::Required<std::string_view> national_bbo_ind;
    // FINRA_BBO_Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> finra_bbo_indicator;
    // FINRA_ADF_MPID_Indicator: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> finra_adf_mpid_indicator;
    // Quote_Cancel_Correction: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> quote_cancel_correction;
    // Source_Of_Quote: text
    ::scaled::delimited::values::Required<std::string_view> source_of_quote;
    // Best Bid Quote Condition: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> best_bid_quote_condition;
    // Best_Bid_Exchange: text
    ::scaled::delimited::values::Required<std::string_view> best_bid_exchange;
    // Best_Bid_Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> best_bid_price;
    static constexpr int best_bid_price_places = 6;
    // Best_Bid_Size: an integer
    ::scaled::delimited::values::Required<std::int64_t> best_bid_size;
    // Best_Bid_FINRA_Market_Maker_ID: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> best_bid_finra_market_maker_id;
    // Best_Offer_Quote_Condition: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> best_offer_quote_condition;
    // Best_Offer_Exchange: text
    ::scaled::delimited::values::Required<std::string_view> best_offer_exchange;
    // Best_Offer_Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> best_offer_price;
    static constexpr int best_offer_price_places = 6;
    // Best_Offer_Size: an integer
    ::scaled::delimited::values::Required<std::int64_t> best_offer_size;
    // Best_Offer_FINRA_Market_Maker_ID: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> best_offer_finra_market_maker_id;
    // LULD_Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> luld_indicator;
    // LULD_NBBO_Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> luld_nbbo_indicator;
    // SIP_Generated_Message_Identifier: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> sip_generated_message_identifier;
    // Participant_Timestamp: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> participant_timestamp;
    // FINRA_ADF_Timestamp: nanoseconds since midnight, America/New_York; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::uint64_t> finra_adf_timestamp;
    // Security_Status_Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> security_status_indicator;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        time.reset();
        exchange.reset();
        symbol.reset();
        bid_price.reset();
        bid_size.reset();
        offer_price.reset();
        offer_size.reset();
        quote_condition.reset();
        sequence_number.reset();
        national_bbo_ind.reset();
        finra_bbo_indicator.reset();
        finra_adf_mpid_indicator.reset();
        quote_cancel_correction.reset();
        source_of_quote.reset();
        best_bid_quote_condition.reset();
        best_bid_exchange.reset();
        best_bid_price.reset();
        best_bid_size.reset();
        best_bid_finra_market_maker_id.reset();
        best_offer_quote_condition.reset();
        best_offer_exchange.reset();
        best_offer_price.reset();
        best_offer_size.reset();
        best_offer_finra_market_maker_id.reset();
        luld_indicator.reset();
        luld_nbbo_indicator.reset();
        sip_generated_message_identifier.reset();
        participant_timestamp.reset();
        finra_adf_timestamp.reset();
        security_status_indicator.reset();
    }

    // Time on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t time_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time.value()));
    }

    // Participant_Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t participant_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(participant_timestamp.value()));
    }

    // FINRA_ADF_Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds;
    // none where the line leaves it empty
    std::optional<std::int64_t> finra_adf_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        if (!finra_adf_timestamp.has_value()) {
            return std::nullopt;
        }
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(finra_adf_timestamp.value()));
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "Nbbo{";
        out << "time=";
        ::scaled::delimited::values::print(out, time, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", exchange=";
        ::scaled::delimited::values::print(out, exchange, ::scaled::delimited::values::text);
        out << ", symbol=";
        ::scaled::delimited::values::print(out, symbol, ::scaled::delimited::values::text);
        out << ", bid_price=";
        ::scaled::delimited::values::print(out, bid_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, bid_price_places); });
        out << ", bid_size=";
        ::scaled::delimited::values::print(out, bid_size, ::scaled::delimited::values::integer);
        out << ", offer_price=";
        ::scaled::delimited::values::print(out, offer_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, offer_price_places); });
        out << ", offer_size=";
        ::scaled::delimited::values::print(out, offer_size, ::scaled::delimited::values::integer);
        out << ", quote_condition=";
        ::scaled::delimited::values::print(out, quote_condition, ::scaled::delimited::values::text);
        out << ", sequence_number=";
        ::scaled::delimited::values::print(out, sequence_number, ::scaled::delimited::values::integer);
        out << ", national_bbo_ind=";
        ::scaled::delimited::values::print(out, national_bbo_ind, ::scaled::delimited::values::text);
        out << ", finra_bbo_indicator=";
        ::scaled::delimited::values::print(out, finra_bbo_indicator, ::scaled::delimited::values::text);
        out << ", finra_adf_mpid_indicator=";
        ::scaled::delimited::values::print(out, finra_adf_mpid_indicator, ::scaled::delimited::values::integer);
        out << ", quote_cancel_correction=";
        ::scaled::delimited::values::print(out, quote_cancel_correction, ::scaled::delimited::values::text);
        out << ", source_of_quote=";
        ::scaled::delimited::values::print(out, source_of_quote, ::scaled::delimited::values::text);
        out << ", best_bid_quote_condition=";
        ::scaled::delimited::values::print(out, best_bid_quote_condition, ::scaled::delimited::values::text);
        out << ", best_bid_exchange=";
        ::scaled::delimited::values::print(out, best_bid_exchange, ::scaled::delimited::values::text);
        out << ", best_bid_price=";
        ::scaled::delimited::values::print(out, best_bid_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, best_bid_price_places); });
        out << ", best_bid_size=";
        ::scaled::delimited::values::print(out, best_bid_size, ::scaled::delimited::values::integer);
        out << ", best_bid_finra_market_maker_id=";
        ::scaled::delimited::values::print(out, best_bid_finra_market_maker_id, ::scaled::delimited::values::text);
        out << ", best_offer_quote_condition=";
        ::scaled::delimited::values::print(out, best_offer_quote_condition, ::scaled::delimited::values::text);
        out << ", best_offer_exchange=";
        ::scaled::delimited::values::print(out, best_offer_exchange, ::scaled::delimited::values::text);
        out << ", best_offer_price=";
        ::scaled::delimited::values::print(out, best_offer_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, best_offer_price_places); });
        out << ", best_offer_size=";
        ::scaled::delimited::values::print(out, best_offer_size, ::scaled::delimited::values::integer);
        out << ", best_offer_finra_market_maker_id=";
        ::scaled::delimited::values::print(out, best_offer_finra_market_maker_id, ::scaled::delimited::values::text);
        out << ", luld_indicator=";
        ::scaled::delimited::values::print(out, luld_indicator, ::scaled::delimited::values::text);
        out << ", luld_nbbo_indicator=";
        ::scaled::delimited::values::print(out, luld_nbbo_indicator, ::scaled::delimited::values::text);
        out << ", sip_generated_message_identifier=";
        ::scaled::delimited::values::print(out, sip_generated_message_identifier, ::scaled::delimited::values::text);
        out << ", participant_timestamp=";
        ::scaled::delimited::values::print(out, participant_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", finra_adf_timestamp=";
        ::scaled::delimited::values::print(out, finra_adf_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", security_status_indicator=";
        ::scaled::delimited::values::print(out, security_status_indicator, ::scaled::delimited::values::text);
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const Nbbo& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = Nbbo;

}