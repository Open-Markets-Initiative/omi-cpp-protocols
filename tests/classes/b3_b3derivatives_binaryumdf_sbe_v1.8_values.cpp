// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/definitions.hpp"

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }

    values["packet.packetheader.channelid"] = canonical::number(packet.packet_header().channel_id());
    values["packet.packetheader.packetreserved"] = canonical::number(packet.packet_header().packet_reserved());
    values["packet.packetheader.sequenceversion"] = canonical::number(packet.packet_header().sequence_version());
    values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
    values["packet.packetheader.sendingtime"] = canonical::number(packet.packet_header().sending_time());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(each.framing_header().message_length());
        values[entry + ".framingheader.encodingtype"] = canonical::number(each.framing_header().encoding_type());
        values[entry + ".messageheader.blocklength"] = canonical::number(each.message_header().block_length());
        values[entry + ".messageheader.templateid"] = canonical::number(each.message_header().template_id());
        values[entry + ".messageheader.schemaid"] = canonical::number(each.message_header().schema_id());
        values[entry + ".messageheader.version"] = canonical::number(each.message_header().version());

        if (const auto* message = dynamic_cast<const protocol::SequenceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.sequencemessage";
            values[entry + ".payload.sequencemessage.nextseqno"] = canonical::number((*message).next_seq_no());
        } else if (const auto* message = dynamic_cast<const protocol::EmptyBookMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.emptybookmessage";
            values[entry + ".payload.emptybookmessage.securityid"] = canonical::number((*message).security_id());
        } else if (const auto* message = dynamic_cast<const protocol::ChannelReset11Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.channelreset11message";
        } else if (const auto* message = dynamic_cast<const protocol::SecurityStatus3Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.securitystatus3message";
            values[entry + ".payload.securitystatus3message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.securitystatus3message.tradingsessionid"] = canonical::number((*message).trading_session_id());
            values[entry + ".payload.securitystatus3message.securitytradingstatus"] = canonical::number((*message).security_trading_status());
            values[entry + ".payload.securitystatus3message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityGroupPhase10Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.securitygroupphase10message";
            values[entry + ".payload.securitygroupphase10message.securitygroup"] = canonical::text(std::string((*message).security_group()), '\0', false);
            values[entry + ".payload.securitygroupphase10message.tradingsessionid"] = canonical::number((*message).trading_session_id());
            values[entry + ".payload.securitygroupphase10message.tradingsessionsubid"] = canonical::number((*message).trading_session_sub_id());
            values[entry + ".payload.securitygroupphase10message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::DeprecatedSecurityDefinitionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.deprecatedsecuritydefinitionmessage";
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityexchange"] = canonical::text(std::string((*message).security_exchange()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityidsource"] = canonical::text(canonical::character((*message).security_id_source()));
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitygroup"] = canonical::text(std::string((*message).security_group()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.symbol"] = canonical::text(std::string((*message).symbol()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityupdateaction"] = canonical::text(canonical::character((*message).security_update_action()));
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitytype"] = canonical::number((*message).security_type());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitysubtype"] = canonical::number((*message).security_sub_type());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.totnorelatedsym"] = canonical::number((*message).tot_no_related_sym());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.issuedate"] = canonical::number((*message).issue_date());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.asset"] = canonical::text(std::string((*message).asset()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.cficode"] = canonical::text(std::string((*message).cfi_code()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.year"] = canonical::number((*message).maturity_month_year().year());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.month"] = canonical::number((*message).maturity_month_year().month());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.day"] = canonical::number((*message).maturity_month_year().day());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.week"] = canonical::number((*message).maturity_month_year().week());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.year"] = canonical::number((*message).contract_settl_month().year());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.month"] = canonical::number((*message).contract_settl_month().month());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.day"] = canonical::number((*message).contract_settl_month().day());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.week"] = canonical::number((*message).contract_settl_month().week());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.currency"] = canonical::text(std::string((*message).currency()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.product"] = canonical::number((*message).product());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityDefinitionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.securitydefinitionmessage";
            values[entry + ".payload.securitydefinitionmessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.securitydefinitionmessage.securityexchange"] = canonical::text(std::string((*message).security_exchange()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.securityidsource"] = canonical::text(canonical::character((*message).security_id_source()));
            values[entry + ".payload.securitydefinitionmessage.securitygroup"] = canonical::text(std::string((*message).security_group()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.symbol"] = canonical::text(std::string((*message).symbol()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.securityupdateaction"] = canonical::text(canonical::character((*message).security_update_action()));
            values[entry + ".payload.securitydefinitionmessage.securitytype"] = canonical::number((*message).security_type());
            values[entry + ".payload.securitydefinitionmessage.securitysubtype"] = canonical::number((*message).security_sub_type());
            values[entry + ".payload.securitydefinitionmessage.totnorelatedsym"] = canonical::number((*message).tot_no_related_sym());
            values[entry + ".payload.securitydefinitionmessage.issuedate"] = canonical::number((*message).issue_date());
            values[entry + ".payload.securitydefinitionmessage.asset"] = canonical::text(std::string((*message).asset()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.cficode"] = canonical::text(std::string((*message).cfi_code()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.year"] = canonical::number((*message).maturity_month_year().year());
            values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.month"] = canonical::number((*message).maturity_month_year().month());
            values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.day"] = canonical::number((*message).maturity_month_year().day());
            values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.week"] = canonical::number((*message).maturity_month_year().week());
            values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.year"] = canonical::number((*message).contract_settl_month().year());
            values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.month"] = canonical::number((*message).contract_settl_month().month());
            values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.day"] = canonical::number((*message).contract_settl_month().day());
            values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.week"] = canonical::number((*message).contract_settl_month().week());
            values[entry + ".payload.securitydefinitionmessage.currency"] = canonical::text(std::string((*message).currency()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.product"] = canonical::number((*message).product());
        } else if (const auto* message = dynamic_cast<const protocol::News5Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.news5message";
            values[entry + ".payload.news5message.newssource"] = canonical::number((*message).news_source());
            values[entry + ".payload.news5message.partcount"] = canonical::number((*message).part_count());
            values[entry + ".payload.news5message.partnumber"] = canonical::number((*message).part_number());
            values[entry + ".payload.news5message.totaltextlength"] = canonical::number((*message).total_text_length());
        } else if (const auto* message = dynamic_cast<const protocol::OpeningPrice15Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.openingprice15message";
            values[entry + ".payload.openingprice15message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.openingprice15message.mdupdateaction"] = canonical::number((*message).md_update_action());
            values[entry + ".payload.openingprice15message.openclosesettlflag"] = canonical::number((*message).open_close_settl_flag());
            values[entry + ".payload.openingprice15message.mdfutureprice"] = canonical::scaled((*message).md_future_price().mantissa(), (*message).md_future_price().exponent());
            values[entry + ".payload.openingprice15message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::TheoreticalOpeningPrice16Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.theoreticalopeningprice16message";
            values[entry + ".payload.theoreticalopeningprice16message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.theoreticalopeningprice16message.mdupdateaction"] = canonical::number((*message).md_update_action());
            values[entry + ".payload.theoreticalopeningprice16message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::ClosingPrice17Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.closingprice17message";
            values[entry + ".payload.closingprice17message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.closingprice17message.openclosesettlflag"] = canonical::number((*message).open_close_settl_flag());
            values[entry + ".payload.closingprice17message.mdcorporateprice"] = canonical::scaled((*message).md_corporate_price().mantissa(), (*message).md_corporate_price().exponent());
            values[entry + ".payload.closingprice17message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionImbalance19Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.auctionimbalance19message";
            values[entry + ".payload.auctionimbalance19message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.auctionimbalance19message.mdupdateaction"] = canonical::number((*message).md_update_action());
        } else if (const auto* message = dynamic_cast<const protocol::PriceBand20Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.priceband20message";
            values[entry + ".payload.priceband20message.securityid"] = canonical::number((*message).security_id());
        } else if (const auto* message = dynamic_cast<const protocol::QuantityBand21Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.quantityband21message";
            values[entry + ".payload.quantityband21message.securityid"] = canonical::number((*message).security_id());
        } else if (const auto* message = dynamic_cast<const protocol::PriceBand22Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.priceband22message";
            values[entry + ".payload.priceband22message.securityid"] = canonical::number((*message).security_id());
        } else if (const auto* message = dynamic_cast<const protocol::HighPrice24Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.highprice24message";
            values[entry + ".payload.highprice24message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.highprice24message.mdupdateaction"] = canonical::number((*message).md_update_action());
            values[entry + ".payload.highprice24message.tradedate"] = canonical::number((*message).trade_date());
            values[entry + ".payload.highprice24message.mdfutureprice"] = canonical::scaled((*message).md_future_price().mantissa(), (*message).md_future_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::LowPrice25Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.lowprice25message";
            values[entry + ".payload.lowprice25message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.lowprice25message.mdupdateaction"] = canonical::number((*message).md_update_action());
            values[entry + ".payload.lowprice25message.tradedate"] = canonical::number((*message).trade_date());
            values[entry + ".payload.lowprice25message.mdfutureprice"] = canonical::scaled((*message).md_future_price().mantissa(), (*message).md_future_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::LastTradePrice27Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.lasttradeprice27message";
            values[entry + ".payload.lasttradeprice27message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.lasttradeprice27message.tradingsessionid"] = canonical::number((*message).trading_session_id());
            values[entry + ".payload.lasttradeprice27message.mdfutureprice"] = canonical::scaled((*message).md_future_price().mantissa(), (*message).md_future_price().exponent());
            values[entry + ".payload.lasttradeprice27message.mdentrysizequantity"] = canonical::number((*message).md_entry_size_quantity());
            values[entry + ".payload.lasttradeprice27message.tradeid"] = canonical::number((*message).trade_id());
            values[entry + ".payload.lasttradeprice27message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::SettlementPrice28Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.settlementprice28message";
            values[entry + ".payload.settlementprice28message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.settlementprice28message.tradedate"] = canonical::number((*message).trade_date());
            values[entry + ".payload.settlementprice28message.mdfutureprice"] = canonical::scaled((*message).md_future_price().mantissa(), (*message).md_future_price().exponent());
            values[entry + ".payload.settlementprice28message.openclosesettlflag"] = canonical::number((*message).open_close_settl_flag());
            values[entry + ".payload.settlementprice28message.pricetype"] = canonical::number((*message).price_type());
            values[entry + ".payload.settlementprice28message.settlpricetype"] = canonical::number((*message).settl_price_type());
        } else if (const auto* message = dynamic_cast<const protocol::OpenInterest29Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.openinterest29message";
            values[entry + ".payload.openinterest29message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.openinterest29message.tradedate"] = canonical::number((*message).trade_date());
            values[entry + ".payload.openinterest29message.mdentrysizequantity"] = canonical::number((*message).md_entry_size_quantity());
        } else if (const auto* message = dynamic_cast<const protocol::SnapshotFullRefreshHeader30Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshheader30message";
            values[entry + ".payload.snapshotfullrefreshheader30message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.snapshotfullrefreshheader30message.lastmsgseqnumprocessed"] = canonical::number((*message).last_msg_seq_num_processed());
            values[entry + ".payload.snapshotfullrefreshheader30message.totnumreports"] = canonical::number((*message).tot_num_reports());
            values[entry + ".payload.snapshotfullrefreshheader30message.totnumbids"] = canonical::number((*message).tot_num_bids());
            values[entry + ".payload.snapshotfullrefreshheader30message.totnumoffers"] = canonical::number((*message).tot_num_offers());
            values[entry + ".payload.snapshotfullrefreshheader30message.totnumstats"] = canonical::number((*message).tot_num_stats());
        } else if (const auto* message = dynamic_cast<const protocol::OrderMbO50Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.ordermbo50message";
            values[entry + ".payload.ordermbo50message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.ordermbo50message.mdupdateaction"] = canonical::number((*message).md_update_action());
            values[entry + ".payload.ordermbo50message.mdentrytype"] = canonical::text(canonical::character((*message).md_entry_type()));
            values[entry + ".payload.ordermbo50message.mdentrysizequantity"] = canonical::number((*message).md_entry_size_quantity());
            values[entry + ".payload.ordermbo50message.mdentrypositionno"] = canonical::number((*message).md_entry_position_no());
            values[entry + ".payload.ordermbo50message.secondaryorderid"] = canonical::number((*message).secondary_order_id());
        } else if (const auto* message = dynamic_cast<const protocol::DeleteOrderMbO51Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.deleteordermbo51message";
            values[entry + ".payload.deleteordermbo51message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.deleteordermbo51message.mdentrytype"] = canonical::text(canonical::character((*message).md_entry_type()));
            values[entry + ".payload.deleteordermbo51message.mdentrypositionno"] = canonical::number((*message).md_entry_position_no());
            values[entry + ".payload.deleteordermbo51message.secondaryorderid"] = canonical::number((*message).secondary_order_id());
        } else if (const auto* message = dynamic_cast<const protocol::MassDeleteOrdersMbO52Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.massdeleteordersmbo52message";
            values[entry + ".payload.massdeleteordersmbo52message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.massdeleteordersmbo52message.mdupdateaction"] = canonical::number((*message).md_update_action());
            values[entry + ".payload.massdeleteordersmbo52message.mdentrytype"] = canonical::text(canonical::character((*message).md_entry_type()));
            values[entry + ".payload.massdeleteordersmbo52message.mdentrypositionno"] = canonical::number((*message).md_entry_position_no());
        } else if (const auto* message = dynamic_cast<const protocol::Trade53Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.trade53message";
            values[entry + ".payload.trade53message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.trade53message.tradingsessionid"] = canonical::number((*message).trading_session_id());
            values[entry + ".payload.trade53message.mdfutureprice"] = canonical::scaled((*message).md_future_price().mantissa(), (*message).md_future_price().exponent());
            values[entry + ".payload.trade53message.mdentrysizequantity"] = canonical::number((*message).md_entry_size_quantity());
            values[entry + ".payload.trade53message.tradeid"] = canonical::number((*message).trade_id());
            values[entry + ".payload.trade53message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::ForwardTrade54Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.forwardtrade54message";
            values[entry + ".payload.forwardtrade54message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.forwardtrade54message.tradingsessionid"] = canonical::number((*message).trading_session_id());
            values[entry + ".payload.forwardtrade54message.mdfutureprice"] = canonical::scaled((*message).md_future_price().mantissa(), (*message).md_future_price().exponent());
            values[entry + ".payload.forwardtrade54message.mdentrysizequantity"] = canonical::number((*message).md_entry_size_quantity());
            values[entry + ".payload.forwardtrade54message.tradeid"] = canonical::number((*message).trade_id());
            values[entry + ".payload.forwardtrade54message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummary55Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.executionsummary55message";
            values[entry + ".payload.executionsummary55message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.executionsummary55message.aggressorside"] = canonical::number((*message).aggressor_side());
            values[entry + ".payload.executionsummary55message.lastpx"] = canonical::scaled((*message).last_px().mantissa(), (*message).last_px().exponent());
            values[entry + ".payload.executionsummary55message.fillqty"] = canonical::number((*message).fill_qty());
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionStatistics56Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.executionstatistics56message";
            values[entry + ".payload.executionstatistics56message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.executionstatistics56message.tradingsessionid"] = canonical::number((*message).trading_session_id());
            values[entry + ".payload.executionstatistics56message.tradedate"] = canonical::number((*message).trade_date());
            values[entry + ".payload.executionstatistics56message.tradevolume"] = canonical::number((*message).trade_volume());
            values[entry + ".payload.executionstatistics56message.numberoftrades"] = canonical::number((*message).number_of_trades());
        } else if (const auto* message = dynamic_cast<const protocol::TradeBust57Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.tradebust57message";
            values[entry + ".payload.tradebust57message.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.tradebust57message.tradingsessionid"] = canonical::number((*message).trading_session_id());
            values[entry + ".payload.tradebust57message.mdfutureprice"] = canonical::scaled((*message).md_future_price().mantissa(), (*message).md_future_price().exponent());
            values[entry + ".payload.tradebust57message.mdentrysizequantity"] = canonical::number((*message).md_entry_size_quantity());
            values[entry + ".payload.tradebust57message.tradeid"] = canonical::number((*message).trade_id());
            values[entry + ".payload.tradebust57message.tradedate"] = canonical::number((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::SnapshotFullRefreshOrdersMbO71Message*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshordersmbo71message";
            values[entry + ".payload.snapshotfullrefreshordersmbo71message.securityid"] = canonical::number((*message).security_id());
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
    std::printf("== B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 (classes values)\n");
    int failures = 0;
    failures += check("SecurityDefinitionMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SecurityDefinitionMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SecurityDefinitionMessage.values");
    failures += check("SequenceMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SequenceMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SequenceMessage.values");
    return failures == 0 ? 0 : 1;
}