// Eurex.T7.Eobi.Fbe.v13.0 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/classes/eurex/t7/eobi/fbe/v13.0/definitions.hpp"

namespace protocol = ::eurex::t7::eobi::fbe::v13_0;

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

    values["packet.packetheader.eobiheader.bodylen"] = canonical::number(packet.packet_header().eobi_header().body_len());
    values["packet.packetheader.eobiheader.templateid"] = canonical::number(packet.packet_header().eobi_header().template_id());
    values["packet.packetheader.eobiheader.msgseqnum"] = canonical::number(packet.packet_header().eobi_header().msg_seq_num());
    values["packet.packetheader.applseqnum"] = canonical::number(packet.packet_header().appl_seq_num());
    values["packet.packetheader.dscp"] = canonical::number(packet.packet_header().dscp());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheadercomp.bodylen"] = canonical::number(each.message_header_comp().body_len());
        values[entry + ".messageheadercomp.templateid"] = canonical::number(each.message_header_comp().template_id());
        values[entry + ".messageheadercomp.msgseqnum"] = canonical::number(each.message_header_comp().msg_seq_num());

        if (const auto* message = dynamic_cast<const protocol::AddComplexInstrument*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.addcomplexinstrument";
        } else if (const auto* message = dynamic_cast<const protocol::AddFlexibleInstrument*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.addflexibleinstrument";
        } else if (const auto* message = dynamic_cast<const protocol::AddScaledSimpleInstrument*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.addscaledsimpleinstrument";
        } else if (const auto* message = dynamic_cast<const protocol::AuctionBbo*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.auctionbbo";
        } else if (const auto* message = dynamic_cast<const protocol::AuctionClearingPrice*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.auctionclearingprice";
        } else if (const auto* message = dynamic_cast<const protocol::CrossRequest*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.crossrequest";
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummary*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.executionsummary";
        } else if (const auto* message = dynamic_cast<const protocol::FullOrderExecution*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.fullorderexecution";
        } else if (const auto* message = dynamic_cast<const protocol::Heartbeat*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.heartbeat";
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentStateChange*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.instrumentstatechange";
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentSummary*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.instrumentsummary";
        } else if (const auto* message = dynamic_cast<const protocol::MassInstrumentStateChange*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.massinstrumentstatechange";
        } else if (const auto* message = dynamic_cast<const protocol::OrderAdd*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.orderadd";
        } else if (const auto* message = dynamic_cast<const protocol::OrderDelete*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.orderdelete";
        } else if (const auto* message = dynamic_cast<const protocol::OrderMassDelete*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.ordermassdelete";
        } else if (const auto* message = dynamic_cast<const protocol::OrderModify*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.ordermodify";
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifySamePrio*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.ordermodifysameprio";
        } else if (const auto* message = dynamic_cast<const protocol::PartialOrderExecution*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.partialorderexecution";
        } else if (const auto* message = dynamic_cast<const protocol::ProductStateChange*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.productstatechange";
        } else if (const auto* message = dynamic_cast<const protocol::ProductSummary*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.productsummary";
        } else if (const auto* message = dynamic_cast<const protocol::QuoteRequest*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.quoterequest";
        } else if (const auto* message = dynamic_cast<const protocol::SnapshotOrder*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.snapshotorder";
        } else if (const auto* message = dynamic_cast<const protocol::TesTradeReport*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.testradereport";
        } else if (const auto* message = dynamic_cast<const protocol::TopOfBook*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.topofbook";
        } else if (const auto* message = dynamic_cast<const protocol::TradeReport*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.tradereport";
        } else if (const auto* message = dynamic_cast<const protocol::TradeReversal*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.tradereversal";
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
    std::printf("== Eurex.T7.Eobi.Fbe.v13.0 (classes values)\n");
    int failures = 0;
    failures += check("AddComplexInstrument", "Eurex/T7.Eobi.Fbe.v13.0/AddComplexInstrument.pcap", "eurex/t7/eobi/fbe/v13.0/AddComplexInstrument.values");
    failures += check("AddFlexibleInstrument", "Eurex/T7.Eobi.Fbe.v13.0/AddFlexibleInstrument.pcap", "eurex/t7/eobi/fbe/v13.0/AddFlexibleInstrument.values");
    failures += check("AuctionBbo", "Eurex/T7.Eobi.Fbe.v13.0/AuctionBbo.pcap", "eurex/t7/eobi/fbe/v13.0/AuctionBbo.values");
    failures += check("AuctionClearingPrice", "Eurex/T7.Eobi.Fbe.v13.0/AuctionClearingPrice.pcap", "eurex/t7/eobi/fbe/v13.0/AuctionClearingPrice.values");
    failures += check("CrossRequest", "Eurex/T7.Eobi.Fbe.v13.0/CrossRequest.pcap", "eurex/t7/eobi/fbe/v13.0/CrossRequest.values");
    failures += check("ExecutionSummary", "Eurex/T7.Eobi.Fbe.v13.0/ExecutionSummary.pcap", "eurex/t7/eobi/fbe/v13.0/ExecutionSummary.values");
    failures += check("FullOrderExecution", "Eurex/T7.Eobi.Fbe.v13.0/FullOrderExecution.pcap", "eurex/t7/eobi/fbe/v13.0/FullOrderExecution.values");
    failures += check("Heartbeat", "Eurex/T7.Eobi.Fbe.v13.0/Heartbeat.pcap", "eurex/t7/eobi/fbe/v13.0/Heartbeat.values");
    failures += check("InstrumentStateChange", "Eurex/T7.Eobi.Fbe.v13.0/InstrumentStateChange.pcap", "eurex/t7/eobi/fbe/v13.0/InstrumentStateChange.values");
    failures += check("InstrumentSummary", "Eurex/T7.Eobi.Fbe.v13.0/InstrumentSummary.pcap", "eurex/t7/eobi/fbe/v13.0/InstrumentSummary.values");
    failures += check("MassInstrumentStateChange", "Eurex/T7.Eobi.Fbe.v13.0/MassInstrumentStateChange.pcap", "eurex/t7/eobi/fbe/v13.0/MassInstrumentStateChange.values");
    failures += check("OrderAdd", "Eurex/T7.Eobi.Fbe.v13.0/OrderAdd.pcap", "eurex/t7/eobi/fbe/v13.0/OrderAdd.values");
    failures += check("OrderDelete", "Eurex/T7.Eobi.Fbe.v13.0/OrderDelete.pcap", "eurex/t7/eobi/fbe/v13.0/OrderDelete.values");
    failures += check("OrderMassDelete", "Eurex/T7.Eobi.Fbe.v13.0/OrderMassDelete.pcap", "eurex/t7/eobi/fbe/v13.0/OrderMassDelete.values");
    failures += check("OrderModify", "Eurex/T7.Eobi.Fbe.v13.0/OrderModify.pcap", "eurex/t7/eobi/fbe/v13.0/OrderModify.values");
    failures += check("OrderModifySamePrio", "Eurex/T7.Eobi.Fbe.v13.0/OrderModifySamePrio.pcap", "eurex/t7/eobi/fbe/v13.0/OrderModifySamePrio.values");
    failures += check("PartialOrderExecution", "Eurex/T7.Eobi.Fbe.v13.0/PartialOrderExecution.pcap", "eurex/t7/eobi/fbe/v13.0/PartialOrderExecution.values");
    failures += check("ProductStateChange", "Eurex/T7.Eobi.Fbe.v13.0/ProductStateChange.pcap", "eurex/t7/eobi/fbe/v13.0/ProductStateChange.values");
    failures += check("ProductSummary", "Eurex/T7.Eobi.Fbe.v13.0/ProductSummary.pcap", "eurex/t7/eobi/fbe/v13.0/ProductSummary.values");
    failures += check("QuoteRequest", "Eurex/T7.Eobi.Fbe.v13.0/QuoteRequest.pcap", "eurex/t7/eobi/fbe/v13.0/QuoteRequest.values");
    failures += check("SnapshotOrder", "Eurex/T7.Eobi.Fbe.v13.0/SnapshotOrder.pcap", "eurex/t7/eobi/fbe/v13.0/SnapshotOrder.values");
    failures += check("TesTradeReport", "Eurex/T7.Eobi.Fbe.v13.0/TesTradeReport.pcap", "eurex/t7/eobi/fbe/v13.0/TesTradeReport.values");
    failures += check("TopOfBook", "Eurex/T7.Eobi.Fbe.v13.0/TopOfBook.pcap", "eurex/t7/eobi/fbe/v13.0/TopOfBook.values");
    failures += check("TradeReport", "Eurex/T7.Eobi.Fbe.v13.0/TradeReport.pcap", "eurex/t7/eobi/fbe/v13.0/TradeReport.values");
    failures += check("TradeReversal", "Eurex/T7.Eobi.Fbe.v13.0/TradeReversal.pcap", "eurex/t7/eobi/fbe/v13.0/TradeReversal.values");
    return failures == 0 ? 0 : 1;
}