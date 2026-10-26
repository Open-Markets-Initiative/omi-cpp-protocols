// Iex.IexEquities.Deep.IexTp.v1.06 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/iex/iexequities/deep/iextp/v1.06/definitions.hpp"

namespace protocol = ::iex::iexequities::deep::iextp::v1_06;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.iextpheader.version"] = canonical::number(packet.iextp_header().version());
        values["packet.iextpheader.messageprotocolid"] = canonical::number(packet.iextp_header().message_protocol_id());
        values["packet.iextpheader.channelid"] = canonical::number(packet.iextp_header().channel_id());
        values["packet.iextpheader.sessionid"] = canonical::number(packet.iextp_header().session_id());
        values["packet.iextpheader.payloadlength"] = canonical::number(packet.iextp_header().payload_length());
        values["packet.iextpheader.messagecount"] = canonical::number(packet.iextp_header().message_count());
        values["packet.iextpheader.streamoffset"] = canonical::number(packet.iextp_header().stream_offset());
        values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(packet.iextp_header().first_message_sequence_number());
        values["packet.iextpheader.sendtime"] = canonical::number(packet.iextp_header().send_time());
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

    void on(const protocol::SystemEventMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.systemeventmessage";
        values[entry + ".messagedata.systemeventmessage.systemevent"] = canonical::text(canonical::character(message.system_event()));
        values[entry + ".messagedata.systemeventmessage.timestamp"] = canonical::number(message.timestamp());
    }

    void on(const protocol::SecurityDirectoryMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.securitydirectorymessage";
        values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.etp"] = canonical::number(static_cast<std::uint64_t>(message.security_directory_flags().etp()));
        values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.whenissued"] = canonical::number(static_cast<std::uint64_t>(message.security_directory_flags().when_issued()));
        values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.testsecurity"] = canonical::number(static_cast<std::uint64_t>(message.security_directory_flags().test_security()));
        values[entry + ".messagedata.securitydirectorymessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.securitydirectorymessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.securitydirectorymessage.roundlotsize"] = canonical::number(message.round_lot_size());
        values[entry + ".messagedata.securitydirectorymessage.adjustedpocprice"] = canonical::scaled(message.adjusted_poc_price().mantissa(), message.adjusted_poc_price().exponent());
        values[entry + ".messagedata.securitydirectorymessage.luldtier"] = canonical::number(message.luld_tier());
    }

    void on(const protocol::TradingStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradingstatusmessage";
        values[entry + ".messagedata.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.trading_status()));
        values[entry + ".messagedata.tradingstatusmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.tradingstatusmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.tradingstatusmessage.reason"] = canonical::text(std::string(message.reason()), ' ', false);
    }

    void on(const protocol::OperationalHaltStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.operationalhaltstatusmessage";
        values[entry + ".messagedata.operationalhaltstatusmessage.operationalhaltstatus"] = canonical::text(canonical::character(message.operational_halt_status()));
        values[entry + ".messagedata.operationalhaltstatusmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.operationalhaltstatusmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
    }

    void on(const protocol::ShortSalePriceTestStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.shortsalepriceteststatusmessage";
        values[entry + ".messagedata.shortsalepriceteststatusmessage.shortsalepriceteststatus"] = canonical::number(message.short_sale_price_test_status());
        values[entry + ".messagedata.shortsalepriceteststatusmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.shortsalepriceteststatusmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.shortsalepriceteststatusmessage.detail"] = canonical::text(canonical::character(message.detail()));
    }

    void on(const protocol::SecurityEventMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.securityeventmessage";
        values[entry + ".messagedata.securityeventmessage.securityevent"] = canonical::text(canonical::character(message.security_event()));
        values[entry + ".messagedata.securityeventmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.securityeventmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
    }

    void on(const protocol::PriceLevelBuyUpdateMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.pricelevelbuyupdatemessage";
        values[entry + ".messagedata.pricelevelbuyupdatemessage.eventflags"] = canonical::number(message.event_flags());
        values[entry + ".messagedata.pricelevelbuyupdatemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.pricelevelbuyupdatemessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.pricelevelbuyupdatemessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.pricelevelbuyupdatemessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::PriceLevelSellUpdateMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.pricelevelsellupdatemessage";
        values[entry + ".messagedata.pricelevelsellupdatemessage.eventflags"] = canonical::number(message.event_flags());
        values[entry + ".messagedata.pricelevelsellupdatemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.pricelevelsellupdatemessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.pricelevelsellupdatemessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.pricelevelsellupdatemessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::TradeReportMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradereportmessage";
        values[entry + ".messagedata.tradereportmessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().singleprice_cross_trade()));
        values[entry + ".messagedata.tradereportmessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().trade_through_exempt()));
        values[entry + ".messagedata.tradereportmessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().odd_lot()));
        values[entry + ".messagedata.tradereportmessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().extended_hours()));
        values[entry + ".messagedata.tradereportmessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().intermarket_sweep()));
        values[entry + ".messagedata.tradereportmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.tradereportmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.tradereportmessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.tradereportmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".messagedata.tradereportmessage.tradeid"] = canonical::number(message.trade_id());
    }

    void on(const protocol::OfficialPriceMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.officialpricemessage";
        values[entry + ".messagedata.officialpricemessage.pricetype"] = canonical::text(canonical::character(message.price_type()));
        values[entry + ".messagedata.officialpricemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.officialpricemessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.officialpricemessage.officialprice"] = canonical::scaled(message.official_price().mantissa(), message.official_price().exponent());
    }

    void on(const protocol::TradeBreakMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().singleprice_cross_trade()));
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().trade_through_exempt()));
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().odd_lot()));
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().extended_hours()));
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>(message.sale_condition_flags().intermarket_sweep()));
        values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message.trade_id());
    }

    void on(const protocol::AuctionInformationMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.auctioninformationmessage";
        values[entry + ".messagedata.auctioninformationmessage.auctiontype"] = canonical::text(canonical::character(message.auction_type()));
        values[entry + ".messagedata.auctioninformationmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.auctioninformationmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.auctioninformationmessage.pairedshares"] = canonical::number(message.paired_shares());
        values[entry + ".messagedata.auctioninformationmessage.referenceprice"] = canonical::scaled(message.reference_price().mantissa(), message.reference_price().exponent());
        values[entry + ".messagedata.auctioninformationmessage.indicativeclearingprice"] = canonical::scaled(message.indicative_clearing_price().mantissa(), message.indicative_clearing_price().exponent());
        values[entry + ".messagedata.auctioninformationmessage.imbalanceshares"] = canonical::number(message.imbalance_shares());
        values[entry + ".messagedata.auctioninformationmessage.imbalanceside"] = canonical::text(canonical::character(message.imbalance_side()));
        values[entry + ".messagedata.auctioninformationmessage.extensionnumber"] = canonical::text(canonical::character(message.extension_number()));
        values[entry + ".messagedata.auctioninformationmessage.scheduledauctiontime"] = canonical::number(message.scheduled_auction_time());
        values[entry + ".messagedata.auctioninformationmessage.auctionbookclearingprice"] = canonical::scaled(message.auction_book_clearing_price().mantissa(), message.auction_book_clearing_price().exponent());
        values[entry + ".messagedata.auctioninformationmessage.collarreferenceprice"] = canonical::scaled(message.collar_reference_price().mantissa(), message.collar_reference_price().exponent());
        values[entry + ".messagedata.auctioninformationmessage.lowerauctioncollar"] = canonical::scaled(message.lower_auction_collar().mantissa(), message.lower_auction_collar().exponent());
        values[entry + ".messagedata.auctioninformationmessage.upperauctioncollar"] = canonical::scaled(message.upper_auction_collar().mantissa(), message.upper_auction_collar().exponent());
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
    std::printf("== Iex.IexEquities.Deep.IexTp.v1.06 (flyweight values)\n");
    int failures = 0;
    failures += check("AuctionInformationMessage", "Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap", "iex/iexequities/deep/iextp/v1.06/AuctionInformationMessage.values");
    failures += check("Heartbeat", "Iex/IexEquities.Deep.IexTp.v1.06/Heartbeat.pcap", "iex/iexequities/deep/iextp/v1.06/Heartbeat.values");
    failures += check("OfficialPriceMessage", "Iex/IexEquities.Deep.IexTp.v1.06/OfficialPriceMessage.pcap", "iex/iexequities/deep/iextp/v1.06/OfficialPriceMessage.values");
    failures += check("PriceLevelBuyUpdateMessage", "Iex/IexEquities.Deep.IexTp.v1.06/PriceLevelBuyUpdateMessage.pcap", "iex/iexequities/deep/iextp/v1.06/PriceLevelBuyUpdateMessage.values");
    failures += check("PriceLevelSellUpdateMessage", "Iex/IexEquities.Deep.IexTp.v1.06/PriceLevelSellUpdateMessage.pcap", "iex/iexequities/deep/iextp/v1.06/PriceLevelSellUpdateMessage.values");
    failures += check("SecurityEventMessage", "Iex/IexEquities.Deep.IexTp.v1.06/SecurityEventMessage.pcap", "iex/iexequities/deep/iextp/v1.06/SecurityEventMessage.values");
    failures += check("ShortSalePriceTestStatusMessage", "Iex/IexEquities.Deep.IexTp.v1.06/ShortSalePriceTestStatusMessage.pcap", "iex/iexequities/deep/iextp/v1.06/ShortSalePriceTestStatusMessage.values");
    failures += check("SystemEventMessage", "Iex/IexEquities.Deep.IexTp.v1.06/SystemEventMessage.pcap", "iex/iexequities/deep/iextp/v1.06/SystemEventMessage.values");
    failures += check("TradeReportMessage", "Iex/IexEquities.Deep.IexTp.v1.06/TradeReportMessage.pcap", "iex/iexequities/deep/iextp/v1.06/TradeReportMessage.values");
    failures += check("TradingStatusMessage", "Iex/IexEquities.Deep.IexTp.v1.06/TradingStatusMessage.pcap", "iex/iexequities/deep/iextp/v1.06/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
