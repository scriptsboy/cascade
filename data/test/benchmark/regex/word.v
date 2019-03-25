reg[31:0] count = 0;
reg[31:0] state = 0;
reg[31:0] i = 0;
reg[31:0] ie = 0;
reg[7:0] char;

integer itr = 1;
stream s = $fopen("data/test/benchmark/regex/iliad.hex");

always @(posedge clock.val) begin
  $get(s, char);
  if ($eof(s)) begin
    if (itr == 1) begin
      $write(count);
      $finish(0);
    end else begin
      itr <= itr + 1;
      $seek(s, 0);
      $get(s, char);
    end
  end

  if (state > 0) begin
    ie <= ie + 1;
  end
  case (state)
    32'd0:
      state <= 2;
    32'd1: case(char) 
      8'h6c: begin
        state <= 7;
      end
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    32'd2: case(char) 
      8'h41: begin
        state <= 4;
      end
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    32'd3: case(char) 
      8'h6c: begin
        state <= 1;
      end
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    32'd4: case(char) 
      8'h63: begin
        state <= 6;
      end
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    32'd5: case(char) 
      8'h69: begin
        state <= 3;
      end
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    32'd6: case(char) 
      8'h68: begin
        state <= 5;
      end
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    32'd7: case(char) 
      8'h65: begin
        state <= 8;
      end
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    32'd8: case(char) 
      8'h73: begin
        //$display("Match %d:%d", i, ie);
        i <= ie + 1;
        count <= count + 1;
        state <= 2;
      end
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    32'd9: case(char) 
      default: begin
        i <= ie + 1;
        state <= 2;
      end
    endcase
    default: begin
      $display("Unrecognized state!");
      $finish;
    end
  endcase
end
