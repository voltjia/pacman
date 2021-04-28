
module pacman_soc (
	clk_clk,
	gpio_0_in_port,
	gpio_0_out_port,
	gpio_1_in_port,
	gpio_1_out_port,
	gpio_2_in_port,
	gpio_2_out_port,
	gpio_3_in_port,
	gpio_3_out_port,
	reset_reset_n,
	sdram_clk_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	spi_MISO,
	spi_MOSI,
	spi_SCLK,
	spi_SS_n,
	usb_gpx_export,
	usb_irq_export,
	usb_rst_export,
	control_export);	

	input		clk_clk;
	input	[31:0]	gpio_0_in_port;
	output	[31:0]	gpio_0_out_port;
	input	[31:0]	gpio_1_in_port;
	output	[31:0]	gpio_1_out_port;
	input	[31:0]	gpio_2_in_port;
	output	[31:0]	gpio_2_out_port;
	input	[31:0]	gpio_3_in_port;
	output	[31:0]	gpio_3_out_port;
	input		reset_reset_n;
	output		sdram_clk_clk;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	input		spi_MISO;
	output		spi_MOSI;
	output		spi_SCLK;
	output		spi_SS_n;
	input		usb_gpx_export;
	input		usb_irq_export;
	output		usb_rst_export;
	output	[31:0]	control_export;
endmodule
