// Cme.Globex.Mdp3.Sbe.v1.9 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/cme/globex/mdp3/sbe/v1.9/messages/session.hpp"

namespace protocol = ::cme::mdp3::v9;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::binary_packet_header& header, const packet::Frame&) {
        values["udppacket.binarypacketheader.packetsequencenumber"] = canonical::number(header.packet_sequence_number.get().value());
        values["udppacket.binarypacketheader.sendingtime"] = canonical::number(header.sending_time.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::binary_packet_header&) {
        ++index;
    }

    void on_message(const protocol::channel_reset& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.channelreset";
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::admin_login& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.adminlogin";
        values[entry + ".payload.mktdatamessage.mktdatapayload.adminlogin.heartbtint"] = canonical::number(message.fields.heart_bt_int.get().value());
    }

    void on_message(const protocol::admin_logout& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.adminlogout";
        values[entry + ".payload.mktdatamessage.mktdatapayload.adminlogout.text"] = canonical::text(std::string(message.fields.text.get().value()), '\0', false);
    }

    void on_message(const protocol::md_instrument_definition_future_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.totnumreportsoptional"] = (message.fields.tot_num_reports_optional.get().has_value() ? canonical::number(message.fields.tot_num_reports_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securityupdateaction"] = canonical::text(canonical::character(message.fields.security_update_action.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.lastupdatetime"] = canonical::number(message.fields.last_update_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.mdsecuritytradingstatus"] = (message.fields.md_security_trading_status.get().has_value() ? canonical::number(message.fields.md_security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.applid"] = canonical::number(message.fields.appl_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.marketsegmentid"] = canonical::number(message.fields.market_segment_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.underlyingproduct"] = canonical::number(message.fields.underlying_product.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securityexchange"] = canonical::text(std::string(message.fields.security_exchange.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securitytype"] = canonical::text(std::string(message.fields.security_type.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maturitymonthyear.year"] = (message.fields.maturity_month_year.year.get().has_value() ? canonical::number(message.fields.maturity_month_year.year.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maturitymonthyear.month"] = (message.fields.maturity_month_year.month.get().has_value() ? canonical::number(message.fields.maturity_month_year.month.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maturitymonthyear.day"] = (message.fields.maturity_month_year.day.get().has_value() ? canonical::number(message.fields.maturity_month_year.day.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maturitymonthyear.week"] = (message.fields.maturity_month_year.week.get().has_value() ? canonical::number(message.fields.maturity_month_year.week.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.currency"] = canonical::text(std::string(message.fields.currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlcurrency"] = canonical::text(std::string(message.fields.settl_currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matchalgorithm"] = canonical::text(canonical::character(message.fields.match_algorithm.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.mintradevol"] = canonical::number(message.fields.min_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maxtradevol"] = canonical::number(message.fields.max_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.minpriceincrement"] = canonical::scaled(message.fields.min_price_increment.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.displayfactor"] = canonical::scaled(message.fields.display_factor.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.unitofmeasureqty"] = (message.fields.unit_of_measure_qty.get().has_value() ? canonical::scaled(message.fields.unit_of_measure_qty.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.tradingreferenceprice"] = (message.fields.trading_reference_price.get().has_value() ? canonical::scaled(message.fields.trading_reference_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maxpricevariation"] = (message.fields.max_price_variation.get().has_value() ? canonical::scaled(message.fields.max_price_variation.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.decayquantity"] = (message.fields.decay_quantity.get().has_value() ? canonical::number(message.fields.decay_quantity.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.decaystartdate"] = (message.fields.decay_start_date.get().has_value() ? canonical::number(message.fields.decay_start_date.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.originalcontractsize"] = (message.fields.original_contract_size.get().has_value() ? canonical::number(message.fields.original_contract_size.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.contractmultiplier"] = (message.fields.contract_multiplier.get().has_value() ? canonical::number(message.fields.contract_multiplier.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.contractmultiplierunit"] = (message.fields.contract_multiplier_unit.get().has_value() ? canonical::number(message.fields.contract_multiplier_unit.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.flowscheduletype"] = (message.fields.flow_schedule_type.get().has_value() ? canonical::number(message.fields.flow_schedule_type.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.minpriceincrementamount"] = (message.fields.min_price_increment_amount.get().has_value() ? canonical::scaled(message.fields.min_price_increment_amount.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.userdefinedinstrument"] = canonical::text(canonical::character(message.fields.user_defined_instrument.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.tradingreferencedate"] = (message.fields.trading_reference_date.get().has_value() ? canonical::number(message.fields.trading_reference_date.get().value()) : canonical::absent());
    }

    void on_message(const protocol::md_instrument_definition_spread_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.totnumreportsoptional"] = (message.fields.tot_num_reports_optional.get().has_value() ? canonical::number(message.fields.tot_num_reports_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securityupdateaction"] = canonical::text(canonical::character(message.fields.security_update_action.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.lastupdatetime"] = canonical::number(message.fields.last_update_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.mdsecuritytradingstatus"] = (message.fields.md_security_trading_status.get().has_value() ? canonical::number(message.fields.md_security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.applid"] = canonical::number(message.fields.appl_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.marketsegmentid"] = canonical::number(message.fields.market_segment_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.underlyingproductoptional"] = (message.fields.underlying_product_optional.get().has_value() ? canonical::number(message.fields.underlying_product_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securityexchange"] = canonical::text(std::string(message.fields.security_exchange.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securitytype"] = canonical::text(std::string(message.fields.security_type.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maturitymonthyear.year"] = (message.fields.maturity_month_year.year.get().has_value() ? canonical::number(message.fields.maturity_month_year.year.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maturitymonthyear.month"] = (message.fields.maturity_month_year.month.get().has_value() ? canonical::number(message.fields.maturity_month_year.month.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maturitymonthyear.day"] = (message.fields.maturity_month_year.day.get().has_value() ? canonical::number(message.fields.maturity_month_year.day.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maturitymonthyear.week"] = (message.fields.maturity_month_year.week.get().has_value() ? canonical::number(message.fields.maturity_month_year.week.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.currency"] = canonical::text(std::string(message.fields.currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securitysubtype"] = canonical::text(std::string(message.fields.security_sub_type.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.userdefinedinstrument"] = canonical::text(canonical::character(message.fields.user_defined_instrument.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matchalgorithm"] = canonical::text(canonical::character(message.fields.match_algorithm.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.mintradevol"] = canonical::number(message.fields.min_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maxtradevol"] = canonical::number(message.fields.max_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.minpriceincrement"] = canonical::scaled(message.fields.min_price_increment.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.displayfactor"] = canonical::scaled(message.fields.display_factor.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.priceratio"] = (message.fields.price_ratio.get().has_value() ? canonical::scaled(message.fields.price_ratio.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.tickrule"] = (message.fields.tick_rule.get().has_value() ? canonical::number(message.fields.tick_rule.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.tradingreferenceprice"] = (message.fields.trading_reference_price.get().has_value() ? canonical::scaled(message.fields.trading_reference_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maxpricevariation"] = (message.fields.max_price_variation.get().has_value() ? canonical::scaled(message.fields.max_price_variation.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.tradingreferencedate"] = (message.fields.trading_reference_date.get().has_value() ? canonical::number(message.fields.trading_reference_date.get().value()) : canonical::absent());
    }

    void on_message(const protocol::security_status& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.securitystatus";
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securityidoptional"] = (message.fields.security_id_optional.get().has_value() ? canonical::number(message.fields.security_id_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.tradedate"] = (message.fields.trade_date.get().has_value() ? canonical::number(message.fields.trade_date.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitytradingstatus"] = (message.fields.security_trading_status.get().has_value() ? canonical::number(message.fields.security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.haltreason"] = canonical::number(message.fields.halt_reason.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitytradingevent"] = canonical::number(message.fields.security_trading_event.get().value());
    }

    void on_message(const protocol::md_incremental_refresh_book_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_daily_statistics_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_limits_banding_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_session_statistics_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_volume& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::snapshot_full_refresh_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.lastmsgseqnumprocessed"] = canonical::number(message.fields.last_msg_seq_num_processed.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.totnumreports"] = canonical::number(message.fields.tot_num_reports.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.rptseq"] = canonical::number(message.fields.rpt_seq.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.lastupdatetime"] = canonical::number(message.fields.last_update_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.tradedate"] = (message.fields.trade_date.get().has_value() ? canonical::number(message.fields.trade_date.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.mdsecuritytradingstatus"] = (message.fields.md_security_trading_status.get().has_value() ? canonical::number(message.fields.md_security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.maxpricevariation"] = (message.fields.max_price_variation.get().has_value() ? canonical::scaled(message.fields.max_price_variation.get().value(), -7) : canonical::absent());
    }

    void on_message(const protocol::quote_request& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.quoterequest";
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.quotereqid"] = canonical::text(std::string(message.fields.quote_req_id.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_instrument_definition_option_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.totnumreportsoptional"] = (message.fields.tot_num_reports_optional.get().has_value() ? canonical::number(message.fields.tot_num_reports_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securityupdateaction"] = canonical::text(canonical::character(message.fields.security_update_action.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.lastupdatetime"] = canonical::number(message.fields.last_update_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.mdsecuritytradingstatus"] = (message.fields.md_security_trading_status.get().has_value() ? canonical::number(message.fields.md_security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.applid"] = canonical::number(message.fields.appl_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.marketsegmentid"] = canonical::number(message.fields.market_segment_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.underlyingproduct"] = canonical::number(message.fields.underlying_product.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securityexchange"] = canonical::text(std::string(message.fields.security_exchange.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securitytype"] = canonical::text(std::string(message.fields.security_type.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.putorcall"] = canonical::number(message.fields.put_or_call.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maturitymonthyear.year"] = (message.fields.maturity_month_year.year.get().has_value() ? canonical::number(message.fields.maturity_month_year.year.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maturitymonthyear.month"] = (message.fields.maturity_month_year.month.get().has_value() ? canonical::number(message.fields.maturity_month_year.month.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maturitymonthyear.day"] = (message.fields.maturity_month_year.day.get().has_value() ? canonical::number(message.fields.maturity_month_year.day.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maturitymonthyear.week"] = (message.fields.maturity_month_year.week.get().has_value() ? canonical::number(message.fields.maturity_month_year.week.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.currency"] = canonical::text(std::string(message.fields.currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.strikeprice"] = (message.fields.strike_price.get().has_value() ? canonical::scaled(message.fields.strike_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.strikecurrency"] = canonical::text(std::string(message.fields.strike_currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlcurrency"] = canonical::text(std::string(message.fields.settl_currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.mincabprice"] = (message.fields.min_cab_price.get().has_value() ? canonical::scaled(message.fields.min_cab_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matchalgorithm"] = canonical::text(canonical::character(message.fields.match_algorithm.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.mintradevol"] = canonical::number(message.fields.min_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maxtradevol"] = canonical::number(message.fields.max_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.minpriceincrementoptional"] = (message.fields.min_price_increment_optional.get().has_value() ? canonical::scaled(message.fields.min_price_increment_optional.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.minpriceincrementamount"] = (message.fields.min_price_increment_amount.get().has_value() ? canonical::scaled(message.fields.min_price_increment_amount.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.displayfactor"] = canonical::scaled(message.fields.display_factor.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.tickrule"] = (message.fields.tick_rule.get().has_value() ? canonical::number(message.fields.tick_rule.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.unitofmeasureqty"] = (message.fields.unit_of_measure_qty.get().has_value() ? canonical::scaled(message.fields.unit_of_measure_qty.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.tradingreferenceprice"] = (message.fields.trading_reference_price.get().has_value() ? canonical::scaled(message.fields.trading_reference_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.userdefinedinstrument"] = canonical::text(canonical::character(message.fields.user_defined_instrument.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.tradingreferencedate"] = (message.fields.trading_reference_date.get().has_value() ? canonical::number(message.fields.trading_reference_date.get().value()) : canonical::absent());
    }

    void on_message(const protocol::md_incremental_refresh_trade_summary_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_order_book_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::snapshot_full_refresh_order_book_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.lastmsgseqnumprocessed"] = canonical::number(message.fields.last_msg_seq_num_processed.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.totnumreports"] = canonical::number(message.fields.tot_num_reports.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.nochunks"] = canonical::number(message.fields.no_chunks.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.currentchunk"] = canonical::number(message.fields.current_chunk.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.transacttime"] = canonical::number(message.fields.transact_time.get().value());
    }

    void on_message(const protocol::md_incremental_refresh_book& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_order_book& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_trade_summary& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_daily_statistics& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_limits_banding& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::md_incremental_refresh_session_statistics& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
    }

    void on_message(const protocol::snapshot_full_refresh& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefresh";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lastmsgseqnumprocessed"] = canonical::number(message.fields.last_msg_seq_num_processed.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.totnumreports"] = canonical::number(message.fields.tot_num_reports.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.rptseq"] = canonical::number(message.fields.rpt_seq.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lastupdatetime"] = canonical::number(message.fields.last_update_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.tradedate"] = (message.fields.trade_date.get().has_value() ? canonical::number(message.fields.trade_date.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.mdsecuritytradingstatus"] = (message.fields.md_security_trading_status.get().has_value() ? canonical::number(message.fields.md_security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.highlimitpriceex"] = (message.fields.high_limit_price_ex.get().has_value() ? canonical::scaled(message.fields.high_limit_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lowlimitpriceex"] = (message.fields.low_limit_price_ex.get().has_value() ? canonical::scaled(message.fields.low_limit_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.maxpricevariationex"] = (message.fields.max_price_variation_ex.get().has_value() ? canonical::scaled(message.fields.max_price_variation_ex.get().value(), -9) : canonical::absent());
    }

    void on_message(const protocol::snapshot_full_refresh_order_book& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.lastmsgseqnumprocessed"] = canonical::number(message.fields.last_msg_seq_num_processed.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.totnumreports"] = canonical::number(message.fields.tot_num_reports.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.nochunks"] = canonical::number(message.fields.no_chunks.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.currentchunk"] = canonical::number(message.fields.current_chunk.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.transacttime"] = canonical::number(message.fields.transact_time.get().value());
    }

    void on_message(const protocol::md_instrument_definition_future& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.totnumreportsoptional"] = (message.fields.tot_num_reports_optional.get().has_value() ? canonical::number(message.fields.tot_num_reports_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityupdateaction"] = canonical::text(canonical::character(message.fields.security_update_action.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.lastupdatetime"] = canonical::number(message.fields.last_update_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mdsecuritytradingstatus"] = (message.fields.md_security_trading_status.get().has_value() ? canonical::number(message.fields.md_security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.applid"] = canonical::number(message.fields.appl_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.marketsegmentid"] = canonical::number(message.fields.market_segment_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.underlyingproduct"] = canonical::number(message.fields.underlying_product.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityexchange"] = canonical::text(std::string(message.fields.security_exchange.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securitytype"] = canonical::text(std::string(message.fields.security_type.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.year"] = (message.fields.maturity_month_year.year.get().has_value() ? canonical::number(message.fields.maturity_month_year.year.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.month"] = (message.fields.maturity_month_year.month.get().has_value() ? canonical::number(message.fields.maturity_month_year.month.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.day"] = (message.fields.maturity_month_year.day.get().has_value() ? canonical::number(message.fields.maturity_month_year.day.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.week"] = (message.fields.maturity_month_year.week.get().has_value() ? canonical::number(message.fields.maturity_month_year.week.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.currency"] = canonical::text(std::string(message.fields.currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlcurrency"] = canonical::text(std::string(message.fields.settl_currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matchalgorithm"] = canonical::text(canonical::character(message.fields.match_algorithm.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mintradevol"] = canonical::number(message.fields.min_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maxtradevol"] = canonical::number(message.fields.max_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrementex"] = canonical::scaled(message.fields.min_price_increment_ex.get().value(), -9);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.displayfactorex"] = canonical::scaled(message.fields.display_factor_ex.get().value(), -9);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasureqtyex"] = (message.fields.unit_of_measure_qty_ex.get().has_value() ? canonical::scaled(message.fields.unit_of_measure_qty_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.tradingreferencepriceex"] = (message.fields.trading_reference_price_ex.get().has_value() ? canonical::scaled(message.fields.trading_reference_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.highlimitpriceex"] = (message.fields.high_limit_price_ex.get().has_value() ? canonical::scaled(message.fields.high_limit_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.lowlimitpriceex"] = (message.fields.low_limit_price_ex.get().has_value() ? canonical::scaled(message.fields.low_limit_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maxpricevariationex"] = (message.fields.max_price_variation_ex.get().has_value() ? canonical::scaled(message.fields.max_price_variation_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decayquantity"] = (message.fields.decay_quantity.get().has_value() ? canonical::number(message.fields.decay_quantity.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decaystartdate"] = (message.fields.decay_start_date.get().has_value() ? canonical::number(message.fields.decay_start_date.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.originalcontractsize"] = (message.fields.original_contract_size.get().has_value() ? canonical::number(message.fields.original_contract_size.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplier"] = (message.fields.contract_multiplier.get().has_value() ? canonical::number(message.fields.contract_multiplier.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplierunit"] = (message.fields.contract_multiplier_unit.get().has_value() ? canonical::number(message.fields.contract_multiplier_unit.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.flowscheduletype"] = (message.fields.flow_schedule_type.get().has_value() ? canonical::number(message.fields.flow_schedule_type.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrementamountex"] = (message.fields.min_price_increment_amount_ex.get().has_value() ? canonical::scaled(message.fields.min_price_increment_amount_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.userdefinedinstrument"] = canonical::text(canonical::character(message.fields.user_defined_instrument.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.tradingreferencedate"] = (message.fields.trading_reference_date.get().has_value() ? canonical::number(message.fields.trading_reference_date.get().value()) : canonical::absent());
    }

    void on_message(const protocol::md_instrument_definition_option& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.totnumreportsoptional"] = (message.fields.tot_num_reports_optional.get().has_value() ? canonical::number(message.fields.tot_num_reports_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityupdateaction"] = canonical::text(canonical::character(message.fields.security_update_action.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.lastupdatetime"] = canonical::number(message.fields.last_update_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mdsecuritytradingstatus"] = (message.fields.md_security_trading_status.get().has_value() ? canonical::number(message.fields.md_security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.applid"] = canonical::number(message.fields.appl_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.marketsegmentid"] = canonical::number(message.fields.market_segment_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.underlyingproduct"] = canonical::number(message.fields.underlying_product.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityexchange"] = canonical::text(std::string(message.fields.security_exchange.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securitytype"] = canonical::text(std::string(message.fields.security_type.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.putorcall"] = canonical::number(message.fields.put_or_call.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.year"] = (message.fields.maturity_month_year.year.get().has_value() ? canonical::number(message.fields.maturity_month_year.year.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.month"] = (message.fields.maturity_month_year.month.get().has_value() ? canonical::number(message.fields.maturity_month_year.month.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.day"] = (message.fields.maturity_month_year.day.get().has_value() ? canonical::number(message.fields.maturity_month_year.day.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.week"] = (message.fields.maturity_month_year.week.get().has_value() ? canonical::number(message.fields.maturity_month_year.week.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.currency"] = canonical::text(std::string(message.fields.currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikepriceex"] = (message.fields.strike_price_ex.get().has_value() ? canonical::scaled(message.fields.strike_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikecurrency"] = canonical::text(std::string(message.fields.strike_currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlcurrency"] = canonical::text(std::string(message.fields.settl_currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mincabpriceex"] = (message.fields.min_cab_price_ex.get().has_value() ? canonical::scaled(message.fields.min_cab_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matchalgorithm"] = canonical::text(canonical::character(message.fields.match_algorithm.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mintradevol"] = canonical::number(message.fields.min_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maxtradevol"] = canonical::number(message.fields.max_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementoptionalex"] = (message.fields.min_price_increment_optional_ex.get().has_value() ? canonical::scaled(message.fields.min_price_increment_optional_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementamountex"] = (message.fields.min_price_increment_amount_ex.get().has_value() ? canonical::scaled(message.fields.min_price_increment_amount_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.displayfactorex"] = canonical::scaled(message.fields.display_factor_ex.get().value(), -9);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tickrule"] = (message.fields.tick_rule.get().has_value() ? canonical::number(message.fields.tick_rule.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasureqtyex"] = (message.fields.unit_of_measure_qty_ex.get().has_value() ? canonical::scaled(message.fields.unit_of_measure_qty_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tradingreferencepriceex"] = (message.fields.trading_reference_price_ex.get().has_value() ? canonical::scaled(message.fields.trading_reference_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.lowlimitpriceex"] = (message.fields.low_limit_price_ex.get().has_value() ? canonical::scaled(message.fields.low_limit_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.highlimitpriceex"] = (message.fields.high_limit_price_ex.get().has_value() ? canonical::scaled(message.fields.high_limit_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.userdefinedinstrument"] = canonical::text(canonical::character(message.fields.user_defined_instrument.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tradingreferencedate"] = (message.fields.trading_reference_date.get().has_value() ? canonical::number(message.fields.trading_reference_date.get().value()) : canonical::absent());
    }

    void on_message(const protocol::md_instrument_definition_spread& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.totnumreportsoptional"] = (message.fields.tot_num_reports_optional.get().has_value() ? canonical::number(message.fields.tot_num_reports_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityupdateaction"] = canonical::text(canonical::character(message.fields.security_update_action.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.lastupdatetime"] = canonical::number(message.fields.last_update_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mdsecuritytradingstatus"] = (message.fields.md_security_trading_status.get().has_value() ? canonical::number(message.fields.md_security_trading_status.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.applid"] = canonical::number(message.fields.appl_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.marketsegmentid"] = canonical::number(message.fields.market_segment_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.underlyingproductoptional"] = (message.fields.underlying_product_optional.get().has_value() ? canonical::number(message.fields.underlying_product_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityexchange"] = canonical::text(std::string(message.fields.security_exchange.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitygroup"] = canonical::text(std::string(message.fields.security_group.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.asset"] = canonical::text(std::string(message.fields.asset.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitytype"] = canonical::text(std::string(message.fields.security_type.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.year"] = (message.fields.maturity_month_year.year.get().has_value() ? canonical::number(message.fields.maturity_month_year.year.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.month"] = (message.fields.maturity_month_year.month.get().has_value() ? canonical::number(message.fields.maturity_month_year.month.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.day"] = (message.fields.maturity_month_year.day.get().has_value() ? canonical::number(message.fields.maturity_month_year.day.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.week"] = (message.fields.maturity_month_year.week.get().has_value() ? canonical::number(message.fields.maturity_month_year.week.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.currency"] = canonical::text(std::string(message.fields.currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitysubtype"] = canonical::text(std::string(message.fields.security_sub_type.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.userdefinedinstrument"] = canonical::text(canonical::character(message.fields.user_defined_instrument.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matchalgorithm"] = canonical::text(canonical::character(message.fields.match_algorithm.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mintradevol"] = canonical::number(message.fields.min_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maxtradevol"] = canonical::number(message.fields.max_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.minpriceincrementoptionalex"] = (message.fields.min_price_increment_optional_ex.get().has_value() ? canonical::scaled(message.fields.min_price_increment_optional_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.displayfactorex"] = canonical::scaled(message.fields.display_factor_ex.get().value(), -9);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.priceratioex"] = (message.fields.price_ratio_ex.get().has_value() ? canonical::scaled(message.fields.price_ratio_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tickrule"] = (message.fields.tick_rule.get().has_value() ? canonical::number(message.fields.tick_rule.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tradingreferencepriceex"] = (message.fields.trading_reference_price_ex.get().has_value() ? canonical::scaled(message.fields.trading_reference_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.highlimitpriceex"] = (message.fields.high_limit_price_ex.get().has_value() ? canonical::scaled(message.fields.high_limit_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.lowlimitpriceex"] = (message.fields.low_limit_price_ex.get().has_value() ? canonical::scaled(message.fields.low_limit_price_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maxpricevariationex"] = (message.fields.max_price_variation_ex.get().has_value() ? canonical::scaled(message.fields.max_price_variation_ex.get().value(), -9) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tradingreferencedate"] = (message.fields.trading_reference_date.get().has_value() ? canonical::number(message.fields.trading_reference_date.get().value()) : canonical::absent());
    }

    void on_message(const protocol::negotiate& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.hmacsignature"] = canonical::text(std::string(message.fields.hmac_signature.get().value()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.accesskeyid"] = canonical::text(std::string(message.fields.access_key_id.get().value()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.uuid"] = canonical::number(message.fields.uuid.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.requesttimestamp"] = canonical::number(message.fields.request_timestamp.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.session"] = canonical::text(std::string(message.fields.session.get().value()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.firm"] = canonical::text(std::string(message.fields.firm.get().value()), '\0', false);
    }

    void on_message(const protocol::negotiation_reject& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.reason"] = canonical::text(std::string(message.fields.reason.get().value()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.uuid"] = canonical::number(message.fields.uuid.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.requesttimestamp"] = canonical::number(message.fields.request_timestamp.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.errorcodes"] = canonical::number(message.fields.error_codes.get().value());
    }

    void on_message(const protocol::negotiation_response& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.uuid"] = canonical::number(message.fields.uuid.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.requesttimestamp"] = canonical::number(message.fields.request_timestamp.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.secretkeysecureidexpiration"] = (message.fields.secret_key_secure_id_expiration.get().has_value() ? canonical::number(message.fields.secret_key_secure_id_expiration.get().value()) : canonical::absent());
    }

    void on_message(const protocol::terminate& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.reason"] = canonical::text(std::string(message.fields.reason.get().value()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.uuid"] = canonical::number(message.fields.uuid.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.requesttimestamp"] = canonical::number(message.fields.request_timestamp.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.errorcodes"] = canonical::number(message.fields.error_codes.get().value());
    }

    void on_message(const protocol::market_data_request& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest.mdreqid"] = canonical::number(message.fields.md_req_id.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest.subscriptionreqtype"] = canonical::number(message.fields.subscription_req_type.get().value());
    }

    void on_message(const protocol::request_ack& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.mdreqid"] = canonical::number(message.fields.md_req_id.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.subscriptionreqtype"] = canonical::number(message.fields.subscription_req_type.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.mdreqidstatus"] = canonical::number(message.fields.md_req_id_status.get().value());
    }

    void on_message(const protocol::request_reject& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.mdreqidoptional"] = (message.fields.md_req_id_optional.get().has_value() ? canonical::number(message.fields.md_req_id_optional.get().value()) : canonical::absent());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.mdreqrejreason"] = canonical::number(message.fields.md_req_rej_reason.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.sessiontext"] = canonical::text(std::string(message.fields.session_text.get().value()), '\0', false);
    }

    void on_message(const protocol::security_list_request& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest.mdreqid"] = canonical::number(message.fields.md_req_id.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest.subscriptionreqtype"] = canonical::number(message.fields.subscription_req_type.get().value());
    }

    void on_message(const protocol::security_status_request& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest.mdreqid"] = canonical::number(message.fields.md_req_id.get().value());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest.subscriptionreqtype"] = canonical::number(message.fields.subscription_req_type.get().value());
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
    std::printf("== Cme.Globex.Mdp3.Sbe.v1.9 (advanced values)\n");
    int failures = 0;
    failures += check("MdIncrementalRefreshBook", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshBook.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshBook.values");
    failures += check("MdIncrementalRefreshOrderBook", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshOrderBook.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshOrderBook.values");
    failures += check("MdIncrementalRefreshTradeSummary", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshTradeSummary.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshTradeSummary.values");
    failures += check("MdIncrementalRefreshVolume", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshVolume.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshVolume.values");
    return failures == 0 ? 0 : 1;
}
