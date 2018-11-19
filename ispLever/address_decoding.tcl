
########## Tcl recorder starts at 09/12/18 08:55:19 ##########

set version "2.0"
set proj_dir "C:/Users/akselsl/Documents/Byggern/byggern-TTK4155"
cd $proj_dir

# Get directory paths
set pver $version
regsub -all {\.} $pver {_} pver
set lscfile "lsc_"
append lscfile $pver ".ini"
set lsvini_dir [lindex [array get env LSC_INI_PATH] 1]
set lsvini_path [file join $lsvini_dir $lscfile]
if {[catch {set fid [open $lsvini_path]} msg]} {
	 puts "File Open Error: $lsvini_path"
	 return false
} else {set data [read $fid]; close $fid }
foreach line [split $data '\n'] { 
	set lline [string tolower $line]
	set lline [string trim $lline]
	if {[string compare $lline "\[paths\]"] == 0} { set path 1; continue}
	if {$path && [regexp {^\[} $lline]} {set path 0; break}
	if {$path && [regexp {^bin} $lline]} {set cpld_bin $line; continue}
	if {$path && [regexp {^fpgapath} $lline]} {set fpga_dir $line; continue}
	if {$path && [regexp {^fpgabinpath} $lline]} {set fpga_bin $line}}

set cpld_bin [string range $cpld_bin [expr [string first "=" $cpld_bin]+1] end]
regsub -all "\"" $cpld_bin "" cpld_bin
set cpld_bin [file join $cpld_bin]
set install_dir [string range $cpld_bin 0 [expr [string first "ispcpld" $cpld_bin]-2]]
regsub -all "\"" $install_dir "" install_dir
set install_dir [file join $install_dir]
set fpga_dir [string range $fpga_dir [expr [string first "=" $fpga_dir]+1] end]
regsub -all "\"" $fpga_dir "" fpga_dir
set fpga_dir [file join $fpga_dir]
set fpga_bin [string range $fpga_bin [expr [string first "=" $fpga_bin]+1] end]
regsub -all "\"" $fpga_bin "" fpga_bin
set fpga_bin [file join $fpga_bin]

if {[string match "*$fpga_bin;*" $env(PATH)] == 0 } {
   set env(PATH) "$fpga_bin;$env(PATH)" }

if {[string match "*$cpld_bin;*" $env(PATH)] == 0 } {
   set env(PATH) "$cpld_bin;$env(PATH)" }

lappend auto_path [file join $install_dir "ispcpld" "tcltk" "lib" "ispwidget" "runproc"]
package require runcmd

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 08:55:19 ###########


########## Tcl recorder starts at 09/12/18 09:23:32 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:23:33 ###########


########## Tcl recorder starts at 09/12/18 09:26:07 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:26:07 ###########


########## Tcl recorder starts at 09/12/18 09:30:40 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:30:40 ###########


########## Tcl recorder starts at 09/12/18 09:30:44 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:30:44 ###########


########## Tcl recorder starts at 09/12/18 09:32:01 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:32:01 ###########


########## Tcl recorder starts at 09/12/18 09:34:35 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:34:35 ###########


########## Tcl recorder starts at 09/12/18 09:34:37 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:34:37 ###########


########## Tcl recorder starts at 09/12/18 09:35:09 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:35:09 ###########


########## Tcl recorder starts at 09/12/18 09:35:12 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:35:12 ###########


########## Tcl recorder starts at 09/12/18 09:35:47 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:35:47 ###########


########## Tcl recorder starts at 09/12/18 09:35:59 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:35:59 ###########


########## Tcl recorder starts at 09/12/18 09:36:53 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:36:53 ###########


########## Tcl recorder starts at 09/12/18 09:36:56 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:36:56 ###########


########## Tcl recorder starts at 09/12/18 09:38:36 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:38:36 ###########


########## Tcl recorder starts at 09/12/18 09:38:39 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:38:39 ###########


########## Tcl recorder starts at 09/12/18 09:41:23 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:41:23 ###########


########## Tcl recorder starts at 09/12/18 09:41:27 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:41:27 ###########


########## Tcl recorder starts at 09/12/18 09:46:36 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:46:36 ###########


########## Tcl recorder starts at 09/12/18 09:46:38 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 09:46:38 ###########


########## Tcl recorder starts at 09/12/18 14:24:18 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 14:24:18 ###########


########## Tcl recorder starts at 09/12/18 14:24:27 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/12/18 14:24:27 ###########


########## Tcl recorder starts at 09/19/18 08:53:47 ##########

set version "2.0"
set proj_dir "C:/Users/torbjfug/Documents/Byggern/byggern-TTK4155/ispLever"
cd $proj_dir

# Get directory paths
set pver $version
regsub -all {\.} $pver {_} pver
set lscfile "lsc_"
append lscfile $pver ".ini"
set lsvini_dir [lindex [array get env LSC_INI_PATH] 1]
set lsvini_path [file join $lsvini_dir $lscfile]
if {[catch {set fid [open $lsvini_path]} msg]} {
	 puts "File Open Error: $lsvini_path"
	 return false
} else {set data [read $fid]; close $fid }
foreach line [split $data '\n'] { 
	set lline [string tolower $line]
	set lline [string trim $lline]
	if {[string compare $lline "\[paths\]"] == 0} { set path 1; continue}
	if {$path && [regexp {^\[} $lline]} {set path 0; break}
	if {$path && [regexp {^bin} $lline]} {set cpld_bin $line; continue}
	if {$path && [regexp {^fpgapath} $lline]} {set fpga_dir $line; continue}
	if {$path && [regexp {^fpgabinpath} $lline]} {set fpga_bin $line}}

set cpld_bin [string range $cpld_bin [expr [string first "=" $cpld_bin]+1] end]
regsub -all "\"" $cpld_bin "" cpld_bin
set cpld_bin [file join $cpld_bin]
set install_dir [string range $cpld_bin 0 [expr [string first "ispcpld" $cpld_bin]-2]]
regsub -all "\"" $install_dir "" install_dir
set install_dir [file join $install_dir]
set fpga_dir [string range $fpga_dir [expr [string first "=" $fpga_dir]+1] end]
regsub -all "\"" $fpga_dir "" fpga_dir
set fpga_dir [file join $fpga_dir]
set fpga_bin [string range $fpga_bin [expr [string first "=" $fpga_bin]+1] end]
regsub -all "\"" $fpga_bin "" fpga_bin
set fpga_bin [file join $fpga_bin]

if {[string match "*$fpga_bin;*" $env(PATH)] == 0 } {
   set env(PATH) "$fpga_bin;$env(PATH)" }

if {[string match "*$cpld_bin;*" $env(PATH)] == 0 } {
   set env(PATH) "$cpld_bin;$env(PATH)" }

lappend auto_path [file join $install_dir "ispcpld" "tcltk" "lib" "ispwidget" "runproc"]
package require runcmd

# Commands to make the Process: 
# Create Fuse Map
if [runCmd "\"$cpld_bin/synsvf\" -exe \"$install_dir/ispvmsystem/ispufw\" -prj address_decoding -if address_decoding.jed -j2s -log address_decoding.svl "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 08:53:47 ###########


########## Tcl recorder starts at 09/19/18 09:33:54 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 09:33:54 ###########


########## Tcl recorder starts at 09/19/18 09:33:57 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 09:33:57 ###########


########## Tcl recorder starts at 09/19/18 09:41:15 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 09:41:15 ###########


########## Tcl recorder starts at 09/19/18 09:42:12 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 09:42:12 ###########


########## Tcl recorder starts at 09/19/18 09:42:14 ##########

# Commands to make the Process: 
# Chip Report
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 09:42:14 ###########


########## Tcl recorder starts at 09/19/18 09:43:01 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 09:43:01 ###########


########## Tcl recorder starts at 09/19/18 09:43:24 ##########

# Commands to make the Process: 
# JEDEC File
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 09:43:24 ###########


########## Tcl recorder starts at 09/19/18 10:58:35 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 09/19/18 10:58:35 ###########


########## Tcl recorder starts at 11/19/18 14:36:27 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"chip_select.vhd\" -o \"chip_select.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 11/19/18 14:36:27 ###########


########## Tcl recorder starts at 11/19/18 14:36:41 ##########

# Commands to make the Process: 
# JEDEC File
if [catch {open chip_select.cmd w} rspFile] {
	puts stderr "Cannot create response file chip_select.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: address_decoding.sty
PROJECT: chip_select
WORKING_PATH: \"$proj_dir\"
MODULE: chip_select
VHDL_FILE_LIST: chip_select.vhd
OUTPUT_FILE_NAME: chip_select
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e chip_select -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete chip_select.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"chip_select.edi\" -out \"chip_select.bl0\" -err automake.err -log \"chip_select.log\" -prj address_decoding -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"chip_select.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"chip_select.bl1\" -o \"address_decoding.bl2\" -omod chip_select -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" address_decoding.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" address_decoding.bl3 -pla -o address_decoding.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" address_decoding.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" address_decoding.tt3 -dev p16v8 -o address_decoding.jed -ivec NoInput.tmv -rep address_decoding.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 11/19/18 14:36:41 ###########

