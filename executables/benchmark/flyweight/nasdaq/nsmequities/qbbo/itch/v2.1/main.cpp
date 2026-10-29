// Nasdaq.NsmEquities.Qbbo.Itch.v2.1 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/qbbo/itch/v2.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::qbbo::itch::v2_1;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().session());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().message_count());
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
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::StockDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.market_category());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.round_lots_only());
        checksum += bench::digest(message.issue_classification());
        checksum += bench::digest(message.issue_sub_type());
        checksum += bench::digest(message.authenticity());
        checksum += bench::digest(message.short_sale_threshold_indicator());
        checksum += bench::digest(message.ipo_flag());
        checksum += bench::digest(message.luld_reference_price_tier());
        checksum += bench::digest(message.etp_flag());
        checksum += bench::digest(message.etp_leverage_factor());
        checksum += bench::digest(message.inverse_indicator());
    }

    void on(const protocol::StockTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.current_trading_state());
        checksum += bench::digest(message.reason());
    }

    void on(const protocol::RegShoRestrictionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.reg_sho_action());
    }

    void on(const protocol::MwcbDeclineLevelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.level_1().mantissa());
        checksum += bench::digest(message.level_2().mantissa());
        checksum += bench::digest(message.level_3().mantissa());
    }

    void on(const protocol::MwcbBreachMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.breached_level());
    }

    void on(const protocol::OperationalHaltMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.market_code());
        checksum += bench::digest(message.operational_halt_action());
    }

    void on(const protocol::BboQuotationMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.best_bid_price().mantissa());
        checksum += bench::digest(message.best_bid_size());
        checksum += bench::digest(message.best_offer_price().mantissa());
        checksum += bench::digest(message.best_offer_size());
    }

    void on(const protocol::PriceImprovementMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.interest_flag());
    }

    void on(const protocol::IpoQuotingPeriodUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking());
        checksum += bench::digest(message.time_stamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.ipo_quotation_release_time());
        checksum += bench::digest(message.ipo_quotation_release_qualifier());
        checksum += bench::digest(message.ipo_price().mantissa());
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.Qbbo.Itch.v2.1", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
