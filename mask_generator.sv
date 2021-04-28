module mask_generator #(N = 32) (input  [31:0]  position,
                                 input  [31:0]  length,
                                 output [N-1:0] mask);

   assign mask = ((1 << length) - 1) << position;

endmodule
