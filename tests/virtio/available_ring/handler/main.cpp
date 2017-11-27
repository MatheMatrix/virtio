/* Copyright 2017 Tymoteusz Blazejczyk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "virtio_available_ring_handler_top.h"

#include <logic/trace.hpp>
#include <logic/axi4/stream/bus_if.hpp>
#include <logic/axi4/stream/reset_if.hpp>

#include <uvm>
#include <systemc>

int sc_main(int /* argc */, char** /* argv */) {
    bool test_passed{false};

    sc_core::sc_clock aclk{"aclk"};
    sc_core::sc_signal<bool> areset_n{"areset_n"};

    logic::axi4::stream::bus_if<2> rx{"rx"};
    logic::axi4::stream::bus_if<4> tx{"tx"};
    logic::axi4::stream::bus_if<> notify{"notify"};
    logic::axi4::stream::bus_if<> configure{"configure"};
    logic::axi4::stream::reset_if reset{};

    virtio_available_ring_handler_top dut{"virtio_available_ring_handler_top"};

    logic::trace<decltype(dut)> trace{dut};

    uvm::uvm_config_db<logic::axi4::stream::bus_if_base*>::set(
            nullptr, "*.rx_agent.*", "vif", &rx);

    uvm::uvm_config_db<logic::axi4::stream::bus_if_base*>::set(
            nullptr, "*.tx_agent.*", "vif", &tx);

    uvm::uvm_config_db<logic::axi4::stream::bus_if_base*>::set(
            nullptr, "*.notify_agent.*", "vif", &notify);

    uvm::uvm_config_db<logic::axi4::stream::bus_if_base*>::set(
            nullptr, "*.configure_agent.*", "vif", &configure);

    uvm::uvm_config_db<logic::axi4::stream::reset_if*>::set(
            nullptr, "*.reset_agent.*", "vif", &reset);

    reset.aclk(aclk);
    reset.areset_n(areset_n);

    rx.aclk(aclk);
    rx.areset_n(areset_n);

    tx.aclk(aclk);
    tx.areset_n(areset_n);

    dut.aclk(aclk);
    dut.areset_n(areset_n);
    dut.rx_tready(rx.tready);
    dut.rx_tvalid(rx.tvalid);
    dut.rx_tlast(rx.tlast);
    dut.rx_tkeep(rx.tkeep);
    dut.rx_tstrb(rx.tstrb);
    dut.rx_tuser(rx.tuser);
    dut.rx_tdata(rx.tdata);
    dut.rx_tdest(rx.tdest);
    dut.rx_tid(rx.tid);

    dut.tx_tready(tx.tready);
    dut.tx_tvalid(tx.tvalid);
    dut.tx_tlast(tx.tlast);
    dut.tx_tkeep(tx.tkeep);
    dut.tx_tstrb(tx.tstrb);
    dut.tx_tuser(tx.tuser);
    dut.tx_tdata(tx.tdata);
    dut.tx_tdest(tx.tdest);
    dut.tx_tid(tx.tid);

    dut.notify_tready(notify.tready);
    dut.notify_tvalid(notify.tvalid);
    dut.notify_tlast(notify.tlast);
    dut.notify_tkeep(notify.tkeep);
    dut.notify_tstrb(notify.tstrb);
    dut.notify_tuser(notify.tuser);
    dut.notify_tdata(notify.tdata);
    dut.notify_tdest(notify.tdest);
    dut.notify_tid(notify.tid);

    dut.configure_tready(configure.tready);
    dut.configure_tvalid(configure.tvalid);
    dut.configure_tlast(configure.tlast);
    dut.configure_tkeep(configure.tkeep);
    dut.configure_tstrb(configure.tstrb);
    dut.configure_tuser(configure.tuser);
    dut.configure_tdata(configure.tdata);
    dut.configure_tdest(configure.tdest);
    dut.configure_tid(configure.tid);

    uvm::run_test("test");

    uvm::uvm_config_db<bool>::get(nullptr, "*", "test_passed", test_passed);

    return test_passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
