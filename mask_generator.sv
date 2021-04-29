module mask_generator #(N = 32) (input  [15:0]  position,
                                 input  [15:0]  length,
                                 output [N-1:0] mask);

   assign mask = ((1 << length) - 1) << position;

endmodule
