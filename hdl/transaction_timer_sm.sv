`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 07/22/2024 12:33:56 PM
// Design Name: 
// Module Name: transaction_timer_sm
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module transaction_timer_sm #(
    parameter integer REG_SIZE = 32,
    parameter integer ADDR_SIZE = 32
    )(
    input logic clk,
    input logic rst_n,

    input logic [REG_SIZE-1:0] i_start_address,
    input logic [REG_SIZE-1:0] i_stop_address,
    input logic i_enable,

    input logic i_axi_awvalid,
    input logic i_axi_awready,
    input logic [ADDR_SIZE-1:0] i_axi_awaddr,
    input logic i_axi_arvalid,
    input logic i_axi_arready,
    input logic [ADDR_SIZE-1:0] i_axi_araddr,

    input logic [REG_SIZE-1:0] i_count,

    output logic o_valid,
    output logic [REG_SIZE-1:0] o_time,
    output logic o_counter_enable,
    output logic o_counter_load,
    output logic o_busy,
    output logic o_waiting

    );

    localparam logic [REG_SIZE-1:0] ADDR_MASK = (1 << ADDR_SIZE) - 'd1;

    logic axi_awcheck;
    logic axi_archeck;
    logic [REG_SIZE-1:0] time_next;
    logic valid_next;

    enum logic [2:0] {IDLE, RESET_COUNTER, WAIT_FOR_INPUT, WAIT_FOR_OUTPUT, SAVE_COUNT} state_reg, state_next;

    always_ff @(posedge clk) begin
        if (rst_n) begin
            state_reg <= state_next;
            o_time <= time_next;
            o_valid <= valid_next;
        end
        else begin
            state_reg <= IDLE;
            o_time <= 'd0;
            o_valid <= 1'b0;
        end
    end

    always_comb begin
        axi_awcheck = i_axi_awvalid & i_axi_awready;
        axi_archeck = i_axi_arvalid & i_axi_arready;
        time_next = o_time;
        o_counter_load = 1'b0;
        o_counter_enable = 1'b0;
        valid_next = o_valid;
        o_busy = 1'b0;
        o_waiting = 1'b0;

        state_next = state_reg;
        case(state_reg)
            IDLE: begin
                if (i_enable) begin
                    state_next = RESET_COUNTER;
                end
            end
            RESET_COUNTER: begin
                o_busy = 1'b1;
                o_counter_load = 1'b1;
                state_next = WAIT_FOR_INPUT;
            end
            WAIT_FOR_INPUT: begin
                o_busy = 1'b1;
                o_waiting = 1'b1;
                if (~i_enable) begin
                    state_next = IDLE;
                end
                else begin
                    if (axi_awcheck && (i_axi_awaddr == (i_start_address & ADDR_MASK))) begin
                        state_next = WAIT_FOR_OUTPUT;
                    end
                end
            end
            WAIT_FOR_OUTPUT: begin
                valid_next = 1'b0;
                o_busy = 1'b1;
                o_counter_enable = 1'b1;
                if (axi_archeck && (i_axi_araddr == (i_stop_address & ADDR_MASK))) begin
                    state_next = SAVE_COUNT;
                end
            end
            SAVE_COUNT: begin
                valid_next = 1'b1;
                state_next = IDLE;
                time_next = i_count;
            end
        endcase
    end

endmodule
