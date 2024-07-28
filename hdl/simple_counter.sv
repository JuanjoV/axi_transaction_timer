`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 07/22/2024 12:33:56 PM
// Design Name: 
// Module Name: simple_counter
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


module simple_counter #(
    parameter integer COUNT_SIZE = 32
    )(
    input logic clk,
    input logic rst_n,
    input logic i_enable,
    input logic i_load,
    input logic [COUNT_SIZE-1:0] i_load_value,
    output logic [COUNT_SIZE-1:0] o_count,
    output logic o_overflow
    );

    logic [COUNT_SIZE-1:0] count_next;
    logic overflow_next;


    always_ff @(posedge clk) begin
        if (rst_n) begin
            if (i_enable) begin
                o_count <= count_next;
            end
            else begin
                o_count <= i_load ? i_load_value : o_count;
            end
            o_overflow <= i_load ? 1'b0 : overflow_next;
        end
        else begin
            o_overflow <= 1'b0;
            o_count <= 'd0;
        end
    end


    always_comb begin
        count_next = o_count + 'd1;
        overflow_next = (count_next == 0) | o_overflow;
    end
endmodule
