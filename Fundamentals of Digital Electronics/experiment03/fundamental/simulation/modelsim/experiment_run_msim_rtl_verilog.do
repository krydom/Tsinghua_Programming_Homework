transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/asus/Desktop/test {C:/Users/asus/Desktop/test/test.v}

vlog -vlog01compat -work work +incdir+C:/Users/asus/Desktop/test/simulation/modelsim {C:/Users/asus/Desktop/test/simulation/modelsim/experiment.vt}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  experiment_vlg_tst

add wave *
view structure
view signals
run -all
