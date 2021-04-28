module sprite (input         clk,
               input  [3:0]  x,
               input  [3:0]  y,
               input  [7:0]  index,
               input  [31:0] control,
               output [31:0] rgba);

   logic load;
   logic [31:0] position;
   logic [8191:0] mask;
   logic [8191:0] rgbas_in;
   logic [8191:0] rgbas_out;

   assign position = (control[15:12] * 16 + control[19:16]) * 32;

   always_ff @ (posedge clk)
   begin
      if (control[31:28] == 4'h1 & control[27:20] == index)
         begin
            load <= 1;
            rgbas_in <= (rgbas_out & ~mask)
               | ({ control[11:8], 4'h00,
                    control[7:4], 4'h00,
                    control[3:0], 4'h00, 8'hFF } << position);
         end
      else
         load <= 0;
   end

   mask_generator #(.N(8192)) mask_generator (
      .position(position),
      .length(32),
      .mask(mask));

   shift_register #(.N(8192)) shift_register (
      .clk(clk),
      .shift_enable(0),
      .load(load),
      .data_in(rgbas_in),
      .data_out(rgbas_out));

   mux8192232 mux8192232 (
      .data_in(rgbas_out),
      .select(y * 16 + x),
      .data_out(rgba));

endmodule
