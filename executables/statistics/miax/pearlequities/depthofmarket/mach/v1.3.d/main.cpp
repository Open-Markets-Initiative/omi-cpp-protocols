#include "Settings.hpp"

int main(const int argc, char** argv) {
    try {
        const auto settings = args(argc, argv);

        packet::Parser parser{ settings.pcap };
        statistics::Statistics statistics{ settings.statistics, parser };

        while (parser.next()) {
            ++statistics.total_packets;
            if (parser.identify() == packet::result::miax_pearlequities_depthofmarket_mach_v1_3_d) {
                statistics.udp();
            } else {
                ++statistics.unknown_packets;
            }
        }

        statistics.report();
        return 0;
    }
    catch (const std::exception &exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
}