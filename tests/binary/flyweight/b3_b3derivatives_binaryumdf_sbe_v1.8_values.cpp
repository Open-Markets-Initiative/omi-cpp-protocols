// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 canonical values, through the Flyweight reader: every value Flyweight reads
// from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/definitions.hpp"

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.channelid"] = canonical::number(packet.packet_header().channel_id());
        values["packet.packetheader.packetreserved"] = canonical::number(packet.packet_header().packet_reserved());
        values["packet.packetheader.sequenceversion"] = canonical::number(packet.packet_header().sequence_version());
        values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
        values["packet.packetheader.sendingtime"] = canonical::number(packet.packet_header().sending_time());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::SequenceMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.sequencemessage";
        values[entry + ".payload.sequencemessage.nextseqno"] = canonical::number(message.next_seq_no());
    }

    void on(const protocol::EmptyBookMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.emptybookmessage";
        values[entry + ".payload.emptybookmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.emptybookmessage.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.emptybookmessage.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
    }

    void on(const protocol::ChannelReset11Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.channelreset11message";
        values[entry + ".payload.channelreset11message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.channelreset11message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.channelreset11message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
    }

    void on(const protocol::SecurityStatus3Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.securitystatus3message";
        values[entry + ".payload.securitystatus3message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.securitystatus3message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.securitystatus3message.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.securitystatus3message.securitytradingstatus"] = canonical::number(message.security_trading_status());
        values[entry + ".payload.securitystatus3message.securitytradingevent"] = (message.security_trading_event().has_value() ? canonical::number((*message.security_trading_event())) : canonical::absent());
        values[entry + ".payload.securitystatus3message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.securitystatus3message.tradsesopentime"] = (message.trad_ses_open_time().has_value() ? canonical::number((*message.trad_ses_open_time())) : canonical::absent());
        values[entry + ".payload.securitystatus3message.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.securitystatus3message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::SecurityGroupPhase10Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.securitygroupphase10message";
        values[entry + ".payload.securitygroupphase10message.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.securitygroupphase10message.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.securitygroupphase10message.tradingsessionsubid"] = canonical::number(message.trading_session_sub_id());
        values[entry + ".payload.securitygroupphase10message.securitytradingevent"] = (message.security_trading_event().has_value() ? canonical::number((*message.security_trading_event())) : canonical::absent());
        values[entry + ".payload.securitygroupphase10message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.securitygroupphase10message.tradsesopentime"] = (message.trad_ses_open_time().has_value() ? canonical::number((*message.trad_ses_open_time())) : canonical::absent());
        values[entry + ".payload.securitygroupphase10message.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
    }

    void on(const protocol::DeprecatedSecurityDefinitionMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.deprecatedsecuritydefinitionmessage";
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityexchange"] = canonical::text(std::string(message.security_exchange()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityidsource"] = canonical::text(canonical::character(message.security_id_source()));
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityupdateaction"] = canonical::text(canonical::character(message.security_update_action()));
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitytype"] = canonical::number(message.security_type());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitysubtype"] = canonical::number(message.security_sub_type());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.totnorelatedsym"] = canonical::number(message.tot_no_related_sym());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.minpriceincrementlegacy"] = (message.min_price_increment_legacy().has_value() ? canonical::scaled((*message.min_price_increment_legacy()).mantissa(), (*message.min_price_increment_legacy()).exponent()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.strikeprice"] = (message.strike_price().has_value() ? canonical::scaled((*message.strike_price()).mantissa(), (*message.strike_price()).exponent()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractmultiplier"] = (message.contract_multiplier().has_value() ? canonical::scaled((*message.contract_multiplier()).mantissa(), (*message.contract_multiplier()).exponent()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.pricedivisor"] = (message.price_divisor().has_value() ? canonical::scaled((*message.price_divisor()).mantissa(), (*message.price_divisor()).exponent()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityvaliditytimestamp"] = (message.security_validity_timestamp().has_value() ? canonical::number((*message.security_validity_timestamp())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.nosharesissued"] = (message.no_shares_issued().has_value() ? canonical::number((*message.no_shares_issued())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.clearinghouseid"] = (message.clearing_house_id().has_value() ? canonical::number((*message.clearing_house_id())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.minorderqty"] = (message.min_order_qty().has_value() ? canonical::number((*message.min_order_qty())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maxorderqty"] = (message.max_order_qty().has_value() ? canonical::number((*message.max_order_qty())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.minlotsize"] = (message.min_lot_size().has_value() ? canonical::number((*message.min_lot_size())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.mintradevol"] = (message.min_trade_vol().has_value() ? canonical::number((*message.min_trade_vol())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.corporateactioneventid"] = (message.corporate_action_event_id().has_value() ? canonical::number((*message.corporate_action_event_id())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.issuedate"] = canonical::number(message.issue_date());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitydate"] = (message.maturity_date().has_value() ? canonical::number((*message.maturity_date())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.startdate"] = (message.start_date().has_value() ? canonical::number((*message.start_date())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.enddate"] = (message.end_date().has_value() ? canonical::number((*message.end_date())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.settltype"] = (message.settl_type().has_value() ? canonical::number((*message.settl_type())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.settldate"] = (message.settl_date().has_value() ? canonical::number((*message.settl_date())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.dateddate"] = (message.dated_date().has_value() ? canonical::number((*message.dated_date())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.cficode"] = canonical::text(std::string(message.cfi_code()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.year"] = canonical::number(message.maturity_month_year().year());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.month"] = canonical::number(message.maturity_month_year().month());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.day"] = canonical::number(message.maturity_month_year().day());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.week"] = canonical::number(message.maturity_month_year().week());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.year"] = canonical::number(message.contract_settl_month().year());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.month"] = canonical::number(message.contract_settl_month().month());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.day"] = canonical::number(message.contract_settl_month().day());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.week"] = canonical::number(message.contract_settl_month().week());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.currency"] = canonical::text(std::string(message.currency()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.lottype"] = (message.lot_type().has_value() ? canonical::number((*message.lot_type())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.ticksizedenominator"] = (message.tick_size_denominator().has_value() ? canonical::number((*message.tick_size_denominator())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.product"] = canonical::number(message.product());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.exercisestyle"] = (message.exercise_style().has_value() ? canonical::number((*message.exercise_style())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.putorcall"] = (message.put_or_call().has_value() ? canonical::number((*message.put_or_call())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.pricetypeoptional"] = (message.price_type_optional().has_value() ? canonical::number((*message.price_type_optional())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.marketsegmentid"] = (message.market_segment_id().has_value() ? canonical::number((*message.market_segment_id())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.governanceindicator"] = (message.governance_indicator().has_value() ? canonical::number((*message.governance_indicator())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitymatchtype"] = (message.security_match_type().has_value() ? canonical::number((*message.security_match_type())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.lastfragment"] = (message.last_fragment().has_value() ? canonical::number((*message.last_fragment())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.multilegmodel"] = (message.multi_leg_model().has_value() ? canonical::number((*message.multi_leg_model())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.multilegpricemethod"] = (message.multi_leg_price_method().has_value() ? canonical::number((*message.multi_leg_price_method())) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.mincrossqty"] = (message.min_cross_qty().has_value() ? canonical::number((*message.min_cross_qty())) : canonical::absent());
    }

    void on(const protocol::SecurityDefinitionMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.securitydefinitionmessage";
        values[entry + ".payload.securitydefinitionmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.securitydefinitionmessage.securityexchange"] = canonical::text(std::string(message.security_exchange()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.securityidsource"] = canonical::text(canonical::character(message.security_id_source()));
        values[entry + ".payload.securitydefinitionmessage.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.securityupdateaction"] = canonical::text(canonical::character(message.security_update_action()));
        values[entry + ".payload.securitydefinitionmessage.securitytype"] = canonical::number(message.security_type());
        values[entry + ".payload.securitydefinitionmessage.securitysubtype"] = canonical::number(message.security_sub_type());
        values[entry + ".payload.securitydefinitionmessage.totnorelatedsym"] = canonical::number(message.tot_no_related_sym());
        values[entry + ".payload.securitydefinitionmessage.minpriceincrementoptional"] = (message.min_price_increment_optional().has_value() ? canonical::scaled((*message.min_price_increment_optional()).mantissa(), (*message.min_price_increment_optional()).exponent()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.strikeprice"] = (message.strike_price().has_value() ? canonical::scaled((*message.strike_price()).mantissa(), (*message.strike_price()).exponent()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.contractmultiplier"] = (message.contract_multiplier().has_value() ? canonical::scaled((*message.contract_multiplier()).mantissa(), (*message.contract_multiplier()).exponent()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.pricedivisor"] = (message.price_divisor().has_value() ? canonical::scaled((*message.price_divisor()).mantissa(), (*message.price_divisor()).exponent()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.securityvaliditytimestamp"] = (message.security_validity_timestamp().has_value() ? canonical::number((*message.security_validity_timestamp())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.nosharesissued"] = (message.no_shares_issued().has_value() ? canonical::number((*message.no_shares_issued())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.clearinghouseid"] = (message.clearing_house_id().has_value() ? canonical::number((*message.clearing_house_id())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.minorderqty"] = (message.min_order_qty().has_value() ? canonical::number((*message.min_order_qty())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.maxorderqty"] = (message.max_order_qty().has_value() ? canonical::number((*message.max_order_qty())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.minlotsize"] = (message.min_lot_size().has_value() ? canonical::number((*message.min_lot_size())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.mintradevol"] = (message.min_trade_vol().has_value() ? canonical::number((*message.min_trade_vol())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.corporateactioneventid"] = (message.corporate_action_event_id().has_value() ? canonical::number((*message.corporate_action_event_id())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.issuedate"] = canonical::number(message.issue_date());
        values[entry + ".payload.securitydefinitionmessage.maturitydate"] = (message.maturity_date().has_value() ? canonical::number((*message.maturity_date())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.startdate"] = (message.start_date().has_value() ? canonical::number((*message.start_date())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.enddate"] = (message.end_date().has_value() ? canonical::number((*message.end_date())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.settltype"] = (message.settl_type().has_value() ? canonical::number((*message.settl_type())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.settldate"] = (message.settl_date().has_value() ? canonical::number((*message.settl_date())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.dateddate"] = (message.dated_date().has_value() ? canonical::number((*message.dated_date())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.cficode"] = canonical::text(std::string(message.cfi_code()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.year"] = canonical::number(message.maturity_month_year().year());
        values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.month"] = canonical::number(message.maturity_month_year().month());
        values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.day"] = canonical::number(message.maturity_month_year().day());
        values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.week"] = canonical::number(message.maturity_month_year().week());
        values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.year"] = canonical::number(message.contract_settl_month().year());
        values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.month"] = canonical::number(message.contract_settl_month().month());
        values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.day"] = canonical::number(message.contract_settl_month().day());
        values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.week"] = canonical::number(message.contract_settl_month().week());
        values[entry + ".payload.securitydefinitionmessage.currency"] = canonical::text(std::string(message.currency()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.lottype"] = (message.lot_type().has_value() ? canonical::number((*message.lot_type())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.ticksizedenominator"] = (message.tick_size_denominator().has_value() ? canonical::number((*message.tick_size_denominator())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.product"] = canonical::number(message.product());
        values[entry + ".payload.securitydefinitionmessage.exercisestyle"] = (message.exercise_style().has_value() ? canonical::number((*message.exercise_style())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.putorcall"] = (message.put_or_call().has_value() ? canonical::number((*message.put_or_call())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.pricetypeoptional"] = (message.price_type_optional().has_value() ? canonical::number((*message.price_type_optional())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.marketsegmentid"] = (message.market_segment_id().has_value() ? canonical::number((*message.market_segment_id())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.governanceindicator"] = (message.governance_indicator().has_value() ? canonical::number((*message.governance_indicator())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.securitymatchtype"] = (message.security_match_type().has_value() ? canonical::number((*message.security_match_type())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.lastfragment"] = (message.last_fragment().has_value() ? canonical::number((*message.last_fragment())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.multilegmodel"] = (message.multi_leg_model().has_value() ? canonical::number((*message.multi_leg_model())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.multilegpricemethod"] = (message.multi_leg_price_method().has_value() ? canonical::number((*message.multi_leg_price_method())) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.mincrossqty"] = (message.min_cross_qty().has_value() ? canonical::number((*message.min_cross_qty())) : canonical::absent());
    }

    void on(const protocol::News5Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.news5message";
        values[entry + ".payload.news5message.securityidoptional"] = (message.security_id_optional().has_value() ? canonical::number((*message.security_id_optional())) : canonical::absent());
        values[entry + ".payload.news5message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.news5message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.news5message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.news5message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.news5message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.news5message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.news5message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.news5message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.news5message.newssource"] = canonical::number(message.news_source());
        values[entry + ".payload.news5message.partcount"] = canonical::number(message.part_count());
        values[entry + ".payload.news5message.partnumber"] = canonical::number(message.part_number());
        values[entry + ".payload.news5message.newsid"] = (message.news_id().has_value() ? canonical::number((*message.news_id())) : canonical::absent());
        values[entry + ".payload.news5message.origtime"] = (message.orig_time().has_value() ? canonical::number((*message.orig_time())) : canonical::absent());
        values[entry + ".payload.news5message.totaltextlength"] = canonical::number(message.total_text_length());
    }

    void on(const protocol::OpeningPrice15Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.openingprice15message";
        values[entry + ".payload.openingprice15message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.openingprice15message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.openingprice15message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.openingprice15message.mdupdateaction"] = canonical::number(message.md_update_action());
        values[entry + ".payload.openingprice15message.openclosesettlflag"] = canonical::number(message.open_close_settl_flag());
        values[entry + ".payload.openingprice15message.mdfutureprice"] = canonical::scaled(message.md_future_price().mantissa(), message.md_future_price().exponent());
        values[entry + ".payload.openingprice15message.netchgprevday"] = (message.net_chg_prev_day().has_value() ? canonical::scaled((*message.net_chg_prev_day()).mantissa(), (*message.net_chg_prev_day()).exponent()) : canonical::absent());
        values[entry + ".payload.openingprice15message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.openingprice15message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.openingprice15message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::TheoreticalOpeningPrice16Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.theoreticalopeningprice16message";
        values[entry + ".payload.theoreticalopeningprice16message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.theoreticalopeningprice16message.mdupdateaction"] = canonical::number(message.md_update_action());
        values[entry + ".payload.theoreticalopeningprice16message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.theoreticalopeningprice16message.mdcorporateoffsetpriceoptional"] = (message.md_corporate_offset_price_optional().has_value() ? canonical::scaled((*message.md_corporate_offset_price_optional()).mantissa(), (*message.md_corporate_offset_price_optional()).exponent()) : canonical::absent());
        values[entry + ".payload.theoreticalopeningprice16message.mdentrysizequantityoptional"] = (message.md_entry_size_quantity_optional().has_value() ? canonical::number((*message.md_entry_size_quantity_optional())) : canonical::absent());
        values[entry + ".payload.theoreticalopeningprice16message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.theoreticalopeningprice16message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::ClosingPrice17Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.closingprice17message";
        values[entry + ".payload.closingprice17message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.closingprice17message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.closingprice17message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.closingprice17message.openclosesettlflag"] = canonical::number(message.open_close_settl_flag());
        values[entry + ".payload.closingprice17message.mdcorporateprice"] = canonical::scaled(message.md_corporate_price().mantissa(), message.md_corporate_price().exponent());
        values[entry + ".payload.closingprice17message.lasttradedate"] = (message.last_trade_date().has_value() ? canonical::number((*message.last_trade_date())) : canonical::absent());
        values[entry + ".payload.closingprice17message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.closingprice17message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.closingprice17message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::AuctionImbalance19Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.auctionimbalance19message";
        values[entry + ".payload.auctionimbalance19message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.auctionimbalance19message.mdupdateaction"] = canonical::number(message.md_update_action());
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.unusedimbalancecondition0"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().unused_imbalance_condition_0()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.unusedimbalancecondition1"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().unused_imbalance_condition_1()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.unusedimbalancecondition2"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().unused_imbalance_condition_2()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.unusedimbalancecondition3"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().unused_imbalance_condition_3()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.unusedimbalancecondition4"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().unused_imbalance_condition_4()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.unusedimbalancecondition5"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().unused_imbalance_condition_5()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.unusedimbalancecondition6"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().unused_imbalance_condition_6()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.unusedimbalancecondition7"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().unused_imbalance_condition_7()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.imbalancemorebuyers"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().imbalance_more_buyers()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.imbalancemoresellers"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().imbalance_more_sellers()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.reserved6"] = canonical::number(static_cast<std::uint64_t>(message.imbalance_condition().reserved_6()));
        values[entry + ".payload.auctionimbalance19message.mdentrysizequantityoptional"] = (message.md_entry_size_quantity_optional().has_value() ? canonical::number((*message.md_entry_size_quantity_optional())) : canonical::absent());
        values[entry + ".payload.auctionimbalance19message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.auctionimbalance19message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::PriceBand20Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.priceband20message";
        values[entry + ".payload.priceband20message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.priceband20message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.priceband20message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.priceband20message.pricebandtype"] = (message.price_band_type().has_value() ? canonical::number((*message.price_band_type())) : canonical::absent());
        values[entry + ".payload.priceband20message.pricelimittype"] = (message.price_limit_type().has_value() ? canonical::number((*message.price_limit_type())) : canonical::absent());
        values[entry + ".payload.priceband20message.pricebandmidpointpricetype"] = (message.price_band_midpoint_price_type().has_value() ? canonical::number((*message.price_band_midpoint_price_type())) : canonical::absent());
        values[entry + ".payload.priceband20message.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.priceband20message.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.priceband20message.tradingreferencepricelegacy"] = (message.trading_reference_price_legacy().has_value() ? canonical::scaled((*message.trading_reference_price_legacy()).mantissa(), (*message.trading_reference_price_legacy()).exponent()) : canonical::absent());
        values[entry + ".payload.priceband20message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.priceband20message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::QuantityBand21Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.quantityband21message";
        values[entry + ".payload.quantityband21message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.quantityband21message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.quantityband21message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.quantityband21message.avgdailytradedqty"] = (message.avg_daily_traded_qty().has_value() ? canonical::number((*message.avg_daily_traded_qty())) : canonical::absent());
        values[entry + ".payload.quantityband21message.maxtradevol"] = (message.max_trade_vol().has_value() ? canonical::number((*message.max_trade_vol())) : canonical::absent());
        values[entry + ".payload.quantityband21message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.quantityband21message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::PriceBand22Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.priceband22message";
        values[entry + ".payload.priceband22message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.priceband22message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.priceband22message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.priceband22message.pricebandtype"] = (message.price_band_type().has_value() ? canonical::number((*message.price_band_type())) : canonical::absent());
        values[entry + ".payload.priceband22message.pricelimittype"] = (message.price_limit_type().has_value() ? canonical::number((*message.price_limit_type())) : canonical::absent());
        values[entry + ".payload.priceband22message.pricebandmidpointpricetype"] = (message.price_band_midpoint_price_type().has_value() ? canonical::number((*message.price_band_midpoint_price_type())) : canonical::absent());
        values[entry + ".payload.priceband22message.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.priceband22message.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.priceband22message.tradingreferencepriceoptional"] = (message.trading_reference_price_optional().has_value() ? canonical::scaled((*message.trading_reference_price_optional()).mantissa(), (*message.trading_reference_price_optional()).exponent()) : canonical::absent());
        values[entry + ".payload.priceband22message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.priceband22message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::HighPrice24Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.highprice24message";
        values[entry + ".payload.highprice24message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.highprice24message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.highprice24message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.highprice24message.mdupdateaction"] = canonical::number(message.md_update_action());
        values[entry + ".payload.highprice24message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.highprice24message.mdfutureprice"] = canonical::scaled(message.md_future_price().mantissa(), message.md_future_price().exponent());
        values[entry + ".payload.highprice24message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.highprice24message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::LowPrice25Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.lowprice25message";
        values[entry + ".payload.lowprice25message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.lowprice25message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.lowprice25message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.lowprice25message.mdupdateaction"] = canonical::number(message.md_update_action());
        values[entry + ".payload.lowprice25message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.lowprice25message.mdfutureprice"] = canonical::scaled(message.md_future_price().mantissa(), message.md_future_price().exponent());
        values[entry + ".payload.lowprice25message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.lowprice25message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::LastTradePrice27Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.lasttradeprice27message";
        values[entry + ".payload.lasttradeprice27message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.lasttradeprice27message.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.lasttradeprice27message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().opening_price()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().crossed()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().last_trade_at_the_same_price()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().out_of_sequence()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition4"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_4()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition5"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_5()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().trade_on_behalf()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition7"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_7()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition8"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_8()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition9"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_9()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition10"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_10()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition11"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_11()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition12"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_12()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().regular_trade()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().block_trade()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.unusedtradecondition15"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_15()));
        values[entry + ".payload.lasttradeprice27message.mdfutureprice"] = canonical::scaled(message.md_future_price().mantissa(), message.md_future_price().exponent());
        values[entry + ".payload.lasttradeprice27message.mdentrysizequantity"] = canonical::number(message.md_entry_size_quantity());
        values[entry + ".payload.lasttradeprice27message.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.lasttradeprice27message.mdentrybuyer"] = (message.md_entry_buyer().has_value() ? canonical::number((*message.md_entry_buyer())) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.mdentryseller"] = (message.md_entry_seller().has_value() ? canonical::number((*message.md_entry_seller())) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.lasttradeprice27message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.sellerdays"] = (message.seller_days().has_value() ? canonical::number((*message.seller_days())) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.mdentryinterestrate"] = (message.md_entry_interest_rate().has_value() ? canonical::scaled((*message.md_entry_interest_rate()).mantissa(), (*message.md_entry_interest_rate()).exponent()) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.trdsubtype"] = (message.trd_sub_type().has_value() ? canonical::number((*message.trd_sub_type())) : canonical::absent());
    }

    void on(const protocol::SettlementPrice28Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.settlementprice28message";
        values[entry + ".payload.settlementprice28message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.settlementprice28message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.settlementprice28message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.settlementprice28message.mdfutureprice"] = canonical::scaled(message.md_future_price().mantissa(), message.md_future_price().exponent());
        values[entry + ".payload.settlementprice28message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.settlementprice28message.openclosesettlflag"] = canonical::number(message.open_close_settl_flag());
        values[entry + ".payload.settlementprice28message.pricetype"] = canonical::number(message.price_type());
        values[entry + ".payload.settlementprice28message.settlpricetype"] = canonical::number(message.settl_price_type());
        values[entry + ".payload.settlementprice28message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::OpenInterest29Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.openinterest29message";
        values[entry + ".payload.openinterest29message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.openinterest29message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.openinterest29message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.openinterest29message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.openinterest29message.mdentrysizequantity"] = canonical::number(message.md_entry_size_quantity());
        values[entry + ".payload.openinterest29message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.openinterest29message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::SnapshotFullRefreshHeader30Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshheader30message";
        values[entry + ".payload.snapshotfullrefreshheader30message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.snapshotfullrefreshheader30message.lastmsgseqnumprocessed"] = canonical::number(message.last_msg_seq_num_processed());
        values[entry + ".payload.snapshotfullrefreshheader30message.totnumreports"] = canonical::number(message.tot_num_reports());
        values[entry + ".payload.snapshotfullrefreshheader30message.totnumbids"] = canonical::number(message.tot_num_bids());
        values[entry + ".payload.snapshotfullrefreshheader30message.totnumoffers"] = canonical::number(message.tot_num_offers());
        values[entry + ".payload.snapshotfullrefreshheader30message.totnumstats"] = canonical::number(message.tot_num_stats());
        values[entry + ".payload.snapshotfullrefreshheader30message.lastrptseq"] = (message.last_rpt_seq().has_value() ? canonical::number((*message.last_rpt_seq())) : canonical::absent());
    }

    void on(const protocol::OrderMbO50Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.ordermbo50message";
        values[entry + ".payload.ordermbo50message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.ordermbo50message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.ordermbo50message.mdupdateaction"] = canonical::number(message.md_update_action());
        values[entry + ".payload.ordermbo50message.mdentrytype"] = canonical::text(canonical::character(message.md_entry_type()));
        values[entry + ".payload.ordermbo50message.mdcorporateoffsetpriceoptional"] = (message.md_corporate_offset_price_optional().has_value() ? canonical::scaled((*message.md_corporate_offset_price_optional()).mantissa(), (*message.md_corporate_offset_price_optional()).exponent()) : canonical::absent());
        values[entry + ".payload.ordermbo50message.mdentrysizequantity"] = canonical::number(message.md_entry_size_quantity());
        values[entry + ".payload.ordermbo50message.mdentrypositionno"] = canonical::number(message.md_entry_position_no());
        values[entry + ".payload.ordermbo50message.enteringfirm"] = (message.entering_firm().has_value() ? canonical::number((*message.entering_firm())) : canonical::absent());
        values[entry + ".payload.ordermbo50message.mdinserttimestamp"] = (message.md_insert_timestamp().has_value() ? canonical::number((*message.md_insert_timestamp())) : canonical::absent());
        values[entry + ".payload.ordermbo50message.secondaryorderid"] = canonical::number(message.secondary_order_id());
        values[entry + ".payload.ordermbo50message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
        values[entry + ".payload.ordermbo50message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
    }

    void on(const protocol::DeleteOrderMbO51Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.deleteordermbo51message";
        values[entry + ".payload.deleteordermbo51message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.deleteordermbo51message.mdentrytype"] = canonical::text(canonical::character(message.md_entry_type()));
        values[entry + ".payload.deleteordermbo51message.mdentrypositionno"] = canonical::number(message.md_entry_position_no());
        values[entry + ".payload.deleteordermbo51message.mdentrysizequantityoptional"] = (message.md_entry_size_quantity_optional().has_value() ? canonical::number((*message.md_entry_size_quantity_optional())) : canonical::absent());
        values[entry + ".payload.deleteordermbo51message.secondaryorderid"] = canonical::number(message.secondary_order_id());
        values[entry + ".payload.deleteordermbo51message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.deleteordermbo51message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::MassDeleteOrdersMbO52Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.massdeleteordersmbo52message";
        values[entry + ".payload.massdeleteordersmbo52message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.massdeleteordersmbo52message.mdupdateaction"] = canonical::number(message.md_update_action());
        values[entry + ".payload.massdeleteordersmbo52message.mdentrytype"] = canonical::text(canonical::character(message.md_entry_type()));
        values[entry + ".payload.massdeleteordersmbo52message.mdentrypositionno"] = canonical::number(message.md_entry_position_no());
        values[entry + ".payload.massdeleteordersmbo52message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.massdeleteordersmbo52message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::Trade53Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.trade53message";
        values[entry + ".payload.trade53message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.trade53message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.trade53message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.trade53message.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.trade53message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().opening_price()));
        values[entry + ".payload.trade53message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().crossed()));
        values[entry + ".payload.trade53message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().last_trade_at_the_same_price()));
        values[entry + ".payload.trade53message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().out_of_sequence()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition4"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_4()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition5"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_5()));
        values[entry + ".payload.trade53message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().trade_on_behalf()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition7"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_7()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition8"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_8()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition9"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_9()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition10"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_10()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition11"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_11()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition12"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_12()));
        values[entry + ".payload.trade53message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().regular_trade()));
        values[entry + ".payload.trade53message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().block_trade()));
        values[entry + ".payload.trade53message.tradecondition.unusedtradecondition15"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_15()));
        values[entry + ".payload.trade53message.mdfutureprice"] = canonical::scaled(message.md_future_price().mantissa(), message.md_future_price().exponent());
        values[entry + ".payload.trade53message.mdentrysizequantity"] = canonical::number(message.md_entry_size_quantity());
        values[entry + ".payload.trade53message.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.trade53message.mdentrybuyer"] = (message.md_entry_buyer().has_value() ? canonical::number((*message.md_entry_buyer())) : canonical::absent());
        values[entry + ".payload.trade53message.mdentryseller"] = (message.md_entry_seller().has_value() ? canonical::number((*message.md_entry_seller())) : canonical::absent());
        values[entry + ".payload.trade53message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.trade53message.trdsubtype"] = (message.trd_sub_type().has_value() ? canonical::number((*message.trd_sub_type())) : canonical::absent());
        values[entry + ".payload.trade53message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.trade53message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::ForwardTrade54Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.forwardtrade54message";
        values[entry + ".payload.forwardtrade54message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.forwardtrade54message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.forwardtrade54message.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.forwardtrade54message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().opening_price()));
        values[entry + ".payload.forwardtrade54message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().crossed()));
        values[entry + ".payload.forwardtrade54message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().last_trade_at_the_same_price()));
        values[entry + ".payload.forwardtrade54message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().out_of_sequence()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition4"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_4()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition5"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_5()));
        values[entry + ".payload.forwardtrade54message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().trade_on_behalf()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition7"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_7()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition8"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_8()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition9"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_9()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition10"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_10()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition11"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_11()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition12"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_12()));
        values[entry + ".payload.forwardtrade54message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().regular_trade()));
        values[entry + ".payload.forwardtrade54message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().block_trade()));
        values[entry + ".payload.forwardtrade54message.tradecondition.unusedtradecondition15"] = canonical::number(static_cast<std::uint64_t>(message.trade_condition().unused_trade_condition_15()));
        values[entry + ".payload.forwardtrade54message.mdfutureprice"] = canonical::scaled(message.md_future_price().mantissa(), message.md_future_price().exponent());
        values[entry + ".payload.forwardtrade54message.mdentrysizequantity"] = canonical::number(message.md_entry_size_quantity());
        values[entry + ".payload.forwardtrade54message.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.forwardtrade54message.mdentrybuyer"] = (message.md_entry_buyer().has_value() ? canonical::number((*message.md_entry_buyer())) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.mdentryseller"] = (message.md_entry_seller().has_value() ? canonical::number((*message.md_entry_seller())) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.forwardtrade54message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.sellerdays"] = (message.seller_days().has_value() ? canonical::number((*message.seller_days())) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.mdentryinterestrate"] = (message.md_entry_interest_rate().has_value() ? canonical::scaled((*message.md_entry_interest_rate()).mantissa(), (*message.md_entry_interest_rate()).exponent()) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.trdsubtype"] = (message.trd_sub_type().has_value() ? canonical::number((*message.trd_sub_type())) : canonical::absent());
    }

    void on(const protocol::ExecutionSummary55Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.executionsummary55message";
        values[entry + ".payload.executionsummary55message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.executionsummary55message.aggressorside"] = canonical::number(message.aggressor_side());
        values[entry + ".payload.executionsummary55message.lastpx"] = canonical::scaled(message.last_px().mantissa(), message.last_px().exponent());
        values[entry + ".payload.executionsummary55message.fillqty"] = canonical::number(message.fill_qty());
        values[entry + ".payload.executionsummary55message.tradedhiddenqty"] = (message.traded_hidden_qty().has_value() ? canonical::number((*message.traded_hidden_qty())) : canonical::absent());
        values[entry + ".payload.executionsummary55message.cxlqty"] = (message.cxl_qty().has_value() ? canonical::number((*message.cxl_qty())) : canonical::absent());
        values[entry + ".payload.executionsummary55message.aggressortime"] = (message.aggressor_time().has_value() ? canonical::number((*message.aggressor_time())) : canonical::absent());
        values[entry + ".payload.executionsummary55message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
        values[entry + ".payload.executionsummary55message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
    }

    void on(const protocol::ExecutionStatistics56Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.executionstatistics56message";
        values[entry + ".payload.executionstatistics56message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.executionstatistics56message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.executionstatistics56message.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.executionstatistics56message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.executionstatistics56message.tradevolume"] = canonical::number(message.trade_volume());
        values[entry + ".payload.executionstatistics56message.vwappx"] = (message.vwap_px().has_value() ? canonical::scaled((*message.vwap_px()).mantissa(), (*message.vwap_px()).exponent()) : canonical::absent());
        values[entry + ".payload.executionstatistics56message.netchgprevday"] = (message.net_chg_prev_day().has_value() ? canonical::scaled((*message.net_chg_prev_day()).mantissa(), (*message.net_chg_prev_day()).exponent()) : canonical::absent());
        values[entry + ".payload.executionstatistics56message.numberoftrades"] = canonical::number(message.number_of_trades());
        values[entry + ".payload.executionstatistics56message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.executionstatistics56message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::TradeBust57Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.tradebust57message";
        values[entry + ".payload.tradebust57message.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.tradebust57message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.tradebust57message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.tradebust57message.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.tradebust57message.mdfutureprice"] = canonical::scaled(message.md_future_price().mantissa(), message.md_future_price().exponent());
        values[entry + ".payload.tradebust57message.mdentrysizequantity"] = canonical::number(message.md_entry_size_quantity());
        values[entry + ".payload.tradebust57message.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.tradebust57message.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.tradebust57message.mdentrytimestamp"] = (message.md_entry_timestamp().has_value() ? canonical::number((*message.md_entry_timestamp())) : canonical::absent());
        values[entry + ".payload.tradebust57message.rptseq"] = (message.rpt_seq().has_value() ? canonical::number((*message.rpt_seq())) : canonical::absent());
    }

    void on(const protocol::SnapshotFullRefreshOrdersMbO71Message& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshordersmbo71message";
        values[entry + ".payload.snapshotfullrefreshordersmbo71message.securityid"] = canonical::number(message.security_id());
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Flyweight and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 (flyweight values)\n");
    int failures = 0;
    failures += check("SecurityDefinitionMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SecurityDefinitionMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SecurityDefinitionMessage.values");
    failures += check("SequenceMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SequenceMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SequenceMessage.values");
    return failures == 0 ? 0 : 1;
}
