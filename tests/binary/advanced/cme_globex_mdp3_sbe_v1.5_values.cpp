// Cme.Globex.Mdp3.Sbe.v1.5 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/cme/globex/mdp3/sbe/v1.5/messages/session.hpp"

namespace protocol = ::cme::mdp3::v5;

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
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrement"] = canonical::scaled(message.fields.min_price_increment.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.displayfactor"] = canonical::scaled(message.fields.display_factor.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasureqty"] = (message.fields.unit_of_measure_qty.get().has_value() ? canonical::scaled(message.fields.unit_of_measure_qty.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.tradingreferenceprice"] = (message.fields.trading_reference_price.get().has_value() ? canonical::scaled(message.fields.trading_reference_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maxpricevariation"] = (message.fields.max_price_variation.get().has_value() ? canonical::scaled(message.fields.max_price_variation.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decayquantity"] = (message.fields.decay_quantity.get().has_value() ? canonical::number(message.fields.decay_quantity.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decaystartdate"] = (message.fields.decay_start_date.get().has_value() ? canonical::number(message.fields.decay_start_date.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.originalcontractsize"] = (message.fields.original_contract_size.get().has_value() ? canonical::number(message.fields.original_contract_size.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplier"] = (message.fields.contract_multiplier.get().has_value() ? canonical::number(message.fields.contract_multiplier.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplierunit"] = (message.fields.contract_multiplier_unit.get().has_value() ? canonical::number(message.fields.contract_multiplier_unit.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.flowscheduletype"] = (message.fields.flow_schedule_type.get().has_value() ? canonical::number(message.fields.flow_schedule_type.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrementamount"] = (message.fields.min_price_increment_amount.get().has_value() ? canonical::scaled(message.fields.min_price_increment_amount.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.userdefinedinstrument"] = canonical::text(canonical::character(message.fields.user_defined_instrument.get().value()));
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
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.minpriceincrement"] = canonical::scaled(message.fields.min_price_increment.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.displayfactor"] = canonical::scaled(message.fields.display_factor.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.priceratio"] = (message.fields.price_ratio.get().has_value() ? canonical::scaled(message.fields.price_ratio.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tickrule"] = (message.fields.tick_rule.get().has_value() ? canonical::number(message.fields.tick_rule.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tradingreferenceprice"] = (message.fields.trading_reference_price.get().has_value() ? canonical::scaled(message.fields.trading_reference_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maxpricevariation"] = (message.fields.max_price_variation.get().has_value() ? canonical::scaled(message.fields.max_price_variation.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
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

    void on_message(const protocol::md_incremental_refresh_trade& message, std::uint64_t, const protocol::binary_packet_header&) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(message.header.simple_binary_header.block_length.get().value());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(message.header.simple_binary_header.template_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(message.header.simple_binary_header.schema_id.get().value());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(message.header.simple_binary_header.version.get().value());
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.transacttime"] = canonical::number(message.fields.transact_time.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.fields.match_event_indicator.has_end_of_event()));
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
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.maxpricevariation"] = (message.fields.max_price_variation.get().has_value() ? canonical::scaled(message.fields.max_price_variation.get().value(), -7) : canonical::absent());
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
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikeprice"] = (message.fields.strike_price.get().has_value() ? canonical::scaled(message.fields.strike_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikecurrency"] = canonical::text(std::string(message.fields.strike_currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlcurrency"] = canonical::text(std::string(message.fields.settl_currency.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mincabprice"] = (message.fields.min_cab_price.get().has_value() ? canonical::scaled(message.fields.min_cab_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matchalgorithm"] = canonical::text(canonical::character(message.fields.match_algorithm.get().value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mintradevol"] = canonical::number(message.fields.min_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maxtradevol"] = canonical::number(message.fields.max_trade_vol.get().value());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementoptional"] = (message.fields.min_price_increment_optional.get().has_value() ? canonical::scaled(message.fields.min_price_increment_optional.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementamount"] = (message.fields.min_price_increment_amount.get().has_value() ? canonical::scaled(message.fields.min_price_increment_amount.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.displayfactor"] = canonical::scaled(message.fields.display_factor.get().value(), -7);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tickrule"] = (message.fields.tick_rule.get().has_value() ? canonical::number(message.fields.tick_rule.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mainfraction"] = (message.fields.main_fraction.get().has_value() ? canonical::number(message.fields.main_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.subfraction"] = (message.fields.sub_fraction.get().has_value() ? canonical::number(message.fields.sub_fraction.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.pricedisplayformat"] = (message.fields.price_display_format.get().has_value() ? canonical::number(message.fields.price_display_format.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasure"] = canonical::text(std::string(message.fields.unit_of_measure.get().value()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasureqty"] = (message.fields.unit_of_measure_qty.get().has_value() ? canonical::scaled(message.fields.unit_of_measure_qty.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tradingreferenceprice"] = (message.fields.trading_reference_price.get().has_value() ? canonical::scaled(message.fields.trading_reference_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_final()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.fields.settl_price_type.has_null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.clearedvolume"] = (message.fields.cleared_volume.get().has_value() ? canonical::number(message.fields.cleared_volume.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.openinterestqty"] = (message.fields.open_interest_qty.get().has_value() ? canonical::number(message.fields.open_interest_qty.get().value()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.lowlimitprice"] = (message.fields.low_limit_price.get().has_value() ? canonical::scaled(message.fields.low_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.highlimitprice"] = (message.fields.high_limit_price.get().has_value() ? canonical::scaled(message.fields.high_limit_price.get().value(), -7) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.userdefinedinstrument"] = canonical::text(canonical::character(message.fields.user_defined_instrument.get().value()));
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
    std::printf("== Cme.Globex.Mdp3.Sbe.v1.5 (advanced values)\n");
    int failures = 0;
    failures += check("MdIncrementalRefreshBook", "Cme/Globex.Mdp3.Sbe.v1.5/MdIncrementalRefreshBook.pcap", "cme/globex/mdp3/sbe/v1.5/MdIncrementalRefreshBook.values");
    failures += check("MdIncrementalRefreshSessionStatistics", "Cme/Globex.Mdp3.Sbe.v1.5/MdIncrementalRefreshSessionStatistics.pcap", "cme/globex/mdp3/sbe/v1.5/MdIncrementalRefreshSessionStatistics.values");
    failures += check("MdIncrementalRefreshTradeSummary", "Cme/Globex.Mdp3.Sbe.v1.5/MdIncrementalRefreshTradeSummary.pcap", "cme/globex/mdp3/sbe/v1.5/MdIncrementalRefreshTradeSummary.values");
    failures += check("MdIncrementalRefreshVolume", "Cme/Globex.Mdp3.Sbe.v1.5/MdIncrementalRefreshVolume.pcap", "cme/globex/mdp3/sbe/v1.5/MdIncrementalRefreshVolume.values");
    failures += check("MdInstrumentDefinitionSpread", "Cme/Globex.Mdp3.Sbe.v1.5/MdInstrumentDefinitionSpread.pcap", "cme/globex/mdp3/sbe/v1.5/MdInstrumentDefinitionSpread.values");
    return failures == 0 ? 0 : 1;
}
