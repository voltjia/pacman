module pacman(input  		MAX10_CLK1_50,
				  input	[1:0] KEY,
				  output [7:0] HEX0,
				  output [7:0] HEX1,
				  output [7:0] HEX2,
				  output [7:0] HEX3,
				  output [7:0] HEX4,
				  output [7:0] HEX5,
				  output 		VGA_HS,
				  output			VGA_VS,
				  output [3:0] VGA_R,
				  output [3:0] VGA_G,
				  output [3:0] VGA_B);
									
	logic reset, blank, sync;
	logic [7:0] red, green, blue;
	logic [9:0] draw_x, draw_y;
	
	assign reset = ~KEY[0];

	assign HEX5 = 8'b10001100;
	assign HEX4 = 8'b10001000;
	assign HEX3 = 8'b11000110;
	assign HEX2 = 8'b10001100;
	assign HEX1 = 8'b10001000;
	assign HEX0 = 8'b11000110;
	
	assign VGA_R = red[7:4];
	assign VGA_G = green[7:4];
	assign VGA_B = blue[7:4];

	vga_controller vga_controller(.clk(MAX10_CLK1_50), .reset(reset), .hs(VGA_HS), .vs(VGA_VS), .blank, .sync, .draw_x, .draw_y);
	color_mapper color_mapper(.*);

endmodule
