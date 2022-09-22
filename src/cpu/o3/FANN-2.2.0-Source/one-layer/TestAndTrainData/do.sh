#!/bin/csh
#

rm out-all 
rm out-*
set test = 1 
#
#
set ns = $1
set nf = $2 
while ( $test < 26) 

	echo  ${ns} ${nf} 1 > spectre.train
	cat train_${test}.data >> spectre.train
	cat train_${test}.data >> spectre.train
	# > spectre.train
	./simple_train 
#./xor_train
	sleep 5 
	echo  1 ${nf} 1 > spectre.data
	cat test_${test}.data >> spectre.data
	./xor_test > out-${test} 

	set error = ` grep difference out-${test} | sed -e 's/^.*.\=//' `

	echo "${test}	${error}" >> out-all  
	@ test++

end

#
#rm cros-*
#set group = $1 
##echo $group
#set allprogs = 25
#set train = 1
#set test = 1 
#
#
#while ( $test < 26) 
#	set train = 1
#	while ( $train < 26) 
#
##		set cmd = "head -n ${train} mysafes | tail -n 1 mysafes" 
##echo $cmd
## >> cros-test-${test}
#
#		if ( ${train} == ${test} ) then
#			echo "`head -n ${test} data${group} | tail -n 1 `" >> cros-test-${test}
#			#echo $test >> cros-test-${test}
#		else  
#			echo "`head -n ${train} data${group} | tail -n 1 `" >> cros-train-${test}
#		#	echo $train >> cros-train-${test}
#		endif
#		@ train++
#
#	end
#@ test++
#end
#
#
#set test = 1 
#
#while ( $test < 26) 
#	rm "train_${test}.data"
#	foreach bench ( `cat cros-train-${test} ` )
#		echo $bench
#		./read ${bench} 0   >> "train_${test}.data"
#		foreach bench ( ` ls ../all-pkis/susp/* ` )
#			./read ${bench} 1   >> "train_${test}.data"
#		end
#	end
#
#	rm "test_${test}.data"
#	foreach bench ( `cat cros-test-${test} ` )
#		echo $bench
#		./read ${bench} 0   >> "test_${test}.data"
##		foreach bench ( ` ls ../all-pkis/susp/* ` )
##			./read ${bench} 1   >> "train_${test}.data"
##		end
#	end
#
#@ test++
#end
#
#
#
#
#
#
#
#
#
#
#
##foreach all ( 1 2 3 4 5)
##set test = 1 
##end
#
#
#
#
#
#
#
#
#
#
##set safe = "" 
#
#
#
##echo "" > "../data/train.data"
#
##foreach all ( 1 2 3 4 5)
##foreach bench ( ` ls ../all-pkis/safes/* ` )
##./read ${bench} 0  >> "../data/train.data"
##end
#
#
#
##foreach bad ( 1 2 3 4 5  ) 
##foreach bench ( ` ls ../all-pkis/susp/* ` )
##./read ${bench} 1   >> "../data/train.data"
##end
#
##end
#
##end 
#
