module color_mapper (input  logic        clk,
                     input  logic        blank,
                     input  logic [9:0]  x, y,
                     input  logic [31:0] control,
                     output logic [3:0]  red, green, blue);

   logic [7:0] index;
   logic [11:0] rgb;
   logic [11:0] pallete [256][16];
   logic [3:0] pixels [256][256];
   logic [7:0] indices [1200];

   assign index = indices[(y / 16) * 40 + x / 16];
   assign rgb = pallete[index][pixels[index][(y % 16) * 16 + x % 16]];
   /*
   sprite sprite0 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(0),
      .control(control),
      .rgb(rgbs[0]));

   sprite sprite1 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(1),
      .control(control),
      .rgb(rgbs[1]));

   sprite sprite2 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(2),
      .control(control),
      .rgb(rgbs[2]));

   sprite sprite3 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(3),
      .control(control),
      .rgb(rgbs[3]));

   sprite sprite4 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(4),
      .control(control),
      .rgb(rgbs[4]));

   sprite sprite5 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(5),
      .control(control),
      .rgb(rgbs[5]));

   sprite sprite6 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(6),
      .control(control),
      .rgb(rgbs[6]));

   sprite sprite7 (
      .clk(clk),
      .x(x % 16),
      .y(y % 16),
      .index(7),
      .control(control),
      .rgb(rgbs[7]));
   */
   always_ff @ (posedge clk)
   begin
      if (control[31:28] == 4'h1)
         pixels[control[27:20]][control[15:12] * 16 + control[19:16]] <= control[11:0];
      else if (control[31:28] == 4'h2)
         indices[control[21:16] * 40 + control[27:22]] <= control[7:0];
   end

   always_comb
   begin
      if (~blank)
         begin
            red = 4'h0;
            green = 4'h0;
            blue = 4'h0;
         end
      else
         begin
            red = rgb[11:8];
            green = rgb[7:4];
            blue = rgb[3:0];
         end
   end

endmodule
