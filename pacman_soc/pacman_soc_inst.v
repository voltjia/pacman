	pacman_soc u0 (
		.clk_clk                        (<connected-to-clk_clk>),                        //                     clk.clk
		.control_export                 (<connected-to-control_export>),                 //                 control.export
		.key_external_connection_export (<connected-to-key_external_connection_export>), // key_external_connection.export
		.reset_reset_n                  (<connected-to-reset_reset_n>),                  //                   reset.reset_n
		.sdram_clk_clk                  (<connected-to-sdram_clk_clk>),                  //               sdram_clk.clk
		.sdram_wire_addr                (<connected-to-sdram_wire_addr>),                //              sdram_wire.addr
		.sdram_wire_ba                  (<connected-to-sdram_wire_ba>),                  //                        .ba
		.sdram_wire_cas_n               (<connected-to-sdram_wire_cas_n>),               //                        .cas_n
		.sdram_wire_cke                 (<connected-to-sdram_wire_cke>),                 //                        .cke
		.sdram_wire_cs_n                (<connected-to-sdram_wire_cs_n>),                //                        .cs_n
		.sdram_wire_dq                  (<connected-to-sdram_wire_dq>),                  //                        .dq
		.sdram_wire_dqm                 (<connected-to-sdram_wire_dqm>),                 //                        .dqm
		.sdram_wire_ras_n               (<connected-to-sdram_wire_ras_n>),               //                        .ras_n
		.sdram_wire_we_n                (<connected-to-sdram_wire_we_n>),                //                        .we_n
		.spi_MISO                       (<connected-to-spi_MISO>),                       //                     spi.MISO
		.spi_MOSI                       (<connected-to-spi_MOSI>),                       //                        .MOSI
		.spi_SCLK                       (<connected-to-spi_SCLK>),                       //                        .SCLK
		.spi_SS_n                       (<connected-to-spi_SS_n>),                       //                        .SS_n
		.usb_gpx_export                 (<connected-to-usb_gpx_export>),                 //                 usb_gpx.export
		.usb_irq_export                 (<connected-to-usb_irq_export>),                 //                 usb_irq.export
		.usb_rst_export                 (<connected-to-usb_rst_export>)                  //                 usb_rst.export
	);

