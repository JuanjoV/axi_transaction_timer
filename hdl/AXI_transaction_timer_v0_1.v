
`timescale 1 ns / 1 ps

	module AXI_transaction_timer_v0_1 #
	(
		// Users to add parameters here
		parameter integer AXI_MONITOR_ADDR_SIZE = 32,
		// User parameters ends
		// Do not modify the parameters beyond this line


		// Parameters of Axi Slave Bus Interface S00_AXI
		parameter integer C_S00_AXI_DATA_WIDTH	= 32,
		parameter integer C_S00_AXI_ADDR_WIDTH	= 6
	)
	(
		// Users to add ports here
		input wire s01_axi_awready,
		input wire s01_axi_awvalid,
		input wire [AXI_MONITOR_ADDR_SIZE-1:0] s01_axi_awaddr,
		input wire s01_axi_arready,
		input wire s01_axi_arvalid,
		input wire [AXI_MONITOR_ADDR_SIZE-1:0] s01_axi_araddr,

		// User ports ends
		// Do not modify the ports beyond this line


		// Ports of Axi Slave Bus Interface S00_AXI
		input wire  s00_axi_aclk,
		input wire  s00_axi_aresetn,
		input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_awaddr,
		input wire [2 : 0] s00_axi_awprot,
		input wire  s00_axi_awvalid,
		output wire  s00_axi_awready,
		input wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_wdata,
		input wire [(C_S00_AXI_DATA_WIDTH/8)-1 : 0] s00_axi_wstrb,
		input wire  s00_axi_wvalid,
		output wire  s00_axi_wready,
		output wire [1 : 0] s00_axi_bresp,
		output wire  s00_axi_bvalid,
		input wire  s00_axi_bready,
		input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_araddr,
		input wire [2 : 0] s00_axi_arprot,
		input wire  s00_axi_arvalid,
		output wire  s00_axi_arready,
		output wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_rdata,
		output wire [1 : 0] s00_axi_rresp,
		output wire  s00_axi_rvalid,
		input wire  s00_axi_rready
	);

	wire [31:0] current_count;
	wire [31:0] count_reg;
	wire [31:0] start_address;
	wire [31:0] stop_address;
	wire [31:0] status_reg;

	wire enable_sm;
	wire count_valid;
	wire sm_busy;
	wire sm_waiting;
	wire count_overflow;
	wire count_enable;
	wire count_load;

// Instantiation of Axi Bus Interface S00_AXI
	AXI_transaction_timer_v0_1_S00_AXI # ( 
		.C_S_AXI_DATA_WIDTH(C_S00_AXI_DATA_WIDTH),
		.C_S_AXI_ADDR_WIDTH(C_S00_AXI_ADDR_WIDTH)
	) AXI_transaction_timer_v0_1_S00_AXI_inst (
		.S_AXI_ACLK(s00_axi_aclk),
		.S_AXI_ARESETN(s00_axi_aresetn),
		.S_AXI_AWADDR(s00_axi_awaddr),
		.S_AXI_AWPROT(s00_axi_awprot),
		.S_AXI_AWVALID(s00_axi_awvalid),
		.S_AXI_AWREADY(s00_axi_awready),
		.S_AXI_WDATA(s00_axi_wdata),
		.S_AXI_WSTRB(s00_axi_wstrb),
		.S_AXI_WVALID(s00_axi_wvalid),
		.S_AXI_WREADY(s00_axi_wready),
		.S_AXI_BRESP(s00_axi_bresp),
		.S_AXI_BVALID(s00_axi_bvalid),
		.S_AXI_BREADY(s00_axi_bready),
		.S_AXI_ARADDR(s00_axi_araddr),
		.S_AXI_ARPROT(s00_axi_arprot),
		.S_AXI_ARVALID(s00_axi_arvalid),
		.S_AXI_ARREADY(s00_axi_arready),
		.S_AXI_RDATA(s00_axi_rdata),
		.S_AXI_RRESP(s00_axi_rresp),
		.S_AXI_RVALID(s00_axi_rvalid),
		.S_AXI_RREADY(s00_axi_rready),
		.ip_count(count_reg),
		.ip_overflow(count_overflow),
		.ip_busy(sm_busy),
		.ip_waiting(sm_waiting),
		.ip_valid(count_valid),
		.ip_enable(enable_sm),
		.ip_start_address(start_address),
		.ip_stop_address(stop_address)
	);

	// Add user logic here

	transaction_timer_sm #(
		.REG_SIZE(32),
		.ADDR_SIZE(AXI_MONITOR_ADDR_SIZE)
	) u_transaction_timer_sm (
		.clk(s00_axi_aclk),
		.rst_n(s00_axi_aresetn),
		.i_start_address(start_address),
		.i_stop_address(stop_address),
		.i_enable(enable_sm),
		.i_axi_awvalid(s01_axi_awvalid),
		.i_axi_awready(s01_axi_awready),
		.i_axi_awaddr(s01_axi_awaddr),
		.i_axi_arvalid(s01_axi_arvalid),
		.i_axi_arready(s01_axi_arready),
		.i_axi_araddr(s01_axi_araddr),
		.i_count(current_count),
		.o_valid(count_valid),
		.o_time(count_reg),
		.o_counter_enable(count_enable),
		.o_counter_load(count_load),
		.o_busy(sm_busy),
		.o_waiting(sm_waiting)
	);

	simple_counter #(
		.COUNT_SIZE(32)
	)  u_simple_counter (
		.clk(s00_axi_aclk),
		.rst_n(s00_axi_aresetn),
		.i_enable(count_enable),
		.i_load(count_load),
		.i_load_value(32'd0),
		.o_count(current_count),
		.o_overflow(count_overflow)
	);

	// User logic ends

	endmodule
