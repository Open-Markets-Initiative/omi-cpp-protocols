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
    ::scaled::delimited::values::Required<std::int64_t> tradedonnysemkt;
    // TradedOnNASDAQBX: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonnasdaqbx;
    // TradedOnNSX: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonnsx;
    // TradedOnFINRA: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonfinra;
    // TradedOnISE: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonise;
    // TradedOnEdgeA: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonedgea;
    // TradedOnEdgeX: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonedgex;
    // TradedOnNYSETexas: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonnysetexas;
    // TradedOnNYSE: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonnyse;
    // TradedOnArca: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonarca;
    // TradedOnNasdaq: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonnasdaq;
    // TradedOnCBOE: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedoncboe;
    // TradedOnPSX: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonpsx;
    // TradedOnBATSY: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonbatsy;
    // TradedOnBATS: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonbats;
    // TradedOnIEX: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedoniex;
    // Tick_Pilot_Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> tick_pilot_indicator;
    // Effective_Date: a date, days since 1970-01-01; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int32_t> effective_date;
    // TradedOnLTSE: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonltse;
    // TradedOnMEMX: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonmemx;
    // TradedOnMIAX: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedonmiax;
    // TradedOn24X: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedon24x;
    // TradedOnTXSE: an integer
    ::scaled::delimited::values::Required<std::int64_t> tradedontxse;

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
        tradedonnysemkt.reset();
        tradedonnasdaqbx.reset();
        tradedonnsx.reset();
        tradedonfinra.reset();
        tradedonise.reset();
        tradedonedgea.reset();
        tradedonedgex.reset();
        tradedonnysetexas.reset();
        tradedonnyse.reset();
        tradedonarca.reset();
        tradedonnasdaq.reset();
        tradedoncboe.reset();
        tradedonpsx.reset();
        tradedonbatsy.reset();
        tradedonbats.reset();
        tradedoniex.reset();
        tick_pilot_indicator.reset();
        effective_date.reset();
        tradedonltse.reset();
        tradedonmemx.reset();
        tradedonmiax.reset();
        tradedon24x.reset();
        tradedontxse.reset();
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
        out << ", tradedonnysemkt=";
        ::scaled::delimited::values::print(out, tradedonnysemkt, ::scaled::delimited::values::integer);
        out << ", tradedonnasdaqbx=";
        ::scaled::delimited::values::print(out, tradedonnasdaqbx, ::scaled::delimited::values::integer);
        out << ", tradedonnsx=";
        ::scaled::delimited::values::print(out, tradedonnsx, ::scaled::delimited::values::integer);
        out << ", tradedonfinra=";
        ::scaled::delimited::values::print(out, tradedonfinra, ::scaled::delimited::values::integer);
        out << ", tradedonise=";
        ::scaled::delimited::values::print(out, tradedonise, ::scaled::delimited::values::integer);
        out << ", tradedonedgea=";
        ::scaled::delimited::values::print(out, tradedonedgea, ::scaled::delimited::values::integer);
        out << ", tradedonedgex=";
        ::scaled::delimited::values::print(out, tradedonedgex, ::scaled::delimited::values::integer);
        out << ", tradedonnysetexas=";
        ::scaled::delimited::values::print(out, tradedonnysetexas, ::scaled::delimited::values::integer);
        out << ", tradedonnyse=";
        ::scaled::delimited::values::print(out, tradedonnyse, ::scaled::delimited::values::integer);
        out << ", tradedonarca=";
        ::scaled::delimited::values::print(out, tradedonarca, ::scaled::delimited::values::integer);
        out << ", tradedonnasdaq=";
        ::scaled::delimited::values::print(out, tradedonnasdaq, ::scaled::delimited::values::integer);
        out << ", tradedoncboe=";
        ::scaled::delimited::values::print(out, tradedoncboe, ::scaled::delimited::values::integer);
        out << ", tradedonpsx=";
        ::scaled::delimited::values::print(out, tradedonpsx, ::scaled::delimited::values::integer);
        out << ", tradedonbatsy=";
        ::scaled::delimited::values::print(out, tradedonbatsy, ::scaled::delimited::values::integer);
        out << ", tradedonbats=";
        ::scaled::delimited::values::print(out, tradedonbats, ::scaled::delimited::values::integer);
        out << ", tradedoniex=";
        ::scaled::delimited::values::print(out, tradedoniex, ::scaled::delimited::values::integer);
        out << ", tick_pilot_indicator=";
        ::scaled::delimited::values::print(out, tick_pilot_indicator, ::scaled::delimited::values::text);
        out << ", effective_date=";
        ::scaled::delimited::values::print(out, effective_date, ::scaled::delimited::values::date);
        out << ", tradedonltse=";
        ::scaled::delimited::values::print(out, tradedonltse, ::scaled::delimited::values::integer);
        out << ", tradedonmemx=";
        ::scaled::delimited::values::print(out, tradedonmemx, ::scaled::delimited::values::integer);
        out << ", tradedonmiax=";
        ::scaled::delimited::values::print(out, tradedonmiax, ::scaled::delimited::values::integer);
        out << ", tradedon24x=";
        ::scaled::delimited::values::print(out, tradedon24x, ::scaled::delimited::values::integer);
        out << ", tradedontxse=";
        ::scaled::delimited::values::print(out, tradedontxse, ::scaled::delimited::values::integer);
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