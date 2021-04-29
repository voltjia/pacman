/*
 * ECE385-HelperTools/PNG-To-Txt
 * Author: Rishi Thakkar
 *
 */

module  frameRAM
(
		input [5:0] data_In,
		input [7:0] write_address, read_address,
		input we, Clk,

		output logic [5:0] data_Out
);

// mem has width of 6 bits and a total of 256 addresses
logic [5:0] mem [0:255];

initial
begin
	 $readmemh("sprite_bytes/Pac-man.txt", mem);
end


always_ff @ (posedge Clk) begin
	if (we)
		mem[write_address] <= data_In;
	data_Out<= mem[read_address];
end

endmodule
