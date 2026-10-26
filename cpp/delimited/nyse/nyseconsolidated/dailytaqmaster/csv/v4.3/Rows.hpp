#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqMaster.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqmaster::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 41;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqMaster.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqmaster_v4_3 {

    // Layout: Symbol|Security_Description|CUSIP|Security_Type|SIP_Symbol|Old_Symbol|Test_Symbol_Flag|Listed_Exchange|Tape|Unit_Of_Trade|Round_Lot|NYSE_Industry_Code|Shares_Outstanding|Halt_Delay_Reason|Specialist_Clearing_Agent|Specialist_Clearing_Number|Specialist_Post_Number|Specialist_Panel|TradedOnNYSEMKT|TradedOnNASDAQBX|TradedOnNSX|TradedOnFINRA|TradedOnISE|TradedOnEdgeA|TradedOnEdgeX|TradedOnNYSETexas|TradedOnNYSE|TradedOnArca|TradedOnNasdaq|TradedOnCBOE|TradedOnPSX|TradedOnBATSY|TradedOnBATS|TradedOnIEX|Tick_Pilot_Indicator|Effective_Date|TradedOnLTSE|TradedOnMEMX|TradedOnMIAX|TradedOn24X|TradedOnTXSE
    constexpr std::array<std::string_view, 41> layout{ "Symbol", "Security_Description", "CUSIP", "Security_Type", "SIP_Symbol", "Old_Symbol", "Test_Symbol_Flag", "Listed_Exchange", "Tape", "Unit_Of_Trade", "Round_Lot", "NYSE_Industry_Code", "Shares_Outstanding", "Halt_Delay_Reason", "Specialist_Clearing_Agent", "Specialist_Clearing_Number", "Specialist_Post_Number", "Specialist_Panel", "TradedOnNYSEMKT", "TradedOnNASDAQBX", "TradedOnNSX", "TradedOnFINRA", "TradedOnISE", "TradedOnEdgeA", "TradedOnEdgeX", "TradedOnNYSETexas", "TradedOnNYSE", "TradedOnArca", "TradedOnNasdaq", "TradedOnCBOE", "TradedOnPSX", "TradedOnBATSY", "TradedOnBATS", "TradedOnIEX", "Tick_Pilot_Indicator", "Effective_Date", "TradedOnLTSE", "TradedOnMEMX", "TradedOnMIAX", "TradedOn24X", "TradedOnTXSE" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Security: a line of 41 fields, onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 41, "Security");
        row.symbol.set(fields[0]);  // Symbol
        row.security_description.set(fields[1]);  // Security_Description
        if (!fields[2].empty()) {  // CUSIP
            row.cusip.set(fields[2]);
        }
        row.security_type.set(fields[3]);  // Security_Type
        row.sip_symbol.set(fields[4]);  // SIP_Symbol
        if (!fields[5].empty()) {  // Old_Symbol
            row.old_symbol.set(fields[5]);
        }
        row.test_symbol_flag.set(fields[6]);  // Test_Symbol_Flag
        row.listed_exchange.set(fields[7]);  // Listed_Exchange
        row.tape.set(fields[8]);  // Tape
        row.unit_of_trade.set(::scaled::delimited::integer<std::int64_t>(fields[9], "Unit_Of_Trade"));  // Unit_Of_Trade
        row.round_lot.set(::scaled::delimited::integer<std::int64_t>(fields[10], "Round_Lot"));  // Round_Lot
        if (!fields[11].empty()) {  // NYSE_Industry_Code
            row.nyse_industry_code.set(fields[11]);
        }
        if (!fields[12].empty()) {  // Shares_Outstanding
            row.shares_outstanding.data = ::scaled::delimited::decimal(fields[12], 2, "Shares_Outstanding");
        }
        if (!fields[13].empty()) {  // Halt_Delay_Reason
            row.halt_delay_reason.set(fields[13]);
        }
        if (!fields[14].empty()) {  // Specialist_Clearing_Agent
            row.specialist_clearing_agent.set(fields[14]);
        }
        if (!fields[15].empty()) {  // Specialist_Clearing_Number
            row.specialist_clearing_number.set(::scaled::delimited::integer<std::int64_t>(fields[15], "Specialist_Clearing_Number"));
        }
        if (!fields[16].empty()) {  // Specialist_Post_Number
            row.specialist_post_number.set(::scaled::delimited::integer<std::int64_t>(fields[16], "Specialist_Post_Number"));
        }
        if (!fields[17].empty()) {  // Specialist_Panel
            row.specialist_panel.set(fields[17]);
        }
        row.tradedonnysemkt.set(::scaled::delimited::integer<std::int64_t>(fields[18], "TradedOnNYSEMKT"));  // TradedOnNYSEMKT
        row.tradedonnasdaqbx.set(::scaled::delimited::integer<std::int64_t>(fields[19], "TradedOnNASDAQBX"));  // TradedOnNASDAQBX
        row.tradedonnsx.set(::scaled::delimited::integer<std::int64_t>(fields[20], "TradedOnNSX"));  // TradedOnNSX
        row.tradedonfinra.set(::scaled::delimited::integer<std::int64_t>(fields[21], "TradedOnFINRA"));  // TradedOnFINRA
        row.tradedonise.set(::scaled::delimited::integer<std::int64_t>(fields[22], "TradedOnISE"));  // TradedOnISE
        row.tradedonedgea.set(::scaled::delimited::integer<std::int64_t>(fields[23], "TradedOnEdgeA"));  // TradedOnEdgeA
        row.tradedonedgex.set(::scaled::delimited::integer<std::int64_t>(fields[24], "TradedOnEdgeX"));  // TradedOnEdgeX
        row.tradedonnysetexas.set(::scaled::delimited::integer<std::int64_t>(fields[25], "TradedOnNYSETexas"));  // TradedOnNYSETexas
        row.tradedonnyse.set(::scaled::delimited::integer<std::int64_t>(fields[26], "TradedOnNYSE"));  // TradedOnNYSE
        row.tradedonarca.set(::scaled::delimited::integer<std::int64_t>(fields[27], "TradedOnArca"));  // TradedOnArca
        row.tradedonnasdaq.set(::scaled::delimited::integer<std::int64_t>(fields[28], "TradedOnNasdaq"));  // TradedOnNasdaq
        row.tradedoncboe.set(::scaled::delimited::integer<std::int64_t>(fields[29], "TradedOnCBOE"));  // TradedOnCBOE
        row.tradedonpsx.set(::scaled::delimited::integer<std::int64_t>(fields[30], "TradedOnPSX"));  // TradedOnPSX
        row.tradedonbatsy.set(::scaled::delimited::integer<std::int64_t>(fields[31], "TradedOnBATSY"));  // TradedOnBATSY
        row.tradedonbats.set(::scaled::delimited::integer<std::int64_t>(fields[32], "TradedOnBATS"));  // TradedOnBATS
        row.tradedoniex.set(::scaled::delimited::integer<std::int64_t>(fields[33], "TradedOnIEX"));  // TradedOnIEX
        if (!fields[34].empty()) {  // Tick_Pilot_Indicator
            row.tick_pilot_indicator.set(fields[34]);
        }
        if (!fields[35].empty()) {  // Effective_Date
            row.effective_date.set(static_cast<std::int32_t>(::scaled::delimited::days(fields[35], "Effective_Date")));
        }
        row.tradedonltse.set(::scaled::delimited::integer<std::int64_t>(fields[36], "TradedOnLTSE"));  // TradedOnLTSE
        row.tradedonmemx.set(::scaled::delimited::integer<std::int64_t>(fields[37], "TradedOnMEMX"));  // TradedOnMEMX
        row.tradedonmiax.set(::scaled::delimited::integer<std::int64_t>(fields[38], "TradedOnMIAX"));  // TradedOnMIAX
        row.tradedon24x.set(::scaled::delimited::integer<std::int64_t>(fields[39], "TradedOn24X"));  // TradedOn24X
        row.tradedontxse.set(::scaled::delimited::integer<std::int64_t>(fields[40], "TradedOnTXSE"));  // TradedOnTXSE
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqMaster.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqmaster_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqMaster.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqmaster_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}