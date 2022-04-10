spec_src_dir := $(abspath 29222-capif_stage3-h20)
output_dir := $(abspath ../lib/openapi)
spec_output_dir := $(abspath ./build/compiled_spec)
doc_output_dir := $(abspath ./build/docs)
tmp_dir := /tmp/capif

yamls := $(wildcard $(spec_src_dir)/TS*.yaml)
capif_yamls := $(wildcard $(spec_src_dir)/TS29222_CAPIF*.yaml)
capif_htmls := $(patsubst $(spec_src_dir)/%.yaml, $(doc_output_dir)/%.html, $(capif_yamls))

merged_api_version := h20

generator_flag := --skip-validate-spec

.PHONY: all, docs, ccf-pistache, client-cpp, client-js, clean
all: ccf-pistache client-cpp client-js

docs: $(capif_htmls)

ccf-pistache: $(spec_output_dir)/ccf.yaml
	mkdir -p $(output_dir)/ccf/pistache
	openapi-generator-cli generate -o $(output_dir)/ccf/pistache \
	  -g cpp-pistache-server $(generator_flag) \
	  -i $^

ccf-restbed: $(spec_output_dir)/ccf.yaml
	mkdir -p $(output_dir)/ccf/restbed
	openapi-generator-cli generate -o $(output_dir)/ccf/restbed \
	  -g cpp-restbed-server $(generator_flag) \
	  -i $^

ccf-qhttpengine: $(spec_output_dir)/ccf.yaml
	mkdir -p $(output_dir)/ccf/qhttpengine
	openapi-generator-cli generate -o $(output_dir)/ccf/qhttpengine \
	  -g cpp-qt-qhttpengine-server $(generator_flag) \
	  -i $^

client-cpp: $(spec_output_dir)/capif.yaml
	mkdir -p $(output_dir)/client/cpp
	openapi-generator-cli generate -o $(output_dir)/client/cpp \
	  -g cpp-restsdk $(generator_flag) \
	  -i $^

client-js: $(spec_output_dir)/capif.yaml
	mkdir -p $(output_dir)/client/js
	openapi-generator-cli generate -o $(output_dir)/client/js \
	  -g javascript $(generator_flag) \
	  -i $^

$(spec_output_dir)/%.yaml: openapi-merge-%.json $(yamls)
	mkdir -p $(@D)
	mkdir -p $(tmp_dir)

	@echo Merging used APIs\' specifications
	cp $^ $(tmp_dir)
	cd $(tmp_dir) && openapi-merge-cli -c $<

	# cp $(tmp_dir)/output.yaml $@
	# cp $(yamls) $(@D)

	@echo Compiling specifications to get rid off $$ref
	openapi-generator-cli generate -o $(tmp_dir) -g openapi-yaml -i $(tmp_dir)/output.yaml
	mv $(tmp_dir)/openapi/openapi.yaml $@

	# @echo Removing optional operationId to prevent duplication
	# yq -i 'del(.. | select(has("operationId")).operationId)' $@

	@echo Removing useless field
	yq -i 'del(.servers)' $@
	yq -i 'del(.externalDocs)' $@
	yq -i 'del(.info.description)' $@

	@echo Updating description
	yq -i '.info.title="Merged 3GPP CAPIF API. Based on $<"' $@
	yq -i '.info.version="$(merged_api_version)"' $@

	# @echo Validating the generated specification
	# openapi-generator-cli validate -i $@

	rm -rf $(tmp_dir)

$(doc_output_dir)/%.html: $(spec_src_dir)/%.yaml
	mkdir -p $(@D)
	redoc-cli build -o $@ $^

clean:
	rm -rf $(spec_output_dir)
	rm -rf $(doc_output_dir)
	rm -rf $(output_dir)
