// Cme.Globex.Mdp3.Sbe.v1.5 canonical values, through the Classes Packet: every value Classes decodes from
// each sample, at its address, held to what the model reads.

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
#include "cpp/binary/classes/cme/globex/mdp3/sbe/v1.5/definitions.hpp"

namespace protocol = ::cme::globex::mdp3::sbe::v1_5;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::UdpPacket packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }

    values["udppacket.binarypacketheader.packetsequencenumber"] = canonical::number(packet.binary_packet_header().packet_sequence_number());
    values["udppacket.binarypacketheader.sendingtime"] = canonical::number(packet.binary_packet_header().sending_time());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(each.message_header().message_size());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(each.message_header().simple_binary_header().block_length());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(each.message_header().simple_binary_header().template_id());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(each.message_header().simple_binary_header().schema_id());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(each.message_header().simple_binary_header().version());

        if (const auto* message = dynamic_cast<const protocol::MktdataMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
            if (const auto* message_2 = dynamic_cast<const protocol::ChannelReset*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.channelreset";
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::AdminLogin*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.adminlogin";
                values[entry + ".payload.mktdatamessage.mktdatapayload.adminlogin.heartbtint"] = canonical::number((*message_2).heart_bt_int());
            } else if (const auto* message_2 = dynamic_cast<const protocol::AdminLogout*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.adminlogout";
                values[entry + ".payload.mktdatamessage.mktdatapayload.adminlogout.text"] = canonical::text(std::string((*message_2).text()), '\0', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdInstrumentDefinitionFuture*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.totnumreportsoptional"] = ((*message_2).tot_num_reports_optional().has_value() ? canonical::number((*(*message_2).tot_num_reports_optional())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityupdateaction"] = canonical::text(canonical::character((*message_2).security_update_action()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.lastupdatetime"] = canonical::number((*message_2).last_update_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mdsecuritytradingstatus"] = ((*message_2).md_security_trading_status().has_value() ? canonical::number((*(*message_2).md_security_trading_status())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.applid"] = canonical::number((*message_2).appl_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.marketsegmentid"] = canonical::number((*message_2).market_segment_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.underlyingproduct"] = canonical::number((*message_2).underlying_product());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityexchange"] = canonical::text(std::string((*message_2).security_exchange()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securitygroup"] = canonical::text(std::string((*message_2).security_group()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.asset"] = canonical::text(std::string((*message_2).asset()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.symbol"] = canonical::text(std::string((*message_2).symbol()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityid"] = canonical::number((*message_2).security_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securitytype"] = canonical::text(std::string((*message_2).security_type()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.cficode"] = canonical::text(std::string((*message_2).cfi_code()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.year"] = ((*message_2).maturity_month_year().year().has_value() ? canonical::number((*(*message_2).maturity_month_year().year())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.month"] = ((*message_2).maturity_month_year().month().has_value() ? canonical::number((*(*message_2).maturity_month_year().month())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.day"] = ((*message_2).maturity_month_year().day().has_value() ? canonical::number((*(*message_2).maturity_month_year().day())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.week"] = ((*message_2).maturity_month_year().week().has_value() ? canonical::number((*(*message_2).maturity_month_year().week())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.currency"] = canonical::text(std::string((*message_2).currency()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlcurrency"] = canonical::text(std::string((*message_2).settl_currency()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matchalgorithm"] = canonical::text(canonical::character((*message_2).match_algorithm()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mintradevol"] = canonical::number((*message_2).min_trade_vol());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maxtradevol"] = canonical::number((*message_2).max_trade_vol());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrement"] = canonical::scaled((*message_2).min_price_increment().mantissa(), (*message_2).min_price_increment().exponent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.displayfactor"] = canonical::scaled((*message_2).display_factor().mantissa(), (*message_2).display_factor().exponent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mainfraction"] = ((*message_2).main_fraction().has_value() ? canonical::number((*(*message_2).main_fraction())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.subfraction"] = ((*message_2).sub_fraction().has_value() ? canonical::number((*(*message_2).sub_fraction())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.pricedisplayformat"] = ((*message_2).price_display_format().has_value() ? canonical::number((*(*message_2).price_display_format())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasure"] = canonical::text(std::string((*message_2).unit_of_measure()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasureqty"] = ((*message_2).unit_of_measure_qty().has_value() ? canonical::scaled((*(*message_2).unit_of_measure_qty()).mantissa(), (*(*message_2).unit_of_measure_qty()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.tradingreferenceprice"] = ((*message_2).trading_reference_price().has_value() ? canonical::scaled((*(*message_2).trading_reference_price()).mantissa(), (*(*message_2).trading_reference_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().final()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().actual()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().rounded()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().intraday()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().reserved_bits()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().unused_settl_price_type_5()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().unused_settl_price_type_6()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().null_value()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.openinterestqty"] = ((*message_2).open_interest_qty().has_value() ? canonical::number((*(*message_2).open_interest_qty())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.clearedvolume"] = ((*message_2).cleared_volume().has_value() ? canonical::number((*(*message_2).cleared_volume())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.highlimitprice"] = ((*message_2).high_limit_price().has_value() ? canonical::scaled((*(*message_2).high_limit_price()).mantissa(), (*(*message_2).high_limit_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.lowlimitprice"] = ((*message_2).low_limit_price().has_value() ? canonical::scaled((*(*message_2).low_limit_price()).mantissa(), (*(*message_2).low_limit_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maxpricevariation"] = ((*message_2).max_price_variation().has_value() ? canonical::scaled((*(*message_2).max_price_variation()).mantissa(), (*(*message_2).max_price_variation()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decayquantity"] = ((*message_2).decay_quantity().has_value() ? canonical::number((*(*message_2).decay_quantity())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decaystartdate"] = ((*message_2).decay_start_date().has_value() ? canonical::number((*(*message_2).decay_start_date())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.originalcontractsize"] = ((*message_2).original_contract_size().has_value() ? canonical::number((*(*message_2).original_contract_size())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplier"] = ((*message_2).contract_multiplier().has_value() ? canonical::number((*(*message_2).contract_multiplier())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplierunit"] = ((*message_2).contract_multiplier_unit().has_value() ? canonical::number((*(*message_2).contract_multiplier_unit())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.flowscheduletype"] = ((*message_2).flow_schedule_type().has_value() ? canonical::number((*(*message_2).flow_schedule_type())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrementamount"] = ((*message_2).min_price_increment_amount().has_value() ? canonical::scaled((*(*message_2).min_price_increment_amount()).mantissa(), (*(*message_2).min_price_increment_amount()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.userdefinedinstrument"] = canonical::text(canonical::character((*message_2).user_defined_instrument()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdInstrumentDefinitionSpread*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.totnumreportsoptional"] = ((*message_2).tot_num_reports_optional().has_value() ? canonical::number((*(*message_2).tot_num_reports_optional())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityupdateaction"] = canonical::text(canonical::character((*message_2).security_update_action()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.lastupdatetime"] = canonical::number((*message_2).last_update_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mdsecuritytradingstatus"] = ((*message_2).md_security_trading_status().has_value() ? canonical::number((*(*message_2).md_security_trading_status())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.applid"] = canonical::number((*message_2).appl_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.marketsegmentid"] = canonical::number((*message_2).market_segment_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.underlyingproductoptional"] = ((*message_2).underlying_product_optional().has_value() ? canonical::number((*(*message_2).underlying_product_optional())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityexchange"] = canonical::text(std::string((*message_2).security_exchange()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitygroup"] = canonical::text(std::string((*message_2).security_group()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.asset"] = canonical::text(std::string((*message_2).asset()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.symbol"] = canonical::text(std::string((*message_2).symbol()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityid"] = canonical::number((*message_2).security_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitytype"] = canonical::text(std::string((*message_2).security_type()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.cficode"] = canonical::text(std::string((*message_2).cfi_code()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.year"] = ((*message_2).maturity_month_year().year().has_value() ? canonical::number((*(*message_2).maturity_month_year().year())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.month"] = ((*message_2).maturity_month_year().month().has_value() ? canonical::number((*(*message_2).maturity_month_year().month())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.day"] = ((*message_2).maturity_month_year().day().has_value() ? canonical::number((*(*message_2).maturity_month_year().day())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.week"] = ((*message_2).maturity_month_year().week().has_value() ? canonical::number((*(*message_2).maturity_month_year().week())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.currency"] = canonical::text(std::string((*message_2).currency()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitysubtype"] = canonical::text(std::string((*message_2).security_sub_type()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.userdefinedinstrument"] = canonical::text(canonical::character((*message_2).user_defined_instrument()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matchalgorithm"] = canonical::text(canonical::character((*message_2).match_algorithm()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mintradevol"] = canonical::number((*message_2).min_trade_vol());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maxtradevol"] = canonical::number((*message_2).max_trade_vol());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.minpriceincrement"] = canonical::scaled((*message_2).min_price_increment().mantissa(), (*message_2).min_price_increment().exponent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.displayfactor"] = canonical::scaled((*message_2).display_factor().mantissa(), (*message_2).display_factor().exponent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.pricedisplayformat"] = ((*message_2).price_display_format().has_value() ? canonical::number((*(*message_2).price_display_format())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.priceratio"] = ((*message_2).price_ratio().has_value() ? canonical::scaled((*(*message_2).price_ratio()).mantissa(), (*(*message_2).price_ratio()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tickrule"] = ((*message_2).tick_rule().has_value() ? canonical::number((*(*message_2).tick_rule())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.unitofmeasure"] = canonical::text(std::string((*message_2).unit_of_measure()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tradingreferenceprice"] = ((*message_2).trading_reference_price().has_value() ? canonical::scaled((*(*message_2).trading_reference_price()).mantissa(), (*(*message_2).trading_reference_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().final()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().actual()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().rounded()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().intraday()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().reserved_bits()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().unused_settl_price_type_5()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().unused_settl_price_type_6()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().null_value()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.openinterestqty"] = ((*message_2).open_interest_qty().has_value() ? canonical::number((*(*message_2).open_interest_qty())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.clearedvolume"] = ((*message_2).cleared_volume().has_value() ? canonical::number((*(*message_2).cleared_volume())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.highlimitprice"] = ((*message_2).high_limit_price().has_value() ? canonical::scaled((*(*message_2).high_limit_price()).mantissa(), (*(*message_2).high_limit_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.lowlimitprice"] = ((*message_2).low_limit_price().has_value() ? canonical::scaled((*(*message_2).low_limit_price()).mantissa(), (*(*message_2).low_limit_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maxpricevariation"] = ((*message_2).max_price_variation().has_value() ? canonical::scaled((*(*message_2).max_price_variation()).mantissa(), (*(*message_2).max_price_variation()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mainfraction"] = ((*message_2).main_fraction().has_value() ? canonical::number((*(*message_2).main_fraction())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.subfraction"] = ((*message_2).sub_fraction().has_value() ? canonical::number((*(*message_2).sub_fraction())) : canonical::absent());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SecurityStatus*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.securitystatus";
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitygroup"] = canonical::text(std::string((*message_2).security_group()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.asset"] = canonical::text(std::string((*message_2).asset()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securityidoptional"] = ((*message_2).security_id_optional().has_value() ? canonical::number((*(*message_2).security_id_optional())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.tradedate"] = ((*message_2).trade_date().has_value() ? canonical::number((*(*message_2).trade_date())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitytradingstatus"] = ((*message_2).security_trading_status().has_value() ? canonical::number((*(*message_2).security_trading_status())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.haltreason"] = canonical::number((*message_2).halt_reason());
                values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitytradingevent"] = canonical::number((*message_2).security_trading_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshBook*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshDailyStatistics*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshLimitsBanding*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshSessionStatistics*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshTrade*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshVolume*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::SnapshotFullRefresh*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefresh";
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lastmsgseqnumprocessed"] = canonical::number((*message_2).last_msg_seq_num_processed());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.totnumreports"] = canonical::number((*message_2).tot_num_reports());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.securityid"] = canonical::number((*message_2).security_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.rptseq"] = canonical::number((*message_2).rpt_seq());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lastupdatetime"] = canonical::number((*message_2).last_update_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.tradedate"] = ((*message_2).trade_date().has_value() ? canonical::number((*(*message_2).trade_date())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.mdsecuritytradingstatus"] = ((*message_2).md_security_trading_status().has_value() ? canonical::number((*(*message_2).md_security_trading_status())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.highlimitprice"] = ((*message_2).high_limit_price().has_value() ? canonical::scaled((*(*message_2).high_limit_price()).mantissa(), (*(*message_2).high_limit_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lowlimitprice"] = ((*message_2).low_limit_price().has_value() ? canonical::scaled((*(*message_2).low_limit_price()).mantissa(), (*(*message_2).low_limit_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.maxpricevariation"] = ((*message_2).max_price_variation().has_value() ? canonical::scaled((*(*message_2).max_price_variation()).mantissa(), (*(*message_2).max_price_variation()).exponent()) : canonical::absent());
            } else if (const auto* message_2 = dynamic_cast<const protocol::QuoteRequest*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.quoterequest";
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.quotereqid"] = canonical::text(std::string((*message_2).quote_req_id()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdInstrumentDefinitionOption*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.totnumreportsoptional"] = ((*message_2).tot_num_reports_optional().has_value() ? canonical::number((*(*message_2).tot_num_reports_optional())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityupdateaction"] = canonical::text(canonical::character((*message_2).security_update_action()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.lastupdatetime"] = canonical::number((*message_2).last_update_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mdsecuritytradingstatus"] = ((*message_2).md_security_trading_status().has_value() ? canonical::number((*(*message_2).md_security_trading_status())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.applid"] = canonical::number((*message_2).appl_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.marketsegmentid"] = canonical::number((*message_2).market_segment_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.underlyingproduct"] = canonical::number((*message_2).underlying_product());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityexchange"] = canonical::text(std::string((*message_2).security_exchange()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securitygroup"] = canonical::text(std::string((*message_2).security_group()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.asset"] = canonical::text(std::string((*message_2).asset()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.symbol"] = canonical::text(std::string((*message_2).symbol()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityid"] = canonical::number((*message_2).security_id());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securitytype"] = canonical::text(std::string((*message_2).security_type()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.cficode"] = canonical::text(std::string((*message_2).cfi_code()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.putorcall"] = canonical::number((*message_2).put_or_call());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.year"] = ((*message_2).maturity_month_year().year().has_value() ? canonical::number((*(*message_2).maturity_month_year().year())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.month"] = ((*message_2).maturity_month_year().month().has_value() ? canonical::number((*(*message_2).maturity_month_year().month())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.day"] = ((*message_2).maturity_month_year().day().has_value() ? canonical::number((*(*message_2).maturity_month_year().day())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.week"] = ((*message_2).maturity_month_year().week().has_value() ? canonical::number((*(*message_2).maturity_month_year().week())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.currency"] = canonical::text(std::string((*message_2).currency()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikeprice"] = ((*message_2).strike_price().has_value() ? canonical::scaled((*(*message_2).strike_price()).mantissa(), (*(*message_2).strike_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikecurrency"] = canonical::text(std::string((*message_2).strike_currency()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlcurrency"] = canonical::text(std::string((*message_2).settl_currency()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mincabprice"] = ((*message_2).min_cab_price().has_value() ? canonical::scaled((*(*message_2).min_cab_price()).mantissa(), (*(*message_2).min_cab_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matchalgorithm"] = canonical::text(canonical::character((*message_2).match_algorithm()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mintradevol"] = canonical::number((*message_2).min_trade_vol());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maxtradevol"] = canonical::number((*message_2).max_trade_vol());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementoptional"] = ((*message_2).min_price_increment_optional().has_value() ? canonical::scaled((*(*message_2).min_price_increment_optional()).mantissa(), (*(*message_2).min_price_increment_optional()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementamount"] = ((*message_2).min_price_increment_amount().has_value() ? canonical::scaled((*(*message_2).min_price_increment_amount()).mantissa(), (*(*message_2).min_price_increment_amount()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.displayfactor"] = canonical::scaled((*message_2).display_factor().mantissa(), (*message_2).display_factor().exponent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tickrule"] = ((*message_2).tick_rule().has_value() ? canonical::number((*(*message_2).tick_rule())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mainfraction"] = ((*message_2).main_fraction().has_value() ? canonical::number((*(*message_2).main_fraction())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.subfraction"] = ((*message_2).sub_fraction().has_value() ? canonical::number((*(*message_2).sub_fraction())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.pricedisplayformat"] = ((*message_2).price_display_format().has_value() ? canonical::number((*(*message_2).price_display_format())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasure"] = canonical::text(std::string((*message_2).unit_of_measure()), '\0', false);
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasureqty"] = ((*message_2).unit_of_measure_qty().has_value() ? canonical::scaled((*(*message_2).unit_of_measure_qty()).mantissa(), (*(*message_2).unit_of_measure_qty()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tradingreferenceprice"] = ((*message_2).trading_reference_price().has_value() ? canonical::scaled((*(*message_2).trading_reference_price()).mantissa(), (*(*message_2).trading_reference_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().final()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().actual()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().rounded()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().intraday()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().reserved_bits()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().unused_settl_price_type_5()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().unused_settl_price_type_6()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>((*message_2).settl_price_type().null_value()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.clearedvolume"] = ((*message_2).cleared_volume().has_value() ? canonical::number((*(*message_2).cleared_volume())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.openinterestqty"] = ((*message_2).open_interest_qty().has_value() ? canonical::number((*(*message_2).open_interest_qty())) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.lowlimitprice"] = ((*message_2).low_limit_price().has_value() ? canonical::scaled((*(*message_2).low_limit_price()).mantissa(), (*(*message_2).low_limit_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.highlimitprice"] = ((*message_2).high_limit_price().has_value() ? canonical::scaled((*(*message_2).high_limit_price()).mantissa(), (*(*message_2).high_limit_price()).exponent()) : canonical::absent());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.userdefinedinstrument"] = canonical::text(canonical::character((*message_2).user_defined_instrument()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshTradeSummary*>(message->mktdata_payload())) {
                values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary";
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.transacttime"] = canonical::number((*message_2).transact_time());
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_trade_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_volume_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_quote_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_stats_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().last_implied_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().recovery_msg()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().reserved()));
                values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>((*message_2).match_event_indicator().end_of_event()));
            }
        } else if (const auto* message = dynamic_cast<const protocol::MdpsessionmgmtMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
            if (const auto* message_2 = dynamic_cast<const protocol::Negotiate*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.hmacsignature"] = canonical::text(std::string((*message_2).hmac_signature()), '\0', false);
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.accesskeyid"] = canonical::text(std::string((*message_2).access_key_id()), '\0', false);
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.uuid"] = canonical::number((*message_2).uuid());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.requesttimestamp"] = canonical::number((*message_2).request_timestamp());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.session"] = canonical::text(std::string((*message_2).session()), '\0', false);
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.firm"] = canonical::text(std::string((*message_2).firm()), '\0', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::NegotiationReject*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.reason"] = canonical::text(std::string((*message_2).reason()), '\0', false);
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.uuid"] = canonical::number((*message_2).uuid());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.requesttimestamp"] = canonical::number((*message_2).request_timestamp());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.errorcodes"] = canonical::number((*message_2).error_codes());
            } else if (const auto* message_2 = dynamic_cast<const protocol::NegotiationResponse*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.uuid"] = canonical::number((*message_2).uuid());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.requesttimestamp"] = canonical::number((*message_2).request_timestamp());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.secretkeysecureidexpiration"] = ((*message_2).secret_key_secure_id_expiration().has_value() ? canonical::number((*(*message_2).secret_key_secure_id_expiration())) : canonical::absent());
            } else if (const auto* message_2 = dynamic_cast<const protocol::Terminate*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.reason"] = canonical::text(std::string((*message_2).reason()), '\0', false);
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.uuid"] = canonical::number((*message_2).uuid());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.requesttimestamp"] = canonical::number((*message_2).request_timestamp());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.errorcodes"] = canonical::number((*message_2).error_codes());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MarketDataRequest*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest.mdreqid"] = canonical::number((*message_2).md_req_id());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest.subscriptionreqtype"] = canonical::number((*message_2).subscription_req_type());
            } else if (const auto* message_2 = dynamic_cast<const protocol::RequestAck*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.mdreqid"] = canonical::number((*message_2).md_req_id());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.subscriptionreqtype"] = canonical::number((*message_2).subscription_req_type());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.mdreqidstatus"] = canonical::number((*message_2).md_req_id_status());
            } else if (const auto* message_2 = dynamic_cast<const protocol::RequestReject*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.mdreqidoptional"] = ((*message_2).md_req_id_optional().has_value() ? canonical::number((*(*message_2).md_req_id_optional())) : canonical::absent());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.mdreqrejreason"] = canonical::number((*message_2).md_req_rej_reason());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.text"] = canonical::text(std::string((*message_2).text()), '\0', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::SecurityListRequest*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest.mdreqid"] = canonical::number((*message_2).md_req_id());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest.subscriptionreqtype"] = canonical::number((*message_2).subscription_req_type());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SecurityStatusRequest*>(message->mdpsessionmgmt_payload())) {
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest";
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest.mdreqid"] = canonical::number((*message_2).md_req_id());
                values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest.subscriptionreqtype"] = canonical::number((*message_2).subscription_req_type());
            }
        }
    }

    return values;
}

// Read each datagram of a sample with Classes and hold it to the model's values
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
    std::printf("== Cme.Globex.Mdp3.Sbe.v1.5 (classes values)\n");
    int failures = 0;
    failures += check("MdIncrementalRefreshBook", "Cme/Globex.Mdp3.Sbe.v1.5/MdIncrementalRefreshBook.pcap", "cme/globex/mdp3/sbe/v1.5/MdIncrementalRefreshBook.values");
    failures += check("MdIncrementalRefreshSessionStatistics", "Cme/Globex.Mdp3.Sbe.v1.5/MdIncrementalRefreshSessionStatistics.pcap", "cme/globex/mdp3/sbe/v1.5/MdIncrementalRefreshSessionStatistics.values");
    failures += check("MdIncrementalRefreshTradeSummary", "Cme/Globex.Mdp3.Sbe.v1.5/MdIncrementalRefreshTradeSummary.pcap", "cme/globex/mdp3/sbe/v1.5/MdIncrementalRefreshTradeSummary.values");
    failures += check("MdIncrementalRefreshVolume", "Cme/Globex.Mdp3.Sbe.v1.5/MdIncrementalRefreshVolume.pcap", "cme/globex/mdp3/sbe/v1.5/MdIncrementalRefreshVolume.values");
    failures += check("MdInstrumentDefinitionSpread", "Cme/Globex.Mdp3.Sbe.v1.5/MdInstrumentDefinitionSpread.pcap", "cme/globex/mdp3/sbe/v1.5/MdInstrumentDefinitionSpread.values");
    return failures == 0 ? 0 : 1;
}
