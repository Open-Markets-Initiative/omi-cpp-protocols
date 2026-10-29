#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Nyse.NyseConsolidated.DailyTaqMaster.Csv.v4.3: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace nyse::nyseconsolidated::dailytaqmaster::csv::v4_3 {

// Security: a data line of the model, its fields typed as the model states them
struct Security {
    // Symbol: text
    ::scaled::delimited::values::Required<std::string_view> symbol;
    // Security_Description: text, its Windows1252 decoded to UTF-8
    ::scaled::delimited::values::RequiredText<::scaled::delimited::encoding::Encoding::windows1252> security_description;
    // CUSIP: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> cusip;
    // Security_Type: text
    ::scaled::delimited::values::Required<std::string_view> security_type;
    // SIP_Symbol: text
    ::scaled::delimited::values::Required<std::string_view> sip_symbol;
    // Old_Symbol: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> old_symbol;
    // Test_Symbol_Flag: text
    ::scaled::delimited::values::Required<std::string_view> test_symbol_flag;
    // Listed_Exchange: text
    ::scaled::delimited::values::Required<std::string_view> listed_exchange;
    // Tape: text
    ::scaled::delimited::values::Required<std::string_view> tape;
    // Unit_Of_Trade: an integer
    ::scaled::delimited::values::Required<std::int64_t> unit_of_trade;
    // Round_Lot: an integer
    ::scaled::delimited::values::Required<std::int64_t> round_lot;
    // NYSE_Industry_Code: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> nyse_industry_code;
    // Shares_Outstanding: a decimal, the integer of its 2 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> shares_outstanding;
    static constexpr int shares_outstanding_places = 2;
    // Halt_Delay_Reason: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> halt_delay_reason;
    // Specialist_Clearing_Agent: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> specialist_clearing_agent;
    // Specialist_Clearing_Number: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> specialist_clearing_number;
    // Specialist_Post_Number: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> specialist_post_number;
    // Specialist_Panel: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> specialist_panel;
    // TradedOnNYSEMKT: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_nysemkt;
    // TradedOnNASDAQBX: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_nasdaqbx;
    // TradedOnNSX: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_nsx;
    // TradedOnFINRA: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_finra;
    // TradedOnISE: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_ise;
    // TradedOnEdgeA: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_edge_a;
    // TradedOnEdgeX: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_edge_x;
    // TradedOnNYSETexas: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_nyse_texas;
    // TradedOnNYSE: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_nyse;
    // TradedOnArca: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_arca;
    // TradedOnNasdaq: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_nasdaq;
    // TradedOnCBOE: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_cboe;
    // TradedOnPSX: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_psx;
    // TradedOnBATSY: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_batsy;
    // TradedOnBATS: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_bats;
    // TradedOnIEX: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_iex;
    // Tick_Pilot_Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> tick_pilot_indicator;
    // Effective_Date: a date, days since 1970-01-01; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int32_t> effective_date;
    // TradedOnLTSE: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_ltse;
    // TradedOnMEMX: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_memx;
    // TradedOnMIAX: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_miax;
    // TradedOn24X: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_24x;
    // TradedOnTXSE: an integer
    ::scaled::delimited::values::Required<std::int64_t> traded_on_txse;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        symbol.reset();
        security_description.reset();
        cusip.reset();
        security_type.reset();
        sip_symbol.reset();
        old_symbol.reset();
        test_symbol_flag.reset();
        listed_exchange.reset();
        tape.reset();
        unit_of_trade.reset();
        round_lot.reset();
        nyse_industry_code.reset();
        shares_outstanding.reset();
        halt_delay_reason.reset();
        specialist_clearing_agent.reset();
        specialist_clearing_number.reset();
        specialist_post_number.reset();
        specialist_panel.reset();
        traded_on_nysemkt.reset();
        traded_on_nasdaqbx.reset();
        traded_on_nsx.reset();
        traded_on_finra.reset();
        traded_on_ise.reset();
        traded_on_edge_a.reset();
        traded_on_edge_x.reset();
        traded_on_nyse_texas.reset();
        traded_on_nyse.reset();
        traded_on_arca.reset();
        traded_on_nasdaq.reset();
        traded_on_cboe.reset();
        traded_on_psx.reset();
        traded_on_batsy.reset();
        traded_on_bats.reset();
        traded_on_iex.reset();
        tick_pilot_indicator.reset();
        effective_date.reset();
        traded_on_ltse.reset();
        traded_on_memx.reset();
        traded_on_miax.reset();
        traded_on_24x.reset();
        traded_on_txse.reset();
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "Security{";
        out << "symbol=";
        ::scaled::delimited::values::print(out, symbol, ::scaled::delimited::values::text);
        out << ", security_description=";
        ::scaled::delimited::values::print(out, security_description, ::scaled::delimited::values::text);
        out << ", cusip=";
        ::scaled::delimited::values::print(out, cusip, ::scaled::delimited::values::text);
        out << ", security_type=";
        ::scaled::delimited::values::print(out, security_type, ::scaled::delimited::values::text);
        out << ", sip_symbol=";
        ::scaled::delimited::values::print(out, sip_symbol, ::scaled::delimited::values::text);
        out << ", old_symbol=";
        ::scaled::delimited::values::print(out, old_symbol, ::scaled::delimited::values::text);
        out << ", test_symbol_flag=";
        ::scaled::delimited::values::print(out, test_symbol_flag, ::scaled::delimited::values::text);
        out << ", listed_exchange=";
        ::scaled::delimited::values::print(out, listed_exchange, ::scaled::delimited::values::text);
        out << ", tape=";
        ::scaled::delimited::values::print(out, tape, ::scaled::delimited::values::text);
        out << ", unit_of_trade=";
        ::scaled::delimited::values::print(out, unit_of_trade, ::scaled::delimited::values::integer);
        out << ", round_lot=";
        ::scaled::delimited::values::print(out, round_lot, ::scaled::delimited::values::integer);
        out << ", nyse_industry_code=";
        ::scaled::delimited::values::print(out, nyse_industry_code, ::scaled::delimited::values::text);
        out << ", shares_outstanding=";
        ::scaled::delimited::values::print(out, shares_outstanding, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, shares_outstanding_places); });
        out << ", halt_delay_reason=";
        ::scaled::delimited::values::print(out, halt_delay_reason, ::scaled::delimited::values::text);
        out << ", specialist_clearing_agent=";
        ::scaled::delimited::values::print(out, specialist_clearing_agent, ::scaled::delimited::values::text);
        out << ", specialist_clearing_number=";
        ::scaled::delimited::values::print(out, specialist_clearing_number, ::scaled::delimited::values::integer);
        out << ", specialist_post_number=";
        ::scaled::delimited::values::print(out, specialist_post_number, ::scaled::delimited::values::integer);
        out << ", specialist_panel=";
        ::scaled::delimited::values::print(out, specialist_panel, ::scaled::delimited::values::text);
        out << ", traded_on_nysemkt=";
        ::scaled::delimited::values::print(out, traded_on_nysemkt, ::scaled::delimited::values::integer);
        out << ", traded_on_nasdaqbx=";
        ::scaled::delimited::values::print(out, traded_on_nasdaqbx, ::scaled::delimited::values::integer);
        out << ", traded_on_nsx=";
        ::scaled::delimited::values::print(out, traded_on_nsx, ::scaled::delimited::values::integer);
        out << ", traded_on_finra=";
        ::scaled::delimited::values::print(out, traded_on_finra, ::scaled::delimited::values::integer);
        out << ", traded_on_ise=";
        ::scaled::delimited::values::print(out, traded_on_ise, ::scaled::delimited::values::integer);
        out << ", traded_on_edge_a=";
        ::scaled::delimited::values::print(out, traded_on_edge_a, ::scaled::delimited::values::integer);
        out << ", traded_on_edge_x=";
        ::scaled::delimited::values::print(out, traded_on_edge_x, ::scaled::delimited::values::integer);
        out << ", traded_on_nyse_texas=";
        ::scaled::delimited::values::print(out, traded_on_nyse_texas, ::scaled::delimited::values::integer);
        out << ", traded_on_nyse=";
        ::scaled::delimited::values::print(out, traded_on_nyse, ::scaled::delimited::values::integer);
        out << ", traded_on_arca=";
        ::scaled::delimited::values::print(out, traded_on_arca, ::scaled::delimited::values::integer);
        out << ", traded_on_nasdaq=";
        ::scaled::delimited::values::print(out, traded_on_nasdaq, ::scaled::delimited::values::integer);
        out << ", traded_on_cboe=";
        ::scaled::delimited::values::print(out, traded_on_cboe, ::scaled::delimited::values::integer);
        out << ", traded_on_psx=";
        ::scaled::delimited::values::print(out, traded_on_psx, ::scaled::delimited::values::integer);
        out << ", traded_on_batsy=";
        ::scaled::delimited::values::print(out, traded_on_batsy, ::scaled::delimited::values::integer);
        out << ", traded_on_bats=";
        ::scaled::delimited::values::print(out, traded_on_bats, ::scaled::delimited::values::integer);
        out << ", traded_on_iex=";
        ::scaled::delimited::values::print(out, traded_on_iex, ::scaled::delimited::values::integer);
        out << ", tick_pilot_indicator=";
        ::scaled::delimited::values::print(out, tick_pilot_indicator, ::scaled::delimited::values::text);
        out << ", effective_date=";
        ::scaled::delimited::values::print(out, effective_date, ::scaled::delimited::values::date);
        out << ", traded_on_ltse=";
        ::scaled::delimited::values::print(out, traded_on_ltse, ::scaled::delimited::values::integer);
        out << ", traded_on_memx=";
        ::scaled::delimited::values::print(out, traded_on_memx, ::scaled::delimited::values::integer);
        out << ", traded_on_miax=";
        ::scaled::delimited::values::print(out, traded_on_miax, ::scaled::delimited::values::integer);
        out << ", traded_on_24x=";
        ::scaled::delimited::values::print(out, traded_on_24x, ::scaled::delimited::values::integer);
        out << ", traded_on_txse=";
        ::scaled::delimited::values::print(out, traded_on_txse, ::scaled::delimited::values::integer);
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const Security& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = Security;

}