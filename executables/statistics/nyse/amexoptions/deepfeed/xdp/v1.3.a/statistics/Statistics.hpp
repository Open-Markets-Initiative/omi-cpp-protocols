#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/nyse/amexoptions/deepfeed/xdp/v1.3.a/definitions.hpp"

namespace statistics {

// Nyse Xdp C++ statistics
struct Statistics {

    nyse::amexoptions::deepfeed::xdp::v1_3_a::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t outright_market_depth_buy_message = 0;
    uint64_t outright_market_depth_sell_message = 0;
    uint64_t underlying_status_message = 0;
    uint64_t outright_series_status_message = 0;
    uint64_t refresh_outright_market_depth_buy_message = 0;
    uint64_t refresh_outright_market_depth_sell_message = 0;
    uint64_t underlying_index_mapping_message = 0;
    uint64_t series_index_mapping_message = 0;
    uint64_t stream_id_message = 0;
    uint64_t sequence_number_reset_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_message(frame);
        }
    }

    // walk the Packet tree's datagrams
    void walk_message(const packet::Frame& frame) {
        message.initialize(frame.payload, frame.payload_len);

        while (message.next()) {
            process_message(message.message, message.message_type);
        }
    }

    // count a message of the Packet tree
    void process_message(const std::byte*, const std::uint16_t message_type) {
        switch (message_type) {
            case 403:
                ++total_messages;
                ++outright_market_depth_buy_message;
                break;
            case 405:
                ++total_messages;
                ++outright_market_depth_sell_message;
                break;
            case 419:
                ++total_messages;
                ++underlying_status_message;
                break;
            case 421:
                ++total_messages;
                ++outright_series_status_message;
                break;
            case 503:
                ++total_messages;
                ++refresh_outright_market_depth_buy_message;
                break;
            case 505:
                ++total_messages;
                ++refresh_outright_market_depth_sell_message;
                break;
            case 435:
                ++total_messages;
                ++underlying_index_mapping_message;
                break;
            case 437:
                ++total_messages;
                ++series_index_mapping_message;
                break;
            case 455:
                ++total_messages;
                ++stream_id_message;
                break;
            case 1:
                ++total_messages;
                ++sequence_number_reset_message;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown message_type: " << static_cast<int>(message_type) << std::endl;
                }
                break;
        }
    }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  OutrightMarketDepthBuyMessage (403)          " << outright_market_depth_buy_message << std::endl;
        std::cout << "  OutrightMarketDepthSellMessage (405)         " << outright_market_depth_sell_message << std::endl;
        std::cout << "  UnderlyingStatusMessage (419)                " << underlying_status_message << std::endl;
        std::cout << "  OutrightSeriesStatusMessage (421)            " << outright_series_status_message << std::endl;
        std::cout << "  RefreshOutrightMarketDepthBuyMessage (503)   " << refresh_outright_market_depth_buy_message << std::endl;
        std::cout << "  RefreshOutrightMarketDepthSellMessage (505)  " << refresh_outright_market_depth_sell_message << std::endl;
        std::cout << "  UnderlyingIndexMappingMessage (435)          " << underlying_index_mapping_message << std::endl;
        std::cout << "  SeriesIndexMappingMessage (437)              " << series_index_mapping_message << std::endl;
        std::cout << "  StreamIdMessage (455)                        " << stream_id_message << std::endl;
        std::cout << "  SequenceNumberResetMessage (1)               " << sequence_number_reset_message << std::endl;
    }
};
}
