// Nyse.NyseEquities.IntegratedFeed.Pillar.v2.5.g canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/nyse/nyseequities/integratedfeed/pillar/v2.5.g/definitions.hpp"

namespace protocol = ::nyse::nyseequities::integratedfeed::pillar::v2_5_g;

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

    values["packet.packetheader.pktsize"] = canonical::number(packet.packet_header().pkt_size());
    values["packet.packetheader.deliveryflag"] = canonical::number(packet.packet_header().delivery_flag());
    values["packet.packetheader.numbermsgs"] = canonical::number(packet.packet_header().number_msgs());
    values["packet.packetheader.seqnum"] = canonical::number(packet.packet_header().seq_num());
    values["packet.packetheader.sendtime.seconds"] = canonical::number(packet.packet_header().send_time().seconds());
    values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(packet.packet_header().send_time().nanoseconds());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(each.message_header().message_size());
        values[entry + ".messageheader.messagetype"] = canonical::number(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SequenceNumberResetMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.sequencenumberresetmessage";
            values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number((*message).product_id());
            values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number((*message).channel_id());
        } else if (const auto* message = dynamic_cast<const protocol::SourceTimeReferenceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.sourcetimereferencemessage";
            values[entry + ".payload.sourcetimereferencemessage.id"] = canonical::number((*message).id());
            values[entry + ".payload.sourcetimereferencemessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.sourcetimereferencemessage.sourcetime"] = canonical::number((*message).source_time());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolIndexMappingMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingmessage";
            values[entry + ".payload.symbolindexmappingmessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.symbolindexmappingmessage.symbol"] = canonical::text(std::string((*message).symbol()), '\0', false);
            values[entry + ".payload.symbolindexmappingmessage.marketid"] = canonical::number((*message).market_id());
            values[entry + ".payload.symbolindexmappingmessage.systemid"] = canonical::number((*message).system_id());
            values[entry + ".payload.symbolindexmappingmessage.exchangecode"] = canonical::text(canonical::character((*message).exchange_code()), '\0', false);
            values[entry + ".payload.symbolindexmappingmessage.pricescalecode"] = canonical::number((*message).price_scale_code());
            values[entry + ".payload.symbolindexmappingmessage.securitytype"] = canonical::text(canonical::character((*message).security_type()), '\0', false);
            values[entry + ".payload.symbolindexmappingmessage.lotsize"] = canonical::number((*message).lot_size());
            values[entry + ".payload.symbolindexmappingmessage.prevcloseprice"] = canonical::number((*message).prev_close_price());
            values[entry + ".payload.symbolindexmappingmessage.prevclosevolume"] = canonical::number((*message).prev_close_volume());
            values[entry + ".payload.symbolindexmappingmessage.priceresolution"] = canonical::number((*message).price_resolution());
            values[entry + ".payload.symbolindexmappingmessage.roundlot"] = canonical::text(canonical::character((*message).round_lot()), '\0', false);
            values[entry + ".payload.symbolindexmappingmessage.mpv"] = canonical::number((*message).mpv());
            values[entry + ".payload.symbolindexmappingmessage.unitoftrade"] = canonical::number((*message).unit_of_trade());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolClearMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.symbolclearmessage";
            values[entry + ".payload.symbolclearmessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.symbolclearmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.symbolclearmessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.symbolclearmessage.nextsourceseqnum"] = canonical::number((*message).next_source_seq_num());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityStatusMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.securitystatusmessage";
            values[entry + ".payload.securitystatusmessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.securitystatusmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.securitystatusmessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.securitystatusmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.securitystatusmessage.securitystatus"] = canonical::text(canonical::character((*message).security_status()), '\0', false);
            values[entry + ".payload.securitystatusmessage.haltcondition"] = canonical::text(canonical::character((*message).halt_condition()), '\0', false);
            values[entry + ".payload.securitystatusmessage.price1"] = canonical::number((*message).price_1());
            values[entry + ".payload.securitystatusmessage.price2"] = canonical::number((*message).price_2());
            values[entry + ".payload.securitystatusmessage.ssrtriggeringexchangeid"] = canonical::text(canonical::character((*message).ssr_triggering_exchange_id()), '\0', false);
            values[entry + ".payload.securitystatusmessage.ssrtriggeringvolume"] = canonical::number((*message).ssr_triggering_volume());
            values[entry + ".payload.securitystatusmessage.time"] = ((*message).time().has_value() ? canonical::number((*(*message).time())) : canonical::absent());
            values[entry + ".payload.securitystatusmessage.ssrstate"] = canonical::text(canonical::character((*message).ssr_state()), '\0', false);
            values[entry + ".payload.securitystatusmessage.marketstate"] = canonical::text(canonical::character((*message).market_state()), '\0', false);
            values[entry + ".payload.securitystatusmessage.sessionstate"] = canonical::text(canonical::character((*message).session_state()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordermessage";
            values[entry + ".payload.addordermessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.addordermessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.addordermessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.addordermessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addordermessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.addordermessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character((*message).side()), '\0', false);
            values[entry + ".payload.addordermessage.firmid"] = canonical::text(std::string((*message).firm_id()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.modifyordermessage";
            values[entry + ".payload.modifyordermessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.modifyordermessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.modifyordermessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.modifyordermessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.modifyordermessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.modifyordermessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.modifyordermessage.positionchange"] = canonical::number((*message).position_change());
            values[entry + ".payload.modifyordermessage.side"] = canonical::text(canonical::character((*message).side()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::DeleteOrderMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
            values[entry + ".payload.deleteordermessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.deleteordermessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.deleteordermessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.deleteordermessage.orderid"] = canonical::number((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutionmessage";
            values[entry + ".payload.orderexecutionmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.orderexecutionmessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.orderexecutionmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.orderexecutionmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutionmessage.tradeid"] = canonical::number((*message).trade_id());
            values[entry + ".payload.orderexecutionmessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.orderexecutionmessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.orderexecutionmessage.printableflag"] = canonical::number((*message).printable_flag());
            values[entry + ".payload.orderexecutionmessage.tradecond1"] = canonical::text(canonical::character((*message).trade_cond_1()), '\0', false);
            values[entry + ".payload.orderexecutionmessage.tradecond2"] = canonical::text(canonical::character((*message).trade_cond_2()), '\0', false);
            values[entry + ".payload.orderexecutionmessage.tradecond3"] = canonical::text(canonical::character((*message).trade_cond_3()), '\0', false);
            values[entry + ".payload.orderexecutionmessage.tradecond4"] = canonical::text(canonical::character((*message).trade_cond_4()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::ReplaceOrderMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.replaceordermessage";
            values[entry + ".payload.replaceordermessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.replaceordermessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.replaceordermessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.replaceordermessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.replaceordermessage.neworderid"] = canonical::number((*message).new_order_id());
            values[entry + ".payload.replaceordermessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.replaceordermessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.replaceordermessage.side"] = canonical::text(canonical::character((*message).side()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::ImbalanceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.imbalancemessage";
            values[entry + ".payload.imbalancemessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.imbalancemessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.imbalancemessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.imbalancemessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.imbalancemessage.referenceprice"] = canonical::number((*message).reference_price());
            values[entry + ".payload.imbalancemessage.pairedqty"] = canonical::number((*message).paired_qty());
            values[entry + ".payload.imbalancemessage.totalimbalanceqty"] = canonical::number((*message).total_imbalance_qty());
            values[entry + ".payload.imbalancemessage.marketimbalanceqty"] = canonical::number((*message).market_imbalance_qty());
            values[entry + ".payload.imbalancemessage.auctiontime"] = canonical::number((*message).auction_time());
            values[entry + ".payload.imbalancemessage.auctiontype"] = canonical::text(canonical::character((*message).auction_type()), '\0', false);
            values[entry + ".payload.imbalancemessage.imbalanceside"] = canonical::text(canonical::character((*message).imbalance_side()), '\0', false);
            values[entry + ".payload.imbalancemessage.continuousbookclearingprice"] = canonical::number((*message).continuous_book_clearing_price());
            values[entry + ".payload.imbalancemessage.auctioninterestclearingprice"] = canonical::number((*message).auction_interest_clearing_price());
            values[entry + ".payload.imbalancemessage.ssrfilingprice"] = canonical::number((*message).ssr_filing_price());
            values[entry + ".payload.imbalancemessage.indicativematchprice"] = canonical::number((*message).indicative_match_price());
            values[entry + ".payload.imbalancemessage.uppercollar"] = canonical::number((*message).upper_collar());
            values[entry + ".payload.imbalancemessage.lowercollar"] = canonical::number((*message).lower_collar());
            values[entry + ".payload.imbalancemessage.auctionstatus"] = canonical::number((*message).auction_status());
            values[entry + ".payload.imbalancemessage.freezestatus"] = canonical::number((*message).freeze_status());
            values[entry + ".payload.imbalancemessage.numextensions"] = canonical::number((*message).num_extensions());
            values[entry + ".payload.imbalancemessage.unpairedqty"] = canonical::number((*message).unpaired_qty());
            values[entry + ".payload.imbalancemessage.unpairedside"] = canonical::text(canonical::character((*message).unpaired_side()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderRefreshMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderrefreshmessage";
            values[entry + ".payload.addorderrefreshmessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.addorderrefreshmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.addorderrefreshmessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.addorderrefreshmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.addorderrefreshmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addorderrefreshmessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.addorderrefreshmessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.addorderrefreshmessage.side"] = canonical::text(canonical::character((*message).side()), '\0', false);
            values[entry + ".payload.addorderrefreshmessage.firmid"] = canonical::text(std::string((*message).firm_id()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::NonDisplayedTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.nondisplayedtrademessage";
            values[entry + ".payload.nondisplayedtrademessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.nondisplayedtrademessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.nondisplayedtrademessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.nondisplayedtrademessage.tradeid"] = canonical::number((*message).trade_id());
            values[entry + ".payload.nondisplayedtrademessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.nondisplayedtrademessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.nondisplayedtrademessage.printableflag"] = canonical::number((*message).printable_flag());
            values[entry + ".payload.nondisplayedtrademessage.tradecond1"] = canonical::text(canonical::character((*message).trade_cond_1()), '\0', false);
            values[entry + ".payload.nondisplayedtrademessage.tradecond2"] = canonical::text(canonical::character((*message).trade_cond_2()), '\0', false);
            values[entry + ".payload.nondisplayedtrademessage.tradecond3"] = canonical::text(canonical::character((*message).trade_cond_3()), '\0', false);
            values[entry + ".payload.nondisplayedtrademessage.tradecond4"] = canonical::text(canonical::character((*message).trade_cond_4()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::CrossTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.crosstrademessage";
            values[entry + ".payload.crosstrademessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.crosstrademessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.crosstrademessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.crosstrademessage.crossid"] = canonical::number((*message).cross_id());
            values[entry + ".payload.crosstrademessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.crosstrademessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.crosstrademessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::TradeCancelMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradecancelmessage";
            values[entry + ".payload.tradecancelmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.tradecancelmessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.tradecancelmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.tradecancelmessage.tradeid"] = canonical::number((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::CrossCorrectionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.crosscorrectionmessage";
            values[entry + ".payload.crosscorrectionmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.crosscorrectionmessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.crosscorrectionmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.crosscorrectionmessage.crossid"] = canonical::number((*message).cross_id());
            values[entry + ".payload.crosscorrectionmessage.volume"] = canonical::number((*message).volume());
        } else if (const auto* message = dynamic_cast<const protocol::RetailPriceImprovementMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.retailpriceimprovementmessage";
            values[entry + ".payload.retailpriceimprovementmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.retailpriceimprovementmessage.symbolindex"] = canonical::number((*message).symbol_index());
            values[entry + ".payload.retailpriceimprovementmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.retailpriceimprovementmessage.rpiindicator"] = canonical::text(canonical::character((*message).rpi_indicator()), '\0', false);
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
    std::printf("== Nyse.NyseEquities.IntegratedFeed.Pillar.v2.5.g (classes values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/AddOrderMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/AddOrderMessage.values");
    failures += check("CrossTradeMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/CrossTradeMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/CrossTradeMessage.values");
    failures += check("DeleteOrderMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/DeleteOrderMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/DeleteOrderMessage.values");
    failures += check("ImbalanceMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/ImbalanceMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/ImbalanceMessage.values");
    failures += check("ModifyOrderMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/ModifyOrderMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/ModifyOrderMessage.values");
    failures += check("NonDisplayedTradeMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/NonDisplayedTradeMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/NonDisplayedTradeMessage.values");
    failures += check("OrderExecutionMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/OrderExecutionMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/OrderExecutionMessage.values");
    failures += check("ReplaceOrderMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/ReplaceOrderMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/ReplaceOrderMessage.values");
    failures += check("RetailPriceImprovementMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/RetailPriceImprovementMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/RetailPriceImprovementMessage.values");
    failures += check("SecurityStatusMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/SecurityStatusMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/SecurityStatusMessage.values");
    failures += check("SequenceNumberResetMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/SequenceNumberResetMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/SequenceNumberResetMessage.values");
    failures += check("SourceTimeReferenceMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/SourceTimeReferenceMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/SourceTimeReferenceMessage.values");
    failures += check("SymbolClearMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/SymbolClearMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/SymbolClearMessage.values");
    failures += check("SymbolIndexMappingMessage", "Nyse/NyseEquities.IntegratedFeed.Pillar.v2.5.g/SymbolIndexMappingMessage.pcap", "nyse/nyseequities/integratedfeed/pillar/v2.5.g/SymbolIndexMappingMessage.values");
    return failures == 0 ? 0 : 1;
}
