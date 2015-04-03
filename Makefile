# SHELL:=/bin/bash

all:

install:
	echo "export PIPELINE_TOOLKIT_ROOT=$(PWD)" >setup.sh
	mkdir -p $(PIPELINE_TOOLKIT_ROOT)/lib
	cd $(PIPELINE_TOOLKIT_ROOT)/http_request_parser
	make
	ln -s $(PIPELINE_TOOLKIT_ROOT)/http_request_parser/lib/libhttp_request_parser.so $(PIPELINE_TOOLKIT_ROOT)/lib/
	cd $(PIPELINE_TOOLKIT_ROOT)/hash_table
	make
	ln -s $(PIPELINE_TOOLKIT_ROOT)/hash_table/lib/libhash_table.so $(PIPELINE_TOOLKIT_ROOT)/lib/
	cd $(PIPELINE_TOOLKIT_ROOT)
	# for util in "http_request_parser hash_table"
	# do
		# sdir="${PIPELINE_TOOLKIT_ROOT}/${util}/lib"
		# slib="${sdir}/lib${util}.so"
		# if [ -e ${slib} ] ; then
			# echo "creating link to ${slib}"
			# ln -s -T ${slib} ${tdir}/
		# fi
	# done
