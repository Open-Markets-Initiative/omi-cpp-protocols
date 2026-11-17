// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: main.cpp
// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/memx/memxequities/memoirdepthfeed/sbe/v1.3.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/advanced/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/session.hpp"

namespace protocol = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::common_header& header, const packet::Frame&) {
        checksum += bench::digest(header.message_type.get().value());
        checksum += bench::digest(header.header_length.get().value());
        checksum += bench::digest(header.session_id.get().value());
        checksum += bench::digest(header.sequence_number.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::common_header&) {
        ++index;
    }

    void on_message(const protocol::instrument_directory_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.symbol_sfx.get().value());
        checksum += bench::digest(message.fields.round_lot.get().value());
        checksum += bench::digest(message.fields.is_test_symbol.get().value());
        checksum += bench::digest(message.fields.mpv.get().value());
    }

    void on_message(const protocol::reg_sho_restriction_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction.get().value());
    }

    void on_message(const protocol::security_trading_status_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_trading_status.get().value());
        checksum += bench::digest(message.fields.security_trading_status_reason.get().value());
    }

    void on_message(const protocol::trading_session_status_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.trading_session.get().value());
    }

    void on_message(const protocol::order_added_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::order_deleted_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
    }

    void on_message(const protocol::order_reduced_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::broken_trade_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.original_quantity.get().value());
        checksum += bench::digest(message.fields.original_price.get().value());
    }

    void on_message(const protocol::corrected_trade_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.original_quantity.get().value());
        checksum += bench::digest(message.fields.original_price.get().value());
        checksum += bench::digest(message.fields.corrected_quantity.get().value());
        checksum += bench::digest(message.fields.corrected_price.get().value());
    }

    void on_message(const protocol::clear_book_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
    }

    void on_message(const protocol::snapshot_complete_message& message, std::uint64_t, const protocol::common_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.block_length.get().value());
        checksum += bench::digest(message.header.template_id.get().value());
        checksum += bench::digest(message.header.schema_id.get().value());
        checksum += bench::digest(message.header.version.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.as_of_sequence_number.get().value());
    }
};

// The values Advanced reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
