# SHELL:=/bin/bash

all:

install:
	echo "export PIPELINE_TOOLKIT_ROOT=$(PWD)" >setup.sh
	mkdir -p $(PWD)/lib
	echo "export LD_LIBRARY_PATH=$(PWD)/lib:$(LD_LIBRARY_PATH)" >>setup.sh
	cd $(PWD)/http_request_parser
	make
	ln -s $(PWD)/http_request_parser/lib/libhttp_request_parser.so $(PWD)/lib/
	cd $(PWD)/hash_table
	make
	ln -s $(PWD)/hash_table/lib/libhash_table.so $(PWD)/lib/
	cd $(PWD)
	# for util in "http_request_parser hash_table"
	# do
		# sdir="${PIPELINE_TOOLKIT_ROOT}/${util}/lib"
		# slib="${sdir}/lib${util}.so"
		# if [ -e ${slib} ] ; then
			# echo "creating link to ${slib}"
			# ln -s -T ${slib} ${tdir}/
		# fi
	# done
