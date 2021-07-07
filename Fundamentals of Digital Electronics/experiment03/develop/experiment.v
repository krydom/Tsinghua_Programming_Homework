module experiment(
	input [3:0] a, b, k,      // 输入代表a,b和k
	input clk, 
	output reg [7:0] light,   // 控制数码管输出
   output reg [3:0] sel      // 选择在哪个数码管输出
);

reg sign;
reg [1:0] cur;
reg [7:0] ans;               // 运算结果
reg [3:0] data;              // 输出值
integer cnt;

always @ (a or b or k)       // 运算
begin
    sign = 0;
    ans = 0;
    case (k[1:0])            // 控制运算类型
		  2'b00: ans = 0;
        2'b01: ans = a + b;
        2'b10:
            begin
                {sign, ans[3:0]} = a - b;
                if (sign)
                    ans[3:0] = b - a;
            end
        2'b11: ans = a * b;
    endcase
end

always @ (posedge clk)
begin
    cnt = cnt + 1;
    if (cnt == 5000)
    begin
        cnt = 0;
        cur = cur + 1;
    end
end


always @ (*) //选择模块，十进制输出
begin
    sel = 4'b1111;
    case (cur)
        2'b00: 
		      begin 
				    data = ans % 10;
					 sel = 4'b1110;
				end
        2'b01: 
		      begin 
				    data = ans / 10 % 10;
					 sel = 4'b1101; 
				end
        2'b10:
		      begin 
				    data = ans / 100; 
				    sel = 4'b1011; 
				end
        2'b11: 
		      begin 
				    data = (sign) ? 4'hA : 4'h0; 
				    sel = 4'b0111; 
				end
    endcase
end


always @ (*)                      // 数码管输出
begin
    light[0] = 0;
    case (data[3:0])
        4'h0: light[7:1] = 7'b1111110;
        4'h1: light[7:1] = 7'b0110000;
        4'h2: light[7:1] = 7'b1101101;
        4'h3: light[7:1] = 7'b1111001;
        4'h4: light[7:1] = 7'b0110011;
        4'h5: light[7:1] = 7'b1011011;
        4'h6: light[7:1] = 7'b1011111;
        4'h7: light[7:1] = 7'b1110000;
        4'h8: light[7:1] = 7'b1111111;
        4'h9: light[7:1] = 7'b1111011;
        4'hA: light[7:1] = 7'b0000001;
    endcase
end

endmodule

