module color_mapper (input  logic        clk,
                     input  logic        blank,
                     input  logic [9:0]  x, y,
                     input  logic [31:0] control,
                     output logic [7:0]  red, green, blue);

   logic load;
   logic [7:0] index;
   logic [31:0] rgba;
   logic [31:0] rgba0;
   logic [31:0] rgba1;
   logic [8191:0] rgbas;
   logic [9599:0] mask;
   logic [9599:0] indices_in;
   logic [9599:0] indices_out;

   assign position = (control[21:16] * 40 + control[27:22]) * 8;
   assign rgbas = { {254{32'hFFFFFFFF}}, rgba1[31:0], rgba0[31:0] };

   shift_register #(.N(9600)) shift_register (
      .clk(clk),
      .shift_enable(0),
      .load(load),
      .data_in(indices_in),
      .data_out(indices_out));

   sprite sprite0 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(0),
      .control(control),
      .rgba(rgba0));

   sprite sprite1 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(1),
      .control(control),
      .rgba(rgba1));

   mux960028 mux960028 (
      .data_in(indices_out),
      .select((y / 16) * 40 + x / 16),
      .data_out(index));

   mux8192232 mux8192232 (
      .data_in(rgbas),
      .select(index),
      .data_out(rgba));

   mask_generator #(.N(9600)) mask_generator (
      .position(position),
      .length(8),
      .mask(mask));

   always_ff @ (posedge clk)
   begin
      if (control[31:28] == 4'h2)
         begin
            load <= 1;
            indices_in <= (indices_out & ~mask) | (control[7:0] << position);
         end
      else
         load <= 0;
   end

   always_comb
   begin
      if (~blank)
         begin
            red = 8'h00;
            green = 8'h00;
            blue = 8'h00;
         end
      else
         begin
            red = rgba[31:24];
            green = rgba[23:16];
            blue = rgba[15:8];
         end
   end

endmodule
