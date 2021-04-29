module sprite (input         clk,
               input  [3:0]  x,
               input  [3:0]  y,
               input  [7:0]  index,
               input  [31:0] control,
               output [11:0] rgb);
   /*
   logic [11:0] rgbs [256];

   assign rgb = rgbs[y * 16 + x];

   always_ff @ (posedge clk)
   begin
      if (control[31:28] == 4'h1 & control[27:20] == index)
         rgbs[control[15:12] * 16 + control[19:16]] <= control[11:0];
   end
   */
endmodule
