// Bse.BseIndia.Eobi.Fbe.v1.4 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/bse/bseindia/eobi/fbe/v1.4/definitions.hpp"

namespace protocol = ::bse::bseindia::eobi::fbe::v1_4;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.eobiheader.bodylen"] = canonical::number(packet.packet_header().eobi_header().body_len());
        values["packet.packetheader.eobiheader.templateid"] = canonical::number(packet.packet_header().eobi_header().template_id());
        values["packet.packetheader.eobiheader.msgseqnum"] = canonical::number(packet.packet_header().eobi_header().msg_seq_num());
        values["packet.packetheader.applseqnum"] = canonical::number(packet.packet_header().appl_seq_num());
        values["packet.packetheader.marketsegmentid"] = canonical::number(packet.packet_header().market_segment_id());
        values["packet.packetheader.partitionid"] = canonical::number(packet.packet_header().partition_id());
        values["packet.packetheader.completionindicator"] = canonical::number(packet.packet_header().completion_indicator());
        values["packet.packetheader.applseqresetindicator"] = canonical::number(packet.packet_header().appl_seq_reset_indicator());
        values["packet.packetheader.transacttime"] = canonical::number(packet.packet_header().transact_time());
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

    void on(const protocol::HeartbeatMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.heartbeatmessage";
        values[entry + ".payload.heartbeatmessage.lastmsgseqnumprocessed"] = canonical::number(message.last_msg_seq_num_processed());
    }

    void on(const protocol::ProductSummaryMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.productsummarymessage";
        values[entry + ".payload.productsummarymessage.lastmsgseqnumprocessed"] = canonical::number(message.last_msg_seq_num_processed());
        values[entry + ".payload.productsummarymessage.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.productsummarymessage.tradingsessionsubid"] = canonical::number(message.trading_session_sub_id());
        values[entry + ".payload.productsummarymessage.tradsesstatus"] = canonical::number(message.trad_ses_status());
        values[entry + ".payload.productsummarymessage.fastmarketindicator"] = canonical::number(message.fast_market_indicator());
    }

    void on(const protocol::SnapshotOrderMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.snapshotordermessage";
        values[entry + ".payload.snapshotordermessage.orderdetails.trdregtstimepriority"] = canonical::number(message.order_details().trd_reg_ts_time_priority());
        values[entry + ".payload.snapshotordermessage.orderdetails.displayqty"] = canonical::number(message.order_details().display_qty());
        values[entry + ".payload.snapshotordermessage.orderdetails.side"] = canonical::number(message.order_details().side());
        values[entry + ".payload.snapshotordermessage.orderdetails.price"] = canonical::scaled(message.order_details().price().mantissa(), message.order_details().price().exponent());
    }

    void on(const protocol::InstrumentSummaryMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.instrumentsummarymessage";
        values[entry + ".payload.instrumentsummarymessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.instrumentsummarymessage.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.instrumentsummarymessage.trdregtsexecutiontime"] = (message.trd_reg_ts_execution_time().has_value() ? canonical::number((*message.trd_reg_ts_execution_time())) : canonical::absent());
        values[entry + ".payload.instrumentsummarymessage.totnoorders"] = canonical::number(message.tot_no_orders());
        values[entry + ".payload.instrumentsummarymessage.securitystatus"] = canonical::number(message.security_status());
        values[entry + ".payload.instrumentsummarymessage.securitytradingstatus"] = canonical::number(message.security_trading_status());
        values[entry + ".payload.instrumentsummarymessage.fastmarketindicator"] = canonical::number(message.fast_market_indicator());
        values[entry + ".payload.instrumentsummarymessage.nomdentries"] = canonical::number(message.no_md_entries());
        values[entry + ".payload.instrumentsummarymessage.tradevolume"] = canonical::number(message.trade_volume());
        values[entry + ".payload.instrumentsummarymessage.nooftrades"] = canonical::number(message.no_of_trades());
    }

    void on(const protocol::AuctionBestBidOfferMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.auctionbestbidoffermessage";
        values[entry + ".payload.auctionbestbidoffermessage.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.auctionbestbidoffermessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.auctionbestbidoffermessage.bidpx"] = (message.bid_px().has_value() ? canonical::scaled((*message.bid_px()).mantissa(), (*message.bid_px()).exponent()) : canonical::absent());
        values[entry + ".payload.auctionbestbidoffermessage.offerpx"] = (message.offer_px().has_value() ? canonical::scaled((*message.offer_px()).mantissa(), (*message.offer_px()).exponent()) : canonical::absent());
    }

    void on(const protocol::AuctionClearingPriceMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.auctionclearingpricemessage";
        values[entry + ".payload.auctionclearingpricemessage.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.auctionclearingpricemessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.auctionclearingpricemessage.lastpx"] = canonical::scaled(message.last_px().mantissa(), message.last_px().exponent());
        values[entry + ".payload.auctionclearingpricemessage.lastqty"] = canonical::number(message.last_qty());
    }

    void on(const protocol::TopOfBookMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.topofbookmessage";
        values[entry + ".payload.topofbookmessage.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.topofbookmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.topofbookmessage.bidpx"] = (message.bid_px().has_value() ? canonical::scaled((*message.bid_px()).mantissa(), (*message.bid_px()).exponent()) : canonical::absent());
        values[entry + ".payload.topofbookmessage.offerpx"] = (message.offer_px().has_value() ? canonical::scaled((*message.offer_px()).mantissa(), (*message.offer_px()).exponent()) : canonical::absent());
    }

    void on(const protocol::OrderAddMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.orderaddmessage";
        values[entry + ".payload.orderaddmessage.trdregtstimein"] = (message.trd_reg_ts_time_in().has_value() ? canonical::number((*message.trd_reg_ts_time_in())) : canonical::absent());
        values[entry + ".payload.orderaddmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.orderaddmessage.orderdetails.trdregtstimepriority"] = canonical::number(message.order_details().trd_reg_ts_time_priority());
        values[entry + ".payload.orderaddmessage.orderdetails.displayqty"] = canonical::number(message.order_details().display_qty());
        values[entry + ".payload.orderaddmessage.orderdetails.side"] = canonical::number(message.order_details().side());
        values[entry + ".payload.orderaddmessage.orderdetails.price"] = canonical::scaled(message.order_details().price().mantissa(), message.order_details().price().exponent());
    }

    void on(const protocol::OrderModifyMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.ordermodifymessage";
        values[entry + ".payload.ordermodifymessage.trdregtstimein"] = (message.trd_reg_ts_time_in().has_value() ? canonical::number((*message.trd_reg_ts_time_in())) : canonical::absent());
        values[entry + ".payload.ordermodifymessage.trdregtsprevtimepriority"] = canonical::number(message.trd_reg_ts_prev_time_priority());
        values[entry + ".payload.ordermodifymessage.prevprice"] = canonical::scaled(message.prev_price().mantissa(), message.prev_price().exponent());
        values[entry + ".payload.ordermodifymessage.prevdisplayqty"] = canonical::number(message.prev_display_qty());
        values[entry + ".payload.ordermodifymessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.ordermodifymessage.orderdetails.trdregtstimepriority"] = canonical::number(message.order_details().trd_reg_ts_time_priority());
        values[entry + ".payload.ordermodifymessage.orderdetails.displayqty"] = canonical::number(message.order_details().display_qty());
        values[entry + ".payload.ordermodifymessage.orderdetails.side"] = canonical::number(message.order_details().side());
        values[entry + ".payload.ordermodifymessage.orderdetails.price"] = canonical::scaled(message.order_details().price().mantissa(), message.order_details().price().exponent());
    }

    void on(const protocol::OrderModifySamePriorityMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.ordermodifysameprioritymessage";
        values[entry + ".payload.ordermodifysameprioritymessage.trdregtstimein"] = (message.trd_reg_ts_time_in().has_value() ? canonical::number((*message.trd_reg_ts_time_in())) : canonical::absent());
        values[entry + ".payload.ordermodifysameprioritymessage.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.ordermodifysameprioritymessage.prevdisplayqty"] = canonical::number(message.prev_display_qty());
        values[entry + ".payload.ordermodifysameprioritymessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.ordermodifysameprioritymessage.orderdetails.trdregtstimepriority"] = canonical::number(message.order_details().trd_reg_ts_time_priority());
        values[entry + ".payload.ordermodifysameprioritymessage.orderdetails.displayqty"] = canonical::number(message.order_details().display_qty());
        values[entry + ".payload.ordermodifysameprioritymessage.orderdetails.side"] = canonical::number(message.order_details().side());
        values[entry + ".payload.ordermodifysameprioritymessage.orderdetails.price"] = canonical::scaled(message.order_details().price().mantissa(), message.order_details().price().exponent());
    }

    void on(const protocol::OrderDeleteMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.orderdeletemessage";
        values[entry + ".payload.orderdeletemessage.trdregtstimein"] = (message.trd_reg_ts_time_in().has_value() ? canonical::number((*message.trd_reg_ts_time_in())) : canonical::absent());
        values[entry + ".payload.orderdeletemessage.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.orderdeletemessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.orderdeletemessage.orderdetails.trdregtstimepriority"] = canonical::number(message.order_details().trd_reg_ts_time_priority());
        values[entry + ".payload.orderdeletemessage.orderdetails.displayqty"] = canonical::number(message.order_details().display_qty());
        values[entry + ".payload.orderdeletemessage.orderdetails.side"] = canonical::number(message.order_details().side());
        values[entry + ".payload.orderdeletemessage.orderdetails.price"] = canonical::scaled(message.order_details().price().mantissa(), message.order_details().price().exponent());
    }

    void on(const protocol::OrderMassDeleteMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.ordermassdeletemessage";
        values[entry + ".payload.ordermassdeletemessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.ordermassdeletemessage.transacttime"] = canonical::number(message.transact_time());
    }

    void on(const protocol::PartialOrderExecutionMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.partialorderexecutionmessage";
        values[entry + ".payload.partialorderexecutionmessage.side"] = canonical::number(message.side());
        values[entry + ".payload.partialorderexecutionmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.partialorderexecutionmessage.trdregtstimepriority"] = canonical::number(message.trd_reg_ts_time_priority());
        values[entry + ".payload.partialorderexecutionmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.partialorderexecutionmessage.trdmatchid"] = canonical::number(message.trd_match_id());
        values[entry + ".payload.partialorderexecutionmessage.lastqty"] = canonical::number(message.last_qty());
        values[entry + ".payload.partialorderexecutionmessage.lastpx"] = canonical::scaled(message.last_px().mantissa(), message.last_px().exponent());
    }

    void on(const protocol::FullOrderExecutionMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.fullorderexecutionmessage";
        values[entry + ".payload.fullorderexecutionmessage.side"] = canonical::number(message.side());
        values[entry + ".payload.fullorderexecutionmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.fullorderexecutionmessage.trdregtstimepriority"] = canonical::number(message.trd_reg_ts_time_priority());
        values[entry + ".payload.fullorderexecutionmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.fullorderexecutionmessage.trdmatchid"] = canonical::number(message.trd_match_id());
        values[entry + ".payload.fullorderexecutionmessage.lastqty"] = canonical::number(message.last_qty());
        values[entry + ".payload.fullorderexecutionmessage.lastpx"] = canonical::scaled(message.last_px().mantissa(), message.last_px().exponent());
    }

    void on(const protocol::TradeReversalMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.tradereversalmessage";
        values[entry + ".payload.tradereversalmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.tradereversalmessage.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.tradereversalmessage.trdmatchid"] = canonical::number(message.trd_match_id());
        values[entry + ".payload.tradereversalmessage.lastqty"] = canonical::number(message.last_qty());
        values[entry + ".payload.tradereversalmessage.lastpx"] = canonical::scaled(message.last_px().mantissa(), message.last_px().exponent());
        values[entry + ".payload.tradereversalmessage.trdregtsexecutiontime"] = (message.trd_reg_ts_execution_time().has_value() ? canonical::number((*message.trd_reg_ts_execution_time())) : canonical::absent());
        values[entry + ".payload.tradereversalmessage.nomdentries"] = canonical::number(message.no_md_entries());
    }

    void on(const protocol::ExecutionSummaryMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.executionsummarymessage";
        values[entry + ".payload.executionsummarymessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.executionsummarymessage.aggressortimestamp"] = (message.aggressor_timestamp().has_value() ? canonical::number((*message.aggressor_timestamp())) : canonical::absent());
        values[entry + ".payload.executionsummarymessage.execid"] = canonical::number(message.exec_id());
        values[entry + ".payload.executionsummarymessage.lastqty"] = canonical::number(message.last_qty());
        values[entry + ".payload.executionsummarymessage.aggressorside"] = canonical::number(message.aggressor_side());
        values[entry + ".payload.executionsummarymessage.tradecondition"] = (message.trade_condition().has_value() ? canonical::number((*message.trade_condition())) : canonical::absent());
        values[entry + ".payload.executionsummarymessage.lastpx"] = canonical::scaled(message.last_px().mantissa(), message.last_px().exponent());
        values[entry + ".payload.executionsummarymessage.restinghiddenqty"] = (message.resting_hidden_qty().has_value() ? canonical::number((*message.resting_hidden_qty())) : canonical::absent());
    }

    void on(const protocol::InstrumentInfoMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.instrumentinfomessage";
        values[entry + ".payload.instrumentinfomessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.instrumentinfomessage.closeprice"] = (message.close_price().has_value() ? canonical::scaled((*message.close_price()).mantissa(), (*message.close_price()).exponent()) : canonical::absent());
        values[entry + ".payload.instrumentinfomessage.prevcloseprice"] = (message.prev_close_price().has_value() ? canonical::scaled((*message.prev_close_price()).mantissa(), (*message.prev_close_price()).exponent()) : canonical::absent());
        values[entry + ".payload.instrumentinfomessage.uppercktlimit"] = (message.upper_ckt_limit().has_value() ? canonical::scaled((*message.upper_ckt_limit()).mantissa(), (*message.upper_ckt_limit()).exponent()) : canonical::absent());
        values[entry + ".payload.instrumentinfomessage.lowercktlimit"] = (message.lower_ckt_limit().has_value() ? canonical::scaled((*message.lower_ckt_limit()).mantissa(), (*message.lower_ckt_limit()).exponent()) : canonical::absent());
    }

    void on(const protocol::LppRangeMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.lpprangemessage";
        values[entry + ".payload.lpprangemessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.lpprangemessage.upperexeclimit"] = canonical::scaled(message.upper_exec_limit().mantissa(), message.upper_exec_limit().exponent());
        values[entry + ".payload.lpprangemessage.lowerexeclimit"] = canonical::scaled(message.lower_exec_limit().mantissa(), message.lower_exec_limit().exponent());
    }

    void on(const protocol::ProductStateChangeMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.productstatechangemessage";
        values[entry + ".payload.productstatechangemessage.tradingsessionid"] = canonical::number(message.trading_session_id());
        values[entry + ".payload.productstatechangemessage.tradingsessionsubid"] = canonical::number(message.trading_session_sub_id());
        values[entry + ".payload.productstatechangemessage.tradsesstatus"] = canonical::number(message.trad_ses_status());
        values[entry + ".payload.productstatechangemessage.fastmarketindicator"] = canonical::number(message.fast_market_indicator());
        values[entry + ".payload.productstatechangemessage.transacttime"] = canonical::number(message.transact_time());
    }

    void on(const protocol::InstrumentStateChangeMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.instrumentstatechangemessage";
        values[entry + ".payload.instrumentstatechangemessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.instrumentstatechangemessage.securitystatus"] = canonical::number(message.security_status());
        values[entry + ".payload.instrumentstatechangemessage.securitytradingstatus"] = canonical::number(message.security_trading_status());
        values[entry + ".payload.instrumentstatechangemessage.fastmarketindicator"] = canonical::number(message.fast_market_indicator());
        values[entry + ".payload.instrumentstatechangemessage.transacttime"] = canonical::number(message.transact_time());
    }

    void on(const protocol::AddComplexInstrumentMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.addcomplexinstrumentmessage";
        values[entry + ".payload.addcomplexinstrumentmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.addcomplexinstrumentmessage.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.addcomplexinstrumentmessage.securitysubtype"] = (message.security_sub_type().has_value() ? canonical::number((*message.security_sub_type())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrumentmessage.productcomplex"] = canonical::number(message.product_complex());
        values[entry + ".payload.addcomplexinstrumentmessage.impliedmarketindicator"] = canonical::number(message.implied_market_indicator());
        values[entry + ".payload.addcomplexinstrumentmessage.nolegs"] = canonical::number(message.no_legs());
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
    std::printf("== Bse.BseIndia.Eobi.Fbe.v1.4 (flyweight values)\n");
    int failures = 0;
    failures += check("ExecutionSummaryMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/ExecutionSummaryMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/ExecutionSummaryMessage.values");
    failures += check("FullOrderExecutionMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/FullOrderExecutionMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/FullOrderExecutionMessage.values");
    failures += check("HeartbeatMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/HeartbeatMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/HeartbeatMessage.values");
    failures += check("InstrumentInfoMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/InstrumentInfoMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/InstrumentInfoMessage.values");
    failures += check("InstrumentStateChangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/InstrumentStateChangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/InstrumentStateChangeMessage.values");
    failures += check("LppRangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/LppRangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/LppRangeMessage.values");
    failures += check("OrderAddMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderAddMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderAddMessage.values");
    failures += check("OrderDeleteMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderDeleteMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderDeleteMessage.values");
    failures += check("OrderModifyMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderModifyMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderModifyMessage.values");
    failures += check("PartialOrderExecutionMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/PartialOrderExecutionMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/PartialOrderExecutionMessage.values");
    failures += check("ProductStateChangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/ProductStateChangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/ProductStateChangeMessage.values");
    return failures == 0 ? 0 : 1;
}
