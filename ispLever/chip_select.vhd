library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity chip_select is
	Port (
		a11 : In std_logic;
		a10 : In std_logic;
		a9  : In std_logic;
		a8  : In std_logic;
		wr  : In std_logic;

		ram_cs  	: Out std_logic;
		adc_cs  	: Out std_logic;
		oled_cs 	: Out std_logic;
		oled_dc 	: Out std_logic;
		wr_inverted	: Out std_logic	
	);
	attribute LOC : string;
	attribute LOC of ram_cs		: signal is "P19";
	attribute LOC of adc_cs		: signal is "P18";
	attribute LOC of oled_cs	: signal is "P17";
	attribute LOC of oled_dc	: signal is "P16";
	attribute LOC of wr_inverted	: signal is "P15";
	

	attribute LOC of a11		: signal is "P1";
	attribute LOC of a10		: signal is "P2";
	attribute LOC of a9		: signal is "P3";
	attribute LOC of a8		: signal is "P4";
	attribute LOC of wr		: signal is "P5";
end chip_select;

architecture behave of chip_select is begin
	oled_cs <= (a11 OR a10 OR a9);
	oled_dc <= (a11 OR a10 OR (NOT a9));
	adc_cs	<= (a11 OR (NOT a10));
	ram_cs	<= (NOT a11);
	wr_inverted <= not wr;

end behave;
