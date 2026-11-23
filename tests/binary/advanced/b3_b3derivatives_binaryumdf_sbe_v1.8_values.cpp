// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 canonical values, through the Advanced session layer: every value Advanced
// reads from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/advanced/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/session.hpp"

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.channelid"] = canonical::number(header.channel_id.get().value());
        values["packet.packetheader.sequenceversion"] = canonical::number(header.sequence_version.get().value());
        values["packet.packetheader.sequencenumber"] = canonical::number(header.sequence_number.get().value());
        values["packet.packetheader.sendingtime"] = canonical::number(header.sending_time.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::sequence_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.sequencemessage";
        values[entry + ".payload.sequencemessage.nextseqno"] = canonical::number(message.fields.next_seq_no.get().value());
    }

    void on_message(const protocol::empty_book_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.emptybookmessage";
        values[entry + ".payload.emptybookmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.emptybookmessage.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.emptybookmessage.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.emptybookmessage.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
    }

    void on_message(const protocol::channel_reset_11_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.channelreset11message";
        values[entry + ".payload.channelreset11message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.channelreset11message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.channelreset11message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
    }

    void on_message(const protocol::security_status_3_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.securitystatus3message";
        values[entry + ".payload.securitystatus3message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.securitystatus3message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.securitystatus3message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.securitystatus3message.tradingsessionid"] = canonical::number(message.fields.trading_session_id.get().value());
        values[entry + ".payload.securitystatus3message.securitytradingstatus"] = canonical::number(message.fields.security_trading_status.get().value());
        values[entry + ".payload.securitystatus3message.securitytradingevent"] = (message.fields.security_trading_event.get().has_value() ? canonical::number(message.fields.security_trading_event.get().value()) : canonical::absent());
        values[entry + ".payload.securitystatus3message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.securitystatus3message.tradsesopentime"] = (message.fields.trad_ses_open_time.get().has_value() ? canonical::number(message.fields.trad_ses_open_time.get().value()) : canonical::absent());
        values[entry + ".payload.securitystatus3message.transacttime"] = (message.fields.transact_time.get().has_value() ? canonical::number(message.fields.transact_time.get().value()) : canonical::absent());
        values[entry + ".payload.securitystatus3message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::security_group_phase_10_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.securitygroupphase10message";
        values[entry + ".payload.securitygroupphase10message.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.securitygroupphase10message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.securitygroupphase10message.tradingsessionid"] = canonical::number(message.fields.trading_session_id.get().value());
        values[entry + ".payload.securitygroupphase10message.tradingsessionsubid"] = canonical::number(message.fields.trading_session_sub_id.get().value());
        values[entry + ".payload.securitygroupphase10message.securitytradingevent"] = (message.fields.security_trading_event.get().has_value() ? canonical::number(message.fields.security_trading_event.get().value()) : canonical::absent());
        values[entry + ".payload.securitygroupphase10message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.securitygroupphase10message.tradsesopentime"] = (message.fields.trad_ses_open_time.get().has_value() ? canonical::number(message.fields.trad_ses_open_time.get().value()) : canonical::absent());
        values[entry + ".payload.securitygroupphase10message.transacttime"] = (message.fields.transact_time.get().has_value() ? canonical::number(message.fields.transact_time.get().value()) : canonical::absent());
    }

    void on_message(const protocol::deprecated_security_definition_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.deprecatedsecuritydefinitionmessage";
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityexchange"] = canonical::text(std::string(message.fields.security_exchange.get().value()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityidsource"] = canonical::text(canonical::character(message.fields.security_id_source.get().value()));
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityupdateaction"] = canonical::text(canonical::character(message.fields.security_update_action.get().value()));
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitytype"] = canonical::number(message.fields.security_type.get().value());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitysubtype"] = canonical::number(message.fields.security_sub_type.get().value());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.totnorelatedsym"] = canonical::number(message.fields.tot_no_related_sym.get().value());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.minpriceincrementlegacy"] = (message.fields.min_price_increment_legacy.get().has_value() ? canonical::scaled(message.fields.min_price_increment_legacy.get().value(), -4) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.strikeprice"] = (message.fields.strike_price.get().has_value() ? canonical::scaled(message.fields.strike_price.get().value(), -4) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractmultiplier"] = (message.fields.contract_multiplier.get().has_value() ? canonical::scaled(message.fields.contract_multiplier.get().value(), -8) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.pricedivisor"] = (message.fields.price_divisor.get().has_value() ? canonical::scaled(message.fields.price_divisor.get().value(), -8) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityvaliditytimestamp"] = (message.fields.security_validity_timestamp.get().has_value() ? canonical::number(message.fields.security_validity_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.nosharesissued"] = (message.fields.no_shares_issued.get().has_value() ? canonical::number(message.fields.no_shares_issued.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.clearinghouseid"] = (message.fields.clearing_house_id.get().has_value() ? canonical::number(message.fields.clearing_house_id.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.minorderqty"] = (message.fields.min_order_qty.get().has_value() ? canonical::number(message.fields.min_order_qty.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maxorderqty"] = (message.fields.max_order_qty.get().has_value() ? canonical::number(message.fields.max_order_qty.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.minlotsize"] = (message.fields.min_lot_size.get().has_value() ? canonical::number(message.fields.min_lot_size.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.mintradevol"] = (message.fields.min_trade_vol.get().has_value() ? canonical::number(message.fields.min_trade_vol.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.corporateactioneventid"] = (message.fields.corporate_action_event_id.get().has_value() ? canonical::number(message.fields.corporate_action_event_id.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.issuedate"] = canonical::number(message.fields.issue_date.get().value());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitydate"] = (message.fields.maturity_date.get().has_value() ? canonical::number(message.fields.maturity_date.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.startdate"] = (message.fields.start_date.get().has_value() ? canonical::number(message.fields.start_date.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.enddate"] = (message.fields.end_date.get().has_value() ? canonical::number(message.fields.end_date.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.settltype"] = (message.fields.settl_type.get().has_value() ? canonical::number(message.fields.settl_type.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.settldate"] = (message.fields.settl_date.get().has_value() ? canonical::number(message.fields.settl_date.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.dateddate"] = (message.fields.dated_date.get().has_value() ? canonical::number(message.fields.dated_date.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.year"] = (message.fields.maturity_month_year.year.get().has_value() ? canonical::number(message.fields.maturity_month_year.year.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.month"] = (message.fields.maturity_month_year.month.get().has_value() ? canonical::number(message.fields.maturity_month_year.month.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.day"] = (message.fields.maturity_month_year.day.get().has_value() ? canonical::number(message.fields.maturity_month_year.day.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.week"] = (message.fields.maturity_month_year.week.get().has_value() ? canonical::number(message.fields.maturity_month_year.week.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.year"] = (message.fields.contract_settl_month.year.get().has_value() ? canonical::number(message.fields.contract_settl_month.year.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.month"] = (message.fields.contract_settl_month.month.get().has_value() ? canonical::number(message.fields.contract_settl_month.month.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.day"] = (message.fields.contract_settl_month.day.get().has_value() ? canonical::number(message.fields.contract_settl_month.day.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.week"] = (message.fields.contract_settl_month.week.get().has_value() ? canonical::number(message.fields.contract_settl_month.week.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.currency"] = canonical::text(std::string(message.fields.currency.get().value()), '\0', false);
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.lottype"] = (message.fields.lot_type.get().has_value() ? canonical::number(message.fields.lot_type.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.ticksizedenominator"] = (message.fields.tick_size_denominator.get().has_value() ? canonical::number(message.fields.tick_size_denominator.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.product"] = canonical::number(message.fields.product.get().value());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.exercisestyle"] = (message.fields.exercise_style.get().has_value() ? canonical::number(message.fields.exercise_style.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.putorcall"] = (message.fields.put_or_call.get().has_value() ? canonical::number(message.fields.put_or_call.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.pricetypeoptional"] = (message.fields.price_type_optional.get().has_value() ? canonical::number(message.fields.price_type_optional.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.marketsegmentid"] = (message.fields.market_segment_id.get().has_value() ? canonical::number(message.fields.market_segment_id.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.governanceindicator"] = (message.fields.governance_indicator.get().has_value() ? canonical::number(message.fields.governance_indicator.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitymatchtype"] = (message.fields.security_match_type.get().has_value() ? canonical::number(message.fields.security_match_type.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.lastfragment"] = (message.fields.last_fragment.get().has_value() ? canonical::number(message.fields.last_fragment.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.multilegmodel"] = (message.fields.multi_leg_model.get().has_value() ? canonical::number(message.fields.multi_leg_model.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.multilegpricemethod"] = (message.fields.multi_leg_price_method.get().has_value() ? canonical::number(message.fields.multi_leg_price_method.get().value()) : canonical::absent());
        values[entry + ".payload.deprecatedsecuritydefinitionmessage.mincrossqty"] = (message.fields.min_cross_qty.get().has_value() ? canonical::number(message.fields.min_cross_qty.get().value()) : canonical::absent());
    }

    void on_message(const protocol::security_definition_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.securitydefinitionmessage";
        values[entry + ".payload.securitydefinitionmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.securitydefinitionmessage.securityexchange"] = canonical::text(std::string(message.fields.security_exchange.get().value()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.securityidsource"] = canonical::text(canonical::character(message.fields.security_id_source.get().value()));
        values[entry + ".payload.securitydefinitionmessage.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.securityupdateaction"] = canonical::text(canonical::character(message.fields.security_update_action.get().value()));
        values[entry + ".payload.securitydefinitionmessage.securitytype"] = canonical::number(message.fields.security_type.get().value());
        values[entry + ".payload.securitydefinitionmessage.securitysubtype"] = canonical::number(message.fields.security_sub_type.get().value());
        values[entry + ".payload.securitydefinitionmessage.totnorelatedsym"] = canonical::number(message.fields.tot_no_related_sym.get().value());
        values[entry + ".payload.securitydefinitionmessage.minpriceincrementoptional"] = (message.fields.min_price_increment_optional.get().has_value() ? canonical::scaled(message.fields.min_price_increment_optional.get().value(), -8) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.strikeprice"] = (message.fields.strike_price.get().has_value() ? canonical::scaled(message.fields.strike_price.get().value(), -4) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.contractmultiplier"] = (message.fields.contract_multiplier.get().has_value() ? canonical::scaled(message.fields.contract_multiplier.get().value(), -8) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.pricedivisor"] = (message.fields.price_divisor.get().has_value() ? canonical::scaled(message.fields.price_divisor.get().value(), -8) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.securityvaliditytimestamp"] = (message.fields.security_validity_timestamp.get().has_value() ? canonical::number(message.fields.security_validity_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.nosharesissued"] = (message.fields.no_shares_issued.get().has_value() ? canonical::number(message.fields.no_shares_issued.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.clearinghouseid"] = (message.fields.clearing_house_id.get().has_value() ? canonical::number(message.fields.clearing_house_id.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.minorderqty"] = (message.fields.min_order_qty.get().has_value() ? canonical::number(message.fields.min_order_qty.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.maxorderqty"] = (message.fields.max_order_qty.get().has_value() ? canonical::number(message.fields.max_order_qty.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.minlotsize"] = (message.fields.min_lot_size.get().has_value() ? canonical::number(message.fields.min_lot_size.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.mintradevol"] = (message.fields.min_trade_vol.get().has_value() ? canonical::number(message.fields.min_trade_vol.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.corporateactioneventid"] = (message.fields.corporate_action_event_id.get().has_value() ? canonical::number(message.fields.corporate_action_event_id.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.issuedate"] = canonical::number(message.fields.issue_date.get().value());
        values[entry + ".payload.securitydefinitionmessage.maturitydate"] = (message.fields.maturity_date.get().has_value() ? canonical::number(message.fields.maturity_date.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.startdate"] = (message.fields.start_date.get().has_value() ? canonical::number(message.fields.start_date.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.enddate"] = (message.fields.end_date.get().has_value() ? canonical::number(message.fields.end_date.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.settltype"] = (message.fields.settl_type.get().has_value() ? canonical::number(message.fields.settl_type.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.settldate"] = (message.fields.settl_date.get().has_value() ? canonical::number(message.fields.settl_date.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.dateddate"] = (message.fields.dated_date.get().has_value() ? canonical::number(message.fields.dated_date.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.year"] = (message.fields.maturity_month_year.year.get().has_value() ? canonical::number(message.fields.maturity_month_year.year.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.month"] = (message.fields.maturity_month_year.month.get().has_value() ? canonical::number(message.fields.maturity_month_year.month.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.day"] = (message.fields.maturity_month_year.day.get().has_value() ? canonical::number(message.fields.maturity_month_year.day.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.week"] = (message.fields.maturity_month_year.week.get().has_value() ? canonical::number(message.fields.maturity_month_year.week.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.year"] = (message.fields.contract_settl_month.year.get().has_value() ? canonical::number(message.fields.contract_settl_month.year.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.month"] = (message.fields.contract_settl_month.month.get().has_value() ? canonical::number(message.fields.contract_settl_month.month.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.day"] = (message.fields.contract_settl_month.day.get().has_value() ? canonical::number(message.fields.contract_settl_month.day.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.week"] = (message.fields.contract_settl_month.week.get().has_value() ? canonical::number(message.fields.contract_settl_month.week.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.currency"] = canonical::text(std::string(message.fields.currency.get().value()), '\0', false);
        values[entry + ".payload.securitydefinitionmessage.lottype"] = (message.fields.lot_type.get().has_value() ? canonical::number(message.fields.lot_type.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.ticksizedenominator"] = (message.fields.tick_size_denominator.get().has_value() ? canonical::number(message.fields.tick_size_denominator.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.product"] = canonical::number(message.fields.product.get().value());
        values[entry + ".payload.securitydefinitionmessage.exercisestyle"] = (message.fields.exercise_style.get().has_value() ? canonical::number(message.fields.exercise_style.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.putorcall"] = (message.fields.put_or_call.get().has_value() ? canonical::number(message.fields.put_or_call.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.pricetypeoptional"] = (message.fields.price_type_optional.get().has_value() ? canonical::number(message.fields.price_type_optional.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.marketsegmentid"] = (message.fields.market_segment_id.get().has_value() ? canonical::number(message.fields.market_segment_id.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.governanceindicator"] = (message.fields.governance_indicator.get().has_value() ? canonical::number(message.fields.governance_indicator.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.securitymatchtype"] = (message.fields.security_match_type.get().has_value() ? canonical::number(message.fields.security_match_type.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.lastfragment"] = (message.fields.last_fragment.get().has_value() ? canonical::number(message.fields.last_fragment.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.multilegmodel"] = (message.fields.multi_leg_model.get().has_value() ? canonical::number(message.fields.multi_leg_model.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.multilegpricemethod"] = (message.fields.multi_leg_price_method.get().has_value() ? canonical::number(message.fields.multi_leg_price_method.get().value()) : canonical::absent());
        values[entry + ".payload.securitydefinitionmessage.mincrossqty"] = (message.fields.min_cross_qty.get().has_value() ? canonical::number(message.fields.min_cross_qty.get().value()) : canonical::absent());
    }

    void on_message(const protocol::news_5_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.news5message";
        values[entry + ".payload.news5message.securityidoptional"] = (message.fields.security_id_optional.get().has_value() ? canonical::number(message.fields.security_id_optional.get().value()) : canonical::absent());
        values[entry + ".payload.news5message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.news5message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.news5message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.news5message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.news5message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.news5message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.news5message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.news5message.newssource"] = canonical::number(message.fields.news_source.get().value());
        values[entry + ".payload.news5message.partcount"] = canonical::number(message.fields.part_count.get().value());
        values[entry + ".payload.news5message.partnumber"] = canonical::number(message.fields.part_number.get().value());
        values[entry + ".payload.news5message.newsid"] = (message.fields.news_id.get().has_value() ? canonical::number(message.fields.news_id.get().value()) : canonical::absent());
        values[entry + ".payload.news5message.origtime"] = (message.fields.orig_time.get().has_value() ? canonical::number(message.fields.orig_time.get().value()) : canonical::absent());
        values[entry + ".payload.news5message.totaltextlength"] = canonical::number(message.fields.total_text_length.get().value());
    }

    void on_message(const protocol::opening_price_15_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.openingprice15message";
        values[entry + ".payload.openingprice15message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.openingprice15message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.openingprice15message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.openingprice15message.mdupdateaction"] = canonical::number(message.fields.md_update_action.get().value());
        values[entry + ".payload.openingprice15message.openclosesettlflag"] = canonical::number(message.fields.open_close_settl_flag.get().value());
        values[entry + ".payload.openingprice15message.mdfutureprice"] = canonical::scaled(message.fields.md_future_price.get().value(), -4);
        values[entry + ".payload.openingprice15message.netchgprevday"] = (message.fields.net_chg_prev_day.get().has_value() ? canonical::scaled(message.fields.net_chg_prev_day.get().value(), -8) : canonical::absent());
        values[entry + ".payload.openingprice15message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.openingprice15message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.openingprice15message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::theoretical_opening_price_16_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.theoreticalopeningprice16message";
        values[entry + ".payload.theoreticalopeningprice16message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.theoreticalopeningprice16message.mdupdateaction"] = canonical::number(message.fields.md_update_action.get().value());
        values[entry + ".payload.theoreticalopeningprice16message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.theoreticalopeningprice16message.mdcorporateoffsetpriceoptional"] = (message.fields.md_corporate_offset_price_optional.get().has_value() ? canonical::scaled(message.fields.md_corporate_offset_price_optional.get().value(), -4) : canonical::absent());
        values[entry + ".payload.theoreticalopeningprice16message.mdentrysizeoptional"] = (message.fields.md_entry_size_optional.get().has_value() ? canonical::number(message.fields.md_entry_size_optional.get().value()) : canonical::absent());
        values[entry + ".payload.theoreticalopeningprice16message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.theoreticalopeningprice16message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::closing_price_17_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.closingprice17message";
        values[entry + ".payload.closingprice17message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.closingprice17message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.closingprice17message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.closingprice17message.openclosesettlflag"] = canonical::number(message.fields.open_close_settl_flag.get().value());
        values[entry + ".payload.closingprice17message.mdcorporateprice"] = canonical::scaled(message.fields.md_corporate_price.get().value(), -8);
        values[entry + ".payload.closingprice17message.lasttradedate"] = (message.fields.last_trade_date.get().has_value() ? canonical::number(message.fields.last_trade_date.get().value()) : canonical::absent());
        values[entry + ".payload.closingprice17message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.closingprice17message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.closingprice17message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::auction_imbalance_19_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.auctionimbalance19message";
        values[entry + ".payload.auctionimbalance19message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.auctionimbalance19message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.auctionimbalance19message.mdupdateaction"] = canonical::number(message.fields.md_update_action.get().value());
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.imbalancemorebuyers"] = canonical::number(static_cast<std::uint64_t>(message.fields.imbalance_condition.has_imbalance_more_buyers()));
        values[entry + ".payload.auctionimbalance19message.imbalancecondition.imbalancemoresellers"] = canonical::number(static_cast<std::uint64_t>(message.fields.imbalance_condition.has_imbalance_more_sellers()));
        values[entry + ".payload.auctionimbalance19message.mdentrysizeoptional"] = (message.fields.md_entry_size_optional.get().has_value() ? canonical::number(message.fields.md_entry_size_optional.get().value()) : canonical::absent());
        values[entry + ".payload.auctionimbalance19message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.auctionimbalance19message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::price_band_20_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.priceband20message";
        values[entry + ".payload.priceband20message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.priceband20message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.priceband20message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.priceband20message.pricebandtype"] = (message.fields.price_band_type.get().has_value() ? canonical::number(message.fields.price_band_type.get().value()) : canonical::absent());
        values[entry + ".payload.priceband20message.pricelimittype"] = (message.fields.price_limit_type.get().has_value() ? canonical::number(message.fields.price_limit_type.get().value()) : canonical::absent());
        values[entry + ".payload.priceband20message.pricebandmidpointpricetype"] = (message.fields.price_band_midpoint_price_type.get().has_value() ? canonical::number(message.fields.price_band_midpoint_price_type.get().value()) : canonical::absent());
        values[entry + ".payload.priceband20message.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -4) : canonical::absent());
        values[entry + ".payload.priceband20message.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -4) : canonical::absent());
        values[entry + ".payload.priceband20message.tradingreferencepricelegacy"] = (message.fields.trading_reference_price_legacy.get().has_value() ? canonical::scaled(message.fields.trading_reference_price_legacy.get().value(), -4) : canonical::absent());
        values[entry + ".payload.priceband20message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.priceband20message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::quantity_band_21_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.quantityband21message";
        values[entry + ".payload.quantityband21message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.quantityband21message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.quantityband21message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.quantityband21message.avgdailytradedqty"] = (message.fields.avg_daily_traded_qty.get().has_value() ? canonical::number(message.fields.avg_daily_traded_qty.get().value()) : canonical::absent());
        values[entry + ".payload.quantityband21message.maxtradevol"] = (message.fields.max_trade_vol.get().has_value() ? canonical::number(message.fields.max_trade_vol.get().value()) : canonical::absent());
        values[entry + ".payload.quantityband21message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.quantityband21message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::price_band_22_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.priceband22message";
        values[entry + ".payload.priceband22message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.priceband22message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.priceband22message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.priceband22message.pricebandtype"] = (message.fields.price_band_type.get().has_value() ? canonical::number(message.fields.price_band_type.get().value()) : canonical::absent());
        values[entry + ".payload.priceband22message.pricelimittype"] = (message.fields.price_limit_type.get().has_value() ? canonical::number(message.fields.price_limit_type.get().value()) : canonical::absent());
        values[entry + ".payload.priceband22message.pricebandmidpointpricetype"] = (message.fields.price_band_midpoint_price_type.get().has_value() ? canonical::number(message.fields.price_band_midpoint_price_type.get().value()) : canonical::absent());
        values[entry + ".payload.priceband22message.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -4) : canonical::absent());
        values[entry + ".payload.priceband22message.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -4) : canonical::absent());
        values[entry + ".payload.priceband22message.tradingreferencepriceoptional"] = (message.fields.trading_reference_price_optional.get().has_value() ? canonical::scaled(message.fields.trading_reference_price_optional.get().value(), -8) : canonical::absent());
        values[entry + ".payload.priceband22message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.priceband22message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::high_price_24_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.highprice24message";
        values[entry + ".payload.highprice24message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.highprice24message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.highprice24message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.highprice24message.mdupdateaction"] = canonical::number(message.fields.md_update_action.get().value());
        values[entry + ".payload.highprice24message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.highprice24message.mdfutureprice"] = canonical::scaled(message.fields.md_future_price.get().value(), -4);
        values[entry + ".payload.highprice24message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.highprice24message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::low_price_25_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.lowprice25message";
        values[entry + ".payload.lowprice25message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.lowprice25message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.lowprice25message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.lowprice25message.mdupdateaction"] = canonical::number(message.fields.md_update_action.get().value());
        values[entry + ".payload.lowprice25message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.lowprice25message.mdfutureprice"] = canonical::scaled(message.fields.md_future_price.get().value(), -4);
        values[entry + ".payload.lowprice25message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.lowprice25message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::last_trade_price_27_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.lasttradeprice27message";
        values[entry + ".payload.lasttradeprice27message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.lasttradeprice27message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.lasttradeprice27message.tradingsessionid"] = canonical::number(message.fields.trading_session_id.get().value());
        values[entry + ".payload.lasttradeprice27message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_opening_price()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_crossed()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_last_trade_at_the_same_price()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_out_of_sequence()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_trade_on_behalf()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_regular_trade()));
        values[entry + ".payload.lasttradeprice27message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_block_trade()));
        values[entry + ".payload.lasttradeprice27message.mdfutureprice"] = canonical::scaled(message.fields.md_future_price.get().value(), -4);
        values[entry + ".payload.lasttradeprice27message.mdentrysize"] = canonical::number(message.fields.md_entry_size.get().value());
        values[entry + ".payload.lasttradeprice27message.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.lasttradeprice27message.mdentrybuyer"] = (message.fields.md_entry_buyer.get().has_value() ? canonical::number(message.fields.md_entry_buyer.get().value()) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.mdentryseller"] = (message.fields.md_entry_seller.get().has_value() ? canonical::number(message.fields.md_entry_seller.get().value()) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.lasttradeprice27message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.sellerdays"] = (message.fields.seller_days.get().has_value() ? canonical::number(message.fields.seller_days.get().value()) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.mdentryinterestrate"] = (message.fields.md_entry_interest_rate.get().has_value() ? canonical::scaled(message.fields.md_entry_interest_rate.get().value(), -4) : canonical::absent());
        values[entry + ".payload.lasttradeprice27message.trdsubtype"] = (message.fields.trd_sub_type.get().has_value() ? canonical::number(message.fields.trd_sub_type.get().value()) : canonical::absent());
    }

    void on_message(const protocol::settlement_price_28_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.settlementprice28message";
        values[entry + ".payload.settlementprice28message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.settlementprice28message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.settlementprice28message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.settlementprice28message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.settlementprice28message.mdfutureprice"] = canonical::scaled(message.fields.md_future_price.get().value(), -4);
        values[entry + ".payload.settlementprice28message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.settlementprice28message.openclosesettlflag"] = canonical::number(message.fields.open_close_settl_flag.get().value());
        values[entry + ".payload.settlementprice28message.pricetype"] = canonical::number(message.fields.price_type.get().value());
        values[entry + ".payload.settlementprice28message.settlpricetype"] = canonical::number(message.fields.settl_price_type.get().value());
        values[entry + ".payload.settlementprice28message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::open_interest_29_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.openinterest29message";
        values[entry + ".payload.openinterest29message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.openinterest29message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.openinterest29message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.openinterest29message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.openinterest29message.mdentrysize"] = canonical::number(message.fields.md_entry_size.get().value());
        values[entry + ".payload.openinterest29message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.openinterest29message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::snapshot_full_refresh_header_30_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshheader30message";
        values[entry + ".payload.snapshotfullrefreshheader30message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.snapshotfullrefreshheader30message.lastmsgseqnumprocessed"] = canonical::number(message.fields.last_msg_seq_num_processed.get().value());
        values[entry + ".payload.snapshotfullrefreshheader30message.totnumreports"] = canonical::number(message.fields.tot_num_reports.get().value());
        values[entry + ".payload.snapshotfullrefreshheader30message.totnumbids"] = canonical::number(message.fields.tot_num_bids.get().value());
        values[entry + ".payload.snapshotfullrefreshheader30message.totnumoffers"] = canonical::number(message.fields.tot_num_offers.get().value());
        values[entry + ".payload.snapshotfullrefreshheader30message.totnumstats"] = canonical::number(message.fields.tot_num_stats.get().value());
        values[entry + ".payload.snapshotfullrefreshheader30message.lastrptseq"] = (message.fields.last_rpt_seq.get().has_value() ? canonical::number(message.fields.last_rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::order_mb_o_50_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.ordermbo50message";
        values[entry + ".payload.ordermbo50message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.ordermbo50message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.ordermbo50message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.ordermbo50message.mdupdateaction"] = canonical::number(message.fields.md_update_action.get().value());
        values[entry + ".payload.ordermbo50message.mdentrytype"] = canonical::text(canonical::character(message.fields.md_entry_type.get().value()));
        values[entry + ".payload.ordermbo50message.mdcorporateoffsetpriceoptional"] = (message.fields.md_corporate_offset_price_optional.get().has_value() ? canonical::scaled(message.fields.md_corporate_offset_price_optional.get().value(), -4) : canonical::absent());
        values[entry + ".payload.ordermbo50message.mdentrysize"] = canonical::number(message.fields.md_entry_size.get().value());
        values[entry + ".payload.ordermbo50message.mdentrypositionno"] = canonical::number(message.fields.md_entry_position_no.get().value());
        values[entry + ".payload.ordermbo50message.enteringfirm"] = (message.fields.entering_firm.get().has_value() ? canonical::number(message.fields.entering_firm.get().value()) : canonical::absent());
        values[entry + ".payload.ordermbo50message.mdinserttimestamp"] = (message.fields.md_insert_timestamp.get().has_value() ? canonical::number(message.fields.md_insert_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.ordermbo50message.secondaryorderid"] = canonical::number(message.fields.secondary_order_id.get().value());
        values[entry + ".payload.ordermbo50message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
        values[entry + ".payload.ordermbo50message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
    }

    void on_message(const protocol::delete_order_mb_o_51_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.deleteordermbo51message";
        values[entry + ".payload.deleteordermbo51message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.deleteordermbo51message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.deleteordermbo51message.mdentrytype"] = canonical::text(canonical::character(message.fields.md_entry_type.get().value()));
        values[entry + ".payload.deleteordermbo51message.mdentrypositionno"] = canonical::number(message.fields.md_entry_position_no.get().value());
        values[entry + ".payload.deleteordermbo51message.mdentrysizeoptional"] = (message.fields.md_entry_size_optional.get().has_value() ? canonical::number(message.fields.md_entry_size_optional.get().value()) : canonical::absent());
        values[entry + ".payload.deleteordermbo51message.secondaryorderid"] = canonical::number(message.fields.secondary_order_id.get().value());
        values[entry + ".payload.deleteordermbo51message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.deleteordermbo51message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::mass_delete_orders_mb_o_52_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.massdeleteordersmbo52message";
        values[entry + ".payload.massdeleteordersmbo52message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.massdeleteordersmbo52message.mdupdateaction"] = canonical::number(message.fields.md_update_action.get().value());
        values[entry + ".payload.massdeleteordersmbo52message.mdentrytype"] = canonical::text(canonical::character(message.fields.md_entry_type.get().value()));
        values[entry + ".payload.massdeleteordersmbo52message.mdentrypositionno"] = canonical::number(message.fields.md_entry_position_no.get().value());
        values[entry + ".payload.massdeleteordersmbo52message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.massdeleteordersmbo52message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::trade_53_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.trade53message";
        values[entry + ".payload.trade53message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.trade53message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.trade53message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.trade53message.tradingsessionid"] = canonical::number(message.fields.trading_session_id.get().value());
        values[entry + ".payload.trade53message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_opening_price()));
        values[entry + ".payload.trade53message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_crossed()));
        values[entry + ".payload.trade53message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_last_trade_at_the_same_price()));
        values[entry + ".payload.trade53message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_out_of_sequence()));
        values[entry + ".payload.trade53message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_trade_on_behalf()));
        values[entry + ".payload.trade53message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_regular_trade()));
        values[entry + ".payload.trade53message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_block_trade()));
        values[entry + ".payload.trade53message.mdfutureprice"] = canonical::scaled(message.fields.md_future_price.get().value(), -4);
        values[entry + ".payload.trade53message.mdentrysize"] = canonical::number(message.fields.md_entry_size.get().value());
        values[entry + ".payload.trade53message.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.trade53message.mdentrybuyer"] = (message.fields.md_entry_buyer.get().has_value() ? canonical::number(message.fields.md_entry_buyer.get().value()) : canonical::absent());
        values[entry + ".payload.trade53message.mdentryseller"] = (message.fields.md_entry_seller.get().has_value() ? canonical::number(message.fields.md_entry_seller.get().value()) : canonical::absent());
        values[entry + ".payload.trade53message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.trade53message.trdsubtype"] = (message.fields.trd_sub_type.get().has_value() ? canonical::number(message.fields.trd_sub_type.get().value()) : canonical::absent());
        values[entry + ".payload.trade53message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.trade53message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::forward_trade_54_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.forwardtrade54message";
        values[entry + ".payload.forwardtrade54message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.forwardtrade54message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.forwardtrade54message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.forwardtrade54message.tradingsessionid"] = canonical::number(message.fields.trading_session_id.get().value());
        values[entry + ".payload.forwardtrade54message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_opening_price()));
        values[entry + ".payload.forwardtrade54message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_crossed()));
        values[entry + ".payload.forwardtrade54message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_last_trade_at_the_same_price()));
        values[entry + ".payload.forwardtrade54message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_out_of_sequence()));
        values[entry + ".payload.forwardtrade54message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_trade_on_behalf()));
        values[entry + ".payload.forwardtrade54message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_regular_trade()));
        values[entry + ".payload.forwardtrade54message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_condition.has_block_trade()));
        values[entry + ".payload.forwardtrade54message.mdfutureprice"] = canonical::scaled(message.fields.md_future_price.get().value(), -4);
        values[entry + ".payload.forwardtrade54message.mdentrysize"] = canonical::number(message.fields.md_entry_size.get().value());
        values[entry + ".payload.forwardtrade54message.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.forwardtrade54message.mdentrybuyer"] = (message.fields.md_entry_buyer.get().has_value() ? canonical::number(message.fields.md_entry_buyer.get().value()) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.mdentryseller"] = (message.fields.md_entry_seller.get().has_value() ? canonical::number(message.fields.md_entry_seller.get().value()) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.forwardtrade54message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.sellerdays"] = (message.fields.seller_days.get().has_value() ? canonical::number(message.fields.seller_days.get().value()) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.mdentryinterestrate"] = (message.fields.md_entry_interest_rate.get().has_value() ? canonical::scaled(message.fields.md_entry_interest_rate.get().value(), -4) : canonical::absent());
        values[entry + ".payload.forwardtrade54message.trdsubtype"] = (message.fields.trd_sub_type.get().has_value() ? canonical::number(message.fields.trd_sub_type.get().value()) : canonical::absent());
    }

    void on_message(const protocol::execution_summary_55_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.executionsummary55message";
        values[entry + ".payload.executionsummary55message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.executionsummary55message.aggressorside"] = canonical::number(message.fields.aggressor_side.get().value());
        values[entry + ".payload.executionsummary55message.lastpx"] = canonical::scaled(message.fields.last_px.get().value(), -4);
        values[entry + ".payload.executionsummary55message.fillqty"] = canonical::number(message.fields.fill_qty.get().value());
        values[entry + ".payload.executionsummary55message.tradedhiddenqty"] = (message.fields.traded_hidden_qty.get().has_value() ? canonical::number(message.fields.traded_hidden_qty.get().value()) : canonical::absent());
        values[entry + ".payload.executionsummary55message.cxlqty"] = (message.fields.cxl_qty.get().has_value() ? canonical::number(message.fields.cxl_qty.get().value()) : canonical::absent());
        values[entry + ".payload.executionsummary55message.aggressortime"] = (message.fields.aggressor_time.get().has_value() ? canonical::number(message.fields.aggressor_time.get().value()) : canonical::absent());
        values[entry + ".payload.executionsummary55message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
        values[entry + ".payload.executionsummary55message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
    }

    void on_message(const protocol::execution_statistics_56_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.executionstatistics56message";
        values[entry + ".payload.executionstatistics56message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.executionstatistics56message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.executionstatistics56message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.executionstatistics56message.tradingsessionid"] = canonical::number(message.fields.trading_session_id.get().value());
        values[entry + ".payload.executionstatistics56message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.executionstatistics56message.tradevolume"] = canonical::number(message.fields.trade_volume.get().value());
        values[entry + ".payload.executionstatistics56message.vwappx"] = (message.fields.vwap_px.get().has_value() ? canonical::scaled(message.fields.vwap_px.get().value(), -4) : canonical::absent());
        values[entry + ".payload.executionstatistics56message.netchgprevday"] = (message.fields.net_chg_prev_day.get().has_value() ? canonical::scaled(message.fields.net_chg_prev_day.get().value(), -8) : canonical::absent());
        values[entry + ".payload.executionstatistics56message.numberoftrades"] = canonical::number(message.fields.number_of_trades.get().value());
        values[entry + ".payload.executionstatistics56message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.executionstatistics56message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::trade_bust_57_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.tradebust57message";
        values[entry + ".payload.tradebust57message.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.tradebust57message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.tradebust57message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.tradebust57message.tradingsessionid"] = canonical::number(message.fields.trading_session_id.get().value());
        values[entry + ".payload.tradebust57message.mdfutureprice"] = canonical::scaled(message.fields.md_future_price.get().value(), -4);
        values[entry + ".payload.tradebust57message.mdentrysize"] = canonical::number(message.fields.md_entry_size.get().value());
        values[entry + ".payload.tradebust57message.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.tradebust57message.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.tradebust57message.mdentrytimestamp"] = (message.fields.md_entry_timestamp.get().has_value() ? canonical::number(message.fields.md_entry_timestamp.get().value()) : canonical::absent());
        values[entry + ".payload.tradebust57message.rptseq"] = (message.fields.rpt_seq.get().has_value() ? canonical::number(message.fields.rpt_seq.get().value()) : canonical::absent());
    }

    void on_message(const protocol::snapshot_full_refresh_orders_mb_o_71_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".framingheader.encodingtype"] = canonical::number(message.header.encoding_type.get().value());
        values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshordersmbo71message";
        values[entry + ".payload.snapshotfullrefreshordersmbo71message.securityid"] = canonical::number(message.fields.security_id.get().value());
    }
};

// The values Advanced reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.values;
}

// Read each datagram of a sample with Advanced and hold it to the model's values
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
    std::printf("== B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 (advanced values)\n");
    int failures = 0;
    failures += check("SecurityDefinitionMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SecurityDefinitionMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SecurityDefinitionMessage.values");
    failures += check("SequenceMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SequenceMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SequenceMessage.values");
    return failures == 0 ? 0 : 1;
}
